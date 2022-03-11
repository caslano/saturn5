// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2015, 2018, 2019.
// Modifications copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Adeel Ahmad, as part of Google Summer of Code 2018 program

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_MATH_HPP
#define BOOST_GEOMETRY_UTIL_MATH_HPP

#include <cmath>
#include <limits>

#include <boost/core/ignore_unused.hpp>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
//#include <boost/math/special_functions/round.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>

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
          bool IsFloatingPoint = boost::is_floating_point<T>::value>
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
          bool IsFloatingPoint = boost::is_floating_point<T>::value>
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
};

template <typename Type,
          bool IsFloatingPoint = boost::is_floating_point<Type>::value>
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
          bool IsFloatingPoint = boost::is_floating_point<Type>::value>
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
          bool IsFloatingPoint = boost::is_floating_point<Type>::value>
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
          bool IsFloatingPoint = boost::is_floating_point<Type>::value>
struct equals_with_epsilon
    : public equals<Type, IsFloatingPoint>
{};

template
<
    typename T,
    bool IsFundemantal = boost::is_fundamental<T>::value /* false */
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
    bool IsFundemantal = boost::is_fundamental<T>::value /* false */
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
    bool IsIntegral = boost::is_integral<Fundamental>::value
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
template <typename T, bool IsIntegral = boost::is_integral<T>::value>
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
            T, boost::is_fundamental<T>::value
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
            T, boost::is_fundamental<T>::value
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
\brief The error-free sum of two numbers.
*/
template<typename T>
inline T sum_error(T const& u, T const& v, T& t)
{
    volatile T s = u + v;
    volatile T up = s - v;
    volatile T vpp = s - up;

    up -= u;
    vpp -= v;
    t = -(up + vpp);

    return s;
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