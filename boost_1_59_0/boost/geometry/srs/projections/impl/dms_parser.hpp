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
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
*/