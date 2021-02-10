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
2D/uinMZErkQZOzNZcU6ipPiMXFfGZYeNQx2LJEuMH2JkHEAzySSCoY1T3Kph5fBaEDwoeSAB5UUVGtKZAvp44qCpiEutRTXUsyrKsvU9JE8e90diEHvdPiu3e8I+H7R773tnnROxMv38LAj+p1XnfPhQLTPT8Rx73zY7768HPb6A/Ff/9UeQIPHj/ERSYnz96Lzj4t+ZzAQvb7ovrk46wIcANxvnw+7nUFTdM+Pzy5PuuevgMqXQ3HeG4qz7pvuEKoNe03sDwGtthS9U/Gm0z9+DT/bL7tn3eF7Qui0OzzH7k6hv7a4aPeH3ePLs3ZfXFz2L3oDgobjOukOjs/a3Tedk10BSEDHovMWhiUGr9tnZ844AZIzzJcdQLH98oxgUT8wzJNuv3M8xPEU346BaoDdWVMMLjrHXfzS+UcHhtLuv28qsIPOv19CJXiI0E7ab9qvYHD1O8gCU3J82e+8QYSBEIPLl4Nhd3g57IhXvd7JAEEB+EGn/7Z73Bm0xFlvQBS7HHRAUbSHbeoeoAC54DF8f3k56BLhuufDTr9/eTHs9s4bpKR674AygGwbWp8QkXvnNGYgUq//HuEiPWgOmuLd6w6U95GmRLU20mIA1DseIjSrJvQK9BxagxXnnVdnXaD6cQef9hDQu+6g
*/