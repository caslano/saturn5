
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SPINLOCK_H
#define BOOST_FIBERS_SPINLOCK_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#if !defined(BOOST_FIBERS_NO_ATOMICS) 
# include <mutex>
# include <boost/fiber/detail/spinlock_ttas_adaptive.hpp>
# include <boost/fiber/detail/spinlock_ttas.hpp>
# if defined(BOOST_FIBERS_HAS_FUTEX)
#  include <boost/fiber/detail/spinlock_ttas_adaptive_futex.hpp>
#  include <boost/fiber/detail/spinlock_ttas_futex.hpp>
# endif
# if defined(BOOST_USE_TSX)
#  include <boost/fiber/detail/spinlock_rtm.hpp>
# endif
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

#if defined(BOOST_FIBERS_NO_ATOMICS)
struct spinlock {
    constexpr spinlock() noexcept {}
    void lock() noexcept {}
    void unlock() noexcept {}
};

struct spinlock_lock {
    constexpr spinlock_lock( spinlock &) noexcept {}
    void lock() noexcept {}
    void unlock() noexcept {}
};
#else
# if defined(BOOST_FIBERS_SPINLOCK_STD_MUTEX)
using spinlock = std::mutex;
# elif defined(BOOST_FIBERS_SPINLOCK_TTAS_FUTEX)
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas_futex >;
#  else
using spinlock = spinlock_ttas_futex;
#  endif
# elif defined(BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE_FUTEX)
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas_adaptive_futex >;
#  else
using spinlock = spinlock_ttas_adaptive_futex;
#  endif
# elif defined(BOOST_FIBERS_SPINLOCK_TTAS_ADAPTIVE)
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas_adaptive >;
#  else
using spinlock = spinlock_ttas_adaptive;
#  endif
# else
#  if defined(BOOST_USE_TSX)
using spinlock = spinlock_rtm< spinlock_ttas >;
#  else
using spinlock = spinlock_ttas;
#  endif
# endif
using spinlock_lock = std::unique_lock< spinlock >;
#endif

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_SPINLOCK_H

/* spinlock.hpp
tytr+hdRFO+yQtFd/bs82SE6pjG3D4mZ6E5KEdQhf+yKVI/dJ7OALGW+RjhD34/eLkrldDK007Zemcqt5gbw3ZbFkNO3aHNTy6zHx2jfsv6ZfF8RbzXdNCKtQdhCPiJ2kI4KVQArWXdDTgWQQ/bdfD5C/CEmk+ei/fcN+m494yYJdHPW15womg5qndOibRfVBdMkczKODBFp5b6Okl3bJVu/JUahFwjEsIORWpbaEFYNlbPlXZbtyiKePYGT/09ULijCP7+qJ9LWnRlP3vh52r2uw4vF+F8C9mYCRT+ql9rwWhGYK40QMS+Defy9c7jny7LIJZCdjfxMykqQVrocROzvDXNbGGNK5SzryIAKSnkZUvCKNMuQYY9p9d3rdJ/szGeRdsnvAOl0Ea3JRsDH96J+uGkWKaG9YqKwuRyA7jlEidt3ERY+vrQRFUj/AZUApu5SGNYD+pQS/temdo75Q1CWszfrWvmHuWOrz+awLzIxg/Ogsjgtb1JyB9ZEnLhLM2wmGk4XHdK4Bf/8CG3JppFz4Id/NeIaUgmMrnqX/R7y/G6993h9WlWf9g==
*/