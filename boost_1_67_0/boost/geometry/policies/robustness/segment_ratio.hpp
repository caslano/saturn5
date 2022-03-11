// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016.
// Modifications copyright (c) 2016 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_HPP

#include <boost/config.hpp>
#include <boost/rational.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>

namespace boost { namespace geometry
{


namespace detail { namespace segment_ratio
{

template
<
    typename Type,
    bool IsIntegral = boost::is_integral<Type>::type::value
>
struct less {};

template <typename Type>
struct less<Type, true>
{
    template <typename Ratio>
    static inline bool apply(Ratio const& lhs, Ratio const& rhs)
    {
        return boost::rational<Type>(lhs.numerator(), lhs.denominator())
             < boost::rational<Type>(rhs.numerator(), rhs.denominator());
    }
};

template <typename Type>
struct less<Type, false>
{
    template <typename Ratio>
    static inline bool apply(Ratio const& lhs, Ratio const& rhs)
    {
        BOOST_GEOMETRY_ASSERT(lhs.denominator() != 0);
        BOOST_GEOMETRY_ASSERT(rhs.denominator() != 0);
        Type const a = lhs.numerator() / lhs.denominator();
        Type const b = rhs.numerator() / rhs.denominator();
        return ! geometry::math::equals(a, b)
            && a < b;
    }
};

template
<
    typename Type,
    bool IsIntegral = boost::is_integral<Type>::type::value
>
struct equal {};

template <typename Type>
struct equal<Type, true>
{
    template <typename Ratio>
    static inline bool apply(Ratio const& lhs, Ratio const& rhs)
    {
        return boost::rational<Type>(lhs.numerator(), lhs.denominator())
            == boost::rational<Type>(rhs.numerator(), rhs.denominator());
    }
};

template <typename Type>
struct equal<Type, false>
{
    template <typename Ratio>
    static inline bool apply(Ratio const& lhs, Ratio const& rhs)
    {
        BOOST_GEOMETRY_ASSERT(lhs.denominator() != 0);
        BOOST_GEOMETRY_ASSERT(rhs.denominator() != 0);
        Type const a = lhs.numerator() / lhs.denominator();
        Type const b = rhs.numerator() / rhs.denominator();
        return geometry::math::equals(a, b);
    }
};

}}

//! Small class to keep a ratio (e.g. 1/4)
//! Main purpose is intersections and checking on 0, 1, and smaller/larger
//! The prototype used Boost.Rational. However, we also want to store FP ratios,
//! (so numerator/denominator both in float)
//! and Boost.Rational starts with GCD which we prefer to avoid if not necessary
//! On a segment means: this ratio is between 0 and 1 (both inclusive)
//!
template <typename Type>
class segment_ratio
{
public :
    typedef Type numeric_type;

    // Type-alias for the type itself
    typedef segment_ratio<Type> thistype;

    inline segment_ratio()
        : m_numerator(0)
        , m_denominator(1)
        , m_approximation(0)
    {}

    inline segment_ratio(const Type& nominator, const Type& denominator)
        : m_numerator(nominator)
        , m_denominator(denominator)
    {
        initialize();
    }

    inline Type const& numerator() const { return m_numerator; }
    inline Type const& denominator() const { return m_denominator; }

    inline void assign(const Type& nominator, const Type& denominator)
    {
        m_numerator = nominator;
        m_denominator = denominator;
        initialize();
    }

    inline void initialize()
    {
        // Minimal normalization
        // 1/-4 => -1/4, -1/-4 => 1/4
        if (m_denominator < 0)
        {
            m_numerator = -m_numerator;
            m_denominator = -m_denominator;
        }

        m_approximation =
            m_denominator == 0 ? 0
            : (
                boost::numeric_cast<fp_type>(m_numerator) * scale()
                / boost::numeric_cast<fp_type>(m_denominator)
            );
    }

    inline bool is_zero() const { return math::equals(m_numerator, 0); }
    inline bool is_one() const { return math::equals(m_numerator, m_denominator); }
    inline bool on_segment() const
    {
        // e.g. 0/4 or 4/4 or 2/4
        return m_numerator >= 0 && m_numerator <= m_denominator;
    }
    inline bool in_segment() const
    {
        // e.g. 1/4
        return m_numerator > 0 && m_numerator < m_denominator;
    }
    inline bool on_end() const
    {
        // e.g. 0/4 or 4/4
        return is_zero() || is_one();
    }
    inline bool left() const
    {
        // e.g. -1/4
        return m_numerator < 0;
    }
    inline bool right() const
    {
        // e.g. 5/4
        return m_numerator > m_denominator;
    }

    inline bool near_end() const
    {
        if (left() || right())
        {
            return false;
        }

        static fp_type const small_part_of_scale = scale() / 100;
        return m_approximation < small_part_of_scale
            || m_approximation > scale() - small_part_of_scale;
    }

    inline bool close_to(thistype const& other) const
    {
        return geometry::math::abs(m_approximation - other.m_approximation) < 50;
    }

    inline bool operator< (thistype const& other) const
    {
        return close_to(other)
            ? detail::segment_ratio::less<Type>::apply(*this, other)
            : m_approximation < other.m_approximation;
    }

    inline bool operator== (thistype const& other) const
    {
        return close_to(other)
            && detail::segment_ratio::equal<Type>::apply(*this, other);
    }

    static inline thistype zero()
    {
        static thistype result(0, 1);
        return result;
    }

    static inline thistype one()
    {
        static thistype result(1, 1);
        return result;
    }

#if defined(BOOST_GEOMETRY_DEFINE_STREAM_OPERATOR_SEGMENT_RATIO)
    friend std::ostream& operator<<(std::ostream &os, segment_ratio const& ratio)
    {
        os << ratio.m_numerator << "/" << ratio.m_denominator
           << " (" << (static_cast<double>(ratio.m_numerator)
                        / static_cast<double>(ratio.m_denominator))
           << ")";
        return os;
    }
#endif



private :
    // NOTE: if this typedef is used then fp_type is non-fundamental type
    // if Type is non-fundamental type
    //typedef typename promote_floating_point<Type>::type fp_type;

    typedef typename boost::mpl::if_c
        <
            boost::is_float<Type>::value, Type, double
        >::type fp_type;

    Type m_numerator;
    Type m_denominator;

    // Contains ratio on scale 0..1000000 (for 0..1)
    // This is an approximation for fast and rough comparisons
    // Boost.Rational is used if the approximations are close.
    // Reason: performance, Boost.Rational does a GCD by default and also the
    // comparisons contain while-loops.
    fp_type m_approximation;


    static inline fp_type scale()
    {
        return 1000000.0;
    }
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_HPP

/* segment_ratio.hpp
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
*/