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
GWPRP/EVep8/Mhtos5LzvshJEync6ZOherhTcj7P8J1pG0j3vrY23d9rLQDd6LEUKzc/AhAv2XcarztbLUy1t1kwBO3dKAxyo4G9Cr65ZhpcETFFjdiIbihCZPO9FOS/8ogv+wBpyUNN0AZX+2Y6ROTMjxC3eNFwuG6Yy9/TFUOcfzC6ijG6+ark6TAibYqueaNPKLAfBi3tlUkJbLJYKBic8mv4Z3ILCj6jpXfOMvgeRiqfYcoglBiiZxDK9FWQB3/baoxMiXOFgd4zhg2x81G0mJKKPitk1ZI56pC9GBhlMd92iShVClrJDsaVtBffAXUhXbwpHjw4CLCtN1gpD+4ArijFdhRP6wHms8nBP1VPAOHhpc/W7pgGS28vXm6hb7L4myxsf6LePlrA+y54MKqIJGdxwPn3GO2wuJch638N9+zhUJkeQSU27wKmPxWsal65WVl6N5DVxD65RwZCxNLnNxJ/QPAv+yiAtSobBRqlCyffiQhCwhIVGYjiQZuzGTXg6UNp2qjqwhjksGBTPh1VB/RgIEiX7lPOwyL4wQRIcd1M6qK8IK9X1ycSfO74hMBnxxdsp8XP1fB0C+Rc/rkRrgCgEjy+3UXlgRP25a/EFh23FqTDGFIhbtUCh2WNOxbBwmsVBTeDx4bXHXkiEH3LhKYgU0yg2RYNSuC70+IkBKL12qj7Y/EcThaEqGhVwsCVl+9v7vyg/vrP
*/