//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFER_TRAITS_HPP
#define BOOST_BEAST_DETAIL_BUFFER_TRAITS_HPP

#include <boost/asio/buffer.hpp>
#include <boost/config/workaround.hpp>
#include <boost/type_traits/make_void.hpp>
#include <cstdint>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)

template<class T>
struct buffers_iterator_type_helper
{
    using type = decltype(
        net::buffer_sequence_begin(
            std::declval<T const&>()));
};

template<>
struct buffers_iterator_type_helper<
    net::const_buffer>
{
    using type = net::const_buffer const*;
};

template<>
struct buffers_iterator_type_helper<
    net::mutable_buffer>
{
    using type = net::mutable_buffer const*;
};

#endif

struct buffer_bytes_impl
{
    std::size_t
    operator()(net::const_buffer b) const noexcept
    {
        return net::const_buffer(b).size();
    }

    std::size_t
    operator()(net::mutable_buffer b) const noexcept
    {
        return net::mutable_buffer(b).size();
    }

    template<
        class B,
        class = typename std::enable_if<
            net::is_const_buffer_sequence<B>::value>::type>
    std::size_t
    operator()(B const& b) const noexcept
    {
        using net::buffer_size;
        return buffer_size(b);
    }
};

/** Return `true` if a buffer sequence is empty

    This is sometimes faster than using @ref buffer_bytes
*/
template<class ConstBufferSequence>
bool
buffers_empty(ConstBufferSequence const& buffers)
{
    auto it = net::buffer_sequence_begin(buffers);
    auto end = net::buffer_sequence_end(buffers);
    while(it != end)
    {
        if(net::const_buffer(*it).size() > 0)
            return false;
        ++it;
    }
    return true;
}

} // detail
} // beast
} // boost

#endif

/* buffer_traits.hpp
0nWKf0YJ/+aFC6HPhvIOfezIPUr/rbMfKjI16STRXkd7kYiu1TJvF9nWV+F66nQczQBcMnALfI4dmSFaxZCt/5Hg55ZgGwQNWkaNqCAhgqGvRngu/SEMZEKjwz3jzTrIEAROc/1Sj5jHP5ipvv9xybM8JHyqwW3uWGx0derispYhBdHLYIAHPAGFvCO//qzhPzN/wnwdv4KMN/VyCxpmtuB14nXOulng9caNdK24ha/btc27pc+sXoytDb+wgy+evZ6UOjO8286pR9ZnVBCONy/alz2BwXvqiDTn1Il3Pr78/MF+s7SaeIKLIuyZgQeRN9gGu2I5egcXwQtceLLGxN74eTaf0lZ6dWtGuL7FbRk0YplsYFXMBF6QEOhOsxzoTzxMTinxowlpTpiddS3TOA8901rHn1+aWBwmPFM9CITPnLODX/AmDnc2D8xL/HL9ej+cZ/EITe8+ND+uNa2BnTAIknogmUbGnJNu9SMb7zfn0X7L/CtXkCrNunMg9OjyqPOFpaWdu4i0v0xhowQcOcx/t5jaHg4Tin+8Fra4UfLDS3a/bmtpj8Zy8MS67GY53G8XncbxCc9+R3KpDBVo/2O2BZX9XvoTuw/Dm1Qnlkvo6xP7Ga9fpvCk4VaAwEAyim5OTAHZ1tfLLehvHLlEBsiMyJq/X9W1I/lxO0hMfQNsEXgknPqEEjt38mDeCoyP/ObmGMQ4HnV4rO8W
*/