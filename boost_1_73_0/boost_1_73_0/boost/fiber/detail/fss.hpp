
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
ADkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1BST1hZX1NTTEtFWV9CTE9CLjNVVAUAAbZIJGCtVm1v2zYQ/q5fcfCAwS5UuW0GdG3aYoqjLF5sS7DkpgYMCLR0irjIoiBSSbx1/31HUU7iNEFToA4iykfe23PPHe2sevDip30sR5uD737i9j+mD607paAWf2OiHleI469g/khxReszXA3hTutrPIBnaX2FfqsVd74+6Pc4foa7lQ5SP4ZaeRXrV5IYzU5/JKptzS9yBf3RAF6/e/c7vIQ3r968suGYlRwLCBWWa6wvbPiQtpI/cnZz40j8ZAMqYIWzZzDKuQQpMnXNagR6L3iCpcQUmIQUZVLzNX3hJagcIeMFwsgPluPZnzZc5zzJOztb0YDMRVOkkLMrhBoT5FfGTMVqBSIjC2Q/5VKRzUZxUTrkHkFhvZGdGR0EK6QAdsV4wdbkjinIlark++EwaeqCMhmmIpHDZAeFk6vNg6yWFM2GbUFUCpSARqIN+rwNG5HyTK8EEQmrZl1wmdt3YZHDMh2KGiQWRWeOVDlKkwJC2KFl65NQUfRc6UWKUmpv17nY7B0kWDtDWVOX5I5goXOpIOBtaMoU6/Z8C8TOS4dyC/l3SnYX
*/