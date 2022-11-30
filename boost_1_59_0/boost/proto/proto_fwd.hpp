///////////////////////////////////////////////////////////////////////////////
/// \file proto_fwd.hpp
/// Forward declarations of all of proto's public types and functions.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FWD_HPP_EAN_04_01_2005
#define BOOST_PROTO_FWD_HPP_EAN_04_01_2005

#include <cstddef>
#include <climits>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/ref.hpp>
#include <boost/mpl/long.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/utility/result_of.hpp>

#ifndef BOOST_PROTO_MAX_ARITY
# define BOOST_PROTO_MAX_ARITY 10
#endif

#ifndef BOOST_PROTO_MAX_LOGICAL_ARITY
# define BOOST_PROTO_MAX_LOGICAL_ARITY 10
#endif

#ifndef BOOST_PROTO_MAX_FUNCTION_CALL_ARITY
# define BOOST_PROTO_MAX_FUNCTION_CALL_ARITY BOOST_PROTO_MAX_ARITY
#endif

#if BOOST_PROTO_MAX_ARITY < 3
# error BOOST_PROTO_MAX_ARITY must be at least 3
#endif

#if BOOST_PROTO_MAX_FUNCTION_CALL_ARITY > BOOST_PROTO_MAX_ARITY
# error BOOST_PROTO_MAX_FUNCTION_CALL_ARITY cannot be larger than BOOST_PROTO_MAX_ARITY
#endif

#ifndef BOOST_PROTO_DONT_USE_PREPROCESSED_FILES
  #if 10 < BOOST_PROTO_MAX_ARITY ||                                                                 \
      10 < BOOST_PROTO_MAX_LOGICAL_ARITY ||                                                         \
      10 < BOOST_PROTO_MAX_FUNCTION_CALL_ARITY
    #define BOOST_PROTO_DONT_USE_PREPROCESSED_FILES
  #endif
#endif

#ifndef BOOST_PROTO_BROKEN_CONST_OVERLOADS
# if BOOST_WORKAROUND(__GNUC__, == 3) \
  || BOOST_WORKAROUND(__EDG_VERSION__, BOOST_TESTED_AT(310))
#  define BOOST_PROTO_BROKEN_CONST_OVERLOADS
# endif
#endif

#ifndef BOOST_PROTO_BROKEN_CONST_QUALIFIED_FUNCTIONS
# if BOOST_WORKAROUND(__GNUC__, == 3) \
  || BOOST_WORKAROUND(__EDG_VERSION__, BOOST_TESTED_AT(310))
#  define BOOST_PROTO_BROKEN_CONST_QUALIFIED_FUNCTIONS
# endif
#endif

#ifdef BOOST_PROTO_BROKEN_CONST_OVERLOADS
# include <boost/utility/enable_if.hpp>
# include <boost/type_traits/is_const.hpp>
# define BOOST_PROTO_DISABLE_IF_IS_CONST(T)\
    , typename boost::disable_if_c<boost::is_const<T>::value, boost::proto::detail::undefined>::type * = 0
#else
# define BOOST_PROTO_DISABLE_IF_IS_CONST(T)
#endif

#ifdef BOOST_PROTO_BROKEN_CONST_QUALIFIED_FUNCTIONS
# include <boost/utility/enable_if.hpp>
# include <boost/type_traits/is_function.hpp>
# define BOOST_PROTO_DISABLE_IF_IS_FUNCTION(T)\
    , typename boost::disable_if_c<boost::is_function<T>::value, boost::proto::detail::undefined>::type * = 0
#else
# define BOOST_PROTO_DISABLE_IF_IS_FUNCTION(T)
#endif

#ifndef BOOST_PROTO_BROKEN_PTS
# if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
#  define BOOST_PROTO_BROKEN_PTS
# endif
#endif

#ifdef BOOST_NO_CXX11_DECLTYPE_N3276
# // Proto can only use the decltype-based result_of if N3276 has been
# // implemented by the compiler.
# // See http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2011/n3276.pdf
# ifndef BOOST_PROTO_USE_NORMAL_RESULT_OF
#  define BOOST_PROTO_USE_NORMAL_RESULT_OF
# endif
#endif

// Unless compiler support is there, use tr1_result_of instead of
// result_of to avoid the problems addressed by N3276.
#ifdef BOOST_PROTO_USE_NORMAL_RESULT_OF
# define BOOST_PROTO_RESULT_OF boost::result_of
#else
# define BOOST_PROTO_RESULT_OF boost::tr1_result_of
#endif

// If we're using the decltype-based result_of, we need to be a bit
// stricter about the return types of some functions.
#if defined(BOOST_RESULT_OF_USE_DECLTYPE) && defined(BOOST_PROTO_USE_NORMAL_RESULT_OF)
# define BOOST_PROTO_STRICT_RESULT_OF
# define BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(X, Y) X
#else
# define BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(X, Y) Y
#endif

#ifdef BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING
# define BOOST_PROTO_EXTENDED_TEMPLATE_PARAMETERS_MATCHING 
#endif

#if defined(_MSC_VER)
# define BOOST_PROTO_PUSH_WARNINGS __pragma(warning(push))
# define BOOST_PROTO_POP_WARNINGS __pragma(warning(pop))
# define BOOST_PROTO_DISABLE_MSVC_C4180 __pragma(warning(disable : 4180))  // qualifier applied to function type has no meaning; ignored
# define BOOST_PROTO_DISABLE_MSVC_C4522 __pragma(warning(disable : 4522))  // 'class' : multiple assignment operators specified
# define BOOST_PROTO_DISABLE_MSVC_C4714 __pragma(warning(disable : 4714))  // function 'xxx' marked as __forceinline not inlined
#else
# define BOOST_PROTO_PUSH_WARNINGS
# define BOOST_PROTO_POP_WARNINGS
# define BOOST_PROTO_DISABLE_MSVC_C4180
# define BOOST_PROTO_DISABLE_MSVC_C4522 
# define BOOST_PROTO_DISABLE_MSVC_C4714
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        typedef char yes_type;
        typedef char (&no_type)[2];

        template<int N>
        struct sized_type
        {
            typedef char (&type)[N];
        };

        struct dont_care;
        struct undefined; // leave this undefined
        struct not_a_valid_type;

        struct private_type_
        {
            private_type_ operator ,(int) const;
        };

        template<typename T>
        struct uncvref
        {
            typedef T type;
        };

        template<typename T>
        struct uncvref<T const>
        {
            typedef T type;
        };

        template<typename T>
        struct uncvref<T &>
        {
            typedef T type;
        };

        template<typename T>
        struct uncvref<T const &>
        {
            typedef T type;
        };

        template<typename T, std::size_t N>
        struct uncvref<T const[N]>
        {
            typedef T type[N];
        };

        template<typename T, std::size_t N>
        struct uncvref<T (&)[N]>
        {
            typedef T type[N];
        };

        template<typename T, std::size_t N>
        struct uncvref<T const (&)[N]>
        {
            typedef T type[N];
        };

        struct ignore
        {
            ignore()
            {}

            template<typename T>
            ignore(T const &)
            {}
        };

        /// INTERNAL ONLY
        ///
        #define BOOST_PROTO_UNCVREF(X)                                                              \
            typename boost::proto::detail::uncvref<X>::type                                         \
            /**/

        struct _default;

        struct not_a_domain;
        struct not_a_grammar;
        struct not_a_generator;

        template<typename T, typename Void = void>
        struct is_transform_;

        template<typename T, typename Void = void>
        struct is_aggregate_;

        template<typename Expr>
        struct flat_view;
    }

    typedef detail::ignore const ignore;

    namespace argsns_
    {
        template<typename Arg0>
        struct term;

        #define M0(Z, N, DATA)                                                                      \
        template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename Arg)> struct BOOST_PP_CAT(list, N);          \
        /**/
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), M0, ~)
        #undef M0
    }

    using namespace argsns_;

    ///////////////////////////////////////////////////////////////////////////////
    // Operator tags
    namespace tagns_
    {
        namespace tag
        {
            struct terminal;
            struct unary_plus;
            struct negate;
            struct dereference;
            struct complement;
            struct address_of;
            struct logical_not;
            struct pre_inc;
            struct pre_dec;
            struct post_inc;
            struct post_dec;

            struct shift_left;
            struct shift_right;
            struct multiplies;
            struct divides;
            struct modulus;
            struct plus;
            struct minus;
            struct less;
            struct greater;
            struct less_equal;
            struct greater_equal;
            struct equal_to;
            struct not_equal_to;
            struct logical_or;
            struct logical_and;
            struct bitwise_and;
            struct bitwise_or;
            struct bitwise_xor;
            struct comma;
            struct mem_ptr;

            struct assign;
            struct shift_left_assign;
            struct shift_right_assign;
            struct multiplies_assign;
            struct divides_assign;
            struct modulus_assign;
            struct plus_assign;
            struct minus_assign;
            struct bitwise_and_assign;
            struct bitwise_or_assign;
            struct bitwise_xor_assign;
            struct subscript;
            struct member;
            struct if_else_;
            struct function;

            // Fusion tags
            template<typename Tag, typename Domain> struct proto_expr;
            template<typename Tag, typename Domain> struct proto_expr_iterator;
            template<typename Tag, typename Domain> struct proto_flat_view;
        }
    }

    using namespace tagns_;

    template<typename Expr>
    struct tag_of;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct _;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct default_generator;

    struct basic_default_generator;

    template<template<typename> class Extends>
    struct generator;

    template<template<typename> class Extends>
    struct pod_generator;

    struct by_value_generator;

    template<typename First, typename Second>
    struct compose_generators;

    template<typename Generator, typename Void = void>
    struct wants_basic_expr;

    template<typename Generator>
    struct use_basic_expr;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    namespace domainns_
    {
        typedef detail::not_a_domain no_super_domain;

        template<
            typename Generator  = default_generator
          , typename Grammar    = proto::_
          , typename Super      = no_super_domain
        >
        struct domain;

        struct default_domain;

        struct basic_default_domain;

        struct deduce_domain;

        template<typename Domain, typename Tag, typename Args, bool WantsBasicExpr = wants_basic_expr<typename Domain::proto_generator>::value>
        struct base_expr;
    }

    using namespace domainns_;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    namespace exprns_
    {
        template<typename Tag, typename Args, long Arity = Args::arity>
        struct basic_expr;

        template<typename Tag, typename Args, long Arity = Args::arity>
        struct expr;

        template<
            typename Expr
          , typename Derived
          , typename Domain = default_domain
          , long Arity = Expr::proto_arity_c
        >
        struct extends;

        template<typename This, typename Fun, typename Domain>
        struct virtual_member;
        
        struct is_proto_expr;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////

    using exprns_::expr;
    using exprns_::basic_expr;
    using exprns_::extends;
    using exprns_::is_proto_expr;

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_LOGICAL_ARITY, typename G, void)>
    struct or_;

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_LOGICAL_ARITY, typename G, void)>
    struct and_;

    template<typename Grammar>
    struct not_;

    template<typename Condition, typename Then = _, typename Else = not_<_> >
    struct if_;

    template<typename Cases, typename Transform = tag_of<_>()>
    struct switch_;

    template<typename T>
    struct exact;

    template<typename T>
    struct convertible_to;

    template<typename Grammar>
    struct vararg;

    struct pack;

    // Boost bug https://svn.boost.org/trac/boost/ticket/4602
    //int const N = INT_MAX;
    int const N = (INT_MAX >> 10);

    namespace context
    {
        struct null_context;

        template<typename Expr, typename Context, long Arity = Expr::proto_arity_c>
        struct null_eval;

        struct default_context;

        template<typename Expr, typename Context, typename Tag = typename Expr::proto_tag, long Arity = Expr::proto_arity_c>
        struct default_eval;

        template<typename Derived, typename DefaultCtx = default_context>
        struct callable_context;

        template<typename Expr, typename Context, long Arity = Expr::proto_arity_c>
        struct callable_eval;
    }

    using context::null_context;
    using context::null_eval;
    using context::default_context;
    using context::default_eval;
    using context::callable_context;
    using context::callable_eval;

    namespace utility
    {
        template<typename T, typename Domain = default_domain>
        struct literal;
    }

    using utility::literal;

    namespace result_of
    {
        template<typename T, typename Domain = default_domain>
        struct as_expr;

        template<typename T, typename Domain = default_domain>
        struct as_child;

        template<typename Expr, typename N = mpl::long_<0> >
        struct child;

        template<typename Expr, long N>
        struct child_c;

        template<typename Expr>
        struct left;

        template<typename Expr>
        struct right;

        template<typename Expr>
        struct deep_copy;

        template<typename Expr, typename Context>
        struct eval;

        template<
            typename Tag
          , typename DomainOrA0
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
                BOOST_PROTO_MAX_ARITY
              , typename A
              , = void BOOST_PP_INTERCEPT
            )
          , typename Void = void
        >
        struct make_expr;

        template<typename Tag, typename DomainOrSequence, typename SequenceOrVoid = void, typename Void = void>
        struct unpack_expr;

        template<typename T>
        struct as_env;

        template<typename Env, typename Tag>
        struct has_env_var;

        template<typename Env, typename Tag>
        struct env_var;
    }

    template<typename T, typename Void = void>
    struct is_expr;

    template<typename T, typename Void = void>
    struct is_domain;

    template<typename SubDomain, typename SuperDomain>
    struct is_sub_domain_of;

    template<typename T, typename Void = void>
    struct is_env;

    template<typename Expr>
    struct arity_of;

    template<typename T, typename Void = void>
    struct domain_of;

    template<typename Expr, typename Grammar>
    struct matches;

    // Generic expression metafunctions and
    // grammar elements
    template<typename Tag, typename Arg>
    struct unary_expr;

    template<typename Tag, typename Left, typename Right>
    struct binary_expr;

    template<typename Tag, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename A, void)>
    struct nary_expr;

    // Specific expression metafunctions and
    // grammar elements, for convenience
    template<typename T> struct terminal;
    template<typename T> struct unary_plus;
    template<typename T> struct negate;
    template<typename T> struct dereference;
    template<typename T> struct complement;
    template<typename T> struct address_of;
    template<typename T> struct logical_not;
    template<typename T> struct pre_inc;
    template<typename T> struct pre_dec;
    template<typename T> struct post_inc;
    template<typename T> struct post_dec;

    template<typename T, typename U> struct shift_left;
    template<typename T, typename U> struct shift_right;
    template<typename T, typename U> struct multiplies;
    template<typename T, typename U> struct divides;
    template<typename T, typename U> struct modulus;
    template<typename T, typename U> struct plus;
    template<typename T, typename U> struct minus;
    template<typename T, typename U> struct less;
    template<typename T, typename U> struct greater;
    template<typename T, typename U> struct less_equal;
    template<typename T, typename U> struct greater_equal;
    template<typename T, typename U> struct equal_to;
    template<typename T, typename U> struct not_equal_to;
    template<typename T, typename U> struct logical_or;
    template<typename T, typename U> struct logical_and;
    template<typename T, typename U> struct bitwise_and;
    template<typename T, typename U> struct bitwise_or;
    template<typename T, typename U> struct bitwise_xor;
    template<typename T, typename U> struct comma;
    template<typename T, typename U> struct mem_ptr;

    template<typename T, typename U> struct assign;
    template<typename T, typename U> struct shift_left_assign;
    template<typename T, typename U> struct shift_right_assign;
    template<typename T, typename U> struct multiplies_assign;
    template<typename T, typename U> struct divides_assign;
    template<typename T, typename U> struct modulus_assign;
    template<typename T, typename U> struct plus_assign;
    template<typename T, typename U> struct minus_assign;
    template<typename T, typename U> struct bitwise_and_assign;
    template<typename T, typename U> struct bitwise_or_assign;
    template<typename T, typename U> struct bitwise_xor_assign;
    template<typename T, typename U> struct subscript;
    template<typename T, typename U> struct member;
    template<typename T, typename U, typename V> struct if_else_;

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename A, void)>
    struct function;

    namespace functional
    {
        struct left;
        struct right;
        struct eval;
        struct deep_copy;

        template<typename Domain = default_domain>
        struct as_expr;

        template<typename Domain = default_domain>
        struct as_child;

        template<typename N = mpl::long_<0> >
        struct child;

        template<long N>
        struct child_c;

        struct as_env;

        template<typename Tag>
        struct has_env_var;

        template<typename Tag>
        struct env_var;

        template<typename Tag, typename Domain = deduce_domain>
        struct make_expr;

        template<typename Tag, typename Domain = deduce_domain>
        struct unpack_expr;

        typedef make_expr<tag::terminal>            make_terminal;
        typedef make_expr<tag::unary_plus>          make_unary_plus;
        typedef make_expr<tag::negate>              make_negate;
        typedef make_expr<tag::dereference>         make_dereference;
        typedef make_expr<tag::complement>          make_complement;
        typedef make_expr<tag::address_of>          make_address_of;
        typedef make_expr<tag::logical_not>         make_logical_not;
        typedef make_expr<tag::pre_inc>             make_pre_inc;
        typedef make_expr<tag::pre_dec>             make_pre_dec;
        typedef make_expr<tag::post_inc>            make_post_inc;
        typedef make_expr<tag::post_dec>            make_post_dec;
        typedef make_expr<tag::shift_left>          make_shift_left;
        typedef make_expr<tag::shift_right>         make_shift_right;
        typedef make_expr<tag::multiplies>          make_multiplies;
        typedef make_expr<tag::divides>             make_divides;
        typedef make_expr<tag::modulus>             make_modulus;
        typedef make_expr<tag::plus>                make_plus;
        typedef make_expr<tag::minus>               make_minus;
        typedef make_expr<tag::less>                make_less;
        typedef make_expr<tag::greater>             make_greater;
        typedef make_expr<tag::less_equal>          make_less_equal;
        typedef make_expr<tag::greater_equal>       make_greater_equal;
        typedef make_expr<tag::equal_to>            make_equal_to;
        typedef make_expr<tag::not_equal_to>        make_not_equal_to;
        typedef make_expr<tag::logical_or>          make_logical_or;
        typedef make_expr<tag::logical_and>         make_logical_and;
        typedef make_expr<tag::bitwise_and>         make_bitwise_and;
        typedef make_expr<tag::bitwise_or>          make_bitwise_or;
        typedef make_expr<tag::bitwise_xor>         make_bitwise_xor;
        typedef make_expr<tag::comma>               make_comma;
        typedef make_expr<tag::mem_ptr>             make_mem_ptr;
        typedef make_expr<tag::assign>              make_assign;
        typedef make_expr<tag::shift_left_assign>   make_shift_left_assign;
        typedef make_expr<tag::shift_right_assign>  make_shift_right_assign;
        typedef make_expr<tag::multiplies_assign>   make_multiplies_assign;
        typedef make_expr<tag::divides_assign>      make_divides_assign;
        typedef make_expr<tag::modulus_assign>      make_modulus_assign;
        typedef make_expr<tag::plus_assign>         make_plus_assign;
        typedef make_expr<tag::minus_assign>        make_minus_assign;
        typedef make_expr<tag::bitwise_and_assign>  make_bitwise_and_assign;
        typedef make_expr<tag::bitwise_or_assign>   make_bitwise_or_assign;
        typedef make_expr<tag::bitwise_xor_assign>  make_bitwise_xor_assign;
        typedef make_expr<tag::subscript>           make_subscript;
        typedef make_expr<tag::if_else_>            make_if_else;
        typedef make_expr<tag::function>            make_function;

        struct flatten;
        struct make_pair;
        struct first;
        struct second;
        struct at;
        struct pop_front;
        struct push_front;
        struct pop_back;
        struct push_back;
        struct reverse;
    }

    typedef functional::flatten     _flatten;
    typedef functional::make_pair   _make_pair;
    typedef functional::first       _first;
    typedef functional::second      _second;
    typedef functional::at          _at;
    typedef functional::pop_front   _pop_front;
    typedef functional::push_front  _push_front;
    typedef functional::pop_back    _pop_back;
    typedef functional::push_back   _push_back;
    typedef functional::reverse     _reverse;
    typedef functional::eval        _eval;
    struct _deep_copy;

    typedef functional::make_expr<tag::terminal>           _make_terminal;
    typedef functional::make_expr<tag::unary_plus>         _make_unary_plus;
    typedef functional::make_expr<tag::negate>             _make_negate;
    typedef functional::make_expr<tag::dereference>        _make_dereference;
    typedef functional::make_expr<tag::complement>         _make_complement;
    typedef functional::make_expr<tag::address_of>         _make_address_of;
    typedef functional::make_expr<tag::logical_not>        _make_logical_not;
    typedef functional::make_expr<tag::pre_inc>            _make_pre_inc;
    typedef functional::make_expr<tag::pre_dec>            _make_pre_dec;
    typedef functional::make_expr<tag::post_inc>           _make_post_inc;
    typedef functional::make_expr<tag::post_dec>           _make_post_dec;
    typedef functional::make_expr<tag::shift_left>         _make_shift_left;
    typedef functional::make_expr<tag::shift_right>        _make_shift_right;
    typedef functional::make_expr<tag::multiplies>         _make_multiplies;
    typedef functional::make_expr<tag::divides>            _make_divides;
    typedef functional::make_expr<tag::modulus>            _make_modulus;
    typedef functional::make_expr<tag::plus>               _make_plus;
    typedef functional::make_expr<tag::minus>              _make_minus;
    typedef functional::make_expr<tag::less>               _make_less;
    typedef functional::make_expr<tag::greater>            _make_greater;
    typedef functional::make_expr<tag::less_equal>         _make_less_equal;
    typedef functional::make_expr<tag::greater_equal>      _make_greater_equal;
    typedef functional::make_expr<tag::equal_to>           _make_equal_to;
    typedef functional::make_expr<tag::not_equal_to>       _make_not_equal_to;
    typedef functional::make_expr<tag::logical_or>         _make_logical_or;
    typedef functional::make_expr<tag::logical_and>        _make_logical_and;
    typedef functional::make_expr<tag::bitwise_and>        _make_bitwise_and;
    typedef functional::make_expr<tag::bitwise_or>         _make_bitwise_or;
    typedef functional::make_expr<tag::bitwise_xor>        _make_bitwise_xor;
    typedef functional::make_expr<tag::comma>              _make_comma;
    typedef functional::make_expr<tag::mem_ptr>            _make_mem_ptr;
    typedef functional::make_expr<tag::assign>             _make_assign;
    typedef functional::make_expr<tag::shift_left_assign>  _make_shift_left_assign;
    typedef functional::make_expr<tag::shift_right_assign> _make_shift_right_assign;
    typedef functional::make_expr<tag::multiplies_assign>  _make_multiplies_assign;
    typedef functional::make_expr<tag::divides_assign>     _make_divides_assign;
    typedef functional::make_expr<tag::modulus_assign>     _make_modulus_assign;
    typedef functional::make_expr<tag::plus_assign>        _make_plus_assign;
    typedef functional::make_expr<tag::minus_assign>       _make_minus_assign;
    typedef functional::make_expr<tag::bitwise_and_assign> _make_bitwise_and_assign;
    typedef functional::make_expr<tag::bitwise_or_assign>  _make_bitwise_or_assign;
    typedef functional::make_expr<tag::bitwise_xor_assign> _make_bitwise_xor_assign;
    typedef functional::make_expr<tag::subscript>          _make_subscript;
    typedef functional::make_expr<tag::if_else_>           _make_if_else;
    typedef functional::make_expr<tag::function>           _make_function;

    template<typename T>
    struct is_callable;

    template<typename T>
    struct is_transform;

    template<typename T>
    struct is_aggregate;

    #define BOOST_PROTO_UNEXPR() typedef int proto_is_expr_;
    #define BOOST_PROTO_CALLABLE() typedef void proto_is_callable_;
    #define BOOST_PROTO_AGGREGATE() typedef void proto_is_aggregate_;
    #define BOOST_PROTO_USE_BASIC_EXPR() typedef void proto_use_basic_expr_;

    struct callable
    {
        BOOST_PROTO_CALLABLE()
    };

    namespace envns_
    {
        struct key_not_found;

        struct empty_env;

        typedef int empty_state;

        template<typename Tag, typename Value, typename Base = empty_env>
        struct env;

        struct data_type;

        struct transforms_type;
    }

    using envns_::key_not_found;
    using envns_::empty_env;
    using envns_::empty_state;
    using envns_::env;
    using envns_::data_type;
    using envns_::transforms_type;

    struct external_transform;

    template<typename PrimitiveTransform = void, typename X = void>
    struct transform;

    template<typename Grammar, typename Fun = Grammar>
    struct when;

    template<typename Fun>
    struct otherwise;

    template<typename Fun>
    struct call;

    template<typename Fun>
    struct make;

    template<typename PrimitiveTransform>
    struct protect;

    template<typename T>
    struct noinvoke;

    template<typename Fun>
    struct lazy;

    template<typename Sequence, typename State, typename Fun>
    struct fold;

    template<typename Sequence, typename State, typename Fun>
    struct reverse_fold;

    // Q: can we replace fold_tree with fold<flatten(_), state, fun> ?
    // A: once segmented Fusion works well.
    template<typename Sequence, typename State, typename Fun>
    struct fold_tree;

    template<typename Sequence, typename State, typename Fun>
    struct reverse_fold_tree;

    template<typename Grammar, typename Domain = deduce_domain>
    struct pass_through;

    template<typename Grammar = detail::_default>
    struct _default;

    struct _expr;
    struct _state;
    struct _data;

    struct _value;

    struct _void;

    template<typename T, T I>
    struct integral_c;

    template<char I>
    struct char_;

    template<int I>
    struct int_;

    template<long I>
    struct long_;

    template<std::size_t I>
    struct size_t;

    template<int I>
    struct _child_c;

    typedef _child_c<0> _child0;
    typedef _child_c<1> _child1;
    typedef _child0     _child;
    typedef _child0     _left;
    typedef _child1     _right;

    // _child2, _child3, _child4, ...
    #define M0(Z, N, DATA) typedef _child_c<N> BOOST_PP_CAT(_child, N);
    BOOST_PP_REPEAT_FROM_TO(
        2
      , BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY)
      , M0
      , ~
    )
    #undef M0

    struct _byref;
    struct _byval;

    template<typename Tag>
    struct _env_var;

    struct _env;

    template<typename T>
    struct is_extension;

    namespace exops = exprns_;

}} // namespace boost::proto

#endif

/* proto_fwd.hpp
/KZcH1ow3qYNZ2jgUNYeP0i05C7IiyqcIq/el9f22MCItst0YSWoBf6jtBA3RHvL2tfbjeF5bfSMjp94FUSdnW79dS+dPBW6+6hNLGXOEPWKzmI7g22WncH7oUeocH/oESr8xshDVsHhamISptf7prcttFNpYnqzd/rRx4ZqbqFt9Wm7Fl4npjf4vqkoTaoWrBVei46MaMdEBz+61an3JOZaz5PRPpTSfNpTp+d+GSqXBn3kDn/FJoTN3ryj7vA88HRJ31PKFpah5W0dnrdr+PStsYx8OyrWRnJTKHdOGP1v1b369KMYLPZmWQcm7iCg5aqv3ZU7cDO9Lt7Fvun1CweIvEbf3oorVb9up1q1/ANF+o/GCoMQaKJDn+iil9Ebrcdi83B//fAdaLyvhpJXuMZzQpc+0RG9MPZNtHcBT2AInEJ3S/gnLZfuJ3WA48/lvgDpvEwYBweo6Ucng9YzF2R17UI75estrw5eLuyh6tNe/7EKO3wd5B3X6b6bPtHpq6m4jvo4VNNOvXIFVYGTtSJZq8hr0/GA0rkoXbp+qwvpbnWEuDwU6Jc+LlPryevH5Onz6JSX6kjyOJX/gdJhVRshWByerQSLX+c0meYa/U08aq9Sw+i/gk7FlssYFWIsK0lVkMZ+YPKXg8J2h7srxEiceN2tPtf6WGHqR1+cbms5Ar3zrBuAHnTp/l1swVQPpHUsroKh1eOc22WdcwpTS/NeX/y4ZcOSD9cq30JXyo/a6BGOwu8gk+uF7cS3OzhYH8VXO4P9xNOcTIEGp8rd38CNDx0tfMIf9M5udj8JnwYKJw3+56/EcvkbgPHkON1MON9Fs2qgoTVbCOrdcrHKxzjY0oPR+w3sxQyztd3GntAM7cZQOTXIy5JLmiBJQFRMEGaJdsuH/xMdckTk0X7jClWnhWrS6ELP83ygHN/SKd5c8vkNbIYBT8gOYkHomG82+t/PnpHef4Eo4Macajrpn6tmRcvDK6DpbBDjx2J7Lk0p6X0TVfphB5E1HLuCvm5goI/yzjNO9WRu2aWoTvkuppUHhMoCxMLSx/0TPy61sTODnXD9liqHNnaYXmwbqZ5yM9VE/vTSjJjVMG3dLjM8NAgT+bPvKL0S2lATg9NNRJQ2xTSpGMrH11ABKKdplGEXE7OIyQATAEcs1D7g3g9GB8jIq+zCV3RXJkSBXHpHC8SVqEALHctOYosjtBN+LTZh1uY0BdR4GP2zysDKaveKcZiD5sz/ZWgTj3XwZyYke5YVAeQgsV+YpUfF8sdNXg5z1bdFG1MABxE7QT0pKMBYDqTgPzp84p0BmX1bhm1mqK3bY32MUSUQBfZfrfx0RIuJV8dxQzu+5Ag+zaogRcBGlkJMnsity40j0ogmpITHaCLEzZuo7uyXyWmMClIB0VeoOk9+0REPNXKBI8HxiOiFkz86UADcOQR2LOmMcUVslwAjKbrRefCp8jAgL15OrGVpblULNoz2IdgwaCusJ7arAQ4p7Hp5s2nJ0rrocz6UPx54Iqd6Ei10olBnlGbIhvnsAXgXdE2gzACfSH+5wwC1zEhif3Otf1eKQi/2gAhnRo1hRIm2YMkp1uEwWpk8xZe9AueCfEzTvyN8WFPXHTPVBKZqwH80dHcjTbX3FMV3v+liqtbvgq288GeIvEzdv07PqyKC2hHeviBLJVREQJ26UajydYyZrkrMSLuG6nmldy1v85cIsYJhPjRm09dNLYpM3zrVgm5fmedEbizdxQ7xhgkl58PtOgiDiF5z6nl14KAgVgz9wgMNt9PLeWrzQo/R4X4PYMzEfj1bkx/JW5dPAw+0uAKIT2/kgsL7tEQU+F4aw4or7f73fH5X+SVs4DZQTK8moiED/UJ7jeGvr72JndxRJ6VgFRMjU0c7ejFqVd4cKt/FwasalMxsWMyWUvjrx8v5F9NSz7CVjqgasIMmxcLBMA2BLy/VZccUoYnOLIrkbSVSSl6Eva47zfY9iEPO0+UPmCvBXhH/VsiH7vkgAfy/Vc4GqsN/BOD/Ixb4/7nfsktm+sDQjm3CQNKHhd7ZLncYXkAL9NkuOQ3u0+B/A2loMfqd+YWUCtGHvKexvzf7GoNFIEMr8mnN2WFg2/oSpR2+WTSiKoV7OwqoOi5K7PM3a2m0T0SdVEawF2VPX3j9roXbov1j9RB7ArQxStkEc93ucEPayFhzqI14aKjI6MxCuZHfF5z12ut3Vlwf8TeiD8QmrrydOIBjXBfU5FexjI/Gv5xO08YXcCzcFqtHoJDeyumdyOEIenDgK9YWvVW2vthhyP8eFAfnW+5xc/6ibGbdS1+wWax9fHDonA6mi0zaWodnRtPFDAeuZjgKpHGf2tAW/kzsDjdVDIpMNgJy3DbDYDHKbab3JFjARC++vUheZr4JjsTZErS8NDNPGWP7zsWLMd8wK8HZT5K0k415gN0vgj8cZroOoxUDivg/hFfn6XgkXkiicUbQre7AIbY8zeg9yP/dlWHG9l1M736DcFgBHB5wmfYbIOm+x2kVu4zNaxue1zrL5z+qpfnyZHAwtbV0AM6N3XRuUK2MZSPZc6Z8e2g6UTkszQZacFihXHiEznPPTEZ2MT/VVdTHxIKKgTb5TD9LnpNvmnmLtwEnUFsw1N0nP9bzOgeeKBI7T35MnCxIt0a0cqIr2Mc7ERrnidA4T4RNFo57N477+RatMDELBBbwGzE6wnpHi3KiU+vrnZgZdPhatfRSZ0nfmwBHL3Ui8+4lGbhLK+lnfQS/+qFHM23BTIb6jWJ6IoU/wvsD0W7qGSjVlAJlGUbjk5OYhq77JVxnWNe1E52sTrGy8HeKx9nAa1+0DzNrfZiBIIKwF7FP1Vo0eo2c8kK7QTtmb4vG4ToMOHETzVAPNaZ/Yr2VefL2OHzactSwuJINErZo3ekIsYd2GqU2fTmeSd8etai03t40jhdS+RYA4X3Vrihtiox+KYUDsS1BpB7fciWl/wlkBnAQtRn6ZzZu+Oildo5xBVOpT4hfxSFxN1Ap8j82Yj+DwXuOSVqJxQuV0wXir5VY2bKE9zvF7E6dX9f6ucPCTcGZ5mdBT4nrTlZG3/4SOy4cz1Bu4tHhtMQGSQ2LkLKEv439mESHWF8Gw1BiWDYXwe5medZrovMg4bKVT1FVE0sr2YtEEv0+isjaGBHeVsNE6GO8XaSbe0K0V+y9kxKrXMLby2aqXH11wdtpDDgz+Tn4A7yH3yZ+LRs+VxS78uyYHeLPDar5hbEOMCVEmtWARGNONtYrAhCWNszivyrvUftsJofwjDWe1aaknxkwvbzzdhobX3lncOxGjGPYWOAQ5W23Q8qWQW0MFMCN5+kXYtYO/uOWdrPb7fSZtht/WJh8P411aINhmMNB35n7JzNc3FZq/fVo/Z+rkbN844V2M6we0aCM2cHgZIrFQNnT3ppdYkt0x0llq2F9Wln+bTm72SW7VLP3ntXsD7o0e7LZbB8321fetjCVfQ3Ki6utVnc/Z6sno8F7klodqfq3Wr31A241IJH/51arWI0LdqrAoYlNNd3/Q8FGSzvdnEXR60170n3R3rzd9KW9ZoEz6IER6VcmELn5mXbD+zzS4+ybarUC+R2O+S0tEqeY7ymCW0C19j9+LtaiGyBsR/sD0FCM+DfaB8fIVxoK3ww/4MUJASlVMMhC+DW77HMiEz7IYrn0fVTQL3ilmI7c7igo3AipaoEseE6NmTYpSTy7u6kDXT/KejuMthlQ4fRqLV6V/Lz4Eo8cYL1OF3Ryrl1NRzbLTR22kkbYF+eCiFzRL8NWgq6m/l95HxgGNu/l2FlsnVAnd613wmHIL1zsLS6naSK7suRZYRoTFyYaExfJfmPTTUNi8M/9Xjxj+LYEexAZxqRsdKy5ragsILpW0oY4vcAncE5TQUH8DO5ewNYDWXGrZFk8Mt0mf9YvI+6sS2FWVsLYg7qxoCkNFm/KV07z9kNwUbQiFW6LVie5LXqSn71puS3iZ2WpcGXEjpZMJ0b30JPo0Nc4x0b++LXV1ieMpuGEDKYpEINZTgyXR9AHbFCO9bfgej04trlOMRCKndWm9Paqjzp4nTMvonh0dyXrCpRjHnclQnE2LX455vonyfPPzhRiBNqIjgLbPK2JfRNxK/6HXnjZQY82TjkO4se/5cdwz6NdrjwGNdbIxfwQDnq0fofhiiJ8q2EYphLwcKPKVd+U5AZoakqG6ZCoixsgL79YfbYboCx6Ef258Q4yiyxFZsY7aJW8Lgd6a22I8c5qfrWOXyFrOYBfuSsBiBPcB8obkVBV4pKFWYt1fK0KrkqaU7F+vcQwz6U3WZzzq0YsmKMuWjB/f1otGHfl6ZgbD3za8hU8XkeWWrpeufpgR2IWN3IWnrspi989HdODxEqekwiefeBgTCSjDcOWw6qO+6zPEKWn70Y7PPiaOSDscmLIY5dM755qo2Sn6ee1I9StQB0SXR4cEfG3sTcKnB4bGuiNLKlHyFsVs13u7cbfpaen2jjCRn1hzP3BNcqk90pLkZGliKZKu2mNxndL7Cwp+BBWKPKxCPWGssDMvs2ywLzoNsvu0nObZYvZ7TbLArMzz7LA/CbPssCUeZYF5se44kr/hAg5NvmS9Tel21r2DbInck+n5Hcf0uAw0nfJpPQa6RF7lkxyyks+hFMC2sr1bvoklz7JUzw+0V9uRlJU3q+LOFqxvjyblZdqGMsOELPc5usI/sjiNhIBG8xtsGPKPfKf4Q7imFIsFMV8a5OyxD5Z3/SLi31C7PobYaVgOV3uLJK/rjKUYxNPZOlWmpP57Jy6igUxQTtt1pOLSjsLS9IeR93gW7Y4cQKMSNJlFxbIjfsBipmp++uBurkEQSPnZrkrM/ms8659k9HOPpjg7yQqwXiBuSvYQPkboFB9AfzVB+zMsLwBlmuN2mxGfsYRulYPFX7YYQDMwqcdS3zEsz35O22AYsQgyd0dHOyrWXihntcQzVChPXR/I7xS0VM7QmVD3IYCmmPoUtW7LEhSJR1rwJLiaMW3L2Wn+tuCoyNrVlhx1YUdTqXB9NERPCBf5B0fTvUCfKiUNcfg9nJOtHzKSgk53H/ExAzd4fM3BvtRG4O9lWjpLiVaugpCQ7bFd1cyHK2cLlbi64RU7vDT/KQQrGUjhLINhYWFqrDoQ+fJ+eJYzsFCdHB+0tuJAOodz6eRUR297P5Ulm57845X2KlV1H+UL+wVG0U/KjeQTyVCC87s7E752YB0W6KMzAwUyk/K1JPKtxk4qphsBSJdw9cvmSmTRporJgQzyKyEk7N+SkVMb2NVSOPwet9eMb0h2NN3JtjdXkPzKdqfq3lseJ1vR/By3xntUvtmkI005Ge0VLFZCJRcmhIwuFh52avpNnMw7rN6Uf4dzVCFEicaGBYNKP25CnbfRoVdmzA59uzrgORhkNqW1jDLDkvnwthKjA4uyZjFvNW3gnmrXiKvnh1NspvoYlqpvFDnf9Uvjs9IAonMduVUFxadpZF8MCbqdEbmTlOarlAZ8TKDGYB/gcg7pveEZulWpxh/FyuO0qADs3aGbl8l7AwMq7pzb4eB8HvcI+NErxlfEf2+J5jj5fNKGw4nIxcXFcobvkO/MdzuAn0cfi02zUmMohxCr5MNO+BxKaepsGjlMDhA7HX1Xo6nMWQTdupCtXO3zARkEW8QFeVauy3aQ23k+bm057KiOvpLUUtb4sOspvZ9GywFvfLIXtY2F5jKq9HewSgjeFlkOQjsAtPeWsRz3ylvpNxzmqI9TQPs1sl2m3e2h3hgKKwTCD1fh7bU1CjIgU/wiUs0sxxdHz82R2OcxSgmhg8EZE09toolt9BWkf1r8xjti5lA71bROzryii7rMOYUx6VZg5KkWbTp3hmqyLIFCy2VXp5YqoTLkenHptLBx46gVrCfpKMBueaPZ2PqLMCeKUdLBtcBCzRH9jwWm2tUaCnHtMjdwUbEeq5T3OaEywc9JWqnU0yf5Ez0cOEqhBBePOiIXiBGRPshgnRkkjMgH9xhqMk9Gv4HTHN9sS16MiF+2+TMk/Xia7FndUrwEmOeS75NXJGY54j2Lk1BHkWyfvRpgzP4Knp5gdzyjGlfeSGUIXi/ZvRp0wUzkMi3al/M6uJ9HBLNi6GEKffo3XP2nZznhL7RQ4VQz14iRj4fzRSTXL7uWm9kWCg3budau8U8J5V6VBmOulDvE0l53nG+PLOQ5wUqz14GIseVJGX597Oy/F6TI9MPxe/ebDfMy6v/27wMHfPkVOOULYptA7DOfTRbRVnK2a7fOpI20ImZ+sRB+sSsVfrEMbL8P08ZkVsdUuNfp3yAf13ybv71yNn0SwuikG8z5G30G2eEQaw5N7SCDEKs1bjj5vhLF/A2fzutXp5sTEYA0myG7eWnoXaAvORqg/slLVRnRB9mO1vDCPYPG2U9TJBGWwW/K9Q81twfIRi7ervl37FsIBMrb8KOlh/cMhioYiU9FbXRgQXm8+cHAXvLIqthKvdc09+fqh4G9ZBc+ifOzlco5majQr6TwWtO1ipZhAJ7Ck8RyCGw15edPLmNodjspXunXNRgGIl5mgGSrld5Xk87nvAAvgLvnblZok6fkW088x5ldGJLyqygJ1SeYatIIMzVrL66ge12PbbSGVVlYIkjjgyEpxKHYGVlN1Fo/ubXsOfmnEBMIvP8uoJKGGxqwLvqvQ/sNywM9UgaiTjv3ndXbLvSwrHtSjHvJ3bydrX64g7DqzWXB0N7DH0j8KpmgSNNpPPVCtqnb2Q89h4F7Pv5/kRgn7LvYakNEwN1SvjuUppKpQq1NMtQFR+yEakdSEOnNFNmX7wFYarvjLtyrPlM6ebg55YR4d5RuahRrno+SImOrzdbPKm0r9G/mkrYAIOle8I1tGT9zbVp+BBS0JBgManOeHLVhV3x5h9y7HMHwx228/XNfP2+3cKhi37szrWRcs4nOtbMLNFe6Zn7OUhaoxHswZSGnLCPumgtf7xTOt5iY7FtMNwJAfvn200r5/ePt2NHDn3q1AVglHE8wuUWkpIy1NfiA3flEFgactaf7zWMFo/D6r+DexMHQ7yoPBKwfnoB1Dl+GZCV15r66V+oRmvFKmFtaITp8QOgm41AWDO4J0X5D+vD0MtQicKetlkIShP/vL2DuhX4Z0vn/f8Ar5RzczVIAIBDS419DXwU1dX3brIJm2RhF5JAhKChRkWT+hWwrgs2iAv4sbgxIYEiH1o/4ta2gDNAlQDpJpFhWEotVmyRSkssbe3z6AtqFIsJoYQIAiJWFKqxRnvzbFpDTUMCeZj3/M+d2UwQ+76/H2xm7p25cz/PPeeec/6Hdd49HXeg3xL1YMOJh5LsSQqSysBfhzaLH4xNT2TFZm2+W1P7jbAH2y4Pd5ZLIiVPFNjcH8+jvvew3kqL1sA4nZujpLfwOTwaUvkcjoeCbeFIMorPHpfuIIp6PAH0VGC+MkLjaSCnmLQpkcq0zcJNVer4b1YFHQlLFxppScD+Ao+aBi1+rpK3hmPhqEAkM9QjCYW9txZRuGkAnd6aTI4gw+NOUhP4R//Edg4z3ueQgyrNTVckSy76U6TysOsBGuBFv2P/LePpOxNLDHHCeP8nRvRRa++X9paMhjeIDGTshx27kkeimjLGXP6n
*/