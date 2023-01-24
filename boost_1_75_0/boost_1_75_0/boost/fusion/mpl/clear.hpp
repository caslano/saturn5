/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1817)
#define FUSION_CLEAR_10022005_1817

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/mpl/detail/clear.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct clear_impl;

    template <>
    struct clear_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {            
            typedef typename 
                fusion::detail::clear<typename fusion::detail::tag_of<Sequence>::type>::type 
            type;
        };
    };
}}

#endif


/* clear.hpp
MjmT/JL3qVPIy6bDr9woR6bnqD+gmT0y3a5OAfl3S7GQF85Vqho9GtgpKz3F5XmX661bdleKXEyZKD/pgJ3FevK3a2XFk0bmLjpEwxk1OomjmBTZ7ocRzd0t1fQCxt63myv3EDL2OmDsh4Knqg891IMeAWpnRnsigiszdzjhmyoroGGbXPgRHOqHmjASLbdRMPm0RCb/0EqZ7Crwn1UmBr+WGBMGu5AUybJZzl+Iw2NykYhsV2/dSmTJEdwMpC5XpmZ7/oSZctuHH4ROPZhZFro3y4R8PY/4ul3wdTuSeWMt8vVab8SZg6NcDKMMsuz9eUae+L/Xn+oCC77r8ZsYN37MJvXx02zacbOJBvDRt2AAnWIAb1ijD+AOHEDnjw5gGhRkvAovx1XSYKtnV+PlHTn1ifeIVO/r95yGtG6nwSBfbhj4luBNPmiwlzUVR2hFdMhiwinfiQl3ZGvchFsLdVJzd3G7SMj+8fodP1o/yD8fCIIEt8YRxK6/YGfcC34MewMBli8UDlh2pU9ZnuZV0j9iTyPiC95Q9kcmrd4xZMmnXeNwdK3f0XWGduWcX/nEj7zrGOoE8CBZjfumYgYZcrVj13Lg6LWUlRbYzs1Keu3UcHoDfQ/B1uXSahWr21G75JPo7HwNATjyD6FCqgNLyEq65eZw+k30PZSN2EMz07wh1Rz8JDrYpyxNU85oDdCdrxO787VJsTral3zE
*/