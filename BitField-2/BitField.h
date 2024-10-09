#include <iostream>
#include <cstdint>

class BitField {
private:
    size_t _sizeBit;
    uint16_t* _mem;
    size_t _memSize;
    size_t Get_mem_index (size_t n) const{
        size_t index=n/(8*sizeof(uint16_t));
        if (n>=_sizeBit)
            throw "bit out of range!!";
        return index;
    }

    size_t GetMemIndex(size_t n) const;
    uint16_t GetMask(size_t n) const { //const говорит что в этом методе не изменяются поля 
            uint16_t m=1<<(n%(sizeof(uint16_t)*8)); // return 1 << (n%16);
            return m;
        }
public:
    BitField(size_t len);
    BitField(const BitField& tmp);
    BitField& operator=(const BitField& tmp);
    
    size_t GetLength() const; // Получить количество бит
    void SetBit(size_t n){
        if (n >= _sizeBit) {
            throw "bit out of range!!";
        }
        _mem[GetMemIndex(n)] |= GetMask(n);
    }
    void ClrBit(size_t n){
    if (n >= _sizeBit) {
            throw "bit out of range!!";
        }
        _mem[GetMemIndex(n)] &= ~GetMask(n);
    } // Настя
    uint8_t GetBit(size_t n) const { // проверить выход n and _size_n=bit, получить маску 000010 внизу, получить индекс в памяти в каком элементе, побитовая кон& &!=0
            if(n>=_sizeBit)
                throw "bit out of range!!";
            return ((GetMask(n)&_mem[Get_mem_index(n)])!=0);
        } // вывести бит по индексу // Саша


    BitField operator|(const BitField& tmp)
    {
        if (_sizeBit != tmp._sizeBit) {
            throw "bit out of range!!";
        }
        BitField result(_sizeBit);
        for (size_t i = 0; i < _memSize; ++i) {
            result._mem[i] = _mem[i] | tmp._mem[i];
        }
        return result;
    } // Карина
    BitField operator&(const BitField& tmp)
    {
        if (_sizeBit != tmp._sizeBit) {
            throw "bit out of range!!";
        }
        BitField result(_sizeBit);
        for (size_t i = 0; i < _memSize; ++i) {
            result._mem[i] = _mem[i] & tmp._mem[i];
        }
        return result;
    } // Алина
    BitField operator^(const BitField& tmp)
     {
        if (_sizeBit != tmp._sizeBit) {
            throw "bit out of range!!";
        }
        BitField result(_sizeBit);
        for (size_t i = 0; i < _memSize; ++i) {
            result._mem[i] = _mem[i] ^ tmp._mem[i];
        }
        return result;
    } // Арина
    bool BitField::operator==(const BitField& tmp) { //Даша
        if (_sizeBit != tmp._sizeBit) {
            return false;
        }
        for (size_t i = 0; i < _memSize; ++i) {
            if (_mem[i] != tmp._mem[i]) {
                return false;
            }
        }
        return true;
    }
    BitField& operator~(){ //Все (побитовое отрицание)
            for(size_t i =0;i<_memSize;i++)
            _mem[i]=~_mem[i];
        return *this;
        }

    ~BitField(){
        delete [] _mem;
    } // Все
};