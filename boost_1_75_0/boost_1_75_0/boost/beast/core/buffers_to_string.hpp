//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_TO_STRING_HPP
#define BOOST_BEAST_BUFFERS_TO_STRING_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/asio/buffer.hpp>
#include <string>

namespace boost {
namespace beast {

/** Return a string representing the contents of a buffer sequence.

    This function returns a string representing an entire buffer
    sequence. Nulls and unprintable characters in the buffer
    sequence are inserted to the resulting string as-is. No
    character conversions are performed.

    @param buffers The buffer sequence to convert

    @par Example

    This function writes a buffer sequence converted to a string
    to `std::cout`.

    @code
    template<class ConstBufferSequence>
    void print(ConstBufferSequence const& buffers)
    {
        std::cout << buffers_to_string(buffers) << std::endl;
    }
    @endcode
*/
template<class ConstBufferSequence>
std::string
buffers_to_string(ConstBufferSequence const& buffers)
{
    static_assert(
        net::is_const_buffer_sequence<ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");
    std::string result;
    result.reserve(buffer_bytes(buffers));
    for(auto const buffer : buffers_range_ref(buffers))
        result.append(static_cast<char const*>(
            buffer.data()), buffer.size());
    return result;
}

} // beast
} // boost

#endif

/* buffers_to_string.hpp
esXgjMM+q7kLbkZYj/lu8iTFZ8Na0TYq0Iexh6oDFre1dXuuzjFPt5XrPxFyD8GZMEgYgGNzYts2v9i2bdu2bduY2M4f27btibHeqj3tuc9dXV1v96NXfcE3NLvnHAY1WGToiHnuSkwe1x+XmjE7ynS6afKF4KiCK/wGXZPnyuwn5kL4p0Tnuny4qf4I6z7nhJ8mD+N0yLNB+Up4k/6pF/TLXzpmfNGox0PfB+XvTho0+1fqP5201TzsX/nFq11FEb1+EPl/Innuagoi0IxWfdRFBWVGYGTf1kpurZgIJkdhAge9StBUd6COhlUICTIOHgQKNRwOD/Rf7UZgeqtzPZupZR5Py0CS92Zx9kTeamfGZ6hSo9C4YXuzcz13ZdcP0oA7RkjbBCvbTqzgmIdVjmMx/YzBA1eMJlq2fPK4kw+aLOBrC2MLvgoQFFBdUF0glhClkmQPVeCrgAEIViBYCR14zPBU2oGP9Kj3Pp7zEojBN+W+LkkI81xRc6IlcYTL0SpBekXp58xsSgBOrf4GSFyec9mpSe0D2/u4DFR9lNUhV0fQHl/hbopnr5NG7aV5qw2B7HPoDVlgq+Jg1LLyczCA9OwirEmSqCU2CXA+6p0kUSRppY9oJS7ZA4EnB2aSGWRvl6boyzy5r8tv4jL8I3lQ3/5oVql0ha6klUXhLGsGvAKk4YR4UH0QjTra1ZN6/5Mh3DtPRvUejDNK
*/