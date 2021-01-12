
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
873TEaaHnA3PT0Nbih4xJ0/NehZeKzyPzZvfcSnxo5JSIm8iZf377pDvU5TMhPjJif4l8oZszjPz7dnfCYyZMHGyyZnPfsO2Uicn5dvW3rCtEK+47HVm7+OH/fur1pWW3CZz/v3558+NWph/ZdQ7KKl98r/3vyh3POf58Bvh+fC8QqEc860C+qucHZ7fnM+6nMPOnMtuvIgjOY+jeTHP4yWcy0t5PefzVi7gH3g5/8iruJmL
*/