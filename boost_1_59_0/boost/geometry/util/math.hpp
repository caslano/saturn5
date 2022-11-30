// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adeel Ahmad, as part of Google Summer of Code 2018 program
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_MATH_HPP
#define BOOST_GEOMETRY_UTIL_MATH_HPP

#include <cmath>
#include <limits>
#include <type_traits>

#include <boost/core/ignore_unused.hpp>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
//#include <boost/math/special_functions/round.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

namespace math
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename T>
inline T const& greatest(T const& v1, T const& v2)
{
    return (std::max)(v1, v2);
}

template <typename T>
inline T const& greatest(T const& v1, T const& v2, T const& v3)
{
    return (std::max)(greatest(v1, v2), v3);
}

template <typename T>
inline T const& greatest(T const& v1, T const& v2, T const& v3, T const& v4)
{
    return (std::max)(greatest(v1, v2, v3), v4);
}

template <typename T>
inline T const& greatest(T const& v1, T const& v2, T const& v3, T const& v4, T const& v5)
{
    return (std::max)(greatest(v1, v2, v3, v4), v5);
}


template <typename T>
inline T bounded(T const& v, T const& lower, T const& upper)
{
    return (std::min)((std::max)(v, lower), upper);
}

template <typename T>
inline T bounded(T const& v, T const& lower)
{
    return (std::max)(v, lower);
}


template <typename T,
          bool IsFloatingPoint = std::is_floating_point<T>::value>
struct abs
{
    static inline T apply(T const& value)
    {
        T const zero = T();
        return value < zero ? -value : value;
    }
};

template <typename T>
struct abs<T, true>
{
    static inline T apply(T const& value)
    {
        using ::fabs;
        using std::fabs; // for long double

        return fabs(value);
    }
};


struct equals_default_policy
{
    template <typename T>
    static inline T apply(T const& a, T const& b)
    {
        // See http://www.parashift.com/c++-faq-lite/newbie.html#faq-29.17
        return greatest(abs<T>::apply(a), abs<T>::apply(b), T(1));
    }
};

template <typename T,
          bool IsFloatingPoint = std::is_floating_point<T>::value>
struct equals_factor_policy
{
    equals_factor_policy()
        : factor(1) {}
    explicit equals_factor_policy(T const& v)
        : factor(greatest(abs<T>::apply(v), T(1)))
    {}
    equals_factor_policy(T const& v0, T const& v1, T const& v2, T const& v3)
        : factor(greatest(abs<T>::apply(v0), abs<T>::apply(v1),
                          abs<T>::apply(v2), abs<T>::apply(v3),
                          T(1)))
    {}

    T const& apply(T const&, T const&) const
    {
        return factor;
    }

    template <typename E>
    void multiply_epsilon(E const& multiplier)
    {
        factor *= multiplier;
    }

    T factor;
};

template <typename T>
struct equals_factor_policy<T, false>
{
    equals_factor_policy() {}
    explicit equals_factor_policy(T const&) {}
    equals_factor_policy(T const& , T const& , T const& , T const& ) {}

    static inline T apply(T const&, T const&)
    {
        return T(1);
    }

    void multiply_epsilon(T const& ) {}
};

template <typename Type,
          bool IsFloatingPoint = std::is_floating_point<Type>::value>
struct equals
{
    template <typename Policy>
    static inline bool apply(Type const& a, Type const& b, Policy const&)
    {
        return a == b;
    }
};

template <typename Type>
struct equals<Type, true>
{
    template <typename Policy>
    static inline bool apply(Type const& a, Type const& b, Policy const& policy)
    {
        boost::ignore_unused(policy);

        if (a == b)
        {
            return true;
        }

        if (boost::math::isfinite(a) && boost::math::isfinite(b))
        {
            // If a is INF and b is e.g. 0, the expression below returns true
            // but the values are obviously not equal, hence the condition
            return abs<Type>::apply(a - b)
                <= std::numeric_limits<Type>::epsilon() * policy.apply(a, b);
        }
        else
        {
            return a == b;
        }
    }
};

template <typename T1, typename T2, typename Policy>
inline bool equals_by_policy(T1 const& a, T2 const& b, Policy const& policy)
{
    return detail::equals
        <
            typename select_most_precise<T1, T2>::type
        >::apply(a, b, policy);
}

template <typename Type,
          bool IsFloatingPoint = std::is_floating_point<Type>::value>
struct smaller
{
    static inline bool apply(Type const& a, Type const& b)
    {
        return a < b;
    }
};

template <typename Type>
struct smaller<Type, true>
{
    static inline bool apply(Type const& a, Type const& b)
    {
        if (!(a < b)) // a >= b
        {
            return false;
        }
        
        return ! equals<Type, true>::apply(b, a, equals_default_policy());
    }
};

template <typename Type,
          bool IsFloatingPoint = std::is_floating_point<Type>::value>
struct smaller_or_equals
{
    static inline bool apply(Type const& a, Type const& b)
    {
        return a <= b;
    }
};

template <typename Type>
struct smaller_or_equals<Type, true>
{
    static inline bool apply(Type const& a, Type const& b)
    {
        if (a <= b)
        {
            return true;
        }

        return equals<Type, true>::apply(a, b, equals_default_policy());
    }
};


template <typename Type,
          bool IsFloatingPoint = std::is_floating_point<Type>::value>
struct equals_with_epsilon
    : public equals<Type, IsFloatingPoint>
{};

template
<
    typename T,
    bool IsFundemantal = std::is_fundamental<T>::value /* false */
>
struct square_root
{
    typedef T return_type;

    static inline T apply(T const& value)
    {
        // for non-fundamental number types assume that sqrt is
        // defined either:
        // 1) at T's scope, or
        // 2) at global scope, or
        // 3) in namespace std
        using ::sqrt;
        using std::sqrt;

        return sqrt(value);
    }
};

template <typename FundamentalFP>
struct square_root_for_fundamental_fp
{
    typedef FundamentalFP return_type;

    static inline FundamentalFP apply(FundamentalFP const& value)
    {
#ifdef BOOST_GEOMETRY_SQRT_CHECK_FINITENESS
        // This is a workaround for some 32-bit platforms.
        // For some of those platforms it has been reported that
        // std::sqrt(nan) and/or std::sqrt(-nan) returns a finite value.
        // For those platforms we need to define the macro
        // BOOST_GEOMETRY_SQRT_CHECK_FINITENESS so that the argument
        // to std::sqrt is checked appropriately before passed to std::sqrt
        if (boost::math::isfinite(value))
        {
            return std::sqrt(value);
        }
        else if (boost::math::isinf(value) && value < 0)
        {
            return -std::numeric_limits<FundamentalFP>::quiet_NaN();
        }
        return value;
#else
        // for fundamental floating point numbers use std::sqrt
        return std::sqrt(value);
#endif // BOOST_GEOMETRY_SQRT_CHECK_FINITENESS
    }
};

template <>
struct square_root<float, true>
    : square_root_for_fundamental_fp<float>
{
};

template <>
struct square_root<double, true>
    : square_root_for_fundamental_fp<double>
{
};

template <>
struct square_root<long double, true>
    : square_root_for_fundamental_fp<long double>
{
};

template <typename T>
struct square_root<T, true>
{
    typedef double return_type;

    static inline double apply(T const& value)
    {
        // for all other fundamental number types use also std::sqrt
        //
        // Note: in C++98 the only other possibility is double;
        //       in C++11 there are also overloads for integral types;
        //       this specialization works for those as well.
        return square_root_for_fundamental_fp
            <
                double
            >::apply(boost::numeric_cast<double>(value));
    }
};



template
<
    typename T,
    bool IsFundemantal = std::is_fundamental<T>::value /* false */
>
struct modulo
{
    typedef T return_type;

    static inline T apply(T const& value1, T const& value2)
    {
        // for non-fundamental number types assume that a free
        // function mod() is defined either:
        // 1) at T's scope, or
        // 2) at global scope
        return mod(value1, value2);
    }
};

template
<
    typename Fundamental,
    bool IsIntegral = std::is_integral<Fundamental>::value
>
struct modulo_for_fundamental
{
    typedef Fundamental return_type;

    static inline Fundamental apply(Fundamental const& value1,
                                    Fundamental const& value2)
    {
        return value1 % value2;
    }
};

// specialization for floating-point numbers
template <typename Fundamental>
struct modulo_for_fundamental<Fundamental, false>
{
    typedef Fundamental return_type;

    static inline Fundamental apply(Fundamental const& value1,
                                    Fundamental const& value2)
    {
        return std::fmod(value1, value2);
    }
};

// specialization for fundamental number type
template <typename Fundamental>
struct modulo<Fundamental, true>
    : modulo_for_fundamental<Fundamental>
{};



/*!
\brief Short constructs to enable partial specialization for PI, 2*PI
       and PI/2, currently not possible in Math.
*/
template <typename T>
struct define_pi
{
    static inline T apply()
    {
        // Default calls Boost.Math
        return boost::math::constants::pi<T>();
    }
};

template <typename T>
struct define_two_pi
{
    static inline T apply()
    {
        // Default calls Boost.Math
        return boost::math::constants::two_pi<T>();
    }
};

template <typename T>
struct define_half_pi
{
    static inline T apply()
    {
        // Default calls Boost.Math
        return boost::math::constants::half_pi<T>();
    }
};

template <typename T>
struct relaxed_epsilon
{
    static inline T apply(const T& factor)
    {
        return factor * std::numeric_limits<T>::epsilon();
    }
};

// This must be consistent with math::equals.
// By default math::equals() scales the error by epsilon using the greater of
// compared values but here is only one value, though it should work the same way.
// (a-a) <= max(a, a) * EPS       -> 0 <= a*EPS
// (a+da-a) <= max(a+da, a) * EPS -> da <= (a+da)*EPS
template <typename T, bool IsIntegral = std::is_integral<T>::value>
struct scaled_epsilon
{
    static inline T apply(T const& val)
    {
        return (std::max)(abs<T>::apply(val), T(1))
                    * std::numeric_limits<T>::epsilon();
    }

    static inline T apply(T const& val, T const& eps)
    {
        return (std::max)(abs<T>::apply(val), T(1))
                    * eps;
    }
};

template <typename T>
struct scaled_epsilon<T, true>
{
    static inline T apply(T const&)
    {
        return T(0);
    }

    static inline T apply(T const&, T const&)
    {
        return T(0);
    }
};

// ItoF ItoI FtoF
template <typename Result, typename Source,
          bool ResultIsInteger = std::numeric_limits<Result>::is_integer,
          bool SourceIsInteger = std::numeric_limits<Source>::is_integer>
struct rounding_cast
{
    static inline Result apply(Source const& v)
    {
        return boost::numeric_cast<Result>(v);
    }
};

// TtoT
template <typename Source, bool ResultIsInteger, bool SourceIsInteger>
struct rounding_cast<Source, Source, ResultIsInteger, SourceIsInteger>
{
    static inline Source apply(Source const& v)
    {
        return v;
    }
};

// FtoI
template <typename Result, typename Source>
struct rounding_cast<Result, Source, true, false>
{
    static inline Result apply(Source const& v)
    {
        return boost::numeric_cast<Result>(v < Source(0) ?
                                            v - Source(0.5) :
                                            v + Source(0.5));
    }
};

template <typename T, bool IsIntegral = std::is_integral<T>::value>
struct divide
{
    static inline T apply(T const& n, T const& d)
    {
        return n / d;
    }
};

template <typename T>
struct divide<T, true>
{
    static inline T apply(T const& n, T const& d)
    {
        return n == 0 ? 0
          : n < 0
          ? (d < 0 ? (n + (-d + 1) / 2) / d + 1
                   : (n + ( d + 1) / 2) / d - 1  )
          : (d < 0 ? (n - (-d + 1) / 2) / d - 1
                   : (n - ( d + 1) / 2) / d + 1  )
        ;
    }
};

} // namespace detail
#endif


template <typename T>
inline T pi() { return detail::define_pi<T>::apply(); }

template <typename T>
inline T two_pi() { return detail::define_two_pi<T>::apply(); }

template <typename T>
inline T half_pi() { return detail::define_half_pi<T>::apply(); }

template <typename T>
inline T relaxed_epsilon(T const& factor)
{
    return detail::relaxed_epsilon<T>::apply(factor);
}

template <typename T>
inline T scaled_epsilon(T const& value)
{
    return detail::scaled_epsilon<T>::apply(value);
}

template <typename T>
inline T scaled_epsilon(T const& value, T const& eps)
{
    return detail::scaled_epsilon<T>::apply(value, eps);
}

// Maybe replace this by boost equals or so

/*!
    \brief returns true if both arguments are equal.
    \ingroup utility
    \param a first argument
    \param b second argument
    \return true if a == b
    \note If both a and b are of an integral type, comparison is done by ==.
    If one of the types is floating point, comparison is done by abs and
    comparing with epsilon. If one of the types is non-fundamental, it might
    be a high-precision number and comparison is done using the == operator
    of that class.
*/

template <typename T1, typename T2>
inline bool equals(T1 const& a, T2 const& b)
{
    return detail::equals
        <
            typename select_most_precise<T1, T2>::type
        >::apply(a, b, detail::equals_default_policy());
}

template <typename T1, typename T2>
inline bool equals_with_epsilon(T1 const& a, T2 const& b)
{
    return detail::equals_with_epsilon
        <
            typename select_most_precise<T1, T2>::type
        >::apply(a, b, detail::equals_default_policy());
}

template <typename T1, typename T2>
inline bool smaller(T1 const& a, T2 const& b)
{
    return detail::smaller
        <
            typename select_most_precise<T1, T2>::type
        >::apply(a, b);
}

template <typename T1, typename T2>
inline bool larger(T1 const& a, T2 const& b)
{
    return detail::smaller
        <
            typename select_most_precise<T1, T2>::type
        >::apply(b, a);
}

template <typename T1, typename T2>
inline bool smaller_or_equals(T1 const& a, T2 const& b)
{
    return detail::smaller_or_equals
        <
            typename select_most_precise<T1, T2>::type
        >::apply(a, b);
}

template <typename T1, typename T2>
inline bool larger_or_equals(T1 const& a, T2 const& b)
{
    return detail::smaller_or_equals
        <
            typename select_most_precise<T1, T2>::type
        >::apply(b, a);
}


template <typename T>
inline T d2r()
{
    static T const conversion_coefficient = geometry::math::pi<T>() / T(180.0);
    return conversion_coefficient;
}

template <typename T>
inline T r2d()
{
    static T const conversion_coefficient = T(180.0) / geometry::math::pi<T>();
    return conversion_coefficient;
}


#ifndef DOXYGEN_NO_DETAIL
namespace detail {

template <typename DegreeOrRadian>
struct as_radian
{
    template <typename T>
    static inline T apply(T const& value)
    {
        return value;
    }
};

template <>
struct as_radian<degree>
{
    template <typename T>
    static inline T apply(T const& value)
    {
        return value * d2r<T>();
    }
};

template <typename DegreeOrRadian>
struct from_radian
{
    template <typename T>
    static inline T apply(T const& value)
    {
        return value;
    }
};

template <>
struct from_radian<degree>
{
    template <typename T>
    static inline T apply(T const& value)
    {
        return value * r2d<T>();
    }
};

} // namespace detail
#endif

template <typename DegreeOrRadian, typename T>
inline T as_radian(T const& value)
{
    return detail::as_radian<DegreeOrRadian>::apply(value);
}

template <typename DegreeOrRadian, typename T>
inline T from_radian(T const& value)
{
    return detail::from_radian<DegreeOrRadian>::apply(value);
}


/*!
    \brief Calculates the haversine of an angle
    \ingroup utility
    \note See http://en.wikipedia.org/wiki/Haversine_formula
    haversin(alpha) = sin2(alpha/2)
*/
template <typename T>
inline T hav(T const& theta)
{
    T const half = T(0.5);
    T const sn = sin(half * theta);
    return sn * sn;
}

/*!
\brief Short utility to return the square
\ingroup utility
\param value Value to calculate the square from
\return The squared value
*/
template <typename T>
inline T sqr(T const& value)
{
    return value * value;
}

/*!
\brief Short utility to return the square root
\ingroup utility
\param value Value to calculate the square root from
\return The square root value
*/
template <typename T>
inline typename detail::square_root<T>::return_type
sqrt(T const& value)
{
    return detail::square_root
        <
            T, std::is_fundamental<T>::value
        >::apply(value);
}

/*!
\brief Short utility to return the modulo of two values
\ingroup utility
\param value1 First value
\param value2 Second value
\return The result of the modulo operation on the (ordered) pair
(value1, value2)
*/
template <typename T>
inline typename detail::modulo<T>::return_type
mod(T const& value1, T const& value2)
{
    return detail::modulo
        <
            T, std::is_fundamental<T>::value
        >::apply(value1, value2);
}

/*!
\brief Short utility to workaround gcc/clang problem that abs is converting to integer
       and that older versions of MSVC does not support abs of long long...
\ingroup utility
*/
template<typename T>
inline T abs(T const& value)
{
    return detail::abs<T>::apply(value);
}

/*!
\brief Short utility to calculate the sign of a number: -1 (negative), 0 (zero), 1 (positive)
\ingroup utility
*/
template <typename T>
inline int sign(T const& value)
{
    T const zero = T();
    return value > zero ? 1 : value < zero ? -1 : 0;
}

/*!
\brief Short utility to cast a value possibly rounding it to the nearest
       integral value.
\ingroup utility
\note If the source T is NOT an integral type and Result is an integral type
      the value is rounded towards the closest integral value. Otherwise it's
      casted without rounding.
*/
template <typename Result, typename T>
inline Result rounding_cast(T const& v)
{
    return detail::rounding_cast<Result, T>::apply(v);
}

/*
\brief Short utility to divide. If the division is integer, it rounds the division
       to the nearest value, without using floating point calculations
\ingroup utility
*/
template <typename T>
inline T divide(T const& n, T const& d)
{
    return detail::divide<T>::apply(n, d);
}

/*!
\brief Evaluate the sine and cosine function with the argument in degrees
\note The results obey exactly the elementary properties of the trigonometric
      functions, e.g., sin 9&deg; = cos 81&deg; = &minus; sin 123456789&deg;.
      If x = &minus;0, then \e sinx = &minus;0; this is the only case where
      &minus;0 is returned.
*/
template<typename T>
inline void sin_cos_degrees(T const& x,
                            T & sinx,
                            T & cosx)
{
    // In order to minimize round-off errors, this function exactly reduces
    // the argument to the range [-45, 45] before converting it to radians.
    T remainder; int quotient;

    remainder = math::mod(x, T(360));
    quotient = floor(remainder / 90 + T(0.5));
    remainder -= 90 * quotient;

    // Convert to radians.
    remainder *= d2r<T>();

    T s = sin(remainder), c = cos(remainder);

    switch (unsigned(quotient) & 3U)
    {
        case 0U: sinx =  s; cosx =  c; break;
        case 1U: sinx =  c; cosx = -s; break;
        case 2U: sinx = -s; cosx = -c; break;
        default: sinx = -c; cosx =  s; break; // case 3U
    }

    // Set sign of 0 results. -0 only produced for sin(-0).
    if (x != 0)
    {
        sinx += T(0); cosx += T(0);
    }
}

/*!
\brief Round off a given angle
*/
template<typename T>
inline T round_angle(T const& x) {
    static const T z = 1/T(16);

    if (x == 0)
    {
        return 0;
    }

    T y = math::abs(x);

    // z - (z - y) must not be simplified to y.
    y = y < z ? z - (z - y) : y;

    return x < 0 ? -y : y;
}

/*!
\brief Evaluate the polynomial in x using Horner's method.
*/
// TODO: adl1995 - Merge these functions with formulas/area_formulas.hpp
// i.e. place them in one file.
template <typename NT, typename IteratorType>
inline NT horner_evaluate(NT const& x,
                          IteratorType begin,
                          IteratorType end)
{
    NT result(0);
    IteratorType it = end;
    do
    {
        result = result * x + *--it;
    }
    while (it != begin);
    return result;
}

/*!
\brief Evaluate the polynomial.
*/
template<typename IteratorType, typename CT>
inline CT polyval(IteratorType first,
                  IteratorType last,
                  CT const& eps)
{
    int N = std::distance(first, last) - 1;
    int index = 0;

    CT y = N < 0 ? 0 : *(first + (index++));

    while (--N >= 0)
    {
        y = y * eps + *(first + (index++));
    }

    return y;
}

/*
\brief Short utility to calculate the power
\ingroup utility
*/
template <typename T1, typename T2>
inline T1 pow(T1 const& a, T2 const& b)
{
    using std::pow;
    return pow(a, b);
}

} // namespace math


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_MATH_HPP

/* math.hpp
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
*/