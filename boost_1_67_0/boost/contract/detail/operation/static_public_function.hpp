
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
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
*/