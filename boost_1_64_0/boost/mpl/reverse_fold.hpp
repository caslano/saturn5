
#ifndef BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED
#define BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/aux_/reverse_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_fold
{
    typedef typename aux::reverse_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , BackwardOp
        , ForwardOp
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,reverse_fold,(Sequence,State,BackwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, reverse_fold)

}}

#endif // BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED

/* reverse_fold.hpp
O+/3iWMBsNuoFMpwP6M5TYjb5fYGauF5pULw3dTjW2GH75X8D1h2y/75MoIcI55DuP1oN9Rem2Womlk/5NhX2S809m5ZTAzApcIRh5wg1xWb5+RAZygJJjgM62o7txqt9DFPcoXq7XCJUNsgmGKU9hlmra+KQYrF0m85cnf9pk25GXg1OSZZELCETpihoQT0Wonv59fQhpG698eALuUfAyixeeN98dDcPah+MhcjWel4JKkKwckWiJ4kuv/uA/vAzicQ+ZxAev8riYz9HsGFVGzRAYqW0CnTpzVR1MhoTD1yzOErW9T6HMqdaDmBOCmr3RPvIAKHpa1bgSsuCUoOp2NlfliiXbPH3hMLMNkzooVNAgsmX4ztFHxTbl7Nrx9O7xIwJbnmC8kE61xbvwcS7f04De9YDDDAkDy3YtKx8CDXsK5MrHKgXvDS8Ur9SbnZQNYkSHpyVmG1LcVUXedVt3llQEHu3GJSqYp9A2PYvKxouGGth5FrwGSBuHV2ljC9aKAHK0ZJOd+B9u0tTg58UcYuSbz25unvKl7i97mkVln/ywI4fqNf1TlCjA==
*/