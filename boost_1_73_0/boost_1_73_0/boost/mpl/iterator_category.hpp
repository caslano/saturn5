
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
ZpHqT5+XVEN/4EFZXxCYVffklSsa5eurP/CgrC8JzBp7ycUPS2pHf+BBWf8kMIueD6sE9VZ/4EFZXxGYdcvEP/1CUsf7Aw/K+po458YUQZ03AHhQ1jcEZi3+ePFZkrp8APCgrOPEmTVVUPEBwIOy/kVgFn0tS6ptAPCgrG8JzIqc/MuU7YK6ZwDwoKz/JTDr3H/2B9TWAcCDsv5N0DxcF9+yWVCHBgAPyjpB0Nw4mRWV1NEBwIOyThKUZc75TYI=
*/