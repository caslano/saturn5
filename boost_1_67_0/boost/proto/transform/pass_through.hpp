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