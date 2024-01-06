#include "1task.h"
#include "vector.h"
#include <vector>
int main(int argc, char **argv){
    cout<<"map:\n";
    std::map<int, int, std::less<int>,Allocator<std::pair<const int,int>, 50>> my_map;
    my_map[0] = 1;
    for(int i=1; i<10; ++i){
        my_map[i] = i*my_map[i-1];
        cout<<"i: "<< i << ", value: "<< my_map[i]<<endl;
    }

    cout<<"\nvector:\n";
    MyVector<int, Allocator<int, 50>> my_vec = {1,2,3,4,5,6,7,8,9};
    for(int iter: my_vec){
        cout<<iter<<endl;
    }
}
