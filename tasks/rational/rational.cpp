#include "rational.h"

Rational::Rational() : numer_(0), denom_(1) {
}

Rational::Rational(int value) : numer_(value), denom_(1) {  // NOLINT
}

Rational::Rational(int numer, int denom) : numer_(numer), denom_(denom) {
    if (denom_ == 0) {
        throw RationalDivisionByZero{};
    }
    if (denom_ < 0) {
        denom_ *= -1;
        numer_ *= -1;
    }
    int gcd_numer_denom = std::gcd(abs(numer_), denom_);
    numer_ /= gcd_numer_denom;
    denom_ /= gcd_numer_denom;
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    *this = Rational(value, this->denom_);
}

void Rational::SetDenominator(int value) {
    *this = Rational(this->numer_, value);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t numer = lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator();
    int64_t denom = lhs.GetDenominator() * rhs.GetDenominator();
    lhs.Set(numer, denom);
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int64_t numer = lhs.GetNumerator() * rhs.GetNumerator();
    int64_t denom = lhs.GetDenominator() * rhs.GetDenominator();
    lhs.Set(numer, denom);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string str;
    is >> str;
    ratio.SetNumerator(std::stoi(str.substr(0, str.find('/'))));
    if (str.find('/') != str.npos) {
        ratio.SetDenominator(std::stoi(str.substr(str.find('/') + 1)));
    } else {
        ratio.SetDenominator(1);
    }
    return is;
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    if (denom < 0) {
        denom *= -1;
        numer *= -1;
    }
    int64_t gcd_numer_denom = std::gcd(abs(numer), denom);
    numer /= gcd_numer_denom;
    denom /= gcd_numer_denom;
    numer_ = static_cast<int>(numer);
    denom_ = static_cast<int>(denom);
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return res += rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return res -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return res *= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational res = lhs;
    return res /= rhs;
}

Rational operator++(Rational& ratio, int) {
    Rational tmp = ratio;
    ++ratio;
    return tmp;
}

Rational operator--(Rational& ratio, int) {
    Rational tmp = ratio;
    --ratio;
    return tmp;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() > rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() == rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << '/' << ratio.GetDenominator();
    }
    return os;
}
