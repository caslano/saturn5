//  (C) Copyright Jeremy William Murphy 2016.
//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_POLYNOMIAL_GCD_HPP
#define BOOST_MATH_TOOLS_POLYNOMIAL_GCD_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <algorithm>
#include <type_traits>
#include <boost/math/tools/is_standalone.hpp>
#include <boost/math/tools/polynomial.hpp>

#ifndef BOOST_MATH_STANDALONE
#include <boost/integer/common_factor_rt.hpp>

#else
#include <numeric>
#include <utility>
#include <iterator>
#include <type_traits>
#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/config.hpp>

namespace boost { namespace integer {

namespace gcd_detail {

template <typename EuclideanDomain>
inline EuclideanDomain Euclid_gcd(EuclideanDomain a, EuclideanDomain b) noexcept(std::is_arithmetic<EuclideanDomain>::value)
{
    using std::swap;
    while (b != EuclideanDomain(0))
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

enum method_type
{
    method_euclid = 0,
    method_binary = 1,
    method_mixed = 2
};

} // gcd_detail

template <typename Iter, typename T = typename std::iterator_traits<Iter>::value_type>
std::pair<T, Iter> gcd_range(Iter first, Iter last) noexcept(std::is_arithmetic<T>::value)
{
    BOOST_MATH_ASSERT(first != last);

    T d = *first;
    ++first;
    while (d != T(1) && first != last)
    {
        #ifdef BOOST_MATH_HAS_CXX17_NUMERIC
        d = std::gcd(d, *first);
        #else
        d = gcd_detail::Euclid_gcd(d, *first);
        #endif
        ++first;
    }
    return std::make_pair(d, first);
}

}} // namespace boost::integer
#endif

namespace boost{

   namespace integer {

      namespace gcd_detail {

         template <class T>
         struct gcd_traits;

         template <class T>
         struct gcd_traits<boost::math::tools::polynomial<T> >
         {
            inline static const boost::math::tools::polynomial<T>& abs(const boost::math::tools::polynomial<T>& val) { return val; }

            static const method_type method = method_euclid;
         };

      }
}

namespace math{ namespace tools{

/* From Knuth, 4.6.1:
*
* We may write any nonzero polynomial u(x) from R[x] where R is a UFD as
*
*      u(x) = cont(u) . pp(u(x))
*
* where cont(u), the content of u, is an element of S, and pp(u(x)), the primitive
* part of u(x), is a primitive polynomial over S.
* When u(x) = 0, it is convenient to define cont(u) = pp(u(x)) = O.
*/

template <class T>
T content(polynomial<T> const &x)
{
    return x ? boost::integer::gcd_range(x.data().begin(), x.data().end()).first : T(0);
}

// Knuth, 4.6.1
template <class T>
polynomial<T> primitive_part(polynomial<T> const &x, T const &cont)
{
    return x ? x / cont : polynomial<T>();
}


template <class T>
polynomial<T> primitive_part(polynomial<T> const &x)
{
    return primitive_part(x, content(x));
}


// Trivial but useful convenience function referred to simply as l() in Knuth.
template <class T>
T leading_coefficient(polynomial<T> const &x)
{
    return x ? x.data().back() : T(0);
}


namespace detail
{
    /* Reduce u and v to their primitive parts and return the gcd of their
    * contents. Used in a couple of gcd algorithms.
    */
    template <class T>
    T reduce_to_primitive(polynomial<T> &u, polynomial<T> &v)
    {
        T const u_cont = content(u), v_cont = content(v);
        u /= u_cont;
        v /= v_cont;

        #ifdef BOOST_MATH_HAS_CXX17_NUMERIC
        return std::gcd(u_cont, v_cont);
        #else
        return boost::integer::gcd_detail::Euclid_gcd(u_cont, v_cont);
        #endif
    }
}


/**
* Knuth, The Art of Computer Programming: Volume 2, Third edition, 1998
* Algorithm 4.6.1C: Greatest common divisor over a unique factorization domain.
*
* The subresultant algorithm by George E. Collins [JACM 14 (1967), 128-142],
* later improved by W. S. Brown and J. F. Traub [JACM 18 (1971), 505-514].
*
* Although step C3 keeps the coefficients to a "reasonable" size, they are
* still potentially several binary orders of magnitude larger than the inputs.
* Thus, this algorithm should only be used where T is a multi-precision type.
*
* @tparam   T   Polynomial coefficient type.
* @param    u   First polynomial.
* @param    v   Second polynomial.
* @return       Greatest common divisor of polynomials u and v.
*/
template <class T>
typename std::enable_if< std::numeric_limits<T>::is_integer, polynomial<T> >::type
subresultant_gcd(polynomial<T> u, polynomial<T> v)
{
    using std::swap;
    BOOST_MATH_ASSERT(u || v);

    if (!u)
        return v;
    if (!v)
        return u;

    typedef typename polynomial<T>::size_type N;

    if (u.degree() < v.degree())
        swap(u, v);

    T const d = detail::reduce_to_primitive(u, v);
    T g = 1, h = 1;
    polynomial<T> r;
    while (true)
    {
        BOOST_MATH_ASSERT(u.degree() >= v.degree());
        // Pseudo-division.
        r = u % v;
        if (!r)
            return d * primitive_part(v); // Attach the content.
        if (r.degree() == 0)
            return d * polynomial<T>(T(1)); // The content is the result.
        N const delta = u.degree() - v.degree();
        // Adjust remainder.
        u = v;
        v = r / (g * detail::integer_power(h, delta));
        g = leading_coefficient(u);
        T const tmp = detail::integer_power(g, delta);
        if (delta <= N(1))
            h = tmp * detail::integer_power(h, N(1) - delta);
        else
            h = tmp / detail::integer_power(h, delta - N(1));
    }
}


/**
 * @brief GCD for polynomials with unbounded multi-precision integral coefficients.
 *
 * The multi-precision constraint is enforced via numeric_limits.
 *
 * Note that intermediate terms in the evaluation can grow arbitrarily large, hence the need for
 * unbounded integers, otherwise numeric loverflow would break the algorithm.
 *
 * @tparam  T   A multi-precision integral type.
 */
template <typename T>
typename std::enable_if<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_bounded, polynomial<T> >::type
gcd(polynomial<T> const &u, polynomial<T> const &v)
{
    return subresultant_gcd(u, v);
}
// GCD over bounded integers is not currently allowed:
template <typename T>
typename std::enable_if<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_bounded, polynomial<T> >::type
gcd(polynomial<T> const &u, polynomial<T> const &v)
{
   static_assert(sizeof(v) == 0, "GCD on polynomials of bounded integers is disallowed due to the excessive growth in the size of intermediate terms.");
   return subresultant_gcd(u, v);
}
// GCD over polynomials of floats can go via the Euclid algorithm:
template <typename T>
typename std::enable_if<!std::numeric_limits<T>::is_integer && (std::numeric_limits<T>::min_exponent != std::numeric_limits<T>::max_exponent) && !std::numeric_limits<T>::is_exact, polynomial<T> >::type
gcd(polynomial<T> const &u, polynomial<T> const &v)
{
    return boost::integer::gcd_detail::Euclid_gcd(u, v);
}

}
//
// Using declaration so we overload the default implementation in this namespace:
//
using boost::math::tools::gcd;

}

namespace integer
{
   //
   // Using declaration so we overload the default implementation in this namespace:
   //
   using boost::math::tools::gcd;
}

} // namespace boost::math::tools

#endif

/* polynomial_gcd.hpp
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
*/