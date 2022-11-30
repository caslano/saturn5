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
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
*/