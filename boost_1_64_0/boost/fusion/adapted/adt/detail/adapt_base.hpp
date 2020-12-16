/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_DETAIL_ADAPT_BASE_HPP
#define BOOST_FUSION_ADAPTED_ADT_DETAIL_ADAPT_BASE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_is_tpl.hpp>

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/typeof/typeof.hpp>

#define BOOST_FUSION_ADAPT_ADT_GET_IDENTITY_TEMPLATE_IMPL(TEMPLATE_PARAMS_SEQ)  \
    typename detail::get_identity<                                              \
        lvalue                                                                  \
      , BOOST_PP_SEQ_ELEM(1,TEMPLATE_PARAMS_SEQ)                                \
    >::type

#define BOOST_FUSION_ADAPT_ADT_GET_IDENTITY_NON_TEMPLATE_IMPL(                  \
    TEMPLATE_PARAMS_SEQ)                                                        \
                                                                                \
    boost::remove_const<boost::remove_reference<lvalue>::type>::type

#define BOOST_FUSION_ADAPT_ADT_ATTRIBUTE_GETEXPR(ATTRIBUTE,                     \
    ATTRIBUTE_TUPLE_SIZE, DEDUCE_TYPE)                                          \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,                                   \
        BOOST_PP_IF(DEDUCE_TYPE, 0, 2), ATTRIBUTE)

#define BOOST_FUSION_ADAPT_ADT_ATTRIBUTE_SETEXPR(ATTRIBUTE,                     \
    ATTRIBUTE_TUPLE_SIZE, DEDUCE_TYPE)                                          \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,                                   \
        BOOST_PP_IF(DEDUCE_TYPE, 1, 3), ATTRIBUTE)

#ifdef BOOST_MSVC
#   define BOOST_FUSION_DEDUCED_ATTR_TYPE(NAME_SEQ, ATTRIBUTE,                  \
        ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ)                      \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS(                    \
        TEMPLATE_PARAMS_SEQ)                                                    \
                                                                                \
    struct deduced_attr_type {                                                  \
      static const BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj;        \
      typedef                                                                   \
          BOOST_PP_EXPR_IF(BOOST_FUSION_ADAPT_IS_TPL(TEMPLATE_PARAMS_SEQ),      \
                           typename)                                            \
          BOOST_TYPEOF( PREFIX() BOOST_FUSION_ADAPT_ADT_ATTRIBUTE_GETEXPR(      \
              ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, 1)) type;                        \
    };

#else
#   define BOOST_FUSION_DEDUCED_ATTR_TYPE(NAME_SEQ, ATTRIBUTE,                  \
        ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ)                      \
    struct deduced_attr_type {                                                  \
      static const BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj;        \
      typedef BOOST_TYPEOF( PREFIX() BOOST_FUSION_ADAPT_ADT_ATTRIBUTE_GETEXPR(  \
                      ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, 1)) type;                \
    };

#endif

#define BOOST_FUSION_ADT_ATTRIBUTE_TYPEOF(                                      \
    NAME_SEQ, ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ)     \
                                                                                \
    BOOST_FUSION_DEDUCED_ATTR_TYPE(                                             \
        NAME_SEQ, ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ) \
                                                                                \
    typedef                                                                     \
        BOOST_PP_EXPR_IF(BOOST_FUSION_ADAPT_IS_TPL(TEMPLATE_PARAMS_SEQ),        \
                         typename)                                              \
        deduced_attr_type::type type;                                           \
    typedef type const_type;

#define BOOST_FUSION_ADT_ATTRIBUTE_GIVENTYPE(                                   \
    NAME_SEQ, ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ)     \
                                                                                \
    typedef BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE, 0, ATTRIBUTE) type;       \
    typedef BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE, 1, ATTRIBUTE) const_type;


#define BOOST_FUSION_ADAPT_ADT_C_BASE(                                          \
    TEMPLATE_PARAMS_SEQ,NAME_SEQ,I,PREFIX,                                      \
    ATTRIBUTE,ATTRIBUTE_TUPLE_SIZE, DEDUCE_TYPE)                                \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct access::adt_attribute_access<                                        \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                         \
      , I                                                                       \
    >                                                                           \
    {                                                                           \
                                                                                \
        BOOST_PP_IF(DEDUCE_TYPE,                                                \
            BOOST_FUSION_ADT_ATTRIBUTE_TYPEOF,                                  \
            BOOST_FUSION_ADT_ATTRIBUTE_GIVENTYPE)(                              \
                NAME_SEQ,                                                       \
                ATTRIBUTE,                                                      \
                ATTRIBUTE_TUPLE_SIZE,                                           \
                PREFIX,                                                         \
                TEMPLATE_PARAMS_SEQ)                                            \
                                                                                \
        template<class Val>                                                     \
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED                          \
        static void                                                             \
        boost_fusion_adapt_adt_impl_set(                                        \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj,               \
            Val const& val)                                                     \
        {                                                                       \
           PREFIX() BOOST_FUSION_ADAPT_ADT_ATTRIBUTE_SETEXPR(ATTRIBUTE,         \
                ATTRIBUTE_TUPLE_SIZE, DEDUCE_TYPE);                             \
        }                                                                       \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        static type                                                             \
        boost_fusion_adapt_adt_impl_get(                                        \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj)               \
        {                                                                       \
            return PREFIX() BOOST_FUSION_ADAPT_ADT_ATTRIBUTE_GETEXPR(ATTRIBUTE, \
                ATTRIBUTE_TUPLE_SIZE, DEDUCE_TYPE);                             \
        }                                                                       \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        static const_type                                                       \
        boost_fusion_adapt_adt_impl_get(                                        \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ) const& obj)         \
        {                                                                       \
            return PREFIX() BOOST_FUSION_ADAPT_ADT_ATTRIBUTE_GETEXPR(ATTRIBUTE, \
                ATTRIBUTE_TUPLE_SIZE, DEDUCE_TYPE);                             \
        }                                                                       \
    };                                                                          \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct adt_attribute_proxy<                                                 \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                         \
      , I                                                                       \
      , true                                                                    \
    >                                                                           \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_EXPR_IF(BOOST_PP_SEQ_HEAD(TEMPLATE_PARAMS_SEQ), typename)  \
            access::adt_attribute_access<                                       \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                 \
              , I                                                               \
            >::const_type type;                                                 \
                                                                                \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        explicit                                                                \
        adt_attribute_proxy(                                                    \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ) const& o)           \
          : obj(&o)                                                             \
        {}                                                                      \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        type get() const                                                        \
        {                                                                       \
            return access::adt_attribute_access<                                \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                 \
              , I                                                               \
            >::boost_fusion_adapt_adt_impl_get(*obj);                           \
        }                                                                       \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        operator type() const                                                   \
        {                                                                       \
            return get();                                                       \
        }                                                                       \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ) const* obj;             \
    };                                                                          \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct adt_attribute_proxy<                                                 \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                         \
      , I                                                                       \
      , false                                                                   \
    >                                                                           \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_EXPR_IF(BOOST_PP_SEQ_HEAD(TEMPLATE_PARAMS_SEQ), typename)  \
            access::adt_attribute_access<                                       \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                 \
              , I                                                               \
            >::type type;                                                       \
                                                                                \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        explicit                                                                \
        adt_attribute_proxy(                                                    \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& o)                 \
          : obj(&o)                                                             \
        {}                                                                      \
                                                                                \
        template<class Val>                                                     \
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED                          \
        adt_attribute_proxy&                                                    \
        operator=(Val const& val)                                               \
        {                                                                       \
            access::adt_attribute_access<                                       \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                 \
              , I                                                               \
            >::boost_fusion_adapt_adt_impl_set(*obj, val);                      \
            return *this;                                                       \
        }                                                                       \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        type get() const                                                        \
        {                                                                       \
            return access::adt_attribute_access<                                \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                 \
              , I                                                               \
            >::boost_fusion_adapt_adt_impl_get(*obj);                           \
        }                                                                       \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        operator type() const                                                   \
        {                                                                       \
            return get();                                                       \
        }                                                                       \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)* obj;                   \
    };                                                                          \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct access::struct_member<                                               \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                         \
      , I                                                                       \
    >                                                                           \
    {                                                                           \
        typedef BOOST_PP_EXPR_IF(BOOST_PP_SEQ_HEAD(TEMPLATE_PARAMS_SEQ),        \
                                 typename)                                      \
            adt_attribute_proxy<                                                \
                          BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)       \
                        , I                                                     \
                        , false                                                 \
                      >::type lvalue;                                           \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS(                \
            TEMPLATE_PARAMS_SEQ)                                                \
                                                                                \
        typedef                                                                 \
            BOOST_PP_IF(                                                        \
                BOOST_PP_SEQ_HEAD(TEMPLATE_PARAMS_SEQ),                         \
                BOOST_FUSION_ADAPT_ADT_GET_IDENTITY_TEMPLATE_IMPL,              \
                BOOST_FUSION_ADAPT_ADT_GET_IDENTITY_NON_TEMPLATE_IMPL)(         \
                    TEMPLATE_PARAMS_SEQ)                                        \
        type;                                                                   \
                                                                                \
        template<typename Seq>                                                  \
        struct apply                                                            \
        {                                                                       \
            typedef                                                             \
                adt_attribute_proxy<                                            \
                    BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)             \
                  , I                                                           \
                  , is_const<Seq>::value                                        \
                >                                                               \
            type;                                                               \
                                                                                \
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                            \
            static type                                                         \
            call(Seq& obj)                                                      \
            {                                                                   \
                return type(obj);                                               \
            }                                                                   \
        };                                                                      \
    };

#endif

/* adapt_base.hpp
D88fkT8yf1T+6Pwx+WPzx+WPz5+QPzF/Uv7k/Cn5U/On5U/Pn5E/M39W/uz8Oflz8+flz89fkL8wf1H+4vwl+Uvzl+Uvz1+RvzJ/Vf7q/DX5a/PX5a/P35C/MX9T/ub8Lflb87flb8/fkb8zf1f+7vw9+Xvz9+Xvzz+QfzD/UP7h/CP5R/OP5R/PP5F/Mv9U/um8015rDE73h72Ds81bNjsdXDo5M7eyUpudW5lZnl9anV9cqK0PWq0U3h6m0G7r5MT03EptrV1rb7RqrW6RfwE11ho+vb42ObU7gkLAj9FsUbjVWHN5bjgqvBcX1usP272uKsKqNSyzrh1vnS4xxPexUffkoN63JBEr883FwXK9i2K1wgiApjwSKiroVnfYXm+3BjPHeu2GSRbjSB2jcSYqTq/CpMqkWpisTS8cBVeH98yv1lZWl+cX9tUax1qN4yFa5ByBG9DOWiKLBNStb7Zq/UG7G7MgUIyNNmt11YhwtEcKS8f1pDu4FNWEsDgWCbW4eGBuesFGmVs4dHBueXp1brbIKQKhkxRWQ8137Qg5qVxRcoShKjFWmemwV9uzoNG9ofj75hYQ68D8nedmV+cPztXqzXOTDGsGMausd8ypLAV1SjKsRcQs1K+aUVNDJNzw+G7zxngoWtjM89M7owyABYmBRAkXVuf2zS3XGpt9H2iOfMBmTAjsIgDKNo3hUQJv+8ljoaCqAEgXoNIFuJa0cOjAgaIKRKJ8IqjwxT13mptZrTUGrfqw5UFI7gHIwCMpi5nVOduPF2bn9iJmggOdxygU76PUrDGczDctBylzaWb1SJEfkUUTNVqDYW29U99QHiONdTeTcK/dTOIw+AiHmA6lqiQAI8bSEqgKCVRCAuhkdXrPgTlfvzEHKk7jED9gpDKJk6cSDk/3TcIVv3FWSgXW+/1asz6sE0xN42MosbUZQED6HZizA0MKh1JxEXNnH5pbmJkz42wAErDqRTC6KWoF59xMoI1Oq96FjcccSOqiRcwBKSPoNkT3+qddgCoRdamosWkmsC1OBhQzqvX6qDOsbdbVcY/ZaXU3hscSkO1oXnckWg8aEYKJ2qkkWFv3hUf2Ib0tADBxOF1bmJ/14aA2WzLNjIQiwJUeWt2728dgtRFA1V3dNRnpG5jtViFCCcNR3x/qaXx36GZ7fd2Sbk/0BnZ/NA+HcH/cDgZrAqELmEa3Nah32ue3msP2ZlnU0SUIBuskCnK4TFiUT2E0g8tqDFtDWwpxqziogEP1643jkPO8ESb6blkQ3acmXXKrosGt4GDxkCju0ML84bnllXAOE3PQDmkcNUozoGpHBpjgjG8LAMgcfAgNURu3TW3o4yQdEM86QPsGAoBsxIOggRjwRUVvifUBMFQFoFALh+dX5sOhKcaRQ4xSJvC+xWC42WuOOi2LQcj6WqflwWtdqiKo0bpDatXCWNbbXYwsWE42DY6F57CS25xqY/XSs4T1Yk0sa5XO2vpl052Qvotc1wPsxPYSgFWundtqmNTtqSYVAcIWAUE2x2X6VBmXEC+BFYyAkcuGI0YSD7AtQwjE8AE0BwFhAsT2KV/GuFJd+Gg/VVDAuHe6JJrRrZJqb3QDstYYniIIHTzI4kRr0F434+vmmrZwtH0/hLoWM42E3M/XlYVUA+UGodrSS/ZHGON6jZLwW5jERSFTNGgN6xtTWBoTAXZBkLTePoazh+HuXxxdmKmdM40VN2ZA5WSjGeAmC8LshKzTQWyVYKFPjAtpVrDjMlLiKEQ8WW87sdc6vcZx6G+kjDxmJgUvdwxrFRNNCzAaDFrw7uf21kq0zA6tbaBxh/WTtlWtUe/DO5gCdGFOLnAdAydXGIsn1KE=
*/