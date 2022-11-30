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
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
*/