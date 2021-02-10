/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_31122005_1508)
#define BOOST_FUSION_SIZE_IMPL_31122005_1508

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct size_impl;

        template <>
        struct size_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::size<Sequence> {};
        };
    }
}}

#endif

/* size_impl.hpp
xTtsMTYwb2hBa8WQdrorwsBQCan0VhhPyTyMpomfWE5dWr+wOudtQeFEh+84WX20TKRcoPxxVkN9Am8qZAtH0jybkW09Pxu4qFewEqSipBh9MEmdeckk9qepH4VWgjdbk8aoLUp/JbTiopzqu0fWVGmGCTgM9HtNvqJmj2UusPS6pfpAw2GRFh2hLCcaShji3WneboiUW9EUowdobVERSsG52DKMy0Vng4Sj13iijy0NZI0ZQI71r5BNHX27RmnyrilOqXpVthy5y3edUwQOs1pZWMoervMoCKKrIJq4uuLh0QircyzrdIdTqiQtV/ZdTVvGe2emwSums3nUZo0Wq5nem2aDTtLCYdVp9/NO4IBhNapgErY2I9eCFcAp+aor1tiY4t7CHqE7ClmSKSqdvlXn7ixIrQOzm8ZRGk2iILEu0nRqRN4/7udp4Bl+dWwxhfz5A5d0skNsPSuHWjiCb0iXJ1TTgh8oprMe7KcnvSF4o6mTi/UAHb1o/RBxG9nzGquntH5qiMOyFM26K+SD9d1ySmZwcL+4fuCe+oGfzi3XsHmLcwnugIq9dBaH8MUNZp4VU4XzVJrQXhZdAiuNpqaVbDcb0eBE7KZ0pzILL8PoKswic2u0ei1U16JB4nngBkmEs+M0fgYDGCDv
*/