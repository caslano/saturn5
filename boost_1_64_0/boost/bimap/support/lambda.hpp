// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/lambda.hpp
/// \brief Placeholders definition to help in bimap modify function

#ifndef BOOST_BIMAP_SUPPORT_LAMBDA_HPP
#define BOOST_BIMAP_SUPPORT_LAMBDA_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/lambda/lambda.hpp>

namespace boost {
namespace bimaps {

namespace {

/*
boost::lambda::placeholder1_type & _first  = boost::lambda::_1;
boost::lambda::placeholder2_type & _second = boost::lambda::_2;

boost::lambda::placeholder1_type & _left   = boost::lambda::_1;
boost::lambda::placeholder2_type & _right  = boost::lambda::_2;
*/

boost::lambda::placeholder1_type & _key  = boost::lambda::_1;
boost::lambda::placeholder1_type & _data = boost::lambda::_1;

}

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_LAMBDA_HPP


/* lambda.hpp
7OXSuq6Wlq/tqnv+FvHsr6wjHP6rpXyxCH546ZK0kqldS0trah0dpxgr6G6E6EelY/6+mH/ma1S9V6P7UlFi/NPyo26HmfUPbhfzI771Vidxe5aU59KquprLCusu85cGy3S5cTtE3FZjvk3Mj/rupPanmrUbqG+lbOu0xC/u5hh3g8yaD+vE/LjvHlIp04S3dFkdjQExrdVAY//MbrN9pL+Js0/2pGvA7Lgz24sEnRl3uS3cMTfKtadQSelCKa34peV1+mrb7tOEtKN1KqX2Kqt3+F4xWhc2i7/3+dZZPnddkvtQDs2+dwn2fVx6Q3Fyj9m+QdYMbMdbd1rz8XNKt+BcpU3ibxH2OccvDnVTT7jSqH0xcg87blOpGynwNK0becpi2SfGqTOT9fcU5Rlaf86EUzPbstdkfDfCYHQZ04P7Ecr8fS2fWpfKTX0JLX+Zut/ZWVL/QsqX+LfMrF/hlJ++nG8w/oWVD7m+xlwPKwdh+4SqLoLWVfKlhR7FtAQzX9XKgJ8gfsK785uqa6Y+F+K0uqTU1QZXVLnafrXfz5SVD8S8x+rvveeauskydWSfmN+lpvpc7SZuFtSXWS59x1Ovse1dq+Va7bjWTUmFxWKnnvv3c/ZPI8xYM8+Zu8VOrGmPP/6mmI3+a2EKeZfZvjUNrr0mTP9V84r0irRv2pe050bkefnt7/dt754bHv3xHv3Q3v3uh6W//KJPt45/efBbnS9suO3OK6//7Snt36PDoz/eQ8+h/foVHuMJHuMV3v30gXX+9V1F38sSEPc6/99U3YVrYD+dCzwSXg/HwrVwLrwBzoebdO5yIyxUXYCr4M1wpV6/Ad4Kfwxvg81wPXwOfhfuh7fDj9T+Z/D7sCNhuwMmwx/ADLgR9oa2vQHwLpgjZp2zap6LvA9o/PrrvHFL5xKP0LnEo+FkOAlOgafr3GXEOguWwGmwDM6GS2E+XAcv07m+l8MH4XL4MFwBn4Xz4Ss6t/t1HZf4t45LxPkCc7v7wQvhBHgRPBUWwqmwCE6DC2ABLIW1sAxeChfBq2A5XA0Xw+tgJbwHVsFfwktgM6yFr8KlZg61to3aLie0mEOdofmfCXNgXzgK9tNykA3H6Rzgs+BAOA8OglVwMKyFx2l5GKLlYZjqbAyHt8Ac+HM4XtPtZPgCHAX3wNHwfXgi/AccB/frfTfEWtG12aNrs0fXZv8/Wpt9GWNoG5Cm6Fha9Ige0SN6RI/oET2iR/SIHtEjekSP6NHmIw4p+xLH/21UViywh/+/8Nh/jmvt//IYS45JSCoyEUkYwL/LAmP/c7+eP392IavQLWRASsf1OgwIjPkUFpsxH7WfbaWKmV9izmL8r6uM1yW0dLtAx35C3WJ23MZbqeI2Rd3q2vgyuKPj+W63mB23PawY0kTGkDmWif2vYz9Wrp8s1zrJuOYCuTaXaz3lWoKafdZJYo532S0240Wd5Vp37ovZ3Le3lWwltXnd3w4yFijpKOdS3OcWBM71MuOCEu+QcfVmzbtYyzm2cCU/kHez88+cNW/ezMKF/noGImtL6+r91hHD5qw/7CzQPAbprPwrrovE/zVB/0sqSi3XmpOMXtYWLyp1xgPVfk/La214ruscD7MmZUWVXi93rpt110ZmHllfxB5/+464Sxk0c9YYGWPNNeNvGkazFlvIWuo6VmfWVNSwnNxtpfjHOi/dA+a1av6sd2i+DO2g669zcRisgLZOzEaxvzKYbhW1taU1SysW2sGQMvZJf6mRVqqOQQ66PLBG872U13Fc72KXwbiiMPdDJkwoGs2/wrArzhqyL8i9Z1jdrMGSzpdIGHVOh47T/kzuN1nNzBlY7uSbFH9X3esGfy8=
*/