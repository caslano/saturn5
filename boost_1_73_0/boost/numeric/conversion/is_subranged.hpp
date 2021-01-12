//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/is_subranged.hpp"

namespace boost { namespace numeric {

template<class T, class S>
struct is_subranged
  : convdetail::get_is_subranged<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                  ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                >::type {} ;

} } // namespace boost::numeric

#endif



/* is_subranged.hpp
Nnd327Z8Q6p160U5Yd2D69eq5nF+q2/t6H/IYKWoo2NFt/y3vqs51dnVM1iNruZi4Nn1/QHTW18Tzas7eqRiVw+2EBVKeE17u2Smq3WwDevqVe0NbbL3NNinV1Zhd2/qf6nDCg21olci0rZFSm9Pa1trz1orBq++p61bekXrNsnpFSR2bk9zoxV/uDWSFM2b6hUPc3dqa6Q0twxob9kKbmvumrqie1vEdDc3yjywNRLkGECD
*/