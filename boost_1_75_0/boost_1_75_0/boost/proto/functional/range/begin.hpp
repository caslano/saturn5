///////////////////////////////////////////////////////////////////////////////
/// \file begin.hpp
/// Proto callables for boost::begin()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012

#include <boost/range/begin.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::begin()
    struct begin
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::begin(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::begin(rng);
        }
    };

}}}

#endif

/* begin.hpp
+5oyOV8oJQQtKNnMOAvZ0xo1E0SCBK0KZ3EcDOeHu+Re6ey06bZNw7MSfqUbzDUh+fQtaq4o7ELt92Q7TLO94Xtgk0oVVuUuf3N458rJW92wbH132viHQSxxFwJND935Y6ixn/LOTdZM1DDhy43cnd3E+Eu15FTS9+F78I8p2Ps/tuvUtqUpAl5oHwg+aGCqvX9wdlZBbShoFIZSoIVSLqW43VLcpbgEd3d31+IOpRQp7hSXAsGd4O7W4F7C4p4AwUmyMrOzs7M7szP7eF7+h//tezjnY+cprJE61z9WhpO6ADOQlPckcL5H4ZLyvpI+ud8hcAE4jlOf5NkCKrNXNkweUg6dhSwAisqICg6oha5Cu9lL9B05z39C551hAtSmQOjc3XHh36cmjyE4z5unsKBaWHAcly/ukShWbgA5ozNfSxiavQ6fmHTf9+si/wlKgbEQ696p3qm1Fo8RFXv0v1yCVHAYe2rCAdvkHCTizmPNjpijRHXWfRLWZ9AcXDGrcrKCUsPEEvwrhYu1zDoqe0j0XLZROZC5GTIR8HOd+zhIXGjJHLwJUTL3bVSd9GqGyjoLB70Gg4+3rP/S6DJqo8hpy1vkz1d96Eo9pWS20U/TkuE2ZcObTGY21+6gxEIaMCFArqYPtEX4s9SW9bxXAwQz+zBPeWDbTCWKiWaSaz/mzNLdz6iM13pNW0glngkGw3QVUsJ90Vx//CRW
*/