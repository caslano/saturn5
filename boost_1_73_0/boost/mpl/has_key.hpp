
#ifndef BOOST_MPL_HAS_KEY_HPP_INCLUDED
#define BOOST_MPL_HAS_KEY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/has_key_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct has_key
    : has_key_impl< typename sequence_tag<AssociativeSequence>::type >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,has_key,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2, has_key)

}}

#endif // BOOST_MPL_HAS_KEY_HPP_INCLUDED

/* has_key.hpp
6r4veVjvS5SMTuN+Ys+oQu5+Gd2De3AP7sE9uAf34B7cg3v4Pxn+7vK/tfj/YM/9H5O+onyl7F1H0l2ZUJgyRdB4T6XszYzyjbTLZ/w1HJ51MxBLN1CZw/q8vY1lGZTnNc/bfeR5e+VCBCyFIZT3I4lvf9eAhNJtjhTT793mYCVJg61sL90ouSzzO35vwHNjM70V2Z/hJnswTXnkqWkbgO/Yk8wy7ZbEi5V4ZRzaKeA57B+2
*/