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
68Ebxf57rEcY3OPOMHnQP3G/QBywQfiOqBzVluuHjIv3rTuivTqhydrvEr0n4a9i34d1E5vw95B0yi16dobhHnqnjz6f5eZdbm8zXa1rZ1j//fpVDMuiaP508vvv12/oz33zskfCUD2HutdDk8z773nOvwILXlHhQ6IioiLbRE6M7IXL721R0EDHQPdqV6gDyKEaPC5QG2+crmrL3ouWEu9urLH18E9L7n2PY3onkd5CxGOveQ0367cL99x10K2dEj7qeyWtStC1km5z9L1h7dzpqZ7FFRUqjvvk0c6w7sh2ZtkrH67vG+deea1jZDvhWmaJ1nGiHVCX2UP4yqnD9OgrJX69P76KbowK7lHt7sN3sLPQjnIWVc2bt8h9Dz3cX8VCaP3bkImaB79wvZdmItc87aZuDXgC9ClkHz1Mf0t5o6fm5BXOd5rFYN1Im0XleOumr/B/pB5E3PzOGEdnS5hKCcNviv7evSW9xd6ofoF/u6IuzU7qIChB3rN4IbKv+R9qNNamtM5+ZGcvRcT41K+0p4TOHjrzuQezft8aputX33uBvEPOLC/c0rWblMdHntnhfA8a1J54BLz55/nKc1ZFcbGvPCUqtmu0X+GfRVl6wsfRjtNFpp1yyg4zGxvlFGcVU/PkFNfOSwXRZ5aTr1wk3z4yaKAMHJZ7MDajXap0XxnMLnbhi3HL4P4UrwxYZvI7znj3h+eeeMTB/Pjq6Z1crs3mWvJ40IdmG/fLT3nxtUH7nmHC21clKiNQn0WZBb/L3iqf7bwg5EPqJ14DNZoL+n75qSjGixJN24jO093C/yTWqCMpM8aBHjIe7cJl7kto4fl+NkmzCI+KbXm6NtGV4bI94bo0vz155BLbzkNnbkvmN5d4vv7mgrUtffZva0slZhS/r8Ggu1Dvm873kZ28xTGrrGB2ZQD5UVYME6f30j0u9t5aP2codwzc/0T+Tlo3vkvs3XR7eLujh85c7gDl1H0L0oabpO3TjrMjlZifgRL5vvznCK8u8JZ9bGl5Qdlp+pUBwuuiDDxhBwQcM0zQ/v20jPrBzrdZOE7g3zHen9xH/BeJPVuH76O8bx+V+tw5i79LMDOrZnEfX6qljc3rJP02/m7Lb5FpzRnug3WK7AxpV6sv8G1XmwLIe6v1byvd6vTfVpaN+4CqJO5SXXfIO+ySd5962hulxMwGnQOaAnoAbXS/pZ4uKS91qeBtk7x9tdz/Kvbhwcan5O+t6+HEBTyTqsemLAvHpX8R//M5JmV4c1zFcTPbgW43x8T/PI5TPfyJPFvo7gcrmzGG4h1RTeohy2+8xDOIaKmsB8u4CvljffnKfVVbJabU5h4XXwL8GOlkX+gr97zi6qDfxzrh7WdjPTDsiGByp/+Ferx+i9j7GL9QV9ENo/kM063USFKxhn99xLC+bpBwfY09agLrxBP3UPJ44pmHncGfN60nnvFdLWHOtbGeGEe68H8g/KXznGXeM7w14p9m884nGIZj/GjDeiZ3jr4H+w/C0x92j5/8tdLvxtSKfyzy+iTdDLV8uPve89aqtYQrTpC/zgVFlj28w9CeooDfdEeDgbx7tdPfP36LO+w+v/XYbtcZ+oZNlr4BsvTpG44FaJMnA7RJZTRtky0Ma5sUN5HbB+Im8tZ7CVFmuKHM/m2XI5w+fD+lK+gzc9w4wtt2pzmLClzFQfsM8na17HcHfwHbqvbvI/49/PqEbIu/Zb4kck0OPq4J/ndMz2kkD/q776Fl51v+BPwryPJ3BD2YgnZkKX9l6WKUPuh4kbzROv9zujD/zfg77D92HMZ3oA4wX1kcO47geL7enS9ziSMPofIKsQpSXuUM2q+8IfyDmFdP+Jg=
*/