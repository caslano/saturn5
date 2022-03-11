///////////////////////////////////////////////////////////////////////////////
/// \file matches.hpp
/// Contains definition of matches\<\> metafunction for determining if
/// a given expression matches a given pattern.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006
#define BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/config.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/proto/detail/template_arity.hpp>
#include <boost/utility/enable_if.hpp>
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#include <boost/type_traits/is_array.hpp>
#endif
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/when.hpp>
#include <boost/proto/transform/impl.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable:4305) // 'specialization' : truncation from 'const int' to 'bool'
#endif

#define BOOST_PROTO_LOGICAL_typename_G  BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, typename G)
#define BOOST_PROTO_LOGICAL_G           BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, G)

namespace boost { namespace proto
{

    namespace detail
    {
        template<typename Expr, typename BasicExpr, typename Grammar>
        struct matches_;

        template<bool B, typename Pred>
        struct and_2;

        template<typename And, typename Expr, typename State, typename Data>
        struct _and_impl;

        template<typename T, typename U>
        struct array_matches
          : mpl::false_
        {};

        template<typename T, std::size_t M>
        struct array_matches<T[M], T *>
          : mpl::true_
        {};

        template<typename T, std::size_t M>
        struct array_matches<T[M], T const *>
          : mpl::true_
        {};

        template<typename T, std::size_t M>
        struct array_matches<T[M], T[proto::N]>
          : mpl::true_
        {};

        template<typename T, typename U
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(long Arity = detail::template_arity<U>::value)
        >
        struct lambda_matches
          : mpl::false_
        {};

        template<typename T>
        struct lambda_matches<T, proto::_ BOOST_PROTO_TEMPLATE_ARITY_PARAM(-1)>
          : mpl::true_
        {};

        template<typename T>
        struct lambda_matches<T, T BOOST_PROTO_TEMPLATE_ARITY_PARAM(-1)>
          : mpl::true_
        {};

        template<typename T, std::size_t M, typename U>
        struct lambda_matches<T[M], U BOOST_PROTO_TEMPLATE_ARITY_PARAM(-1)>
          : array_matches<T[M], U>
        {};

        template<typename T, std::size_t M>
        struct lambda_matches<T[M], _ BOOST_PROTO_TEMPLATE_ARITY_PARAM(-1)>
          : mpl::true_
        {};

        template<typename T, std::size_t M>
        struct lambda_matches<T[M], T[M] BOOST_PROTO_TEMPLATE_ARITY_PARAM(-1)>
          : mpl::true_
        {};

        template<template<typename> class T, typename Expr0, typename Grammar0>
        struct lambda_matches<T<Expr0>, T<Grammar0> BOOST_PROTO_TEMPLATE_ARITY_PARAM(1) >
          : lambda_matches<Expr0, Grammar0>
        {};

        // vararg_matches_impl
        template<typename Args1, typename Back, long From, long To>
        struct vararg_matches_impl;

        // vararg_matches
        template<typename Expr, typename Args1, typename Args2, typename Back, bool Can, bool Zero, typename Void = void>
        struct vararg_matches
          : mpl::false_
        {};

        template<typename Expr, typename Args1, typename Args2, typename Back>
        struct vararg_matches<Expr, Args1, Args2, Back, true, true, typename Back::proto_is_vararg_>
          : matches_<
                Expr
              , proto::basic_expr<ignore, Args1, Args1::arity>
              , proto::basic_expr<ignore, Args2, Args1::arity>
            >
        {};

        template<typename Expr, typename Args1, typename Args2, typename Back>
        struct vararg_matches<Expr, Args1, Args2, Back, true, false, typename Back::proto_is_vararg_>
          : and_2<
                matches_<
                    Expr
                  , proto::basic_expr<ignore, Args1, Args2::arity>
                  , proto::basic_expr<ignore, Args2, Args2::arity>
                >::value
              , vararg_matches_impl<Args1, typename Back::proto_grammar, Args2::arity + 1, Args1::arity>
            >
        {};

        // How terminal_matches<> handles references and cv-qualifiers.
        // The cv and ref matter *only* if the grammar has a top-level ref.
        //
        // Expr       |   Grammar    |  Matches?
        // -------------------------------------
        // T              T             yes
        // T &            T             yes
        // T const &      T             yes
        // T              T &           no
        // T &            T &           yes
        // T const &      T &           no
        // T              T const &     no
        // T &            T const &     no
        // T const &      T const &     yes

        template<typename T, typename U>
        struct is_cv_ref_compatible
          : mpl::true_
        {};

        template<typename T, typename U>
        struct is_cv_ref_compatible<T, U &>
          : mpl::false_
        {};

        template<typename T, typename U>
        struct is_cv_ref_compatible<T &, U &>
          : mpl::bool_<is_const<T>::value == is_const<U>::value>
        {};

    #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        // MSVC-7.1 has lots of problems with array types that have been
        // deduced. Partially specializing terminal_matches<> on array types
        // doesn't seem to work.
        template<
            typename T
          , typename U
          , bool B = is_array<BOOST_PROTO_UNCVREF(T)>::value
        >
        struct terminal_array_matches
          : mpl::false_
        {};

        template<typename T, typename U, std::size_t M>
        struct terminal_array_matches<T, U(&)[M], true>
          : is_convertible<T, U(&)[M]>
        {};

        template<typename T, typename U>
        struct terminal_array_matches<T, U(&)[proto::N], true>
          : is_convertible<T, U *>
        {};

        template<typename T, typename U>
        struct terminal_array_matches<T, U *, true>
          : is_convertible<T, U *>
        {};

        // terminal_matches
        template<typename T, typename U>
        struct terminal_matches
          : mpl::or_<
                mpl::and_<
                    is_cv_ref_compatible<T, U>
                  , lambda_matches<
                        BOOST_PROTO_UNCVREF(T)
                      , BOOST_PROTO_UNCVREF(U)
                    >
                >
              , terminal_array_matches<T, U>
            >
        {};
    #else
        // terminal_matches
        template<typename T, typename U>
        struct terminal_matches
          : mpl::and_<
                is_cv_ref_compatible<T, U>
              , lambda_matches<
                    BOOST_PROTO_UNCVREF(T)
                  , BOOST_PROTO_UNCVREF(U)
                >
            >
        {};

        template<typename T, std::size_t M>
        struct terminal_matches<T(&)[M], T(&)[proto::N]>
          : mpl::true_
        {};

        template<typename T, std::size_t M>
        struct terminal_matches<T(&)[M], T *>
          : mpl::true_
        {};

        // Avoid ambiguity errors on MSVC
        #if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
        template<typename T, std::size_t M>
        struct terminal_matches<T const (&)[M], T const[M]>
          : mpl::true_
        {};
        #endif
    #endif

        template<typename T>
        struct terminal_matches<T, T>
          : mpl::true_
        {};

        template<typename T>
        struct terminal_matches<T &, T>
          : mpl::true_
        {};

        template<typename T>
        struct terminal_matches<T const &, T>
          : mpl::true_
        {};

        template<typename T>
        struct terminal_matches<T, proto::_>
          : mpl::true_
        {};

        template<typename T>
        struct terminal_matches<T, exact<T> >
          : mpl::true_
        {};

        template<typename T, typename U>
        struct terminal_matches<T, proto::convertible_to<U> >
          : is_convertible<T, U>
        {};

        // matches_
        template<typename Expr, typename BasicExpr, typename Grammar>
        struct matches_
          : mpl::false_
        {};

        template<typename Expr, typename BasicExpr>
        struct matches_< Expr, BasicExpr, proto::_ >
          : mpl::true_
        {};

        template<typename Expr, typename Tag, typename Args1, long N1, typename Args2, long N2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, N1>, proto::basic_expr<Tag, Args2, N2> >
          : vararg_matches< Expr, Args1, Args2, typename Args2::back_, (N1+2 > N2), (N2 > N1) >
        {};

        template<typename Expr, typename Tag, typename Args1, long N1, typename Args2, long N2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, N1>, proto::basic_expr<proto::_, Args2, N2> >
          : vararg_matches< Expr, Args1, Args2, typename Args2::back_, (N1+2 > N2), (N2 > N1) >
        {};

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 0>, proto::basic_expr<Tag, Args2, 0> >
          : terminal_matches<typename Args1::child0, typename Args2::child0>
        {};

        template<typename Expr, typename Tag, typename Args1, typename Args2, long N2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 0>, proto::basic_expr<proto::_, Args2, N2> >
          : mpl::false_
        {};

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 0>, proto::basic_expr<proto::_, Args2, 0> >
          : terminal_matches<typename Args1::child0, typename Args2::child0>
        {};

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 1>, proto::basic_expr<Tag, Args2, 1> >
          : matches_<
                typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar
              , typename Args2::child0::proto_grammar
            >
        {};

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 1>, proto::basic_expr<proto::_, Args2, 1> >
          : matches_<
                typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar
              , typename Args2::child0::proto_grammar
            >
        {};

        #include <boost/proto/detail/and_n.hpp>
        #include <boost/proto/detail/or_n.hpp>
        #include <boost/proto/detail/matches_.hpp>
        #include <boost/proto/detail/vararg_matches_impl.hpp>
        #include <boost/proto/detail/lambda_matches.hpp>

        // handle proto::if_
        template<typename Expr, typename Tag, typename Args, long Arity, typename If, typename Then, typename Else>
        struct matches_<Expr, proto::basic_expr<Tag, Args, Arity>, proto::if_<If, Then, Else> >
          : mpl::eval_if_c<
                static_cast<bool>(
                    remove_reference<
                        typename when<_, If>::template impl<Expr, int, int>::result_type
                    >::type::value
                )
              , matches_<Expr, proto::basic_expr<Tag, Args, Arity>, typename Then::proto_grammar>
              , matches_<Expr, proto::basic_expr<Tag, Args, Arity>, typename Else::proto_grammar>
            >::type
        {
            typedef
                typename mpl::if_c<
                    static_cast<bool>(
                        remove_reference<
                            typename when<_, If>::template impl<Expr, int, int>::result_type
                        >::type::value
                    )
                  , Then
                  , Else
                >::type
            which;
        };

        // handle degenerate cases of proto::or_
        template<typename Expr, typename BasicExpr>
        struct matches_<Expr, BasicExpr, or_<> >
          : mpl::false_
        {
            typedef not_<_> which;
        };

        template<typename Expr, typename BasicExpr, typename G0>
        struct matches_<Expr, BasicExpr, or_<G0> >
          : matches_<Expr, BasicExpr, typename G0::proto_grammar>
        {
            typedef G0 which;
        };

        // handle degenerate cases of proto::and_
        template<typename Expr, typename BasicExpr>
        struct matches_<Expr, BasicExpr, and_<> >
          : mpl::true_
        {};

        template<typename Expr, typename BasicExpr, typename G0>
        struct matches_<Expr, BasicExpr, and_<G0> >
          : matches_<Expr, BasicExpr, typename G0::proto_grammar>
        {};

        // handle proto::not_
        template<typename Expr, typename BasicExpr, typename Grammar>
        struct matches_<Expr, BasicExpr, not_<Grammar> >
          : mpl::not_<matches_<Expr, BasicExpr, typename Grammar::proto_grammar> >
        {};

        // handle proto::switch_
        template<typename Expr, typename Tag, typename Args, long Arity, typename Cases, typename Transform>
        struct matches_<Expr, proto::basic_expr<Tag, Args, Arity>, switch_<Cases, Transform> >
          : matches_<
                Expr
              , proto::basic_expr<Tag, Args, Arity>
              , typename Cases::template case_<
                    typename when<_,Transform>::template impl<Expr,int,int>::result_type
                >::proto_grammar
            >
        {
            typedef
                typename Cases::template case_<
                    typename when<_, Transform>::template impl<Expr, int, int>::result_type
                >
            which;
        };

        // handle proto::switch_ with the default Transform for specially for better compile times
        template<typename Expr, typename Tag, typename Args, long Arity, typename Cases>
        struct matches_<Expr, proto::basic_expr<Tag, Args, Arity>, switch_<Cases> >
          : matches_<
                Expr
              , proto::basic_expr<Tag, Args, Arity>
              , typename Cases::template case_<Tag>::proto_grammar
            >
        {
            typedef typename Cases::template case_<Tag> which;
        };
    }

    /// \brief A Boolean metafunction that evaluates whether a given
    /// expression type matches a grammar.
    ///
    /// <tt>matches\<Expr,Grammar\></tt> inherits (indirectly) from
    /// \c mpl::true_ if <tt>Expr::proto_grammar</tt> matches
    /// <tt>Grammar::proto_grammar</tt>, and from \c mpl::false_
    /// otherwise.
    ///
    /// Non-terminal expressions are matched against a grammar
    /// according to the following rules:
    ///
    /// \li The wildcard pattern, \c _, matches any expression.
    /// \li An expression <tt>expr\<AT, listN\<A0,A1,...An\> \></tt>
    ///     matches a grammar <tt>expr\<BT, listN\<B0,B1,...Bn\> \></tt>
    ///     if \c BT is \c _ or \c AT, and if \c Ax matches \c Bx for
    ///     each \c x in <tt>[0,n)</tt>.
    /// \li An expression <tt>expr\<AT, listN\<A0,...An,U0,...Um\> \></tt>
    ///     matches a grammar <tt>expr\<BT, listM\<B0,...Bn,vararg\<V\> \> \></tt>
    ///     if \c BT is \c _ or \c AT, and if \c Ax matches \c Bx
    ///     for each \c x in <tt>[0,n)</tt> and if \c Ux matches \c V
    ///     for each \c x in <tt>[0,m)</tt>.
    /// \li An expression \c E matches <tt>or_\<B0,B1,...Bn\></tt> if \c E
    ///     matches some \c Bx for \c x in <tt>[0,n)</tt>.
    /// \li An expression \c E matches <tt>and_\<B0,B1,...Bn\></tt> if \c E
    ///     matches all \c Bx for \c x in <tt>[0,n)</tt>.
    /// \li An expression \c E matches <tt>if_\<T,U,V\></tt> if
    ///     <tt>boost::result_of\<when\<_,T\>(E,int,int)\>::type::value</tt>
    ///     is \c true and \c E matches \c U; or, if
    ///     <tt>boost::result_of\<when\<_,T\>(E,int,int)\>::type::value</tt>
    ///     is \c false and \c E matches \c V. (Note: \c U defaults to \c _
    ///     and \c V defaults to \c not_\<_\>.)
    /// \li An expression \c E matches <tt>not_\<T\></tt> if \c E does
    ///     not match \c T.
    /// \li An expression \c E matches <tt>switch_\<C,T\></tt> if
    ///     \c E matches <tt>C::case_\<boost::result_of\<T(E)\>::type\></tt>.
    ///     (Note: T defaults to <tt>tag_of\<_\>()</tt>.)
    ///
    /// A terminal expression <tt>expr\<AT,term\<A\> \></tt> matches
    /// a grammar <tt>expr\<BT,term\<B\> \></tt> if \c BT is \c AT or
    /// \c proto::_ and if one of the following is true:
    ///
    /// \li \c B is the wildcard pattern, \c _
    /// \li \c A is \c B
    /// \li \c A is <tt>B &</tt>
    /// \li \c A is <tt>B const &</tt>
    /// \li \c B is <tt>exact\<A\></tt>
    /// \li \c B is <tt>convertible_to\<X\></tt> and
    ///     <tt>is_convertible\<A,X\>::value</tt> is \c true.
    /// \li \c A is <tt>X[M]</tt> or <tt>X(&)[M]</tt> and
    ///     \c B is <tt>X[proto::N]</tt>.
    /// \li \c A is <tt>X(&)[M]</tt> and \c B is <tt>X(&)[proto::N]</tt>.
    /// \li \c A is <tt>X[M]</tt> or <tt>X(&)[M]</tt> and
    ///     \c B is <tt>X*</tt>.
    /// \li \c B lambda-matches \c A (see below).
    ///
    /// A type \c B lambda-matches \c A if one of the following is true:
    ///
    /// \li \c B is \c A
    /// \li \c B is the wildcard pattern, \c _
    /// \li \c B is <tt>T\<B0,B1,...Bn\></tt> and \c A is
    ///     <tt>T\<A0,A1,...An\></tt> and for each \c x in
    ///     <tt>[0,n)</tt>, \c Ax and \c Bx are types
    ///     such that \c Ax lambda-matches \c Bx
    template<typename Expr, typename Grammar>
    struct matches
      : detail::matches_<
            typename Expr::proto_derived_expr
          , typename Expr::proto_grammar
          , typename Grammar::proto_grammar
        >
    {};

    /// INTERNAL ONLY
    ///
    template<typename Expr, typename Grammar>
    struct matches<Expr &, Grammar>
      : detail::matches_<
            typename Expr::proto_derived_expr
          , typename Expr::proto_grammar
          , typename Grammar::proto_grammar
        >
    {};

    /// \brief A wildcard grammar element that matches any expression,
    /// and a transform that returns the current expression unchanged.
    ///
    /// The wildcard type, \c _, is a grammar element such that
    /// <tt>matches\<E,_\>::value</tt> is \c true for any expression
    /// type \c E.
    ///
    /// The wildcard can also be used as a stand-in for a template
    /// argument when matching terminals. For instance, the following
    /// is a grammar that will match any <tt>std::complex\<\></tt>
    /// terminal:
    ///
    /// \code
    /// BOOST_MPL_ASSERT((
    ///     matches<
    ///         terminal<std::complex<double> >::type
    ///       , terminal<std::complex< _ > >
    ///     >
    /// ));
    /// \endcode
    ///
    /// When used as a transform, \c _ returns the current expression
    /// unchanged. For instance, in the following, \c _ is used with
    /// the \c fold\<\> transform to fold the children of a node:
    ///
    /// \code
    /// struct CountChildren
    ///   : or_<
    ///         // Terminals have no children
    ///         when<terminal<_>, mpl::int_<0>()>
    ///         // Use fold<> to count the children of non-terminals
    ///       , otherwise<
    ///             fold<
    ///                 _ // <-- fold the current expression
    ///               , mpl::int_<0>()
    ///               , mpl::plus<_state, mpl::int_<1> >()
    ///             >
    ///         >
    ///     >
    /// {};
    /// \endcode
    struct _ : transform<_>
    {
        typedef _ proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// \param expr An expression
            /// \return \c e
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::expr_param)
            operator()(
                typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return e;
            }
        };
    };

    namespace detail
    {
        template<typename Expr, typename State, typename Data>
        struct _and_impl<proto::and_<>, Expr, State, Data>
          : proto::_::impl<Expr, State, Data>
        {};

        template<typename G0, typename Expr, typename State, typename Data>
        struct _and_impl<proto::and_<G0>, Expr, State, Data>
          : proto::when<proto::_, G0>::template impl<Expr, State, Data>
        {};
    }

    /// \brief Inverts the set of expressions matched by a grammar. When
    /// used as a transform, \c not_\<\> returns the current expression
    /// unchanged.
    ///
    /// If an expression type \c E does not match a grammar \c G, then
    /// \c E \e does match <tt>not_\<G\></tt>. For example,
    /// <tt>not_\<terminal\<_\> \></tt> will match any non-terminal.
    template<typename Grammar>
    struct not_ : transform<not_<Grammar> >
    {
        typedef not_ proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// \param e An expression
            /// \pre <tt>matches\<Expr,not_\>::value</tt> is \c true.
            /// \return \c e
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::expr_param)
            operator()(
                typename impl::expr_param e
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return e;
            }
        };
    };

    /// \brief Used to select one grammar or another based on the result
    /// of a compile-time Boolean. When used as a transform, \c if_\<\>
    /// selects between two transforms based on a compile-time Boolean.
    ///
    /// When <tt>if_\<If,Then,Else\></tt> is used as a grammar, \c If
    /// must be a Proto transform and \c Then and \c Else must be grammars.
    /// An expression type \c E matches <tt>if_\<If,Then,Else\></tt> if
    /// <tt>boost::result_of\<when\<_,If\>(E,int,int)\>::type::value</tt>
    /// is \c true and \c E matches \c U; or, if
    /// <tt>boost::result_of\<when\<_,If\>(E,int,int)\>::type::value</tt>
    /// is \c false and \c E matches \c V.
    ///
    /// The template parameter \c Then defaults to \c _
    /// and \c Else defaults to \c not\<_\>, so an expression type \c E
    /// will match <tt>if_\<If\></tt> if and only if
    /// <tt>boost::result_of\<when\<_,If\>(E,int,int)\>::type::value</tt>
    /// is \c true.
    ///
    /// \code
    /// // A grammar that only matches integral terminals,
    /// // using is_integral<> from Boost.Type_traits.
    /// struct IsIntegral
    ///   : and_<
    ///         terminal<_>
    ///       , if_< is_integral<_value>() >
    ///     >
    /// {};
    /// \endcode
    ///
    /// When <tt>if_\<If,Then,Else\></tt> is used as a transform, \c If,
    /// \c Then and \c Else must be Proto transforms. When applying
    /// the transform to an expression \c E, state \c S and data \c V,
    /// if <tt>boost::result_of\<when\<_,If\>(E,S,V)\>::type::value</tt>
    /// is \c true then the \c Then transform is applied; otherwise
    /// the \c Else transform is applied.
    ///
    /// \code
    /// // Match a terminal. If the terminal is integral, return
    /// // mpl::true_; otherwise, return mpl::false_.
    /// struct IsIntegral2
    ///   : when<
    ///         terminal<_>
    ///       , if_<
    ///             is_integral<_value>()
    ///           , mpl::true_()
    ///           , mpl::false_()
    ///         >
    ///     >
    /// {};
    /// \endcode
    template<
        typename If
      , typename Then   // = _
      , typename Else   // = not_<_>
    >
    struct if_ : transform<if_<If, Then, Else> >
    {
        typedef if_ proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef
                typename when<_, If>::template impl<Expr, State, Data>::result_type
            condition;

            typedef
                typename mpl::if_c<
                    static_cast<bool>(remove_reference<condition>::type::value)
                  , when<_, Then>
                  , when<_, Else>
                >::type
            which;

            typedef typename which::template impl<Expr, State, Data>::result_type result_type;

            /// \param e An expression
            /// \param s The current state
            /// \param d A data of arbitrary type
            /// \return <tt>which::impl<Expr, State, Data>()(e, s, d)</tt>
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return typename which::template impl<Expr, State, Data>()(e, s, d);
            }
        };
    };

    /// \brief For matching one of a set of alternate grammars. Alternates
    /// tried in order to avoid ambiguity. When used as a transform, \c or_\<\>
    /// applies the transform associated with the first grammar that matches
    /// the expression.
    ///
    /// An expression type \c E matches <tt>or_\<B0,B1,...Bn\></tt> if \c E
    /// matches any \c Bx for \c x in <tt>[0,n)</tt>.
    ///
    /// When applying <tt>or_\<B0,B1,...Bn\></tt> as a transform with an
    /// expression \c e of type \c E, state \c s and data \c d, it is
    /// equivalent to <tt>Bx()(e, s, d)</tt>, where \c x is the lowest
    /// number such that <tt>matches\<E,Bx\>::value</tt> is \c true.
    template<BOOST_PROTO_LOGICAL_typename_G>
    struct or_ : transform<or_<BOOST_PROTO_LOGICAL_G> >
    {
        typedef or_ proto_grammar;

        /// \param e An expression
        /// \param s The current state
        /// \param d A data of arbitrary type
        /// \pre <tt>matches\<Expr,or_\>::value</tt> is \c true.
        /// \return <tt>which()(e, s, d)</tt>, where <tt>which</tt> is the
        /// sub-grammar that matched <tt>Expr</tt>.

        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::matches_<
                typename Expr::proto_derived_expr
              , typename Expr::proto_grammar
              , or_
            >::which::template impl<Expr, State, Data>
        {};

        template<typename Expr, typename State, typename Data>
        struct impl<Expr &, State, Data>
          : detail::matches_<
                typename Expr::proto_derived_expr
              , typename Expr::proto_grammar
              , or_
            >::which::template impl<Expr &, State, Data>
        {};
    };

    /// \brief For matching all of a set of grammars. When used as a
    /// transform, \c and_\<\> applies the transforms associated with
    /// the each grammar in the set, and returns the result of the last.
    ///
    /// An expression type \c E matches <tt>and_\<B0,B1,...Bn\></tt> if \c E
    /// matches all \c Bx for \c x in <tt>[0,n)</tt>.
    ///
    /// When applying <tt>and_\<B0,B1,...Bn\></tt> as a transform with an
    /// expression \c e, state \c s and data \c d, it is
    /// equivalent to <tt>(B0()(e, s, d),B1()(e, s, d),...Bn()(e, s, d))</tt>.
    template<BOOST_PROTO_LOGICAL_typename_G>
    struct and_ : transform<and_<BOOST_PROTO_LOGICAL_G> >
    {
        typedef and_ proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::_and_impl<and_, Expr, State, Data>
        {};
    };

    /// \brief For matching one of a set of alternate grammars, which
    /// are looked up based on some property of an expression. The
    /// property on which to dispatch is specified by the \c Transform
    /// template parameter, which defaults to <tt>tag_of\<_\>()</tt>.
    /// That is, when the \c Trannsform is not specified, the alternate
    /// grammar is looked up using the tag type of the current expression.
    ///
    /// When used as a transform, \c switch_\<\> applies the transform
    /// associated with the grammar that matches the expression.
    ///
    /// \note \c switch_\<\> is functionally identical to \c or_\<\> but
    /// is often more efficient. It does a fast, O(1) lookup using the
    /// result of the specified transform to find a sub-grammar that may
    /// potentially match the expression.
    ///
    /// An expression type \c E matches <tt>switch_\<C,T\></tt> if \c E
    /// matches <tt>C::case_\<boost::result_of\<T(E)\>::type\></tt>.
    ///
    /// When applying <tt>switch_\<C,T\></tt> as a transform with an
    /// expression \c e of type \c E, state \c s of type \S and data
    /// \c d of type \c D, it is equivalent to
    /// <tt>C::case_\<boost::result_of\<T(E,S,D)\>::type\>()(e, s, d)</tt>.
    template<typename Cases, typename Transform>
    struct switch_ : transform<switch_<Cases, Transform> >
    {
        typedef switch_ proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl
          : Cases::template case_<
                typename when<_, Transform>::template impl<Expr, State, Data>::result_type
            >::template impl<Expr, State, Data>
        {};
    };

    /// INTERNAL ONLY (This is merely a compile-time optimization for the common case)
    ///
    template<typename Cases>
    struct switch_<Cases> : transform<switch_<Cases> >
    {
        typedef switch_ proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl
          : Cases::template case_<typename Expr::proto_tag>::template impl<Expr, State, Data>
        {};

        template<typename Expr, typename State, typename Data>
        struct impl<Expr &, State, Data>
          : Cases::template case_<typename Expr::proto_tag>::template impl<Expr &, State, Data>
        {};
    };

    /// \brief For forcing exact matches of terminal types.
    ///
    /// By default, matching terminals ignores references and
    /// cv-qualifiers. For instance, a terminal expression of
    /// type <tt>terminal\<int const &\>::type</tt> will match
    /// the grammar <tt>terminal\<int\></tt>. If that is not
    /// desired, you can force an exact match with
    /// <tt>terminal\<exact\<int\> \></tt>. This will only
    /// match integer terminals where the terminal is held by
    /// value.
    template<typename T>
    struct exact
    {};

    /// \brief For matching terminals that are convertible to
    /// a type.
    ///
    /// Use \c convertible_to\<\> to match a terminal that is
    /// convertible to some type. For example, the grammar
    /// <tt>terminal\<convertible_to\<int\> \></tt> will match
    /// any terminal whose argument is convertible to an integer.
    ///
    /// \note The trait \c is_convertible\<\> from Boost.Type_traits
    /// is used to determinal convertibility.
    template<typename T>
    struct convertible_to
    {};

    /// \brief For matching a Grammar to a variable number of
    /// sub-expressions.
    ///
    /// An expression type <tt>expr\<AT, listN\<A0,...An,U0,...Um\> \></tt>
    /// matches a grammar <tt>expr\<BT, listM\<B0,...Bn,vararg\<V\> \> \></tt>
    /// if \c BT is \c _ or \c AT, and if \c Ax matches \c Bx
    /// for each \c x in <tt>[0,n)</tt> and if \c Ux matches \c V
    /// for each \c x in <tt>[0,m)</tt>.
    ///
    /// For example:
    ///
    /// \code
    /// // Match any function call expression, irregardless
    /// // of the number of function arguments:
    /// struct Function
    ///   : function< vararg<_> >
    /// {};
    /// \endcode
    ///
    /// When used as a transform, <tt>vararg\<G\></tt> applies
    /// <tt>G</tt>'s transform.
    template<typename Grammar>
    struct vararg
      : Grammar
    {
        /// INTERNAL ONLY
        typedef void proto_is_vararg_;
    };

    /// INTERNAL ONLY
    ///
    template<BOOST_PROTO_LOGICAL_typename_G>
    struct is_callable<or_<BOOST_PROTO_LOGICAL_G> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<BOOST_PROTO_LOGICAL_typename_G>
    struct is_callable<and_<BOOST_PROTO_LOGICAL_G> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Grammar>
    struct is_callable<not_<Grammar> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename If, typename Then, typename Else>
    struct is_callable<if_<If, Then, Else> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Grammar>
    struct is_callable<vararg<Grammar> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Cases, typename Transform>
    struct is_callable<switch_<Cases, Transform> >
      : mpl::true_
    {};

}}

#undef BOOST_PROTO_LOGICAL_typename_G
#undef BOOST_PROTO_LOGICAL_G

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* matches.hpp
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
*/