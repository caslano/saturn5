
#ifndef BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

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
#   include <boost/mpl/deref.hpp>
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

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

/* reverse_fold_impl.hpp
HwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMzRVVAUAAbZIJGBtU2tr4zAQ/C7If1hSgu/KOUp6hVKfMZQ0tOXaJsS+flfldS3qSD5ZTum/v5WcBwclT2VnZ2ZnldRh56ToMGOp0pWhj3f8/DC27DJ2XxTrPLzD3bJg6+UTSLROVUoKhyzlJ2jKh252xs4gR7tDG3eqJJDFtvkkQCmcGCj5fDqHi9kMVr/ZLRElUPT4A2bX8Gx2VJjPYH6ZXF4nBLl7KthAl4C3GnfhwCvxjmxhtEPt4kfUb65O4IqxJ2PoSXYGuZTv5YOvRaM8fPAlw4EgFQrXW6Qh8vzRv1qltdJv1HwqpYNuxmrn2u4wYWOkaGrjbe2mLW6p5YCDVIstpdqpbdsghCh9ivChXA23yw20/WujJFCGcFCElA9dkEqz3QpdZiyOpfCpwyTfLG4fNtwfOr4ssVn0ttkY4wgxlYSIY0+EJTF71v8bvrTcv05LtBCGSjg/FpNJMLxebQp+Mft5SYMdDZ3BUneUCrhaOPjAiL7aPgwARsORA15Rir7DPUTWKN89xtUIoe5HZWlrMZQy1qJtIEYYt1ZpB1FB+waLf3tFK4ASK9E3LtwCGFIONBGoCr5BNLlf5cXDOgKNEM0vrqYz
*/