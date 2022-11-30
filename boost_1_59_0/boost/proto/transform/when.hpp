///////////////////////////////////////////////////////////////////////////////
/// \file when.hpp
/// Definition of when transform.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_WHEN_HPP_EAN_10_29_2007
#define BOOST_PROTO_TRANSFORM_WHEN_HPP_EAN_10_29_2007

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/call.hpp>
#include <boost/proto/transform/make.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/transform/env.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Grammar, typename R, typename Fun>
        struct when_impl
          : transform<when<Grammar, Fun> >
        {
            typedef Grammar first;
            typedef Fun second;
            typedef typename Grammar::proto_grammar proto_grammar;

            // Note: do not evaluate is_callable<R> in this scope.
            // R may be an incomplete type at this point.

            template<typename Expr, typename State, typename Data>
            struct impl : transform_impl<Expr, State, Data>
            {
                // OK to evaluate is_callable<R> here. R should be compete by now.
                typedef
                    typename mpl::if_c<
                        is_callable<R>::value
                      , proto::call<Fun> // "R" is a function to call
                      , proto::make<Fun> // "R" is an object to construct
                    >::type
                which;

                typedef typename which::template impl<Expr, State, Data>::result_type result_type;

                /// Evaluate <tt>R(A0,A1,...)</tt> as a transform either with
                /// <tt>call\<\></tt> or with <tt>make\<\></tt> depending on
                /// whether <tt>is_callable\<R\>::value</tt> is \c true or
                /// \c false.
                ///
                /// \param e The current expression
                /// \param s The current state
                /// \param d An arbitrary data
                /// \pre <tt>matches\<Expr, Grammar\>::value</tt> is \c true
                /// \return <tt>which()(e, s, d)</tt>
                BOOST_FORCEINLINE
                result_type operator ()(
                    typename impl::expr_param   e
                  , typename impl::state_param  s
                  , typename impl::data_param   d
                ) const
                {
                    return typename which::template impl<Expr, State, Data>()(e, s, d);
                }
            };
        };
    }

    /// \brief A grammar element and a PrimitiveTransform that associates
    /// a transform with the grammar.
    ///
    /// Use <tt>when\<\></tt> to override a grammar's default transform
    /// with a custom transform. It is for used when composing larger
    /// transforms by associating smaller transforms with individual
    /// rules in your grammar, as in the following transform which
    /// counts the number of terminals in an expression.
    ///
    /// \code
    /// // Count the terminals in an expression tree.
    /// // Must be invoked with initial state == mpl::int_<0>().
    /// struct CountLeaves
    ///   : or_<
    ///         when<terminal<_>, mpl::next<_state>()>
    ///       , otherwise<fold<_, _state, CountLeaves> >
    ///     >
    /// {};
    /// \endcode
    ///
    /// In <tt>when\<G, T\></tt>, when \c T is a class type it is a
    /// PrimitiveTransform and the following equivalencies hold:
    ///
    /// <tt>boost::result_of\<when\<G,T\>(E,S,V)\>::type</tt> is the same as
    /// <tt>boost::result_of\<T(E,S,V)\>::type</tt>.
    ///
    /// <tt>when\<G,T\>()(e,s,d)</tt> is the same as
    /// <tt>T()(e,s,d)</tt>.
    template<typename Grammar, typename PrimitiveTransform /*= Grammar*/>
    struct when
      : PrimitiveTransform
    {
        typedef Grammar first;
        typedef PrimitiveTransform second;
        typedef typename Grammar::proto_grammar proto_grammar;
    };

    /// \brief A specialization that treats function pointer Transforms as
    /// if they were function type Transforms.
    ///
    /// This specialization requires that \c Fun is actually a function type.
    ///
    /// This specialization is required for nested transforms such as
    /// <tt>when\<G, T0(T1(_))\></tt>. In C++, functions that are used as
    /// parameters to other functions automatically decay to funtion
    /// pointer types. In other words, the type <tt>T0(T1(_))</tt> is
    /// indistinguishable from <tt>T0(T1(*)(_))</tt>. This specialization
    /// is required to handle these nested function pointer type transforms
    /// properly.
    template<typename Grammar, typename Fun>
    struct when<Grammar, Fun *>
      : when<Grammar, Fun>
    {};

    /// \brief Syntactic sugar for <tt>when\<_, Fun\></tt>, for use
    /// in grammars to handle all the cases not yet handled.
    ///
    /// Use <tt>otherwise\<T\></tt> in your grammars as a synonym for
    /// <tt>when\<_, T\></tt> as in the following transform which
    /// counts the number of terminals in an expression.
    ///
    /// \code
    /// // Count the terminals in an expression tree.
    /// // Must be invoked with initial state == mpl::int_<0>().
    /// struct CountLeaves
    ///   : or_<
    ///         when<terminal<_>, mpl::next<_state>()>
    ///       , otherwise<fold<_, _state, CountLeaves> >
    ///     >
    /// {};
    /// \endcode
    template<typename Fun>
    struct otherwise
      : when<_, Fun>
    {};

    namespace envns_
    {
        // Define the transforms global
        BOOST_PROTO_DEFINE_ENV_VAR(transforms_type, transforms);
    }

    using envns_::transforms;

    /// \brief This specialization uses the Data parameter as a collection
    /// of transforms that can be indexed by the specified rule.
    ///
    /// Use <tt>when\<T, external_transform\></tt> in your code when you would like
    /// to define a grammar once and use it to evaluate expressions with
    /// many different sets of transforms. The transforms are found by
    /// using the Data parameter as a map from rules to transforms.
    ///
    /// See \c action_map for an example.
    template<typename Grammar>
    struct when<Grammar, external_transform>
      : proto::transform<when<Grammar, external_transform> >
    {
        typedef Grammar first;
        typedef external_transform second;
        typedef typename Grammar::proto_grammar proto_grammar;

        template<typename Expr, typename State, typename Data>
        struct impl
          : remove_reference<
                typename mpl::eval_if_c<
                    proto::result_of::has_env_var<Data, transforms_type>::value
                  , proto::result_of::env_var<Data, transforms_type>
                  , proto::result_of::env_var<Data, data_type>
                >::type
            >::type::template when<Grammar>::template impl<Expr, State, Data>
        {};
    };

    /// \brief For defining a map of Rule/Transform pairs for use with
    /// <tt>when\<T, external_transform\></tt> to make transforms external to the grammar
    ///
    /// The following code defines a grammar with a couple of external transforms.
    /// It also defines an action_map that maps from rules to transforms. It then
    /// passes that transforms map at the Data parameter to the grammar. In this way,
    /// the behavior of the grammar can be modified post-hoc by passing a different
    /// action_map.
    ///
    /// \code
    /// struct int_terminal
    ///   : proto::terminal<int>
    /// {};
    /// 
    /// struct char_terminal
    ///   : proto::terminal<char>
    /// {};
    /// 
    /// struct my_grammar
    ///   : proto::or_<
    ///         proto::when< int_terminal, proto::external_transform >
    ///       , proto::when< char_terminal, proto::external_transform >
    ///       , proto::when<
    ///             proto::plus< my_grammar, my_grammar >
    ///           , proto::fold< _, int(), my_grammar >
    ///         >
    ///     >
    /// {};
    /// 
    /// struct my_transforms
    ///   : proto::external_transforms<
    ///         proto::when<int_terminal, print(proto::_value)>
    ///       , proto::when<char_terminal, print(proto::_value)>
    ///     >
    /// {};
    ///
    /// proto::literal<int> i(1);
    /// proto::literal<char> c('a');
    /// my_transforms trx;
    ///
    /// // Evaluate "i+c" using my_grammar with the specified transforms:
    /// my_grammar()(i + c, 0, trx);
    /// \endcode
    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_MPL_LIMIT_MAP_SIZE, typename T, mpl::na)>
    struct external_transforms
    {
        typedef mpl::map<BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_MAP_SIZE, T)> map_type;

        template<typename Rule>
        struct when
          : proto::when<_, typename mpl::at<map_type, Rule>::type>
        {};
    };

    // Other specializations of proto::when are generated by the preprocessor...
    #include <boost/proto/transform/detail/when.hpp>

    /// INTERNAL ONLY
    ///
    template<typename Grammar, typename Transform>
    struct is_callable<when<Grammar, Transform> >
      : mpl::true_
    {};

}} // namespace boost::proto

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* when.hpp
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
*/