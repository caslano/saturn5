//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct udt_builtin_mixture
  : convdetail::get_udt_builtin_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                         ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                       >::type {} ;

} } // namespace boost::numeric

#endif



/* udt_builtin_mixture.hpp
J3Ad8G7gBcBdwAuBPwR+AshfdVwEZAfy78AK4MXAMcAI2ATcAJwEhC9HbLzw5WgW8FrgacDrgPxFz2eA/wGEj0cbgDcGZhwbKPE4Rqms6yc3KLfcSmWdpG1Rbq2VyroYfpdykZXKukXyV5S71kplvTPyZeVus1JZviZm8lMl91jJBPDbJA7gtyn3YzH3e6rkp1Yqy/+KuRtUJc9bqay/Htmq3OtWKuui/B3KVVqpzDao94CqZLiVymwnemZVbBE=
*/