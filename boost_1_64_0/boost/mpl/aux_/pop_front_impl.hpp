
#ifndef BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_front_impl
{
    template< typename Sequence > struct apply
    // conservatively placed, but maybe should go outside surrounding
    // braces.
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) 
    {
        typedef int type;
    }
#endif
    ;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_front_impl)

}}

#endif // BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

/* pop_front_impl.hpp
bsFPwaU1Bi3BLTAjIM4TeQX8E/OLa1H+T30vYux8/JjvNYK7eoc0cKN9/NgvJYcLa92suSvY7O9ACI9R/el3LtJo/Iklxdqcb52QQrD2URNHvBKC4ZFnVghLG9Y/U6WmyL0itL1d8cNTGgcL5lkVR3zn7UEZ3jWlDxJ5rAzeKBkeOZHgVgzCJu/MIrdC0XiARgYmhxcpidBrqvGMEzxUBB5O0RBF8kyLMjaWvKTFUZ+/9kt/D1pbNNyx8iPXhdtnQqDIrLbodXXue/E+6Hj69UoEfAGP15d5z90Cfm3yXr4U0ADdeKYYh1W8Nt4VbvS+PwGTrgh4ibjsd+VVh1wvCzarzXm/cVvIKIMzLbfQUG5Onlj+uXWxBJoKTOvnDF5cl39sTJM+B6IA3Y0YpA8ppg/1ZxhiaXQCeV4P44oaCgwG9BxGJ7F1c1eQ0o1x3RtIuN8r4vk9/QPLGM/aDMQYOAoNueeSOEQmXx/KFWIMVV0hGBketWCe32Z45BaVOJlMheRN+Nov5MTMo40+fuLiOVh8wxwnjPtxOGFyH40Cc84wT8ktO4bZjjxIAVm3KREepoKexeHJFBwepqhOzRBmVPB6C2008mScft4yDRgHCg0kgJQRgc0DgTqlu1dHShvmPIWwwvS+HfBIgHVPgsmTp0OkkcxDnay4UFCzb3Ah90LGq7U3ckpUUcyze0x0tVbZ6Hk95tZOJh/SHLizh3tja5wMImTM5mo7mSaPURF2Kb4D145VtE4p7xnQ6qMlmkWY3MuN9bkbGRelT0eW9KfyLf3zNlp9k20Gjtnz6V+w144sL8oBpeByErT0VuI/tu6kJmGPHor9WYN0yL7/782vtO7n7Rdn1IDMfMeIEZP9VIyVlZGpIiNauLg0N9Vl5p+pDHstk5SpnNylV8ryqtjj2AvQ/BvtfO9/c36d/s35Df0356cBAOJmWtYWzQVSx2Csj8NYnw4beEZ5UeoE2MyTYRfPAJ0KOxiYCXj+inkGpMEvmgbZdMT5Ff6Z5UU06KBZ0J0Bu3rGn5sz/0znE9LRsHbCrzWhS/H8oVQtKYaJFW1sQDPGsyE/R44BrbOZPbS2MrnlKNhDe3Nadx3trKMqHVUTauraVsC70224tt7cirUJz2BDVuDalwsgp4xcyrzynN+ROYY4ZUHngrrrxgGTB/O+6Z/Y0LA7uTxRCfZpFWBVRS6vOpCmq4dpWUtnv/9B3sy7rq209runlaGeP82PKe8/Vn9DWyNv8r58pgz/8rmhBjAuxSH+neEj49BgHxODEYFSzwdicXPmF9vA1vNKNLoRX290GzYeivqxzJXJQyxlvWeHhFnv10GYY2gjzDG0ES7R0AafZWgbymFibEOPUxPomBjf4JkY3+BxjW+Gx7HRkT6pHNtfXFZSG6bvDNcNyhipuKQyELscAvIyJXaYMdSJnT5UbwIzdrj+HQgwA7h8xpjmPCtmwh9KjHNiYlD663jYGniBgho36KthqEdLFPgn092uX/xkzFCKcVEoYGnGH9RK/Wy+Ls6fep5fF4eMidI+z6+PoyQPTJnur3wg7QL2x4vYHwEKbtA1LU25rqX0JS09e+nP75Vxl5F2fnnR32WDouyAiRUKHmMcFp+wlMQfSiSm/NhSnFEhX8DImkQ6f2PsSsB6bLb4b1AiQqEFiRKytVlLlFIoSpZCqWQr7UpJKlpI2UKSJUpCiizRQoksIdHytSotKqlsbTLn/q/73etuz33u+zz/3pl55z1nlvOemfObOdO2TRv+ylDgyvVXT8R/SvvlV/k7LughgdXn+o/4r+/6r35EArUgEMt/pefu+OvtX/F/JS6I//2RIPybqCD8nwR/pf8mpmu67F8=
*/