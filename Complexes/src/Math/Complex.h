#pragma once

#include <string>

class Complex
{
public:
	Complex(const double& real, const double& imaginary);
	Complex(const double& real);
	Complex();
	Complex(const Complex& other) = default;

	std::string toString() const;

	inline double getReal() const { return m_Re; }
	inline double getImaginary() const { return m_Im; }

	inline void setReal(const double& re) { m_Re = re; }
	inline void setImaginary(const double& im) { m_Im = im; }

	Complex conjugate() const;
	double module() const;
	double argument() const;
	Complex normalize() const;
	Complex pow(const uint32_t& degree) const;

	Complex add(const Complex& other) const;
	Complex add(const double& value) const;
	Complex subtract(const Complex& other) const;
	Complex subtract(const double& value) const;
	Complex multiply(const Complex& other) const;
	Complex multiply(const double& value) const;
	Complex divide(const Complex& other) const;
	Complex divide(const double& other) const;

	Complex operator+(const Complex& other) const;
	Complex operator+(const double& value) const;
	Complex operator+=(const Complex& other);
	Complex operator+=(const double& value);
	Complex operator-(const Complex& other) const;
	Complex operator-(const double& value) const;
	Complex operator-=(const Complex& other);
	Complex operator-=(const double& value);
	Complex operator*(const Complex& other) const;
	Complex operator*(const double& value) const;
	Complex operator*=(const Complex& other);
	Complex operator*=(const double& value);
	Complex operator/(const Complex& other) const;
	Complex operator/(const double& value) const;
	Complex operator/=(const Complex& other);
	Complex operator/=(const double& value);

	friend std::ostream& operator<<(std::ostream& os, const Complex& z);

private:
	std::string to_string(const double& value) const;

	double m_Re, m_Im;
};
