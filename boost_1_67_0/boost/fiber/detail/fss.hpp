
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//          based on tss.hpp from boost.thread

#ifndef BOOST_FIBERS_DETAIL_FSS_H
#define BOOST_FIBERS_DETAIL_FSS_H

#include <atomic>
#include <cstddef>

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class fss_cleanup_function {
private:
    std::atomic< std::size_t >  use_count_{ 0 };

public:
    typedef intrusive_ptr< fss_cleanup_function >   ptr_t;

    fss_cleanup_function() noexcept = default;

    virtual ~fss_cleanup_function() = default;

    virtual void operator()( void * data) = 0;

    friend inline
    void intrusive_ptr_add_ref( fss_cleanup_function * p) noexcept {
        p->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    friend inline
    void intrusive_ptr_release( fss_cleanup_function * p) noexcept {
        if ( 1 == p->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            delete p;
        }
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif //  BOOST_FIBERS_DETAIL_FSS_H

/* fss.hpp
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
*/