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
YhpVeWC4FhYtfmTIvBoKjLWGAAtu0WLop787sXjSbM/TloSryp0T1vSxlLxwVIcQimfNRVhm3I3+wWnOunItQ43O5uDJ+s3gTvhz6OLaO6WQSlXVT3/MQhofUt5fNVqw4ViMB8WnmNUMGlBHMK3NVipcrX879k7X7tanm9XJDyaXZMdfrhZ4Z4+LLlL0itYbUEBvw/86U4njB9b6BFrUkFmpSFKYffvVaG6WF8NWTEgmiop2Ty08uB2328YYnZWfKZNgzaKT8S2b1NloJ2izvisNmr473JVNY2Wm8ZuBDLNuB5qWQLEbrkY3ylBeqE9eUNuU9w1taB+bMVBP7M+19e6kQv+VrhGoeejMaR79p88NZUAGLHjK33uqD+Y/zTW9m7a6lX6YdeI45fSJObotMVyKty9Fq5W639i26S/5FqdtLWQ3tnyeeInZKiDrOvC2yz7r11ehkdX6a+V51Quv9inWwhNFHAs68sg6WmUFHoyMNRt/yM+3FgNdjDI5NRLmYHQ2O3rLn4l0hNOK+99OtgbFvxn5Et70vd2XOKlC3+BhPpW0MSOvEl6/amew2sJWU8A1Qxo1gBLtcKw8JVRP+arnjugqToIccx2rHLV/XBKfJ3bqS/dD7zouMHfd5OftsVW9xaS6Yf0TEQF7nYQvDAIIpcnRO8tpYiGz16S7e7dEobmiicwKSc+01pxYo4xg3I2oqFkFS3zLrsqy
*/