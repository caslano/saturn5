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
4Ji/DAIt/uKJsVp40irupjmr4bAydQj+AH1tLmTJy0UId0pkcIgIrclm7zSwbqcKrdwPsUtP4DBH2BWo59HwwnteoEIK43wQn82GUzoRTBnWl0GlhDSEPEXNW+8kpJEppdI3eNvWJTN4QdCsamWUWVc8wEcrBNxC3SFGAwvMB2rglht3G/O6WENbSUYgJrhqUuqRTGnfFMHk2PuS88y21YKDRmbJIrjAipVKY2vXTOoldl7ouGVje8dkUDK5BiNKbGDqV84wCiHv1FuO/FagoZoeKIv+NG/kW+pAciSCm+UQy3eznLpkkRsBJcDLeZw4HqD7VFnXv+g4PaKYUIktNao5pQs6RCqRFFixYmsNJzZ3/JHUrURRUOAVlsxxadmg+1Y1EavSWhBHIj2jrA9LhwFygWXkssEsYWxYvLdEbGuU0k3pOiWCobEsiQaU5Fgbg6gS7T2MVDUaQ9OOpkv2TpRNCaxUjbR8vlDZ2vliA77nLJaMcmLhGGxCoyLzpZDbmeK6CHLOiAeJ7r6nNBG6k9f9Xx28k3j424Cy1kWRoNENK0gPawpDKk++edXDcJatILXF5aB/Pph1n/ZcsoFLGidZi2rKiA68VRsEguYx3zdlCW1KU2YRDU1FaNh19HI+n3qrZJLSadl814bX
*/