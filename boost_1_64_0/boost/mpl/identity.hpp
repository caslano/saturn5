
#ifndef BOOST_MPL_IDENTITY_HPP_INCLUDED
#define BOOST_MPL_IDENTITY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct identity
{
    typedef T type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, identity, (T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct make_identity
{
    typedef identity<T> type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_identity, (T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, identity)
BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, make_identity)

}}

#endif // BOOST_MPL_IDENTITY_HPP_INCLUDED

/* identity.hpp
JP6IC56cpa0sEQEclgicUr3IzSbjqtOkaW0LZ9d7TW7lCKyLblI0+9c+5FH0yDOSkuq/bl6Ehp0buHF/9JZ9+ZFBMTgPlNSe5A93/jXccCW+zkX7leWbSdwTT8dvqfQ9twSF4jj837tCOb+wChM0lmchko335BhUOjMWBhR8hCIYsLL71hngJXEGkHaKCA7WLdgDTP2Erbsn5ES0ZaHv8B+fuh+zAgFq4KOP6BcXq7F3xuV6qBeDedGJWJADhILCbwLIwFcrH12NqO0PomKDrlfmKMisGDd5ahRcu0M72ImbG4YVA/eF07gt1KrZ2qE3GfmtESFiLLVjQd8+NxAj+CMW6UFrCK2qtkMJCH+GIzabwx8O3l2BsPPw5O0niv30YoSak8QHxS0o+Y+PZiP3e4x4FOky9uE3Ix86MwLhNmUWY9IxpNfz5VDrgWHw3UBBnB7+U0PbC2YqS3mxZnOhPiI6nosZ0TD8e70/HvAu6FrPrs9Eu5/m623Vtncf9S4kK1kIbUMjlXQHONym07mOv9tw01Bpn8CfJin7AeAZQx+PkRgw9L6QBQq7eQ==
*/