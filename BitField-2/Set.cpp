#include "Set.h"
//ПЕРЕВОД В БИТФИЛДЫ И ОБРАТНО КАК-ТО АККУРАТНО

Set::Set(size_t mp) : _bitField(10) {
    _maxPower=mp;
}
Set::Set(const Set &s) : _bitField(s._maxPower){
    _maxPower = s._maxPower;
    _bitField = s._bitField;
} 
Set::Set(const BitField &bf) : _bitField(bf.GetLength()){
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
bool Set::IsMember(uint64_t Elem) const{
    // if (Elem >= _maxPower) 
    //     throw "wrong!";
    return _bitField.GetBit(Elem);
}

bool Set::operator== (const Set &s) const{
    return (_bitField==s._bitField);
}
bool Set::operator!= (const Set &s) const{
    if (_bitField==s._bitField)
        return false;
    return true;
}
Set& Set::operator=(const Set &s){
    _maxPower = s.GetMaxPower();
    _bitField = s._bitField;
    return *this; 
}
Set Set::operator+ (const uint64_t Elem){
    return *this;
}
                                  
Set Set::operator- (const uint64_t Elem){
    return *this;
}
                                   
Set Set::operator+ (const Set &s){
    Set res= Set(s);
    if(_maxPower>s.GetMaxPower()){
        res=Set(*this);
        res._bitField=res._bitField|s._bitField;  
    }
    else 
        res._bitField=res._bitField|_bitField;
    return res;
}
Set Set::operator* (const Set &s){
    Set res=Set(s);
    if(_maxPower<s.GetMaxPower()){
        res=Set(*this);
        res._bitField=res._bitField&s._bitField;
    }
    else
        res._bitField=res._bitField&_bitField;
    return res;
}
Set Set::operator~ (){
    return (~this->_bitField);
}
std::vector<uint64_t> Set::GetPrimary(){
    std::vector<uint64_t> simple;
    BitField tmp=_bitField;
    uint64_t now_div=2;
    simple.push_back(1);
    while(now_div<_maxPower){
        if (IsMember(now_div)){
            for(uint64_t i=now_div+now_div; i<_maxPower;i+=now_div){
                _bitField.ClrBit(i);
            }
        }
        if (IsMember(now_div))
            simple.push_back(now_div);
        now_div++;
                
        }
        _bitField=tmp;
        return simple;
}