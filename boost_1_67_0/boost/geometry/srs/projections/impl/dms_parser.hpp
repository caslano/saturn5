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