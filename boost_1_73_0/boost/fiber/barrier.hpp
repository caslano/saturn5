
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_BARRIER_H
#define BOOST_FIBERS_BARRIER_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/mutex.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL barrier {
private:
    std::size_t         initial_;
    std::size_t         current_;
    std::size_t         cycle_{ 0 };
    mutex               mtx_{};
    condition_variable  cond_{};

public:
    explicit barrier( std::size_t);

    barrier( barrier const&) = delete;
    barrier & operator=( barrier const&) = delete;

    bool wait();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_BARRIER_H

/* barrier.hpp
rWs9zQ3pxkKyatZHoyOLdHCuZjrcupEGqs7/voiN9EFu5hqb08LtZGZJ6awFBRWVhWjfKJxVHKHDwbO94D+yvcyeV+E4L5pVSYM29f1+cdfIq72YMKTuS3k40Zll6uEdcr6j1Za/njpdtFx+Ie66WU155gzN4RxIr7++pbCugYg8j0iTex7mGZ2H4ZtqCXcc3JiKv6RwvqrXyPw0eoB6iduRdkvblvkT4qL+x7vzGjtPvaMm
*/