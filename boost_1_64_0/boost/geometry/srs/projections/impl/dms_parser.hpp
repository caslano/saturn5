// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_DMS_PARSER_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_DMS_PARSER_HPP

// This file is totally revised from PROJ4 dmstor.c

// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/static_assert.hpp>

#include <boost/geometry/core/config.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/srs/projections/str_cast.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace projections
{

namespace detail
{

template <typename T>
struct dms_result
{
    enum axis_selector {axis_lat = 1, axis_lon = 0};

    private :
        T m_angle;
        axis_selector m_axis;

    public :

        explicit dms_result(T const& v, axis_selector ax)
            : m_angle(v)
            , m_axis(ax)
        {}

        inline axis_selector axis() const { return m_axis; }

        inline T angle() const { return m_angle; }

        template <typename CH, typename TR>
        inline friend std::basic_ostream<CH, TR>& operator<<(std::basic_ostream<CH, TR>& os,
                        const dms_result& d)
        {
            os << d.m_angle;
            return os;
        }

};


template <typename T
        , bool as_radian = true
        , char N = 'N', char E = 'E', char S = 'S', char W = 'W' // translatable
        , char MIN = '\'', char SEC = '"' // other char's possible
        , char D = 'D', char R = 'R' // degree sign might be small o
        >
struct dms_parser
{


    // Question from Barend: can we compile-time select that it is case-sensitive/case-insensitive?
    // We have to change the switch then -> specializations

    // For now: make it (compile-time) case sensitive
    static const int diff = 'a' - 'A';
#ifndef __GNUC__
    BOOST_STATIC_ASSERT((diff > 0)); // make sure we've the right assumption. GCC does not accept this here.
#endif
    static const char n_alter = N <= 'Z' ? N + diff : N - diff;
    static const char e_alter = E <= 'Z' ? E + diff : E - diff;
    static const char s_alter = S <= 'Z' ? S + diff : S - diff;
    static const char w_alter = W <= 'Z' ? W + diff : W - diff;

    static const char r_alter = R <= 'Z' ? R + diff : R - diff;

    // degree is normally D (proj4) but might be superscript o
    // Note d_alter is not correct then, so map it to NULL now, guarded by the while
    static const char d_alter =
        ((D >= 'A' && D <= 'Z') || (D >= 'a' && D <= 'z')) ? (D <= 'Z' ? D + diff : D - diff) : '\0';


    struct dms_value
    {
        T dms[3];
        bool has_dms[3];

        dms_value()
#ifdef BOOST_GEOMETRY_CXX11_ARRAY_UNIFIED_INITIALIZATION
            : dms{0, 0, 0}
            , has_dms{false, false, false}
        {}
#else
        {
            std::fill(dms, dms + 3, T(0));
            std::fill(has_dms, has_dms + 3, false);
        }
#endif
    };


    template <size_t I>
    static inline void assign_dms(dms_value& dms, std::string& value, bool& has_value)
    {
        dms.dms[I] = geometry::str_cast<T>(value);
        dms.has_dms[I] = true;
        has_value = false;
        value.clear();
    }

    static inline void process(dms_value& dms, std::string& value, bool& has_value)
    {
        if (has_value)
        {
            // Assign last one, sequentially
            if (! dms.has_dms[0]) assign_dms<0>(dms, value, has_value);
            else if (! dms.has_dms[1]) assign_dms<1>(dms, value, has_value);
            else if (! dms.has_dms[2]) assign_dms<2>(dms, value, has_value);
        }
    }

    static inline dms_result<T> apply(std::string const& is)
    {
        return apply(is.c_str());
    }

    static inline dms_result<T> apply(const char* is)
    {
        dms_value dms;
        bool has_value = false;
        std::string value;

        T factor = 1.0; // + denotes N/E values, -1 denotes S/W values
        typename dms_result<T>::axis_selector axis = dms_result<T>::axis_lon; // true denotes N/S values
        bool in_radian = false; // true denotes values as "0.1R"

        while(*is)
        {
            switch(*is)
            {
                case '-' :
                    if (! has_value && ! dms.has_dms[0])
                    {
                        factor = -factor;
                    }
                    break;
                case N :
                case n_alter :
                    axis = dms_result<T>::axis_lat;
                    break;
                case S :
                case s_alter :
                    axis = dms_result<T>::axis_lat;
                    factor = -factor;
                    break;
                case E :
                case e_alter :
                    axis = dms_result<T>::axis_lon;
                    break;
                case W :
                case w_alter :
                    axis = dms_result<T>::axis_lon;
                    factor = -factor;
                    break;
                case D :
                case d_alter :
                    if (! dms.has_dms[0] && has_value)
                    {
                        assign_dms<0>(dms, value, has_value);
                    }
                    break;
                case R :
                case r_alter :
                    if (! dms.has_dms[0] && has_value)
                    {
                        // specified value is in radian!
                        in_radian = true;
                        assign_dms<0>(dms, value, has_value);
                    }
                    break;
                case MIN:
                    if (! dms.has_dms[1] && has_value)
                    {
                        assign_dms<1>(dms, value, has_value);
                    }
                    break;
                case SEC :
                    if (! dms.has_dms[2] && has_value)
                    {
                        assign_dms<2>(dms, value, has_value);
                    }
                    break;
                case ' ' :
                case '\t' :
                case '\n' :
                    process(dms, value, has_value);
                    break;
                default :
                    value += *is;
                    has_value = true;
                    break;
            }
            is++;
        }

        // Assign last one, if any
        process(dms, value, has_value);

        T const d2r = math::d2r<T>();
        T const r2d = math::r2d<T>();

        return dms_result<T>(factor *
            (in_radian && as_radian
                    ? dms.dms[0]
            : in_radian && ! as_radian
                    ? dms.dms[0] * r2d
            : ! in_radian && as_radian
                    ? dms.dms[0] * d2r + dms.dms[1] * d2r / 60.0 + dms.dms[2] * d2r / 3600.0
                    : dms.dms[0] + dms.dms[1] / 60.0 + dms.dms[2] / 3600.0)
            , axis);
    }
};


} // namespace detail


}}} // namespace boost::geometry::projections


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_DMS_PARSER_HPP

/* dms_parser.hpp
32SvKL9pdSS/53iV8rvBa5Xfi702+b2EVhF+fl3Wrg18fcj9W7GtpHjD9vzWONs2ULEz7oP6WzmonzHpR6UffED1gw/m0qf6wYe4H3xYcHcq2AtsdP17ETRHor9Zq3zb9Z9bvo40U4cP/H2kRykuMox9pN19v92WRtLbj+8mPIa6Osja2h8jLldzoE1cll+pcm+JuA/LvZlxf4PzJbAhP1GNR09wXr/l8ehJTr9l8P3IlnZjQNhH+heldb49dYzbAoVCuC99Gni6QM37nmE+NvG+0bPMx3ODzoWG9g9rfUPnDu3zdIgzrPD1/nb1O6mzpd2Mb90R2M/1t7ieDvdQVgTiXrR7mY4j6mckLuLZcwoGuPiX7NiS7CUjKrLmNQZk/e1kiyqwiV4QQvQENtOTsxi5mOjfkWzw0r+n0axgeMb0su0/Bn9PowPgioacSXa5t2LUQxYpeMyOQQrOc43RJNI/YJ+zA2+m+Pve40LslmKh55S04sC3btSa41Wc1w7p/3dE5DFYS7wO/eEbql94M5c+1R/+kdvTW6r9b1J7vH9mvL/AfPR1mI++o9L/lfN5g/c93uX070H6rZD+feD7A8X333PpU3x/yPQ+kn2Uwe5fpe5cDcPHR/DNCIjCcecfUA76LeX4p5LDJ8z3x9yPfsp8fwZ93llQ9s9V2f+dS58qu5fnaIzIC97tGMvf0bnmP9ZfprcTp8nkNHOHPk/ajnOBjEhWXqo8V0cG3jnJJngS3+dkvnZmvnbJC09TnjUwzW6cZvTANIQfnmYPThMJSTPS2ZBQumCaXE6Tl4d1qmhTfAHjFTLeeMLLBn6ozVMe7n+F+69oZHvFTKMkL/xd07HKxmUM45cx/rM8buxqF2Up3xK75xnqZEItvj/dfboEDYfinYJhOYRb7ImdvHv4z/cS8GHKZ1W5un+PvkXziUaF12nOpcSxB2UOvlxSsWwtK+vvKd6AK+qtbdEeT+xkw+GGjNCYwz4M0tFoUHBNo4j4X8xjFllPJP1ylVL8Ei+60hxeGMHR+oWKkPDPcWS86iLZiw9Pjuvxurp8+nsSnRjxAKYRbBniSf3QGNTnRiu3P04iz/gCpfP/VruzeMqID7zkMB7iYJ3u/FqJXxyxA8x2PkyjVArPv+tbDvlEhvH2zax0+5WDbVcijPuPH0J/Sr+lP/2Sant757l2MM7ySW2N28E+jDdrkPX4rYZHtV7219b4Rs4sPvP7MsiieDvtXyek4cPPLxvzY9l/BWW/3XanIyJZMA/4al5qTNmPfuOYsn+e+3BMmchyPIBxvxWY09Sa6To1aVjHS9yc7qWwpot49WJXInuqHGcw8byb1vpuIeBJHMm5q2Y5zwH9d/8OBLmUD3G+M2D/nPbmfH2rrmyuBIVMB0w/Pxim/zDrPzsveK5WH/HnF05W20z7g32fQwg/4tGtHfDBdUyOf94h+/fQj1I82/jIu5WgU74d4hSQ3cxhva9u5zCiO1OV7kzLo0/pzqGsO4fBHKAfbOhnKBoz8+hTNCqZxizGna7qES/KQx2GAaQc70A5ahQPs/PoUzwczjzMUX0O9TWBufBcxjtC8Ny8G9PM5zS/5HVrHaepV7QPV/ZKCxivUeHdq+bjzYy3UOH9UuEdyXiLGe8xsYPgdWrYe8Bgk51Utt0cR7RoMFlqFVDiIsamDN9wlXWPCbv3tGJkNOeHK6wdh6QnnTZWgKm+5CDY57vOzg/A7pTv2R+N+j3MtzZ5XBHdOEbpxrF59CndOI7l2KLk/bHak2llvLYUXmQvOBvs4Hjfhi9q+ZeNkXb9vmO2wJa1tdAytoWWjoF6EHhPu3VoHSNzSMqrjsewThxTAvsz7qgilmw=
*/