// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016-2021.
// Modifications copyright (c) 2016-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_HPP

#include <type_traits>

#include <boost/config.hpp>
#include <boost/rational.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{


namespace detail { namespace segment_ratio
{

template
<
    typename Type,
    bool IsIntegral = std::is_integral<Type>::type::value
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
        BOOST_GEOMETRY_ASSERT(lhs.denominator() != Type(0));
        BOOST_GEOMETRY_ASSERT(rhs.denominator() != Type(0));
        Type const a = lhs.numerator() / lhs.denominator();
        Type const b = rhs.numerator() / rhs.denominator();
        return ! geometry::math::equals(a, b)
            && a < b;
    }
};

template
<
    typename Type,
    bool IsIntegral = std::is_integral<Type>::type::value
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
        BOOST_GEOMETRY_ASSERT(lhs.denominator() != Type(0));
        BOOST_GEOMETRY_ASSERT(rhs.denominator() != Type(0));
        Type const a = lhs.numerator() / lhs.denominator();
        Type const b = rhs.numerator() / rhs.denominator();
        return geometry::math::equals(a, b);
    }
};

template
<
    typename Type,
    bool IsFloatingPoint = std::is_floating_point<Type>::type::value
>
struct possibly_collinear {};

template <typename Type>
struct possibly_collinear<Type, true>
{
    template <typename Ratio, typename Threshold>
    static inline bool apply(Ratio const& ratio, Threshold threshold)
    {
        return std::abs(ratio.denominator()) < threshold;
    }
};

// Any ratio based on non-floating point (or user defined floating point)
// is collinear if the denominator is exactly zero
template <typename Type>
struct possibly_collinear<Type, false>
{
    template <typename Ratio, typename Threshold>
    static inline bool apply(Ratio const& ratio, Threshold)
    {
        static Type const zero = 0;
        return ratio.denominator() == zero;
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
    // Type used for the approximation (a helper value)
    // and for the edge value (0..1) (a helper function).
    using floating_point_type =
        typename detail::promoted_to_floating_point<Type>::type;

    // Type-alias for the type itself
    using thistype = segment_ratio<Type>;

public:
    using int_type = Type;

    inline segment_ratio()
        : m_numerator(0)
        , m_denominator(1)
        , m_approximation(0)
    {}

    inline segment_ratio(const Type& numerator, const Type& denominator)
        : m_numerator(numerator)
        , m_denominator(denominator)
    {
        initialize();
    }

    segment_ratio(segment_ratio const&) = default;
    segment_ratio& operator=(segment_ratio const&) = default;
    segment_ratio(segment_ratio&&) = default;
    segment_ratio& operator=(segment_ratio&&) = default;
    
    // These are needed because in intersection strategies ratios are assigned
    // in fractions and if a user passes CalculationType then ratio Type in
    // turns is taken from geometry coordinate_type and the one used in
    // a strategy uses Type selected using CalculationType.
    // See: detail::overlay::intersection_info_base
    // and  policies::relate::segments_intersection_points
    //      in particular segments_collinear() where ratios are assigned.
    template<typename T> friend class segment_ratio;
    template <typename T>
    segment_ratio(segment_ratio<T> const& r)
        : m_numerator(r.m_numerator)
        , m_denominator(r.m_denominator)
    {
        initialize();
    }
    template <typename T>
    segment_ratio& operator=(segment_ratio<T> const& r)
    {
        m_numerator = r.m_numerator;
        m_denominator = r.m_denominator;
        initialize();
        return *this;
    }
    template <typename T>
    segment_ratio(segment_ratio<T> && r)
        : m_numerator(std::move(r.m_numerator))
        , m_denominator(std::move(r.m_denominator))
    {
        initialize();
    }
    template <typename T>
    segment_ratio& operator=(segment_ratio<T> && r)
    {
        m_numerator = std::move(r.m_numerator);
        m_denominator = std::move(r.m_denominator);
        initialize();
        return *this;
    }

    inline Type const& numerator() const { return m_numerator; }
    inline Type const& denominator() const { return m_denominator; }

    inline void assign(const Type& numerator, const Type& denominator)
    {
        m_numerator = numerator;
        m_denominator = denominator;
        initialize();
    }

    inline void initialize()
    {
        // Minimal normalization
        // 1/-4 => -1/4, -1/-4 => 1/4
        if (m_denominator < zero_instance())
        {
            m_numerator = -m_numerator;
            m_denominator = -m_denominator;
        }

        m_approximation =
            m_denominator == zero_instance() ? 0
            : (
                boost::numeric_cast<floating_point_type>(m_numerator) * scale()
                / boost::numeric_cast<floating_point_type>(m_denominator)
            );
    }

    inline bool is_zero() const { return math::equals(m_numerator, Type(0)); }
    inline bool is_one() const { return math::equals(m_numerator, m_denominator); }
    inline bool on_segment() const
    {
        // e.g. 0/4 or 4/4 or 2/4
        return m_numerator >= zero_instance() && m_numerator <= m_denominator;
    }
    inline bool in_segment() const
    {
        // e.g. 1/4
        return m_numerator > zero_instance() && m_numerator < m_denominator;
    }
    inline bool on_end() const
    {
        // e.g. 0/4 or 4/4
        return is_zero() || is_one();
    }
    inline bool left() const
    {
        // e.g. -1/4
        return m_numerator < zero_instance();
    }
    inline bool right() const
    {
        // e.g. 5/4
        return m_numerator > m_denominator;
    }

    //! Returns a value between 0.0 and 1.0
    //! 0.0 means: exactly in the middle
    //! 1.0 means: exactly on one of the edges (or even over it)
    inline floating_point_type edge_value() const
    {
        using fp = floating_point_type;
        fp const one{1.0};
        floating_point_type const result
                = fp(2) * geometry::math::abs(fp(0.5) - m_approximation / scale());
        return result > one ? one : result;
    }

    template <typename Threshold>
    inline bool possibly_collinear(Threshold threshold) const
    {
        return detail::segment_ratio::possibly_collinear<Type>::apply(*this, threshold);
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

    Type m_numerator;
    Type m_denominator;

    // Contains ratio on scale 0..1000000 (for 0..1)
    // This is an approximation for fast and rough comparisons
    // Boost.Rational is used if the approximations are close.
    // Reason: performance, Boost.Rational does a GCD by default and also the
    // comparisons contain while-loops.
    floating_point_type m_approximation;

    inline bool close_to(thistype const& other) const
    {
        static floating_point_type const threshold{50.0};
        return geometry::math::abs(m_approximation - other.m_approximation)
                < threshold;
    }

    static inline floating_point_type scale()
    {
        static floating_point_type const fp_scale{1000000.0};
        return fp_scale;
    }

    static inline Type zero_instance()
    {
        return 0;
    }
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_SEGMENT_RATIO_HPP

/* segment_ratio.hpp
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
*/