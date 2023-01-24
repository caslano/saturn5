
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_TIMED_MUTEX_H
#define BOOST_FIBERS_TIMED_MUTEX_H

#include <chrono>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/convert.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class condition_variable;

class BOOST_FIBERS_DECL timed_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };

    bool try_lock_until_( std::chrono::steady_clock::time_point const& timeout_time) noexcept;

public:
    timed_mutex() = default;

    ~timed_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    timed_mutex( timed_mutex const&) = delete;
    timed_mutex & operator=( timed_mutex const&) = delete;

    void lock();

    bool try_lock();

    template< typename Clock, typename Duration >
    bool try_lock_until( std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        return try_lock_until_( timeout_time);
    }

    template< typename Rep, typename Period >
    bool try_lock_for( std::chrono::duration< Rep, Period > const& timeout_duration) {
        return try_lock_until_( std::chrono::steady_clock::now() + timeout_duration);
    }

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_TIMED_MUTEX_H

/* timed_mutex.hpp
y2i/sfnA5eD7/OByWb7kmgUjyxcDMtl4tJNRBX6hTpru7QigzhkSbCTPrFb1/1YHWx9nU/uyjnvuDbA+DLp8A52cCgsQ6OSqezsi6ng9JVj3v3K3iZvgE+fkUUXbbYHinLx3T9A4Jwy8LhDk5L57OhLk5MTgCwQ56evW0zqf2A+f/9Au7Jyc6w87BboAJ7WjgZ1pnOsb4KRybkcAZtjgYHEg5pYJgLm9LEjMiova7/eNAfqdqwXdGIYH0aPK6JdifINunJ/TkZ4vHxSs5++sEj2vWEWxijzB48vc9n279OSBOUHjbjyYqwtuMqZDfT6QHKzP51cGmeOt/253jr+4u905Tudz/O0Lbeb4ybs70t++Qfs7bqWY48yVOMdNcvA5/uO7duc47u5251gENvnhro50+a6Bwbr8VGmM1Oa+iys5Z4v+kZIzm2aVU9bkhwV3EfLL0ZBfDmOWc0yl/UMksuRJDFEvv7iUTgj0PELBecRdeAs2KV9Vcq70wC0YlRcXYSS0Ue/CNowWd2HF6/EuzKTdhdXhXViL/i7s/Xx27j5pKttk0N3FFUFfyrgoq8hr3ppPHSnAd2Wwh+7iirQulOm7MDlTdEHqSBdSeBcu03chly4UQb3Va07j7ReRuus7D1P7udpdYIHa+EUWdfzrOjL+O6lxjJguji8UDoRr9z8j6WRga+/kDBXr1Xrxm83Qqjt1uuhec9GdAXX1
*/