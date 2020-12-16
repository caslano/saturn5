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
He91lTN/0gX/nfAi3EpfV/xs4Y/gVvq64b8Vnnm1Mn49k/6DWb+LE+TfdnyL4jL/duBvCif/7PH/x3i94jL/PsH/orjMv41LufZsemGC/uOz+EmKy/7bc/gUxWX/7Xn8RNVl/3EZffCUhs/zE8x/D8QfZvtuih9zkDP/MAy/R/j0sBP/Ufhdwm/BrfjPxkcKv+dKpX99tmF82qbx8etmpu8P+NP4GsV3rHbK1zX4JuG9r3DK17X4k8KrcOv4XYdvEL4Vt68v/Z721cy/jATl/1L8CLyv4pOP4vxrpm8l3kf4ctzqX12Fdxe+FW9mpQ/vJPy44cr4aSXnQPP4pyaYv92KT8fTFVfnl7/CfyP8XdyqbTvxY4UPXukc3138fozwFSuV/h/HarNm/nUWvgbvpjjlz25/T8XvE74Yt9rffPxO4c+uoH5Z/RO8Tnj/y5X2l7J4rmb9Ty98oXDqp319oTdeKZz2w76+0AevEE77YadvAB5QXLYfa64ivYrL+fP1+KF4huJcP7bPj0/gnYQ3W+WE9hN+g7Gnz8Kt4+ulrb1a+GO43f6CFyRIX6aZvh/wIjxT8TlnOvMfv+D5wrNW2+0LDQDfF/5b3Epf6Bpz/ZGYPzjIOr/jPfA0xZn/tduPpXg34XfhXuv8jndRXM7/LsM7Ky7nf+uuow6o/T/Zv8OfSWmcf4eZ/m+8LeH39zo+6PfsfVzJX/xg4eV4a/PdbryN8Cdxa3zZ7Hr2VfhhK5TyV0deJesf/489VeschwS+EdetX6vHh+nWN+C68UkGY+UtPZL3Lw/DR3bjd4/jl13qlL/D8RHC/4Lb/Td8uPBelyn9N3yY8Atwu//2JP0zzf7twn+nmT9ttZH5Dc36jdZ4iWb9Rjoe0KzfqMWXa9a3nY1fKJz21x4fn4+fo1k/cCW+UHjzS5z0XYVXCi/B7fkfOtd/Uly2L13xteL6ZJ905/h2w+8X3r6Nc3y74/cK9+PW8e2B3624XB9aj+ep/XdZfvGTFJflN/Mpxv+e5NdnB+JX4B0U39HBOb8MwlcJf+cSJ/8n4xHhAy91UlP/NOPDZPXThX+An5Hs+pQL/xc+PvH6HFf+HT4u8fypK899hjxMS97+z8avasEcjuLHLHfa/zn4FcJrcKv9n4uvEv4ybrX/AfxC4UMvVvq/LxvGq43z3z6eS/BnDbk+2ukfLcWftlwp/2nW+RXfJJzyb/ePzsUfU1yW/7xXGB8p509ZP+fiQ8T6T/rndv3MxwcLX45b9fN0fKDwrbhVP8/Aj1Bc9s/r6snvlsnPD+vwaXi54iPOcdL3MH6y8MW4lb5H8KnCX8Kt9D2KTxae8zvl+L7D+cHsPw1KcP1yCT4bT1Oc/pPd/tbipwjfcKGzt+/g33v29IMucsr/j1zcfcPY0xfidm/pPfY32frc/eC1eGmL5OXnYrwjPkrx0HnO8bkE7yD8ftw6Ppfi7YQb5zvH5zI8Q7gft8/ff6M8NEuevt34O/wyUQ3/Aid9P+JbhB+PW+n7CX9T+ArcSt/P+OvCv8Gt9GV/ShnTpO9YvBJPln+j8Ao8Wf79Bl+AJ8u/4/AyPGn+fcULT1b/duOX44WKb6Z+tLHyD/+98LbnUpas/MMvFV6MW/N/aTvpwwj/M26Pn76lfLZKnr7P8K64aB/s9H2OHyp8MW6l7wu8Ey7aBzt93+Ot8WTtQyE53VzTPw/hz7RJfv66CF9GAPd4HC+tdc5fq/CI8Dtx6/ivxhcK341bx/8KfqsU7jtbmX84yGNkaebPR+ODNPPnIfw1pf2Q89ML8c2Ky/npMP5XxeX89L34KsXl9fP78MsVl9fP8w72GNfo1rfgV2v69/PxZcI71yo=
*/