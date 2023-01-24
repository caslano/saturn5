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
fa28hUxq6pVwneCvgYmfA3fRHc0KvXoVDFLgixUK87KyfwlYDKnIVEmoCmYaOraxGa3TBwTZbwZ4THFfCD2wSOi9WdzH7nCo7eBe+79sK9Th8qhQXOF6/Kr8cX9cRHF+QGsZTFyz2L3SLXS5+5jSNwoE50x4Y5PvGneLAFNiL6QWvN0UO8HhFcDpznN0L/aQCqe/3ebpy5EuaUA1Wa/FALhMesfBnAZwz1GduIG1BZ/oggvYEgP0owNbQVP7wNzKODgo9oGYFtHxKJhLXcj6+dUFdDYt9MlCx4mBmKRo8Dcqd02k9Vjghhml0M4Jpqxx43DQZPOSyjYAdBeD9hppN7auo73J4SU14n4teP9OJzg5afoqTiRlcg3bm5dxXLULgp95RubWZQx9MO6qi8t/maU30edwiwmkOXiF0y1psUgZP/Doi8iDeHCEONgqbleKwPZU3Qkp2OamV5kONDuqBDYtcLqYcnQWjUMxLtnoTLm+yy0KRzkM8wVgeJzh9vlt4Bq9MML5wZ3aPB4mL3QEcwM4PRb3hmmwn80zkUPcIsUg25ySJQhedPcCw3AOp2CwZvYJTPpSm9MvooEbQeJ+uoxKO84YpssDGSuw03i3f4EfUnlh1tOsWrn4yn1ByxukNPSmiBN+p63VLcAawO4L1dOC1x1iPxDbaq9oqR57xUtraLYBoKByKHBe55UZ+un9ISpqcAlVW7mDSxB6
*/