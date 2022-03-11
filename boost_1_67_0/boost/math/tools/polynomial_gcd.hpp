//  (C) Copyright Jeremy William Murphy 2016.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_POLYNOMIAL_GCD_HPP
#define BOOST_MATH_TOOLS_POLYNOMIAL_GCD_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/polynomial.hpp>
#include <boost/integer/common_factor_rt.hpp>
#include <boost/type_traits/is_pod.hpp>


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
        using boost::integer::gcd;
        T const u_cont = content(u), v_cont = content(v);
        u /= u_cont;
        v /= v_cont;
        return gcd(u_cont, v_cont);
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
typename enable_if_c< std::numeric_limits<T>::is_integer, polynomial<T> >::type
subresultant_gcd(polynomial<T> u, polynomial<T> v)
{
    using std::swap;
    BOOST_ASSERT(u || v);

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
        BOOST_ASSERT(u.degree() >= v.degree());
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
typename enable_if_c<std::numeric_limits<T>::is_integer && !std::numeric_limits<T>::is_bounded, polynomial<T> >::type
gcd(polynomial<T> const &u, polynomial<T> const &v)
{
    return subresultant_gcd(u, v);
}
// GCD over bounded integers is not currently allowed:
template <typename T>
typename enable_if_c<std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_bounded, polynomial<T> >::type
gcd(polynomial<T> const &u, polynomial<T> const &v)
{
   BOOST_STATIC_ASSERT_MSG(sizeof(v) == 0, "GCD on polynomials of bounded integers is disallowed due to the excessive growth in the size of intermediate terms.");
   return subresultant_gcd(u, v);
}
// GCD over polynomials of floats can go via the Euclid algorithm:
template <typename T>
typename enable_if_c<!std::numeric_limits<T>::is_integer && (std::numeric_limits<T>::min_exponent != std::numeric_limits<T>::max_exponent) && !std::numeric_limits<T>::is_exact, polynomial<T> >::type
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