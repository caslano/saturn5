
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
# include <boost/coroutine/windows/protected_stack_allocator.hpp>
#else
# include <boost/coroutine/posix/protected_stack_allocator.hpp>
#endif

/* protected_stack_allocator.hpp
CnhZAc2TDPKQUNifEmKdoAP5ndE+irRi03eeoIjLrp2XLhY8anSrTgxECiwJDeI7eRJ2nYnDQ863mWsK2qFGqNwcf6V4E9sIr0suKKh4BlFgh32kBF4r393WFmGB2SkjUp793e3b9hDqGJ8PPpTLzuGooWWEZLQXEepbL5r4tkola6q8r5Yzz8FR1YWgr+CG7Qs+vdEJjHv7NRs06/31/QnX2eBL6H24FZpoxPMOm+6r1RjipwuC1CfsaW8V6zUZlI85X0gko22x9Pj8W7VsOngcfzL0MdKzRBLD3EaIPWzJ5L46ZH4+qhGLtDcQVUSzjsVEeuVN9MKRXkdqauX3Y9YqjWRRunmY6sKTHgq6LKPeNMDuuPZPcprsvcIvMhbibkNZlfChDDdA4ccxy18lU8kmEUoUDFxO314XxnkCqMjyhqMNQtoN4Y6wvT66k3uKiEZg1l+1zf/1Iy5Jr7FnaYdJAqRAEH2u70yP+dOpq477xBTc+MLLFuXgOl+bcXA2BzQpdwOU27C27r6V+E6ihrFEVcDuVRF0KsQEahz7BXfsQbi9z5X2ZcfAVw==
*/