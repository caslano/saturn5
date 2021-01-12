
#ifndef BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_iter_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

/* reverse_iter_fold_impl.hpp
//3/r4B/xQr958b/H5SR9m8Z/z+MuephsNyxpisHNx6s/fd84diYq11TMk7s27N3SrphJb0WrcDjX01c7BvyxNMS4v0S4j3Fc995SBk5fKTxzNJ++52HGeaTL1mDvdcI75HMMN0YjaOyXip6viFrBw8fMTIlOfbutpzxHgcl73u8622mfXJw9neHd9vF3p08MGngEK99vHBoWt6xmEN6md/70suG96Ju8p1padnvZptt3lR5
*/