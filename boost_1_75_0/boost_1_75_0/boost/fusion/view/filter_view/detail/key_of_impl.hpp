/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
OyMTe3LPQdvkpO6JfGzn/dSqqZvbCNDqSaMjbF4Fy2t3TCxN18l/iP95+p5NpW2pQylGCfLO6Lw6kTJ5Tt2WEmYfmpUNhUaUfFkWkHsebHPQ17GLdoJIJzS2nSHg+pp25rwlzlTFvjuWHuUhRTccnrGWh6hv3ztlo90gXNKPI0nxLGlV8QMAhvaiOkAt3AoEtiL5SkO6HEsJGoK3AhpYKcRVeeyPYcNR33almkYJ47xdvgYuWVo5FpvsCA34frZnru5CB+87dcUzLUZp5IV3MeI3GE+S2kMjT4NcziwZcq/mSzU2JI5jDm5+1WKh957fjCVp8XPnUnxruWeTG/zVC38Ey1GK71nDB3Kpi66nc4b9ivB4sy1LXBDpcs5zbQDrgVHUZH0WPUUzrLbIaOnaexBCxH/u7GnD35qnh5MAJrcn79uXiN+oTI4U8uDjv9EvXmOmD9pMauxP3XXublLwqqu6QbYGBbvfuQq7/3kFP1wDUUa3KYgQ4emhdllTYuaLZLMy6FepCnn3uvl1iOq9/L6sq6LN38aZuKCQ57Fp3eBHX65liqts/lWSojGzk3Zv6UHiL1L6G6UaLfsWB/mqUM8VoIODnU9cwHJV8eN3aedXHlTuZq2c+gv5FvWDeupAxFOBh1cSW7VnNuyn9t7IEl87pPyluVVU6GNCnnNbXaDc/nIgt7KQ6zvua4U7n4l9ffq4iUS+uFqMzCRC
*/