///////////////////////////////////////////////////////////////////////////////
/// \file pass_through.hpp
///
/// Definition of the pass_through transform, which is the default transform
/// of all of the expression generator metafunctions such as unary_plus<>, plus<>
/// and nary_expr<>.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_PASS_THROUGH_HPP_EAN_12_26_2006
#define BOOST_PROTO_TRANSFORM_PASS_THROUGH_HPP_EAN_12_26_2006

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/args.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/detail/ignore_unused.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<
            typename Grammar
          , typename Domain
          , typename Expr
          , typename State
          , typename Data
          , long Arity = arity_of<Expr>::value
        >
        struct pass_through_impl
        {};

        #include <boost/proto/transform/detail/pass_through_impl.hpp>

        template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
        struct pass_through_impl<Grammar, Domain, Expr, State, Data, 0>
          : transform_impl<Expr, State, Data>
        {
            typedef Expr result_type;

            /// \param e An expression
            /// \return \c e
            /// \throw nothrow
            BOOST_FORCEINLINE
            BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename pass_through_impl::expr_param)
            operator()(
                typename pass_through_impl::expr_param e
              , typename pass_through_impl::state_param
              , typename pass_through_impl::data_param
            ) const
            {
                return e;
            }
        };

    } // namespace detail

    /// \brief A PrimitiveTransform that transforms the child expressions
    /// of an expression node according to the corresponding children of
    /// a Grammar.
    ///
    /// Given a Grammar such as <tt>plus\<T0, T1\></tt>, an expression type
    /// that matches the grammar such as <tt>plus\<E0, E1\>::type</tt>, a
    /// state \c S and a data \c V, the result of applying the
    /// <tt>pass_through\<plus\<T0, T1\> \></tt> transform is:
    ///
    /// \code
    /// plus<
    ///     T0::result<T0(E0, S, V)>::type
    ///   , T1::result<T1(E1, S, V)>::type
    /// >::type
    /// \endcode
    ///
    /// The above demonstrates how child transforms and child expressions
    /// are applied pairwise, and how the results are reassembled into a new
    /// expression node with the same tag type as the original.
    ///
    /// The explicit use of <tt>pass_through\<\></tt> is not usually needed,
    /// since the expression generator metafunctions such as
    /// <tt>plus\<\></tt> have <tt>pass_through\<\></tt> as their default
    /// transform. So, for instance, these are equivalent:
    ///
    /// \code
    /// // Within a grammar definition, these are equivalent:
    /// when< plus<X, Y>, pass_through< plus<X, Y> > >
    /// when< plus<X, Y>, plus<X, Y> >
    /// when< plus<X, Y> > // because of when<class X, class Y=X>
    /// plus<X, Y>         // because plus<> is both a
    ///                    //   grammar and a transform
    /// \endcode
    ///
    /// For example, consider the following transform that promotes all
    /// \c float terminals in an expression to \c double.
    ///
    /// \code
    /// // This transform finds all float terminals in an expression and promotes
    /// // them to doubles.
    /// struct Promote
    ///  : or_<
    ///         when<terminal<float>, terminal<double>::type(_value) >
    ///         // terminal<>'s default transform is a no-op:
    ///       , terminal<_>
    ///         // nary_expr<> has a pass_through<> transform:
    ///       , nary_expr<_, vararg<Promote> >
    ///     >
    /// {};
    /// \endcode
    template<typename Grammar, typename Domain /* = deduce_domain*/>
    struct pass_through
      : transform<pass_through<Grammar, Domain> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::pass_through_impl<Grammar, Domain, Expr, State, Data>
        {};
    };

    /// INTERNAL ONLY
    ///
    template<typename Grammar, typename Domain>
    struct is_callable<pass_through<Grammar, Domain> >
      : mpl::true_
    {};

}} // namespace boost::proto

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* pass_through.hpp
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
*/