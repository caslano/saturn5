
#ifndef BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#define BOOST_MPL_PP_RANGE_ITEM(z,n,_) (n)

#define BOOST_MPL_PP_RANGE(first, length) \
    BOOST_PP_SEQ_SUBSEQ( \
        BOOST_PP_REPEAT(BOOST_PP_ADD(first,length), BOOST_MPL_PP_RANGE_ITEM, _), \
        first, length \
    ) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

/* range.hpp
1G6GfnnXUtD36GWqBm8P9NqMeb8vc0PolcdaLJZce7McVbZ/c9JAI7T98tqAiWHEFmGj8GHRRq450yd4gyFtN+QK8cnhTxQUdbdrTvTvANV44n8uDoTjHt1JsZ+9nZRtlXiTshvu4CVMSZFEgkHTTsKgWck2a+Mi0xpAp66znlT9Z7FtzOqfjpsu6rO7ZGJ2hB9yXhtJJ2SJbzOeyiYbEQypewzk5EfqvLaIoI+K1NWcnCVqNTMY2djcfHP6Bxyv+VpQEAO1My5/8HEz7eDNH6r5JUbSNMG3twe34bAbvFHWXkt6ooSLqrJVTWEVYANXrzmdmIPcYwT7wcviE8S9yM8MHny2efZpHAYbRM92WG7r7CL/dhBkH7EbH0BXFCN7t8Yz1heeGR7+eJAZ/vh4MDi4SMtkB7NzgEXLmtirB3jxeiaQioEVOnH1mytYqYg2qI5nOvMR39SXZK9mJEhuLMYLgg34ez70fmK3FuE+17DUB+Aaxp+xPH8e1molxJ8qOnBqvPXkZzY8kLCoZbz+Q6q2Eu8PTNhhEGx1I+B8jNmPKKGvBIfatcoP5j37eY47hdos2rA53nHTk/mIgPUPgR8bfUnaPPuvfya9JJHouksPmNLSxSxvBBh53MywrCbQNKmVT2r7r2ub4COtfcQsntn/9HVp5kMEB3uYvk0VMtNFvGBkvPPWgu9YDK9VdNrxkkk7MDPNc9XuHpww
*/