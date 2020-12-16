// Copyright Daniel Wallin 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_required required,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_optional optional,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_deduced deduced,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY(x) x
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM(z, n, data) ~

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub)                            \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_, sub)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED(x)                    \
    BOOST_PP_CAT(deduced_, x)
/**/

#include <boost/preprocessor/detail/split.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(sub)                        \
    BOOST_PP_SPLIT(0, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(sub)                             \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_optional(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 0, arities)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_required(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 1, arities)
/**/

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0(r, n, elem, data)               \
    ((                                                                       \
        BOOST_PP_TUPLE_ELEM(3, 2, data)                                      \
      , BOOST_PP_TUPLE_REM(BOOST_PP_TUPLE_ELEM(3, 0, data)) elem             \
        BOOST_PP_ENUM_TRAILING(                                              \
            BOOST_PP_SUB(                                                    \
                BOOST_PP_TUPLE_ELEM(3, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(3, 0, data)                              \
            )                                                                \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM                  \
          , ~                                                                \
        )                                                                    \
    ))
/**/

#include <boost/parameter/aux_/preprocessor/impl/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                             \
    r, arity, max_arity, spec, xform                                         \
)                                                                            \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_R(                                       \
        r                                                                    \
      , arity                                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
      , (                                                                    \
            arity                                                            \
          , max_arity                                                        \
          , xform(BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec))            \
        )                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0                                 \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY                              \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_required(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M(r, arities, n, spec)   \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED                       \
    )
/**/

#include <boost/preprocessor/seq/for_each_i.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced(r, arities, spec)        \
    BOOST_PP_SEQ_FOR_EACH_I_R(                                               \
        r                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M                        \
      , arities                                                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC(r, arities, spec)                \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                       \
    )(r, arities, spec)
/**/

#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN(                                      \
    opt_arity, req_arity, wanted_arity, specs                                \
)                                                                            \
    BOOST_PP_SEQ_FOR_EACH(                                                   \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC                                  \
      , (opt_arity, req_arity, wanted_arity)                                 \
      , specs                                                                \
    )
/**/

#endif  // include guard


/* flatten.hpp
dlJroUoeqayJyJdKKYfPKzc/SUrHvxtI3ceJ5+8wpzCfYYa4kxj/0sI1B+7FHOLvUzCRNcO7Y5ZhNmOexHyCacUCL0MxBZh5iZNcjyYmu/YnXmTdpvSxLgeLpRz8WZ1fl9SBf4dzx3qRNuJ3mBN8iR3sZlVBTC77i/4UvuhOcf0R8w9MMjtn9Uvo7/ImtGcseQrzA252DU+cwq6ObV1bE9Os26g+0esHsWSbKY8/6qv2j7QsY1wbvVZQbY2pDE3pp+ZQojPeav0grrcuo5Vy/3lRnd+ZdAW5fiPm+5jfYk5gPsEMZAfRKZhZmOcxv3M3d52ArgS+L2HKMd/G7MCcwaSwV8AgzGTMbZjHMC8lxt7/KqV9/6vSvy2pJb3xMsr5BnrJOzD7MIcwn3Fld3dL9rxu5lrknux6gr/38fcbmH9i8phcUYn5JuY1zFFMcmIz9v7iXGKW67rEFq4HE5NN9curKpjeVnYeENLPial/hbIezx9V+G5IGkcZOUD5eAPTjB1CCygbBygPf8Z8hmlNuRhCuVhOubiFcvEA5WIc5eIGysX3EtOMvsc7Kq+rE1rwUXSF63X3ZbIOe76yzyId3nb9wzUhYTzhn554kHDlqvmcr6hwbE8K9zUqfatrtXRMC/mrzm/hfDOXH7ORe9xTmP2Yw5gUd6JrAGYY5ruYZ0i7/fBPmE8x+axzXoP5NuZ1zHuYVPKtP2YV5mbM9sTmpr4OT1SmPv5VqhwOU2vTbaRdP3IxYyYocKkJX+/LwnSpiS21NQB20o4Nxn1LuX+kwPlQ9sqSPa7CdhdzvhWmNWYQ52/Crg1/V8G2sJ06p13THr4ke111EDffUUazvwS7q/g7DQ5uFzbr2nNO7KAKWyV2HWEnjN5nTjrnenmpgNJ1eeR6We8MiDzeLMftQn2zAfraV8OHucRucdguU7drZdhljdbtPuhv2I3U7X4bthuh2+0J2w3X7R4L22XpdqvDdkZY5oftMnS7Kwy7YUZYXGG7UbrdO/0MOyMs+8J2RlieDNsZYflu2M4Iyw1hu3Tdrothl2n41zpsZ/j3fl/DzkjTn4XtDP/uMuwyjDTND9upeLTCrq1hN7JR99h2yk61/VFrltGmy7zrPyi/KXedI+/DZ+Q+vArjlrmJBVS8HkZfSa3UZboPl4SfQ5Sbq10XWa+VIn64LfsgneAIdd5Dr3gBcZP+n9S9zphKqV94yPooje0Pl0TE87BsnD9P4vkFieeOgUY8eYbEj3B/wx+xf79y18MqnvhhEU/TM/Tz6vxk5hO5jf5+X9mbL+RJF9W+nD9+7czxk/CZ45jcIbz+70Uyxq5nZ3TCfarqutqgOY7VrjjPxlxjxGmnchvUypLcv2r7xN/TwXxtrUX/dbM638zV0jhfaZxbqc5dbKzlsaEBawpGpouKk1Ffdio7wh6VVhWyOMIWN/bCO7sR9l5GWtWwhktE/7Of5Of1ys3X3c8Sktcxf8ek0b8ciZnnbmadnr3CaVKt+ltqQThjn+mV6vxI8i1J3ZuTjWsGmNMWO3Paij8By+cI3FrnQz/RfEyd/6L7DlLgaczLmPcx7d2MNXKbn2WDpS65riP8lrpujXsn9/9XMKcwrXGfjrmKNGgZ1jP6k2fUNV3xPcF4BnylN3bEOM0cPhYjIuGDoRcrA6UvuVpdu8mdzL+/wZwIXeUmZTAFmGWEN6IfaC5r6toWRppuUcfVbrWnOZ4PTpP+xEVr76YzofoSU10L1LUtpV5eCtMwXZXR7+kN4/nXw5X7ee/w/fuF3sa9wbj/3Be2M+4/a8N2xv3MG7bLNO41YbsM/V7zq15GfyDuvYZyyrGUU+xSjfuPKnPqvtKqt3Ffsdw=
*/