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