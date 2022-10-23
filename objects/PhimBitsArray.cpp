#include "./PhimBitsArray.h"

// #include <algorithm>
#include <iostream>

void objects::ByteOperation::getByteRepresentation(unsigned char _byte, char* _rtr) {

    for (int _ = 0; _ < 8; _++) 
    
        *(_rtr++) = (_byte << _) & 0x80 ? '1' : '0';

}

bool objects::ByteOperation::getBit(unsigned char _byte, int _index) {

    return _byte << _index & 0x80;

}

bool objects::ByteOperation::setBit(unsigned char* _byte, int _index, bool _value) {

    if (_index > 7 || _index < 0) return false;

    *_byte = (*_byte & ~(1U << 7 - _index)) | (_value << 7 -_index);

    return true;

}

unsigned char objects::ByteOperation::addBytes(unsigned char _byte1, unsigned char _byte2, bool& _over) {

    unsigned char _rtr = _byte1 + _byte2 + _over;

    _over = (_byte1 + _byte2 + _over > 255);

    return _rtr;

}

unsigned char objects::ByteOperation::subBytes(unsigned char _byte1, unsigned char _byte2, bool& _over) {

    unsigned char _rtr = _byte1 - _byte2 - _over;

    _over = (_byte2 + _over > _byte1);

    return _rtr;

}


objects::PhimBitsArray::~PhimBitsArray() { free(bytes); }

objects::PhimBitsArray::PhimBitsArray() : bytes(NULL), bytesLenght(0) {} 

void objects::PhimBitsArray::clean() { 

    free(bytes);
    bytes = NULL;

    bytesLenght = 0;

    addNewByte(0);

}

void objects::PhimBitsArray::copyBytes(unsigned char* _rtr) { for (int _ = 0; _ < bytesLenght; _++) *(_rtr++) = bytes[_]; } 
    //  or std::copy_n(bytes, bytesLenght, _rtr); }

// size_t objects::PhimBitsArray::getFullSize() { return sizeof(*bytes) * bytesLenght + sizeof(*this); }

unsigned char objects::PhimBitsArray::operator[](int _byteIndex) { 

    if (_byteIndex >= bytesLenght || _byteIndex < 0) return 0;

    return bytes[ _byteIndex ];

}

unsigned char objects::PhimBitsArray::getByteInverted(int _byteIndex) { 

    if (_byteIndex >= bytesLenght || _byteIndex < 0) return 0;

    return bytes[ bytesLenght - 1 - _byteIndex ];

}

bool objects::PhimBitsArray::getBitOfByte(int _byteIndex, int _bitIndex) { return objects::ByteOperation::getBit(operator[](_byteIndex), _bitIndex); } 

bool objects::PhimBitsArray::getBit(int _bitIndex) { 

    if (_bitIndex >= bytesLenght * 8) return false;
    
    return objects::ByteOperation::getBit(bytes[_bitIndex / 8], _bitIndex - _bitIndex / 8 * 8); 
    
}

bool objects::PhimBitsArray::getBitOfByteInverted(int _byteIndex, int _bitIndex) { 

    return objects::ByteOperation::getBit(getByteInverted(_byteIndex), 7 - _bitIndex); 

}

bool objects::PhimBitsArray::getBitInverted(int _bitIndex) { 
    
    return objects::ByteOperation::getBit(getByteInverted(_bitIndex / 8), 7 - (_bitIndex - _bitIndex / 8 * 8)); 

}

char* objects::PhimBitsArray::getBytesRepresentation() { 

    char* _rtr = (char*) malloc(sizeof(char) * bytesLenght * 8  + 1);
    char* _temp = _rtr;

    for (int _ = 0; _ < bytesLenght; _++) {

        objects::ByteOperation::getByteRepresentation(bytes[_], _temp);

        _temp += 8;

    }

    *_temp = 0;

    return _rtr;

}

char* objects::PhimBitsArray::toString() {} // TODO <- same as getBytesRepresentation() but dynamic allocation

void objects::PhimBitsArray::addNewByte(unsigned char _value) { 

    unsigned char* _newValue = (unsigned char*) malloc(sizeof(unsigned char) * bytesLenght + 1);

    if (bytesLenght) copyBytes(_newValue + 1);

    *_newValue = _value;

    free(bytes);

    bytes = _newValue;

    ++bytesLenght;

}

bool objects::PhimBitsArray::setByte(int _byteIndex, unsigned char _value) { 

    if (_byteIndex >= bytesLenght || _byteIndex < 0) return 0;

    bytes[_byteIndex] = _value;

}

bool objects::PhimBitsArray::setBitOfByte(int _byteIndex, int _bitIndex, bool _value) { 

    if (_byteIndex >= bytesLenght || _byteIndex < 0) return false;

    return objects::ByteOperation::setBit(
        bytes + _byteIndex,
        _bitIndex,
        _value
    );

}

bool objects::PhimBitsArray::setBit(int _bitIndex, bool _value) { 

    if (_bitIndex >= bytesLenght * 8 || _bitIndex < 0) return false;

    return objects::ByteOperation::setBit(
        bytes + _bitIndex / 8,
        _bitIndex - _bitIndex / 8 * 8,
        _value
    );

}

bool objects::PhimBitsArray::setByteInverted(int _byteIndex, unsigned char _value) { 

    if (_byteIndex >= bytesLenght || _byteIndex < 0) return 0;

    bytes[bytesLenght - 1 - _byteIndex] = _value;

}

bool objects::PhimBitsArray::setBitOfByteInverted(int _byteIndex, int _bitIndex, bool _value) { 

    if (_byteIndex >= bytesLenght || _byteIndex < 0) return false;

    return objects::ByteOperation::setBit(
        bytes + (bytesLenght - 1 - _byteIndex),
        7 - _bitIndex,
        _value
    );

}

bool objects::PhimBitsArray::setBitInverted(int _bitIndex, bool _value) { 

    if (_bitIndex >= bytesLenght * 8 || _bitIndex < 0) return false;

    return objects::ByteOperation::setBit(
        bytes + (bytesLenght - 1 - _bitIndex / 8),
        7 - (_bitIndex - _bitIndex / 8 * 8),
        _value
    );

}

bool objects::PhimBitsArray::isOdd() { return getBitInverted(0); } 

bool objects::PhimBitsArray::isZero() { 

    bool _rtr = 1;

    for (int _ = 0; _ < bytesLenght * 8; _++)

        if (
            getBit(_)
        ) { _rtr = 0; break; }

    return _rtr;

}

bool objects::PhimBitsArray::operator<(PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    unsigned char _val1, _val2;
    bool _rtr = 0;

    for (int _crrntByte = biggerLenght - 1; _crrntByte >= 0; _crrntByte--) {

        if (
            (_val1 = getByteInverted(_crrntByte)) == (_val2 = _.getByteInverted(_crrntByte))
        ) continue;

        if (_val1 > _val2) break;

        _rtr = 1;

        break;

    }

    return _rtr;

}

bool objects::PhimBitsArray::operator>(PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    unsigned char _val1, _val2;
    bool _rtr = 0;

    for (int _crrntByte = biggerLenght - 1; _crrntByte >= 0; _crrntByte--) {

        if (
            (_val1 = getByteInverted(_crrntByte)) == (_val2 = _.getByteInverted(_crrntByte))
        ) continue;

        if (_val1 < _val2) break;

        _rtr = 1;

        break;

    }

    return _rtr;

}

bool objects::PhimBitsArray::operator<=(PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    unsigned char _val1, _val2;
    bool _rtr = 1;

    for (int _crrntByte = biggerLenght - 1; _crrntByte >= 0; _crrntByte--) {

        if (
            (_val1 = getByteInverted(_crrntByte)) == (_val2 = _.getByteInverted(_crrntByte))
        ) continue;

        if (_val1 < _val2) break;

        _rtr = 0;

        break;

    }

    return _rtr;

}

bool objects::PhimBitsArray::operator>=(PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    unsigned char _val1, _val2;
    bool _rtr = 1;

    for (int _crrntByte = biggerLenght - 1; _crrntByte >= 0; _crrntByte--) {

        if (
            (_val1 = getByteInverted(_crrntByte)) == (_val2 = _.getByteInverted(_crrntByte))
        ) continue;

        if (_val1 > _val2) break;

        _rtr = 0;

        break;

    }

    return _rtr;

}

bool objects::PhimBitsArray::operator==(PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    bool _rtr = 1;

    for (int _crrntByte = biggerLenght - 1; _crrntByte >= 0; _crrntByte--) {

        if (
            getByteInverted(_crrntByte) != _.getByteInverted(_crrntByte)
        ) { _rtr = 0; break; }

    }

    return _rtr;

}

bool objects::PhimBitsArray::operator!=(PhimBitsArray& _) { return !operator==(_); }

objects::PhimBitsArray objects::PhimBitsArray::operator&(objects::PhimBitsArray& _) { 

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    objects::PhimBitsArray _rtr; _rtr.bytes = 0; _rtr.bytesLenght = 0;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        _rtr.addNewByte(
            getByteInverted(_crrntByte) & _.getByteInverted(_crrntByte)
        );

    return _rtr;

}

objects::PhimBitsArray objects::PhimBitsArray::operator|(objects::PhimBitsArray& _) { 

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    objects::PhimBitsArray _rtr; _rtr.bytes = 0; _rtr.bytesLenght = 0;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        _rtr.addNewByte(
            getByteInverted(_crrntByte) | _.getByteInverted(_crrntByte)
        );

    return _rtr;

}

objects::PhimBitsArray objects::PhimBitsArray::operator^(objects::PhimBitsArray& _) { 

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    objects::PhimBitsArray _rtr; _rtr.bytes = 0; _rtr.bytesLenght = 0;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        _rtr.addNewByte(
            getByteInverted(_crrntByte) ^ _.getByteInverted(_crrntByte)
        );

    return _rtr;

}

objects::PhimBitsArray objects::PhimBitsArray::operator~() { 

    objects::PhimBitsArray _rtr; _rtr.bytes = 0; _rtr.bytesLenght = 0;

    for (int _crrntByte = 0; _crrntByte < bytesLenght; _crrntByte++)
        
        _rtr.addNewByte(
            ~getByteInverted(_crrntByte)
        );

    return _rtr;

}

void objects::PhimBitsArray::operator&=(objects::PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        if (
            _crrntByte >= bytesLenght
        ) addNewByte(getByteInverted(_crrntByte) & _.getByteInverted(_crrntByte));

        else setByteInverted(_crrntByte, getByteInverted(_crrntByte) & _.getByteInverted(_crrntByte));

}

void objects::PhimBitsArray::operator|=(objects::PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        if (
            _crrntByte >= bytesLenght
        ) addNewByte(getByteInverted(_crrntByte) | _.getByteInverted(_crrntByte));

        else setByteInverted(_crrntByte, getByteInverted(_crrntByte) & _.getByteInverted(_crrntByte));

}

void objects::PhimBitsArray::operator^=(objects::PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        if (
            _crrntByte >= bytesLenght
        ) addNewByte(getByteInverted(_crrntByte) ^ _.getByteInverted(_crrntByte));

        else setByteInverted(_crrntByte, getByteInverted(_crrntByte) & _.getByteInverted(_crrntByte));

}

objects::PhimBitsArray objects::PhimBitsArray::operator<<(int _) {

    objects::PhimBitsArray _rtr; _rtr.bytesLenght = bytesLenght; _rtr.bytes = (unsigned char*) malloc(sizeof(unsigned char) * _rtr.bytesLenght);
    copyBytes(_rtr.bytes);

    for (int _crrntShift = 0; _crrntShift < _; _crrntShift++) {

        for (int _crrntBit = 0; _crrntBit < bytesLenght * 8 - 1; _crrntBit++) 

            _rtr.setBit(
                _crrntBit,
                _rtr.getBit(_crrntBit + 1)
            );

        _rtr.setBit(
            bytesLenght * 8 - 1,
            0
        );
    }

    return _rtr;


}

objects::PhimBitsArray objects::PhimBitsArray::operator>>(int _) {

    objects::PhimBitsArray _rtr; _rtr.bytesLenght = bytesLenght; _rtr.bytes = (unsigned char*) malloc(sizeof(unsigned char) * _rtr.bytesLenght);
    copyBytes(_rtr.bytes);

    for (int _crrntShift = 0; _crrntShift < _; _crrntShift++) {

        for (int _crrntBit = bytesLenght * 8 - 1; _crrntBit >= 0; _crrntBit--) 

            _rtr.setBit(
                _crrntBit,
                _rtr.getBit(_crrntBit + 1)
            );

        _rtr.setBit(
            bytesLenght * 8 - 1,
            0
        );
    }

    return _rtr;
}

void objects::PhimBitsArray::operator<<=(int _) {

    for (int _crrntShift = 0; _crrntShift < _; _crrntShift++) {

        for (int _crrntBit = 0; _crrntBit < bytesLenght * 8 - 1; _crrntBit++) 

            setBit(
                _crrntBit,
                getBit(_crrntBit + 1)
            );

        setBit(
            bytesLenght * 8 - 1,
            0
        );
    }

}

void objects::PhimBitsArray::operator>>=(int _) {

    for (int _crrntShift = 0; _crrntShift < _; _crrntShift++) {

        for (int _crrntBit = bytesLenght * 8 - 1; _crrntBit >= 0; _crrntBit--) 

            setBit(
                _crrntBit + 1,
                getBit(_crrntBit)
            );

        setBit(
            0,
            0
        );
    }

}

objects::PhimBitsArray objects::PhimBitsArray::operator+(objects::PhimBitsArray& _) {

    objects::PhimBitsArray _rtr; _rtr.bytes = 0; _rtr.bytesLenght = 0;
    
    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    bool _over = 0;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        _rtr.addNewByte(
            objects::ByteOperation::addBytes(
                getByteInverted(_crrntByte), 
                _.getByteInverted(_crrntByte), 
                _over)
        );

    if (_over) 

        _rtr.addNewByte(
            1
        );

    return _rtr;

}

objects::PhimBitsArray objects::PhimBitsArray::operator-(objects::PhimBitsArray& _) {

    objects::PhimBitsArray _rtr; _rtr.bytes = 0; _rtr.bytesLenght = 0;
    
    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    bool _over = 0;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++)

        _rtr.addNewByte(
            objects::ByteOperation::subBytes(
                getByteInverted(_crrntByte), 
                _.getByteInverted(_crrntByte), 
                _over)
        );

    if (_over) 

        _rtr.clean();

    return _rtr;

}

void objects::PhimBitsArray::operator+=(objects::PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    unsigned char _temp;
    bool _over = 0;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++) {

        _temp = objects::ByteOperation::addBytes(
                getByteInverted(_crrntByte), 
                _.getByteInverted(_crrntByte), 
                _over);

        if (
            _crrntByte >= bytesLenght
        ) addNewByte(_temp);

        else setByteInverted(_crrntByte, _temp);

    }

    if (_over) 

        addNewByte(
            1
        );

}

void objects::PhimBitsArray::operator-=(objects::PhimBitsArray& _) {

    int biggerLenght = (bytesLenght > _.bytesLenght) ? bytesLenght : _.bytesLenght;
    unsigned char _temp;
    bool _over = 0;

    for (int _crrntByte = 0; _crrntByte < biggerLenght; _crrntByte++) {

        _temp = objects::ByteOperation::subBytes(
                getByteInverted(_crrntByte), 
                _.getByteInverted(_crrntByte), 
                _over);

        if (
            _crrntByte >= bytesLenght
        ) addNewByte(_temp);

        else setByteInverted(_crrntByte, _temp);

    }

    if (_over) clean();

}

objects::PhimBitsArray objects::PhimBitsArray::operator*(objects::PhimBitsArray& _) {

    objects::PhimBitsArray _rtr, _this, __; 
    _rtr.bytes = 0; _rtr.bytesLenght = 0;
    _this.bytesLenght = bytesLenght; _this.bytes = (unsigned char*) malloc(sizeof(unsigned char) * _this.bytesLenght);
    __.bytesLenght = _.bytesLenght; __.bytes = (unsigned char*) malloc(sizeof(unsigned char) * __.bytesLenght);
    
    copyBytes(_this.bytes);
    _.copyBytes(__.bytes);

    for (int _ = bytesLenght; _ < bytesLenght + __.bytesLenght; _++) _this.addNewByte(0);

    while(!__.isZero()) {

        if (__.isOdd()) _rtr += _this;

        __ >>= 1;
        _this <<= 1;

    }

    return _rtr;

}
        
objects::PhimBitsArray objects::PhimBitsArray::operator/(objects::PhimBitsArray& _) {

    objects::PhimBitsArray _rtr, _temp; 
    _rtr.bytes = 0; _rtr.bytesLenght = 0;
    _temp.bytes = 0; _temp.bytesLenght = 0;
    int _crrntBit = 0;

    for (int _c = 0; _c < _.bytesLenght + 1; _c++) _temp.addNewByte(0);
    for (int _c = 0; _c < bytesLenght; _c++) _rtr.addNewByte(0);

    while(1) {

        while(1) {

            if (_crrntBit >= bytesLenght * 8) return _rtr;

            _temp <<= 1;

            _temp.setBitInverted(
                0,
                getBit(_crrntBit++)
            );

            if (_temp >= _) break;

            _rtr <<= 1;

        }

        _temp -= _;

        _rtr <<= 1;

        _rtr.setBitInverted(0, 1);

    }

}

objects::PhimBitsArray objects::PhimBitsArray::operator%(objects::PhimBitsArray& _) {

    objects::PhimBitsArray _rtr, _temp; 
    _rtr.bytes = 0; _rtr.bytesLenght = 0;
    _temp.bytes = 0; _temp.bytesLenght = 0;
    int _crrntBit = 0;

    for (int _c = 0; _c < _.bytesLenght + 1; _c++) _temp.addNewByte(0);
    for (int _c = 0; _c < bytesLenght; _c++) _rtr.addNewByte(0);

    while(1) {

        while(1) {

            if (_crrntBit >= bytesLenght * 8) return _temp;

            _temp <<= 1;

            _temp.setBitInverted(
                0,
                getBit(_crrntBit++)
            );

            if (_temp >= _) break;

            _rtr <<= 1;

        }

        _temp -= _;

        _rtr <<= 1;

        _rtr.setBitInverted(0, 1);

    }

}

void objects::PhimBitsArray::operator*=(objects::PhimBitsArray& _) {

    objects::PhimBitsArray _this, __; 
    _this.bytesLenght = bytesLenght; _this.bytes = (unsigned char*) malloc(sizeof(unsigned char) * _this.bytesLenght);
    __.bytesLenght = _.bytesLenght; __.bytes = (unsigned char*) malloc(sizeof(unsigned char) * __.bytesLenght);
    
    copyBytes(_this.bytes);
    _.copyBytes(__.bytes);

    clean();

    for (int _ = bytesLenght; _ < bytesLenght + __.bytesLenght; _++) _this.addNewByte(0);

    while(!__.isZero()) {

        if (__.isOdd()) *this += _this;

        __ >>= 1;
        _this <<= 1;

    }

}

void objects::PhimBitsArray::operator/=(objects::PhimBitsArray& _) {

    objects::PhimBitsArray _rtr, _temp; 
    _rtr.bytes = 0; _rtr.bytesLenght = 0;
    _temp.bytes = 0; _temp.bytesLenght = 0;
    int _crrntBit = 0;

    for (int _c = 0; _c < _.bytesLenght + 1; _c++) _temp.addNewByte(0);
    for (int _c = 0; _c < bytesLenght; _c++) _rtr.addNewByte(0);

    while(1) {

        while(1) {

            if (_crrntBit >= bytesLenght * 8) {

                free(bytes);

                bytes = (unsigned char*) malloc(sizeof(unsigned char) * _rtr.bytesLenght);

                _rtr.copyBytes(bytes);

                return;    
            
            }

            _temp <<= 1;

            _temp.setBitInverted(
                0,
                getBit(_crrntBit++)
            );

            if (_temp >= _) break;

            _rtr <<= 1;

        }

        _temp -= _;

        _rtr <<= 1;

        _rtr.setBitInverted(0, 1);

    }


}



