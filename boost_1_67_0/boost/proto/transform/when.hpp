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