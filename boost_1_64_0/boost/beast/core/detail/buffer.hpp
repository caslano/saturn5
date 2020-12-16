//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_BUFFER_HPP
#define BOOST_BEAST_CORE_DETAIL_BUFFER_HPP

#include <boost/beast/core/error.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <stdexcept>

namespace boost {
namespace beast {
namespace detail {

template<
    class DynamicBuffer,
    class ErrorValue>
auto
dynamic_buffer_prepare_noexcept(
    DynamicBuffer& buffer,
    std::size_t size,
    error_code& ec,
    ErrorValue ev) ->
        boost::optional<typename
        DynamicBuffer::mutable_buffers_type>
{
    if(buffer.max_size() - buffer.size() < size)
    {
        // length error
        ec = ev;
        return boost::none;
    }
    boost::optional<typename
        DynamicBuffer::mutable_buffers_type> result;
    result.emplace(buffer.prepare(size));
    ec = {};
    return result;
}

template<
    class DynamicBuffer,
    class ErrorValue>
auto
dynamic_buffer_prepare(
    DynamicBuffer& buffer,
    std::size_t size,
    error_code& ec,
    ErrorValue ev) ->
        boost::optional<typename
        DynamicBuffer::mutable_buffers_type>
{
#ifndef BOOST_NO_EXCEPTIONS
    try
    {
        boost::optional<typename
            DynamicBuffer::mutable_buffers_type> result;
        result.emplace(buffer.prepare(size));
        ec = {};
        return result;
    }
    catch(std::length_error const&)
    {
        ec = ev;
    }
    return boost::none;

#else
    return dynamic_buffer_prepare_noexcept(
        buffer, size, ec, ev);
#endif
}

} // detail
} // beast
} // boost

#endif

/* buffer.hpp
tqRTw/CDA6RTb0mnvjB4/Sax/+pj8I0OYEdgXyDTwTpy8PrtbmmviUXB02nFdNoynWim086STnZR8HRaWtKpOU06n1Bun7O9NrK9fmGRW91p0jlikVvDadKJY3m6sDwJLM85QN0OioOn08GwtIPi4Ol8x/I4mE4Y0wm3pOM8TTr/YHnyQZvIV0G+lsCp5EsGXwfebduTb9UP4N22mbzbdgowleeJBvH8WBrPkQzVcuOaF/PjX55VLM+PWD+1wATg7Zb6yWf4PgHKs1L4eJ8I+cLJZwf2JN8u8Cm+5RIGfMraXzFcZID4n7CUo458vQOUYx/L8TrL8SbfBjpgSaeB4fsHSOcVSzkSZwcvxzKWo4blWGGJP3V28HJcRz4nKJN8N5PP5C8i3yzD3d/OBl4GLAVOBc7h36frgAXAMuBs4ALgPKALWAlcBFwMXApcTn7PubhjTHdsgHNx48Bn4iUcN0wEdgFOBiYCpwJ7A6/kOCIXmAm8Gsi/s5wrM36/v7M9KLeewDjaO9Nuhu1lrWfGEx2gnkcyn6OArYAX8e/3aMv3t5/hOwSohxHgO+hQcqZJLY5QnUBpoGxQCWgpaCOoHnQYFL0EZ1NAq0BbQAdBJ0EpSyNULsgFqgVtBR0AqesiVCwoFZQDqgZtB+0FnQR1Wob4QGWgTaDdoEaQWh6BczVnPos1EWevykCrQf7nsRwYRPUE+Z/LOuB0n80q8zufNQbp+Z/RihoBBJlntTKBpzuv9f4C3zNb+8wzW6BOIxEfJgDpwBzQcfgtBY5ZZtfnudbCngzM9DvXtYdnuw5U4nzUSPcZr8YhYcqR6T3rlYLfDWZYV+AzX2sDnPuqx++DoEBnvzKrvOe/WlwIuY9ynwPLAE4FBTsPthZudaAtqcgvsB54EhjsfNgqnhHba7pbzoqNedYh58WiRp/+baCU0d5zY5mjwQOynh9bOtp7hmw9fm8Fec6S7R2NNEHJi3zPlKWNOfO5suOWs2XJQM/5MidwPWgnyP+sWaOcNwOhjQV5WwjfXvCzZ2VjEQZUB9oHCnQWTY1DXhf7nklLB+XzbNomv/NpO2E/CXzfRJD/WbVYnFHb+KxDn1nLgD0X5OLZtfXAOlDtUNhRrk2getBhUIsafPOgfNBq0C7QQdApUMKKCJUJygetBm0HHQSp6xEGlANaDaoDNYBarESfBMoHrQXVgw6DolfBHZQLWgvaA2oERd8QoTJAuTeEzs6FTMiETMiETMiETMiETMiETMiEzNmZH/j9v9Ki4oLc0rxKHMn/99//M8+w9re839czTIm5zHCv+yUAv+inVPQVsnflkjEXj8rDcTJcCym5yUMmZD/Qx/3kvuG5lruGGaaHiuP+nyFiP4F1+VR1J8gbrkiHm6DDddT3TvcR+3lGK+++TM891ozTLn68y1fvte07nfeQm37hskLstO7BGsiwXn+X9s+G/yDxH2iY+5V2wj3fjrVUc69azd3YqtbK7ogsi+wTmRLexu4It9mjcVbHFoa4JG1o1QZJXNzn+7jENVbFid0jixZIe4JaCfdWOlyF3m/6ovDgHCnLs0/sqaoTuOPEzVem69VQxuMrh8PC04p2Q9WLPUp581pu5lXSmYty7xb/wfCPtcS3QJ8ZflP8e6kWqr01jsGe8pr7ch4Rnp20G556Uhb5mPw6zsfE/wqFFS0Jg7V75jNDn0vubdYn9/QNZJ0cdLBOeptVEhXlCA+3t2tSK0oFq5dRksaEs6qX6X71knuaeumJOkFbD1gvLr96yT5DvYxzfweqfZB6KWxGvQwTnqqg9TBc/KdBxpfqepggbqOatR9N7kwH4rtGH4L+gG7R2q1orv9Z1FguvZVT71E=
*/