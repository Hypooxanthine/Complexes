#pragma once

#include <string>

class Complex
{
public:
	Complex(const long double& real, const long double& imaginary);
	Complex(const long double& real);
	Complex();
	Complex(const Complex& other) = default;

	std::string toString() const;

	inline long double getReal() const { return m_Re; }
	inline long double getImaginary() const { return m_Im; }

	inline void setReal(const long double& re) { m_Re = re; }
	inline void setImaginary(const long double& im) { m_Im = im; }

	Complex conjugate() const;
	long double module() const;
	long double argument() const;
	Complex normalize() const;
	Complex pow(const uint32_t& degree) const;

	Complex add(const Complex& other) const;
	Complex add(const long double& value) const;
	Complex subtract(const Complex& other) const;
	Complex subtract(const long double& value) const;
	Complex multiply(const Complex& other) const;
	Complex multiply(const long double& value) const;
	Complex divide(const Complex& other) const;
	Complex divide(const long double& other) const;

	Complex operator+(const Complex& other) const;
	Complex operator+(const long double& value) const;
	Complex operator+=(const Complex& other);
	Complex operator+=(const long double& value);
	Complex operator-(const Complex& other) const;
	Complex operator-(const long double& value) const;
	Complex operator-=(const Complex& other);
	Complex operator-=(const long double& value);
	Complex operator*(const Complex& other) const;
	Complex operator*(const long double& value) const;
	Complex operator*=(const Complex& other);
	Complex operator*=(const long double& value);
	Complex operator/(const Complex& other) const;
	Complex operator/(const long double& value) const;
	Complex operator/=(const Complex& other);
	Complex operator/=(const long double& value);

	friend std::ostream& operator<<(std::ostream& os, const Complex& z);

private:
	std::string to_string(const long double& value) const;

	long double m_Re, m_Im;
};
