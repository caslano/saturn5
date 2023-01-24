
#ifndef BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< 
      typename T
    , typename Base
    , int at_front = 0
    >
struct v_item
    : Base
{
    typedef typename Base::upper_bound_ index_;
    typedef typename next<index_>::type upper_bound_;
    typedef typename next<typename Base::size>::type size;
    typedef Base base;
    typedef v_item type;

    // agurt 10/sep/04: MWCW <= 9.3 workaround here and below; the compiler
    // breaks if using declaration comes _before_ the new overload
    static aux::type_wrapper<T> item_(index_);
    using Base::item_;
};

template<
      typename T
    , typename Base
    >
struct v_item<T,Base,1>
    : Base
{
    typedef typename prior<typename Base::lower_bound_>::type index_;
    typedef index_ lower_bound_;
    typedef typename next<typename Base::size>::type size;
    typedef Base base;
    typedef v_item type;

    static aux::type_wrapper<T> item_(index_);
    using Base::item_;
};

// "erasure" item
template< 
      typename Base
    , int at_front
    >
struct v_mask
    : Base
{
    typedef typename prior<typename Base::upper_bound_>::type index_;
    typedef index_ upper_bound_;
    typedef typename prior<typename Base::size>::type size;
    typedef Base base;
    typedef v_mask type;

    static aux::type_wrapper<void_> item_(index_);
    using Base::item_;
};

template< 
      typename Base
    >
struct v_mask<Base,1>
    : Base
{
    typedef typename Base::lower_bound_ index_;
    typedef typename next<index_>::type lower_bound_;
    typedef typename prior<typename Base::size>::type size;
    typedef Base base;
    typedef v_mask type;

    static aux::type_wrapper<void_> item_(index_);
    using Base::item_;
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

/* item.hpp
P7GNplXepabW6m97lzVqUQPzls8h6MtXLfm/TdveY47SW6bVPQc0HAfUfyS8rZjCloFyeZK7pJyFoHa+Ev8VDzYbzO6y+Nm1VCuba5xjZ1v46A86KfiwRKC31EoUe7OPw69kNAkcpoHV1Os6YQqJsjdiPk30g+naPMsL2KB6JqH8VjCg3mNyggVECTFkexgSlsBMYEtFbUgpEFFIR9+c9r2lm502uKGb9WWmJ9njSp4AzOpv/k1Io2p+RHZRfvDhZaAof5pcffD/8oqIic04/Kt9PpUhJ4IQAgql3HtfMfKG94tuYYNrROxuKD8eibFWVGN+aIvid4cS8Xql2QuMsJ9ptY2DqGCxVoHwa7mLTYmnFhEf4BDJ8Oo+bkAApf15EZLIG7xcZ15GGEVO7fVqobzhS4mxUCz2HlNB7hOtCHcu5PFMwehSunOw/2sIarMDtjSO2nj6xuDNPgQ4wIyiUTrr8ktgSGvT7vBz4NkaHG2sEzSOUTx+hIj2MTkKw1xqpsbVj7Y1Cvg3MiAjBA1CXyeRSBw+D45d0BqSlt4vG0Mvey/gJhTp6dGVthobecwvgdqt+/tZavJ5mgjssrX8Fk1gOHKy8KMSUL8XPpQnPv0Og9DmF0cs3kUobLF2r2bDl4E6Fs98ALJJKScrtgyXto5j3WPz8ott9W7mmH07WBRleTxRrASsp9csqkfWs4X1iXfWFncmU3GmvktS
*/