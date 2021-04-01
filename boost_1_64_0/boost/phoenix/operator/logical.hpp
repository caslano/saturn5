/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_LOGICAL_HPP
#define BOOST_PHOENIX_OPERATOR_LOGICAL_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    
    BOOST_PHOENIX_UNARY_OPERATORS(
        (logical_not)
    )
    BOOST_PHOENIX_BINARY_OPERATORS(
        (logical_and)
        (logical_or)
    )
    
    using proto::exprns_::operator!;
    using proto::exprns_::operator&&;
    using proto::exprns_::operator||;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* logical.hpp
EHVjD3TZxT4G1o6UT0nAIioJWzcC46FcPg0TxSFrJg9rtSL6ulx6Om6EVM5dWp018o1lqSkf0JQcj5IIGAQDgMBKYYAZ/wvEMjcDkZul9AcCkVM/4/qhkZdZF1LL1sIrSON0j9lMF56nnk6dXsg7Px8XHpY2lVbEgq8VJZ77pOnyHkWuGqtpx1lbyG8Ok6ZZPql+odJ+TQiON6DHfY7WhKeRWBVpTiFn+sa4+v18DWTwN2VhXxki/bHDcJbEw5VxevSB1pE1JwjkFz0zpHQwCPxU4I8pH4tPLWSaO8wO2dSvbj+8wR5tNrB3U6U8kCa7zBUzthkzUBJ32IYOilF8TfRumbM0ofXv37GtVzov1d4ADT13ntrDnvsUFr5w0pBeJC+Hyhmwh1zG2NULf5Z6KhxOLIQ64epIIEaWCFnKZG+CMKTUY2lu6E2/hpYYPnsfsrYyCp5ocM0njdZFbH6irDtyHRx70dYbgd7LQS5qPkcVTzL8AmWmKK0dQxJXTuwqoibAxsUEkDVY13LoA3kD4qdiljunBP8PBEywWbJ7BDaQFUcbvqGKeE4uBg==
*/