//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_RATE_POLICY_HPP
#define BOOST_BEAST_CORE_RATE_POLICY_HPP

#include <boost/beast/core/detail/config.hpp>
#include <cstdint>
#include <limits>

namespace boost {
namespace beast {

/** Helper class to assist implementing a <em>RatePolicy</em>.

    This class is used by the implementation to gain access to the
    private members of a user-defined object meeting the requirements
    of <em>RatePolicy</em>. To use it, simply declare it as a friend
    in your class:
    
    @par Example
    @code
    class custom_rate_policy
    {
        friend class beast::rate_policy_access;
        ...
    @endcode

    @par Concepts

    @li <em>RatePolicy</em>

    @see beast::basic_stream
*/
class rate_policy_access
{
private:
    template<class, class, class>
    friend class basic_stream;

    template<class Policy>
    static
    std::size_t
    available_read_bytes(Policy& policy)
    {
        return policy.available_read_bytes();
    }

    template<class Policy>
    static
    std::size_t
    available_write_bytes(Policy& policy)
    {
        return policy.available_write_bytes();
    }

    template<class Policy>
    static
    void
    transfer_read_bytes(
        Policy& policy, std::size_t n)
    {
        return policy.transfer_read_bytes(n);
    }

    template<class Policy>
    static
    void
    transfer_write_bytes(
        Policy& policy, std::size_t n)
    {
        return policy.transfer_write_bytes(n);
    }

    template<class Policy>
    static
    void
    on_timer(Policy& policy)
    {
        return policy.on_timer();
    }
};

//------------------------------------------------------------------------------

/** A rate policy with unlimited throughput.

    This rate policy object does not apply any rate limit.

    @par Concepts

    @li <em>RatePolicy</em>

    @see beast::basic_stream, beast::tcp_stream
*/
class unlimited_rate_policy
{
    friend class rate_policy_access;

    static std::size_t constexpr all =
        (std::numeric_limits<std::size_t>::max)();

    std::size_t
    available_read_bytes() const noexcept
    {
        return all;
    }

    std::size_t
    available_write_bytes() const noexcept
    {
        return all;
    }

    void
    transfer_read_bytes(std::size_t) const noexcept
    {
    }

    void
    transfer_write_bytes(std::size_t) const noexcept
    {
    }

    void
    on_timer() const noexcept
    {
    }
};

//------------------------------------------------------------------------------

/** A rate policy with simple, configurable limits on reads and writes.

    This rate policy allows for simple individual limits on the amount
    of bytes per second allowed for reads and writes.

    @par Concepts

    @li <em>RatePolicy</em>

    @see beast::basic_stream
*/
class simple_rate_policy
{
    friend class rate_policy_access;

    static std::size_t constexpr all =
        (std::numeric_limits<std::size_t>::max)();

    std::size_t rd_remain_ = all;
    std::size_t wr_remain_ = all;
    std::size_t rd_limit_ = all;
    std::size_t wr_limit_ = all;

    std::size_t
    available_read_bytes() const noexcept
    {
        return rd_remain_;
    }

    std::size_t
    available_write_bytes() const noexcept
    {
        return wr_remain_;
    }

    void
    transfer_read_bytes(std::size_t n) noexcept
    {
        if( rd_remain_ != all)
            rd_remain_ =
                (n < rd_remain_) ? rd_remain_ - n : 0;
    }

    void
    transfer_write_bytes(std::size_t n) noexcept
    {
        if( wr_remain_ != all)
            wr_remain_ =
                (n < wr_remain_) ? wr_remain_ - n : 0;
    }

    void
    on_timer() noexcept
    {
        rd_remain_ = rd_limit_;
        wr_remain_ = wr_limit_;
    }

public:
    /// Set the limit of bytes per second to read
    void
    read_limit(std::size_t bytes_per_second) noexcept
    {
        rd_limit_ = bytes_per_second;
        if( rd_remain_ > bytes_per_second)
            rd_remain_ = bytes_per_second;
    }

    /// Set the limit of bytes per second to write
    void
    write_limit(std::size_t bytes_per_second) noexcept
    {
        wr_limit_ = bytes_per_second;
        if( wr_remain_ > bytes_per_second)
            wr_remain_ = bytes_per_second;
    }
};

} // beast
} // boost

#endif

/* rate_policy.hpp
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
*/