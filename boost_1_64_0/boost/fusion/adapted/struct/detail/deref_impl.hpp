/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
        {
           typedef typename
               access::struct_member<
                   typename remove_const<typename It::seq_type>::type
                 , It::index::value
               >::template apply<typename It::seq_type>
           impl;

           typedef typename impl::type type;

           BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
           static type
           call(It const& it)
           {
               return impl::call(*it.seq);
           }
        };
    };
}}}

#endif

/* deref_impl.hpp
roVd/wR1RrFMLe/UckeroAX1PFOjtlPPEO/m8S7VdN47M/VSGAyrvaoHjAfB5WbZ7/UuZp5DuhdYnkvX8/6oTeVGSPtCrfdorffsDzIO613qN/ti7dU1jrrds6/q637PfolfebbfoRb9WK5x1v2efZrLPfsRTSPrXmgeE56ebX0R6ga39Kjb04eVFlO/p/u99jKmw3rffzvSke6ajrrf96/qW/t9/1CZUE+/UydH2YYjr5OjJs47GWeY7okNv43uiRpZ04hC83zehx0H9hA5vVbfh+2Za5U10enTn/w0fkudsFInlzplj8Xuy+/V88xgKZ+VhWROAXKtn6VbZdRU/SzHLmOcuiXV9yRTLll0/lKeqdCduv1xhVNVVVM3UsMaHfz0O8xFjild8et4p6WL/n4hv7c8wbyrudf7n7uT6X5HNPKdwBti5HnjqkaLp5760YBvN/R+skX+yJy637F0v/MZ+c6k+93RI3dn0v1u5JG7C+p+J7PudyyP1J3Yut7V3NRBnm8YcM4VN91+/JoXBgxZu/3LTXmR77JGvsPJsxbrzbMHZV77nv1J1jMP9NfAxd+JFn/p9NfWPTzedeNYiWMo5123Abw7N5R3++DU3nQiz+IMB6V9jQDvUHvweo9+JM/kjAJfAscYei/6XEOf6RzLO5bjzPRy/OJ+JuVJj+mvgv5OqcXfbvo749D+0J9H5y+d/jof0h/7Qqavk/cQZ1zM8CL6a+Bh/8J+R97PyTI+o79Uvp8M3jGZwruNmYY+izvV0HvL0wx9tjEHXMkznE/x7OZmMJ93XQsMfSevEPwdGDD0Wf6Z4OlgsdQDMAjmS6cH3gjOBt8FSw19xnse+KnsLYNfgZdLOF591qsZeCV4iuw186zTQkNtw6izX/3Aawx9BnwxOM6rz3xV+6Pbi658DHtXcP7Ha9+Pttq/bg//qV3+M/vQ/w970OsKD38fuq570G57z8Med+4/R7/3zH3nQ+05c7/51+81O/eZsx4/vL3mSPvMpQhvkYQBOvabuddc933misfd9pqj32f+d+8xH8n95UPvLTv3leu2p7z5ceRT3vcT+B3cMLg8uKVw6+B2wskBpji4YWvq92LrP/Wf+k/9p/5T/6n/1H/qP/Wf+s//18cPV/Dv3/8vLi3IDqoDAIbxq84AyP5+diusAY6VPe8JqWMTU0YOg2X/mXr73ziBf48fF/o7/6r3/jd2N0K29VJd9v6/wCJgYLVa86sJvE77/nubm/v+NfFsibDvP+hBazx12/M3xjn3/M344lz2/H/ph7VbW76i3+8/h+E24r50U949bgT6ZY/YEq4ynZ6bFbUdG9mHW/mIuQ9Xs5/l7a/2Y4tLTTsx3Ee7tLAg23DYoiwpRtUwbYkbNc+oK5XvxqPCRJB8lhB6X7I75rD7zLzO51ryXLjY/vj+aHheYY6l1nxGzJfKw6/LF+2QqwCs72sZ9/Rv4Zr3DVIHZc+0IjwPJXmFBdPqYMfHLR/tVPryJB1HJB819dmICW+nDaXeWfJRu75y1jdbXciwldfqGPOdt+I7byTl9ZgZjzIpb9bvqPVEO+tekqM+u9v5jVw/U2PD09pYbL840lrX+mmm061+ur4rxxmKwsygQ240OMqshy1ZD5vIGaTH7Wk9nHpopte1HtYpvd2Y3uBR7vI63iKvIXSjltWBQ8jqrUeFy+qmUueeMOOq3VaCis+mP3xMA3d7yskS7m9gT3kn4+/PcypS3s2kfur4s3BeQ+UtmnyxzVLmZITe37SmdhtRgxTd05P3u/D0tMSXJmvs6Rk5LPr0NP8V6dnL9PRi++0G11raxBqencuqe/l4HOmZ3pR2tRxxZzUMj/sEsXU=
*/