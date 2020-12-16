/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_CALL_HPP
#define BOOST_PHOENIX_CORE_CALL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/transform/impl.hpp>

#ifndef BOOST_PHOENIX_NO_VARIADIC_CALL
#   include <boost/phoenix/core/detail/index_sequence.hpp>
#endif

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <
            typename Fun
          , typename Expr
          , typename State
          , typename Data
          , long Arity = proto::arity_of<Expr>::value
        >
        struct call_impl;

        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 0>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;

            typedef
                typename boost::result_of<
                    Fun(Expr, context_type)
                >::type
                result_type;

            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return Fun()(e, boost::phoenix::context(s, d));
            }
        };

#ifdef BOOST_PHOENIX_NO_VARIADIC_CALL
        #include <boost/phoenix/core/detail/cpp03/call.hpp>
#else
        template <typename Fun, typename Expr, typename State, typename Data
                , typename Indices>
        struct call_impl_;

        template <typename Fun, typename Expr, typename State, typename Data
                , std::size_t... Indices>
        struct call_impl_<Fun, Expr, State, Data, index_sequence<Indices...> >
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            template <std::size_t Index>
            struct result_of_expr
            {
                typedef
                    typename proto::result_of::child_c<Expr, Index>::type
                    type;
            };
            typedef
                typename boost::result_of<
                    Fun(
                        typename result_of_expr<Indices>::type...
                      , context_type
                    )
                >::type
                result_type;
            result_type operator()(
                typename call_impl_::expr_param e
              , typename call_impl_::state_param s
              , typename call_impl_::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c<Indices>(e)...
                      , boost::phoenix::context(s, d)
                    );
            }
        };

        template <typename Fun, typename Expr, typename State, typename Data, long Arity>
        struct call_impl
            : call_impl_<Fun, Expr, State, Data, typename make_index_sequence<Arity>::type>
        {
        };
#endif
    }

    template <typename Fun, typename Dummy = void>
    struct call
        : proto::transform<call<Fun> >
    {
        template <typename Expr, typename State, typename Data>
        struct impl
            : detail::call_impl<Fun, Expr, State, Data>
        {};
    };
}

    namespace proto
    {
        template <typename Fun, typename Dummy>
        struct is_callable<phoenix::call<Fun, Dummy> > : mpl::true_ {};
    }
}

#endif

/* call.hpp
ZFjZMRgfWAnalnae/RzjA2tBrGGdsNFY1mB5zQfFD9o6uj//4FlsE2BdDWTM6vvDbmyDJ7XXfusngXJcOqW9F60zVM7BMsEyiPmH1f0Ky/O09pqTumu9/N3ZGXjeQez2xYeXsR+B0byUSd5dDtPBZujxxMbP27EL6xbMIC1nz2Fsu2C0H7kX6iWf2+vMLXPzDizPs3lfc7zB6NytR2wPud4KRseso81Lzse8gOVVR5lgNC8bB34eiHk5l/e9rzcYvXYELYpMw/YJRttZsdbx8n1hMHq+DXO7yd+LUtP9VigRLK8YknX5NC0YY8XYdccscnHneIwdjI5Llk0jVmL7PK+Nwef52sXYznR2PrJSNJbLBe086+qlQhkYHxjNZ+2DB+UaNRi937wYGSfXTS9qy3r6yi/lXjRgeZWLBawCsZUZcu5tY9IlgtEyq1px9yIsa7BT9P4hdtlJtEuwRk3HrB4v2uAxL2vvRb+O+3oSljXYQWIFnlSW84mMvNfrMsG86f3t48l4THFFO0Z+dnbzTqwjsKPEvpsywYJ21SDCif3cxR+vOTawTDruFo4oj/H9qK33QUEX5G+owDoSq9VnMbaX6GsGsZpeiw+PwTm0+To8K5CmeVZgARtM629jL5zPp4HROmp0t+YBtBuw5khsVaveEzD2nwyiO7ERPs/lvROYOxnLA6OWnsA6yjSI10ZyfQjy64F2Rz4jAtO+68dYNmPil7zNmzETY2bGLIxZGYtmzMZYAmOJjCUxlsxYGmPpjGUyls2YuMvUH2MmxsyMWRizMhbNmI2xBMYSGUtiLJmxNMbSGctkLBuMPhsMmt9bPt+8px0je5wtNwVjv6edgz1QTsvfcDCWeU+7Xpd1L0buXXRfOx88cOvgNSwzsPJ03XtiwVsYu90MZC1h5kZ8bmh5qL3GLVhavgfWOxidsy+dd86G5wOrRsfPI97F8HxgiTS+uLazsN6ztGW20jDvAZY1mIXOwbZ9Oxzz+at23bTJ5cP3MR0Yfda66Lr7AKyHRwYxkc4/O7fCeYjpN1jzINbiZtWO2K7B8rrmJICNoM+yMoY3xjrKhncZ6Xzp3JcyHdgU+oz2oxedMC+w819bYjefNhqJ6cCiDWSuOPJdef17aoBvYEibeb3VYjT4uJmR3r/77sPfI1jBaLsu8k2h1ng+sHO0TURMlf0WfrA1j+Ql6uP2LTDdn9oyk7+bgHRgdJ1h1Pju8j1OMNofpj9b2BXL8y/5vKqYfT64ayCuD5rBShMb/se5jzE+XboqWdvlujeYqzTtmMVYIthHBmkLawdORHsOa+Ik3Tfnw/7EY76A3y0p0qaU+KME5vO1fIcHDH57dW0g9qPX8vdORe1rch4vfsb28gbeDSU2L/S6/P0mWJBB2oj2acMxnUGBeZa0AlEXT2E/Aosk1m977wtYZoqiOeZbu06vx3RGRcSTdIHuK6di7C6KiCA2pcenjzAdmI80TR15uyqiEDnfws6b5G9+3BThQux6htzHLNldESWN0u5G3ayFdVRQ0ZTnaVvKG2yDYLQ8f1r15gGeD148b0TOd+O9tEkYQyEFfvsv7VHpYSUxL4W15fnicKQvtt0i2mP6znuGY3matyJGknSHfvsbn9tbiyqiM7E93SecwXRgsjy1fSUTzJ2cz/+Y/H2O2UcRH5N039ya2w/jAztELHRyy4ZoxRUxnljm0L9PYVmXUGD9WlrPq1seY7mA1SB5mTF/4QvMSykFvuUjreT0Dfic0lZaEZdJOs8u6Ycx9rIK7pfgDVY0eJ47zrPKQezStO+Cg3lI0+4LB1aF2LC/XsnfIzCWAOZHrOc8NwvGzlgm2FSDtOO3ukVgfBUUMY4=
*/