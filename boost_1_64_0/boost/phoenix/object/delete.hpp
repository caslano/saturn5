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
AvvBX76bduiSb36pekTAbjm+cEv58TApAsrpkH6DQQJ0ijYvvrpfHVaII8RZgeWIghd7+tLChCAojcF84vBcY/mVaD0d6ph5kbYuofoXjfiJXnGTCWwJ5TinS8QR4aU0c7hORUFqOEKGLOdFre9c3qjRxHi6yfP9K6bm0eeO58zEsADJhKfnScEtjgy1UoboMcqnZwrVu/gWBeGgHm4JN35UuqY1fmbrB6iDYETpoIr95E+frLx/p5Eu6Qxb1Enjjc0vcxED9FfMseQson5tmpkOyaPrR+iZJes/v/P0v9wB+ZOJPsV2qo3KkfWv76ZwUMOD7DQJWeaDYsZxOp2codC5RQ4n4AQnn+p06kzguYqvUxFlrANt02FvLOWapnjnowfnAgk9tUL4K0QBhobymJmpOirR9KD6DYYniSNDnzvTeAJnv2vSHojfj15joEqbSg86yoHICJBwUngM8far2YbjhMWCoco9RF9uqPH1E/qRyqB6q3++6aLT1HnXNCPdpoRGsPqL+KpO1kEBE9mDt+IS4CNdmFNORtv8w9QkGjyaNUJ9D79RjDsvKg==
*/