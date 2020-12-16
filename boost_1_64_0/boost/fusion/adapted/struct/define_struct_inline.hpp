/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_INLINE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct_inline.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE(                                  \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES)                                      \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_INLINE_IMPL(                                 \
        TEMPLATE_PARAMS_SEQ,                                                    \
        NAME,                                                                   \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT_INLINE(NAME, ATTRIBUTES)                     \
    BOOST_FUSION_DEFINE_STRUCT_INLINE_IMPL(NAME, ATTRIBUTES)                    \

#endif

/* define_struct_inline.hpp
1u/l0rt5ND4hU0omSWYFmfVktpHZTaZtPvFk8sjUkVlGZh2ZrflyLntnPrkxkeKrjUey6bmATJjMUjJryGwh8+FEOa/dapKc1+46ieJPpoLMYjI/J/PoJHOOe+skOc+9exKlQQG5TaaSzEIyK8isI7OlgGQLmsYwTb+mX9Ov6df0a/o1/Zp+Tb//z99/evxfUx2P/jvW/4u572SI3r1LzH0LV6ui4YU0pwv8FcYbE9VVQW4bc2Ent505viXIJ7sRlz2Y5oDe9v0SDtdHknMaaO6J+Z405h6h+LDildvjmU8lIlXVkURVTSKOdxNjKB7VtLafwwuO76WSfJL48bM8PhKbY/EjadC6g8NNp68UikMWqsSCgWQCfJ/jKex3G3wj714ggR4IW97bPl8XnYUbkmoawuwHZLLWeTLgo7Fo0os/aVH6MC+/tZd6IY3PDvAcCeZTFMdVHEcmaurD4qbMWMJbv5GVTXPUmEfPxjx6GdYGTCFzB72/7utjaCwvA5hsrK6JYA59xJ7WbmBNxZoxYt5e3uGFNRGY46+VU/+QzfLx6sbZCXN+/z2Ea7qcCwxVkLmL3M36hsOVX1ZWpRJvH8J2uAwb1hTwJ+UbuhA+4PJTeuErVeGmciKxSrUWhFJehnkswlzQXHp4GtYkVEJvtkKFmZVmHHCcgbgvaxN0P+6CH4XwIw9+tP3W9yMVC/iyb354eaJPC0msJQfbi+9J9k97U1pIP2ZFY2HOcvsS9vahFu0+/I7f61kfqafPJdfeZBP3QgeRjhFzXQf8riEj8sfJZI4Qafg9u8EZujocxmff4x6kXHKQ6sCR5JfwJwPf1Nt3RE4gX2SJuI4Blkj6+4NGIkz9W0oHuyPNu3hp/oMRprrqRJLDtS/pItabHCXfD0060vQv+wDoX4nsRPa3ZO4R9ZbmH9eqfO2/KPd734uFuGtlU+XnZRIjF2V69PHX9yyA6yivftqF6yIxuQ4qm+RaU3gHEP4q4oM1Uyg77IS/BupMyNw3RqbB8+rZyIOVB2J9T3PKB7BX96Z8EOqp0iDZSDdC7T3ubUKt2c2lzeld5Mkc+XfPouLBJ4SAHaWw4R72ejMfG+JhmxQ22MPuUdggDztfYdkedoiPDfL9fS/Tx3x/6xTm+/tWho+xe21EWHzsRH6+3X8ewc/L/ecT+Hm+/zycy2GpKodW/UbNBvsh1261ZyzKz3P8dXdxfo6rtXXIJ6o+TSI/9NHzXmDtV7I+zuVO5Z1rea1YQyqJsvJ9SH6727qY7cRm5JPHEMb1ZB4QfYAWej5ZyOfO7ku5hP8qrFbdOPQgKXwb6oJfkvkVyW5oafpHV83utU1CWtl+oa4n/GD6D/Mlw8j+NdkPkuyKA0y/cLXnfJRV9nem09uM89rLOpH9Lc7INNrsYlUvoM0WmOwdqbpTYHyFssovjPENaLwOsK3/Ln1X1b3i+mIEpV+Y4iXWQv2J4yHd6SzXXtE7c0RUGGsl6yHC2AXGCEIYuAry65U2raRbn2KtZIP1fAWeLxokn5/D83rUOxOQ5snWMqX4nEgywo+HRX46MH2ac8d2H/oggf4RMNX/kA6hvKBsqPTvqZWrhF0n45voeXU74lKCsnFSSLbjMw9ScQlHqOA1LNprudhTm72ijRT8eaZsB84n+9kelGbsj+rEhxv4plb2a81e2uwVss3mOmvYIbLOosaV6411xDXn+gG38iIt1iN90D4xtoGef8dhphBo3+CZHmb9NNOun1DPdT6OMQr3rFSt+l5I8wT80de+8v2x/jrZR9lNTgK6HFCWgR30XcS9YFcSv6o1x81fz/xmew4X0tt7Tvj5/OmDpfzjaD9b4/0n8TwXz0/jufA=
*/