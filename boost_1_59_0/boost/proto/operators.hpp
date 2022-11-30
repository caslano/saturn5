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
    BOOST_PROTO_PUSH_WARNINGS                                                                       \
                                                                                                    \
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
                                                                                                    \
    BOOST_PROTO_POP_WARNINGS                                                                        \
    /**/

#define BOOST_PROTO_DEFINE_BINARY_OPERATOR(OP, TAG, TRAIT, DOMAIN)                                  \
    BOOST_PROTO_PUSH_WARNINGS                                                                       \
                                                                                                    \
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
                                                                                                    \
    BOOST_PROTO_POP_WARNINGS                                                                        \
    /**/

#else

#define BOOST_PROTO_DEFINE_UNARY_OPERATOR(OP, TAG, TRAIT, DOMAIN, POST)                             \
    template<typename Arg>                                                                          \
    BOOST_PROTO_PUSH_WARNINGS                                                                       \
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
    BOOST_PROTO_POP_WARNINGS                                                                        \
    /**/

#define BOOST_PROTO_DEFINE_BINARY_OPERATOR(OP, TAG, TRAIT, DOMAIN)                                  \
    template<typename Left, typename Right>                                                         \
    BOOST_PROTO_PUSH_WARNINGS                                                                       \
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
    BOOST_PROTO_POP_WARNINGS                                                                        \
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