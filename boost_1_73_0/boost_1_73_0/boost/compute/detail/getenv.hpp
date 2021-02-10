//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_GETENV_HPP
#define BOOST_COMPUTE_DETAIL_GETENV_HPP

#include <cstdlib>

namespace boost {
namespace compute {
namespace detail {

inline const char* getenv(const char *env_var)
{
#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4996)
#endif
    return std::getenv(env_var);
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_GETENV_HPP

/* getenv.hpp
3uSp+wniHLiMtLErUagPfCXja4txTs0LJLaQggtZtaYmddAL13ba8N3NyjtlKlc0LaR3BLFWdRIklwrNvEOcd5z1l5IFp/zocEl/cjQ0jpPk3WhyfjQ88s3uODgXo2TqGbo0KLtaQFs08FLkSq5pML57wdSWVqUksozvNSE1H8BkldFWJvPQrSLjd+MixRbW1qD2c1IlJsEvhADpRqx3EP41GvYH5wh278CbKKLan3T+SrttF8xKGJmjDd5y323/+z+d47gEo9s62Rwu9KfmPN7d3qG4o+Oyn9HKPx14feJY7mHYfbkbs+z/n2SN4+nF0dA/rvqT670S4Vvhw+qAEISyUHftUCk2B6xmntcFKrjfde6jSskl5Bjb60n85m1/OPUymvSnV5Mh/RRfXvWjiY87x213qwvS82quH2E4sn6+Pxv9SO3TDld0CcT3nCzcIlD2olxp2VSG/euTbVzUou5yO+N4+nBgZZP7oPL+P+O348u+v2nSHiqbft/89pdM+tv2+tnu8JRN94ZmyGubr6KHtaJLreZRSb4XuL7LHup2q0un3oTK23+yaYf+G+2uoaEXfO9HDl0sHroIWu/SX5oOEuweWyZoB2U2b7d23YYj8Wd3c6OBJozUW4l296ODiV+j7SS/fZ2q1gzJ
*/