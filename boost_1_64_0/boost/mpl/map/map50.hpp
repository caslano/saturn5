
#ifndef BOOST_MPL_MAP_MAP50_HPP_INCLUDED
#define BOOST_MPL_MAP_MAP50_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/map/map40.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER map50.hpp
#   include <boost/mpl/map/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(41, 50, <boost/mpl/map/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_MAP_MAP50_HPP_INCLUDED

/* map50.hpp
OudRoGY+vfMoRjOf3nmUo5lP935NM5/eeVSsnk//PKKsUea7znkUrplP7zzK0syndx7laebTO48K1fPpn0eUW8l81zmPQjXz6f6+6c0n59Fxyjk8RtJnLEE97vLBmfZjLydrxyjSGZfI3FdsHkHGHtKMNUQ8BPO4Qj6qcYS0YyDHEKQ/V+mjVd0/q3oMY4fjF1v6YTVYxvlxPL6P9K3qcNxhg/SVGkkaZRDWEPYRCgluo+gXldCHkEhYRMgjHCeUEHyi6FOVkExYQdhDKCS4jWY5Qh9CImEeYQvhEOEcweUBxjAm9CEYCCsIewiFhMrRjP1DiCBkENYQ9hFOE64RfHkBOJQQT8gmbCLkE4oInrHuLu0JkYRMwhrCPkIhwW2Mu0sAIZyQSVhHyCecI7jFsb2EMEIiYREhj3CC4BLP/xHCCDGEbMIWQgGhhOCVQJyECMI0wjpCPqGI4DGWOAnhhAzCGkI+oYjgMY7/I/QhJBNyCHsIpwnXCL6JjPFMiCdkE7YQCgglieX91JZ/yj/ln/JP+af887/++Yv6/0uPS/nz/f8pffYtUI3d7yN96HlL3W1twnal/cxG7tvN75H3iIgs63vBW1mHQfOeXY7E5S5xVSHkMV+WNi5lUKtYgyE6PjYj9gbjlLpxvtjH+RLz5TiKc2xy7Lj0PxefwUEfgS8zX66j+JSeFG9w/yzt4x3s3yvMl+coPqIzJMdm3OhxNOeZeFd5Tpb3FQcRdjJfvjZO3hIry5hz21hHelxsSnTcGMsYXsRvHNNLvc/nJf7qss8ehN3MF5iriT/9z+Uj89hjrmy8rMLS9qCoot4Y3jdvjDG9McX/Xk2ZnvfViMaPxzxXdY774Qq1Lz376v/umGQ6Y4zpjMWuN/aY3hhmemN36Y2FpjfG2M0b22yQsa3IsNg+mydM/rHeqZXzMt92n7Dv1o9hdtaY3976KPKHrcn1i/5Ynhv22V2vUJDDP9qOyG+C/FZEEqcr+qnKHF2ljKg2+qN5uSxZzt3Bcl1luVCsgt1Uy+WUslwbWa6tLNdOtVyuLFfVwXItZLkArIz3qJbLKyW+QFmulcQXpBojKl+WGyLLqceIqidjMNXHxlJG2kzKcrtKGXEPKZvsj01wEN5l2S65rmF1B9vVUbarE3pgCBa4OTeWk+9M1VjhmnGd1OVvfgMp91K+E8IG2o/1lDyLMjKCecynLfwtY4qrxn4izLIb/8kyxngJ/+c5m7gJJUyPYVoif2cSpvH3InQ0RlTebOs4Uef4Wz0ueeVs9pEQSognbCLkE7TjlRdny7hSMl75cfSeU1E1thTrJmQxLZjvW/AwQRnLPEKZB88p88+1jj3V/362Gb2YtgmDUTsOVcRc4tOMR5U91zL+uYxNRVxMi8BzeI2Qyd9ej5rKLYMxBNcoy/K3eVz0Tfy9RjmOaB7H6jx/u82zHc/Kf551TKvEeTpjqKvHt2KeffOQ7+fRPKa623zbcdV3dGW7lGkYiQFMM2Ah31ego7Gw9jF9GvaPID7UjsW+Dc3jsbss4LgSIgnqsdmzFpjKZfegRze2J4L0U/5WymJRNYaW3njtMoaW7bjtAQuJS5nO3zKels0Y7uEL7cfX8hiuHmOLbWcec7nvHv4+T/BcZCoD9kdHY271X6Qd+11/HC5fpmUwfwl/r8CQSPYJI7EQLxPMY8P7LCY/Yihqx4iPwmymG3AdXotkXjxH8B7BsUqiPHaJ7ZhePnzfg2EYzDyJeKIH245RfM9D8zjzRT3YniXW8eYv92C9SzkOrHcNIZ9wjlB5POXMhP7jy8tTyz//uZ+/6PnfkHYTnv/r0Q9IRB1Tf8WuLvEJY2MnJ2dEG+IyMk39+S8=
*/