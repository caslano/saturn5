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
dY5mz0eet6WsaB104wc9W8ueHLrZIDTnVre+36WoQeddfg/UoA7yHIbdE+ZNlVAE1BXkgtEgiQj4jTV2/QjnDIZ6E/b4HixaG2Lisu/yVxe6JPfWChlfgf0Ulc4cm9wxv5jcgTjk84RxHKjfMLydEcrnViMtYImBsp/f6QJANFMTWx1w9TUhpcmtQOl7fhfXic/y5bzu9RHBmVuDcqcTIdv8k2iL39pr2cw5Gzm1Itf+sbDyHwGaQVNb0kt+GXcnqSQFqTEPtk/SaxQ7YZ2/sj4yIu3BMnXCnQfrkeNyKQRDksca9p73jIfw6+8jlSxkP8B6A58G631rnEZ8FDlCkvblLHs8CaN3McnuRjZeUeRVZ74br4//3G0m580+4ZwetkixBmH6L/QMav0/9DT4Cz0dqNpmwWhzL46Cyz3Ec/e4iGCwNLXkApipvr0M/3QubmWjj5OMieaJViAqvfCXS8UFo3yFvpoFn1/PH4XK0FQ5wEOZVKH8OTRafSeUg/viPGT4lXxvcsHwEJKH4uZaPpidZT1TfWcbdRgLhAWOvQql7vBhhyqDIo5FLzsUb82fh0ioFvKVTpEdwB0OfmjdMuaNhLx28C4sEbm54eZJDWPwN+XCSPCLpoZR+JtwQV8xc+6uSa/mj8BR1lzQy/Z+eGnoy8OpftGGezlAJW4YeeCgHbCuuNW6tiNiuwRyC3oSNLoLUwCsYgDb/vIJofMo4E28TfCsT57dYke3B/vkbiCtlyAs95NPLapCxMyy72neGHH/tu55FtcyGCUU2fqmnVJl6mqvlx/dzYYGfr99K+q4UB26R9uuNPlfJrgVmKd3EXjRzW46WjnxNxteQwN9WHQg+uSC6RvrAxOmzVrWVk8/gjjHch3QGTX+zPVdSxIg60KPkUX5lMYDeUegAPRcuMksIDh/qjsLPncvmeBS7ImDAv0ECN6erAnFB7rpBZ8FFRg+uQ0eYJiCQvbX+8y9+XZgH1duCfcuFm8ASR0pFIFGQTuvcpR5MRI4H3q2bguEzYea+N2LI4LtqaEhD8U6jAd/4qS4QzIeufTLBAhR4GFutlQlYYbFDnFvNb4C9Ooz1+InW54v1nonh86b+RzjzUPe0bYvxcnOggX0Iao4yCjinTUYNjNKtpiUkQb/5PVvRNznQcb7vLa9M+K5c9hfJRfW46mCQa11Q/NgwVNPwkZBO9LSQosPQXrnjpYtfUFi/+U6mVbD8CZdsQgoRtVjYr2YDhCLVLp8ZhlZwmXi4tnUZ7f1DJH17Gpi69xqV8f9zJjVPE6WBDKXeg25zP2zrtbz8opGfn2VQ2PALgmyEFD/VXq9c2G4YAolsf4wKp/sj8xLVQG8WU9LRwBWmfFcZ3d20xDBnOB0ruPAX4Gvd9NsN/xjMPh/W6NrIduJCJoRB4n/WiXa42z4STLgvF35QQg2i2z9t9mg+FuvneXZPD/VhJFqqtP0MeXERryAxreXqUHCLpOdWUPiaNuCXOzzoo5K0QCAADPcABSCP0H0uyYldCEuY0+0cdSsC8k5HzQi6qknuBk682Aif8VfSUcPKrdvjvHprXNFaMVd2vNiyTaz24MnpBNWcdGfVc88Ksy9RnojII4KJ2wrcKvm+wKz1XigfJYdnBgRsk95KruYAYgaCqr6o1J50l8oMUBvlGljrlws8IQ0cQyT0mb/7UJL0jNMF4KNI3mnOzkQxpN8tKEWmM9t6VwLfyj4lLe8ogLGHwvURmtGtqq3Uw71Hk+gX92asNOPiv4qWiq/e6gOCMwH7zmEftxVk+bAX/k0zvjSin2I3+sb26Ezbxazunf2OHlAD3kHfRp655HkxwwbB3Y2/i1+/GKG8EZt14cw6RKCn633ju0E62bCgxPOxpQKpYdFb6lgXox+0lN9hJk/oAcPdrMVOLB75/7uc0CmRd08KFoyfQP1D6YESMa6/rKpZ4Oql/zu1S35YcZ3qfbTMcuvyKLW+2P0K4V5UKH/gUNqbaFldKj/W4XVz6F7CmugwmY8yNTZ8XQomY5XQyEE74KxHdzDEhQa2pSAYsNFVWaEDvKtW38DTk60TtIIzGj1KCn0XX29q0LePk8LjfsRGALInjgq4c1dGPrpasmSuNQtL0GE+TDC4Ymx27frp5rP4ZX01Or5iBZ99V/m8FebnLl8aGQr8566dHcUxmF0dxUGHnoMlGkkzP58NQhvCl3EF3jKUb/TobCjWoAqeVgBXavuWQVywuuf3CcamboUz05DS7bOmx/kYkxOW/lLMY0Zj3hHniEeZtOt6fWmaslrDNf9ykBYciWgDl1xAUjIG4V7HuuHhgUfPjhZL14QqMf3r/P/6/z+uuAHF+LLO7WO0g2TmaMPhhyt3aRiXB/ULrRYOnwd8GA8N+Qjm3fRUM/7Eh8pDIW3VPIx47xF7q/OXJ+awFrxSxPBZZoHNdVNxDHjn8ytdsnuIQ1YFzFAaqfNwntR4AYmmjgUsiHGjHwyGwCxKz9v51bfRks40cPanGYDQKtiicgVt4cVOalEaIV7TrpHNZuVqYNXy9pNXcHgTahCInyV/+Y0DRitDgVGa0GBKg+mlTV5UyCfD5cLk4EGD/hOfhj0tXTAZE8GKijkowLdOls84kg7/OLKg2WgrW4yUGr/dD9XSVpAUm+cnG6dbbLY75lFoEfOlJE0M+OF0GPM0lYYzCDPbskAEDZlNQA3Cqaa+iU5o+ClJtddiVvfg6prrovFKXMPSK2P7SoNs/i4fQRMrY8SaA09vucku28kXsJ8Mf+AaY66+PCbOgilZTG3HpZ0nYw8q6fEPCUIm7HMd5l4H51oB12rb9/0CPRZ14a8w2nTuIA9Jk0UGiqiC2jZtbLfSOrNQSdTk95I0otl8mAscZDyA4nV8D1BbYg6zoeOrUkJzzAjCC/Oh35xIGNixi1t5ZC5XT6FKSlz4MJZHrX5r6Hjk4UzYbNiQPG6P9ITBYR9tkHheQeaeTtTKlwUHGyqQBSeVeSr6rlNM3oLuJCB5v9+oyY/yxYxSZJIiQENcU+++l1hULH3iKhjBh+GCGchc8iOdGo7RIJ/SiZZ8q+0sVD26UMPeigWY7IVpsNcH1t9cQ24rwfIJ69/HVroi764lpESSq6PrN85vwal3JqNJAOISEJggUxIJr/8skoRx0HivxoOkmuAtBq5J1/e/hb/dGjh3Di37F73IUks4Z8Yzml1RDD49Ay4XWzoEt4r9LbtwWgWw267puSu5jEEeRcFwHtMAbzl/dZVtxaXxdRRBNGNRahcfXR1aa+OW4XUIotXfL9s1myo5ClNTCSm7Uysvw+Yw1mInQkcfVZIdFB/GBRIzo6eN586+qHZkiq5+mMQBJMDufSjuM/vlQD44xvCp5KRPeQ5fS6Y73TdiKHJjZaweZJegm5H/HUcS/FIGBZGPBLJsKvtNmxzSjK5eUOXp3TysOQY+absfW3ovZ/B2PqWzOYmT+mh/3icOSXNmDrlAk8B+qExYNnMYuBk2bNCn2w+01GOpSK09q0Zfw74HPaNjWyVW5IB2MVZwTxSKWSFgJNeMKsfvqlUeRPy/U+sbuHzKydJz4JZD+v1I48v0FqGmsZB8QDoZZ6jFfXJiqSnZnx/JMKotc8u9QEFXv4VtoOT+zxADNIVm5LemiUeO3ma7V+HQm4TAadHHs23iTfTK3C2AQ3Jvw0xGIw29bbg63CnFNg1sZkeXCudxOCf3sQxIB4ayL1cqQoCjxTkr+KyvBSS5Q+vUFGOjmtw0pyXeN0K7ETtoH3sapBqpL86FlLSUiwCxRK5Z7ipe4xZzJXV8tIjhdgPTIh6tqmuhY1kIe8zxfdEIiVMHvjvA/a7i0dl89LnFFrgazReaDlf7vVW/Z1jJRn3QBFOU7p/ubde1Ik6koGyxYfWx32CqhydNLtIl7F/T1Kf9KgyYGLbEKQPw4ndhv8bBQtnc058jR2BmtiegRkxerHs4uwasZ6/87LKpDb1PNzLtjQRG51y3CEdBYWp1G8L+Nw3A9c944EZorOdofp3OBiJXAxCAFhIlbDitkLcGu2+cDvfi75TuIxy92g+aCO9inZd2F5B4oLCxgm/rZzcpC+1ti23WgUXd91vx4ZiFih60Bi/b0gElLsDqnUlTHPuzyvLhUK7y48JXZ06XKSvoRklVs1AG4fTJwg0rV9t+sqbKw/ZeoGp5fnKezdoj9SvZUT5bZscbD7MDA7/cov0ufBoQ8ucSK+FPj8sKfSZtHtTts6CV4qnoePPtiaQZ83Ej4NLGl8LY2jh33OITRr4NjT5qDISPb90oRZaAK/OgSFBEuuBIBbjXSSL7m6v1WFDrWWrUOjno5Spz3infaM6H4Q28zqFGJm/R24T3ilw1Lej6ow3kGEt4BBUX/0tusSSdHWtqBXT+we23vknBFX6PhTDOda9sN1dr9S2MkXsY9QJbUM6gzAbcw/PAw5CCMGuQtfBb6buctxWWkLnGt5gMmwejhz5XP7zC6GzttLGtNkTAhZ+2DVkAIlaux3AnDNjWlcCgk+o0AuGV9XdJ3iV2w1kOMjm78G5tX5Lh0WrzrP28RLr5Sde00n1sSSMXQfeGsQQzD/rlh8XFlwcLvzOuX7jnoYBxPRTKq5gqBQNINOY92KGT3eygpqJ8y4Mjgpwz7joulFN9znUheXJckLd030KXm6D0sWF20xziCIHKw43FiP9crYwQiM03mTobWNmoQgEk1OQvlWfxLqIfDL+GofQLjwjzAQDf777hSNQL8/tAYWUicwH6oKemR62LRadUGq05VRwRQ4qqO0ZHrabXDCkmsz3GBT2cag0i9qfo5f4z9t9qBXUMmNo5DIrWtuDxWvpEWFey4c2vYOHz61ynIMfuVU6Ht39dA4OWH1hNXT33AplZLgCXo++Wa4qBmbz1bRen/wC0qXr9PIPyJK7ZW+U8a1dOarheMQdIv2aNV6DbOKMfkeHRRrV3XnfM+7xRVpVbVF9E8Drfj1wpGyGE5B7uehPBvcrSQYO8CmZMQcE5iAXXlgJBizFLUS18my0VAW+vQ7OqseDp5RBKd2y53QwNEciBNsmEV7+j3IfsWw5smK9wWJ+RD9dkHwrwlqSHALH7Nw2nZhbXQ+9WPe1ptYmScNKBx+BUYqiZ1QNZIv4ry7J4ANY3Fh0ihKeHJ40Z8/OAA2PrymN8e6ISCAy4zQ4z7C5cThaSeCJ0QuUd8EyL4jbiZ9jFeBWhS9EICOmwj0iNMBk1metNr3PrSk9n37BMycfxz3F28OeA/+7wWGN10C9iP3Jbly4uW7D5+mtwlNarGPiT1hywy4C00RAIn5cT6+rE/CtOYEYDgzHANwL7gMLg0fA0n+jObMqou/kjiAIl1bE8iT1FP6CDyDR3KJeI7BZnJIzphAO84HAf71Yt5TSfP0oFuwEfsdKk0UIiN2uov9OkBPhv+Gw8ZB8/ffDcTfENhg36K3JtEnG8daiMdh/rsBERcT7WPihkYzhARvPWJmGsZsiciPYixi/468RZGC7gXmvLUhCRA9VNyytub4Qm/9TijX0qCSclhV7/6B/GU8eu4CAGZ8oApuVYBh7JhyXFX+RePFKDoHTQOSITY09hZOMFQW+AlOyMr3BJcP/jGUDbm35BTyKENzpwjsLiUcnXDNtmGzYbIDA4uBARd4vuP3YwVhd89ak2C4R9eHJ4VGKVNpklDjS4ChFmS8kzx6FFtXjBOLUKsppkwKIIcTj2Bfhrqykb7C3wj2thz5MY7kpyr2gaSceJmiKIGEljMG5U6SdjvQKIQbiduNS4vwIP1Ck9qT/8ijhEQKdsWDGmxRrtwOcjvNrfxxwIZT0K6T3Zy6WuREREvcwAvkI4kJJhuW5+pyR5PEHrHyfcOoNM2uKM8n8TM/Jt7iTX320+PK1Ipw3hK1rm+sP+87J/mAbgFPBPeAJRbIveAkETyOkWEkWL1ZeWHFPY4s9EsLSwiZ/dAMeUMT3BDwmT3j0M1wAZCv3yAoLhiOuKK19h1lE0b+QruI9kZXDyVZ8Ss8ljFWCT0JEL4ybgBVxUHBaoJ5641QeXI7DnppzOuorLG6h4Xf1Dt+ONn0OmHMVP1ripSxpm7YfHU5E/4K3fdOBSpi3mr/4tTINZ90Tk4Qv6SFTPW2hXc4pFqvQG0jLRXdlJwZaEHwqDV0zm8NRx35vTfsGhy8cD+wD+iyPE0oEIIGQAukXCbtxXkRUh6tFiIOrw/XCadNlY7zBHGA0mHkj9eF152ugm47gi2C2Fm9glMKTuqMMIDwm6MWHYAGfBrB4yr0g1A/niwhlxbqj7JYm/YAPgPOd0QY8XiQGki3iQR654kngGFhT0uI/BUuDnxaRBiAyN6jO5KxZPAkaKBbJXLH4rSmHsQitOT3pPbHPIKkNqWBkeAi4FqwB9rfG/45l9MjJmsqT+ox9I2CjIwxrPXwoIjpcDpz4v6MM4djTeDX4k9iaOMsRDmERrRFD4dERPeATsOaGHNhekeD24aZErLHOhgqV5MO59zUv8JnlP0G7IszCmcD+G0HWT2nxbiMMwCIbuBtnFI4MASR/Iz/Gl3+Im98aZ5rcHDcPp5vS+NHducNzYiDTIjGE7Bjb/dEalrEi3T6BIJbhI7UIinCOBnKCCBYsKwIEdhu2ZMr6VVqWg14DhRx4H6kckN4sa/YNR55Ifanz0f04heLxP3svzog2/rWmbac6N/MMY2lguKY/kzoTexx9aozl+3DHkmwwylOZmdPQtTk+6N//hyPUDriNwvnP3K3VD9PmpmzkH04ysCZuYGonXCQGEAFI+7Vh/z6kH8ZNKXA4zyfJRz3gqKaT2E5/TZOFJS/XWmc/l06Zmhy/ie/21QyJ3f61pu+Gokspl7A/b7wnnctjNrzEb2rcHLeWl52eckG5MqSLS5BV+ZXYZOgPEtX2vHaCkHI/MRx1bweVmVXLbLKP9U87T4qpjngv6R/5BdxQzjqkMXQul+iPybQsjbgczL3WGMh73R5tqnPprmew5Ei8+o5e9qa92NBQj2qAnzaEdHWms1wg/YqlYkFAz6j6+cpAoRqFOGDoe61lmft79dnwURYXv1FKki72eYdMTRF/A7U2G83nhiyOBoMxrQvND7VImumaSMsh7c9I/jIGv7eyXW14AqX05ZWGgZI6/Gb2TO4ssdvo0U9xnVOAOkdn6mQbhpULWzHvz4Yt+tOGDxLcQWeZZqm4noAJfuMWQyOzQSWn3+rzRjU3y+Ince+PZQF+2lQHyWePE2nt1rem8iJcbUTF94do7Fz87CjVBwM4BeyKh0/ThJ0MjATSt2irKfKZyUI19/o84/49RusHv+RLrEh4PWfrynEuVash4l84LquP57edEKL8OThwH+6vkYeoH/lS1Nun+9otJ0agqctNJtCKbLCpX7BKW8ChXJWqTKa8Sa37IjUb22AI/pWbTTeq6EcIfy0vp1qu/nRbSnpTuWNUPkm/vlxJkbs+q4DSkmXz7/AXL8oj6g5LnU1FNMTAiyqVf7QtxJVGIdCvX/4d0E8Xwf104hI3YN7ESdMkMqAb03zA26TQTGarn9apsa9nKV86l1Kp+b0fTf47IJbIp9xeca3cRIVhz87u35aVGyUznd/8w4HMT2urcUqMlJYXlf/tlJJkfccgvpVn8K6eWvdIy8teyciHh1tAwL6R1tr/pUt9lXoVj345m0SyxLco2uCi2qIFHcIFhWMrk8+3c2lHljx4rTVhJp93xd4p4Clov/rNptD3E6lDnBJHcCDt0daqqe1oNNo78emYwKW9UNULy1zrbtcHi4Lo5H5QlmypSpTs/ZvRVxrCFu7H6ZQl1WI+O/yAH1Gl3UU2viRs/pfji0ZyF5s6BDUqw28SCz48gZVJcH8DjRXwdIoYOqynhjz5se/w++6t4dhNjiHVrNHu8vwclM6Mq4UdBdLlUk5EKrKnixjZ1yzO1EoeUhH5iku4476dToXoxlyqLH8ie/wNALVpATTofCLXsTr4qnXPbdKpM/uy8P3RYnCOH79s9ApdXewS3l2HmehRBmvi6ri03f7joBx06fTv3+zBBW1/pq/ybA12/unOPxLyK977nRhmN6Qj/wkzUP7CyUZKhSHDFGpq3+Fw+Wkg5SWieu/pMMbMQ0tU79hJdnzMXPCqS/RqEbp80Vk1v6gGFh7gN8CVbtPpZe90da0Kfr8NiIN5qCdUlb+wjUFprDTYm5Iqq/RQa/ggNsPrDjXezyZc3RxL+J0aZcVyDre7FfWSBV58Xu9TGcjKArNeORvQtk+1kvGaMkWpOWuML3O6RVL/wXDpT5RbTKj2aMznhxYup2TP5H2VS4x2tfCrSJOWvXNzX2j/tUVnMhjqhNSb3Olcod+1A7XMBuoMrr0VyWobbb2/zhd9Oiv+xtzspTh3c5W2cx4/wmLYMwoqKCv3Csu9S+FlizJ3m/2Rk1+zsER5jrTUy1LW5cfc1RLj7pcNNlX+OSPSudu+RvvS2aPCiKDD34rlyQVaik6OL2rzirHYREvO770tlOTAwwyvUvcLmsfffx068Hn7ieqsjCuh9KdDWLlMZfbrdMrs70+KUbS/n2SAe0dUXiU8tSOHa5tGzbwoX5qozVuVnttRMhAg1AWnMv10ydKuf1G1Jj26uE7YUTVP+jipd22LkDh/Za/tpCEDbiYyN/iJ1v2rtsoxIFdtRl2IJkN93uDdr3/JpUPoDdU16AbS3h+JRKKz1+CGXtxZPRFfc6X0qyu5nCQvA/klvmvSpjoXmrq98BfQyfJIiJt+T1k8xB/zNQ/UxWk2kLD9W1lifyJi5AO2WvGps0lpXZse05jw8aAnM0g+Q/Rw/j3pBEJ3yZl5+7amhuqnI+227tvLjSfL5RRobbVt/7GGx9m8Vwux1vF2Gw2tXqbaTdIZUP2llozYpLx/nbNqN+ADz8UPS5lGUIczNYR4mh8KNWod1YWHZmn3eOl4dlZjZfJ749ljLJZHhwh7GHZknLP/XGcx7NM6teZVJXWlmasfHP1x6vuCI7DUuX/QYLjw+m3zTQ3bgiYV4bFExvyh+ACvAcQ0qZ+oXLf26Psv+2fBqUWW9iajunF1yGq9jHdsd4fdJcHK5l/dyqReCqBe8lsJS5C6VlXt5um4FPnE2zZ1CuIEsqQDMt81DjEtKwOzy2KxL9rx0N3Ug/KKjex29X1ltpkMdqhgxEUkU/K55JxwrWZdWt0fpwI=
*/