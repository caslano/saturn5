
#ifndef BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

template< int dummy_ = 0 >
struct multiset0
{
    typedef aux::multiset_tag tag;

    typedef int_<1> count_;
    static char (& key_count(...) )[count_::value];
    static char (& ref_key_count(...) )[count_::value];
};

}}

#endif // BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

/* multiset0.hpp
vQQbz+hOZP8KEz8buEyrdadW1D0ozgTttWH9M6LVEgFfkX2sriPEL4MphWlXWz0aQm9sQPOaOk3kbIhGGl3Zz8GzsZkbW2M/lREKNb7cROxa1/6NDbWS22uDXeTjRwXJ9oaSLJ9Vd6z7e2ih8KN26vlfXdNG8d4Bbygb1188O8cbm5viqlWV/VmNe7IHA2pzWT7i2urVkjXn4E39cZWxAW05lrOf0JyJ2pcnVG20KatN5Kts
*/