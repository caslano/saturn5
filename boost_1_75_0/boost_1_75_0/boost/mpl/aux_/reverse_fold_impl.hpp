
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
ACIQr+E9VHJKVBw72Agwc4EsjPCEADG1otjWPXgumxO+g/qK1ac9iyCtj5P6Vr+8KB0TKjyLSGNzABGg1JDmsavCMVQxMOpLcNnHMl6b3hcF4SGfnJBss+NLKtrJVDH1rdt3NyKJPuDwsjaqnM3gc5PrDExYjum1//fhXfGDFl9T2LvZJu1Th9begFNJBZISDhvqnKPcw99Av/69K5IDf7REuKSCb7bFr8Ak/pR2J9ONHPLFAZk0oNDA3DZO8QQ2x1nAbxCBaPA9US7gdHH9Crjyqve+GtxzQnHpusxnuUtGcrHmvSgtIN2EJYxV1I4KAqOBhKTGQ+tfU58+NnYZzYRQL2ww6F+sie5fhhQyDOr6ElKrvmIk2A9u+R+uKwg3c1zEro5S768bPKbaW3Q4j2i6KczMDFQOokzAffp7I2AXRQGw6DWJhRNiQ0ijJAd8/Vu8RxddsxB7xFPsATg+AP5uIvdEmRPfaPasIhS6UrTrX+6P7Hps6fK5zhMUnr8otksPJGuIN8vGNoBwq6Rg+EPfEwJfbjgJgZhJgw1SEInqwIAjiWbfKIwXoZrBMCN5fNDUSVkRK3RFUMpHuFBx1JnyJLfwGRzi4V19Z8qyB3u3LOSsHGlERVP5EHeyO3pQS4DhL9yywew1IZfdTLGW9Z25LqWL2FDBZBp7Eepj8XIr0CZzz7bDiu8N82b7WLfWjszUgWxPOeaU9lJY
*/