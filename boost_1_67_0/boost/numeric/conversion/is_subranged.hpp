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
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
*/