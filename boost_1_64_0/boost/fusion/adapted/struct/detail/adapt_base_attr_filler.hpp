/*=============================================================================
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ATTR_FILLER_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_ATTR_FILLER_HPP

#include <boost/config.hpp>

#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/struct/detail/preprocessor/is_seq.hpp>

#include <boost/mpl/aux_/preprocessor/token_equal.hpp>

#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/push_front.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>


#define BOOST_FUSION_ADAPT_STRUCT_FILLER_0(X, Y)                                \
    BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(X,Y)                                    \
    BOOST_FUSION_ADAPT_STRUCT_FILLER_1

#define BOOST_FUSION_ADAPT_STRUCT_FILLER_1(X, Y)                                \
    BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(X,Y)                                    \
    BOOST_FUSION_ADAPT_STRUCT_FILLER_0

#define BOOST_FUSION_ADAPT_STRUCT_FILLER_0_END
#define BOOST_FUSION_ADAPT_STRUCT_FILLER_1_END

#define BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(X, Y)                               \
    BOOST_PP_IIF(BOOST_MPL_PP_TOKEN_EQUAL(auto, BOOST_PP_EXPAND(X)),            \
      ((1, (Y))),                                                               \
      ((2, (X,Y)))                                                              \
    )

#define BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE)                   \
  BOOST_PP_TUPLE_ELEM(2, 0, ATTRIBUTE)

#define BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE)                        \
  BOOST_PP_TUPLE_ELEM(2, 1, ATTRIBUTE)


#if BOOST_PP_VARIADICS

#   define BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER_OP(r, unused, elem)      \
        BOOST_PP_IIF(BOOST_FUSION_PP_IS_SEQ(elem),                              \
            BOOST_PP_CAT(BOOST_FUSION_ADAPT_STRUCT_FILLER_0 elem ,_END),        \
            BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY(elem)),          \
                BOOST_FUSION_ADAPT_STRUCT_WRAP_ATTR(auto, elem)))

#   define BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER(VA_ARGS_SEQ)             \
        BOOST_PP_SEQ_PUSH_FRONT(                                                \
            BOOST_PP_SEQ_FOR_EACH(                                              \
                BOOST_FUSION_ADAPT_STRUCT_ATTRIBUTES_FILLER_OP,                 \
                unused, VA_ARGS_SEQ),                                           \
            (0,0))

#endif // BOOST_PP_VARIADICS

#endif

/* adapt_base_attr_filler.hpp
WXMjhuUg62mLWA4NWA6/A7uBDWN0vTya5dAIlLbRGEyTtThJF9gkRsujpjG6f20G3gI2B5+Q8RT4prwv8HN5X6Ak4kSmq8LgOXEJg+lqpmxw8bwq03Un2AFczvTdHaPl1j18D/eDN4MrwTtE9oJ3g+VMxwMchzwIvgY+BO4AHwZ3g4+AP4CPgj9LukApp8fBhuAavq+nQI6feM5bnf8OGz/9I0aPyw+yPv0Mpkp1jNXt20t55KNc94PXybsBbwRjKc+PAlfLe2E/0xCUfqyFyGMPylX6E8TdNlaPC+JAtiOee3ZvRwcp33726Hb0C8dPhle3Iw84Ur5ynJoOV8nwZjK836m73TwDz360faweZ3aI1e/tNOqY7ghK3J1idX3qDE6U8TSYB54BMh6eSca7d4nnC45LvwTjwH1gZ5F30n6kjoOJIrfBS6Wdx+jy/A68Ffye76+JJ3SW2GjH99dW3gPl84YYPX/ZyPCfYbibWO8qQUnTc4xnc4weF7wAXg++BErdfoVy4FXWu7+AfwdfBxtIHwG2Bd8E48G3wARwG5gNbo/R/eU7Ej64A1wMvgc+Ar4PvgLujNHjyA+kPoO7wI/B3RIf+BH4E/gx6EdePwVPBP8q8gf8jOWS5OOZXp71lXKZKvWGd/pLvLo8Znl1PzgHHCD9qle/17lePV6aJ/Mgma+BZeDl4P0gZL6qzwvAreq+me63rgJ3gteAzZUc0OVxrcQDXgeeA/5B4gGvB1PAG8CAyHiwBLwJ/CP4R68eV9wGPgkuA58D/wR+At4B/gIuB1sjj3d5dTmUgd3Ae8BB4L1gEngfeC54v8wHwZVgBlgOzgQfAOeCD4JXgQ+BSDPO0upxdgX4NPgY+Cz4BLgdXOPV4+onwX+Aa8GmKOunwVPB9WAncCMo7+AZcBRYCU4GXwDzwRfBy8AtEh/4slePl1+VeMCtXj1efg38Fnwd9PvxrsGW4BvgyeCbEi/4lpQ/uA3sD74t8YLbJf/gO+BCcAe4FHwXXA6+Bz4Ivg+uBXeCG8Fd4C7wQ4kf3A02jkG9BJuBH8s8HPwEHArukXIHPwUngX+VcgY/A2eBe6V8wc+lXoFfSLzgl1K+4FeSb/BrcC9YDX4FfgN6UK+/BRuC34GNwB/kvYMHJJ/gP8FM8BcpV9Dw4b2CHvAG0AfeDh4FloENwY3g0eCz4DHgN3o9gmeBkTfKs8ZqPUN/vvZreYYyUf3Ed+A5Iqf8ejz+g1/3twfAudKv+PW48Ee/Hm/8BD4t8ht8VgKU/h/wgO9Ksjnf9ptyj2d51dg1TO6lc10pEzwLzAKngNl+LaengrPAaeB8MAe8E8z16/Y93a/bdx74MpgPvgEWgF+BheB+6UP8elxaBJ4OFoODwSA4GiwBJ4Kz/Hr8Mxu8FCwFLwcvBa8C54K3gfP8Wh5eJuUBXg4+A14BbpI8g1vBBZIO8CoZH4JXc5y415BOiuNE9gfSj+3ke7qN/eXdYFtlZ1f3j/eA48F7Pfp9rfDo8dAq8CGlfwPyR+ZdXAeALFK2HtaDG8ENHj1uew4cLWvTHi1nXpbwwFc4j3/Vo+XNX8BZ4G5Q5hUfgyvBT2Q9QeQ5uB783KPlyxfge+A+8EPwK85PDsDxrK6RwnrQRvpT5jfIcddssL3IebCryHewr9RfcKjId46PL+f4eD44B7yS48IFoLSBheBSkffgAyLvwcdk3S5G199rYnT9vZbjxevAD2R9Usax4BLwW1mfZL95PdhE5D94nMj/GD0fvRHsJ/0AOED6gRhdn26VdEp/wHZQ6eE5W56/lfz3Ue+J96G5rroc7CnvHTxb3rfUU/A+MEPGnWAAXOnX47VycLuMN8Gflc4=
*/