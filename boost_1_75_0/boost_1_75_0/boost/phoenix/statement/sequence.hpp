/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP
#define BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/proto/operators.hpp> // Included to solve #5715

namespace boost { namespace phoenix
{
    namespace expression
    {
        template <typename A0, typename A1>
        struct sequence
            : expr<proto::tag::comma, A0, A1>
        {};
    }

    namespace rule
    {
        struct sequence
            : expression::sequence<
                meta_grammar
              , meta_grammar
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<proto::tag::comma, Dummy>
        : enable_rule<rule::sequence, Dummy>
    {};

}}

#endif

/* sequence.hpp
TUuoc6EHZJsPDi4WJJipH20WTKnWc7fVn2MPREcA+3bTii4iAY0SnibWdhTU17qjgUJw9irJcY+rO8X2OyW12J8HXHM0sUkGoZufLJ6YW0ePriA1mCDJe5/hve8T8MGjG2Rjn9OJUqGTCtx3sf/1K4MetiMO138LjGEZsUJFrmiLmIBNuzbt1wUFq5I3yBx0jYyV5U6vJ7tVVvoRe2A+zlLJb4gUrPeE0LkaOfZtl5bKTNs07OhNVHrIsGYjtR3BkGIZNXY9Rux8XxsVFzel/UI207xYIpsX/jWw2oN0kASc5S7ckOX2Ia1o3zVBAmMWH6DYoFC8wBMfngocCjkMPfHcFw2RLkqh7MhPlSfk79cfCQBYN1G0nwnZAF/jnttbd2wZn+M3uwQFP3uljOmaxMR+oCcQrqQhKAKDrd1WvvKx/OiJRXDgj7a+F6EnPKFDayc2NlUPyOyMPZPOVWucoogY9t/9yz8tXpAF3mSB88if1fD8YMXFXov5FvvdcmVPpii/ZtQQldXrwNvcF797x1b429UVerv9GsfQ/mLJqdUbljZKcFwdc1uy+Xk2QIsIavsfNgZT7c+EQ1dZDUqztC02qK3sIZvXIfvoiTK/q89418/m7A8ZkhlViXt2077cmb2WF9mA4uKdAfUFKEZkjlxacIvMNoD8RLeYWS2mCdtVeZxTZe1jbsQ88OD9ofs2l/dSFxxwvzHBzveI
*/