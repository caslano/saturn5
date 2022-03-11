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