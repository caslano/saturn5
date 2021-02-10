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
F/1hj+rNyZMGvC80GvKsgS8KwTGrHP64y/On0ejSvwji0Tjqj4YhnMBMaeRzCVIZm3GZehRVWGBKVQFVUiQyFWWG1Cg2N0Bhbrgm1ohqjYJZ6iXH4/6BVUVsdJpx3XQ6hLSWJSUXmZO2nB61b0nE2Zw6iPI2NXbVrpCgUHLu9Bz7giea6RUhJchJTJ2mUVqxAodpq0gsGse8K4ZBplNX1gRdXs8hHqdhUY1loYzhCeEwoZFlhEellMYyIZ7GyawIebGu+lZ2nZoVqj45cj7cDPxsqIbUPZKJR95c35iXTHTI5KX1HCVq5rIhWTVWcarkjM/beQX0Ig6Hsg3xaGjQlgXZOYpU1V+NRGmt7jBrvBoVkWjqsLg8tBoR0kMn3YrOCdZWrwX2r0CvkOTxGUzDIA4uz4JeL+jF/iQIPf8y7o7Hnwf+uWvXw/73C1HvZG97R9fq27zDLvXn9MJu9X/w91/RnbKHwuD/naOHkrawm/yxxiXNFwz6ZyHMNC3P9dyV7sRxtaT5oBaTt2AZLWxrvErzhKp/NvCHF7EfxW7BRP3LoFkVtDei7RkP/aj/NYivaN2NrrZr+gsl3OtOJ4M4jEirS4BP8VyyW6w2L3EAhVZLTmceSKTVkdELyd1RZbyaoefqnhf8EU38uNcP
*/