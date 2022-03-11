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