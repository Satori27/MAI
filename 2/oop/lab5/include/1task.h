#include <iostream>
#include <memory>
#include <list>
#include <map>
#include <utility>

using namespace std;
// #define DEBUG

template < class T, size_t N >
  class Allocator {
    private: char * _used_blocks;
    list < void * > _free_blocks;
    uint64_t _free_count;

    public: static constexpr size_t max_count = N;
    using value_type = T;
    using pointer = T * ;
    using const_pointer = const T * ;
    using size_type = std::size_t;

    Allocator() {
      _used_blocks = (char * ) malloc(sizeof(T) * max_count);
      _free_blocks = list < void * > ();
      for (uint64_t i = 0; i < max_count; i++) {
        _free_blocks.push_front(_used_blocks + i * sizeof(T));
      }
      _free_count = max_count;
      #ifdef DEBUG
        std::cout << "allocator: memory init" << std::endl;
      #endif
    }

    ~Allocator() {
      #ifdef DEBUG
      if (_free_count < max_count)
        std::cout << "allocator: Memory leak?" << std::endl;
      else
        std::cout << "allocator: Memory freed" << std::endl;
      #endif

      ((list < void * > ) _free_blocks).clear();

      if (_used_blocks != NULL && _used_blocks[0] == '\0') {
        delete _used_blocks;
      }

      _used_blocks = nullptr;
    }

    template < class U >
    struct rebind {
      using other = Allocator < U, N > ;
    };

    T * allocate(size_t n) {
      T * result = nullptr;
      if (_free_count > 0) {
        auto it2 = std::next(_free_blocks.begin(), --_free_count);
        result = (T * )( * it2);
        #ifdef DEBUG
            std::cout << "allocator: Allocate " << (max_count - _free_count) << " of " << max_count << " Address:" << result << std::endl;
        #endif
      } else {
        std::cout << "allocator: No memory exception :-)" << std::endl;
      }
      return result;
    }

    void deallocate(T * pointer, size_t) {
      #ifdef DEBUG
        std::cout << "allocator: Deallocate block " << pointer << std::endl;
      #endif 
      auto it2 = std::next(_free_blocks.begin(), _free_count);
      ++_free_count;
      * it2 = pointer;
    }
    template < typename U,
    typename...Args >
    void construct(U * p, Args && ...args) {
      new(p) U(std::forward < Args > (args)...);
    }

    void destroy(pointer p) {
      p -> ~T();
    }
  };

template < class T, class U, size_t N >
  constexpr bool operator == (const Allocator < T, N > & lhs,
    const Allocator < U, N > & rhs) {
    return true;
  }

template < typename T, typename U, size_t BLOCK_COUNT >
  constexpr bool operator != (const Allocator < T, BLOCK_COUNT > & lhs,
    const Allocator < U, BLOCK_COUNT > & rhs) {
    return false;
  }
