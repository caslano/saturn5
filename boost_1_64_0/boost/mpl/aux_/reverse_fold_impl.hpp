
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
3umwqGR3TYPF4dE9jX6fil8A07pXVdfBwEO6zFDBXq9vnjUC0g/8F9QvWSF9HYVeZFQ3UgLgtLo4AyhJWaKcthA6QR8jlE1RlgxzxmudtEbjK13jFpoDKHQKTALJkPbWGMeEdmBH7t/ycMsWM5bOyJmGd+0JVrLUBW4q5obJIDOwRIJgEpXObO9e8vj8NjQSw0J3AQykMwtOyeqNUsBVKWJZor/93z2+Fw1sQ9dIKBxrmuXhv0UlsOx6a1guN1y3dov3RjEPnhA9bf80D3P+guamB5BHoKY72Q5ue2g/M4VMCbeMiTwmE4Jyq+25FyiXglN8w54VpCW2V9SQONUcazW0X3nMk9PLguDPpNHCjZ5rayTI7Nf7+DYmCALWl9UkucDR3ozG3RX/WGztwSlWqFWLtnpU3xNF+fQsGyfBZzahMT/MN/AMHNQ+bn9nCWOuPAxrGeRTs4DapPmk3OML7BJIKPb3Jt7IcGTjgQI8+0ruij6psHft3PKl72Nu1Ea+LtoHvTQ8cSZL4tYxRLOjUsacg5b7CLgm6VWw39/YZOM9kY6Ns6UsdfbVSg==
*/