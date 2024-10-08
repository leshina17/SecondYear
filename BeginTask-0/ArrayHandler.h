#include <cstring>
template<typename T>
class ArrayHandler {
private:
    size_t _size;
    T* _array;
    long long _count;
    T _min;
    T _max;
public:
    ArrayHandler(size_t size = 10) {
        _size = size;
        _array = new T[_size];
        _max = INT8_MIN;
        _min = INT8_MAX;
        _count = 0;
    }

    void AppendElem(T elem) {
        _max=elem;
        _min-elem;
        if (_count == _size) {
            _size = _size +10;
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
        // for (int i = 0; i < _size; ++i) {
        // if (_array[i] == elem) {
        //     return true;
        // }
    //}
        return false;
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