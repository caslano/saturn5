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
MsrV8WLiKhLa2rjTshJ61BnZ4uLF7mWuDTkWmZ+RtUZLeLG7f3D5Spdoo6hKv77KpIVZdfxL/+x8cDIU+8UK7aiNP4K4k7AvAzThLXGdJG7ktcigkxzWdez9Jl4Ua8/656cnw/O+HjePRl1rBglWF9BQrkTFyGf9/zn6eMzIQtGwfzSqaEXqwZKiYn3v+PhMWGJZrFeQz/qnomNEukrK+AuQ3JZ31v6gWygYeFPUQK+qdAQDKnRgbF4Zha+s6OD0lwMN4yqECAaYYuxFNwfQ9V3vwzmMoLRRxUDQbuwFqEJAFSGb1WohpX5slfvKEOMm9KYcJOkAycGi5gbqHZj6Irl2GmfFIKrRJLaluba17nlTYBCrSS7YeVPFtpWNIUypaNz7zWpc0AVZ+wLzVnRR3nGpBw+U64Dqwm6IvGs1yPRG1ihjPauhWgqLu7ESGHIS3TuqDfJxy2bwZrkNao8WR1eNimqtSlpZ8ITNvm6UOIR4CY0GWGqHGYtsNq+/aeaHwTWqMcAdRkrDpe9Qs5YYfvrwoSW6HcIilukyDqjhM9G5m80qx2SupJ//mVHz4xKHgxvItLG4m7yI5zNcs1kYycDJZLcl3p2c9oew0r3jUf+3kRrHlhIq8mbOLGqSjVZa/Go5m4Fm3+/ukmbP
*/