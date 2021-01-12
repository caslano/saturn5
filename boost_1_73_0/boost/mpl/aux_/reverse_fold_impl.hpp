
#ifndef BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

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
#   include <boost/mpl/deref.hpp>
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

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

/* reverse_fold_impl.hpp
0eUCebpIvfqwNIvPWGj9c5zHzTP3NPtQ5TDVvJ1+cLwLY4QZwjah4o/aa8IqYYtQ+ifLCT2F64U5QqawQaiy07leGCBMFM7tbh8Ic/x7jbBTqLnL+V5IFaYKc4U1wg6h2m7LCpcJM4QFwlphh7DNA+4bf/YdQpU9vlN6+zFDmBrFheVCpulzbO9i4XrbOktYKGw1/ahy0tPU+pvZL8L1wmwhU2i3WDloIs3mWS+eym28jFOF
*/