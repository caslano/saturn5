
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H
#define BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H

#include <cstddef>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/preallocated.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

// class hold stack-context and coroutines execution-context
class BOOST_COROUTINES_DECL coroutine_context
{
private:
    template< typename Coro >
    friend void trampoline( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_void( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_pull( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push( context::detail::transfer_t);
    template< typename Coro >
    friend void trampoline_push_void( context::detail::transfer_t);

    preallocated            palloc_;
    context::detail::fcontext_t     ctx_;

public:
    typedef void( * ctx_fn)( context::detail::transfer_t);

    // default ctor represents the current execution-context
    coroutine_context();

    // ctor creates a new execution-context running coroutine-fn `fn`
    // `ctx_` will be allocated on top of the stack managed by parameter
    // `stack_ctx`
    coroutine_context( ctx_fn fn, preallocated const& palloc);

    coroutine_context( coroutine_context const&);

    coroutine_context& operator=( coroutine_context const&);

    void * jump( coroutine_context &, void * = 0);

    stack_context & stack_ctx()
    { return palloc_.sctx; }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_COROUTINE_CONTEXT_H

/* coroutine_context.hpp
hH5/lvrdbvQxUepjl3HvqI5BmpxfcIbmU0zaHmjz6aOB1N5eo94VEl/2lecXJNrnBi1Z6veA0d7lUnsHDZmsLa2RnO9xhuY1TNohY76LJB7IOSBn5VyHcW+fC4yBfV5nIVmB8l9/CFxRPz+T9dPMLRz15xb0oDeXU4j6QSb9U4wlxX4oLNU7ZtZzF2OszCrm+zKs23O45Pb8NkNtvI0671ECAFbPRGS588qCeYxvueY/E2ZM0H/ZVkRDwTon9TrBBgCi7uLx/orBc0CnqeM/5lYSfPllR+PaGa45PQzMq7+RPasw8O0u/WX8RTwjZ8vWjy+b3zihbpI3NpBRSXNky7mZXwP5Tn3CWfZSn9PtMEetH5gS7cxnBc16dOvTfzkKxOk2/fOZ8KVraHvGUSE+OwbrqOnUx8nnBmz2Ss8g2mgyy5ZVhpPVn4/SqxrfB5bqmPebzHK4ypzuYleR/nTZ+frPduBnHRUHYLZ91qwvVyh2OSY4vTb/41oece62/YIScIO2LK83y248GyrXL7uAOlkXUEduJ8dRXufCxpbj+ON+jToS38W1IW06Jtgd/pP/nIUs1DXC/D6NXtfjyDfo+g2mrK5qENKOz3UOeahOO/RCktBbcRmoI8ui/6MTNj0AJIjzD0g/bhP4dmJDuV87TSAfERc6FuN14zIfal5bzqs/riut1TnrtrKQPbmmec5Tbk+uE3I9K/S6OXbL8Yh2Mr+tJb/C8w8/dwiM1TCMevZWlPO01rWybXAVu8YzWUOTzUSubpckO1s7eI/bwSPTnkp2p5xH9Yx6ofw03rNx7vUR5jM0XDcmZp4zX9sZmt/qef1087v/1GVEeU79SLtxk//Da8Z7zptK92fpL5h2sj9EJWnN5LblCiGY8sZQTGnQZKxo0mSsaNBkXGjSZFxo0GS8Z9JkvGfQZLxn0mS8Z9BkvGfSZLxn0GS8Z9JkvGfQ5H0dgybjPZMm7/WYNBnvGTQZ7xk0Ge+ZNBnvmTQZ7xk0Ge+ZNBnbGTQZ25k0GdsZNBmfmTQZnxk0GZ+ZNBmfmTQZn90o4bON9NFMosn47MaL2KMo/xujWW44LTBat3ATo0k2vSk6JTsl3pZbYrznyrQHzSvVMd4/VO4NzXotrOsZ3qviGWo9M2ZLkGyeec3K7nonljgCzyH0OW89Y7dGfibOeBpOfsdv63K7qrsoW/C5l7YyXcJN7Q07ZzwskzPRpT986q9po5/C7KzAXraFT/W5LGdxKpQXaYa7lM7by2sjr0tji+vurPFCpvvTXQlJCWmG7TPpxoFvLqcGxEZ+ZkneXw/Mz9heD7GPBYbMXkObX3ZAR0WQJtvMAgubWWBhHwssbE2BhV0psNhDLrDQvQILnSq4CJ0qcnrsxpFhe4nPz/6u9pC8xLBwq33el5qdCzcHxnSc+YRdg82hbqGFDyi08AGFFj6g0MIHFFr4gEILH1Bo4QMKL4I/5r6oGT/5TU4l/mRUsDkxF9i2GW9ySTcegfDKfK5Dan90Bf63k/l/7ngoRJZdFnLrspBbl4Xcuiz8ussi3+OyyPe4LNbeZbH2Lou1d1msvcti7V0Wa++yWHuXhf93WeR7XBb+32WR73FZ+H+Xhf93Wfh/l4X/d4X6f5PWWbeD6NMYiSafJ3FZ4ASXBU5wWeQMXRbYwWWBHVzS+ZSljOUjLUiTz6e4LDCGywITuCxwh8sCd7hCbZ9J63ZtYCzPSXIVZdDWSTTpXIxJ62HUu0FqT7Kl0P4OfQ786o9IFniLSywwyvQK9sL8bq1fnwPGINuXlwf4zy8uDuY/Rl/KO3E9yQG0Uewe5MjSj6CwV+lxuOT3Jvet6Mc9+SQqxvt3XAMJICnvYYE=
*/