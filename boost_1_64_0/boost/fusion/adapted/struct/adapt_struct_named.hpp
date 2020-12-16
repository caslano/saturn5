/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_STRUCT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>
#include <boost/preprocessor/config/config.hpp>

#ifdef BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                  \
        WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ...)                                 \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                       \
            WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                 \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(                                      \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION(                    \
                (0)NAMESPACE_SEQ)NAME,                                          \
            __VA_ARGS__)

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED(WRAPPED_TYPE, NAME, ...)             \
        BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                     \
            WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,__VA_ARGS__)


#else // BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                  \
        WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                          \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                       \
            WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                 \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_AS_VIEW(                                      \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION(                    \
                (0)NAMESPACE_SEQ)NAME,                                          \
            ATTRIBUTES)

#   define BOOST_FUSION_ADAPT_STRUCT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)      \
        BOOST_FUSION_ADAPT_STRUCT_NAMED_NS(                                     \
            WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

#endif

/* adapt_struct_named.hpp
/k8B5/tNgW3UscI8eZcysAp1p6fcv61w7Z5BzE06OQ4v85udvKpjn1U8tai4Y9nAVN583sCVG1t0HO3VCybm60t+a+G12I/6osK1u5Jwbjc47c4UORcZxP2x00sBTtUrL4NT56njnmWJG3vJX1UYzsKV+GsBXOa31xWunbMq39lmcFMrvbz9hob756fC/zcNjqIB/PcGXlbkubXdwjnm4P5gcfpdlG/ZHMrWHzVcVXqYB3Ry5XLPs8bJTjjmABWun5kl9z1rHAoX4+9JPDDX876F63H9wOL0uP7J5hDXD3Uc/TrvnT9rHA/xgP9Fx2mtuIf/VcOl35jf0/FaOVf3MWGRxkaeYsZsUUI/3/tvxEcHVwd1f/gOn4B36U13gnPpwz4Fp+m9GP8MuKZP5bB/zvgsT/8p71UG5mp/vgDn0md+yVw4rT7zK/C2PnO3wp36zL+Dd+kzvwbn0md+A86lz/wWnEuf+Z3i0uozv3fI6O7/AN6lzwwdCs7x/TLA2frMTOC2PrOZwp36zObgXfrMFgEuqM9sqWSc+swDwLv0ma3AufSZB4Kz9ZkHAVf6TBnWgxWeVmfZGjIuneUh4Fw6yzbggjpL+e6hOj8rypcCRarrufy0BafrM9sB25M+sz1kLH0mh6cDuHQ6y47g0+ksDwPv0lkerjinzrKT4v36oLPC9OgzdwQ4lz6zCzhbn3kkcFuf2RW4S595FDhbn9kNuK3P7A7cpc/MAufSZx6tOGd/uIfinf3hY8C79Jk9FWf0TXsFcFXf9g5wqo92LDhdn9kHmK3P7Avc1mceB9ylz+ynOI2RXH9wLn3mAJuz+v0Dwbv0mceDs/WZ2cBd+sxBAU59j8HgXPrMIeBsfeZQhTv1mcMU79RnDgefTp95AniXPnOEgysHdyI4lz5zJDiXPnOU4pz6zNHgXfrMMeDS6TPHgt+TPnMcZFz6zPHgXPrMHHC2PnMCcJc+Mxecrc/MA+7SZ+aDs/WZE4Hb+sxJwF36zAJwLn1mITiXPvMkcC595mSbQ5yKgLv0mVMU59RnFoN36TNLwLn0maXgXPrMk8HZ+swy4LY+s1zhEgZeAdzWZ04FruszpwGz9Zk/Au7SZ1aCc+kzp4Oz9ZmnGLiqg08FruszZwBz6TNPA+fSZ56uOKc+swq8S585U3EufSbHodqQoZppovR3lsKdes4a8C49Z1hxTj1nRPFOPWetzmvt7Gwd13sdyCNzdJ4/h0yHKHBLzyn6P76e8oz0Mr4+dK6ScepT69LwtVijXu/mxWJ9Pxyx9DJ+OBqUjFMvG0/P+/7MC8gE9bKNkLH1sgngtl42CTydXjYF3tbLzgfu0ssukNxe9bILIefSyy4Cp+tlzzQwVabPAm7r/BYDt/WyPw7gqp92doBT7p0DztbLLgHu0sue6+K08vETxTv7oeeBd+llz7c5q392AXiXXvZCcC697EXgXHrZpYoz+r4XB3CVpj8NcCpNLwFn62WXAdf1spcC0/Wyy4HZetnLgLv0sisU59TLXu7kVVtxBXhdL/szA1N5c6WBKzeu1HG0u1cBs/WyVwO39bLXAHfpZa8FZ+tlrwPu0steH+BUvfJzcLZe9gbgul72F8BsveyNAVzmt1XAXXrZm8DZetlfAnfpZW8GZ+tlbwFu62VvBe7Sy64G59LL3mZzKFtrgLv0src7uXI5dwbO1sveCdyll70LnK2XXQvc1svebeF6XO+xOD2u62wOcb0XuEsvex84Wy97P3BbL/sAcFsv+ysdh7+/BtYYUcmfnJVg7kGdQ3CJYz/Wm5yPP8R4A409VTXbhvCHgZdD//oInlV9hTkwxhNOPeRjbq4KKjw5FwYZl57xccU=
*/