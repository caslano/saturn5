
#ifndef BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

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
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX iter_fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

/* iter_fold_impl.hpp
/wdRnj4+fF18vYbjQpj6kNIg5HfaTbqpP/lB8M8fFzef5o0kobu+rBZls/j5L5jCu3cgUjg+psVPfwP7s4vDTuDtW2g3SDilmXhl23AtyXTi7sEXuE2Xu0Kx7r/uH1BLAwQKAAAACAAtZ0pSqZIH86sDAAAgBwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMjFVVAUAAbZIJGCdVW1P40YQ/u5fMfWVO5BINjYhkJyT04nccbRwIEiPfmq1scdkhb3r7q4J+dLf3hnHSeBaqdJJke2dnZdnnnlJ4tH5VDqcBInSuaHXI66WxmZuElyhl4XSj8GX2eymecD5p1mQiJ1KItZWwZvgDdyhfULbcSrDILFYFStSyKSXoE26wPRxHK7QhZPGlYi6EcS9Hlz/GkylxxHcY3ZIEvil1vSKYoj6o/5wRCrnV7Ng7XwEDLjjmoPI5SMGZ0Z71L5zifrBL0ZwPGCRxtQro0eQFsbtlGarCtnHsxcLXxZb+VS5yji1NslVgVqWOOZH3Iuj95AupHXox3mt9eo9mIo1x85bqR8w+MzSzgJlNgLKkH4B5yTBL6QHtzB1kREHHuYIGRaKsGMGuTUlSA0NsRadqW1KxAlmjJltGWyoPSsUw1xTmzYHUlnT
*/