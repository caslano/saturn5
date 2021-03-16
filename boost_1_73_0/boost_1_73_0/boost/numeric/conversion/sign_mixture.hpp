//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_SIGN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_SIGN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/sign_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct sign_mixture
  : convdetail::get_sign_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                  ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                >::type {} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* sign_mixture.hpp
yOfCIEd8munPwGHAvwDfBXwTeFigT5FFc4AHgAuAgvZ7CRC20ZXAIpAPNFQwpA1044iIj+hUAr8IPAh4D7AK+G1gfyDm9VINxHxcaoB8aAfnEGGWJnVAzLKkHogghr+8iErAwcB64BDgIcChwDFAnHPUCjyY/RBwBHAGENcQzQG+G3ga8BDg2cAG4LnAUcBLgYcCNwNHA28G4pqju4GHA+8DHgHcBWwEPgo8Evgr4FHAFwu60UD0BvBoIJe3xgI=
*/