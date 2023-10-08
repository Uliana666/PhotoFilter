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
    lhs = lhs + rhs;
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs = lhs * rhs;
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
    return is >> ratio.numer_ >> ratio.denom_;
}

void Rational::Set(int64_t numer, int64_t denom) {
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs = lhs / rhs;
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int numer = lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator();
    int denom = lhs.GetDenominator() * rhs.GetDenominator();
    return Rational(numer, denom);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int numer = lhs.GetNumerator() * rhs.GetDenominator() - rhs.GetNumerator() * lhs.GetDenominator();
    int denom = lhs.GetDenominator() * rhs.GetDenominator();
    return Rational(numer, denom);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int numer = lhs.GetNumerator() * rhs.GetNumerator();
    int denom = lhs.GetDenominator() * rhs.GetDenominator();
    return Rational(numer, denom);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int numer = lhs.GetNumerator() * rhs.GetDenominator();
    int denom = lhs.GetDenominator() * rhs.GetNumerator();
    return Rational(numer, denom);
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
    return os << ratio.GetNumerator() << ' ' << ratio.GetDenominator();
}
