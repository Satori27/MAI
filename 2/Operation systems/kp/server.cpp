#include <iostream>

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <sys/mman.h>
#include <map>


#include <sys/types.h>

#include <vector>

#include <limits.h>


#include <semaphore.h>

#include <sstream>

#include <stdio.h>

#include <string>

#include <string.h>

#include <algorithm>

#include <fcntl.h>

#include <sys/stat.h>

using namespace std;

void throw_error(int func, int error_number, string error_line) {
    if (func == error_number) {
        cerr << error_line << "\n";
        exit(EXIT_FAILURE);
    }
}

void check_semaphore(sem_t * semaphore, sem_t * error, string message) {
    if (semaphore == error) {
        cerr << message << endl;
    }
}

void give_to_mmap(string input, string mmap_name, string error_message, sem_t * semaphore, int * state, bool close_file) {
    int size = input.size();
    int file = shm_open(mmap_name.c_str(), O_RDWR | O_CREAT, 0777);
    throw_error(file, -1, error_message);
    ftruncate(file, size);
    char * mapped = (char * ) mmap(NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        file,
        0);
    memset(mapped, '\0', size);
    sprintf(mapped, "%s", input.c_str());
    int getvalue_error = sem_getvalue(semaphore, state);
    throw_error(getvalue_error, -1, "general sem_getvalue");
    if (close_file) {
        munmap(mapped, size);
        close(file);
    }
}

string get_from_mmap(string mmap_name, string error_message_file, bool close_file) {
    int file = shm_open(mmap_name.c_str(), O_RDWR | O_CREAT, 0777);
    throw_error(file, -1, error_message_file);
    struct stat stat_buffer;

    if (fstat(file, & stat_buffer) == -1) {
        cout << "-1\n";
        return "Fail";
    }

    int size = stat_buffer.st_size;
    void * mapped = mmap(NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        file,
        0);

    if (mapped == MAP_FAILED) {
        cout << "MMAP FAIL" << endl;
        return "Fail";
    }
    std::string str(static_cast < const char * > (mapped), stat_buffer.st_size);

    if (close_file) {
        close(file);

        if (munmap(mapped, size) == -1) {
            cout << "MUNMMAP FAIL" << endl;
            return "fail";
        };
    }

    return str;
}

void set_semaphore(sem_t * semaphore, int * state, int value) {
    while (++( * state) < value + 1) {
        sem_post(semaphore);
    }
    while (--( * state) > value) {
        sem_wait(semaphore);
    }
}

vector < int > parse_string(string str) {
    string str1;
    for(size_t i=2; i<str.size();++i){
        str1+=str[i];
    }
    std::istringstream iss(str1);
    std::vector<int> numbers;
    
    int number;
    while (iss >> number) {
        numbers.push_back(number);
    }


    return numbers;
}

// Расставляем корабль по заданным координатам
void arrangement_ships(vector < vector < string >> & two_matrix, vector < int > coordinates, int player) {
    coordinates[0]--;
    coordinates[1]--;
    coordinates[2]--;
    coordinates[3]--;
    if (coordinates[0] == coordinates[2]) {
        while (coordinates[1] <= coordinates[3]) {
            two_matrix[player][coordinates[0]][coordinates[1]] = '1';
            ++coordinates[1];
            if(coordinates[1]>9){
                break;
            }
        }
    } else {
        while (coordinates[0] <= coordinates[2]) {
            two_matrix[player][coordinates[0]][coordinates[3]] = '1';
            ++coordinates[0];
            if(coordinates[0]>9){
                break;
            }
        }
    }

}

void get_ship_location(vector < string > two_players, vector < vector < string >> & two_matrix, map<string ,int> statistic) {
    vector < string > sem_name(2);
    sem_name[0] = two_players[0] + ".sema";
    sem_name[1] = two_players[1] + ".sema";

    vector < sem_t * > two_semaphores(2);
    two_semaphores[0] = sem_open(sem_name[0].c_str(), 1);
    two_semaphores[1] = sem_open(sem_name[1].c_str(), 1);
    check_semaphore(two_semaphores[0], SEM_FAILED, "First semaphore failed");
    check_semaphore(two_semaphores[1], SEM_FAILED, "Second semaphore failed");

    vector < int > two_states(2);
    two_states[0] = 1;
    two_states[1] = 1;

    vector < string > mmap_client_server(2);
    mmap_client_server[0] = two_players[0] + "_server";
    mmap_client_server[1] = two_players[1] + "_server";

    vector < string > mmap_server_client(2);
    mmap_server_client[0] = "server_" + two_players[0];
    mmap_server_client[1] = "server_" + two_players[1];

    vector < int > ships_count(2);
    ships_count[0] = 0;
    ships_count[1] = 0;

    bool flag = 1;
    int a;
    while (flag) {
        for (int player_index = 0; player_index < 2; player_index++) {
            sem_getvalue(two_semaphores[player_index], & two_states[player_index]);

            if (ships_count[0] == 10 && ships_count[1] == 10) {
                flag = 0;
                break;
            }
            if (two_states[player_index] == 0) {
                string info = get_from_mmap(mmap_client_server[player_index], "Error in get_ships_coordinates", 1);
                if(info=="-1"){
                    int num = statistic[two_players[player_index]];
                    give_to_mmap(to_string(num), mmap_server_client[player_index], "Error in ships server client", two_semaphores[player_index], & two_states[player_index], 1);
                }else{

                    vector < int > numbers = parse_string(info);
                    cout << two_players[player_index] << ": " << info << endl;
                    arrangement_ships(two_matrix, numbers, player_index);
                    ++ships_count[player_index];
                    give_to_mmap("OK!", mmap_server_client[player_index], "Error in ships server client", two_semaphores[player_index], & two_states[player_index], 1);

                }
                set_semaphore(two_semaphores[player_index], & (two_states[player_index]), 2);
                usleep(25000);
            } else {
                usleep(25000);
            }
        }
    }

    ships_count[0] = 0;
    ships_count[1] = 0;
    flag = 1;
    while (flag) {
        for (int player_index = 0; player_index < 2; ++player_index) {
            sem_getvalue(two_semaphores[player_index], & two_states[player_index]);

            if (ships_count[0] == 10 && ships_count[1] == 10) {
                flag = 0;
                break;
            }

            if (two_states[player_index] == 1) {
                give_to_mmap(two_matrix[player_index][ships_count[player_index]].c_str(), mmap_server_client[player_index], "Error in ships server client", two_semaphores[player_index], & two_states[player_index], 1);
                ++ships_count[player_index];
                set_semaphore(two_semaphores[player_index], & two_states[player_index], 0);
                usleep(25000);
            }
        }
    }
}

string get_login(string a){
    string result;
    for(size_t i=0;i<a.size();++i){
        if(a[i]==' '){
            break;
        }
        result+=a[i];
    }
    return result;
}

string give_info(vector<string>& matrix, int x, int y){
    --x;
    --y;
    string answer;
    if(matrix[x][y]=='0'){
        matrix[x][y] = '3';
        answer = "Мимо";
    }
    if(matrix[x][y]=='1'){
        matrix[x][y] = '2';
        answer = "Ранил";
    }
    else{
        answer="Мимо";
    }
    return answer;
}


void get_coor(string a, int* x, int* y){
    string str;
    size_t i=0;
    for(;i<a.size();++i){
        if(a[i]==' '){
            break;
        }
    }
    ++i;
    for(;i<a.size();++i){
        str+=a[i];
    }
    std::istringstream iss(str);
    std::vector<int> numbers; 
    
    int number;
    while (iss >> number) {
        numbers.push_back(number); 
    }
    *x=numbers[0];
    *y=numbers[1];

}

void start_game(vector<vector<string>>& two_matrix,vector < string > two_players, sem_t * start_semaphore, string sem_name, map<string, int>& statistic) {
    int now_move = 0;
    int state = 0;
    vector < string > mmap_client_server(2);
    mmap_client_server[0] = two_players[0] + "_server_start";
    mmap_client_server[1] = two_players[1] + "_server_start";

    vector < string > mmap_server_client(2);
    mmap_server_client[0] = "server_" + two_players[0] + "_start";
    mmap_server_client[1] = "server_" + two_players[1] + "_start";
    sem_getvalue(start_semaphore, & state);
    bool flag = 1;
    vector<int> count(2, 0);
    string win;
    while (flag) {
        sem_getvalue(start_semaphore, & state);

        if (state == 0) {
            string info = two_players[now_move];

            give_to_mmap(info, mmap_server_client[0], "Error in start give to mmap", start_semaphore, & state, 1);
            give_to_mmap(info, mmap_server_client[1], "Error in start give to mmap", start_semaphore, & state, 1);

            set_semaphore(start_semaphore, & state, 1);
            usleep(25000);
        } else if (state == 2) {
            
            string info;
            string info1;

            if (now_move == 0) {
                info = get_from_mmap(mmap_client_server[0], "Error in client server start game", 1);
                cout<<info<<"\n";
            }

            if (now_move == 1) {
                info1 = get_from_mmap(mmap_client_server[1], "Error in client server start game", 1);
                cout<<info1<<"\n";
            }
            string login;
            int x, y;

            if(now_move==0){
                login = two_players[0];
                get_coor(info, &x, &y);
                string answer = give_info(two_matrix[1], x, y);
                if(answer=="Ранил"){
                    ++count[1];
                }

                login+=" " +answer+" "+to_string(x)+" "+to_string(y);
            }

            if(now_move==1){
                login = two_players[1];
                get_coor(info1, &x, &y);
                string answer = give_info(two_matrix[0], x, y);
                if(answer=="Ранил"){
                    ++count[0];
                }

                login+= " " +answer+" "+to_string(x)+" "+to_string(y);
            }
            if (count[1] == 20) {
                string win = two_players[0];
                ++statistic[win];
                cout<<"Winner is "<<win<<"\n";
                usleep(25000);
                give_to_mmap(win, mmap_server_client[0], "Error in start give to mmap", start_semaphore, & state, 1);
                give_to_mmap(win, mmap_server_client[1], "Error in start give to mmap", start_semaphore, & state, 1);
                set_semaphore(start_semaphore, &state, 6);
                usleep(25000);
                flag = 0;
            }
            if (count[0] == 20) {
                cout<<"Winner is "<<win<<"\n";
                ++statistic[win];


                give_to_mmap(win, mmap_server_client[0], "Error in start give to mmap", start_semaphore, & state, 1);
                give_to_mmap(win, mmap_server_client[1], "Error in start give to mmap", start_semaphore, & state, 1);

                set_semaphore(start_semaphore, &state, 6);
                usleep(25000);
                flag = 0;
            }
            
            if(flag==1){
                give_to_mmap(login, mmap_server_client[0], "Error in ships server client", start_semaphore, & state, 1);
                give_to_mmap(login, mmap_server_client[1], "Error in ships server client", start_semaphore, & state, 1);
                now_move = now_move ^ 1;


                set_semaphore(start_semaphore, & state, 3);
                usleep(25000);
            }
        } else {
            usleep(50000);
        }
    }
    usleep(25000);
    // set_semaphore(start_semaphore, &state, 4);
    // usleep(250000);

}

int main() {
    // Создание общего семафора
    string input;
    vector < string > logins;
    map<string, int> statistic;
    int logins_index = 0;
    cout << "Введите логины:\n";
    while (1) {
        cin >> input;

        if (input == "end") {
            break;
        }
        statistic[input] = 0;
        logins.push_back(input);

        ++logins_index;
    }

    printf("\nЛогины сохранены\n\n");


    // Получение всех логинов

    // Это для регистрации игры между двумя игроками
    while(1){
        string general_sem_name = "general.sem";
        sem_unlink(general_sem_name.c_str());
        sem_t * general_semaphore = sem_open(general_sem_name.c_str(), O_CREAT, 0777, 1);
        int general_state = 1;

        string start_game_sem = "start_game";
        sem_unlink(start_game_sem.c_str());
        sem_t * start_game_semaphore = sem_open(start_game_sem.c_str(), O_CREAT, 0777, 0);
        check_semaphore(start_game_semaphore, SEM_FAILED, "Error in start game semaphore");

        string client_server_general = "client_server_general";
        string server_client_general = "server_client_general";

        int login_count_for_game = 0;
        vector < string > two_players_name(2);
        while (1) {
            if (login_count_for_game == 2) {
                break;
            }

            sem_getvalue(general_semaphore, & general_state);

            if (general_state == 0) {
                string login = get_from_mmap(client_server_general, "Error in open file", 1);
                cout << login << " is logined" << "\n";
                two_players_name[login_count_for_game] = login;
                ++login_count_for_game;
                if (find(begin(logins), end(logins), login) != logins.end() && two_players_name[0] != two_players_name[1]) {
                    give_to_mmap("Регистрация прошла успешно", server_client_general, "Bad in server_client_general", general_semaphore, & general_state, 1);
                }

                set_semaphore(general_semaphore, & general_state, 2);
                usleep(25000);
            } else {
                usleep(500000);
            }
        }
        sem_close(general_semaphore);
        sem_destroy(general_semaphore);

        string str0(10, '0');
        vector < vector < string >> two_matrix(2, vector < string > (10, str0));

        cout << "Сейчас играют " << two_players_name[0] << " против " << two_players_name[1] << endl;

        sem_unlink(general_sem_name.c_str());
        usleep(1000000);
        get_ship_location(two_players_name, two_matrix, statistic);

        start_game(two_matrix, two_players_name, start_game_semaphore, start_game_sem, statistic);
        usleep(5000000);
    }

    return 0;
}