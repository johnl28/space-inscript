#pragma once



//#define TO_FLOAT(floatNumber) static_cast<float>(floatNumber)
//#define TO_INT(intNumber) static_cast<int>(intNumber)




template<typename T>
float to_float(const T& value) {
    return static_cast<float>(value);
}

template<typename T>
int to_int(const T& value) {
    return static_cast<int>(value);
}


