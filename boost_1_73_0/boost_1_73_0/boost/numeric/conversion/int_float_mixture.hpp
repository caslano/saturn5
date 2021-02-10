//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/int_float_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct int_float_mixture
  : convdetail::get_int_float_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                       ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                     >::type {} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
6joziy1GxJG1pKXNYQhxAFNiEOaAyjyRtmKuPG9M1DGtAvxgatZ4EzI5wFB7cEbDszbNIqdcQB+G03fh+ZQ+DCaTwXh6QeEJDcYXrOz9cHyE1CsYsyRvCisdjFtSi0IrmdQ2n+/ptX5SeazLRFLbS4dUtVsbpIVcJHJWzityD76ChQ7PJ6Ph+CQUp5NwGh6GI4KalsqRTxx34iyytAuebuufFlXctMuFEdBuUhaS3tD4fDTq40ybfE6FNd7ERjOBlcBlsLDYsQjf91sgz7WZRVqoXPkOH4i3o/DPwUgMRqNuxSAjd7s8ZkNLWgPXZyjQxgjnB3tUhb4lFlCRVn8vE8WiYqUJoa78ohrQ+nQuvcpT01n69Fk0Avq5sdatfEo70NAlDgZRWlg4mXacR4HZgNo77mAnuUd7l1I0GJBdoxhQ6UgH+Do7rnuZt4PW9oA8GSJYIsAOWKodTAYbWlGRMGdsBaWChagCZJUyEWsZ5WXB5I9LxKt4vXhD+49gX8cWYatR97l4MdCBf5/QChz3HZ08CfpW9GirHk4G4D4Sw/Fw+kUfmpJw0mPObGQqPJ0KLAFxffbvyy5KIzV20RTSV+evkf/P8vdp6Uf3F7/j+yXFdKuvAYVWxKh6N52esnFT2lj+3wNND7CHlXOC
*/