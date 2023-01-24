// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_ADD_CONST_IF_C_HPP
#define BOOST_GEOMETRY_UTIL_ADD_CONST_IF_C_HPP


#include <boost/mpl/if.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function to define a const or non const type
    \ingroup utility
    \details If the boolean template parameter is true, the type parameter
        will be defined as const, otherwise it will be defined as it was.
        This meta-function is used to have one implementation for both
        const and non const references
    \note This traits class is completely independant from Boost.Geometry
        and might be a separate addition to Boost
    \note Used in a.o. for_each, interior_rings, exterior_ring
    \par Example
    \code
        void foo(typename add_const_if_c<IsConst, Point>::type& point)
    \endcode
*/
template <bool IsConst, typename Type>
struct add_const_if_c
{
    typedef typename boost::mpl::if_c
        <
            IsConst,
            Type const,
            Type
        >::type type;
};



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_ADD_CONST_IF_C_HPP

/* add_const_if_c.hpp
Zhlh/5aeFDA7ByTLYDNZc7cCaBJm267eys8iRt+w8JQ4U8bFceesdbf2ICwj7kwxqlUW2wcnALe3P91TefHBlVHBvjJJZC11bHsF930a+3zf5jMEz0bM51tpciPMFMmPOB5ymLanpIX2m47sFkjq91A1u/zlAYK6v41Ptt62NAae56t5Lw6AawKdl/sedNhOaKd3TEr1G9RPYPYdzJ6R09Xq1n6K70i+56L1hbR5levNY0Y0jmkK23WFNM5oHrsfPBr4hrBpNDiE2FeKFqugwAl2V1GrJGplrRojTfzdtQN4N/wLFiQ+2r8L135lkrZ6JrDd8CPzjKW4Opq43ILtw9rSdqUqls2URCxd5h36lY/Swf024+J1HdK2BLNRrQIe5/vrWMBnTJtlYidC7lK9dBn3SeDpSvFsP+ozc23z0JyFTQnsi5ifhQPjslDIjS83+rXhuZcW/VPqGEd2C+mNgEExvBfHo7GYa2Zb9G3V0qvr8t+39IBQGpqTzvfQVDk/9CtyutqiZcw0VpYSoZeXQrW8qPW98d+LrAhkhM2c8lRJUq2OnH7jTr3A4CZz+p3wPv6VUPGuBZ1esWHqRa3EPdTqwg67n+eUU1cf4NbevRPpFaJvpbWKdWbtrVIP12nacKOrritzztiqlVbKk8JZCNkA4WykqaRvoQt6fJbipZFai+bBe5j1Ewi4EzSeNbtCuIF4JuJZyAs6j+wV
*/