/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_SELF_HPP
#define BOOST_PHOENIX_OPERATOR_SELF_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (address_of)
        (dereference)
    )
    BOOST_PHOENIX_BINARY_OPERATORS(
        (assign)
        (subscript)
    )
    
    using proto::exprns_::operator&;
    using proto::exprns_::operator*;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* self.hpp
c5Myy+E37UYG9sswQKYb+YtahX6Pg22DrnzfLlMmgIrRPJCpa5YcClNXxB1E+nPrx/B7m6tzWPGQndRN1lhntyqCazZZCexQsTehTusTenK9nZh0zsWJ/Ni1Cdk+5+3zOeo4RDAJY/y9XfZuCgmqFrf2DjIZ8kKXEdgM9Ji6ihhWCnENUZhRHRjhOl0jCKwwlaVvy4QDTyhg+dPRZiF1dQqxVP3wQcJ18HvNLHoYJRplQHl+Ptm+5R6yrKJYD3Cjz30bYWRXSr7cE8M0r1fOyIqzlCRqOFhty82DTwUKxB7iJaqjy2CEAvis+k+ZJFBW84EHjtmu5BM73YJ/GJetssqZtPp5CacLAVXXPKIRIa4d6ubvpCF1VXCNHt5hZR/c63PffR1UZaGtW0IP6C8UmzwctiAZFgQ+XMlLOyYwYe85HsGaV+35iASHwev7k4MyqKJkY3mnqGtoguYa6Dztcs/wb3c+Szm85JdzfizxAA4+SVYWm1NJVmyR14u/nVXqGeKwZkVe8kkrVzf1+IXUNAq2oQ2w0XtZzTl9GE0pBL8sE2wkTBWIU45++w==
*/