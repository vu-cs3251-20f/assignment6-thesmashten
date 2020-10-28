/* @author G. Hemingway, copyright 2020 - All rights reserved */
#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <Vector.h>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <sstream>
#include <stdexcept>

/**
 *  Creates the zero vector.
 */
template <uint32_t DIM> Vector<DIM>::Vector() noexcept
{
    std::fill_n(begin(), DIM, 0.0);
}

/**
 *  Creates a vector using the first DIM values starting at ptr.
 */
template <uint32_t DIM> Vector<DIM>::Vector(const double* ptr) noexcept
{
    std::copy_n(ptr, DIM, begin());
}

/*******************************************************************************
 *                                                                              *
 *                        S P A C E   O P E R A T I O N S                       *
 *                                                                              *
 *******************************************************************************/

/**
 *  Returns the sum of this vector and rhs.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::add(const Vector<DIM>& rhs) const
{
    Vector<DIM> sum;
    // Either the functor approach -- currently commented out -- or the lambda approach is fine
    // std::transform(begin(), end(), rhs.begin(), sum.begin(), adder());
    std::transform(begin(), end(), rhs.begin(), sum.begin(),
        [](const auto& l, const auto& r) { return l + r; });
    return sum;
}

/**
 *  Returns the additive inverse of this vector.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::invert() const
{
    return scale(-1.0);
}

/**
 *  Scales a copy of this vector by rhs and returns the result.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::scale(const double& rhs) const
{
    Vector<DIM> s;
    // Either the functor approach -- currently commented out -- or the lambda approach is fine
    // Via a binder, we can reuse multiplier with a transform
    // std::transform(begin(), end(), s.begin(), std::bind2nd(multiplier(), rhs));
    std::transform(begin(), end(), s.begin(), [rhs](const auto& value) { return value * rhs; });
    return s;
}

/**
 *  Returns the dot (inner) product of this vector and rhs.
 */
template <uint32_t DIM> double Vector<DIM>::dot(const Vector<DIM>& rhs) const
{
    // transform will return the output iterator. Therefore, I hacked together
    // an iterator that will actually accumulate the values that are "assigned
    // to its content."
    // return std::transform(begin(), end(), rhs.begin(), accumulator_iter(),
    // multiplier()).accumulator;
    double product = 0.0;
    Vector<DIM> outVec;
    std::transform(begin(), end(), rhs.begin(), outVec.begin(),
        [&product](const auto& l, const auto& r) { return product += l * r; });
    return product;
}

/**
 *  Returns the square of the magnitude of this vector.
 */
template <uint32_t DIM> double Vector<DIM>::normSq() const
{
    // Dot product of a vector with itself yields the square of the norm.
    return dot(*this);
}

/**
 *  Returns the magnitude of this vector.
 */
template <uint32_t DIM> double Vector<DIM>::norm() const
{
    return std::sqrt(normSq());
}

/**
 *  Returns a scaled copy of this vector such that its magnitude is 1
 *  Throw overflow_error if norm is zero
 */
template <uint32_t DIM> Vector<DIM> Vector<DIM>::normalize() const
{
    Vector<DIM> tmp(*this);
    double norm = tmp.norm();
    if (norm == 0)
        throw std::overflow_error("vector norm is zero");
    return tmp /= norm;
}

/**
 *  Returns the cross product of this and rhs if called on a 3D vector.
 *  throws an std::domain_error otherwise.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::cross(const Vector<DIM>& v) const
{
    (void)(v);
    throw std::domain_error("Operation not supported");
}

template <> const Vector<3> inline Vector<3>::cross(const Vector<3>& v) const
{
    Vector<3> c;
    c[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
    c[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
    c[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
    return c;
}

/**
 *  Returns a human readable representation of this vector.
 *  Ex. [1 2 3]
 */
template <uint32_t DIM> std::string Vector<DIM>::toString() const
{
    std::stringstream str;
    str << "[";
    // We know that DIM is at least 1 so the following is safe and lets us
    // avoid substringing to erase the final space that the naive approach would
    // produce.
    std::copy(begin(), end() - 1, std::ostream_iterator<double>(str, " "));
    str << (*this)[DIM - 1] << "]";
    return str.str();
}

/***************************************************************************
 *                                                                          *
 *                  O V E R L O A D E D   O P E R A T O R S                 *
 *                                                                          *
 ***************************************************************************/

/**
 *  Returns true if this vector equals rhs.
 */
template <uint32_t DIM> bool Vector<DIM>::operator==(const Vector<DIM>& rhs) const
{
    // Can use either a functor or lambda
    // return std::equal(begin(), end(), rhs.begin(), epsilonTest());
    return std::equal(
        begin(), end(), rhs.begin(), [](auto l, auto r) { return std::abs(r - l) < 0.0000000001; });
}

/**
 *  Returns true if this vector differs from rhs.
 */
template <uint32_t DIM> bool Vector<DIM>::operator!=(const Vector<DIM>& rhs) const
{
    return !(*this == rhs);
}

/**
 *  Returns a reference to the index-th component of this vector. Not range
 *  checked.
 */
template <uint32_t DIM> double& Vector<DIM>::operator[](uint32_t index)
{
    return data[index];
}

/**
 *  Returns a reference to the index-th component of this vector. Not range
 *  checked.
 */
template <uint32_t DIM> const double& Vector<DIM>::operator[](uint32_t index) const
{
    return data[index];
}

/**
 *  Returns the sum of this vector and rhs.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::operator+(const Vector<DIM>& rhs) const
{
    return add(rhs);
}

/**
 *  Increments this vector by rhs and returns the result for chaining.
 */
template <uint32_t DIM> Vector<DIM>& Vector<DIM>::operator+=(const Vector<DIM>& rhs)
{
    return *this = *this + rhs;
}

/**
 *  Returns the additive inverse of this vector.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::operator-() const
{
    return scale(-1.0);
}

/**
 *  Returns the difference between this vector and rhs.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::operator-(const Vector<DIM>& rhs) const
{
    return *this + -rhs;
}

/**
 *  Decrements this vector by rhs and returns the result for chaining.
 */
template <uint32_t DIM> Vector<DIM>& Vector<DIM>::operator-=(const Vector<DIM>& v)
{
    return *this += -v;
}

/**
 *  Scales this vector by rhs and returns the result for chaining.
 */
template <uint32_t DIM> Vector<DIM>& Vector<DIM>::operator*=(const double& rhs)
{
    return *this = scale(rhs);
}

/**
 *  Scales this vector by 1.0 / rhs and returns the result for chaining.
 */
template <uint32_t DIM> Vector<DIM>& Vector<DIM>::operator/=(const double& rhs)
{
    return *this *= (1.0 / rhs);
}

/**
 *  Scales a copy of this vector by rhs and returns the result.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::operator*(const double& rhs) const
{
    return scale(rhs);
}

/**
 *  Scales a copy of this vector by 1.0 / rhs and returns the result.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::operator/(const double& rhs) const
{
    return scale(1.0 / rhs);
}

/**
 *  Returns the dot (inner) product of this vector and rhs.
 */
template <uint32_t DIM> double Vector<DIM>::operator*(const Vector<DIM>& rhs) const
{
    return dot(rhs);
}

/**
 *  Returns the cross product of this and rhs if called on a 3D vector.
 *  throws an std::domain_error otherwise.
 */
template <uint32_t DIM> const Vector<DIM> Vector<DIM>::operator^(const Vector<DIM>& v) const
{
    return cross(v);
}

template <uint32_t DIM> double* Vector<DIM>::begin()
{
    return data;
}

template <uint32_t DIM> const double* Vector<DIM>::begin() const
{
    return data;
}

template <uint32_t DIM> double* Vector<DIM>::end()
{
    return data + DIM;
}

template <uint32_t DIM> const double* Vector<DIM>::end() const
{
    return data + DIM;
}

/**
 *  Returns the result of scaling a copy of v by scale. This free function
 *  guarantees that vector scaling is commutative.
 */
template <uint32_t DIM> const Vector<DIM> operator*(const double& scale, const Vector<DIM>& v)
{
    return v * scale;
}

#endif // VECTOR_CPP
