#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>

class BigInt
{
private:
    std::vector<int> digits;
    bool is_negative;

    // encapsulated methods for validations and actions
    void remove_leading_zeros();
    bool abs_less(const BigInt &other) const;
    static BigInt abs_add(const BigInt &lhs, const BigInt &rhs);
    static BigInt abs_sub(const BigInt &lhs, const BigInt &rhs);

public:
    BigInt();
    BigInt(long long value);
    BigInt(const std::string &str);

    BigInt operator-() const;

    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;

    friend std::ostream &operator<<(std::ostream &os, const BigInt &val);
    friend std::istream &operator>>(std::istream &is, BigInt &val);
};

#endif