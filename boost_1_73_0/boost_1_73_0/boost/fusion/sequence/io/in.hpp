/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_IN_05042005_0120)
#define BOOST_IN_05042005_0120

#include <boost/fusion/support/config.hpp>
#include <istream>
#include <boost/fusion/sequence/io/detail/in.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace boost { namespace fusion
{
    template <typename Sequence>
    inline std::istream&
    in(std::istream& is, Sequence& seq)
    {
        detail::read_sequence(is, seq);
        return is;
    }

    namespace operators
    {
        template <typename Sequence>
        inline typename
            boost::enable_if<
               fusion::traits::is_sequence<Sequence>
              , std::istream&
            >::type
        operator>>(std::istream& is, Sequence& seq)
        {
            return fusion::in(is, seq);
        }
    }
    using operators::operator>>;
}}

#endif

/* in.hpp
BLqjH/oFD9T4GtBgaj+i/vjq8D8C9ek1oDkidS/Zm5j2vw68eb5UrpYqeboI6Wxxbq40XZnLT9NZ5nR131R2y/TsVKHKZQeyWbr2rqi7mrwhP1GcG58tzdDVejkuw2VS2Wxe5PL9os3Jkqq5ksFlO0UlmxlMz2WH6T/JD3NntlPK+emjZJ+fh/0hsi9XxiEhw6XCZYiLs/kq/TRpsMOmB8sC+0nkCFBC7Pjy05XxYjwsXTU4vtRwXDe5M55GP5Y=
*/