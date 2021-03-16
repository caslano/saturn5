
#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Eric Friedman 2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Predicate >
struct find_if_pred
{
    template< typename Iterator >
    struct apply
    {
        typedef not_< aux::iter_apply1<Predicate,Iterator> > type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

/* find_if_pred.hpp
yuz402Q/B02BDbv5NvPlipxAw1zgMEurvl8Fn74ZijhYiC7FONfj1hz6NH8CUPA9fIzOIo8vc4bK62O0oSWm/YUlQFsU3bRG08TgDvkYo6VAwT3Ever+HxRdW+rjcO4SvaJ0KVBs2mAYQEOHUt1q10gRr6Hi/JBg/yXYTwV7QzDUxVjCM9j/h0VUXDHoar9TPb0L9zttLzN7nRgLLbt2uIuuensTLbriZs3Q9iawYHjR9ZTOGy2Hqzi0zqLnSVo=
*/