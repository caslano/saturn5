///////////////////////////////////////////////////////////////////////////////
/// \file operators.hpp
/// Contains all the overloaded operators that make it possible to build
/// Proto expression trees.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_OPERATORS_HPP_EAN_04_01_2005
#define BOOST_PROTO_OPERATORS_HPP_EAN_04_01_2005

#include <boost/config.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/domain.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/generate.hpp>
#include <boost/proto/make_expr.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename MakeExpr, typename Grammar>
        struct lazy_matches
          : proto::matches<typename MakeExpr::type, Grammar>
        {};

        template<typename Domain, typename Grammar, typename Trait, typename Tag, typename Arg>
        struct enable_unary
          : boost::lazy_enable_if_c<
                boost::mpl::and_<
                    Trait
                  , lazy_matches<result_of::make_expr<Tag, basic_default_domain, Arg>, Grammar>
                >::value
              , result_of::make_expr<Tag, Domain, Arg>
            >
        {};

        template<typename Domain, typename Trait, typename Tag, typename Arg>
        struct enable_unary<Domain, proto::_, Trait, Tag, Arg &>
          : boost::lazy_enable_if_c<
                Trait::value
              , result_of::make_expr<Tag, Domain, Arg &>
            >
        {};

        template<typename Trait, typename Tag, typename Arg>
        struct enable_unary<deduce_domain, not_a_grammar, Trait, Tag, Arg &>
          : enable_unary<
                typename domain_of<Arg>::type
              , typename domain_of<Arg>::type::proto_grammar
              , Trait
              , Tag
              , Arg &
            >
        {};

        template<typename Domain, typename Grammar, typename Trait, typename Tag, typename Left, typename Right>
        struct enable_binary
          : boost::lazy_enable_if_c<
                boost::mpl::and_<
                    Trait
                  , lazy_matches<result_of::make_expr<Tag, basic_default_domain, Left, Right>, Grammar>
                >::value
              , result_of::make_expr<Tag, Domain, Left, Right>
            >
        {};

        template<typename Domain, typename Trait, typename Tag, typename Left, typename Right>
        struct enable_binary<Domain, proto::_, Trait, Tag, Left &, Right &>
          : boost::lazy_enable_if_c<
                Trait::value
              , result_of::make_expr<Tag, Domain, Left &, Right &>
            >
        {};

        template<typename Trait, typename Tag, typename Left, typename Right>
        struct enable_binary<deduce_domain, not_a_grammar, Trait, Tag, Left &, Right &>
          : enable_binary<
                typename deduce_domain2<Left, Right>::type
              , typename deduce_domain2<Left, Right>::type::proto_grammar
              , Trait
              , Tag
              , Left &
              , Right &
            >
        {};

    } // detail

#define BOOST_PROTO_UNARY_OP_IS_POSTFIX_0
#define BOOST_PROTO_UNARY_OP_IS_POSTFIX_1 , int

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES

#define BOOST_PROTO_DEFINE_UNARY_OPERATOR(OP, TAG, TRAIT, DOMAIN, POST)                             \
    template<typename Arg>                                                                          \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_unary<                                                    \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_UNARY_(TRAIT, Arg)                                                        \
      , TAG                                                                                         \
      , Arg &                                                                                       \
    >::type const                                                                                   \
    operator OP(Arg &arg BOOST_PROTO_UNARY_OP_IS_POSTFIX_ ## POST)                                  \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Arg &>()(arg);                         \
    }                                                                                               \
                                                                                                    \
    template<typename Arg>                                                                          \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_unary<                                                    \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_UNARY_(TRAIT, Arg)                                                        \
      , TAG                                                                                         \
      , Arg const &                                                                                 \
    >::type const                                                                                   \
    operator OP(Arg const &arg BOOST_PROTO_UNARY_OP_IS_POSTFIX_ ## POST)                            \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Arg const &>()(arg);                   \
    }                                                                                               \
    /**/

#define BOOST_PROTO_DEFINE_BINARY_OPERATOR(OP, TAG, TRAIT, DOMAIN)                                  \
    template<typename Left, typename Right>                                                         \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_binary<                                                   \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_BINARY_(TRAIT, Left, Right)                                               \
      , TAG                                                                                         \
      , Left &                                                                                      \
      , Right &                                                                                     \
    >::type const                                                                                   \
    operator OP(Left &left, Right &right)                                                           \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Left &, Right &>()(left, right);       \
    }                                                                                               \
                                                                                                    \
    template<typename Left, typename Right>                                                         \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_binary<                                                   \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_BINARY_(TRAIT, Left, Right)                                               \
      , TAG                                                                                         \
      , Left &                                                                                      \
      , Right const &                                                                               \
    >::type const                                                                                   \
    operator OP(Left &left, Right const &right)                                                     \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Left &, Right const &>()(left, right); \
    }                                                                                               \
                                                                                                    \
    template<typename Left, typename Right>                                                         \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_binary<                                                   \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_BINARY_(TRAIT, Left, Right)                                               \
      , TAG                                                                                         \
      , Left const &                                                                                \
      , Right &                                                                                     \
    >::type const                                                                                   \
    operator OP(Left const &left, Right &right)                                                     \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Left const &, Right &>()(left, right); \
    }                                                                                               \
                                                                                                    \
    template<typename Left, typename Right>                                                         \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_binary<                                                   \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_BINARY_(TRAIT, Left, Right)                                               \
      , TAG                                                                                         \
      , Left const &                                                                                \
      , Right const &                                                                               \
    >::type const                                                                                   \
    operator OP(Left const &left, Right const &right)                                               \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Left const &, Right const &>()(left, right);\
    }                                                                                               \
    /**/

#else

#define BOOST_PROTO_DEFINE_UNARY_OPERATOR(OP, TAG, TRAIT, DOMAIN, POST)                             \
    template<typename Arg>                                                                          \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_unary<                                                    \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_UNARY_(TRAIT, Arg)                                                        \
      , TAG                                                                                         \
      , Arg const &                                                                                 \
    >::type const                                                                                   \
    operator OP(Arg &&arg BOOST_PROTO_UNARY_OP_IS_POSTFIX_ ## POST)                                 \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Arg const &>()(arg);                   \
    }                                                                                               \
    /**/

#define BOOST_PROTO_DEFINE_BINARY_OPERATOR(OP, TAG, TRAIT, DOMAIN)                                  \
    template<typename Left, typename Right>                                                         \
    BOOST_PROTO_DISABLE_MSVC_C4714 BOOST_FORCEINLINE                                                \
    typename boost::proto::detail::enable_binary<                                                   \
        DOMAIN                                                                                      \
      , DOMAIN::proto_grammar                                                                       \
      , BOOST_PROTO_APPLY_BINARY_(TRAIT, Left, Right)                                               \
      , TAG                                                                                         \
      , Left const &                                                                                \
      , Right const &                                                                               \
    >::type const                                                                                   \
    operator OP(Left &&left, Right &&right)                                                         \
    {                                                                                               \
        return boost::proto::detail::make_expr_<TAG, DOMAIN, Left const &, Right const &>()(left, right);\
    }                                                                                               \
    /**/

#endif

#define BOOST_PROTO_DEFINE_OPERATORS(TRAIT, DOMAIN)                                                 \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(+, boost::proto::tag::unary_plus, TRAIT, DOMAIN, 0)           \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(-, boost::proto::tag::negate, TRAIT, DOMAIN, 0)               \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(*, boost::proto::tag::dereference, TRAIT, DOMAIN, 0)          \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(~, boost::proto::tag::complement, TRAIT, DOMAIN, 0)           \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(&, boost::proto::tag::address_of, TRAIT, DOMAIN, 0)           \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(!, boost::proto::tag::logical_not, TRAIT, DOMAIN, 0)          \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(++, boost::proto::tag::pre_inc, TRAIT, DOMAIN, 0)             \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(--, boost::proto::tag::pre_dec, TRAIT, DOMAIN, 0)             \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(++, boost::proto::tag::post_inc, TRAIT, DOMAIN, 1)            \
    BOOST_PROTO_DEFINE_UNARY_OPERATOR(--, boost::proto::tag::post_dec, TRAIT, DOMAIN, 1)            \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(<<, boost::proto::tag::shift_left, TRAIT, DOMAIN)            \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(>>, boost::proto::tag::shift_right, TRAIT, DOMAIN)           \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(*, boost::proto::tag::multiplies, TRAIT, DOMAIN)             \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(/, boost::proto::tag::divides, TRAIT, DOMAIN)                \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(%, boost::proto::tag::modulus, TRAIT, DOMAIN)                \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(+, boost::proto::tag::plus, TRAIT, DOMAIN)                   \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(-, boost::proto::tag::minus, TRAIT, DOMAIN)                  \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(<, boost::proto::tag::less, TRAIT, DOMAIN)                   \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(>, boost::proto::tag::greater, TRAIT, DOMAIN)                \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(<=, boost::proto::tag::less_equal, TRAIT, DOMAIN)            \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(>=, boost::proto::tag::greater_equal, TRAIT, DOMAIN)         \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(==, boost::proto::tag::equal_to, TRAIT, DOMAIN)              \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(!=, boost::proto::tag::not_equal_to, TRAIT, DOMAIN)          \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(||, boost::proto::tag::logical_or, TRAIT, DOMAIN)            \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(&&, boost::proto::tag::logical_and, TRAIT, DOMAIN)           \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(&, boost::proto::tag::bitwise_and, TRAIT, DOMAIN)            \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(|, boost::proto::tag::bitwise_or, TRAIT, DOMAIN)             \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(^, boost::proto::tag::bitwise_xor, TRAIT, DOMAIN)            \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(BOOST_PP_COMMA(), boost::proto::tag::comma, TRAIT, DOMAIN)   \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(->*, boost::proto::tag::mem_ptr, TRAIT, DOMAIN)              \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(<<=, boost::proto::tag::shift_left_assign, TRAIT, DOMAIN)    \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(>>=, boost::proto::tag::shift_right_assign, TRAIT, DOMAIN)   \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(*=, boost::proto::tag::multiplies_assign, TRAIT, DOMAIN)     \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(/=, boost::proto::tag::divides_assign, TRAIT, DOMAIN)        \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(%=, boost::proto::tag::modulus_assign, TRAIT, DOMAIN)        \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(+=, boost::proto::tag::plus_assign, TRAIT, DOMAIN)           \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(-=, boost::proto::tag::minus_assign, TRAIT, DOMAIN)          \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(&=, boost::proto::tag::bitwise_and_assign, TRAIT, DOMAIN)    \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(|=, boost::proto::tag::bitwise_or_assign, TRAIT, DOMAIN)     \
    BOOST_PROTO_DEFINE_BINARY_OPERATOR(^=, boost::proto::tag::bitwise_xor_assign, TRAIT, DOMAIN)    \
    /**/

    // Extensions are a superset of Proto expressions
    template<typename T>
    struct is_extension
      : is_expr<T>
    {};

    template<typename T>
    struct is_extension<T &>
      : is_expr<T>
    {};

    #define BOOST_PROTO_APPLY_UNARY_(TRAIT, ARG) TRAIT<ARG>
    #define BOOST_PROTO_APPLY_BINARY_(TRAIT, LEFT, RIGHT) boost::mpl::or_<TRAIT<LEFT>, TRAIT<RIGHT> >

    namespace exprns_
    {
        // This defines all of Proto's built-in free operator overloads
        BOOST_PROTO_DEFINE_OPERATORS(is_extension, deduce_domain)

        // if_else, for the non-overloadable ternary conditional operator ?:
        template<typename A0, typename A1, typename A2>
        BOOST_FORCEINLINE
        typename result_of::make_expr<
            tag::if_else_
          , deduce_domain
          , A0 const &
          , A1 const &
          , A2 const &
        >::type const
        if_else(A0 const &a0, A1 const &a1, A2 const &a2)
        {
            return proto::detail::make_expr_<
                tag::if_else_
              , deduce_domain
              , A0 const &
              , A1 const &
              , A2 const &
            >()(a0, a1, a2);
        }
    }

    using exprns_::if_else;

    #undef BOOST_PROTO_APPLY_UNARY_
    #undef BOOST_PROTO_APPLY_BINARY_

    // Redefine BOOST_PROTO_APPLY_UNARY_ and BOOST_PROTO_APPLY_BINARY_ so that end users
    // can use BOOST_PROTO_DEFINE_OPERATORS to define Proto operator overloads that work
    // with their own terminal types.

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES

    #define BOOST_PROTO_APPLY_UNARY_(TRAIT, ARG)                                                    \
        boost::mpl::and_<                                                                           \
            TRAIT<ARG>                                                                              \
          , boost::mpl::not_<boost::proto::is_extension<ARG> >                                      \
        >                                                                                           \
        /**/

    #define BOOST_PROTO_APPLY_BINARY_(TRAIT, LEFT, RIGHT)                                           \
        boost::mpl::and_<                                                                           \
            boost::mpl::or_<TRAIT<LEFT>, TRAIT<RIGHT> >                                             \
          , boost::mpl::not_<                                                                       \
                boost::mpl::or_<                                                                    \
                    boost::proto::is_extension<LEFT>                                                \
                  , boost::proto::is_extension<RIGHT>                                               \
                >                                                                                   \
            >                                                                                       \
        >                                                                                           \
        /**/

#else

    #define BOOST_PROTO_APPLY_UNARY_(TRAIT, ARG)                                                    \
        boost::mpl::and_<                                                                           \
            TRAIT<BOOST_PROTO_UNCVREF(ARG) >                                                        \
          , boost::mpl::not_<boost::proto::is_extension<ARG> >                                      \
        >                                                                                           \
        /**/

    #define BOOST_PROTO_APPLY_BINARY_(TRAIT, LEFT, RIGHT)                                           \
        boost::mpl::and_<                                                                           \
            boost::mpl::or_<TRAIT<BOOST_PROTO_UNCVREF(LEFT) >, TRAIT<BOOST_PROTO_UNCVREF(RIGHT) > > \
          , boost::mpl::not_<                                                                       \
                boost::mpl::or_<                                                                    \
                    boost::proto::is_extension<LEFT>                                                \
                  , boost::proto::is_extension<RIGHT>                                               \
                >                                                                                   \
            >                                                                                       \
        >                                                                                           \
        /**/

#endif

}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* operators.hpp
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
*/