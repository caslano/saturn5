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

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>
#ifdef BOOST_NO_CXX11_LAMBDAS
#include <boost/lambda/lambda.hpp>
#endif
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/math/tools/detail/is_const_iterable.hpp>

#include <vector>
#include <ostream>
#include <algorithm>
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

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

   BOOST_ASSERT(n - 2 * r == m);

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
BOOST_DEDUCED_TYPENAME disable_if_c<std::numeric_limits<T>::is_integer, void >::type
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
BOOST_DEDUCED_TYPENAME enable_if_c<std::numeric_limits<T>::is_integer, void >::type
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
    BOOST_ASSERT(v.size() <= u.size());
    BOOST_ASSERT(v);
    BOOST_ASSERT(u);

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
    BOOST_ASSERT(divisor);
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

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   polynomial(std::vector<T>&& p) : m_data(std::move(p))
   {
      normalize();
   }
#endif

   template <class U>
   explicit polynomial(const U& point, typename boost::enable_if<boost::is_convertible<U, T> >::type* = 0)
   {
       if (point != U(0))
          m_data.push_back(point);
   }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   // move:
   polynomial(polynomial&& p) BOOST_NOEXCEPT
      : m_data(std::move(p.m_data)) { }
#endif

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
    template <class Range>
    explicit polynomial(const Range& r, typename boost::enable_if<boost::math::tools::detail::is_const_iterable<Range> >::type* = 0) 
       : polynomial(r.begin(), r.end()) 
    {
    }
#endif
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST) && !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40500)
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
#endif


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

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   polynomial<T> prime() const
   {
#ifdef BOOST_MSVC
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
#ifdef BOOST_MSVC
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
   polynomial& operator =(polynomial&& p) BOOST_NOEXCEPT
   {
       m_data = std::move(p.m_data);
       return *this;
   }
#endif
   polynomial& operator =(const polynomial& p)
   {
       m_data = p.m_data;
       return *this;
   }

   template <class U>
   typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial&>::type operator +=(const U& value)
   {
       addition(value);
       normalize();
       return *this;
   }

   template <class U>
   typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial&>::type operator -=(const U& value)
   {
       subtraction(value);
       normalize();
       return *this;
   }

   template <class U>
   typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial&>::type operator *=(const U& value)
   {
      multiplication(value);
      normalize();
      return *this;
   }

   template <class U>
   typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial&>::type operator /=(const U& value)
   {
       division(value);
       normalize();
       return *this;
   }

   template <class U>
   typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial&>::type operator %=(const U& /*value*/)
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
       BOOST_ASSERT(n <= m_data.size());
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
#ifdef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
   typedef bool (polynomial::*unmentionable_type)() const;

   BOOST_FORCEINLINE operator unmentionable_type() const
   {
       return is_zero() ? false : &polynomial::is_zero;
   }
#else
   BOOST_FORCEINLINE explicit operator bool() const
   {
       return !m_data.empty();
   }
#endif

   // Fast way to set a polynomial to zero.
   void set_zero()
   {
       m_data.clear();
   }

    /** Remove zero coefficients 'from the top', that is for which there are no
    *        non-zero coefficients of higher degree. */
   void normalize()
   {
#ifndef BOOST_NO_CXX11_LAMBDAS
      m_data.erase(std::find_if(m_data.rbegin(), m_data.rend(), [](const T& x)->bool { return x != T(0); }).base(), m_data.end());
#else
       using namespace boost::lambda;
       m_data.erase(std::find_if(m_data.rbegin(), m_data.rend(), _1 != T(0)).base(), m_data.end());
#endif
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
#ifndef BOOST_NO_CXX11_LAMBDAS
       std::transform(m_data.begin(), m_data.end(), m_data.begin(), [&](const T& x)->T { return x * value; });
#else
        using namespace boost::lambda;
        std::transform(m_data.begin(), m_data.end(), m_data.begin(), ret<T>(_1 * value));
#endif
        return *this;
    }

    template <class U>
    polynomial& division(const U& value)
    {
#ifndef BOOST_NO_CXX11_LAMBDAS
       std::transform(m_data.begin(), m_data.end(), m_data.begin(), [&](const T& x)->T { return x / value; });
#else
        using namespace boost::lambda;
        std::transform(m_data.begin(), m_data.end(), m_data.begin(), ret<T>(_1 / value));
#endif
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class T>
inline polynomial<T> operator + (polynomial<T>&& a, const polynomial<T>& b)
{
   a += b;
   return a;
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
#endif

template <class T>
inline polynomial<T> operator - (const polynomial<T>& a, const polynomial<T>& b)
{
   polynomial<T> result(a);
   result -= b;
   return result;
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
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
#endif

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
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator + (polynomial<T> a, const U& b)
{
   a += b;
   return a;
}

template <class T, class U>
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator - (polynomial<T> a, const U& b)
{
   a -= b;
   return a;
}

template <class T, class U>
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator * (polynomial<T> a, const U& b)
{
   a *= b;
   return a;
}

template <class T, class U>
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator / (polynomial<T> a, const U& b)
{
   a /= b;
   return a;
}

template <class T, class U>
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator % (const polynomial<T>&, const U&)
{
   // Since we can always divide by a scalar, result is always an empty polynomial:
   return polynomial<T>();
}

template <class U, class T>
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator + (const U& a, polynomial<T> b)
{
   b += a;
   return b;
}

template <class U, class T>
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator - (const U& a, polynomial<T> b)
{
   b -= a;
   return -b;
}

template <class U, class T>
inline typename boost::enable_if_c<boost::is_constructible<T, U>::value, polynomial<T> >::type operator * (const U& a, polynomial<T> b)
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