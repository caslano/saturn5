/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_CONST_CAST_HPP
#define BOOST_PHOENIX_OBJECT_CONST_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(const_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct const_cast_eval
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
                const_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::const_cast_, Dummy>
        : call<const_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::const_cast_<detail::target<T>, U>::type const
    const_cast_(U const& u)
    {
        return
            expression::
                const_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* const_cast.hpp
M3fpE+spVOlPWKQrCW1ScQu0Ryjb27oncpP5hljplT+T7hSgLBbQIhGzGOb5bvChLxwNB7rBIDPvWuFi2kJpGoe+mIe3MDzJFSCCA8EUYc0lYaVwTYR0J3M1RZvIbaNncAyW+s/y/jaMp8mhqmvApBNcjYtguQBVcyj2LxughpBIHozE1AO8loE3cWndWCpZE6jebQIVLGQ6D6fJeOFZ8LoED8FAsbdYLgTXzMTwYx8Y/fjcWiGxAH5YayOS1E1lYUj3LhvyxX9ySJh7LC5QhINrMw4VBu4CyeIySNBiKSyL480EI4lrt9skGJGbJLgMJTim4kFgNAdeoOAQDJinjGGhfEGyhKJCGmJm+DzH2DYUkidNwg5BQ16i4rr+bdEBrFzQn0CAjdUUtMVQJJGceDPQWAyfR2UuUrM0i8mo6DFVLWABE4tCQAgF6XDF+nWQLKBAliy3NZ8utHp/ft47HQgnCFORLCPETE6bKzrtQida+S2zcDQFRg1kRE3CLO8UZr2AxeFiexao4vQk60c8Pzn6+/k+0ASZ4OTvLS7YOxQvqST8zFK9Q3oYrAlbmCScfAbhT9sTqvrBm4HmED/3fumPzwfvh70P459tZe5dB+BYgDL/Adbbm+XaD/ujAfw3HgxzfQKZevDfjhes
*/