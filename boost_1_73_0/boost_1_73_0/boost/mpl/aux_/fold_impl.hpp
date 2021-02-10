
#ifndef BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

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
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FOLD_IMPL_HPP_INCLUDED

/* fold_impl.hpp
Klut/kaz4eL736EHb96AymBvDxff/QHstzU+24fXr2G5gTk1JVNbthkvNZr2N1uOgrDV2GPr/1r/BFBLAwQKAAAACAAtZ0pSXt/nDL0DAABUCAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMTFVVAUAAbZIJGClVm1v2zYQ/i7A/+Gqzq1TxGbstNuqyi6COG2yJU2QeO2AYRsYibKISKRAUnX8Zb99d5Rkx23XDStgWBJ199xzz73YsRPWJdyKWRBLlWm83In1SpvUzoIL4Xgh1V1wulhc+S94e7IIYrY1iVnjFTwOHsONMB+FGVqZiiA2oirWaJByx0HpJBfJ3TRcCxvOPBQbj8YwOTiAy5+DOXcigg8i3ccT+KlWeBlPYPw8ev4yQpO3F4ugAY+ACA+tf2AZvxPBsVZOKDc8F2rp8ggOf6AjJRIntYogKbTdGi3WlSCMe8dyVxab87m0lbaycclkIRQvxZS+kMn4FSQ5N1a4aVYrtX4FuiLLqXWGq6UI3tDpMBc8jQAzxE9AOXFIRSGRqEghM7oErsCraITVtUlQJUbykIytXF7H40ISp0bHxD+gSZPzLMidq9Che4wzwV2NiLOAeG+LFrPtG4gplW1FodAJL+DXi3Of7P4urX3I
*/