//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/conversion_traits.hpp"
#include "boost/detail/workaround.hpp"
#include "boost/config.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct conversion_traits 
    : convdetail::get_conversion_traits<T,S>::type 
{
} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* conversion_traits.hpp
PgjcA+Q49zCQJfYdINP8LnC96Ca9EbfPeQTIxY/vAznGPApkGf0wMB62RmIPo1TWjcuuVK7bSmV5zOntc3p9r5Dk3Cv2IbpXR7bzNp5X7XtL7xSQ7XbebZzJzLuNPIfSdO2Cd64S39HsEgC6Zc5wjK8NFdNGQm3pxtc4El4osdcZv+KYtF4lXpuJ1zZKHEfEXneLsJ2mvY5RBfsbdt17814X9xCTpM8DbkYHaRPfrQaCoVuy+MHoRhMZz4p9rQE=
*/