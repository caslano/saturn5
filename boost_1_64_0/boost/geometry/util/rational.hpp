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
p0LUs+JRNzy7T+nZG3rKj7p3ebB/YWFpS5aqcm6ZBZ/eFj5h/26RcnV9LNt6s1zOipw0jo3zhnK3WK49CQobp56FeHO8PW54Nl7V6SN1Nvax3Nf/Wp5pY3McWY+mWXo+PZ+eT8+n59Pz6fn0fHo+/8PHfa6yxMnL7Uy99DxyXuKJQM5G+IY830FqRdr94X5PZZM99rW99rV/cG0jUj1fHXfFsn+WfTTqQ9pm5MN/3B/LfhntId9cpMOQdn/0/ansTa+9jOiJ1Knl0/aj2J9CCzyXJnNuko97TNlzyt7TMhDpE1/LN83S8+n59Hx6Pj2fnk/Pp+fT8+n59Hx6Pj2fns//wecrfIb0+daFqu/jGI5/IH7zg/gnxSAv+BK/xCI9ZFOpY5pKTxZ4Xkvj16oj9pjP1PfL+PuGXpJ/qPq++n78not0oryrjHTbVFV+MJ+/Olt937lSlcuUv0lA2udZpu+oNOQ86/tcpePi8M8SIz18QD3fHGuxjEJ68BbVzoUCVd+WMap++z88lZ5tqvyJJR6q/UWeqv0v1PcE5r/wmKf6nqrSXcy/e59q72iqSu0bVDrgTaSSr4XyEJV/Iu127nOVLvJX9Y25R6WTJqj0EPU4nK7SrVtUevJllV76RKV+8Wpcht7F+pcoeZ8XLUrfLJa7Wz1P3qHksfHq+3Ebx+l5i+p/mUodJzGO0v5rKr1wVuUL4XheDVXfzyxW+Q8Uq/TEGyo9d4j1sP8j/dleKftXrtLNzar+aLaz968qfzbrHfw0662mHf+s0n6s5+oLSKUc9e9zWbUzJovjhPH1kTRBybOZb12A+j51Hsf3kkXZlfoej1HyggdVOvwq/EXyP6C+h9hVej7fovwY7yz1En9YoORbolR6cL96foz2Hsx59GqSSvts81TtcVzy/kW9N6i0H8t7tNKODg/1PcRT9eMhle74yNPiJ+WmsT36h4P2iT/NfrGeg+znhoeZ70/K/jtQzlvyJXJ+j6LeX3mqdq8yfzDt16G+R19S3+d/yXQ4yz9Hf0jivItT/b7wOPs1VMljOb9GFin/Oj+E48V03V3q+dFV6vnWXPXd+6x6ntlJ/2S/T5fTzxhHTg/jeNAvtp1V7Y/p00vlo39voD7Rs9Tzietpvy4lXz1RfV/Jeb91vurPYfbbnoLvktKPY0ewf8NY7zklv7yD830x9cxk+SG0b5dKd3McEsar78lpLO/WaznjCHop6eZZqv35nDd+e1W6g/Nm0ousn/71Kv3+aIIqd/ABpNIux2GzVX0f8zq+Sz6O8+75Ko3nuE4JV/Udc8+/djUfLpQyvrQxDrngZ9JOvIrXp/xpV/ZzxyKVbmO/kgPpB4x/Y0apNJPxdirTRYzHeRm08yr6C/52IRipN8dj2/P0kwLGl4GcZ+3q+/BPOQ+p7+knVb/n96afcB7Fz2HcwL3zfaL3TGWnnYzD/Z7nPHxKlZ+YzLgwB/2WdudxveF4neE6l0l/OfQw/SGcfpLGdemH9L/B7O9F9X35Is5nxtFjnM8j+fykE/lFPpX+VEY5xslHvuP/E/NtSRNVupfzNKHNotqbznWZ7RaEcFw+ZFx6l3H5goqT2zjPDtCe9kKMAVKPcovq31PqeexMNT5bU7lucl8wmP594R7a+U5PJR9Cu5Rynce8vRYv5iq53wz8doH0Eu0xjvM1fov6fmakh9IX+vSSlPPx5FsqHZrKfgTQj+gHWz+jnenf56JV6t09HzmPuP7v43oV/XP6KeffCdrr/LOM+/TrUy/w+w+4z2B8ueDdS+nNeelB+y9iHPR4jv26X8kHLGT/UumHC5S/jVmH/FLuccYV5ttCu1z9F9fzAI4Lx+lgu1oP9to=
*/