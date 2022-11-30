///////////////////////////////////////////////////////////////////////////////
/// \file fold.hpp
/// Contains definition of the fold<> and reverse_fold<> transforms.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_FOLD_HPP_EAN_11_04_2007
#define BOOST_PROTO_TRANSFORM_FOLD_HPP_EAN_11_04_2007

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/reverse_fold.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/transform/when.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Transform, typename Data>
        struct as_callable
        {
            as_callable(Data d)
              : d_(d)
            {}

            template<typename Sig>
            struct result;

            template<typename This, typename State, typename Expr>
            struct result<This(State, Expr)>
            {
                typedef
                    typename when<_, Transform>::template impl<Expr, State, Data>::result_type
                type;
            };

            template<typename State, typename Expr>
            typename when<_, Transform>::template impl<Expr &, State const &, Data>::result_type
            operator ()(State const &s, Expr &e) const
            {
                return typename when<_, Transform>::template impl<Expr &, State const &, Data>()(e, s, this->d_);
            }

        private:
            Data d_;
        };

        template<
            typename State0
          , typename Fun
          , typename Expr
          , typename State
          , typename Data
          , long Arity = arity_of<Expr>::value
        >
        struct fold_impl
        {};

        template<
            typename State0
          , typename Fun
          , typename Expr
          , typename State
          , typename Data
          , long Arity = arity_of<Expr>::value
        >
        struct reverse_fold_impl
        {};

        #include <boost/proto/transform/detail/fold_impl.hpp>

    } // namespace detail

    /// \brief A PrimitiveTransform that invokes the <tt>fusion::fold\<\></tt>
    /// algorithm to accumulate
    template<typename Sequence, typename State0, typename Fun>
    struct fold : transform<fold<Sequence, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            /// \brief A Fusion sequence.
            typedef
                typename remove_reference<
                    typename when<_, Sequence>::template impl<Expr, State, Data>::result_type
                >::type
            sequence;

            /// \brief An initial state for the fold.
            typedef
                typename remove_reference<
                    typename when<_, State0>::template impl<Expr, State, Data>::result_type
                >::type
            state0;

            /// \brief <tt>fun(d)(e,s) == when\<_,Fun\>()(e,s,d)</tt>
            typedef
                detail::as_callable<Fun, Data>
            fun;

            typedef
                typename fusion::result_of::fold<
                    sequence
                  , state0
                  , fun
                >::type
            result_type;

            /// Let \c seq be <tt>when\<_, Sequence\>()(e, s, d)</tt>, let
            /// \c state0 be <tt>when\<_, State0\>()(e, s, d)</tt>, and
            /// let \c fun(d) be an object such that <tt>fun(d)(e, s)</tt>
            /// is equivalent to <tt>when\<_, Fun\>()(e, s, d)</tt>. Then, this
            /// function returns <tt>fusion::fold(seq, state0, fun(d))</tt>.
            ///
            /// \param e The current expression
            /// \param s The current state
            /// \param d An arbitrary data
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                typename when<_, Sequence>::template impl<Expr, State, Data> seq;
                detail::as_callable<Fun, Data> f(d);
                return fusion::fold(
                    seq(e, s, d)
                  , typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d)
                  , f
                );
            }
        };
    };

    /// \brief A PrimitiveTransform that is the same as the
    /// <tt>fold\<\></tt> transform, except that it folds
    /// back-to-front instead of front-to-back.
    template<typename Sequence, typename State0, typename Fun>
    struct reverse_fold  : transform<reverse_fold<Sequence, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            /// \brief A Fusion sequence.
            typedef
                typename remove_reference<
                    typename when<_, Sequence>::template impl<Expr, State, Data>::result_type
                >::type
            sequence;

            /// \brief An initial state for the fold.
            typedef
                typename remove_reference<
                    typename when<_, State0>::template impl<Expr, State, Data>::result_type
                >::type
            state0;

            /// \brief <tt>fun(d)(e,s) == when\<_,Fun\>()(e,s,d)</tt>
            typedef
                detail::as_callable<Fun, Data>
            fun;

            typedef
                typename fusion::result_of::reverse_fold<
                    sequence
                  , state0
                  , fun
                >::type
            result_type;

            /// Let \c seq be <tt>when\<_, Sequence\>()(e, s, d)</tt>, let
            /// \c state0 be <tt>when\<_, State0\>()(e, s, d)</tt>, and
            /// let \c fun(d) be an object such that <tt>fun(d)(e, s)</tt>
            /// is equivalent to <tt>when\<_, Fun\>()(e, s, d)</tt>. Then, this
            /// function returns <tt>fusion::fold(seq, state0, fun(d))</tt>.
            ///
            /// \param e The current expression
            /// \param s The current state
            /// \param d An arbitrary data
            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                typename when<_, Sequence>::template impl<Expr, State, Data> seq;
                detail::as_callable<Fun, Data> f(d);
                return fusion::reverse_fold(
                    seq(e, s, d)
                  , typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d)
                  , f
                );
            }
        };
    };

    // This specialization is only for improved compile-time performance
    // in the commom case when the Sequence transform is \c proto::_.
    //
    /// INTERNAL ONLY
    ///
    template<typename State0, typename Fun>
    struct fold<_, State0, Fun> : transform<fold<_, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::fold_impl<State0, Fun, Expr, State, Data>
        {};
    };

    // This specialization is only for improved compile-time performance
    // in the commom case when the Sequence transform is \c proto::_.
    //
    /// INTERNAL ONLY
    ///
    template<typename State0, typename Fun>
    struct reverse_fold<_, State0, Fun> : transform<reverse_fold<_, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : detail::reverse_fold_impl<State0, Fun, Expr, State, Data>
        {};
    };

    /// INTERNAL ONLY
    ///
    template<typename Sequence, typename State, typename Fun>
    struct is_callable<fold<Sequence, State, Fun> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Sequence, typename State, typename Fun>
    struct is_callable<reverse_fold<Sequence, State, Fun> >
      : mpl::true_
    {};

}}

#endif

/* fold.hpp
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
*/