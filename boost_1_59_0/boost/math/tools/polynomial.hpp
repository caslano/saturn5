//  (C) Copyright John Maddock 2006.
//  (C) Copyright Jeremy William Murphy 2015.


//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_POLYNOMIAL_HPP
#define BOOST_MATH_TOOLS_POLYNOMIAL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/tools/detail/is_const_iterable.hpp>

#include <vector>
#include <ostream>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <iterator>

namespace boost{ namespace math{ namespace tools{

template <class T>
T chebyshev_coefficient(unsigned n, unsigned m)
{
   BOOST_MATH_STD_USING
   if(m > n)
      return 0;
   if((n & 1) != (m & 1))
      return 0;
   if(n == 0)
      return 1;
   T result = T(n) / 2;
   unsigned r = n - m;
   r /= 2;

   BOOST_MATH_ASSERT(n - 2 * r == m);

   if(r & 1)
      result = -result;
   result /= n - r;
   result *= boost::math::binomial_coefficient<T>(n - r, r);
   result *= ldexp(1.0f, m);
   return result;
}

template <class Seq>
Seq polynomial_to_chebyshev(const Seq& s)
{
   // Converts a Polynomial into Chebyshev form:
   typedef typename Seq::value_type value_type;
   typedef typename Seq::difference_type difference_type;
   Seq result(s);
   difference_type order = s.size() - 1;
   difference_type even_order = order & 1 ? order - 1 : order;
   difference_type odd_order = order & 1 ? order : order - 1;

   for(difference_type i = even_order; i >= 0; i -= 2)
   {
      value_type val = s[i];
      for(difference_type k = even_order; k > i; k -= 2)
      {
         val -= result[k] * chebyshev_coefficient<value_type>(static_cast<unsigned>(k), static_cast<unsigned>(i));
      }
      val /= chebyshev_coefficient<value_type>(static_cast<unsigned>(i), static_cast<unsigned>(i));
      result[i] = val;
   }
   result[0] *= 2;

   for(difference_type i = odd_order; i >= 0; i -= 2)
   {
      value_type val = s[i];
      for(difference_type k = odd_order; k > i; k -= 2)
      {
         val -= result[k] * chebyshev_coefficient<value_type>(static_cast<unsigned>(k), static_cast<unsigned>(i));
      }
      val /= chebyshev_coefficient<value_type>(static_cast<unsigned>(i), static_cast<unsigned>(i));
      result[i] = val;
   }
   return result;
}

template <class Seq, class T>
T evaluate_chebyshev(const Seq& a, const T& x)
{
   // Clenshaw's formula:
   typedef typename Seq::difference_type difference_type;
   T yk2 = 0;
   T yk1 = 0;
   T yk = 0;
   for(difference_type i = a.size() - 1; i >= 1; --i)
   {
      yk2 = yk1;
      yk1 = yk;
      yk = 2 * x * yk1 - yk2 + a[i];
   }
   return a[0] / 2 + yk * x - yk1;
}


template <typename T>
class polynomial;

namespace detail {

/**
* Knuth, The Art of Computer Programming: Volume 2, Third edition, 1998
* Chapter 4.6.1, Algorithm D: Division of polynomials over a field.
*
* @tparam  T   Coefficient type, must be not be an integer.
*
* Template-parameter T actually must be a field but we don't currently have that
* subtlety of distinction.
*/
template <typename T, typename N>
typename std::enable_if<!std::numeric_limits<T>::is_integer, void >::type
division_impl(polynomial<T> &q, polynomial<T> &u, const polynomial<T>& v, N n, N k)
{
    q[k] = u[n + k] / v[n];
    for (N j = n + k; j > k;)
    {
        j--;
        u[j] -= q[k] * v[j - k];
    }
}

template <class T, class N>
T integer_power(T t, N n)
{
   switch(n)
   {
   case 0:
      return static_cast<T>(1u);
   case 1:
      return t;
   case 2:
      return t * t;
   case 3:
      return t * t * t;
   }
   T result = integer_power(t, n / 2);
   result *= result;
   if(n & 1)
      result *= t;
   return result;
}


/**
* Knuth, The Art of Computer Programming: Volume 2, Third edition, 1998
* Chapter 4.6.1, Algorithm R: Pseudo-division of polynomials.
*
* @tparam  T   Coefficient type, must be an integer.
*
* Template-parameter T actually must be a unique factorization domain but we
* don't currently have that subtlety of distinction.
*/
template <typename T, typename N>
typename std::enable_if<std::numeric_limits<T>::is_integer, void >::type
division_impl(polynomial<T> &q, polynomial<T> &u, const polynomial<T>& v, N n, N k)
{
    q[k] = u[n + k] * integer_power(v[n], k);
    for (N j = n + k; j > 0;)
    {
        j--;
        u[j] = v[n] * u[j] - (j < k ? T(0) : u[n + k] * v[j - k]);
    }
}


/**
 * Knuth, The Art of Computer Programming: Volume 2, Third edition, 1998
 * Chapter 4.6.1, Algorithm D and R: Main loop.
 *
 * @param   u   Dividend.
 * @param   v   Divisor.
 */
template <typename T>
std::pair< polynomial<T>, polynomial<T> >
division(polynomial<T> u, const polynomial<T>& v)
{
    BOOST_MATH_ASSERT(v.size() <= u.size());
    BOOST_MATH_ASSERT(v);
    BOOST_MATH_ASSERT(u);

    typedef typename polynomial<T>::size_type N;

    N const m = u.size() - 1, n = v.size() - 1;
    N k = m - n;
    polynomial<T> q;
    q.data().resize(m - n + 1);

    do
    {
        division_impl(q, u, v, n, k);
    }
    while (k-- != 0);
    u.data().resize(n);
    u.normalize(); // Occasionally, the remainder is zeroes.
    return std::make_pair(q, u);
}

//
// These structures are the same as the void specializations of the functors of the same name
// in the std lib from C++14 onwards:
//
struct negate
{
   template <class T>
   T operator()(T const &x) const
   {
      return -x;
   }
};

struct plus
{
   template <class T, class U>
   T operator()(T const &x, U const& y) const
   {
      return x + y;
   }
};

struct minus
{
   template <class T, class U>
   T operator()(T const &x, U const& y) const
   {
      return x - y;
   }
};

} // namespace detail

/**
 * Returns the zero element for multiplication of polynomials.
 */
template <class T>
polynomial<T> zero_element(std::multiplies< polynomial<T> >)
{
    return polynomial<T>();
}

template <class T>
polynomial<T> identity_element(std::multiplies< polynomial<T> >)
{
    return polynomial<T>(T(1));
}

/* Calculates a / b and a % b, returning the pair (quotient, remainder) together
 * because the same amount of computation yields both.
 * This function is not defined for division by zero: user beware.
 */
template <typename T>
std::pair< polynomial<T>, polynomial<T> >
quotient_remainder(const polynomial<T>& dividend, const polynomial<T>& divisor)
{
    BOOST_MATH_ASSERT(divisor);
    if (dividend.size() < divisor.size())
        return std::make_pair(polynomial<T>(), dividend);
    return detail::division(dividend, divisor);
}


template <class T>
class polynomial
{
public:
   // typedefs:
   typedef typename std::vector<T>::value_type value_type;
   typedef typename std::vector<T>::size_type size_type;

   // construct:
   polynomial(){}

   template <class U>
   polynomial(const U* data, unsigned order)
      : m_data(data, data + order + 1)
   {
       normalize();
   }

   template <class I>
   polynomial(I first, I last)
      : m_data(first, last)
   {
       normalize();
   }

   template <class I>
   polynomial(I first, unsigned length)
      : m_data(first, std::next(first, length + 1))
   {
       normalize();
   }

   polynomial(std::vector<T>&& p) : m_data(std::move(p))
   {
      normalize();
   }

   template <class U, typename std::enable_if<std::is_convertible<U, T>::value, bool>::type = true>
   explicit polynomial(const U& point)
   {
       if (point != U(0))
          m_data.push_back(point);
   }

   // move:
   polynomial(polynomial&& p) noexcept
      : m_data(std::move(p.m_data)) { }

   // copy:
   polynomial(const polynomial& p)
      : m_data(p.m_data) { }

   template <class U>
   polynomial(const polynomial<U>& p)
   {
      m_data.resize(p.size());
      for(unsigned i = 0; i < p.size(); ++i)
      {
         m_data[i] = boost::math::tools::real_cast<T>(p[i]);
      }
   }
#ifdef BOOST_MATH_HAS_IS_CONST_ITERABLE
    template <class Range, typename std::enable_if<boost::math::tools::detail::is_const_iterable<Range>::value, bool>::type = true>
    explicit polynomial(const Range& r) 
       : polynomial(r.begin(), r.end()) 
    {
    }
#endif
    polynomial(std::initializer_list<T> l) : polynomial(std::begin(l), std::end(l))
    {
    }

    polynomial&
    operator=(std::initializer_list<T> l)
    {
        m_data.assign(std::begin(l), std::end(l));
        normalize();
        return *this;
    }


   // access:
   size_type size() const { return m_data.size(); }
   size_type degree() const
   {
       if (size() == 0)
           throw std::logic_error("degree() is undefined for the zero polynomial.");
       return m_data.size() - 1;
   }
   value_type& operator[](size_type i)
   {
      return m_data[i];
   }
   const value_type& operator[](size_type i) const
   {
      return m_data[i];
   }

   T evaluate(T z) const
   {
      return this->operator()(z);
   }

   T operator()(T z) const
   {
      return m_data.size() > 0 ? boost::math::tools::evaluate_polynomial(&m_data[0], z, m_data.size()) : T(0);
   }
   std::vector<T> chebyshev() const
   {
      return polynomial_to_chebyshev(m_data);
   }

   std::vector<T> const& data() const
   {
       return m_data;
   }

   std::vector<T> & data()
   {
       return m_data;
   }

   polynomial<T> prime() const
   {
#ifdef _MSC_VER
      // Disable int->float conversion warning:
#pragma warning(push)
#pragma warning(disable:4244)
#endif
      if (m_data.size() == 0)
      {
        return polynomial<T>({});
      }

      std::vector<T> p_data(m_data.size() - 1);
      for (size_t i = 0; i < p_data.size(); ++i) {
          p_data[i] = m_data[i+1]*static_cast<T>(i+1);
      }
      return polynomial<T>(std::move(p_data));
#ifdef _MSC_VER
#pragma warning(pop)
#endif
   }

   polynomial<T> integrate() const
   {
      std::vector<T> i_data(m_data.size() + 1);
      // Choose integration constant such that P(0) = 0.
      i_data[0] = T(0);
      for (size_t i = 1; i < i_data.size(); ++i)
      {
          i_data[i] = m_data[i-1]/static_cast<T>(i);
      }
      return polynomial<T>(std::move(i_data));
   }

   // operators:
   polynomial& operator =(polynomial&& p) noexcept
   {
       m_data = std::move(p.m_data);
       return *this;
   }

   polynomial& operator =(const polynomial& p)
   {
       m_data = p.m_data;
       return *this;
   }

   template <class U>
   typename std::enable_if<std::is_constructible<T, U>::value, polynomial&>::type operator +=(const U& value)
   {
       addition(value);
       normalize();
       return *this;
   }

   template <class U>
   typename std::enable_if<std::is_constructible<T, U>::value, polynomial&>::type operator -=(const U& value)
   {
       subtraction(value);
       normalize();
       return *this;
   }

   template <class U>
   typename std::enable_if<std::is_constructible<T, U>::value, polynomial&>::type operator *=(const U& value)
   {
      multiplication(value);
      normalize();
      return *this;
   }

   template <class U>
   typename std::enable_if<std::is_constructible<T, U>::value, polynomial&>::type operator /=(const U& value)
   {
       division(value);
       normalize();
       return *this;
   }

   template <class U>
   typename std::enable_if<std::is_constructible<T, U>::value, polynomial&>::type operator %=(const U& /*value*/)
   {
       // We can always divide by a scalar, so there is no remainder:
       this->set_zero();
       return *this;
   }

   template <class U>
   polynomial& operator +=(const polynomial<U>& value)
   {
      addition(value);
      normalize();
      return *this;
   }

   template <class U>
   polynomial& operator -=(const polynomial<U>& value)
   {
       subtraction(value);
       normalize();
       return *this;
   }

   template <typename U, typename V>
   void multiply(const polynomial<U>& a, const polynomial<V>& b) {
       if (!a || !b)
       {
           this->set_zero();
           return;
       }
       std::vector<T> prod(a.size() + b.size() - 1, T(0));
       for (unsigned i = 0; i < a.size(); ++i)
           for (unsigned j = 0; j < b.size(); ++j)
               prod[i+j] += a.m_data[i] * b.m_data[j];
       m_data.swap(prod);
   }

   template <class U>
   polynomial& operator *=(const polynomial<U>& value)
   {
      this->multiply(*this, value);
      return *this;
   }

   template <typename U>
   polynomial& operator /=(const polynomial<U>& value)
   {
       *this = quotient_remainder(*this, value).first;
       return *this;
   }

   template <typename U>
   polynomial& operator %=(const polynomial<U>& value)
   {
       *this = quotient_remainder(*this, value).second;
       return *this;
   }

   template <typename U>
   polynomial& operator >>=(U const &n)
   {
       BOOST_MATH_ASSERT(n <= m_data.size());
       m_data.erase(m_data.begin(), m_data.begin() + n);
       return *this;
   }

   template <typename U>
   polynomial& operator <<=(U const &n)
   {
       m_data.insert(m_data.begin(), n, static_cast<T>(0));
       normalize();
       return *this;
   }

   // Convenient and efficient query for zero.
   bool is_zero() const
   {
       return m_data.empty();
   }

   // Conversion to bool.
   inline explicit operator bool() const
   {
       return !m_data.empty();
   }

   // Fast way to set a polynomial to zero.
   void set_zero()
   {
       m_data.clear();
   }

    /** Remove zero coefficients 'from the top', that is for which there are no
    *        non-zero coefficients of higher degree. */
   void normalize()
   {
      m_data.erase(std::find_if(m_data.rbegin(), m_data.rend(), [](const T& x)->bool { return x != T(0); }).base(), m_data.end());
   }

private:
    template <class U, class R>
    polynomial& addition(const U& value, R op)
    {
        if(m_data.size() == 0)
            m_data.resize(1, 0);
        m_data[0] = op(m_data[0], value);
        return *this;
    }

    template <class U>
    polynomial& addition(const U& value)
    {
        return addition(value, detail::plus());
    }

    template <class U>
    polynomial& subtraction(const U& value)
    {
        return addition(value, detail::minus());
    }

    template <class U, class R>
    polynomial& addition(const polynomial<U>& value, R op)
    {
        if (m_data.size() < value.size())
            m_data.resize(value.size(), 0);
        for(size_type i = 0; i < value.size(); ++i)
            m_data[i] = op(m_data[i], value[i]);
        return *this;
    }

    template <class U>
    polynomial& addition(const polynomial<U>& value)
    {
        return addition(value, detail::plus());
    }

    template <class U>
    polynomial& subtraction(const polynomial<U>& value)
    {
        return addition(value, detail::minus());
    }

    template <class U>
    polynomial& multiplication(const U& value)
    {
       std::transform(m_data.begin(), m_data.end(), m_data.begin(), [&](const T& x)->T { return x * value; });
       return *this;
    }

    template <class U>
    polynomial& division(const U& value)
    {
       std::transform(m_data.begin(), m_data.end(), m_data.begin(), [&](const T& x)->T { return x / value; });
       return *this;
    }

    std::vector<T> m_data;
};


template <class T>
inline polynomial<T> operator + (const polynomial<T>& a, const polynomial<T>& b)
{
   polynomial<T> result(a);
   result += b;
   return result;
}

template <class T>
inline polynomial<T> operator + (polynomial<T>&& a, const polynomial<T>& b)
{
   a += b;
   return std::move(a);
}
template <class T>
inline polynomial<T> operator + (const polynomial<T>& a, polynomial<T>&& b)
{
   b += a;
   return b;
}
template <class T>
inline polynomial<T> operator + (polynomial<T>&& a, polynomial<T>&& b)
{
   a += b;
   return a;
}

template <class T>
inline polynomial<T> operator - (const polynomial<T>& a, const polynomial<T>& b)
{
   polynomial<T> result(a);
   result -= b;
   return result;
}

template <class T>
inline polynomial<T> operator - (polynomial<T>&& a, const polynomial<T>& b)
{
   a -= b;
   return a;
}
template <class T>
inline polynomial<T> operator - (const polynomial<T>& a, polynomial<T>&& b)
{
   b -= a;
   return -b;
}
template <class T>
inline polynomial<T> operator - (polynomial<T>&& a, polynomial<T>&& b)
{
   a -= b;
   return a;
}

template <class T>
inline polynomial<T> operator * (const polynomial<T>& a, const polynomial<T>& b)
{
   polynomial<T> result;
   result.multiply(a, b);
   return result;
}

template <class T>
inline polynomial<T> operator / (const polynomial<T>& a, const polynomial<T>& b)
{
   return quotient_remainder(a, b).first;
}

template <class T>
inline polynomial<T> operator % (const polynomial<T>& a, const polynomial<T>& b)
{
   return quotient_remainder(a, b).second;
}

template <class T, class U>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator + (polynomial<T> a, const U& b)
{
   a += b;
   return a;
}

template <class T, class U>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator - (polynomial<T> a, const U& b)
{
   a -= b;
   return a;
}

template <class T, class U>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator * (polynomial<T> a, const U& b)
{
   a *= b;
   return a;
}

template <class T, class U>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator / (polynomial<T> a, const U& b)
{
   a /= b;
   return a;
}

template <class T, class U>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator % (const polynomial<T>&, const U&)
{
   // Since we can always divide by a scalar, result is always an empty polynomial:
   return polynomial<T>();
}

template <class U, class T>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator + (const U& a, polynomial<T> b)
{
   b += a;
   return b;
}

template <class U, class T>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator - (const U& a, polynomial<T> b)
{
   b -= a;
   return -b;
}

template <class U, class T>
inline typename std::enable_if<std::is_constructible<T, U>::value, polynomial<T> >::type operator * (const U& a, polynomial<T> b)
{
   b *= a;
   return b;
}

template <class T>
bool operator == (const polynomial<T> &a, const polynomial<T> &b)
{
    return a.data() == b.data();
}

template <class T>
bool operator != (const polynomial<T> &a, const polynomial<T> &b)
{
    return a.data() != b.data();
}

template <typename T, typename U>
polynomial<T> operator >> (polynomial<T> a, const U& b)
{
    a >>= b;
    return a;
}

template <typename T, typename U>
polynomial<T> operator << (polynomial<T> a, const U& b)
{
    a <<= b;
    return a;
}

// Unary minus (negate).
template <class T>
polynomial<T> operator - (polynomial<T> a)
{
    std::transform(a.data().begin(), a.data().end(), a.data().begin(), detail::negate());
    return a;
}

template <class T>
bool odd(polynomial<T> const &a)
{
    return a.size() > 0 && a[0] != static_cast<T>(0);
}

template <class T>
bool even(polynomial<T> const &a)
{
    return !odd(a);
}

template <class T>
polynomial<T> pow(polynomial<T> base, int exp)
{
    if (exp < 0)
        return policies::raise_domain_error(
                "boost::math::tools::pow<%1%>",
                "Negative powers are not supported for polynomials.",
                base, policies::policy<>());
        // if the policy is ignore_error or errno_on_error, raise_domain_error
        // will return std::numeric_limits<polynomial<T>>::quiet_NaN(), which
        // defaults to polynomial<T>(), which is the zero polynomial
    polynomial<T> result(T(1));
    if (exp & 1)
        result = base;
    /* "Exponentiation by squaring" */
    while (exp >>= 1)
    {
        base *= base;
        if (exp & 1)
            result *= base;
    }
    return result;
}

template <class charT, class traits, class T>
inline std::basic_ostream<charT, traits>& operator << (std::basic_ostream<charT, traits>& os, const polynomial<T>& poly)
{
   os << "{ ";
   for(unsigned i = 0; i < poly.size(); ++i)
   {
      if(i) os << ", ";
      os << poly[i];
   }
   os << " }";
   return os;
}

} // namespace tools
} // namespace math
} // namespace boost

//
// Polynomial specific overload of gcd algorithm:
//
#include <boost/math/tools/polynomial_gcd.hpp>

#endif // BOOST_MATH_TOOLS_POLYNOMIAL_HPP

/* polynomial.hpp
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
*/