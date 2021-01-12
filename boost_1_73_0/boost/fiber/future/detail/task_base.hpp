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
sbgJyrg2/6uvv75X3MT6zLNozfwz+rXPjBP9obJjYS49Ty9inGJXXzvbhKt6igM6zq4sqChcUmTi21DCiDf6XHeK+WNq8QLrWmu80ec6X8JqJHHsTBwbi7sbbTOGN2Uf1r04QtzM5fpBZ1dh0w+nabyyCas9YY0RdyV2MjZtqeGyt6TU8fAMTugZvCfunXZ6NKX6/Xc72TOEvfwWopY4GKixzy1jkjr3ndkdK2Wj+allw7Pk
*/