
#ifndef BOOST_MPL_CLEAR_HPP_INCLUDED
#define BOOST_MPL_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/clear_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct clear
    : clear_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,clear,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, clear)

}}

#endif // BOOST_MPL_CLEAR_HPP_INCLUDED

/* clear.hpp
eVnSW7Fac47+1x5j5LGWj95vt5qmU3ED/0dpVflkLsE27o9/+JnaZHI2FmaEZxcWZubnbVmYcDfadtk4Jv9x/HYfP7zfUUjcm3soySaCfBkqJCydmbTXVGMlG9wRBB2p13oYac30VCSdkyKgU63mZ3IFLElalFSZAUJCQpSUlMopxaOKv8QUkijJDmF//tHSiEmt3w3hD45O+ePe6EXXclfskstVd1fBKoYlHxql3vMwSRF43hiw9SB6D/RNtCtobc+4Yt8PFMWrxMfb1reWljKN/ShSmdN9RRbptjKtbXICw3+DG7YawRARta4u/2nHjCkledeJAP75Et/nMK6JaeyWYSFyNOPF7vukwtkISMNs0MB7SeaoYaaB2Ncm2lmmmaaO/Avayan7+7t2B9zT2kfOkflSHDx/tKdD3026ov29N5mEBaqpZHRmTL9SyrWLk5MNK5v4VewU1KpnHCfKyooUbSQ1k8T4danIip4TKgkBtD13YnxQwGI4PCM/f/pXOhbj+6VPONzw5sLXvsPjcr9YoUVtEQyVQgv2FWxM41OHpNtznjY+kpJ4yguE2J8BhhmmZSw6zBOKkTJl9iMjeCsNtdUFfUsTofS4nlokTS5Gdt7eblZQCSuoudeludeYutKYvBNrRP1NN+wzAzWNvWuVNjO+VQFO5fzT/PzpYPHMXsYy/BGu6FDL3JK7F9P5JP3ZxVtHw8I2sINb
*/