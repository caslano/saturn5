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
NtZ+2ZvR71iGlKSssakbA/Qxc1dqu59lKKukhw4bwlVxb/0IkxlEVxNOGEqz/TPbHkszLOR/i8TCy97wEw1xicjn5vUarwgV+ZAnu8rCiOZYCG4+s5oSOQ5ot0vMR419jmkFOZd8xTvnv7RNTWcmxkosGG5BDRT9JGPIRi+FKsphj1UhBdL9UN7vyGES/aaPHXVlgNgNNRe9q3+eYGaxRhXznDXsiTb7fltSk3Ew7CNTv3mdJgvJ4g86t84/MAldebh3SzCXtWcyEzy21JNAOVXxxngFMwUigeq9OY+XjFQiOL7lr0Ww4XmODFnv9XjVcUZQt4yQMcF5Noc3Vpc6IoCTvk3ZUiKzhfdt7I+XUlRwyss4q8tnKde8DaLpdrlKggnzAtt+jyJbQrJP5Q4cSH9N4YId9nQTvqYd0q6DDXh+OCCz7pDWSVcS1qhhBh/2xQX6rmMQND1g1RlUSz3tRxYsZFzIdihbI7iWeahH4ZAobjPAQPVN749e5ppNgCqiTqPB9i5SJTDlQunktdfFwINZt/yx8imyuo8pXmK7wtPrsqfGi8R2DQvRvQ7uhZyLyR2J9Zwz/OONU96882VcTK9u7xzV56k/vKge4lV93OP+8GJ/QN+g8F0U5S+Bc236yidD0uz1nL0Sg85nktuoM3oxP5kFFJ6vPxo7dSeN6mI2CIGOPAy57PFo18y6vnBozTt7P+AuhaXmQ54E
*/