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
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
*/