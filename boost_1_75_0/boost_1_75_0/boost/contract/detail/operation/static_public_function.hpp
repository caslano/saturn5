
#ifndef BOOST_CONTRACT_DETAIL_STATIC_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_STATIC_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_inv.hpp>
#include <boost/contract/detail/none.hpp>
#include <boost/contract/detail/exception.hpp>
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && ( \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS))
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// No subcontracting because static so no obj and no substitution principle.
template<class C> // Non-copyable base.
class static_public_function : public cond_inv</* VR = */ none, C> {
public:
    explicit static_public_function() : cond_inv</* VR = */ none, C>(
            boost::contract::from_function, /* obj = */ 0) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_OLDS)
        void init() /* override */ {
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
            #endif
            #if !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
                    !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
                { // Acquire checking guard.
                    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                        this->check_entry_static_inv();
                    #endif
                    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                        #ifndef \
  BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                            this->check_pre();
                            } // Release checking guard (after pre check).
                        #else
                            } // Release checking guard (before pre check).
                            this->check_pre();
                        #endif
                    #else
                        } // Release checking guard
                    #endif
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~static_public_function() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
            #endif

            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                this->check_exit_static_inv();
            #endif
            if(uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    this->check_post(none());
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* static_public_function.hpp
b8H8cCe+nG6vw58Xv7+/NMyixqT2BgR2hEPdXXNoC1MD1ye6YOgrBhFoXfNHa7u/nTG4WmjBDXTev6Z6CsIdjM0xq79Row7zNldxbfNeejxbAaFdcRAQpQj3bkpAQ2ESzHY2w+uGUugpz4K6tAjwrw5E+3yLr33j3g3ift902kb/gsODkltP3RudJ2LvWcBrF7QP81eCD46n4eVVYSjXOQKpcvsg5ewBuONpib9fwu8sCNmfgqMmgsCufgT2neWANEMj6Cu5BxCugd8vLaG94ijaJzWjvWauBg8kneOAFN/VtZo3Bu11cH9y+wJ29aP4chD3/a171mjv6Yrf88z5XIBeBxmoMUZnQrXDkB6Ixd8vclfth/uPmgriy9GnpQBFaA9bFoOeY4s/O8x6n4OuGxJQqS8Embdd8fdLpV7+4X4hh1P48k1z5eqeN9l6dc97UwFmHSWg2/QYVGtz4c97uPtxexyptEsginjwRiuChKgX8HHZgIOeO/Q9b4JXDbhzYyE0FSHb5yRDZVoslKL9RF60/8gf+bH4mRc/8GGixe+pTyPQ/EocKCi/+uF+ngMWP93/V3lTS7fnh/tPCrnBF//4pb//4HIo7hk4HrixKCmEfX3/TPpH/fbD6jvc74H/leOfYIoOYeeXcsOq8loMBwcVKokx+qS4n4jR06/WXhPi8g8V1WptH7p7D9LE3UGOSaHEYBiQ5pcaOe4V
*/