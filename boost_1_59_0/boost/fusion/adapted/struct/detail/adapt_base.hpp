/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_ADAPT_BASE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_is_tpl.hpp>

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/tag.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/typeof/typeof.hpp>


#define BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME_TEMPLATE_PARAMS(SEQ)              \
    BOOST_PP_SEQ_HEAD(SEQ)<BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TAIL(SEQ))>           \
    BOOST_PP_EMPTY()

#define BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(SEQ)                              \
    BOOST_PP_IF(                                                                \
        BOOST_PP_SEQ_HEAD(SEQ),                                                 \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME_TEMPLATE_PARAMS,                  \
        BOOST_PP_SEQ_HEAD)(BOOST_PP_SEQ_TAIL(SEQ))

#define BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS_IMPL_C(R, _, ELEM)     \
    (typename ELEM)
#define BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS_IMPL(SEQ)              \
    BOOST_PP_SEQ_ENUM(                                                          \
        BOOST_PP_SEQ_FOR_EACH(                                                  \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS_IMPL_C,            \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(SEQ)))
#define BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(SEQ)                   \
    BOOST_PP_IF(                                                                \
        BOOST_PP_SEQ_HEAD(SEQ),                                                 \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS_IMPL,                  \
        BOOST_PP_TUPLE_EAT(1))(SEQ)

#ifdef BOOST_MSVC
#   define BOOST_FUSION_ATTRIBUTE_TYPEOF(                                       \
        NAME_SEQ, ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ) \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS(                    \
        TEMPLATE_PARAMS_SEQ)                                                    \
                                                                                \
    struct deduced_attr_type {                                                  \
      static const BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj;        \
      typedef                                                                   \
      BOOST_PP_IF(BOOST_FUSION_ADAPT_IS_TPL(TEMPLATE_PARAMS_SEQ), typename, )   \
      BOOST_TYPEOF( PREFIX() obj.BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,      \
            0, ATTRIBUTE))                                                      \
      type;                                                                     \
    };                                                                          \
                                                                                \
    typedef                                                                     \
        BOOST_PP_IF(BOOST_FUSION_ADAPT_IS_TPL(TEMPLATE_PARAMS_SEQ), typename, ) \
        deduced_attr_type::type attribute_type;

#else 
#   define BOOST_FUSION_ATTRIBUTE_TYPEOF(                                       \
        NAME_SEQ, ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ) \
                                                                                \
    struct deduced_attr_type {                                                  \
      static const BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)& obj;        \
      typedef BOOST_TYPEOF(                                                     \
          PREFIX() obj.BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE, 0, ATTRIBUTE)) \
      type;                                                                     \
    };                                                                          \
                                                                                \
    typedef                                                                     \
        BOOST_PP_IF(BOOST_FUSION_ADAPT_IS_TPL(TEMPLATE_PARAMS_SEQ), typename, ) \
        deduced_attr_type::type attribute_type;

#endif

#define BOOST_FUSION_ATTRIBUTE_GIVENTYPE(                                       \
    NAME_SEQ, ATTRIBUTE, ATTRIBUTE_TUPLE_SIZE, PREFIX, TEMPLATE_PARAMS_SEQ)     \
    typedef                                                                     \
        BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE, 0, ATTRIBUTE) attribute_type;
   

#ifdef BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS
#   define BOOST_FUSION_ADAPT_STRUCT_TAG_OF_SPECIALIZATION(                     \
        MODIFIER, TEMPLATE_PARAMS_SEQ, NAME_SEQ, TAG)                           \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct tag_of<                                                              \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ) MODIFIER                \
      , void                                                                    \
    >                                                                           \
    {                                                                           \
        typedef TAG type;                                                       \
    };
#else
#   define BOOST_FUSION_ADAPT_STRUCT_TAG_OF_SPECIALIZATION(                     \
        MODIFIER, TEMPLATE_PARAMS_SEQ, NAME_SEQ, TAG)                           \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct tag_of<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ) MODIFIER>     \
    {                                                                           \
        typedef TAG type;                                                       \
    };
#endif

#define BOOST_FUSION_ADAPT_STRUCT_BASE_UNPACK_AND_CALL(R,DATA,I,ATTRIBUTE)      \
    BOOST_PP_TUPLE_ELEM(4,0,DATA)(                                              \
        BOOST_PP_TUPLE_ELEM(4,1,DATA),                                          \
        BOOST_PP_TUPLE_ELEM(4,2,DATA),                                          \
        BOOST_PP_TUPLE_ELEM(4,3,DATA),                                          \
        I,                                                                      \
        ATTRIBUTE)

#ifdef BOOST_MSVC
#   define BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAM(R,_,ELEM)     \
        typedef ELEM ELEM;
#   define BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS_IMPL(SEQ)    \
        BOOST_PP_SEQ_FOR_EACH(                                                  \
            BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAM,             \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(SEQ))
#   define BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS(SEQ)         \
        BOOST_PP_IF(                                                            \
            BOOST_PP_SEQ_HEAD(SEQ),                                             \
            BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS_IMPL,       \
            BOOST_PP_TUPLE_EAT(1))(SEQ)
#else
#   define BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS(SEQ)
#endif

#define BOOST_FUSION_ADAPT_STRUCT_C_BASE(                                       \
    TEMPLATE_PARAMS_SEQ,NAME_SEQ,IS_VIEW,                                       \
    I,PREFIX,ATTRIBUTE,ATTRIBUTE_TUPLE_SIZE,                                    \
    DEDUCE_TYPE)                                                                \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct access::struct_member<                                               \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                         \
      , I                                                                       \
    >                                                                           \
    {                                                                           \
        BOOST_PP_IF(DEDUCE_TYPE,                                                \
            BOOST_FUSION_ATTRIBUTE_TYPEOF, BOOST_FUSION_ATTRIBUTE_GIVENTYPE)(   \
                NAME_SEQ,                                                       \
                ATTRIBUTE,                                                      \
                ATTRIBUTE_TUPLE_SIZE,                                           \
                PREFIX,                                                         \
                TEMPLATE_PARAMS_SEQ)                                            \
                                                                                \
        BOOST_FUSION_ADAPT_STRUCT_MSVC_REDEFINE_TEMPLATE_PARAMS(                \
            TEMPLATE_PARAMS_SEQ)                                                \
                                                                                \
        typedef attribute_type type;                                            \
                                                                                \
        template<typename Seq>                                                  \
        struct apply                                                            \
        {                                                                       \
            typedef typename                                                    \
                add_reference<                                                  \
                    typename mpl::eval_if<                                      \
                        is_const<Seq>                                           \
                      , add_const<attribute_type>                               \
                      , mpl::identity<attribute_type>                           \
                    >::type                                                     \
                >::type                                                         \
            type;                                                               \
                                                                                \
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                            \
            static type                                                         \
            call(Seq& seq)                                                      \
            {                                                                   \
                return seq.PREFIX()                                             \
                    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,                   \
                        BOOST_PP_NOT(DEDUCE_TYPE), ATTRIBUTE);                  \
            }                                                                   \
        };                                                                      \
    };                                                                          \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct struct_member_name<                                                  \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                         \
      , I                                                                       \
    >                                                                           \
    {                                                                           \
        typedef char const* type;                                               \
                                                                                \
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                \
        static type                                                             \
        call()                                                                  \
        {                                                                       \
            return BOOST_PP_STRINGIZE(                                          \
               BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,                        \
                   BOOST_PP_NOT(DEDUCE_TYPE), ATTRIBUTE));                      \
        }                                                                       \
    };

#define BOOST_FUSION_ADAPT_STRUCT_BASE(                                         \
    TEMPLATE_PARAMS_SEQ,                                                        \
    NAME_SEQ,                                                                   \
    TAG,                                                                        \
    IS_VIEW,                                                                    \
    ATTRIBUTES_SEQ,                                                             \
    ATTRIBUTES_CALLBACK)                                                        \
                                                                                \
namespace boost                                                                 \
{                                                                               \
    namespace fusion                                                            \
    {                                                                           \
        namespace traits                                                        \
        {                                                                       \
            BOOST_FUSION_ADAPT_STRUCT_TAG_OF_SPECIALIZATION(                    \
                BOOST_PP_EMPTY(), TEMPLATE_PARAMS_SEQ, NAME_SEQ, TAG)           \
            BOOST_FUSION_ADAPT_STRUCT_TAG_OF_SPECIALIZATION(                    \
                const, TEMPLATE_PARAMS_SEQ, NAME_SEQ, TAG)                      \
        }                                                                       \
                                                                                \
        namespace extension                                                     \
        {                                                                       \
            BOOST_PP_IF(                                                        \
                BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ)),                \
                BOOST_PP_SEQ_FOR_EACH_I_R,                                      \
                BOOST_PP_TUPLE_EAT(4))(                                         \
                    1,                                                          \
                    BOOST_FUSION_ADAPT_STRUCT_BASE_UNPACK_AND_CALL,             \
                    (ATTRIBUTES_CALLBACK,TEMPLATE_PARAMS_SEQ,NAME_SEQ, IS_VIEW),\
                    BOOST_PP_SEQ_TAIL(ATTRIBUTES_SEQ))                          \
                                                                                \
            template<                                                           \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(               \
                    TEMPLATE_PARAMS_SEQ)                                        \
            >                                                                   \
            struct struct_size<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)> \
              : mpl::int_<BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ))>      \
            {};                                                                 \
                                                                                \
            template<                                                           \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(               \
                    TEMPLATE_PARAMS_SEQ)                                        \
            >                                                                   \
            struct struct_is_view<                                              \
                BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)                 \
            >                                                                   \
              : mpl::BOOST_PP_IIF(IS_VIEW,true_,false_)                         \
            {};                                                                 \
        }                                                                       \
    }                                                                           \
                                                                                \
    namespace mpl                                                               \
    {                                                                           \
        template<typename>                                                      \
        struct sequence_tag;                                                    \
                                                                                \
        template<                                                               \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(                   \
                TEMPLATE_PARAMS_SEQ)                                            \
        >                                                                       \
        struct sequence_tag<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ)>    \
        {                                                                       \
            typedef fusion::fusion_sequence_tag type;                           \
        };                                                                      \
                                                                                \
        template<                                                               \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(                   \
                TEMPLATE_PARAMS_SEQ)                                            \
        >                                                                       \
        struct sequence_tag<                                                    \
            BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ) const               \
        >                                                                       \
        {                                                                       \
            typedef fusion::fusion_sequence_tag type;                           \
        };                                                                      \
    }                                                                           \
}

#endif

/* adapt_base.hpp
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
*/