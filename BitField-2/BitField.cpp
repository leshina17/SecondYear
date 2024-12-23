#include "BitField.h"

size_t BitField::GetMemIndex(size_t n) const{
    if (n>=_sizeBit)
        throw "bit out of range!!";
    return n/(8*sizeof(uint16_t));
}
uint16_t BitField::GetMask(size_t n) const {
    return 1<< (n%16);
}

BitField::BitField(size_t len) {
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
}

BitField& BitField::operator=(const BitField& tmp) {
    if (_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}
    
size_t BitField::GetLength() const {
    return _sizeBit;
}

void BitField::SetBit(size_t n) {
    if (n >= _sizeBit)
        throw "bit out of range!!";
    _mem[GetMemIndex(n)] |= GetMask(n);
}

void BitField::ClrBit(size_t n) {
    if (n >= _sizeBit)
        throw "bit out of range!!";
    _mem[GetMemIndex(n)] &= (~GetMask(n));
}

uint8_t BitField::GetBit(size_t n) const {
    if(n>=_sizeBit)
        throw "bit out of range!!";
    return ((GetMask(n)&_mem[GetMemIndex(n)])!=0);
}

BitField BitField::operator|(const BitField& tmp) {
    BitField res=BitField(_sizeBit);
    for (size_t i=0; i<_memSize; i++){
        res._mem[i]=_mem[i]|tmp._mem[i];
    }
    return res;
}

BitField BitField::operator&(const BitField& tmp) {
    BitField res=BitField(*this);
    for (size_t i=0; i<_memSize; i++){
        res._mem[i]&=tmp._mem[i];
    }
    return res;
}

BitField BitField::operator^(const BitField& tmp) {
    BitField res=BitField(*this);
    for (size_t i=0; i<_memSize; i++){
        res._mem[i]^=tmp._mem[i];
    }
    return res;
}

bool BitField::operator==(const BitField& tmp) const{
    for(size_t i=0; i<_memSize;i++){
        if(_mem[i]!=tmp._mem[i])
        return false;
    }
    return true;
}

BitField BitField::operator~(){
    BitField copy = BitField(*this);
    for (size_t i = 0; i < _sizeBit; i++){
        if (GetBit(i))
            copy.ClrBit(i);
        else 
            copy.SetBit(i);
    }
    return copy;
}