
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_DATA_H
#define BOOST_FIBERS_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class context;

namespace detail {

struct data_t {
    spinlock_lock   *   lk{ nullptr };
    context         *   ctx{ nullptr };
    context         *   from;

    explicit data_t( context * from_) noexcept :
        from{ from_ } {
    }

    explicit data_t( spinlock_lock * lk_,
                     context * from_) noexcept :
        lk{ lk_ },
        from{ from_ } {
    }

    explicit data_t( context * ctx_,
                     context * from_) noexcept :
        ctx{ ctx_ },
        from{ from_ } {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_DATA_H

/* data.hpp
J0lTCFwtScLVskzICpVBOebZpt/8WUTRPWjMYx7IFdBSEds4Em1Y+y7EM0cRz7i6m94/nrYk0WbK/Jo6jl/uv1b9Ugh+UvVAk6EmZ+iTkzgsFV6L14erWYWr95AGHFuq7v+JldToQuQEdQZQox8n+PjASFD9uiejvucxxihksalclGQrvkmCALJ1yvgxMPcmwv/o6R/Ok2GDq5oH2eSeSg47FWSsbi1jHzZ3Reloxmo8uI1NIvEhB/GimIzV6JHdBnxODslOxdr7xEMg+akmGQIZ6vQKIRlqBQMq2W7EwInsgJKMuHu6EF1FOdzpOrf341TJVQNnd7uFYOzNFpHnyW7hS38aD4HvAz7Os7pvdGDQaBTDZq3hYti3br2gGPa7q1EMO0PILCaxelRZkMecvVaTwmJUNRmMBUEKO6qIS0OWNgqhKWQZIBBKeZGBeg+G+E3P4m7Anl23lvfMfOGejaGezRI9m+zbs+NrtJ5FY8+4RSF0buVyjtZ8+idMDrGLlXyC1yJFmp6kOenzLMsSDkGiIGypxbShCo+y44yK9f/R9h3gUVTb47vplGRDkoUYEBaNEMUSDGpiRLOQwKxsYJFilBYFQlTQqLsQFDC4CbCOC7HxUHmKFXyPp2ChqRCKJPRQhCgW7BMWNKAiTfZ/zzn3TtkU8n7/7/F9YWZn7r1zy7nnnn56JZjWZZvIQtQfe+HtFJNS0ZuSXQuZ
*/