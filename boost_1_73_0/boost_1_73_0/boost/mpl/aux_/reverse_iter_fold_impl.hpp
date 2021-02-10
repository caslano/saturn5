
#ifndef BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

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
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_iter_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_BACKWARD_IMPL_HPP_INCLUDED

/* reverse_iter_fold_impl.hpp
lIseqYMUYdaTsQGSiqcDCP8MhnsPNTZq6AKMMwOX9kaZBEwDHyBZPL2U1fMmAYuQ3N1/Wa74uUvg47cZV387hZ1MVx6H4TeSac5Qq6BANYFFx/riIa3y7AEtzHzrAqscI8sSSORIu5pv6euKFf/ZZ/JKydt4/wVQSwMECgAAAAgALWdKUiKMsXIEAQAAmQEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDM2VVQFAAG2SCRgTVHfa4MwEH7PX3FY+rYS2N5GJozRUUGqqN17picJ00SSs8X/ftHauafku/t+3CWC0FMtPcZMaNPacPzgdLOu8TH7fE/SS3Fkgm81we+0HdtBie6K7uB1g0w4HLpp7q+XhfHRaTS0MuoFBIpfdDEz1oQyf0DRoqTRYUhRREPobAUQRvZhyFNV5U9wyOCmSYGx4DvpFUgC2XWgDZBCuBRpEPC7AkRt+16aBuxA2pq3yNiDHWkYKYrZ/pSVVZK/7s9ZmpTV8ZxnRRX8Q/gqm1d6TL7s9IVOtxM0kiTIltAtmfM7gpIevhENRF5Zipi4Ltxggc5ZV9smDPT8Ehz/YcH/WHz7jV9QSwMECgAAAAgALWdKUskrANAwAgAAxQMAAB8ACQBjdXJsLW1hc3Rlci90
*/