/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_ARITHMETIC_HPP
#define BOOST_PHOENIX_OPERATOR_ARITHMETIC_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (negate)
        (unary_plus)
        (pre_inc)
        (pre_dec)
        (post_inc)
        (post_dec)
    )
    
    BOOST_PHOENIX_BINARY_OPERATORS(
        (plus_assign)
        (minus_assign)
        (multiplies_assign)
        (divides_assign)
        (modulus_assign)
        (plus)
        (minus)
        (multiplies)
        (divides)
        (modulus)
    )

    using proto::exprns_::operator++;
    using proto::exprns_::operator--;
    using proto::exprns_::operator+=;
    using proto::exprns_::operator-=;
    using proto::exprns_::operator*=;
    using proto::exprns_::operator/=;
    using proto::exprns_::operator%=;
    using proto::exprns_::operator+;
    using proto::exprns_::operator-;
    using proto::exprns_::operator*;
    using proto::exprns_::operator/;
    using proto::exprns_::operator%;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* arithmetic.hpp
Sez1FpFDFBwnBB2Za+eEPCRWGD8Y7oC6bSh+17Q8eICUvOAuPxhrl0ou7gqDbSjrgsMo7P50O9+ovaPj2jAy73oyuP7469U8/ojpA0lrqGd9jQPf1QJwjWElhlWpWkDPEa22c7j6pTCnJxheQgiz710NGiguDpiM2Ngc2o68A84xpG/gg0lluCO4hOZxV11kf46kHljFFYQV+L02sUimpqYdhBVBCQs/V9ScNog6DUfZH/XsEpzJp7I3VH745nhBXkfjS4eiKGamTlYXc0cEnTtRRoN8dikOTwTtqyO2jiTL3r60Fyd0Fo23Z3334yWWjWZMSa7j+33Y2ZofdBwmtIKrPOI65eOnkhDVhPIoqid4kqA5JCheMHxok9hp7p9oJ5vicyb5Hm3h4awRi+Zfwhb9OqJ+kE7vxnkgmIwqWpVT3ISuh+KOflc+WObWHe43Ar5PgFswqlMVy1XKibSJk9+noBcjdB0vFlv9taqiTC2S916bw0Y2lAJk17SRXxKIaCLwRuegAg41AVp+EThGNwhNnKtyWS1Ijglc4BE+4oCdastEtASj+H+6sBZ4Wbib/rHI0UND8YT9mb+l2FAVj+RSYu5OtuLRC7lX8/lh0RgWhFCN2yqckJfAE1v2kUwWVzbhUYq0xCGjy2pQjhunqN9iU7Jsf3XawCAxjYjP7mZyAY01n0I7G9ObMzDeKZLfoMzfhMNDEhs82LJ7
*/