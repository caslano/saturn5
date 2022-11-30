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
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
*/