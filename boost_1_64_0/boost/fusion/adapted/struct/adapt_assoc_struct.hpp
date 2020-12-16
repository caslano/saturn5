/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/less.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base_assoc_attr_filler.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/size_impl.hpp>
#include <boost/fusion/adapted/struct/detail/begin_impl.hpp>
#include <boost/fusion/adapted/struct/detail/end_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_data_impl.hpp>
#include <boost/fusion/adapted/struct/detail/key_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_data_impl.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_C_BASE(                                 \
    TEMPLATE_PARAMS_SEQ,NAME_SEQ,IS_VIEW,I,PREFIX,ATTRIBUTE)                    \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_C_BASE(                                           \
        TEMPLATE_PARAMS_SEQ,                                                    \
        NAME_SEQ,                                                               \
        IS_VIEW,                                                                \
        I,                                                                      \
        BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),       \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR(ATTRIBUTE),                       \
        BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),                  \
        BOOST_PP_LESS(                                                          \
            BOOST_FUSION_ADAPT_STRUCT_WRAPPEDATTR_SIZE(ATTRIBUTE),3))           \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct struct_assoc_key<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ), I> \
    {                                                                           \
        typedef                                                                 \
          BOOST_FUSION_ADAPT_ASSOC_STRUCT_WRAPPEDATTR_GET_KEY(ATTRIBUTE) type;  \
    };

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_C(                                      \
    TEMPLATE_PARAMS_SEQ,NAME_SEQ,IS_VIEW, I, ATTRIBUTE)                         \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_C_BASE(                                     \
        TEMPLATE_PARAMS_SEQ,NAME_SEQ,IS_VIEW,I,BOOST_PP_EMPTY,ATTRIBUTE)


#define BOOST_FUSION_ADAPT_ASSOC_TPL_STRUCT(                                    \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, ATTRIBUTES)                                  \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),    \
        BOOST_FUSION_ADAPT_ASSOC_STRUCT_C)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT(NAME, ATTRIBUTES)                       \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),    \
        BOOST_FUSION_ADAPT_ASSOC_STRUCT_C)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_AS_VIEW(NAME, ATTRIBUTES)               \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        1,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_STRUCT_FILLER_0(0,0,0)ATTRIBUTES,_END),    \
        BOOST_FUSION_ADAPT_ASSOC_STRUCT_C)

#endif

/* adapt_assoc_struct.hpp
i8Xr58beCo5nRyz9yeoAp/QntwU4VQet0Th1wp1Mi9udnFmX3uGUMdeP3+mWQdOGeV5TRlfSsxtr0/NiwMkyd2sy0Lng6AC1z+EeTQZNpYwxytw6jdd1KfcqHCv3ce6thqswqXmW+zVe17U8oOEopKlZ2h6bX9m8GmDL+1ANnjc911dHpR7mQYvj+ti6L2W9JYNE4PcfCnD6Z8e5tkEZ9dkRh0dcMrKgsBuPWryZfgl247G0Mgl5zq3FIxnlObc6F9RRsMwGWwaNRpVW3p9QMuZuAczNPqnz0FU8pWG6TmKjhuvtwNMarpp1yW0KcEpf8YzOJQJpKOeJLRk9jZ41OHf8n9NkXDqG5zVe1zFsMXDoGMC9oHNJ/4o7eS+rxkGfIOeIgXu6PEMni7ButWRsvezvbF7pWOVccYBX7dLLFofyzP2QVywuoP/EOopXHXJS71zDO/jztP39r7lkMTYuTtXP8vbsvu6QQ5w53bal4VGkWeaNNDIo0hz2N4MyQd0m/Py9WxbtpJTZ7paBjhP7im0Z7DF/y8K5jCHd/mhxnGfNJGa5HS45PXkRhrchJ44V1/cCv6Ph/G2Av2vh9agn3tNx1BPva5h+7tYHPl5RUpZvLALl+P8pwCud1ocBjkPnqfJZ5s9uGexpxP2w6WRSjY2RWFLs1Od88dc9y0GpI/39KCiruqjw9+P0MhEc/cxyf3PLeWuBk156fOKWkytP4efONDKpGHfOImGk26cBOXX/UQIyn7llZNpC5nO3jEhTX4e2yy2D9JTh/sIpo41+4NaXTjkOtvCT3frKKSN7UiyEtNq9BzkZuDDL/X0PcvhInH++3pOcKrfyzlq3LMqGDN+3bhlkR7Vv9junnFwn6sX1+z3IUNsRT2Ls+INbDmvMcI/tIWlk4mIvcNLYt5zhlCXDnwvz8OllkEUwD++Wq2tomJuKI+fyPPye5Dhnyni0cMvFUvV6cZGyLYOyUP0F8+gBTln0ABCXVnuS4e1vsn480JLDQnjmDgpw6mzmg4NcPNUYb0hE6P055AvartZBORwbpsrvIWlkwtWxiCfTximD+hBpeGgaGZnUvLCpZi7Sp61bVn0YuNnOLecdlIHN7bItau+UVfsIOzj5YHnrGJRTM2NI18PcMihpUuZwh4xdbjs5ZYLltrNbDuVWyhzhlsHqZSnTxS2DvCPT8UhbRm1rZDe6Onn5mT1/jnLI2GWkm1MmWEa6G3L+BSPMZTm4RuydOTrAoY7w1hcYvFrDdYyOG+trEsz3tHlVDpjvZfOq/eK06R3gVdvlry0IyujtFsv0CcrobRancV9bJthecZiPs+VUW8V8vyCPvCf5/kEebYCMzwA3j/pfygwMyuh1P8sc75ZBvS/Dkh2QQZ6CP4PS8dre5cGGjDxapA4JlkD+GWLL1MxlfKiBq/sBhuk41kTp+Wa4xdv55oQAH8w3IwIywXxzYkAmmG9GBmTc+WaUJWf3cUYHedSjFPXkHP+u8zEBOdR+4MdavJ3/xgV51HuSH2/xdv7MCfDB/DkhIBPMn7kBmWD+zDNkgvVvfpBH3Sr5iRZv5+9JAT5YpxaYMqkY517JFRocpheQ50/yuIqyqeUV6n7dyTpurSEvMjh198iUIG6sKSkO8NCAgy8J8Ob60FKLt/PEyQEe6Yy4lpk8paN8r9zCVZ7GGgWPn4aL4zCunqrjGFdP0zBdN/Aj4NiFKM+4l4v/UEqxNiG9XLJ6Vp3ff5ueTo5OuG9IyP7RKS4Z/bR5pNupTjl1ntcMF8+fV4blNBevPj+H5fT0MvFIpFHIcf+wKp0c37FZVUdTZ37dODOtrNL1VrtlvOqIZWalk0Eq8ZqGtDLUPdf2o4Y=
*/