
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PREALLOCATED_H
#define BOOST_COROUTINES_DETAIL_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct BOOST_COROUTINES_DECL preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated() BOOST_NOEXCEPT :
        sp( 0), size( 0), sctx() {
    }

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) BOOST_NOEXCEPT :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PREALLOCATED_H

/* preallocated.hpp
+bEtpNTT5hUTbb0WRQ7P8KW8orHdT8FylWDnE4Patxi1hHQc+PxwKoRj3FvMOENUAZKOnj1V393lb4HRDW6jT79+efGnSnMZWPx8VR5aU3E0d/Fr3UvLkGsO8RioJfawqHDspyy1af+rkI8ks0w0dsAgbFK5jBbmwMLG5nnSBwoFlZ+T9mB0VLmdvvk0arf+ihtZ6RPXJHIjMrM/79diFyQ9NJdWu4W33eNKCJFHuyA1TnFcRiIGlDopYJ++eF9tCnIbz4TPVvyNdq+fLglgd8FHYKT5cf0ZHwa7Qh/CUs3i5EZRDz4xiTIloKtHHaClsi4MeBzbYV4E/iLjgjpkqpQAwOt1YgKtIo1c2k9ZMAnmuzfGNN6Gmsx+6KqDiSC/id3z6kGFKYuRGo/nwB7CtjsoRIxCSeoM9MAVfzoyKf7AueOA4okidQk3iFhvFr6Lgoqvlv5KnviTmyFyRxNlS75M7cl5pb4zPhnSaxzMt8Ad0RQ3Ae8vId8BhX+AG13vQIi6xZwZPXn1Ml0KeEYmEVPCd49PY4Y/QSNtuKkdiBoSs/gHhN6G51cqR5Ra6lb8VsyNkWfLDZIEmw3tPMLF16voq7guSJlhNXYFrD3aG7gJ0GR7sEiPWx7pAUpAD24eTSvhIib2qw7/tR7DHuqv7LWxt0sh38Qce065gvixJV91Y9+VuOJtlLxBP0M6cz02wnRqeRwLG1i78rF/
*/