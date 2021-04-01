
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
g5CZSdhgsMNV3cuU4dALeM28JeIio1mpK6WVuAzul8VdyUFblSTjN1rzkNyMnfQ+VSGFrAdK+VBMAyQrEgHIEOp9LgIJt0NJJbql8eh1hRgdTenVoQdb5lx7mt/r3fKE85AhRcKFsHUPIpQiXBn6mxzeCDyjVqSASZ6RAwHfaVeEdRVS9A6Benk4t3Ap6nAuuefEX2PB3T7rNBluN0Avmh1NMH+6wI85hR5CuWMg8a65YzeT/iImE2SsTEuZXVcTsMbgW6NtYTEgv5g3y815YJrhPu82odsotLx26rrt7XQo6ADuUTauxjuVEaD/c+rbrr+wFPDe9k0UjefC5EzM431gqC0j6QSDYvGdCGdz1b4XLhd+wo3uxrRRDrDJBEWi9ZKamDBdJo8xzv66T9FlILlrQLRi+3vWzF+pHwkfoOZ+2wvy6h4KTrtyczS41x2zJtyn4skn7P8ueltG106FpxhUafhk7csjP7lgkotNzFYXafEAZQuL6u184xFv0abQ+WYSpEwT8uUiOZyjaQCbN1NaWYY0o4cCqmbhmsHw4ofSPIVmSxi5XwrO3w==
*/