/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DYNAMIC_CAST_HPP
#define BOOST_PHOENIX_OBJECT_DYNAMIC_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(dynamic_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)
    
namespace boost { namespace phoenix
{
    struct dynamic_cast_eval
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
                dynamic_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::dynamic_cast_, Dummy>
        : call<dynamic_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::dynamic_cast_<detail::target<T>, U>::type const
    dynamic_cast_(U const& u)
    {
        return
            expression::
                dynamic_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* dynamic_cast.hpp
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
*/