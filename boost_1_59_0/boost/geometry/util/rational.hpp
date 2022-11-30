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
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
*/