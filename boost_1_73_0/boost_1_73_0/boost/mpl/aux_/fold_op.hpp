
#ifndef BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

// hand-written version is more efficient than bind/lambda expression
template< typename Op >
struct fold_op
{
    template< typename T1, typename T2 > struct apply
    {
        typedef typename apply2<
              Op
            , T1
            , typename T2::type
            >::type type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

/* fold_op.hpp
Lo1vRdvl9hGv2GJfxtsN/FVT+A23whDXwu/w5ujs/GQOg1QuqVm7Tb3X1vCQfi6ckVX78N2fMIWnT0FmMBjgw6O/gP2xjcr24MkT6F5gpbVhcudsxY3CI8J/iNuuFJoKtv0j8TdQSwMECgAAAAgALWdKUsA1XnmpAwAAEAgAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDEyVVQFAAG2SCRgpVbbbttGEH1fQP8wZapECiytZRtFw1AKDMuxlfgGSY371IIhl+LC5C6xu4ysl3x7Z0hKtOI0RVtAEMnh7JkzZy5S4IR1UWjFhAVSJRovD2Kz1ia2E3YtXJhJ9cAul8u76gsuzpcs4K1LwOtT7AV7AQthvggzsDIWLDCiyDboEIcuBKWjVEQPY28jrDepoPhoOIKjw0O4/cimoRM+3Iv4AC3woVR4GR3B6MQ/eeOjy8X1ktXgPhDhga0eeBI+CHamlRPKDa6EWrnUh5NfyKRE5KRWPkSZtq3TclMIwnh0PHV5trNPpS20lfWRRGZChbkY0xcxeQtRGhor3Dgpldq8BV2Q59g6E6qVYO/JOkhFGPuAGeKHsYXOBUQ1vIVYZBIZixgSo3MIFVRyGmF1aSKUi5NOpGejWyXoWSaJXC1oVD2g
*/