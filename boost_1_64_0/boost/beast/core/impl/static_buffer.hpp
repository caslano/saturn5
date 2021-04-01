//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_STATIC_BUFFER_HPP
#define BOOST_BEAST_IMPL_STATIC_BUFFER_HPP

#include <boost/asio/buffer.hpp>
#include <stdexcept>

namespace boost {
namespace beast {

template<std::size_t N>
static_buffer<N>::
static_buffer(static_buffer const& other) noexcept
    : static_buffer_base(buf_, N)
{
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
}

template<std::size_t N>
auto
static_buffer<N>::
operator=(static_buffer const& other) noexcept ->
    static_buffer<N>&
{
    if(this == &other)
        return *this;
    this->consume(this->size());
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
    return *this;
}

} // beast
} // boost

#endif

/* static_buffer.hpp
z0SnQp1cp1cnceHECjdMZLQUkdyzk2RYLWc3zHdrFAqkw4RTj1ah4m1Sj87R8kMZxWpoQgyPVH5ad7Z6YmMDVpQQJYef/ArHtO+AnOC539fxw/Qda9ewPcwIxhJ5qBYmV6Wy9tD0cmRqOSAkUSV02VnG0cjp8p0IatXjv2JohB/zloPGVCzMGpfeY3N+EhC2wzFafafqBKnbcKK/6Pe0TkVDri3b9KyrH9/hcSlRzkLt2Hdb4fJfvjybtqi+w5hL4kQbeU5HKkl7af90rxvUpRWOwX+NHeGrjgpL65Dlx8g+AbmRLf7RgJ9wLk3AWCb+kmka4hJsFaiDVt1HNmyPkmu81qT/YCSyOGzONAl2msI1iFwCI+ubQ1eOoBl8CSwuIDgMxb42m2af7OHUvoQ+sIPUOwS893YT4+7dYmSmFpklapiXjkCxdqM2v8PY409o9XMTtMgenz2gyY03BLX2VxV2HX1VHpL1wHzqL+rNZvNF6xDHhtePNXDIdoBcknVfF5ITglf3hDRMFslCUIHC7VfBZZNMNeTa+MGnLuSyY4WY1MIZUZPuiC4SfQ==
*/