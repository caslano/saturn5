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
QOIANLVIm3pXnrigNWmrFWFX+J7VaK/OfEavavirKu3VN/xVFX8ljq4opZTxh5WECETyvHtkQgQU63RUMkMEjL57PA2RAWCBzF9oH6fza9ovCSE5g/S0DIVMieyVo+5Qso9DmyIX/FcKAV4g1DZt1yzW2epomlAZlpKLHthR6ZSrNbHD7GqaPYkXYy0DG5BxiscOrqZw7BEcWOAeoCFS1LdDfTAT7BlJsWXAVR/TRHbE0MgQn9ifn6z81JBAUXowihhjMNlTm7KnQT2YC+FpscOfl8ZTYdUoK/EtHjTFwI9SAtoPeSJJChwugjz7IyeB/s0nkufR6gPumatw3HNEh3sadLiHZAGjGO5ZvBtxD4AFBNPphbFVo7dohq5ShMZ2BK27NltNIkmkM4vCb7rRes66bzNWQp80rJnIa1KK1Od4zdNYkzI6Qk22ZRaJmkFe8xtORUGZoPUuXtOk4RwdfhQpJHX4ER9x3kz5OIqjyIfCaXHS1cQQORxZ8pK7bISPisJJRJCpvrmzO70Zxt/kqG++429yIHeDd2YfszsBLhGw2dmnAA4CndVbKau3O9ZendcHYMu+NS8dmeZ05QN20IXWHp2aCfACtfmtlHWJoXZvymmmeNTaiVS7PbeWZGwxVGf3rHqalJVlqH49Vs9RbjyegGF7XQ75Bc6w9KzmXFJ5GNEUPCkHhGuSiGfRCp/dygvni8KjBS/UZPnt
*/