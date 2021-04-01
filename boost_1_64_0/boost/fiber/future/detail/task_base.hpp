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
RXPf4oeu2bJSKjykwLTjbKKbHsdWsBX/NmCvFSLWWWk4ribN+QBRiHKcjbApWM8cAINlkXO+iCAIJR7WuKm7/yayCPm1fxd9gAkGJBM7sGmPkZrOZC5Aoaj702fWXSB6c9I60X45SKvqlgo/OpAepBmODSAFGu/nmycaIG8XRivgbEi6C06HZP4cacYoaGbCcME7PDgnNo4BrKL0PWFCqavcrQhV+TBMSG4mOvBCedRnnfTyicCDpU6fTeCoNZ5LAFS2HzFHAT/DNPZu1WJXiLkGK3igOEraDe5TceLDiB/6e6PZJDxVlJPMT0Z6GFu28y+paiNYrsVYA0qNAWQ2qhmYvIdEz8rOBbBPPU4tRJI7pZ2Kbm9sePho1cXPiNsafAZyt8ezNMLTp39iQwkHIuPR3WyFYhEhOGyMVnr5IkNoBaLJsLpzm6iuAcbOVSBwqwl/yRr6ahLxm+y/RR1OVzwNaUGkufOL0wOa1px201zmzCsxoKDgrUkeP7PmIu/OEHQnFx385Zdnat7KHferFhc62e8xjMPXxOau9xpxc4/0rzuo6En+pv66QA==
*/