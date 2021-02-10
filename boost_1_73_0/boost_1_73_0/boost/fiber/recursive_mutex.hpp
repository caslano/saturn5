
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//  based on boost::interprocess::sync::interprocess_spinlock

#ifndef BOOST_FIBERS_RECURSIVE_MUTEX_H
#define BOOST_FIBERS_RECURSIVE_MUTEX_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/assert.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
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

class BOOST_FIBERS_DECL recursive_mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };
    std::size_t                 count_{ 0 };

public:
    recursive_mutex() = default;

    ~recursive_mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( 0 == count_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    recursive_mutex( recursive_mutex const&) = delete;
    recursive_mutex & operator=( recursive_mutex const&) = delete;

    void lock();

    bool try_lock() noexcept;

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_RECURSIVE_MUTEX_H

/* recursive_mutex.hpp
V7KkeOSAr2HFqgoW1AyRmWbLkNMUbiVkjmP+d8Nkx+fGlBEP54W/n2scB5juwfnhvBjv1texzJxyijHineYGv4WGbVMqQYw0o1KzgmXGEonerhtjgnz/omahUO7jW2a/kBp5jJamhrnAOTY1apcUGn6mtG6j3qQvBQ4kkMLUCfvY1Rm7YHVdcPoWXbnTILHCaRC0Akw0iUZREFtTU6YVDtNuX1od75N7Ow48y+GF1VGj5fPvO8RhnOkDpAErDozwEP6x4P+8MoItn/Bhw2CzIukTwbGlTiaWw0IIZ8H4AAFfRGk7tYPThv3+zZvz11vvcnqgGrMYSe9c4rDt5olnSOVll+Q+flZRwpt6c/Sv5RSsLZ975/qB+9EP/GRmuXne/St126BVmHjJdBLCnRtMPWtCNe5a1UbopdENsAKSIAbKzZ9KbvcH0/AmjO7DNGrHzSghOWzcflZvOE3S6Cq99W6jycwcmyVJYYVTwrhqCqQkoxzpREkNqiYZ7QgyiD0P3CCOcBl9nMC35gEGOBFYqS+HcXyNCv6dm3imlFd+4G109kD2za3/AFBLAwQKAAAACAAtZ0pSfI3RA70HAAAXEQAAPQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRf
*/