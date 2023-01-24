
#ifndef BOOST_MPL_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/O1_size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

// returns sequence size if it's an O(1) operation; otherwise returns -1
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct O1_size
    : O1_size_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, O1_size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, O1_size)

}}

#endif // BOOST_MPL_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
nPhr3fXl9ZMkS+yT8rtt7oCrxAmANhQ2wI9zHhoEgw01jjsWtw9tn2/P94lskPzm7dgAU7YVvKEp+hY36MGOM54tfhDB/PwK63RUrBQYCbNjXGsHmaNIxZYL4RfUsF6gY7HNAUqwiAl3U9Zq9Ac/+J5ZKphde4l+Amp/TrBvXE1QcwjNJzp6ezvUuC8e/9lyfApxUy8A11ttF7tYtEKMf+6h4kK2o14FIcW8flDahzWRNy4pDo1TMDfN5uADVBwxLn/WWVBbu9rYUmHsH1ukX6Fx/S4Jz62Y4F322bzKsVF7MXxgnqIYjgXrmP1nl+2J+AIu7AIAMLzCa8dD5z0k04vai7djn89PJixIxWAIVbJwpOEKbvgttB44Y6XSwaBVj2inN/QsiwmeuM//l6k1/vZ18PX/dtn+q6l5Pv9PU/v9Ih1JBbdDGnpRm9hi0BAQ3jX9BVydrWMTGIQAObSeFTzt10fdV4v/NPI0bGA1N6eFDjVSu38ScB2lpe+srkjRMLmVbUrPyMip/uV85KwJMqZKraKVPXsbL/V1AyQosC+PpBt88gG7zcXIVKfWrBy+FTDDzviWlmCQnqu1euM5hzmMbcOHu3qj3/vGuqpnFngXxV/Zqt1TAz/mERM5RxzHI4cGGRo8u0B0SsWohfkdbWu8agaFZl6QpdCK8FXDK2R5KLWoHSRAzAYBtV9r2ja+7MK+sMCP72/koBlx
*/