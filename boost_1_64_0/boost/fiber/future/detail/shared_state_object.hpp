
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
sPtg+/psYy5VHba5oI1lwWOktrVk2qIJ9kIFmhFQoJ1GAFZtXqYKQLJWeWrmGVSPumNMdqn/WvOm+p5ZJ0EzjwQasUIsq2TTlgBJGQk51LxHB8qV0OAAku2tUuqA+FdiCDimIrh7kKhTmIfGtDQGfdOuzI2BSPOjGvD02GiFki0SKs1TSYe4QnAs6btHU21j3a6Eo41xOVUmTbz99/CGQZBXbpB6ccr7VcOFZ5XUDjx2P0mbV+cDMQrHAgSkJiWDdoW4Qr/JVAZknU3V5SGYy5+N3QWZ4ke0pFFN4N8VT1Yn3ni0insoLU9TLuX+Z3JW53hIvuWMdatzUKKeuZ7RW+HPySGVaaJCaEcieFQzE/c/fU2+JAuBRaUcGfrA9Spf+8Bal4INQkukj4LXkFzl9CkeEKj9Ugd/YSXg4lQJbCzFdMLX00Ewg6RhteVg5KTvkUfyp+3vjPHSlFfKmTlfKLJO7FWcd0aGg8HSpApY5q0b/pNR/gUiPYbmbHLwdZzWzARuucBbyysrDo7EeAVSW46bTGESzhzcwSGH+R+Ao0XECrcsSbgT+JJBVg==
*/