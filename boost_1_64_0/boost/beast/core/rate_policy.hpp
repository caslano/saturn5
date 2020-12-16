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
Nku1CKF1fruGup+2BlqB21lPdx9X0ZImVs5qMEI467XOVa+IBWUtcC8a9GrWBxVZUIaatJGaaJpnXXIN/be850Ld7Zn0o/K4xM3VXc805moJ1fAz4jlXW2IxVyu1mKuts5irlXnM1SLddBMmvjXpKIolDrzHe3st5nbN3nXXfR0CbaX7SqQvvGkOfDf6k5/fEePIP9jKNPoAspVrzNtd6ZLOCt3JYSPDmD5a6aZOC93XYacr/p3ED3JQVjF/Oy89AvsQ4/FmeoZ2TF+mzuAJ+ED4knN7b9nTwiWn36sjvgHmIMUu6Gqv0xvCH3xrk+zhM9gXS+1lj5IVk9/n2jDb4DvJX8vRRdthsvlwL3ddJbLn3+9T9rh0K842cZRh5LxE32CSPSzT7KNI+TmaWowTAJXMHvKe83dhmlYAC5hlJtnjXsZ2G9nziaRp64jXjJ5/VP2mfWHiB/ZJYahw9tmJ8ty9kBfBJn0Lz/Y26VsWSrrDpMGtQvuJ3FoSgLlCMOaphuwIXtAJsqK+Eloow0punTHy049DlirvNfy6TrWUWX+U+BhNZAefObGW85l43r04ACakrfHAQI/nsX3mGvnRLuGURz2FPqsP0Y57PS/CmGPLNw6lzyZdKxc6W6uDe9jnKfWojr4p30KGzTLLsErOYV5iIcNKLWTYukpkWJmFDNuu/C0ZPMjz/d9z961U/L6i3c5bahuiyXUtX7QdwnKkOSj9u4TCKxvF4lmqX0q1MMpTcovpw9Se9ZNC+1vyymsS18TrOxkVOipxrao8ryfCuY+Z7cT6uHyg8N1iQ63frcLz3ZJTc7Iz8zLSq3jHCo931D50vqP8toYgPoS/9XUMFg6r9Hf++0ra4Bu2gcGTl9IOrm8cXMe6HaI+dLVDn3h+4kren+lN7x/3of037vSh/fu1+/DSv/Hl1rcGTTbuv79o5tCdrb529Cj6snjhR4Xv/XT0raazmYQHE7n2sZf/xyI8z/+X8mymk2ocLPMyiWuEcARBo16iPfUQfalvuBF4G/UstwMnAMcBpwBTgAupFzxLveGX1Bt+RfrvpBvq4AhgFDCdeqBM4PXALOBc4HRgCTAHWAbMpX5oBvAwMB/4NrAQ+BfgIj4nyjVu4dgsEdgKoYFxg3qeaOp3+gM3A28FbgHeDnyYZ2GUAWfxrJoSnlVzErgN+Hvgr4AfUN/7EfW9fwE+C/wc+Bzffy9Q09H+wGjgC8BO1OdOAm4FFgBfBM6kfnc29b7zeMbNZup5fwk8AiwHHgUe4xk3XwOPATW876vAOOBvgN2AJ4BDgCeBtwJPAblPjnJbZIPXPrmGPKsjAhgGjARGApvyjBEE2ZfWnHqvFiw3DqHCo1w/hLYstzXLjWW+Pqo+lDE29VnCfEtZnwdYn5+zPitYn1KW+yAQPFHtPUPUk12SjszYK3R6EvRjCNGTg7TBCFmTfbox3+W7fJfv8l2+y3f5Lt/lu3yX7/Jd1b+uzvr/1CmXa/1/t2n9/1vu/39Dd+rF9wAbhqHs37qtlcnDk7sqCwDvdTKuwTZ8Xc6Moh9/VzmJak2oscQvwwlnB+xscZmnt9q/Eyx51pjW+uHMspD7o1X6BLWOHibpV3iv6/Ocljosz3m+GfOjBY5rm73X6rkuEyB5Npn3ECGf996KItM6lnnNy5z2tCutvAua1JS2t0faM1a2vTxPo7nU6We66/yOf0m+x3C6zjZVXoJHeefc/FjmqfXH7yXNL/RuXKM2/NY961wfLw30D/VrFhocEOoXGlI75IaQ4SF5gXVD/WpBiT49gPX7VvZRzzDaTJ6D91B68iVV2LWnXNJeC4MXar7XoshjreaMcU/Kw/fgvXMWa9APvW4=
*/