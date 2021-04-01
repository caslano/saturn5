/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP
#define BOOST_PHOENIX_OBJECT_REINTERPRET_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(reinterpret_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct reinterpret_cast_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Target, typename Source, typename Context>
        struct result<This(Target, Source, Context)>
            : detail::result_of::target<Target>
        {};

        template <typename Target, typename Source, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Source const& u, Context const& ctx) const
        {
            return
                reinterpret_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::reinterpret_cast_, Dummy>
        : call<reinterpret_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::reinterpret_cast_<detail::target<T>, U>::type const
    reinterpret_cast_(U const& u)
    {
        return
            expression::
                reinterpret_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* reinterpret_cast.hpp
gddrWApMv0hbjO3QMgybU7pBDDrA2ZR8fTKtALp4JOvc2D1TDLvG9bKsWUAG6nRiuMTJoPBZ0PeEUasmGACt4+o6AB8bVadcyN3muAJcT9bJ/rgjAXP3ySaC/QXLmT6/qOO3fj9apd02sQSxcggwGRREwgLHBfu3GMKMZtghKkbt7avNQVfagYwUDhdYv3maqizYawS3pUnixbG3AxDNWnJyd74H+jiybLYmb5WoQgJYiaaZl5v2tILZWyeKMz9tu4IEYmhZDv8hpWtQ9QaSwyn8Dexc8WN3Pmqw0occwxbm0sZ0cdsglSC6UO2ZkYkBTOaSsM8oIZXHF0TzN6NpqIPZeTu9OxLxPXj/MOiviKycoL/J5zE9MiU/97JW5SO0l+znmK79EI/EQwLk9VgF2mlCDM3hn85nL3IQD7DX89VaLwnF4TV+jvTBTcY1EaThoRsiO7c+i5lYMqJ2ZEHeqcPzyqvb9NOMyS2yqwUjL9Uq9IpfJi3JtOdLRPWkKiV6FrTxbTDm701pQLAZTti3bAsbuAifxLOGFW9gTr1XFHOTm+Uq7UWRoC8QZw==
*/