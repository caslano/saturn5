/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_STATIC_CAST_HPP
#define BOOST_PHOENIX_OBJECT_STATIC_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(static_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct static_cast_eval
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
            return static_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::static_cast_, Dummy>
        : call<static_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::static_cast_<detail::target<T>, U>::type const
    static_cast_(U const& u)
    {
        return
            expression::
                static_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* static_cast.hpp
3qwqzZgvU/HwHiUY1dqrMNLonkvx5I3oan7QZOZqAaoJNDdql+6hICqXuj9o9YjnxGvxsmacbFsxSdxrXNaQkVejAqUeOMwT2+WmLjx94O+Cqms6BVoonXv5+vWPTTyJtPJT3RfX65IZGj2x/PgWZrQYvIhK2Rl9zM3LMQ3MTXcoKzxFVdy7ciHmn2qndYLgX3Y1fcg7NE2T5WSCu9K5th3d1rBh59LsMIBfB2pQR9kd7mkadrEhcCC3THArghqQAYvuOVuIhyf0djjts2UG2VhT0tAYYTzLZOESlFr1crXEAYs4qkEngSis6YDQCpX+aWoYLfGjZTqgNfD9jyV+xKwo6DjFl8ZLYLI+aTxKV53jsYanU/KrkoyLlXOb4UXlaolpeV92mnqRgvAWDzvREafYDRIggF4whYTWBTkeeVJjFBP2u7mVMh81c1mlJb20pCWrVJlasJwie4iyyxRkuQd41uXC9D6SVcAj7bgXtLTiwCplibLIIlqtdEWJslVQ9o2UZ/lBy1rHcnKTY9K69FyHO5l0eb93XM9RGojFT7bIGB/+EnlsL+clKdOHKD0cyhOj03R6rSBNOmagwAKtiDbU5ZTcWsVeQEJHHZdgVarSZ+KL0uC1/d5WJrOKUzDRjZkDHnSB6AVWYRt/
*/