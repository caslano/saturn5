/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_05042005_0741)
#define FUSION_AT_IMPL_05042005_0741

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply <Sequence const, N>
            {
                typedef typename value_at_impl<vector_tag>::template apply<Sequence, N>::type element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& v)
                {
                    BOOST_STATIC_ASSERT((N::value < Sequence::size::value));
                    return v.at_impl(N());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
nVw3wdtkOzdMk+3mSruLcDrOx3wsxnIswWpcgGuxDG9Gk+y/hizXRbheYtl/J+V7W/b/9CmWdj2LvvgcBuNONOAuTMbdWIIv4UJ8GS/GV/AK3Iu34au4E1/DF/FNfB/fwtYc/210x3exA76HtJPjq9c8uBZiaeck5XsclfSBtPMT7ImfY3/8EgfjV5iE3+AEPIzT8Ajm4Xdowu9xPf6At+OPWIc/46v4Cx7BX/E3/A1dadQprSz362mFfdEVw7A1RmIbHIltcSq64Tw8FSvwNLwGO+LT2AlfwM74MnbBVrxWD3TDbng6eqIneuFI7I5p2AMnojdOxV6Yhz5YhHq8AX1xHfrh/eiPWzAQX8O++Bb2w3oMQXfeuKGYgP0xGcMwEyNwBkbiLIzCuRiNS3AgXoqD8BqMwetxMD6AsbgV43AXxuObOAQ/wUT05Hs4Cb0xGftiCibgcJyHI7AcR+JiHI2bcAzej2m4DTPwKZyA+zATP8GJeAgn4Xc4GV1432VhK5yCPXAq9sFpmIozMB1zcTbm4QLMx3I0onmNdRe5DiPXZ/aQA3W8Xrluncj7yhtTMACHy/t5BA7FkZiKY9CIaViOZ+BiHIfLMR0vxwy8CSfgBszEu3AiPoyT8DHMwpdwKn6A0+T9no2taNt0dMMcDMSZOBpzcRwWYAXOwutwNq7FM/E2nIubsAhrcR7uxPn4ChbjISzBr7EUf8IybM05MuHpWI5dsALN32Mu6jUV/kaW8xkuvz+VtIh6nrgYfXAJBuFSDMdlGIsX4kS8CKfiCpyPl+NVeAWuwStxJ16Fu3G1nJ+r5fyswW5YjT3xOgzH6zEF1+JUvAHz8EacjTfhIqzBc/FmvAjX4Qa8BZ/C9XLebsXP8TY5XxtQ+X7YiO3xDuyJd+JYvAsnYC2uwnuxGu/HGtyM9+ID+CY+iB/gQ3gAt6Lym/YR7IHbsA8+hiFYh9H4OKbhE5iOO+TvlK6Tay54kfz/rC2m6Czpbvn/2Sbsg/dgONbiELwXk/B+PBcfUP8/LddQMM7J/6e3UK81Piz724ox+AjG4ja0tE+ui+AlTtr3k/z//lccgr9hLurYvgBOwaXYCi9AV7vfH/rLmv790VZetxsOQHd1O7nmgElOtttJPV98HuNxl2xXopO+fzxftjsNjbLdR9TT48dyHj7FofgZnoGfYyZ+gTPxS5yNX2MpfoOL8Fs8B4+iZWyr9OVLH/8eh7Gta2Qs5I2oxxoMxnWYjrfgZLwV5+EGNOFGXIS34xq8A9fiXXgb3o2bcRNux3vwQ6zFg7gZ9bTnAUzBB3EEPoyZuBUn4TaswMdwGdbhxbgD78Sn8AF8GrfjM/g4Povy+qVfnW2dvP7n5fXvktf/grz+FzECX8J4fAVTcC/OwVflfOzDVfgG3oBv4uP4Fj6N7+DLuB8/ww/wMH6InrTnAHbHTzAUD+FA/BSH4ud4IX4pr7ser8DDeCsewXvwW3wYv8NH8Hv1d670t2OKk/fra/J+fR2H4j71c0eS93muk8/ddvl81GE/fBzD8AkcjztwMj6F2fi0+n6Ufm38wsnfI0z+HtGox0Hy9xiM6RiLkzFOzv8QNGECVuNQ+TsMww2YjA9gCtbhCDyAI2UMdSq2xzEYgmk4Ds/A8TgeKzED1+IEvBEn4UacjM9iFu7GafgGZuOHOB0/whzk9fP3kz5n3CCvvyePD8jrz5PXXyCvf468/jNxEBZhEs7DUThfzkMxluICXI2leCOW4RNowmewAndjpZyHRfg5LsavcQm60q5zsAMuk3n05+JgPA/j8EI5LxfjUrwUr8HLsAYvx3V4hd37cP/Spt+He+R9+BIOxZdR3U6+pwOcbDc=
*/