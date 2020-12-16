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
dXxs/yj7KIXreEzg/pOI4DWh83i0zANf8SSeiHen0xyx0+DOVGJC05IOba7L/B6n+UVlnqY35Iw0A0/sIfrJ99hK03+qZr7xclRin2g2QF+7Xk+V8VWyjI8S74dQDJ2HxrZps9u5y1zvLpjWd4HMu8vyUmcWvoN3mR27y9hdRil9d4PMfyDYLZBpS3ueLJOM6yP8rYjv/rWWS6TUhUqwH8awXS4b7C/UqC7TS/T4m0cXG2UqrLVMUZQxlRHX9V1RXQXjDjjT97fQd/GZ63AWRK6DzTymFhxXwRhDrJkkuN/WWheELzFajcbS+2WZm8cwlvjO53rO07Ha8xw2MPHWcL77njDwpoeEpl9d56EbMmOXnd5vpUd+9Oahyy/+FIBjIxt5+C33bMM+o+z7i4vzC+b97ctmvmzZZ39Am+5a92fJD9Ysi/+0Y1HLswsWT8lnWY+PUR577mCIn0L///n/z/9//v/z/5////z/53/6M9yEfiVj7oZ4fnND4lvhTVLSDIN/RgbQRgfQkgNo4QDa0QG07gDaqXgaznnjaWcG0M4OoJ0fQLswgHZpAO1KPA2ROeJpwzbN7r8BtNEBtOQAWmjT7P4bQOvaNLv/bJrdfzbN7j+bZvefTbP7z6bZ/WfT7P6zaXb/xdOwax/QfzbN7r8BtNEBtOQAWhhLw54ftFsp2iZhl/jLsxY07QWgNQzaoec076FpwzDqlA3auzp72prWbdk8n/Xqd+zRtDOgvcWg/eLTj/wJpQOHjQbt6u0+9DZNOwXaHoPWHp+6pGlnQdtl0F7z8Js9UdMuDOB5CbRhg7b16vHTmpY4DhupQRt96DseHNEWE6OgPVLRNid6iZu8ZGJS086D9iimYVf79t9oWohg4T8yaF//xsY3RrTxRHcmuiMAGp4kn0/88GGPuJumhY8QPJn2poU/vFPTLoH2cYP277st/1DTLqCQOw3abz76sjto2hXQkJRoN97+8W2admoW4ZAN2rEbvPr3mvaCWRETk2npW93gq1ROFPJm65n2peqvhxQNlcMYMXhe7/1bf0V1AO0BBu1h6S8dJJ7L8Lcz2uUVHzx7lcryGNhXtjJt/4VvlIj2lETiuQbPb/1+f0HTkk+V/cflHPrU56nNQHuCQXvlH/75FOqjp8HuZdDu89kbfUiPl9Gn87gWlX7szxqbaSw9I5HYYtCat133LJpHoN3FoN376M1epWkhaDsM2h++8dhH07wF7U4GbTF8f4fmGGhbDdrt3z/zDporoAUGbej239hNZTmNswaDti3fPadpIw7ty9sTp6nu+NvTDdqdvvL+Ls0x0HYbtHdMvu/FlN8zkb9Be+uLS1+m/EA7yDS89fGvOZITA2jnHZ4Lz/jWGMkC0J6whWnv/PDTfkB1QKnuZ6S78+NeekeSPaA9cBvT3lT6UZrKgoPKT69n2vqJlzxf065gdt/E4Fl+7WNeRHV/EwIBbmDaK39xj9dQ30JCvXwd0770go++jmjv4LG0NfHQhZ+/9XVPorKANm7QLt/38ieo3/9D3J3Ax3StAQA/s4QgiC1iH2tjSxO72EYEEcSI2EMistgSIwlij30niF0JVWqrWGsroSitauqpraqp2mrNQ+3L++5k5jvfndd8r+/9TJ7frz+pf865Z7/n3OVcsC7EHl0o9w7LGkaTlsT0F+5+hnkHm0Ys9I54iWUGHboFsUMPpgzEcGCXiFU7umclnle2Kc/sS2t8dv5yi8HPYjtcG7WGyy/i46PqG87YLAwsilhamT1RNssEcyYWcePyWptlgRUlFv1dnk9t5pqWs3mBlSTW+89ak2xmYswM5kpswOTJj2yWbBdu5963J22WlqbOQ6lHroE=
*/