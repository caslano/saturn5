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
Ar/Kq2hn9Ad4+71wYC89xfZTdM6G3pFBnjVnw9KUs+dsCH1m/N/K2fDQfeeXs6GxLZxLpmpPuZkCEeVt6mE2FWCqzVOmxQusphcGtttTPUEpjVUpy8LiZEpZKiq8PsUzkcRz1EohK+emDDr70KMksNWgWY+LxHFkIQrQ9zRrXRKxdwkkL4R6dOBn406wMVS0x8FjsXI2VTLUa2mkRWUKf/v78OnB0tG3yb+Qrbbaq+SjPiNlEKuJoqRMnRIvqFfnUxwF7PB9CP+EZJYpnBuqMVOc1LLWSCoAzPeOFa5gwYvU75H3Zze785ul6gEis+RUGGTp9oK8dEmQx4dWab4bKMR3GjkeUkxlgu4SySLi+I0l+o0cfuNp/UYWv7FCv5HW8jdUndeBgK0NGQtQE/xeSllM5A9ZADqcFScLZgJsTnm9IF7I3rNe6ImK4dsQZqgH1qz9urM42nL++0S8UQhdDXCdlMt0Q2VOCpi9fw/bA2WqeYKgv3wwSX+ZnjxnYWnvWZqEav8geO+WPawwAqVKj0+JNIhOV34TWUD5aAuZ5QTdG2FzYw4IjKbQSxrxaCy9BFVUNBaGlSnmxSCyB7ZpDu0J9OUK3RI2it7w/983BurfuK4g1Mex3mJnbhvliE/at2aWyD8qD8eb3YwRhIjyo4JHK/gjttaedKak1Kzl3Vgm63JmwmXeHBTOEvbxKArfLdJ9PIzZh6LB2kOv
*/