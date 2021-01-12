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
IYL68tK9jXL6f1rOklU9nVvZ+j1dHd2NPV1bZdx09Uj/s8ztwT/andyaRbcttUw4g5LQJo5RsSWdcL/G1f9LV3c/OdW0rG3V4Eac68GSdKsGuvVU+b1x1WCeWT25pSclJ1snYGBCsq3BGdPLA71e9kN6mreyF1TYH/UdnX2SB9WqlrwVrT0tvVbscFt/jxYtVi+LEOkaW5Fa8mbZDVuR0qmOrUjb2D8BQD6f/OmTP2ny83wd
*/