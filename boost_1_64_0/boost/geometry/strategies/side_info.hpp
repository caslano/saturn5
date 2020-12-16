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
sa8j3WMuRlNuGG2G8P9hmH7hYyn2/Z1YQ5Qfh67F/y6UH4+/KeStpN7vsetpaxj5l4Gx1N0XP++BHsQ5Af0S+SOZg2fVB3wYKKDtj6i/Hf4m0MaxxN+H9C/weyT6RuxynWPqH0W9a+Bl8KPkryHWO7BfoA9P4qORtlagF+PzeZ0HypTAn9LuEcR3IDwYfEP+WHgH6uTBe+P/Wux7KP/x9ozFdsQDplHncuKqhK8Gv6XcjrRxZUdigAuJ9WLKnU7dnuQvJ71I1xQ4ibStyf+a/J/RR+PnZtLaFzD+lA1jTyZtH+qcrWXBIcTyMnxne3xQ5k1if4Ay/SnzNvWW4qeU/Gexh2NfpuuQNmq6kEY831GuX5hjArwL8mn7Iso8ho89dX3i/yvKnQOexv8ZpM0Ax23PWibvGj3uabMjdg/y9yJ9K3RFF2LT67/2pNPuecRwN3nPdMQX9RvInwnu0vFBz6a9JvAy+VuDQspfSv4Q0m4Ls5bwdThpnYkjQvlH8DWU/KmkP0HbfdAXUq4tc/njzpQlbyRpdbRfTNor9OsgeC/8XU08N2CvwM9vSP8BH+fiY+D29IV4hsCXg4spe1Yn6lDmEvr2OfxWF+Kn7inYr5FXTr36MGuJ9C7YB0Q4jrqwlkhLoJ+kL21AC/bJxP4CeY0FrHF8hLF/RazL4b/hb357xggeT3y3k/4CeIa8dsSxJEyMulfgZ5ft6TN6EOU7wk/Dj1BmDOnPUf9ouIG6XUm7DnsV7b5P+o/EMZeYJ+JzLb5+h68/EEce9lTSdyD9XvwFSLuUspPg3+meD39ATNeSthp/I7ZDt2edYVeQtgX+nypgjHSe8XE+6fdg13F+uR78CTwGXgGfgZ9B+6p82QlEweHgBDABnAeuADeB+8Ez4HXwBcgfny87g0IwBJSCOJgJ5oE/gybwT7AatJ2QL7uBA8DxYCy4eAIxgUXgBfAR+BG0m4hvcCA4GowC08BFYC64DywBb4GvQft4vuwLBoATQSJOWTAH3AMeBsvACrAWdD4tX7qDw8BQUAHOBleAO8HT4G3wFWhXTVkwGIwH06uJAdwLnq3GJwgm8mUHsA84AowCZ4LrwAPgiQTjlsAf2KomX34NDgW/BfEafILrwWLwHHgP/Ay2m5Qve0zCJxgJzppEnybhE7w6ib5Poi+T86UXOB7UgLngr+DtyfgAv5qSL/uB48B4cAG4AzwPVoO2U/OlBxgKSqcS91TiBveDl8EnYJvT82V3UAROPJ0y4Gbw4On4AR+DvDPyZXuwJxgAhoGx4HxwM3gYvA6+B+3PZKzAsWACmAVuBX8FTWAFCExjDYDeYCioBLXgKnAP+Dv4Bmx5Vr7sAgpBMfgdmAhmgnlgMWgCH4CfQPhsyoNe4FBwJDgF1IL54AHwPFgBfgZdzsmXvcDB4EhQBsaBs0AdmAvuAA+D58Gr4FPwI9imNl8ioCc4CAwBJ4BqcDG4CtwFFoMm8B4ITGd8QDdwAIiBSnA6mA3mg4fAC2AFWAPansuxBfqAGBgDzgM3gAfA6+ArIOfRf7Af6AuOARVgErgU3A4eAX8H74OfQacZ+bIr2B/0AyeBalAHbgcPghfBu2A12PZ8+gyioC8YCsrAZDAL3ATuBk+B18HnIHRBvnQEu4C9wRBwIhgDEuAcMBvcAh4Cj4PnwGugGbSAthcyZuAAcBQYBSaDGeBGsAg8BJ4B/wCfg8BM5gjsDHqBIaAEnA1mgdvBM+Bj8D0IXUTfQC9QDE4BM8Bs0ACWgjfB16DNxRy/oAcYAI4DE8BMcCt4DLwEPgVbXML+AXqBI8AIMAZMA1eCG8FC8AJ4B3wLZFa+dAB7gQHgRFADLge3gkfAG+A=
*/