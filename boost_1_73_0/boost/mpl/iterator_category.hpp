
#ifndef BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {  namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct iterator_category
{
    typedef typename Iterator::category type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,iterator_category,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, iterator_category)

}}

#endif // BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

/* iterator_category.hpp
5bmMgfgLtsar2Al/wyfwBobjTYzHW5gi/cXOUcAXsDCmoSduQC/cjkXwAyyKu7E4nsIS+B2Wxl+wLBI8fLAilsNHsAI2Ql9shZUwBP1Q2U4uffIuLRL8CSUIw2U7M2U7D2M9PIKN8Sga8BhOwWzcjidwF57EDPwaP8LTeBm9C8v7rvL+qz92INyS5yMveLE+XITVcTE2xFexPy7HUbgax+ManI7rcA6+hm/j6/hP3Iwf4hb8
*/