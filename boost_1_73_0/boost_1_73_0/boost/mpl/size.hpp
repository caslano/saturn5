
#ifndef BOOST_MPL_SIZE_HPP_INCLUDED
#define BOOST_MPL_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_impl< typename sequence_tag<Sequence>::type >
            ::template apply< Sequence >::type
      >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, size)

}}

#endif // BOOST_MPL_SIZE_HPP_INCLUDED

/* size.hpp
FpoaT9D/X/l6L1Gp2qZ/YIY7QP/wUqy+hBsJZwTrX5GnQr7h2ldVMKW4sNKXV4n8LHlkrJBgmMMnMYI0YVgEuJvmcpEqNtVtRpMTSLY+IgKSIq2avBoUGFPNT5dwUbOswOB7/BCm8BnoIPie5qooxpZQRES80HXgC/M73iNFqBniZvq7XRZbKxOh6vP10qmc3QXfkY8OIb+ptRga0d0la3zaTrDZgM3YL/wf8Aw2AzZip6K9RjYCfHyd8HrCNwg=
*/