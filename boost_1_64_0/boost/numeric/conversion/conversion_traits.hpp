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
1Bbzj7Xw61p+RTlEoVbDM1qt7tUWatfa+KLyadcIkXlrcExCj+P7S7clTXJQfXf5EpbKLp4PJnQLXzy+4aVMTaPrlKhBg7htqh5k5AUeU10k2LUApWCIvwoJAS8+OghZBvz8sG99KPqiGUxjA2dAF0RbGoFGjtZ7e6wAiEaS7ti6mgs5JrkXGQQCeWMVy0rsI3vNP/AU00OEFiwvHs24pCfrrnWOPD0X5gBC8xfl+9s4ZnHMr/aqP9Qr7AXXm7emPcQPpuqyWEFBiOdXWfPFUBJAoad+TbVOZHFJximnFDggFMBLAQycltUcmRq+Ye7GUK0m45MD3lHu17AD16pz+RCzg8F1rCFs8VBiJnPoZct3yeLx5JPFq2tWe8s6pU9aGg1BDSd5x0jzkHoTJy9LcALkxLSh3haVkTD3xhhwDhA2d6gx7PPxYIiBe9mJeywnkkPymLbdFg5NrDUxe5SpvW4OcPElgRtC22HqhMDJ7Oh/3mmVpasZ3y2tq9h+fXdz+O8r2h5ndNgJP2Ge5SmLzHs+uYvecpp+C9fnczkav4zNXDHfe3vV6xgLGw==
*/