// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<bool IsSame>
struct translate_int_type_impl;

//
// Template name: translate_char.
// Description: Translates a character or an end-of-file indicator from the 
//      int_type of one character traits type to the int_type of another.
//
template<typename SourceTr, typename TargetTr>
typename TargetTr::int_type 
translate_int_type(typename SourceTr::int_type c) 
{ 
    typedef translate_int_type_impl<is_same<SourceTr, TargetTr>::value> impl;
    return impl::template inner<SourceTr, TargetTr>::translate(c);
}

//----------------------------------------------------------------------------//

template<>
struct translate_int_type_impl<true> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c) { return c; }
    };
};

template<>
struct translate_int_type_impl<false> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c)
            { 
                return SourceTr::eq_int_type(SourceTr::eof()) ?
                           TargetTr::eof() :
                           TargetTr::to_int_type(SourceTr::to_char_type(c));
            }
    };
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

/* translate_int_type.hpp
zzcVDz9frd77PfYas9zv/TrO8u6v3SVuMq/YS+zmbomXb+EhccgFyCWEXefPY8YFnN0mVmBMAzecrHpb85+i5+Rqttleu4Qjaw4SVNmY952YddVEuCkvRRc3rSuT6YZ1FZ6wL+2m1yjotQhJeznPjE1TV/lsz6ZcOEmNtqYhbxn3P5v3M6lxFZ1XlI+2a6zSL3PA4ibpDLJ/rNMTbOeYd3R1PI2kIE8ghaSnQMW/SgrZ2cSm93zjzk9Xe5ildO/jegnWJORmxFB2hBldeyjYG117QN8zXlYxlRxTunWMQ2k79oxvTVA5ZGk74bLeIGS//BoV5tX0IU2s6UhQGCrng8bj9LoAYqrtjR9UYXS3UklVltu/LpH6sbuO1JUmsi/kbeQVZIfsm/+oZf2eeXel8RnrDPqBvWKNaNNOGHV6PE/lo7abLWN/Og9xJ/3aXedLjoz/aXed3uA62FP2J/egU86EXWCRUwf3eetghSrbVNUnq5/aTn+Z0k2yf25931z39kVZ9/ZFWfdE32RvvpxznLGns+OmuXIjVR+q+PJ7uMrT+Uon3W7L/s182uQqKkFtNmEn+Hx2si850WdXvQsCe+jq0pSo/Zx9xM869qvvxE/8YIw3ZCYlxB+fchL/j0SyUnolJfiSE3zxPow6xDfR61N0PfPUMVMbOmRuQ5Imyk6l6bSQNHrbFmlWdatapflzY5tqLuWaosL4vvwOhBlvedqa/tbCyep8R2m/tuW/xsfsIZqBHUhfuPan/eco/x2UXYzVlMHapv72F19VlRQX3zplVErXlB5kYUqC1VC/7r2/SZ5wTsVnoDGP9H3EFZ86pd9Dfgf0bZWHX9TnoaoHjmRIXXiSeL/j1J+meXqf6X6pL6r/iMDufmo36T8qou8/3O17rFygkIrbDo6EznNX7YdB7ZuHD88zl9SVTaQz/R+Obl5c4LsPnym/p+p8nfKR8/unOl+/VL8HG/sCrmvuC+R6q7heorreKXGBdYNfKj8tDH2FKTxJkoS3nvBaqfB66vB8/Nblyu+/q9/TdL0tU79X2k2xUvulVW3sc+S6uk+0pKwCa1RtFUa/OGlfYi+mfo3marlnPZquzg0k1notW4LKvzwrkRipOOs8TVXpLFHXKwzYidB93SB1zZPs71kv6LL4SvkbqPJiI9c8TenExbn6St3eL1XnbrOz9Ho8531gUmFl4QTnSyQ6v2aoMKvldyButitupEZi51y3muser8LuJPkh+eXqbzLhEqXzQkg9Cs5DPMl9YJ3k4aVkOLEqLBL3R3DP0GnA3Zn9knMb5NxsS865ngFqnPD0tcrnBPrLu3HvreKWFpcVFJfgNbprPWXq7tvmH6aOOX1HXjPHA/XR6TsSp+i+4x+BvkN0+qGzy9GxF/iS430JVXW+ponome5PgXDH4uddx0+TqmrdJ3l0FqLznrJbsHhCQKdnerDOOnR2Ozqpi88O6OyTcLJEZws6e1Q4VwzyxbeywoW1r16vRzidtBYSp5Qr2nl1hvOb09b72f7+/wO4V57Z9iEfIv9AhnLuI1iHfIwM4/dwEac/LjP3xyM4Tdy/q/r6VpZ9VN7XHPfV+rmsvk/AXdVng60lVZ+dOt5K6ji6qh5Tv3GT+i3uTh2ercKQui3Pgmt12O56K/Yk5F6RzP8c9Dv1LHbuFXXqXlExfYLHpMTM2TMCc/U91X2jYnqYuXrCCLa7UNfgN/jbBz1LO2G3Imxtk07im5ARGt9ydOvCxbdsVtmEyeXFxRLn1MPEmXB0v/apevdyPE+ePbPI/Nwq+q76HnkaU3Ua6+sU18RNXzOorD4xpH0KYVgfh0n7nMLS2cWRlZUVurdg0jzzs7rW1X0=
*/