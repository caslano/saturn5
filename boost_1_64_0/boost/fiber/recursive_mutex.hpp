
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
ZNYCpXHij7b0Df6STgM2qM/Kdybe/YwDjDDwT3DC3I5/Cnz0JoKC7d+1D5FN6lHcTBeVkfV1r3u8TAdqIm0qMvpexegpKuqah3L2im+raTzLe5f01c4pQLRTnn5YdmxVAHyouLGF+efwNolJck/uj00kdmIEfdMDpopE76Jh05iudZ1bjkiO7T6DWtvmGg8uNOGEjVtDLG/6PiBeGj3p453HBimc01zc9WZG0bSXfRL7+vB7XQHlqO05/k/SYaTUJ1YpqVL0XB+bWjQ8oerSwn9HOfYnRJyY86tH5+fF1izhxXo0kzFrjF4PmXeqzclatFybeuIius2hiPPhqx7hin6peB9DkihPU8RIrdtN8MiQbZFn4ocrO8AJITXKq4xzY1AstXBLNhHZd07qo1T1dD7XLbPiCnM9pZm7YHoJ6vm/gqOH57rVTUHYZUXg9jK03/oNdG3CqLEA0/rkNTS9bb2F5A3SO9ClVpZ14BxC9zCRW0cUkDKjMJbFegnmTJilmSZUq3V953HbUDcnP9tnVoODVfkmzbwEA2+BlvIdqgg89Bvf5doQN1w2Sg==
*/