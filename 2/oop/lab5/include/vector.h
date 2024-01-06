#include <memory>
#include <iostream>
using namespace std;

template<typename T, typename Alloc = std::allocator<T>>
class MyVector {
public:
    using allocator_type = Alloc;
    using value_type = T;
    using pointer = typename std::allocator_traits<Alloc>::pointer;
    using pointer_type      = T*;
    using size_type = std::size_t;

    MyVector(const MyVector<T, allocator_type>& copy_vec){
        size_ = 0;
        capacity_= 0;
        data_= nullptr;
        reserve(copy_vec.capacity_+1);
        size_t i=0;
        for(auto c:copy_vec){
            allocator_.construct(data_ + i, c);
            ++i;
        }
        size_ = copy_vec.size_;

    }
    MyVector<int>::iterator a;
    using iterator = T;
    MyVector()
        :data_(nullptr), size_(0), capacity_(0) {
    }

    MyVector(const initializer_list<T> &a){
        size_ =0;
        size_t new_size=a.size();
        capacity_=1;
        while(new_size/=2){
            capacity_*=2;
        }
        reserve(capacity_ * 2 + 1);

        size_t i=0;
        for(const T &c:a){
            allocator_.construct(data_ + i, c);
            ++i;
        }
        size_ = a.size();

    }

    ~MyVector() {
        if (data_) {
            allocator_.deallocate(data_, capacity_);
        }
    }

    T& operator[](size_type index) {
        return data_[index];
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ * 2 + 1);
        }
        allocator_.construct(data_ + size_, value);
        ++size_;
    }

    void reserve(size_type new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        pointer new_data = allocator_.allocate(new_capacity);


        for (size_type i = 0; i < size_; ++i) {
            allocator_.construct(new_data + i, std::move_if_noexcept(data_[i]));
            allocator_.destroy(data_ + i);
        }

        if (data_) {
            allocator_.deallocate(data_, capacity_);
        }

        data_ = new_data;
        capacity_ = new_capacity;
    }
    size_type size(){
        return size_;
    }
    public:
    class Iterator{
        public: 
		    using iterator_category = std::forward_iterator_tag;
			using value_type        = T;
			using pointer_type      = T*;
			using reference_type    = T&;
    
    Iterator() = default;
    Iterator(pointer_type ptr): m_ptr(ptr){}

    reference_type operator*() const{
        return *m_ptr;
    }

    pointer_type operator->(){
        return m_ptr;
    }

    Iterator& operator++(){
        m_ptr++;
        return *this;
    }

    Iterator operator++(int){
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator== (const Iterator& a, const Iterator& b) {
        return a.m_ptr == b.m_ptr;
    }

    friend bool operator!= (const Iterator& a, const Iterator& b) {
		return !(a == b);
    } 
    private:
        pointer_type m_ptr;
    };

    class ConstIter{
    public : 
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using pointer_type           = const T*;
        using reference_type         = const T&;

        ConstIter() = default;
        ConstIter(pointer_type ptr): m_ptr(ptr){}

        value_type operator*() const{
            return *m_ptr;
        }

        ConstIter& operator++(){
            m_ptr++;
            return *this;
        }

        ConstIter operator++(int){
            ConstIter tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator== (const ConstIter& a, const ConstIter& b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator!= (const ConstIter& a, const ConstIter& b) {
            return !(a == b);
        }
    private:
        pointer_type m_ptr;
    };

	Iterator begin() { return Iterator(&data_[0]); }
    Iterator end()   { return Iterator(&data_[size_]); }

    ConstIter begin() const { return ConstIter(&data_[0]); }
    ConstIter end() const   { return ConstIter(&data_[size_]); }

    ConstIter cbegin() const { return ConstIter(&data_[0]); }
    ConstIter cend() const   { return ConstIter(&data_[size_]); }

private:
    allocator_type allocator_;
    pointer data_;
    size_type size_;
    size_type capacity_;
};
