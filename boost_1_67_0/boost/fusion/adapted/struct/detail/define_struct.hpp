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