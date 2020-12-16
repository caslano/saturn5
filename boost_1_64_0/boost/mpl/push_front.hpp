
#ifndef BOOST_MPL_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_PUSH_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/push_front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_front
    : push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_front,(Sequence,T))
};


template< 
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_front
    : has_push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(2, push_front)
BOOST_MPL_AUX_NA_SPEC(1, has_push_front)

}}

#endif // BOOST_MPL_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
dw3EdNr90/tsUDmz+9AOVRKTiBRr72caYhatLdFeR1qIWbp2lvY80hBzBTXIL1hD1fbtzC9a5d3kaNe7M0rM5cXaikyTmMtLtMUiLcRcPksrl2mqnV9QT3Xyi+pYzPr80jqIyQ+shZi1gaIVEHOFElO4aoU3JaTIMMlYW6ylmWWsLdH29zHJWDtLC/ZRMq6iBvms1lqWcQ1kFGfYI0VcQbOfPiYRV5Ro9/UxibiCrg6SaaqdX7Cc6uQX1bOIy/NL6yEiP68OIlI/r4KIq1jE8yGiOO4uB6EowDpMgK2j82+Km/5EtFjLNklZVFeiOQwp1wgwUTUG7FoTYB2RYq6iEdRtEnNVifak2yTmqlnaAzJNtQn+VCef8LiJVJBfulyIuYawDDHryXYg5poIwNp1eNqjAGtXnQnzmeRWYsJ8RrmVmDCfQW4l5lplQdyZtSbA2q1iwsDfzlBiwsD/nqHEhEN4Rqapdn7BKqqTT3jcRCrIL10BMfmByyHmcjISiLlWiikvCJD+Lqo3k1VvwjxKM5SYMKeCDCUmzOnMDCVmrQAUVePerDP1ZrJVTBh8Z7oSEwbflq7EhMHvlmll7bB14eKEmLWEZ4i5guwEYtZGiJkibzCIEjNFiQkTuS5diQmTujJdiQmTujhdiVknAEXVWMx6k5gpVjFh8/0NMWHzyYaYsPlP0vS0MniYO6kgv3SNELOO8AwxV5H9QMy6CDFTdaFSo8RMVWLCRH6SpsSESf0wTYkJk7omTYlZLwBF1VjM5SYxU61iwshHpykxYeRDFOF0OIVMmaba+exH6/IJk5tIBfmla4WY9YRniEl9XQ8x6yNs06FboiPKNh3KNmFCa11KTJjQcpcSEya00GWMmcqK2DZXmGzTEWPM/IrLOmae7bKOmcNdn3vMvHZrmt53aVG9maZ6EybyRKoSEyb1e6QhJkxqNdJizBSAomrcm6tMvZkWY8y8KtU6ZhYjbYyZU1I/95hJt2PoQqVHiZmuxISJvJiixIRJPZ2ixIRJPZZiDJsCUFSNxVxjEjM9xrh5c4p13PxeinXcvDzlcMdNk5gZ8vqOKDEzrONmKNk6br6WbB03/5acwLiZEWPc/FmyddxclGwdN29I/tzj5rVb3bpQ7igx3UpMmIjTEBMm1eFUYsKkWp3GuCkARdVYzFqTmO4Y4+aDTuu4ebfTOm4GnF/AuNlHF6pPlJh9rOPmYKd13OzjtI6bBx0JjJt9Yoybmx3WcXO9wzpu1jq+gHEzU93EosSUOdZx8yyHddw82WEdNwc4Ehg3M2OMm6/brePm83bruLnR/gWMm1m6UFlRYmZZx82Zduu4OdluHTfH2BMYN7NijJuf2qzj5rs267j5su3zjJu0ebiqcQpNrYMv9ONZ9Xp5AHsdSmxUgkxxAHtdrHxXzPyITGNRa51/ev8NtMfUmL/m2KzzV6fNOn/tSDrM+eufk6xj8YNJ1rH47qTPMxaTbPKc/zqauGM5cz0yxTn/dbHyXbHyIzPlzJi0xICjA4PGLPi9LqdlFvwK0sYseEuX8/BmwT9FQ2NEvxVpY0S/rsv5OUb0I6ysnS1Ruqql/j/ktMymH0TamE3ffch5WLPpb6OdERV8FWkjKjj/kPMwo4Lzj7yqaJ7OSqJomG2xgHQFt7LsoNIV3MptSENXcEPzkBaxBXxMLVXb9yL7mG2ODyVlx6NmZcExnqUIZ8MxnqwIp8MxDpBp5RXhE1lpZGs7HR9RbEEgc/BhQcOReZ8TuCLZ5H0W68jx4NXHemSK+yzWxcp3xcyPyJTz7wiPBcfxrU6nJUKZhbQRoUxDOn6EIlYLrMqCK0zrVMqCK9z/mVIWXGFQppUfhBdEQLY=
*/