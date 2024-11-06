#include "Set.h"


Set::Set(size_t mp) : _bitField(10) {
    _maxPower=mp;
}
Set::Set(const Set &s) : _bitField(10){
    _maxPower = s._maxPower;
    _bitField = s._bitField;
} 
Set::Set(const BitField &bf) : _bitField(10){
    _bitField = bf;
    _maxPower = bf.GetLength();
}

size_t Set::GetMaxPower() const{
    return _maxPower;
}    
void Set::InsElem(const uint64_t Elem){
    _bitField.SetBit(Elem);
}
void Set::DelElem(const uint64_t Elem){
    _bitField.ClrBit(Elem);
}
bool Set::IsMember(const uint64_t Elem) const{
    return _bitField.GetBit(Elem);
}


bool Set::operator== (const Set &s) const{
    return ((_maxPower==s._maxPower)&&(_bitField==s._bitField));
}
bool Set::operator!= (const Set &s) const{
    if ((_maxPower==s._maxPower)&&(_bitField==s._bitField))
        return false;
    return true;
}
Set& Set::operator=(const Set &s){
    _maxPower = s._maxPower;
    _bitField = s._bitField;
    return *this; 
}
Set Set::operator+ (const uint64_t Elem){
    Set result(*this);
    result.InsElem(Elem);
    return result;
}
                                  
Set Set::operator- (const uint64_t Elem){
    Set result(*this);
    result.DelElem(Elem);
    return result;
}
                                   
Set Set::operator+ (const Set &s){
    Set result(std::max(_maxPower, s._maxPower)); //хранит результат объединения
    result._bitField=_bitField;
    for (size_t i = 0; i < s._maxPower; ++i) {
        if (s._bitField.GetBit(i)) {
            result._bitField.SetBit(i); 
        }
    }
    return result;
}
Set Set::operator* (const Set &s){
    Set result(std::min(_maxPower, s._maxPower));
    result._bitField = _bitField & s._bitField; 
    return result;
}
Set Set::operator~ (){
    for (size_t i=0; i<=_maxPower; i++)
        _maxPower=~_maxPower;
    return *this;
}
std::vector<uint64_t> Set::GetPrimary(){
    std::vector<uint64_t> simple;
    Set copy(*this);// копия, чтобы не изменять исходное
    for (size_t i = 2; i <= copy.GetMaxPower(); ++i) {
        if (copy.IsMember(i)) {
            simple.push_back(i);
            for (size_t j = i * i; j <= copy.GetMaxPower(); j += i) {
                copy.DelElem(j);
            }
        }
    }
    return simple;
}