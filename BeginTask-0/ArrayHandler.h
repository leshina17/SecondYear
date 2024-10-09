#include <cstring>
#include <limits>
#include <algorithm>
template<typename T>
class ArrayHandler {
private:
    size_t _size;
    T* _array;
    size_t _count;
    T _min;
    T _max;
public:
    ArrayHandler(size_t size = 10) {
        _size = size;
        _array = new T[_size];
        _max = std::numeric_limits<T>::min();
        _min = std::numeric_limits<T>::max();
        _count = 0;
    }

    void AppendElem(T elem) {
        if (_count==0){
            _max=elem;
            _min-elem;
        }
        if (_count == _size) {
            _size = _size*3;
            T* new_arr = new T[_size];
            std::memcpy(new_arr, _array, _count*sizeof(T));
            delete [] _array;
            _array = new_arr;
        }
        _array[_count] = elem;
        if(elem < _min)
            _min = elem;
        if(elem > _max)
            _max = elem;
        _count++;

    }

    bool IsContains(T elem) {
        std::sort(_array, _array + _count);
        return std::binary_search(_array[0], _array[_count], elem);
    }

    T GetMax() {
        return _max;
    }

    T GetMin() {
        return _min;
    }

    ~ArrayHandler() {
        delete [] _array;
    }

}; //посмотреть как ставить гугл тесты google test instal on windows (ссылка в группе)
// git add .
// git commit -m "do"
// git push 
// m=name 