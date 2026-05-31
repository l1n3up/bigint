#include "BigInt.h"
#include <stdexcept>
#include <cctype>
#include <algorithm>

// leading zero check
void BigInt::remove_leading_zeros()
{
    while (digits.size() > 1 && digits.back() == 0)
    {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0)
    {
        is_negative = false;
    }
}

bool BigInt::abs_less(const BigInt &other) const
{
    if (digits.size() != other.digits.size())
    {
        return digits.size() < other.digits.size();
    }
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i)
    {
        if (digits[i] != other.digits[i])
        {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

BigInt BigInt::abs_add(const BigInt &lhs, const BigInt &rhs)
{
    BigInt result;
    result.digits.clear();
    int carry = 0;
    size_t i = 0;
    while (i < lhs.digits.size() || i < rhs.digits.size() || carry)
    {
        int sum = carry;
        if (i < lhs.digits.size())
            sum += lhs.digits[i];
        if (i < rhs.digits.size())
            sum += rhs.digits[i];
        result.digits.push_back(sum % 10);
        carry = sum / 10;
        i++;
    }
    return result;
}

BigInt BigInt::abs_sub(const BigInt &lhs, const BigInt &rhs)
{
    BigInt result;
    result.digits.clear();
    int borrow = 0;
    for (size_t i = 0; i < lhs.digits.size(); ++i)
    {
        int diff = lhs.digits[i] - borrow - (i < rhs.digits.size() ? rhs.digits[i] : 0);
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result.digits.push_back(diff);
    }
    result.remove_leading_zeros();
    return result;
}

BigInt::BigInt() : is_negative(false)
{
    digits.push_back(0);
}

BigInt::BigInt(long long value)
{
    if (value < 0)
    {
        is_negative = true;
        value = -value;
    }
    else
    {
        is_negative = false;
    }
    if (value == 0)
    {
        digits.push_back(0);
    }
    else
    {
        while (value > 0)
        {
            digits.push_back(value % 10);
            value /= 10;
        }
    }
}

BigInt::BigInt(const std::string &str) : is_negative(false)
{
    if (str.empty())
    {
        throw std::invalid_argument("Err: plain string");
    }
    size_t start = 0;

    if (str[0] == '-')
    {
        is_negative = true;
        start = 1;
    }
    else if (str[0] == '+')
    {
        start = 1;
    }

    if (start == str.length())
    {
        throw std::invalid_argument("Err: wrong nmber format");
    }

    for (size_t i = str.length(); i > start; --i)
    {
        char ch = str[i - 1];
        if (!std::isdigit(static_cast<unsigned char>(ch)))
        {
            throw std::invalid_argument("Err: incorrect symbols in string given");
        }
        digits.push_back(ch - '0');
    }
    remove_leading_zeros();
}

BigInt BigInt::operator-() const
{
    BigInt res = *this;
    if (res.digits.size() == 1 && res.digits[0] == 0)
        return res;
    res.is_negative = !res.is_negative;
    return res;
}

bool BigInt::operator==(const BigInt &other) const
{
    return is_negative == other.is_negative && digits == other.digits;
}

bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}

bool BigInt::operator<(const BigInt &other) const
{
    if (is_negative != other.is_negative)
    {
        return is_negative;
    }
    if (is_negative)
    {
        return other.abs_less(*this);
    }
    return abs_less(other);
}

bool BigInt::operator<=(const BigInt &other) const
{
    return *this < other || *this == other;
}

bool BigInt::operator>(const BigInt &other) const
{
    return !(*this <= other);
}

bool BigInt::operator>=(const BigInt &other) const
{
    return !(*this < other);
}

BigInt BigInt::operator+(const BigInt &other) const
{
    if (is_negative == other.is_negative)
    {
        BigInt res = abs_add(*this, other);
        res.is_negative = is_negative;
        return res;
    }
    if (abs_less(other))
    {
        BigInt res = abs_sub(other, *this);
        res.is_negative = other.is_negative;
        return res;
    }
    else
    {
        BigInt res = abs_sub(*this, other);
        res.is_negative = is_negative;
        return res;
    }
}

BigInt BigInt::operator-(const BigInt &other) const
{
    return *this + (-other);
}

BigInt BigInt::operator*(const BigInt &other) const
{
    BigInt result;
    result.digits.assign(digits.size() + other.digits.size(), 0);

    for (size_t i = 0; i < digits.size(); ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; ++j)
        {
            long long cur = result.digits[i + j] +
                            digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0) +
                            carry;
            result.digits[i + j] = cur % 10;
            carry = static_cast<int>(cur / 10);
        }
    }

    result.is_negative = (is_negative != other.is_negative);
    result.remove_leading_zeros();
    return result;
}

std::ostream &operator<<(std::ostream &os, const BigInt &val)
{
    if (val.is_negative)
        os << '-';
    for (int i = static_cast<int>(val.digits.size()) - 1; i >= 0; --i)
    {
        os << val.digits[i];
    }
    return os;
}

std::istream &operator>>(std::istream &is, BigInt &val)
{
    std::string str;
    if (is >> str)
    {
        try
        {
            val = BigInt(str);
        }
        catch (const std::invalid_argument &)
        {
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}