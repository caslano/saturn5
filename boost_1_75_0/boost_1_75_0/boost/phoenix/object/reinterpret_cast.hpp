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
IWszd2NjVwN9knW6r41FcWpkV1g3lWc1lmdRrOvLsmhXfuwYa4i7Fs9AK22ulTjm+jDrWE8kD5a40WOXLgroomEacyRuxw7iVAkddkXNme0SU0YPlDst15c8BNPphDPHrK20nqPrdZrjTdhAyPa3tQGsCyBry8KUiC6ybqoATptw443oWhWdZt1aS8w9a6OW0g7WXqQ8m+Noop8AdNunAjrI2KkxGn1cBl06q29iR6u3WDL6oQC3vwkDN6v76W3AHbhZOXnH7dpM/ZGtjp6/jTW8WKc5HGWDVNzfzhazBmOuguTw+uIUjLuhlCWSeFk6UyBYw3jdiFmXZ9XDwA1xExva0y8HxtoKr5qI1y01dNxU1RSyBm78JV6CTbFuxKyF7WId5w2FrRtS9hIJnwCE0DGAHu0u8urYuqNdiIIMNnAiRWcauChPw70S0p9TfTEWbm96Pc2ANQqTOARrt2njMZeNDgzQPmirLg+4D6phgJ1dRmxsIcE6TNgdrHFa3nXWLQTriq6ybkMi3JA1aeOkS49ypQ3QKOt2IiM407RZ1s2Y2UKbpsgxbclAgml30rqxDydYW5qjbTZNEWv7jNg4inW32DUehf3bWccjQdw0P498Ow23m6j8EuXCqrJC3KH2tBK6NYmbZdoi6ybzNFYjjO7JAWs97iStY6wf2+jow2suW1vhbXXdjYyQXZOskzBrEjdL9MBdxgzciDXG
*/