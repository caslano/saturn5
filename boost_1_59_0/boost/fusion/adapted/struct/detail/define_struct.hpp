/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_DEFINE_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_DEFINE_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/namespace.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/expr_if.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#define BOOST_FUSION_DEFINE_STRUCT_FILLER_0(X, Y)                               \
    ((X, Y)) BOOST_FUSION_DEFINE_STRUCT_FILLER_1
#define BOOST_FUSION_DEFINE_STRUCT_FILLER_1(X, Y)                               \
    ((X, Y)) BOOST_FUSION_DEFINE_STRUCT_FILLER_0
#define BOOST_FUSION_DEFINE_STRUCT_FILLER_0_END
#define BOOST_FUSION_DEFINE_STRUCT_FILLER_1_END

#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS

#define BOOST_FUSION_DEFINE_STRUCT_COPY_CTOR_FILLER_I(                          \
    R, ATTRIBUTE_TUPLE_SIZE, I, ATTRIBUTE)                                      \
                                                                                \
    BOOST_PP_COMMA_IF(I)                                                        \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)(                      \
        other_self.BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE))

#define BOOST_FUSION_DEFINE_STRUCT_COPY_CTOR(                                   \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
    BOOST_FUSION_GPU_ENABLED                                                    \
    NAME(self_type const& other_self)                                           \
      : BOOST_PP_SEQ_FOR_EACH_I_R(                                              \
            1,                                                                  \
            BOOST_FUSION_DEFINE_STRUCT_COPY_CTOR_FILLER_I,                      \
            ATTRIBUTE_TUPLE_SIZE,                                               \
            ATTRIBUTES_SEQ)                                                     \
    {}

// Use templated version instead.
#define BOOST_FUSION_DEFINE_STRUCT_COPY_ASSIGN_FILLER_I(                        \
    R, ATTRIBUTE_TUPLE_SIZE, I_, ATTRIBUTE)                                     \
                                                                                \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)=                      \
        other.BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE);

#define BOOST_FUSION_DEFINE_STRUCT_COPY_ASSIGN_OP(                              \
    ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                       \
                                                                                \
    BOOST_FUSION_GPU_ENABLED                                                    \
    self_type& operator=(self_type const& other)                                \
    {                                                                           \
        BOOST_PP_SEQ_FOR_EACH_I_R(                                              \
            1,                                                                  \
            BOOST_FUSION_DEFINE_STRUCT_COPY_ASSIGN_FILLER_I,                    \
            ATTRIBUTE_TUPLE_SIZE,                                               \
            ATTRIBUTES_SEQ)                                                     \
                                                                                \
        return *this;                                                           \
    }

#else // BOOST_NO_CXX11_DEFAULTED_FUNCTIONS

#define BOOST_FUSION_DEFINE_STRUCT_COPY_CTOR(                                   \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
    BOOST_FUSION_GPU_ENABLED NAME(self_type const&) = default;

#define BOOST_FUSION_DEFINE_STRUCT_COPY_ASSIGN_OP(                              \
    ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                       \
                                                                                \
    BOOST_FUSION_GPU_ENABLED self_type& operator=(self_type const&) = default;

#endif // BOOST_NO_CXX11_DEFAULTED_FUNCTIONS

#define BOOST_FUSION_DEFINE_STRUCT_ASSIGN_FILLER_I(                             \
    R, ATTRIBUTE_TUPLE_SIZE, I_, ATTRIBUTE)                                     \
                                                                                \
    BOOST_PP_EXPR_IF(                                                           \
        I_,                                                                     \
        typedef typename                                                        \
            boost::fusion::result_of::next<                                     \
                BOOST_PP_CAT(I,BOOST_PP_DEC(I_))                                \
            >::type                                                             \
        BOOST_PP_CAT(I,I_);                                                     \
        BOOST_PP_CAT(I,I_) BOOST_PP_CAT(i,I_)=                                  \
                boost::fusion::next(BOOST_PP_CAT(i,BOOST_PP_DEC(I_)));          \
    )                                                                           \
                                                                                \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)=                      \
        boost::fusion::deref(BOOST_PP_CAT(i,I_));

#define BOOST_FUSION_DEFINE_STRUCT_ASSIGN_OP(                                   \
    ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                       \
                                                                                \
    template<typename Seq>                                                      \
    BOOST_FUSION_GPU_ENABLED                                                    \
    self_type&                                                                  \
    operator=(Seq const& seq)                                                   \
    {                                                                           \
        typedef typename                                                        \
            boost::fusion::result_of::begin<Seq const>::type                    \
        I0;                                                                     \
        I0 i0=boost::fusion::begin(seq);                                        \
                                                                                \
        BOOST_PP_SEQ_FOR_EACH_I_R(                                              \
            1,                                                                  \
            BOOST_FUSION_DEFINE_STRUCT_ASSIGN_FILLER_I,                         \
            ATTRIBUTE_TUPLE_SIZE,                                               \
            ATTRIBUTES_SEQ)                                                     \
                                                                                \
        return *this;                                                           \
    }

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES

#define BOOST_FUSION_DEFINE_STRUCT_MOVE_CTOR(NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)
#define BOOST_FUSION_DEFINE_STRUCT_MOVE_ASSIGN_OP(ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)

#else // BOOST_NO_CXX11_RVALUE_REFERENCES

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) \
 || BOOST_WORKAROUND(BOOST_GCC, < 40500) \
 || BOOST_WORKAROUND(BOOST_MSVC, == 1800)

#define BOOST_FUSION_DEFINE_STRUCT_MOVE_CTOR_FILLER_I(                          \
    R, ATTRIBUTE_TUPLE_SIZE, I, ATTRIBUTE)                                      \
                                                                                \
    BOOST_PP_COMMA_IF(I)                                                        \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)(std::move(            \
        other_self.BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)))

#define BOOST_FUSION_DEFINE_STRUCT_MOVE_CTOR(                                   \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
    BOOST_FUSION_GPU_ENABLED                                                    \
    NAME(self_type&& other_self)                                                \
      : BOOST_PP_SEQ_FOR_EACH_I_R(                                              \
            1,                                                                  \
            BOOST_FUSION_DEFINE_STRUCT_MOVE_CTOR_FILLER_I,                      \
            ATTRIBUTE_TUPLE_SIZE,                                               \
            ATTRIBUTES_SEQ)                                                     \
    {}

#else // BOOST_NO_CXX11_DEFAULTED_FUNCTIONS

#define BOOST_FUSION_DEFINE_STRUCT_MOVE_CTOR(                                   \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
    BOOST_FUSION_GPU_ENABLED NAME(self_type&&) = default;

#endif // BOOST_NO_CXX11_DEFAULTED_FUNCTIONS

#if defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) \
 || BOOST_WORKAROUND(BOOST_GCC, < 40600) \
 || BOOST_WORKAROUND(BOOST_MSVC, == 1800)

#define BOOST_FUSION_DEFINE_STRUCT_MOVE_ASSIGN_FILLER_I(                        \
    R, ATTRIBUTE_TUPLE_SIZE, I_, ATTRIBUTE)                                     \
                                                                                \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)=std::move(            \
        other.BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE));

#define BOOST_FUSION_DEFINE_STRUCT_MOVE_ASSIGN_OP(                              \
    ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                       \
                                                                                \
    BOOST_FUSION_GPU_ENABLED                                                    \
    self_type& operator=(self_type&& other)                                     \
    {                                                                           \
        BOOST_PP_SEQ_FOR_EACH_I_R(                                              \
            1,                                                                  \
            BOOST_FUSION_DEFINE_STRUCT_MOVE_ASSIGN_FILLER_I,                    \
            ATTRIBUTE_TUPLE_SIZE,                                               \
            ATTRIBUTES_SEQ)                                                     \
                                                                                \
        return *this;                                                           \
    }

#else // BOOST_NO_CXX11_DEFAULTED_FUNCTIONS

#define BOOST_FUSION_DEFINE_STRUCT_MOVE_ASSIGN_OP(                              \
    ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                       \
                                                                                \
    BOOST_FUSION_GPU_ENABLED self_type& operator=(self_type&&) = default;

#endif // BOOST_NO_CXX11_DEFAULTED_FUNCTIONS

#endif // BOOST_NO_CXX11_RVALUE_REFERENCES

#define BOOST_FUSION_DEFINE_STRUCT_ATTR_I(R, ATTRIBUTE_TUPLE_SIZE, ATTRIBUTE)   \
                                                                                \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,0,ATTRIBUTE)                       \
        BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE);

#define BOOST_FUSION_DEFINE_STRUCT_SEQ_CTOR_FILLER_I(                           \
    R, ATTRIBUTE_TUPLE_SIZE, I, ATTRIBUTE)                                      \
                                                                                \
    BOOST_PP_COMMA_IF(I)                                                        \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)(                      \
        boost::fusion::deref(boost::fusion::advance_c<I>(boost::fusion::begin(  \
            seq))))

#define BOOST_FUSION_DEFINE_STRUCT_SEQ_CTOR_DISABLER(                           \
    ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                       \
                                                                                \
    , typename boost::disable_if<                                               \
        boost::is_convertible<                                                  \
            Seq const&                                                          \
          , BOOST_PP_TUPLE_ELEM(                                                \
                ATTRIBUTE_TUPLE_SIZE,                                           \
                0,                                                              \
                BOOST_PP_SEQ_HEAD(ATTRIBUTES_SEQ))                              \
        >                                                                       \
    >::type* =0

#define BOOST_FUSION_DEFINE_STRUCT_SEQ_DEFAULT_CTOR_FILLER_I(                   \
    R, ATTRIBUTE_TUPLE_SIZE, I, ATTRIBUTE)                                      \
                                                                                \
    BOOST_PP_COMMA_IF(I)                                                        \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)()

#define BOOST_FUSION_DEFINE_STRUCT_IMPL_IMPL(                                   \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
    BOOST_PP_SEQ_FOR_EACH_R(                                                    \
        1,                                                                      \
        BOOST_FUSION_DEFINE_STRUCT_ATTR_I,                                      \
        ATTRIBUTE_TUPLE_SIZE,                                                   \
        ATTRIBUTES_SEQ)                                                         \
                                                                                \
    BOOST_FUSION_GPU_ENABLED                                                    \
    NAME()                                                                      \
      : BOOST_PP_SEQ_FOR_EACH_I_R(                                              \
            1,                                                                  \
            BOOST_FUSION_DEFINE_STRUCT_SEQ_DEFAULT_CTOR_FILLER_I,               \
            ATTRIBUTE_TUPLE_SIZE,                                               \
            ATTRIBUTES_SEQ)                                                     \
    {}                                                                          \
                                                                                \
    BOOST_FUSION_DEFINE_STRUCT_COPY_CTOR(                                       \
        NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)  \
    BOOST_FUSION_DEFINE_STRUCT_MOVE_CTOR(                                       \
        NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)  \
                                                                                \
    template<typename Seq>                                                      \
    BOOST_FUSION_GPU_ENABLED                                                    \
    NAME(Seq const& seq                                                         \
        BOOST_PP_IF(                                                            \
            BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ)),                    \
            BOOST_PP_TUPLE_EAT(2),                                              \
            BOOST_FUSION_DEFINE_STRUCT_SEQ_CTOR_DISABLER)(                      \
                ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                           \
        )                                                                       \
      : BOOST_PP_SEQ_FOR_EACH_I_R(                                              \
            1,                                                                  \
            BOOST_FUSION_DEFINE_STRUCT_SEQ_CTOR_FILLER_I,                       \
            ATTRIBUTE_TUPLE_SIZE,                                               \
            ATTRIBUTES_SEQ)                                                     \
    {}                                                                          \
                                                                                \
    BOOST_FUSION_DEFINE_STRUCT_COPY_ASSIGN_OP(                                  \
        ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                   \
    BOOST_FUSION_DEFINE_STRUCT_MOVE_ASSIGN_OP(                                  \
        ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                   \
    BOOST_FUSION_DEFINE_STRUCT_ASSIGN_OP(ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)

#define BOOST_FUSION_DEFINE_STRUCT_CTOR_1(                                      \
        NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                             \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        explicit                                                                \
        NAME(boost::call_traits<                                                \
                BOOST_PP_TUPLE_ELEM(                                            \
                    ATTRIBUTE_TUPLE_SIZE,0,BOOST_PP_SEQ_HEAD(ATTRIBUTES_SEQ))   \
            >::param_type arg)                                                  \
          : BOOST_PP_TUPLE_ELEM(                                                \
                ATTRIBUTE_TUPLE_SIZE,1,BOOST_PP_SEQ_HEAD(ATTRIBUTES_SEQ))(arg)  \
        {}

#define BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR_1(                                  \
        TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)        \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        explicit                                                                \
        NAME(typename boost::call_traits<                                       \
                typename boost::fusion::detail::get_first_arg<                  \
                    BOOST_PP_TUPLE_ELEM(                                        \
                        ATTRIBUTE_TUPLE_SIZE,                                   \
                        0,                                                      \
                        BOOST_PP_SEQ_HEAD(ATTRIBUTES_SEQ))                      \
                  , BOOST_PP_SEQ_HEAD(TEMPLATE_PARAMS_SEQ)                      \
                >::type                                                         \
            >::param_type arg)                                                  \
          : BOOST_PP_TUPLE_ELEM(                                                \
                ATTRIBUTE_TUPLE_SIZE,1,BOOST_PP_SEQ_HEAD(ATTRIBUTES_SEQ))(arg)  \
        {}

#define BOOST_FUSION_DEFINE_STRUCT_CTOR_FILLER_I(                               \
    R, ATTRIBUTE_TUPLE_SIZE, I, ATTRIBUTE)                                      \
                                                                                \
    BOOST_PP_COMMA_IF(I)                                                        \
    BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,1,ATTRIBUTE)(BOOST_PP_CAT(_,I))

#define BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR_ARG_I(R, DATA, I, ATTRIBUTE)        \
                                                                                \
        BOOST_PP_COMMA_IF(I)                                                    \
        typename boost::call_traits<                                            \
            typename boost::fusion::detail::get_first_arg<                      \
                BOOST_PP_TUPLE_ELEM(                                            \
                    BOOST_PP_TUPLE_ELEM(3,0,DATA),                              \
                    0,                                                          \
                    ATTRIBUTE)                                                  \
              , BOOST_PP_TUPLE_ELEM(3,2,DATA)                                   \
            >::type                                                             \
        >::param_type BOOST_PP_CAT(_,I)

#define BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR_N(                                  \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)            \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                                \
        NAME(BOOST_PP_SEQ_FOR_EACH_I_R(                                         \
                1,                                                              \
                BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR_ARG_I,                      \
                (                                                               \
                    ATTRIBUTE_TUPLE_SIZE,                                       \
                    BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ),                          \
                    BOOST_PP_SEQ_HEAD(TEMPLATE_PARAMS_SEQ)                      \
                ),                                                              \
                ATTRIBUTES_SEQ))                                                \
          : BOOST_PP_SEQ_FOR_EACH_I_R(                                          \
                1,                                                              \
                BOOST_FUSION_DEFINE_STRUCT_CTOR_FILLER_I,                       \
                ATTRIBUTE_TUPLE_SIZE,                                           \
                ATTRIBUTES_SEQ)                                                 \
        {}

#define BOOST_FUSION_DEFINE_STRUCT_CTOR_ARG_I(                                  \
        R, ATTRIBUTE_TUPLE_SIZE, I, ATTRIBUTE)                                  \
                                                                                \
        BOOST_PP_COMMA_IF(I)                                                    \
        boost::call_traits<                                                     \
            BOOST_PP_TUPLE_ELEM(ATTRIBUTE_TUPLE_SIZE,0,ATTRIBUTE)               \
        >::param_type BOOST_PP_CAT(_,I)

#define BOOST_FUSION_DEFINE_STRUCT_CTOR_N(                                      \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
        BOOST_FUSION_GPU_ENABLED                                \
        NAME(BOOST_PP_SEQ_FOR_EACH_I_R(                                         \
                1,                                                              \
                BOOST_FUSION_DEFINE_STRUCT_CTOR_ARG_I,                          \
                ATTRIBUTE_TUPLE_SIZE,                                           \
                ATTRIBUTES_SEQ))                                                \
          : BOOST_PP_SEQ_FOR_EACH_I_R(                                          \
                1,                                                              \
                BOOST_FUSION_DEFINE_STRUCT_CTOR_FILLER_I,                       \
                ATTRIBUTE_TUPLE_SIZE,                                           \
                ATTRIBUTES_SEQ)                                                 \
        {}

#define BOOST_FUSION_DEFINE_STRUCT_CTOR(                                        \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
    BOOST_PP_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ)),                \
        BOOST_FUSION_DEFINE_STRUCT_CTOR_N,                                      \
        BOOST_FUSION_DEFINE_STRUCT_CTOR_1)(                                     \
            NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)

#define BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR(                                    \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)            \
                                                                                \
    BOOST_PP_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ)),                \
        BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR_N,                                  \
        BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR_1)(                                 \
            TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)

#define BOOST_FUSION_DEFINE_NONEMPTY_STRUCT_IMPL(                               \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                                 \
                                                                                \
        BOOST_FUSION_DEFINE_STRUCT_IMPL_IMPL(                                   \
            NAME, BOOST_PP_SEQ_TAIL(ATTRIBUTES_SEQ), ATTRIBUTE_TUPLE_SIZE)      \
                                                                                \
        BOOST_FUSION_DEFINE_STRUCT_CTOR(                                        \
            NAME, BOOST_PP_SEQ_TAIL(ATTRIBUTES_SEQ), ATTRIBUTE_TUPLE_SIZE)

#define BOOST_FUSION_DEFINE_EMPTY_STRUCT_IMPL(                                  \
    NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)

#define BOOST_FUSION_DEFINE_STRUCT_IMPL(                                        \
    NAMESPACE_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                  \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)         \
                                                                                \
    struct NAME                                                                 \
    {                                                                           \
        typedef NAME self_type;                                                 \
                                                                                \
        BOOST_PP_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ)),            \
            BOOST_FUSION_DEFINE_NONEMPTY_STRUCT_IMPL,                           \
            BOOST_FUSION_DEFINE_EMPTY_STRUCT_IMPL)(                             \
                NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)                     \
    };                                                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)

#define BOOST_FUSION_DEFINE_NONEMPTY_TPL_STRUCT_IMPL(                           \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)            \
                                                                                \
        BOOST_FUSION_DEFINE_STRUCT_IMPL_IMPL(                                   \
            NAME, BOOST_PP_SEQ_TAIL(ATTRIBUTES_SEQ), ATTRIBUTE_TUPLE_SIZE)      \
                                                                                \
        BOOST_FUSION_DEFINE_TPL_STRUCT_CTOR(                                    \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME,                                                               \
            BOOST_PP_SEQ_TAIL(ATTRIBUTES_SEQ),                                  \
            ATTRIBUTE_TUPLE_SIZE)

#define BOOST_FUSION_DEFINE_EMPTY_TPL_STRUCT_IMPL(                              \
    TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)

#define BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                    \
    TEMPLATE_PARAMS_SEQ,                                                        \
    NAMESPACE_SEQ,                                                              \
    NAME,                                                                       \
    ATTRIBUTES_SEQ,                                                             \
    ATTRIBUTE_TUPLE_SIZE)                                                       \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)         \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS_IMPL(                  \
            (0)TEMPLATE_PARAMS_SEQ)                                             \
    >                                                                           \
    struct NAME                                                                 \
    {                                                                           \
        typedef NAME self_type;                                                 \
                                                                                \
        BOOST_PP_IF(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ATTRIBUTES_SEQ)),            \
            BOOST_FUSION_DEFINE_NONEMPTY_TPL_STRUCT_IMPL,                       \
            BOOST_FUSION_DEFINE_EMPTY_TPL_STRUCT_IMPL)(                         \
                TEMPLATE_PARAMS_SEQ, NAME, ATTRIBUTES_SEQ, ATTRIBUTE_TUPLE_SIZE)\
    };                                                                          \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)

namespace boost { namespace fusion { namespace detail
{
    template<typename A1, typename A2>
    struct get_first_arg
    {
        typedef A1 type;
    };
}}}

#endif

/* define_struct.hpp
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
*/