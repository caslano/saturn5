
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_SHARED_STATE_OBJECT_H
#define BOOST_FIBERS_DETAIL_SHARED_STATE_OBJECT_H

#include <memory>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/future/detail/shared_state.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename R, typename Allocator >
class shared_state_object : public shared_state< R > {
public:
    typedef typename std::allocator_traits< Allocator >::template rebind_alloc< 
        shared_state_object
    >                                           allocator_type;

    shared_state_object( allocator_type const& alloc) :
        shared_state< R >{},
        alloc_{ alloc } {
    }

protected:
    void deallocate_future() noexcept override final {
        destroy_( alloc_, this);
    }

private:
    allocator_type             alloc_;

    static void destroy_( allocator_type const& alloc, shared_state_object * p) noexcept {
        allocator_type a{ alloc };
        typedef std::allocator_traits< allocator_type >    traity_type;
        traity_type::destroy( a, p);
        traity_type::deallocate( a, p, 1);
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_SHARED_STATE_OBJECT_H

/* shared_state_object.hpp
tidbk+cL2QcJiemE9svCfiAvgRQVsktcbH5PINdxUd5V+qskCb/eERS8AUSegmL0W9XPqEQ9FuQ3AlnTNNmMAauXpkIgtY1YcYO1stQice0ysPuBoJR2mJ0uVzklsEAClrSwF7pssjWi/cvcdoN6RbENC/2GKxdmk9d5gOCNb1RymhTBC0PSfvIRaUz73D5Qtl0pzsbJrCpFTbFwzUhzkX5id35zjY2icHrWd5t7qeJEk1lloimNoT0xgtX18FF5DmtFpjKxwZmBKBb14GSP482Oa/F0hIv/RTW1Zb0O6tpV47gZLqKsb6jnM1iVWyIXW3N1JNURSh6tZUbdGFi0XpeqtkQdQ5UjtD8pfRNGWgSntWO253jNP1XrYd+MxOsiTgEcZH/R8MHrHxkSKjXbQEyaQswZHPzLUOkGjbit+5sOa0bdTUS64TS8oV0KmoUgjKHrPsJ9tNFS4SoJ2/JtfD6csRP/DQGfjXvjYcJius3hSf9j/H4y7LNILVnYy36C/d7Y2lJJ18blK5dtOjyAfxl8udTpYLfM8dGBVn1RFbccL08iwtBbaAjVu4eQiMC8ekr6nfkC6O6GaTTr6akKaACHOBx2v+/94avEyTD43injLRUZvQ5pvWT/sWgpPSrxh3gwjN8MhoPZJYuz
*/