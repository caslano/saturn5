//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_FLAT_STREAM_HPP
#define BOOST_BEAST_CORE_DETAIL_FLAT_STREAM_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/asio/buffer.hpp>
#include <cstdlib>

namespace boost {
namespace beast {
namespace detail {

class flat_stream_base
{
public:
    // Largest buffer size we will flatten.
    // 16KB is the upper limit on reasonably sized HTTP messages.
    static std::size_t constexpr max_size = 16 * 1024;

    // Largest stack we will use to flatten
    static std::size_t constexpr max_stack = 8 * 1024;

    struct flatten_result
    {
        std::size_t size;
        bool flatten;
    };

    // calculates the flatten settings for a buffer sequence
    template<class BufferSequence>
    static
    flatten_result
    flatten(
        BufferSequence const& buffers, std::size_t limit)
    {
        flatten_result result{0, false};
        auto first = net::buffer_sequence_begin(buffers);
        auto last = net::buffer_sequence_end(buffers);
        if(first != last)
        {
            result.size = buffer_bytes(*first);
            if(result.size < limit)
            {
                auto it = first;
                auto prev = first;
                while(++it != last)
                {
                    auto const n = buffer_bytes(*it);
                    if(result.size + n > limit)
                        break;
                    result.size += n;
                    prev = it;
                }
                result.flatten = prev != first;
            }
        }
        return result;
    }
};

} // detail
} // beast
} // boost

#endif

/* flat_stream.hpp
3O8W3K/R/X6bNrLOfjI76J2CMomBcWQX0uKvH4gPekF8Dn3sTwtO306rfrimz1vjZWdupfG64DRSLlH6hgfi/d9lAt9+Fhs8ekzVjXxcZ+Qjkd/PcB/46fvY9L89PTh/dyCOVvf8baqrCJk3yiRyLBvclzE8MIY/w3zxuyDHt3IP+5rukcF5aoJ8u2ueeD6Se54okxj6u3kHeS4w5APvJD3Ls7O/y+tADxUZwXq4DXGqbDc90AaQe9uiTGg9MDzwjb4bZfvJTvJp9tdqVHCefpiJGHWerqmpLJNGKGn9Q1JwXtIdac1L6HpaER/Tan9vqXBJ13OZiNuWLt1hdru/1PnPDL5PO/yK7fdBRxny2wt4z7yfRHzMvz1dz7mk6xX4NdrSJR1IqHIhb2LosW32mfcfuF9QHdNjDGdeRgfnZYfV59vyIh1HyLw0d9JemjvIa4HIn3m/8YekrvUbOv+OurxrTHD+X0NZttryzw5Dha5nrZ3ooLUHfcbLmZ33GSeAeWGh1siHWuPf/fNB3Nfan7218GdrbXtDiqQz98i0/IpvfPfJBeu8A4vufbH75324r4UPtXa++3sd3PdYdH9NfXf3ZITaY3FS7NXIJd/Ioz0oQ4/v+2YD7SJVGv+vM/43Gv9vMP6/l6H/yzf8dI/v0fa28f8d4/8p4/8/jf/v6v/yLUrSNo5npmTp9Xiy5lDCwKJSgMrip+3+cI9vv0AUcBqwL3AhMAa4GtgPeD2wP3Ar3dvovhU4ANgEHAq8B5gA3A0cBHwIOAT4fWAi8Bny/RyYBPwzMBn4NjAF+C5wBBBpUqnAaGAacAwwHTgRmAG8GDgauAI4BrgFOBZ4GzAL+DXgBOCPgROBzwMnA38DzAG+AZwCtNZgTgVa+lJ6vZKsqRJ9jbDKh2V/nnV/YB71NQ84F7gQWAlcAvQCLwJuAuYDtwAXAe8FLrb0Qr4W4FLgs8BLgC8ALwX+Abgc+CfgCuDrwFXAd4CrgRFI02XAWI/P3Z/uQcDLgWnAK4BzgR8BrvH44q0FFgF3AouBjwLXAh8HlgL3A8uohwb/ehCuQYl22FK6ibacttF20SdZj24BjuOZMjN5VsTFPCNiBc+IKATeRZtYO4DX8yya2yjH/SlcuwDd8f7m/pRtVrkpaYNyv5uBk6z7A2fQfYGVLuAc+rN8Od+NvLuU727uo/k89298gftoHmR+HgbO4VkwF/Hslytoy+rjtF11A21S7eaZLw8Cvwb8HvAJ4A94BtCPeObPQeA3gM/xTKA24FPA3/BsoD+Q7w3gt4FxHt8ZQSOB3wWOAn4POAH4feAUunPpzgP+kGeXPEP9HtXzseibqQerPF+iHn7OfUSHuF/mVzyD5zDPCPoty/N3wGqenbQJeIRnsbRzf8ofgJ/nGUt7yNcCfA34LM+6eYFn3PwJ+BeerfRX5vN14DDgG8DRwDeBYscSWMHwWuAJ4Bbg28BPAU/yTJZ/aFtlnL/iXFy0w1bZBtanauAYYA3wHKAXeCnwao8vv9cBS4GbgNcArwFuo/s24LXAz1rxAneR/3Hgx9jfNQC5T4rzOr65oWjHPqkVPJtlJW2nrQKm0E2bfJyrQZopb9rku5JyJay/Zay35dx/VMGzf64yzvZpZ3xTGJ95tk8W0zOO+7fGc7/TBKC8TjKedMW5E+A0xuMBDmY8Y8mnv+MD+5DP3Od1Pfd53QCUPcuUC3xbBj/lwoAplGug3GaDv6kD/jry15PfC2om/93kN20snsN9b9O57+189guzaMvuAvYLeWwfy4ClwALuKzuXZ0TNAN5Bf+qN39d8Y+50h95GGXyNXeRr7iJfaxf52rvIp7K7xpdu8DUoO9+VBl8=
*/