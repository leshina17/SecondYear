#include "Set.h"


Set::Set(size_t mp) : _bitField(mp) {
    _maxPower=mp;
}
Set::Set(const Set &s) : _bitField(s._maxPower){
    _bitField=s._bitField;
    _maxPower=s._maxPower;
} 
Set::Set(const BitField &bf) : _bitField(bf.GetLength()){
    _bitField=bf;
    _maxPower=bf.GetLength();
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
    return(_bitField.GetBit(Elem));
}


bool Set::operator== (const Set &s) const{
    return (_bitField==s._bitField);
}
bool Set::operator!= (const Set &s) const{
    if(_bitField==s._bitField)
    return false;
    else
    return true;
}
Set& Set::operator=(const Set &s){
    _maxPower=s.GetMaxPower();
    _bitField=s._bitField;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){
    return *this;
}
                                  
Set Set::operator- (const uint64_t Elem){
    return *this;
}
                                   
Set Set::operator+ (const Set &s){
    Set b=Set(s);
    if(_maxPower>s.GetMaxPower()){
        b=Set(*this);
        b._bitField=b._bitField|s._bitField;  
    }
    else 
        b._bitField=b._bitField|_bitField;
    return b;
}
Set Set::operator* (const Set &s){
    Set b=Set(s);
    if(_maxPower<s.GetMaxPower()){
        b=Set(*this);
        b._bitField=b._bitField&s._bitField;
    }
    else
        b._bitField=b._bitField&_bitField;
    return b;
}
Set Set::operator~ (){
    return (~this->_bitField);
}
std::vector<uint64_t> Set::GetPrimary(){//в тестах включено 1, тут нет, а остальное правильно
    std::vector<uint64_t> prim_num;
    BitField tmp=_bitField;
    uint64_t current_div=2;
    prim_num.push_back(1);
    while(current_div<_maxPower){
        if (IsMember(current_div)){
            for(uint64_t i=current_div+current_div; i<_maxPower;i+=current_div){
                _bitField.ClrBit(i);
            }
        }
        if (IsMember(current_div))
            prim_num.push_back(current_div);
        current_div++;
                
        }
        _bitField=tmp;
        return prim_num;
}