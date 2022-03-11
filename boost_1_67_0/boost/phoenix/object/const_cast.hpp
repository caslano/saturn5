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
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
*/