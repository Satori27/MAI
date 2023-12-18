#include <stdio.h>
#include <iostream>

#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <sys/mman.h>

#include <string.h>
#include <sstream>


#include <semaphore.h>

#include <fcntl.h>
#include <string>
#include <vector>
#include <map>

#include <sys/stat.h>

using namespace std;

int MAX_SIZE = 50;


void set_semaphore(sem_t * semaphore, int * state, int value) {
    while (++( * state) < value + 1) {
        sem_post(semaphore);
    }
    while (--( * state) > value) {
        sem_wait(semaphore);
    }
}

void throw_error(int function, int error_number, string error_line) {
    if (function == error_number) {
        exit(EXIT_FAILURE);
        cerr<<error_line<<"\n";
    }
}


string get_from_mmap(string mmap_name, string error_message_file, bool close_file) {
    int file = shm_open(mmap_name.c_str(), O_RDWR | O_CREAT, 0777);
    throw_error(file, -1, error_message_file);
    struct stat stat_buffer;

    if(fstat(file, & stat_buffer)==-1){
        return "Fail";
    }

    int size = stat_buffer.st_size;
    void* mapped = mmap(NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        file,
        0);

    if(mapped==MAP_FAILED){
        cout<<"MMAP FAIL"<<endl;
        return "Fail";
    }
    std::string str(static_cast<const char*>(mapped), stat_buffer.st_size);
    
    if (close_file) {
        close(file);
        
        if(munmap(mapped, size)==-1){
            cout<<"MUNMMAP FAIL"<<endl;
            return "fail";
        };
    }

    return str;
}

void check_semaphore(sem_t* sem, sem_t* error, string message){
    if(sem==error){
        cerr<< message<<endl;
    }
}

string get_login(string line){
    string result;
    for(size_t i=0;i<line.size();++i){
        if(line[i]==' '){
            break;
        }
        result+=line[i];
    }
    return result;
}

string get_coor(string line, int* x, int* y){
    string str;
    string str_one;
    size_t line_index=0;
    for(;line_index<line.size();++line_index){
        if(line[line_index]==' '){
            break;
        }
    }
    ++line_index;
    for(;line_index<line.size();++line_index){
        if(line[line_index]==' '){
            break;
        }
        str+=line[line_index];
    }
    ++line_index;
    for(;line_index<line.size();++line_index){
        str_one+=line[line_index];
    }


    std::istringstream iss(str_one); 
    std::vector<int> numbers;
    
    int number;
    while (iss >> number) {
        numbers.push_back(number); 
    }
    *x=numbers[0];
    *y=numbers[1];

    return str;
}

void print_matrix(vector<string> matrix){
    for(int row_index=0;row_index<10;++row_index){
        for(int column_index=0;column_index<10;++column_index){

            if(matrix[row_index][column_index]=='3'){
                cout<<"\u2715"<<" ";
            }
            if(matrix[row_index][column_index]=='2'){
                cout<<"\u25A1\u0338"<<" ";
            }
            if(matrix[row_index][column_index]=='1'){
                cout<<"\u25A1"<<" ";
            }
            if(matrix[row_index][column_index]=='0'){
                cout<<"\u00B7"<<" ";
            }
        }
        cout<<"\n";
    }
}
void give_info(vector<string>& matrix, int x, int y, string info){
    --x;
    --y;
    if(info=="Мимо"){
        matrix[x][y] = '3';
    }

    if(info=="Ранил"){
        matrix[x][y] = '2';
    }
}


void give_to_mmap(string login, string mmap_name, string error_message, sem_t* semaphore, int* state, bool close_file){
            int size = login.size();
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
                sprintf(mapped, "%s", login.c_str());
                int getvalue_error = sem_getvalue(semaphore, state);
                throw_error(getvalue_error, -1, "general sem_getvalue");
                if(close_file){
                    munmap(mapped, size);
                    close(file);
                }
}

// Отправляю координаты и получаю матрицу
void give_ships_coordinates(string login, vector<string>& my_ships){
    string sem_name = login+".sema";
    sem_unlink(sem_name.c_str());
    sem_t* semaphore = sem_open(sem_name.c_str(), O_CREAT | O_EXCL, 0777, 1);
    check_semaphore(semaphore, SEM_FAILED, "Error in child semaphore");
    int state = 1;
    sem_getvalue(semaphore, &state);

    set_semaphore(semaphore, &state, 1);
    string client_server = login+"_server";
    string server_client = "server_"+login;
    cout<<"Введите размер корабля и две точки "<<"\n";
    int ships_count = 0;
    while(1){
        sem_getvalue(semaphore, &state);
        usleep(25000);

        if(state==1){
            int ship_size, coorA_x, coorA_y, coorB_x,coorB_y;
            cin>>ship_size;

            if(ship_size==-1){
                give_to_mmap(to_string(ship_size), client_server, "Error in client ships", semaphore, &state, 1);
                set_semaphore(semaphore, &state, 0);

                usleep(25000);
            }else{
                cin>>coorA_x>> coorA_y>> coorB_x>>coorB_y;
                string final_string = to_string(ship_size) + " " + 
                                    to_string(coorA_x) + " " +
                                    to_string(coorA_y) + " " +
                                    to_string(coorB_x) + " " +
                                    to_string(coorB_y) + " ";
                give_to_mmap(final_string, client_server, "Error in client ships", semaphore, &state, 1);
                set_semaphore(semaphore, &state, 0);

                usleep(25000);
            }
        }
        else if(state==2){
            string info_from_server = get_from_mmap(server_client, "Error in server_client_ship", 1);
            if(info_from_server!="OK!"){
                cout<<"Ваша статистика: "<< info_from_server<<"\n";
                set_semaphore(semaphore, &state, 1);
                usleep(25000);
            }else{
                cout<<info_from_server<<"\n";
                
                ++ships_count;
                set_semaphore(semaphore, &state, 1);
                usleep(25000);
                if(ships_count==10){
                    break;
                }
            }
        }
    }
    ships_count=0;
    bool flag = 1;
    while(flag){
        usleep(25000);
        sem_getvalue(semaphore, &state);
        if(state==0){
            string ships_coordinates = get_from_mmap(server_client, "Error in server_client_ship", 1);
            my_ships.push_back(ships_coordinates);
            ++ships_count;
            set_semaphore(semaphore, &state, 1);
            usleep(25000);
            if(ships_count==10){
                flag=0;
            }
        }
    }
    print_matrix(my_ships);
}


void start_game(string login, sem_t* semaphore, string sem_name, vector<string>& my_ships, vector<string>& enemy_ships){
    int state=0;
    sem_getvalue(semaphore, &state);


    string client_server = login+"_server_start";
    string server_client = "server_"+login+"_start";
    cout<<"Игра началась\n";
    
    int count = 0;
    bool flag=1;
    while(flag){
        sem_getvalue(semaphore, &state);
        usleep(25000);

        if(state==1){
            string give_to_mmap_str;
            string info_from_server = get_from_mmap(server_client, "Error in server_client_start", 1);

            if(login!=info_from_server){
                usleep(10000);
                continue;
            }else{
                string coordinates;
                cout<<"Вы ходите\n";
                int x, y;
                cin>>x>>y;
                coordinates = " "+to_string(x)+" "+to_string(y);

                string give_to_mmap_str;
                give_to_mmap_str = login+coordinates;
                give_to_mmap(give_to_mmap_str, client_server, "Error in client start", semaphore, &state, 0);
                usleep(200000);
                set_semaphore(semaphore, &state, 2);
                usleep(25000);
            }
        }

        else if(state==3){
            string info_from_server = get_from_mmap(server_client, "Error in server_client_start", 1);
            int x,y;
            string server_login = get_login(info_from_server);
            string info = get_coor(info_from_server, &x, &y);
            if(info=="Ранил"){
                ++count;
            }
            if(login!=server_login){
                give_info(my_ships, x, y,info);
            }else{
                give_info(enemy_ships, x, y, info);
            }
            cout<<"Ваше поле\n";
            print_matrix(my_ships);
            cout<<"\n";
            cout<<"Поле противника\n";
            print_matrix(enemy_ships);
            cout<<"\n";
            cout<<info_from_server<<endl;
            cout<<"\n";
            usleep(200000);
            set_semaphore(semaphore, &state, 0);
            usleep(25000);
        }

        else if(state==6){
            string win = get_from_mmap(server_client, "Error in server_client_start", 1);
            // usleep(250000);
            if(login!=win){
                cout<<"\nВы проиграли\n";
            }else{
                cout<<"\nВы выиграли\n";
            }
            flag=0;
        }
    }
}

int main(){
    // Создание общего семафора
    string general_sem_name = "general.sem";
    sem_t* general_semaphore = sem_open(general_sem_name.c_str(), O_RDWR | O_CREAT, 0777);
    int general_state;
    string client_server_general = "client_server_general";
    string server_client_general = "server_client_general";
    string login;

    // отправляем логин на сервер
    while(1){
        sem_getvalue(general_semaphore, &general_state);
        usleep(20000);
        if(general_state==1){
            printf("Введите логин: ");
            cin>>login;
            give_to_mmap(login, client_server_general, "general shm_open from child", general_semaphore, &general_state, 1);
                set_semaphore(general_semaphore, &general_state, 0);
                usleep(25000);
        }
        else if(general_state==2){
            string is_verificate = get_from_mmap(server_client_general, "Error in server_client_general", 1);
            cout<<is_verificate<<"\n";
            set_semaphore(general_semaphore, &general_state, 1);
            break;
        }
    }
    string sem_name = "start_game";
    sem_t* start_semaphore = sem_open(sem_name.c_str(), 0);
    check_semaphore(start_semaphore, SEM_FAILED, "Error in child sem_start");
    vector<string> my_ships;
    string str0(10, '0');
    vector<string> enemy_ships(10, str0);

    give_ships_coordinates(login, my_ships);
    map<int, int> my_ships_count;
    my_ships_count[1] = 4;
    my_ships_count[2] = 3;
    my_ships_count[3] = 2;
    my_ships_count[4] = 1;
    

    start_game(login, start_semaphore, sem_name, my_ships, enemy_ships);
    

}
