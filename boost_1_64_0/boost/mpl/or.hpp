
#ifndef BOOST_MPL_OR_HPP_INCLUDED
#define BOOST_MPL_OR_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>

// agurt, 19/may/04: workaround a conflict with <iso646.h> header's 
// 'or' and 'and' macros, see http://tinyurl.com/3et69; 'defined(or)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'or' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(or)
#   pragma push_macro("or")
#   undef or
#   define or(x)
#endif
#endif
#endif

#   define BOOST_MPL_PREPROCESSED_HEADER or.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(or)
#   pragma pop_macro("or")
#endif
#endif
#endif

#else

#   define AUX778076_OP_NAME or_
#   define AUX778076_OP_VALUE1 true
#   define AUX778076_OP_VALUE2 false
#   include <boost/mpl/aux_/logical_op.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_OR_HPP_INCLUDED

/* or.hpp
+iFzB6Ch16F6LW8vk3wZpjkY4OB0tgCHngoiZw77+EMOVYg3eiwpQRLlh/VXuCJlCFLCAO/0tZGBbrIUoVp4hqd8fqauOv+y5KY82z1St6hQT7ro6RjWuz/fI40k0QmC+6zqUVwgt+Ck0bKa21Z2xpL1x+YJCLC5FJtwzVRMKbMMlAs9DFtPL83kH285CGCuixO6ATDcxgntLCvmG2e0SbL8t0iyhOa/ONmkc2pI/YSUaMo4Q1WBw/jIHCoeqrNk12gj1ZFTJwGbElVjpbdS1Sfh+FCtH1EanRb8DJL4io6/X4NIcM4R02njZwqyxoE6TRrrLIzgPGeryo7x2lFwg846zaNGcsRQF3c1w80kZrsLyWenU/JbGiwrP8W3QfWeCC0pw6ewaIZDxRadeZ859oA+aIYHrfvz0EbuDdLS+tyccvd2mxD4BiGXz3O1SzRpHtk/9TN2hnSjOlTf0T85M9enUNzyaTyPJcYXmylQRJ4xm8QabQC1Zkir2SIf2WlTglE5iVZE4URzrrXiErmWWaNlxEszMxgM/oOgP8gay1VleSPzcOifrJmOpg==
*/