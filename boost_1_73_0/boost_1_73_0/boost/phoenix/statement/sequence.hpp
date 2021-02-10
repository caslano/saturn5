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
ycy3nTH+C6KAh8F86DrRtJ2SAh15dtcPSURdUFQEc2jESaakLyTTxlaoyzMnxn8i34uwp9upP8s0BBECkvE89KAbEAG0sX0QcJvMPZuGrC1jWvYgpMlEWzIkKa028T2ghDT2++S43yBDK3KiNvl8fPn+7NMl+bx/cbF/evkbOXtL9k9/A1wfjk8PYbwd6Ckk9C4IaQQ9h8SZBa5DbdbhMucmdNmPYciBgWhqkzF0BYMh1ad/cM7k2H97eU5wUEEUEQyzFXpIF36IgCSyj5owCqkFTxggIIOB8cbOZB5aqD1MXBHxKLUp7waaRVSiWMFOUWijeJf9DqL0HG8S8U8Ht3byC2law2gQWPG0yZ8dOhNAsrNzcvhD4QFpzuwfBlN6J9qeHJ8c7ey8sSL64vnuyrLN3K9W6OBUiJjQovkwwnHzQ9SDcQiKB2KZUjdAJZ+7FMaSsS0efrltraAZWcORoHc0+ZD+PobpFd5kPqsNr+liQj31ic0HIfmc+QjQ6udrz7/1pj6MRwru+ils+jsAZj6MZraAmUZxEN4AHeP083yY/wxjIj6PXCfTHj8r7WEiBa61GOQ4UR7rnmb5UnFIqpVnhUcKc/Z8FgysMLQW7OPY8WyGJvNJ+cCHJ/sg05YPEHsEfcwi3g18cQMW
*/