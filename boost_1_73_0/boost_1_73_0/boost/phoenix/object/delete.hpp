/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_DELETE_HPP
#define BOOST_PHOENIX_OBJECT_DELETE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(delete_)
  , (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct delete_eval
    {
        typedef void result_type;

        template <typename P, typename Context>
        result_type
        operator()(P const& p, Context const &ctx) const
        {
            delete boost::phoenix::eval(p, ctx);
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::delete_, Dummy>
        : call<delete_eval>
    {};

    template <typename P>
    inline
    typename expression::delete_<P>::type const
    delete_(P const& p)
    {
        return expression::delete_<P>::make(p);
    }

}}

#endif

/* delete.hpp
fZ9gbSy046PbYQWnUWtGgncfxTvmmjZrEmO0KvaGoO2raIcx2pW8XLUvp/vRIxwXsRfH6xp8B0dWNrXxW+01iBwR84FhoTmL5P1coo0c4HqMqdv6xHzmwgzzUxsS6cwlmj1mD3Mt11X0XqJfCM+zJqzfA+Th9bXyRNc0yBe15iZuTDSOyTsEoq/qO3HibiS/K90klninUd+fjLq32lSV2Sxm7kWIO8/6Lkc6g7/F4C0Z/FUGP1bBT6Xq4DjbJes=
*/