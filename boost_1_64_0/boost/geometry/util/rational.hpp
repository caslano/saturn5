// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2011-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2011-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_RATIONAL_HPP
#define BOOST_GEOMETRY_UTIL_RATIONAL_HPP

#include <boost/rational.hpp>
#include <boost/numeric/conversion/bounds.hpp>

#include <boost/geometry/util/coordinate_cast.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost{ namespace geometry
{


// Specialize for Boost.Geometry's coordinate cast
// (from string to coordinate type)
namespace detail
{

template <typename T>
struct coordinate_cast<rational<T> >
{
    static inline void split_parts(std::string const& source, std::string::size_type p,
        T& before, T& after, bool& negate, std::string::size_type& len)
    {
        std::string before_part = source.substr(0, p);
        std::string const after_part = source.substr(p + 1);

        negate = false;

        if (before_part.size() > 0 && before_part[0] == '-')
        {
            negate = true;
            before_part.erase(0, 1);
        }
        before = atol(before_part.c_str());
        after = atol(after_part.c_str());
        len = after_part.length();
    }


    static inline rational<T> apply(std::string const& source)
    {
        T before, after;
        bool negate;
        std::string::size_type len;

        // Note: decimal comma is not (yet) supported, it does (and should) not
        // occur in a WKT, where points are comma separated.
        std::string::size_type p = source.find(".");
        if (p == std::string::npos)
        {
            p = source.find("/");
            if (p == std::string::npos)
            {
                return rational<T>(atol(source.c_str()));
            }
            split_parts(source, p, before, after, negate, len);

            return negate
                ? -rational<T>(before, after)
                : rational<T>(before, after)
                ;

        }

        split_parts(source, p, before, after, negate, len);

        T den = 1;
        for (std::string::size_type i = 0; i < len; i++)
        {
            den *= 10;
        }

        return negate
            ? -rational<T>(before) - rational<T>(after, den)
            : rational<T>(before) + rational<T>(after, den)
            ;
    }
};

} // namespace detail

// Specialize for Boost.Geometry's select_most_precise
template <typename T1, typename T2>
struct select_most_precise<boost::rational<T1>, boost::rational<T2> >
{
    typedef typename boost::rational
        <
            typename select_most_precise<T1, T2>::type
        > type;
};

template <typename T>
struct select_most_precise<boost::rational<T>, double>
{
    typedef typename boost::rational<T> type;
};


}} // namespace boost::geometry


// Specializes boost::rational to boost::numeric::bounds
namespace boost { namespace numeric
{

template<class T>
struct bounds<rational<T> >
{
    static inline rational<T> lowest()
    {
        return rational<T>(bounds<T>::lowest(), 1);
    }
    static inline rational<T> highest()
    {
        return rational<T>(bounds<T>::highest(), 1);
    }
};

}} // namespace boost::numeric


// Support for boost::numeric_cast to int and to double (necessary for SVG-mapper)
namespace boost { namespace numeric
{

template
<
    typename T,
    typename Traits,
    typename OverflowHandler,
    typename Float2IntRounder,
    typename RawConverter,
    typename UserRangeChecker
>
struct converter<int, rational<T>, Traits, OverflowHandler, Float2IntRounder, RawConverter, UserRangeChecker>
{
    static inline int convert(rational<T> const& arg)
    {
        return int(rational_cast<double>(arg));
    }
};

template
<
    typename T,
    typename Traits,
    typename OverflowHandler,
    typename Float2IntRounder,
    typename RawConverter,
    typename UserRangeChecker
>
struct converter<double, rational<T>, Traits, OverflowHandler, Float2IntRounder, RawConverter, UserRangeChecker>
{
    static inline double convert(rational<T> const& arg)
    {
        return rational_cast<double>(arg);
    }
};


}}


#endif // BOOST_GEOMETRY_UTIL_RATIONAL_HPP

/* rational.hpp
MoD2h79bPF2Y4Tah8Zo2wvx009kznlmlO3jS7oycq5/WxjFq6elRFR5T7KuGqYu/kiVi/fbmjuLnYijKqJQzv4ZMJG8mGHgi53ZRzYa5EqHZDahAQ+/iFm7ewVWHPNnO3/ONS81TYHLE5qlcG1Owk8mAsuYEmm7RBwaBwioN0VCLarc/0ZOl+VrPU0zIF+8YuINamICXJFhDmST6RiZgukAsmWtdlzSm3MQIgD+9u/XA/qUf79f7PiMQNJxYYPunDXG4KEOomoT4Y7WA/4ETjxWILMb3OAt9fHNH7u2qhLVDrRuvCukZIMcz6RbE7HwOZmlzzfyuwV415zo1kPpE7dfuMMM6YyQWHh0nVXoKCJuTuBC7+atfrWIuALAFiUPPc3AUsNII0NJazKQyZFTfHgK3Cr+15zQDnrkM+fvbVgBwOBtrR9O1MqYs03AfrBT8txe6+WIF0YJNCeFDmSb+EujD+5ArEa9WpeFr6SZ/Y1s64qJcEME4P/9/4Q0k/7WWJ9eqEJGaI/ZOOS7PYOE807ZVbUBpgfmjvNf6SbupV+B35EHCHpF2SoW45g==
*/