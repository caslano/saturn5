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
5b9mdU8beoyi3OxrfJQKzjU+PmcTDVvjm8rfmGt8fO74zfwI64KLDyE7lrrsMyWY6eX6bM33UPaliPE325pKXl7h7LR8NM1cxhvv+FtuVkGGksWsE44w+Yp0nX7tgO39qLXWKm9kO1nu9q0i3Zs+cvedb+0qzy/ZMHdFk+0tV41asPfivAOpd9f93nFd702730eOZLer7vbCLvfJ83smveg/5uofH2m3Znu7TneNGhD5/rW73be63+92v8cd+T67+/33yHbT3O2URbYTN18937ck7o6umwsOXvnNiqcXrGj7MM63qHoYqMq/+rvqji+/ddPQNl0+SUB9299Bnl89YEWv0rOM6Tf367RnbXzroRHv3av744iG9w3UPQRld0+2GrZRkFzh1/rNFtKOxyIQxaf0MV8gc2qwEFwMXkb9rfdSb+sn1Mv6BfWy/kC9rD6P1st6DHgbeCx4O9gcvAPsC94NDpH0gKPAe8DzwXslXg/1+oIrwDJwFbgCfAB8AHyQeqYfot68KoN3BXiHoIxrTpuZzw4G7SCAHcCO4FmqL9f68k4Hc9QYVOtR7QLeDnYFn1F9v9Yz2x38WJ3L1vope4DVYE9D6xnuZWj7FL3BdmAfsD14JngGmACOA88Gp4LnGFqPal+JF+xnaL2J6BZoN473AnhfoMxhf24C/MlacQqXRCbSDtskMFnmj5ZwKhnOMJdwLmI4kxnOxQznEnCgOs8Y0vvHc/V4wHCsev/WsJzXSb7BpyXf1EMwjHoIlN1pMF2Nc7W9smcNrVd9E+OJl/Qynj6Mx6qXcDDjGQKK36Eh+3g8h87z6WUOfYFJ8Kdt41OPHMMZzfoAf0qP+LlgHjgWXKhsE1nsSjH8LaxnVn3CzxlaD+ELYFfwRbAnuBWsMJTMUvZPXgPhx3gbHCr2JcCxHrVmrfStvwfOAXcaWo/pB+Dz4C6mI9ngWXKeMS9z2GP6iOnYQ3t/n4LzwL+C85WedW1X6nPwJn0Gl3qKeQ6c58PLHHqK97P8fmB9+ZH15CA4BPxJ6jX4M6gmWx6tz9nj0fH7PDo+P3g3v4ssigW/BRuAP4G/82h93Q09Wo4cDbYB0bZUe8Kz+UngseC5YFNwMnicR7erZmAB2Nyj21cL8DqwJfW+twJFHh4PbgBPBLeCJ4FvgHHg++Ap4CdgO/BL8FTwn2B70OvVdu1OAzuCZ4CdwYHg6ZI+8AxwItgdvBDsQf3xPcEA2It24XpTj/yZtAeXAD4Jng2ulXcAvgj29Wj9xP3Ab8D+tAc30KP1Eg+WcgKHgKeCieA54HBwNDhCygsc6THbC8+1Gwtd2svt1Ld/F3gK9e73pd7986l3P4d69+eA94GXgysYfsDgWXSpawz/aDCL4edR/3Y+2BksAHuBQZ+OpwQcC84CrwZn+3S9LQUfBueA68FLqS94Lsh4eY4cddsl3gsY74WM9yLGm8F4pzDeTMabxXizGe9UxjsN/BTM8Zlylme9jTQXOXsF453PeK/0afm1gPrGFzKcVPHDcO5weS9X+7RcvY7p/r1Pt8MlPi33/wBKGNeDko4bwGvBpT5TvvJstNHJRb5+xPf+sdQjEG3A1CvN32Xyd1Z9NLP5u7lgF3AeKL9BG1TjicvBS6QcGN5Sg+eT2YeXOfTGL2B4izxa3lxDu2+Lwf6Gti84TMqB9fD3Ht2PLAFvkHIAl0s5gOskPo9+bzeDG5W+Za1v+o/gq+reYah8eMYY5U5Zb5aP7hfVnA48yqLHNEl+y9+dx/xZy2cH5ee74PGGkvNqvPU+mGhoeT9GrQGY6ShjeBfwuzUd8xro+nQZmCJ1pkGN/nGeqeVZ2zKH/vFlPrZnsDf1cvelXu4=
*/