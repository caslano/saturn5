//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_TASK_BASE_H
#define BOOST_FIBERS_DETAIL_TASK_BASE_H

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename R, typename ... Args >
struct task_base : public shared_state< R > {
    typedef intrusive_ptr< task_base >  ptr_type;

    virtual ~task_base() {
    }

    virtual void run( Args && ... args) = 0;

    virtual ptr_type reset() = 0;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_TASK_BASE_H

/* task_base.hpp
qSVtZYlyWvvTae8FYNcrnKnyuDvhuOWCU3IbmyrjShfQPN+BAslWrndrubpbS+e3FUtTJWUxPL7MXx++ZatbqxcrZafeqNEyD9ODdtZJJnR9MJFc62RNzYBNb3C0DJNPlzK7/WuLFIVrAixgyEmr9oiRAp3Pbp+VgZ03Jut9Ts1t1PLleqnYcNA3XeVLcPtXsHoD3zwCBmONJNaqJH0VxD67/cU0Ezq/1AmXXu1SFC2bGB+vufW6UTPz5Y1uHQQ=
*/