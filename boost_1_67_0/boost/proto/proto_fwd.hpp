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
# define BOOST_PROTO_DISABLE_MSVC_C4180 __pragma(warning(disable : 4180))  // qualifier applied to function type has no meaning; ignored
# define BOOST_PROTO_DISABLE_MSVC_C4522 __pragma(warning(disable : 4522))  // 'class' : multiple assignment operators specified
# define BOOST_PROTO_DISABLE_MSVC_C4714 __pragma(warning(disable : 4714))  // function 'xxx' marked as __forceinline not inlined
#else
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
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
*/