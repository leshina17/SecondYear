#include <cstring>
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
        _max = INT8_MIN;
        _min = INT8_MAX;
        _count = 0;
    }

    void AppendElem(T elem) {
        if (_count==0){
            _max=elem;
            _min-elem;
        }
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
        std::sort(_array, _array + _count);
        int left = 0, right = _count - 1;
        while (left <= right) {
            int ind = left + (right - left) / 2;
            if (_array[ind] == elem) {
                return true;
            } else if (_array[ind] < elem) {
                left = ind + 1;
            } else {
                right = ind - 1;
            }
        }
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