
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//  based on boost::interprocess::sync::interprocess_spinlock

#ifndef BOOST_FIBERS_RECURSIVE_TIMED_MUTEX_H
#define BOOST_FIBERS_RECURSIVE_TIMED_MUTEX_H

#include <chrono>
#include <cstddef>

#include <boost/config.hpp>

#include <boost/assert.hpp>

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

class BOOST_FIBERS_DECL recursive_timed_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };
    std::size_t                 count_{ 0 };

    bool try_lock_until_( std::chrono::steady_clock::time_point const& timeout_time) noexcept;

public:
    recursive_timed_mutex() = default;

    ~recursive_timed_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( 0 == count_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    recursive_timed_mutex( recursive_timed_mutex const&) = delete;
    recursive_timed_mutex & operator=( recursive_timed_mutex const&) = delete;

    void lock();

    bool try_lock() noexcept;

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

#endif // BOOST_FIBERS_RECURSIVE_TIMED_MUTEX_H

/* recursive_timed_mutex.hpp
8izn1tmUl7cJ03YFvYc2wYw5ywPm0NQ1E7wO2Fei0gtlIKvt0BkBMQEfDcAxsr3pZr5UAGPSvnZIuxOTPtyO9Kk66SdfyoZ+L7JhzIhmH/xKNq7ls89akubYUqTSjb4AE81+FzJxKYIFfoEF3LJAkfFtgex1tHAg5TO9Qiif7/y0yqe8/+tEkojv+DyBWV7vofy64S19yFoI1QhEs6OiMasztqU+iOnYx3qiWYIWtzh4egtwWK37xlk1sG54CAtV949mbwQ4lHkoy62SY3xwxL/gzx7T587cJD7YP4JyFL1EGDk+LEN5fTbYOKIouG2ER5y7HtHfSevCUeO9DsjxkdyGTvFFszOQtRGOulnA6cVQpFQWASCE1Ur+5aVYyWIoeWg8sie1IvtDkYPjiyznIuAH3g2P/I5wBF+FntYCDoze4DEt09OCm3dGxc8brHt/JxhQjN6qjmJAH5FTikChM3MI5YmA8pgRDm/dFmA4PvwET6+xyxMReVloBARl3Rz+AU15Pwqu/HWzQJGcHhw/wt8+PwtGmvjxWIlirfzkGwiZ+OVtaF4DNNHAJj8TNEl/R3XPYN0sj6M6HRqvy/mi8TyYAm2Fl4EiOu8TItLCUvF6iseYhKbFJigYQARo2B4RwFX4MSMqrsgBghXQUB4oWW7s6gtcQ/JUVB4Xo/D+Cs+djANb2kECCZQKQJ2cLgE81AT8KACLhIXZV4bSHSKtKpZ2DmARaWMhLdKDfSkw7TnYtjcleJ9w48HUNGC1HBjPj2AbiGaDlHwoURQseMmInIGriAnF53Sqf+ztv5h+2QAjgTFshJpoBp3IE80UyKEpnyWKQiMsggzS/dc6hVVviUjohnpBeDmdYJ09P53OXSP6kNdqiT5PHC9GjDR9FBtdpndTk0VXGMLF1cyhFujv8AJTRWoYNyFw5EIgAjlEWBLQbuLdWJp7gjzWXnWU5ChK95g4PGRnFGnSgauokV55irkEqKiK1ObNlU/wb1YmQ7JPAzlyD8OeRcoNpoh90TLEBpa3LU7J5JRodokcdVHRwEPTFcKLI4e8OHJEIeO8wWKvxORYy+z8XOhN18IbG0TxUeYjytRwMQYoQTYI32G4RKILEdJFDamfh2jPF74szX3e08Tc1+D+See+ZH6abK44Tsnm9SdYZTPA195oYy7JjhK+aPaql2IfIFr1MxuJkbsm/eD/MoLEfiDCd4/xxkS4JcMaYmIHqjhzEIQpDQFKosfA29yZ9LdWbKDhE3s/5NEGGu2qD8Ys/N4xaagbJO5jikWLGy8vqC2yiNaQF3TRSuO99Z9Zva5xG5IEZYK6pTeaXQPQmsx8l0WRHEh1L8SJQnAcUNck6JLz5ql7VnJIPvzi/o9iWsS4c/nUn5icqnLmDsOkOVf0MR0FDLlzwVjtzo28AU/eLTsHgPLjb7cSfP+MXXxJJ5FXl8dAr2ygwBWHeTjcO1ioHfjd1atghR61Es2tHvRTTYdvlkxhX2cK+5MvLBSGJBgNILpkCvs6U9ifZGHYb/OoNLqKwYPNH0nXXoQ0e6+dKXdcxlLlcsWzlIax4oXrlEuUE5bxJVHG32EZlMJ2mMgh4IRlfEmU8Scsg2MPclhgPm6TQ++aoysWaixz84EsJ5bCBBGhmGbgJ4ZpXpPgZVSsRreBfHVtg5OOjRD5SsyEU3Ud5Ps6yPcnzGduiRty/24PW4C5SZjv6yA/MTfhyeTjlP+Nt/4dF0kqhsZfYj2Do/sc4FeRBaUnezDagk+4A93Ve/XPpQtZENTm+k8/xHtG1u3fj+4ZkZ+6xSoOmhi0JCFOLUmIpblMhwWIiVyVl0THakmig5rL6AV2q5y/NXSfnLfHDTeFcpA=
*/