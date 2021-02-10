
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
N7mKtnbI7BSN7xQFq2RfrwYlpK7n/SY0UTwWsRHXYtMmQTBbA2KPab7aJs0G6hvWEs81b8Q54m1sEt/axHjg2g79H8bFFxhHn8TPB8u5uMK5+DLn+/XlAFkXV1gX/8M6RA6BFN8GvAKMBq6PIVQojGKDPMPfI/WSyHwour7hebMzMD12ZpMLC8DB3mAj35vWcOlFvqXD5Vta4Vvahu99+nKAfEsrfEtbreV7Xs7+eD2XlrgXySQAPl/Ju/wi7/Lh8i6v8C5vw/s+fTlA3uUV3uUted/r8vbHvMsrvLuDzbhvKl+UF3FXDhd3ZQV3ZRvc9+nLAeKurOCuvLJ82XOt95oSRokZZ9emg83hu9iOHeeu6p3sH45oG/BOKt7jLVzfSYl2vJXWOykqjrI2eKoHoDX/Wv0R5TyXiYs/YptRA4rdATboJMBhhmPR49rtKnfSbjcrMHT5SI2dzHAOpWN4Mm+qlBAvw3lun9XEAabBDJ7GNzmk+sYIx0VJVDOTwH00qEt8FPVEn5jGz9CPjzsiUAMeP7Av7lMIMAlMjGCzisjURw6B4p31O2NBBwoh5pSgkTHEUQjYF39omU6cFguPMZx8yuU6rerPUkEvN9p6XasVrs1J4DFpsRZmCMiZhLGYav5ns1WoNrQ87BTM
*/