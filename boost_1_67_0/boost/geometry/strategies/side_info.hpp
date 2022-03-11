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