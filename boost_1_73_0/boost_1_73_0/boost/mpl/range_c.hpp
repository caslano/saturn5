
#ifndef BOOST_MPL_RANGE_C_HPP_INCLUDED
#define BOOST_MPL_RANGE_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/range_c/front.hpp>
#include <boost/mpl/aux_/range_c/back.hpp>
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/O1_size.hpp>
#include <boost/mpl/aux_/range_c/empty.hpp>
#include <boost/mpl/aux_/range_c/iterator.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<
      typename T
    , T Start
    , T Finish
    >
struct range_c
{
    typedef aux::half_open_range_tag tag;
    typedef T value_type;
    typedef range_c type;

    typedef integral_c<T,Start> start;
    typedef integral_c<T,Finish> finish;

    typedef r_iter<start> begin;
    typedef r_iter<finish> end;
};

}}

#endif // BOOST_MPL_RANGE_C_HPP_INCLUDED

/* range_c.hpp
QerJwJbaDVh26GIJgDCdlroeMzqD8BHlJy+QKz4hPmC/aX7hZEOsU5B7U/Ph893T6mHxGLCJlLij7St+FbBlqzYkDymUfngzxF04qasDtkb6CN8LG/83vDN+7jkt3ifBz7/KP1BLAwQKAAAACAAtZ0pSIUn6Z1MCAADmBAAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE4NlVUBQABtkgkYLVUYW/TMBD9bqn/4eg0CSYyJ2UMlqWV0MbYBKzVFsY3JDe5LNYSO4rdlkj8eM7xug6qTeIDUZTEvnfvnu+eklg0NhMGJyyRqtD0usNupdvcTNh5ms76B8ym1ylL+CaUcI9mO3CN7RLbwMgcWdJiU3UUzoUVnoBH+xGMwhCmn8GsTFZpg+xUWIwhXeBrCI/gUi8JEYUQHcQHRzFhP31NmeeNwSkMTL/ghbhDdqKVRWWDL6hubRlDFDE2r4S/GUnzxRN+L4Y0nlTSZXiNWb8ggCedsNLahuDrJSRK1OjVw9XZSfT+8F1guwah0G3daGOluoWVtCW4XQNakcifFgqJVW4on3sCSDJd10LlvkTM+e45NfJiFu867tn0KuUr5CuhLKciEJzB0GWOc6GI6tixj2uteaH1sI+Wtq7GkMx13k1KrCqd
*/