// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SIDE_INFO_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIDE_INFO_HPP

#include <cmath>
#include <utility>

#if defined(BOOST_GEOMETRY_DEBUG_INTERSECTION) || defined(BOOST_GEOMETRY_DEBUG_ROBUSTNESS)
#  include <iostream>
#endif

namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

/*!
\brief Class side_info: small class wrapping for sides (-1,0,1)
*/
class side_info
{
public :
    inline side_info(int side_a1 = 0, int side_a2 = 0,
            int side_b1 = 0, int side_b2 = 0)
    {
        sides[0].first = side_a1;
        sides[0].second = side_a2;
        sides[1].first = side_b1;
        sides[1].second = side_b2;
    }

    template <int Which>
    inline void set(int first, int second)
    {
        sides[Which].first = first;
        sides[Which].second = second;
    }

    template <int Which, int Index>
    inline void correct_to_zero()
    {
        if (Index == 0)
        {
            sides[Which].first = 0;
        }
        else
        {
            sides[Which].second = 0;
        }
    }

    template <int Which, int Index>
    inline int get() const
    {
        return Index == 0 ? sides[Which].first : sides[Which].second;
    }


    // Returns true if both lying on the same side WRT the other
    // (so either 1,1 or -1-1)
    template <int Which>
    inline bool same() const
    {
        return sides[Which].first * sides[Which].second == 1;
    }

    inline bool collinear() const
    {
        return sides[0].first == 0
            && sides[0].second == 0
            && sides[1].first == 0
            && sides[1].second == 0;
    }

    inline bool crossing() const
    {
        return sides[0].first * sides[0].second == -1
            && sides[1].first * sides[1].second == -1;
    }

    inline bool touching() const
    {
        return (sides[0].first * sides[1].first == -1
            && sides[0].second == 0 && sides[1].second == 0)
            || (sides[1].first * sides[0].first == -1
            && sides[1].second == 0 && sides[0].second == 0);
    }

    template <int Which>
    inline bool one_touching() const
    {
        // This is normally a situation which can't occur:
        // If one is completely left or right, the other cannot touch
        return one_zero<Which>()
            && sides[1 - Which].first * sides[1 - Which].second == 1;
    }

    inline bool meeting() const
    {
        // Two of them (in each segment) zero, two not
        return one_zero<0>() && one_zero<1>();
    }

    template <int Which>
    inline bool zero() const
    {
        return sides[Which].first == 0 && sides[Which].second == 0;
    }

    template <int Which>
    inline bool one_zero() const
    {
        return (sides[Which].first == 0 && sides[Which].second != 0)
            || (sides[Which].first != 0 && sides[Which].second == 0);
    }

    inline bool one_of_all_zero() const
    {
        int const sum = std::abs(sides[0].first)
                + std::abs(sides[0].second)
                + std::abs(sides[1].first)
                + std::abs(sides[1].second);
        return sum == 3;
    }


    template <int Which>
    inline int zero_index() const
    {
        return sides[Which].first == 0 ? 0 : 1;
    }

#if defined(BOOST_GEOMETRY_DEBUG_INTERSECTION) || defined(BOOST_GEOMETRY_DEBUG_ROBUSTNESS)
    inline void debug() const
    {
        std::cout << sides[0].first << " "
            << sides[0].second << " "
            << sides[1].first << " "
            << sides[1].second
            << std::endl;
    }
#endif

    inline void reverse()
    {
        std::swap(sides[0], sides[1]);
    }

//private :
    std::pair<int, int> sides[2];

};

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SIDE_INFO_HPP

/* side_info.hpp
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
*/