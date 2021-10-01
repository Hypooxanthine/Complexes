#include "Complex.h"

#include <iostream>

Complex::Complex(const double& real, const double& imaginary) 
	: m_Re(real), m_Im(imaginary)
{}

Complex::Complex(const double& real)
	: Complex(real, 0)
{}

Complex::Complex()
	: Complex(0, 0)
{}

std::string Complex::toString() const
{
	std::string out = "";

	// Real part
	if (m_Re != 0)
		out += to_string(m_Re);

	// Imaginary sign
	if (m_Im != 0)
	{
		if (m_Im > 0 && m_Re != 0)
			out += "+";

		if (m_Im == -1)
			out += "-";
		else if(m_Im != 1)
			out += to_string(m_Im);

		out += "i";
	}
	else
	{
		if (m_Re == 0)
			out += "0";
	}

	return out;
}

Complex Complex::conjugate() const
{
	auto out = Complex(m_Re, -m_Im);
	return out;
}


double Complex::module() const
{
	return sqrt(m_Re * m_Re + m_Im * m_Im);
}

double Complex::argument() const
{
	if (m_Im > 0)
		return acos(m_Re / module());
	else
		return -acos(m_Re / module());
}

Complex Complex::normalize() const
{
	return this->divide(this->module());
}

Complex Complex::pow(const uint32_t& degree) const
{
	if (degree == 0)
		return Complex();

	Complex out = *this;

	for (uint32_t i = 1; i < degree; i++)
	{
		out = out.multiply(*this);
	}

	return out;
}

Complex Complex::add(const Complex& other) const
{
	auto out = Complex(m_Re + other.m_Re, m_Im + other.m_Im);
	return out;
}

Complex Complex::add(const double& value) const
{
	return this->add(Complex(value));
}

Complex Complex::subtract(const Complex& other) const
{
	return this->add(Complex(-other.m_Re, -other.m_Im));
}

Complex Complex::subtract(const double& value) const
{
	return this->subtract(Complex(value));
}

Complex Complex::multiply(const Complex& other) const
{
	auto out = Complex(m_Re * other.m_Re - m_Im * other.m_Im,
		m_Re * other.m_Im + m_Im * other.m_Re);
	return out;
}

Complex Complex::multiply(const double& value) const
{
	return this->multiply(Complex(value));
}

Complex Complex::divide(const Complex& other) const
{
	if (other.m_Re == 0 && other.m_Im == 0)
		return Complex();

	Complex numerator = this->multiply(other.conjugate());
	double denominator = other.m_Re * other.m_Re - other.m_Im * other.m_Im;

	return Complex(numerator.m_Re / denominator, numerator.m_Im / denominator);
}

Complex Complex::divide(const double& value) const
{
	return this->divide(Complex(value));
}

Complex Complex::operator+(const Complex& other) const
{
	return this->add(other);
}

Complex Complex::operator+(const double& value) const
{
	return this->add(value);
}

Complex Complex::operator+=(const Complex& other)
{
	*this = this->add(other);
	return *this;
}

Complex Complex::operator+=(const double& value)
{
	return *this += Complex(value);
}

Complex Complex::operator-(const Complex& other) const
{
	return this->subtract(other);
}

Complex Complex::operator-(const double& value) const
{
	return this->subtract(value);
}

Complex Complex::operator-=(const Complex& other)
{
	*this = this->subtract(other);
	return *this;
}

Complex Complex::operator-=(const double& value)
{
	return *this -= Complex(value);
}

Complex Complex::operator*(const Complex& other) const
{
	return this->multiply(other);
}

Complex Complex::operator*(const double& value) const
{
	return this->multiply(value);
}

Complex Complex::operator*=(const Complex& other)
{
	*this = this->multiply(other);
	return *this;
}

Complex Complex::operator*=(const double& value)
{
	return *this *= Complex(value);
}

Complex Complex::operator/(const Complex& other) const
{
	return this->divide(other);
}

Complex Complex::operator/(const double& value) const
{
	return this->divide(value);
}

Complex Complex::operator/=(const Complex& other)
{
	*this = this->divide(other);
	return *this;
}

Complex Complex::operator/=(const double& value)
{
	return *this /= Complex(value);
}

std::string Complex::to_string(const double& value) const
{
	std::string out = std::to_string(value);
	out.erase(out.find_last_not_of('0') + 1, std::string::npos);

	if (out[out.size() - 1] == '.')
		out.erase(out.size() - 1);

	return out;
}

std::ostream& operator<<(std::ostream& os, const Complex& z)
{
	os << z.toString();
	return os;
}