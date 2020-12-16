//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP

#include <iterator>

#include <boost/compute/lambda.hpp>
#include <boost/compute/algorithm/transform.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class InputIterator, class OutputIterator>
inline OutputIterator
clamp_range(InputIterator first,
            InputIterator last,
            OutputIterator result,
            typename std::iterator_traits<InputIterator>::value_type lo,
            typename std::iterator_traits<InputIterator>::value_type hi,
            command_queue &queue)
{
    using ::boost::compute::lambda::_1;
    using ::boost::compute::lambda::_2;
    using ::boost::compute::lambda::clamp;

    return ::boost::compute::transform(
        first,
        last,
        result,
        clamp(_1, lo, hi),
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP

/* clamp_range.hpp
i/Cmwfn43rB+ldE9EwZc/MJYFi8NVfcbT5/nHhiUYcdIs1/KeGuYx77y1OjuA2a/+Natgo8Ppp63NQPz/eZsloNdQfLq0fFNx0ltBjdOQGUSJ8f+7zocMU1V6GMzKv0YYSgokZbeO6N5J9NMTSaHzLjc62Nqr4n4ikTwpvjUJj4i12lRZ3OyIFhDbaI6sKdzcNSzpQXq6mHca/S+tzvMidnDeBe2iW0fmNhTtloufnCZj1Gad1/hnj6G9nlxSvKvtJ67tm4qnbehp6/EIoSbhg97awPFf2d5tgq7nU9fyOHgAVnQGBsjN57matzTZe6Sy2UcaNYSI4Pvr3+04cMTTschORyaa/hI7J7HqZDPJQOjZEaTTUVsc0HbMzg2ObQX1ZpG7USnFbfrHwRRI1PlgWEzKvVWTtq86ampMjHtEycHtd6/CzlUBSI2ykfGXY/THCFdQVLX33p4pTQ0kDQHd72//w+K0woMhBp4+Tc8nMBgKq2hyn/uT4LjH3xpqGzrvC8BZ2ffWdu29/TtKvVsPWNbacOmTd07dqSqgmwlFnluey7aW5b45yB50rUqw9uPCXhnd+/q2Ryt0/TmcijN0/P+XA4lGV2HKHRSJ7Nxw46eTaVN27YSkG3o2donbVT9ODmf12yfjB/5eQVjxAzrznDOKA0NDhEYDU0dSIIYeW6Rw3cPrjtFGCWZ7x6W4ixruHsPuHuTJRYrDw36ecvYeXSKK6bzg4W7W2wyv9xkqcOT6ihBnqFc8eX3sljT9vaWDxgw5285K9WA9Zy5decWfz2j/z7cw3UUYPNmgmA0gTh2qlwhZ8dJspzdA+OjYxSg8sxwwniknsHpjv1aj7kMzrA8WZ0cmhxTfbxvhlPBZljo8eZPASf1ur58ewNc2lEVGQZ4OE+thdjIZKU6McD8zk2MJDa5X8BD7bwxO8Aw9+qIvV/9Wz3kTA1cIl0yKu3oiDnjA3vL6mfnM3gyOVVVX7EQ4GjM1L7RIWmKtmVmq+MNDA2V0UTq4DBzQYgRREpf1U5c5LDKRCtmpz/Lu0f3e/HLQpZTmd4dcnpPCjiVvHxqGY7mI/HW011dhxg5B4nFGA2mxtSXP8PibqAeG9iDvFWvHq/4ZKXc1DumzCqnfsGZ2EwQ6xj1R4nmTXDW0vvSVLk6dYD6OfusKYdq6bx37v3+dWTErYxR/MdiC5MJiROyvEummpO+PdMDUwMT1bKnG/VnBtyEeSGdbsour44PBDiaF5eqeTXCvC5xmYm+X25xHOXg9B6RPpCMRx23CWfP1ACx/OQEhlkdGCuVp6Ymp4yT0czDhEcgqj5xLriOR/d87UKIMc3wnmE83McIAYaJIljzln7Lw8keaEraV8zhUIy/5lh4lnCIZgjGRjXenRfd3d3SXj/GnHvVCsEGByrldaco1jV5F8VQ9vKUh71V7xsaTUbAVM/3631joxPl9F6Ny01d7x0fNmUZl56s900wmeOhHHqgc4Ha5R4+PTbmx3xzH5Y80aCx0VYUxb2u/7sacu9wpvP5yLj+A49XGZmcHhu2dqSy7nq2cOiL1kMA1R/FcOvq85Pn+NdLaKhX5uMchkk5P5dav853n+txVMOHxJ/n4TwDmdrj9XXAGUYA3vMmH8PJprDic9t9nGGJJd4EXGwguL8Z6eo4UnupjzFUgQ/jx0U2fT6eMIaoTzXP87C0J0p8U9nl4LiRyuSE9xzS59Cp09XhyUsmVHcK53r4CE0bPMCYq33a799f8fyS2OUIApNhTeX9fIuL2Zs9okNXKUZ/4dcUMxdZDOupVMsT/n0zxwk2Obl3OgnyfJnDxmlHS9HEdychRkOiQQpbkvXUHC4y5eG4+rVaDods1Cc=
*/