
#ifndef BOOST_MPL_NOT_HPP_INCLUDED
#define BOOST_MPL_NOT_HPP_INCLUDED

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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/nested_type_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(long, C_) > // 'long' is intentional here
struct not_impl
    : bool_<!C_>
{
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct not_
    : aux::not_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,not_,(T))
};

BOOST_MPL_AUX_NA_SPEC(1,not_)

}}

#endif // BOOST_MPL_NOT_HPP_INCLUDED

/* not.hpp
nlXJmAME+GuY/fiWyFNRe9lSrsVcU5mnS6xdKFNDJZqMahNhJiu8I1LYqTJtOhAuaqzTasp8NoDbb+xIlw+yTChho1IbLba34PY6l+5sxTewcOZexboYgNPdkF+N1IMTXRmBr9l7cGW7x/Ynlqwd2Lws+Ob14eX4dHjhtWYUuMW3PPDWdZ3a/1w75Gv+Vnmi5+aZI32739iOMs5yNcFRi6y8F25rp2x3bceNWRC72q0dnK09SH7vag8Kl+bpn6XZAzI/i7MHsslz+TzPHsRtJIpVbNaPzMuUeJC+CrAHCzt8dI1RE+fLR6eyCfXbtb6Fyw/3bVO8Glrj2zQvbMwqflu1v5jtiu2tm/LTjeJ85dwGGPIn2/P1X8F3UEsDBAoAAAAIAC1nSlKxfoJvpwIAAAoFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTcwMVVUBQABtkgkYI1UXU/bQBB8P8n/YRXES9TjbDeFxnJTIQqFFkhEDOoDQjrsdWzh3Fn2JSH/vnv+IFBUtZLlj/N4b2d2xqHB2sSyxgkLc5VqujzhdqOrpJ6w8yiaNSeYTedRcyd8FoodIhTtR2yP7cEcqzVWvM4TZGGFZbElQCKNBKXjDOOnL4Mt1oO2rvAOPPBdF6Y/
*/