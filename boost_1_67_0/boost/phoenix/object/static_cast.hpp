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