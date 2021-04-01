
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
yhxbWZlNxdDWvGt1Tox/etMfTWZslXa/CI0YhNMmO8YtmATO59Vau0T396Lgr+2cY+EQ06SD4vYjyukLbtivEwfqFkPt/v7ZwLDFapsco3gilg6Af3hPLWPkKuOByTGM480Yk7fakbm17ek8yBysTTwVrYmgBDWNuwd/WY7FrJ8g1gXrOdkt06OPPfZZO6O4OMtSUDC1x9fRoisyfENWaA3xGSUXqbxoP6QY1Ji15Ewop/AK/fII9qB5DRwq7MmuCg/GFon2kmaTa1T32ia3hwgY9biGWPPJCI2WEHGl0w6yWSrDGPsDhxyw0/NZt2z51tfPe3tvjNOJX6BfQUrgs8715ypIYhYixSIJaenRSBJJwOF460s6vr4qoWSxCWakL9Rc1VgNeOqvH/QnOls7ZK6oscf67YRg8c5JmyXwTwUrYzsVXqEOTnc/SauwRphU4MD2c/FgNMkIiL9gZtJqS6mj0nckQn4LlAIy8tVfHFEZuRqAzhRMdK7Bba2EIt22RNS81lewCPWPXrFZ84vN9b7+zqnCVEvay67wwyWNRfnccI5MCgcRjuIzwA==
*/