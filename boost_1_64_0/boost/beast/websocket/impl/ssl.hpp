//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_SSL_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_SSL_HPP

#include <utility>

namespace boost {
namespace beast {

/*

    See
    http://stackoverflow.com/questions/32046034/what-is-the-proper-way-to-securely-disconnect-an-asio-ssl-socket/32054476#32054476

    Behavior of ssl::stream regarding close_notify

    If the remote host calls async_shutdown then the
    local host's async_read will complete with eof.

    If both hosts call async_shutdown then the calls
    to async_shutdown will complete with eof.

*/

template<class AsyncStream>
void
teardown(
    role_type,
    net::ssl::stream<AsyncStream>& stream,
    error_code& ec)
{
    stream.shutdown(ec);
}

template<
    class AsyncStream,
    class TeardownHandler>
void
async_teardown(
    role_type,
    net::ssl::stream<AsyncStream>& stream,
    TeardownHandler&& handler)
{
    stream.async_shutdown(
        std::forward<TeardownHandler>(handler));
}

} // beast
} // boost

#endif

/* ssl.hpp
p6QMxZw0qu5zK5xzKnJk7lPSyHfWvqSDOWf7apGTODVnY5mznXznNR3SsaQL9Ty2ctSd5Jd95d78UlS4UjNMaH7Bjp61pul4WPQz5WQ07Egetl3xOcnYGeDPCyYPvSfmUygDtuYHx04ff34w4xnviPkQ0jFJ84hjp6c/T5h07VKBOS6kus8VypV4NeMnqaRnDMylo9m+XfTMnPqlXbY/7XSOm/jgHfHhpHFA2s12p52OcbQ3Z+KoH/1ncMVb8ixAnYQ6B7U7WgdUeNNUfqUf9sPTVO10FfOzfWV1ks/8AjFfWFq+VM++cZtrvNoa705arRDzSVYrTd9pxk6LgPQ1Y3YqY8658ZdXeZ8JA8upjgdeJm6km3TNoUw+7iqT2V+yTJ7tTkMtkxfIO4kbLZNOGmp88K7Mndb6LtOMceF/XzqfqmfW/V7T+RXUD0jn1wLTmRIcns5qp1toOqt5aDqreVgdreatxLws3pQ/U84HV2LOCNHJjIsmmjQrNuVzq5hHNN/gO9FPIy9EkHfcLDNpe62YM44tepVn1Kcz70Lyiut9mRg49c0CsTs5KC+Zc8USRWahFf13BirIn3KOouazXM1nKHLgDKkbr6mMesbzfTfxVyru9Pha8mV98uCHMCXy1Z/XH3pPqYyFzpvwi9F5Ox47vHBsau+PLi877/idpx889nj8zs3/qsdag8d4j/68/qMdsz0i5w9om0zboSthM9Rezaid9Cz9DDjKd1b9IufeUtgbXgD7wIthJlwH+8PL4AB4HRwIt8FBcDscAm+Cw+AD8FT4MDwNPgGHw8NwBHwVjoQfwlHwMx0bPgJnW9pu0PbRSlQCarKGYzFyreFS2BmWwixYBofCFRqucngOrITn6Xt1X79j1DEB7jdB7iTYDHaFLWAPHcvuC9NhNmwD58B28juYq/u7LK139Rsh5Rm1Xd2frO5Pg6fAGbAPXAQHwrPgLDgLzoOz4XJ4NlypchfBeTrGfg7cDM+FW2Gupkse/AmcDx+CBfA5uBC+ou7k1eMOgdj7WCsDWTMj62M2Q9aMyFqLzMB1NDp+/r+6dkbXzdSyZuao1svIWpn/0DoZ3x5u/9qYmutijnJNTNB6mPbkl2xUAWrDfQn/gf7/0sLKomPv/0f7+CeZs//lnAl5crXddzbqnTTczpd2XxkrY3P59QV4rITPv7Rr3kjz9pMm2iqPK631/rpbulk8BZ654T+IzCTOOooz7ZfktvQVff3X9nW0STIhfvD0QftpeFJiLHk+0j7o21GF7OY8b3hKy1a5wlJQ4VrLoLIdTd/zh6J/hDow3mWnonyB0/c0dlqbPQJ3iT5T9axolrA3ccVNhRM3In9Y5O+QU7P9dtpxN9sGZPZEkG9HnMW2TmoUH4lJTSqOj02OjXfWSb+XYoXG/X5x/6fW1VaS3OHm9FMaE/f7UOXpRxv3xJm+yzLviBNfeuzRO9c2xpIeytim5JdCb3pUli/x5S2THirbxeqtbeiPRJ8UO8y6gXN75rCSoAXnhjSz/mU3tyZHCq2fRNpyau9oc+fDwEVR+WY1zmttrmdNql84mfA11mnOccmV9QXWuZpGR0QuOfZR/n0Z9XeUbc9irS6nLKI+RLWIcAsB6l7US6gjqBYx5ATUZNRS1EbUPtRvUR+jtN+j/uhoxpBair/7Wk10vXxMvPipn5xjo3nzPbHzUcwjxPmLqA9R3VmRMpb4+JEdb/0KdQTVjPsMTo1cYP0Gvh9Bj2O9URNRi1GXoR5GHUZpP0H9c7Lec+D45/VIMj7qad0WkX0D1ftDTF7+YKHcQ0mKpQaGxZ9H5ztjLfJ7MbEPkUdfQB1B9beTrBmovahDqPdRaZEkaws=
*/