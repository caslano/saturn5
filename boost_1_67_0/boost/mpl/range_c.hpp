
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
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
*/