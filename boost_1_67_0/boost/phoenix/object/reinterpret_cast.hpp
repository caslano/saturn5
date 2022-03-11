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