
#ifndef BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
#define BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
    
#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) typedef T name;

#else

#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) /**/

#endif

#endif // BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

/* arg_typedef.hpp
/wJQSwMECgAAAAgALWdKUl1Wj5ZMAwAA0gcAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDAzVVQFAAG2SCRgtVVtb9s2EP5OQP/hoCJfiiq05DRbBMVb0DiNt7RxbSXF9mVgpJMlWCINkUqj/fod9RIjGbpmxWZYLzyen7t77uE5MqhNIjTOWFTITNFji+0XVad6xi7jeNnd4P08Zhe0WJ6tb9nF4mrOYru0N1itPrGqKU2xq5VRiSpZxPcYEe9h2Sv2CtZY32Pt6SJFFtW4K1tySIURPkiV5JhsT90WtduH5v6hD8FkAte/OuxcGAwhbvANTE7go7qnHX8C/lF4dBKSz/sPscN6/BBsUZ7uFjwTW3TYlSDLB5UWWYHpgONP4ZdG2giEE4T+5BFnHotNCG7gT4K3Xpr84E1Pjo6Do5MfXYedJQnujLcScoM6hLuWgjnsnZIGpfGuUG5MHsJxZ5KYmELJEJJSadx7xe0ObZYPhuemKh120UjZejkKyo0IaC2kw7xMKY8Y7BgamAqeM2WNDOhjVPcA0IjM5MKAbRG1YatpQytIFWoozE8DYjAgTp8jCkjyRm5BZT14jaapJaaMQkDX8qQsqIwBZ2qbPDSz6/K7bnfocu9KLn07Ziw3Zscy
*/