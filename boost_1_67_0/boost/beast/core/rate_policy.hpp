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