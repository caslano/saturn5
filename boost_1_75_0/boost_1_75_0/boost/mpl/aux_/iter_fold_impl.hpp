
#ifndef BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

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
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX iter_fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

/* iter_fold_impl.hpp
pvYEXx9UBdTGJeFBrNufIJ9v+2Te9hd3pOfBhVWCqCD+AeEE2OhCFUDN/gXMZTbqOYABr3hNzsgBmwI60aUwxxltjmSl5DXOkkjP9gx5Tb7j56hwt9mtM05T/we2GzqBjLHftsIWn5i4bIp+R7gQX7Sd/6B2a7b/gbMZS5AQ1hIW2TEH4qYgdox+QQQQo6pryKBrUVV/wfOURndzVueQcF6tXJsgfqI2mG6dhrgEf0XMga0W2qQeNlLZeLmpc0VY0yRp3hd/j7BKikxztrK0d5JMDmQRSqp9iJsfOPemWePV1qL3lQ/CeGsnsUbzM5RUMr8BwNGbV8qcT1umRp713Zf9lZ3OJOJxt3tRU6Y5X/QulEngA2s9yvjNIkvfFFJVOpHs/lxmPSk7EnY0u7JNptcTF4ebnj86Jfb9MP1rxsOCxUMhmgznpjWqIyO5q2VsB+fJoNcJ2/1XKe2MDsomNrMYAwRmN7A+wBGzN7dyrSqXZeP9dfRx4qfrfqrJ8qBDa8NUeE9c4k7nCORiIWdl6iZqf3If4mTcUQXcnBnG/HbeDiE3WbDoxW4AjdZFIY8PcrUmt/LB3mPNgozQe7PpQGLNsOfyiCeu+r6fZ6VzPVMIblTkzaFTb5L6QSj1AgjGsylT4jGZ8EPrrBOwNOtx69pb4QIE1kaDgRz8EuAt9NX2e5+iib/Lpn+y2H70shSaeuZHPp50Ouy1VNAa
*/