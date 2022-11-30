
#ifndef BOOST_CONTRACT_DETAIL_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_DETAIL_CONSTRUCTOR_HPP_

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

// Ctor subcontracting impl via C++ obj construction mechanism.
template<class C> // Non-copyable base.
class constructor : public cond_inv</* VR = */ none, C> {
public:
    explicit constructor(C* obj) : cond_inv</* VR = */ none, C>(
            boost::contract::from_constructor, obj) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_OLDS)
        void init() /* override */ {
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
            #endif

            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                {
                    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    this->check_entry_static_inv();
                    // No object before ctor body so check only static inv at
                    // entry. Ctor pre checked by constructor_precondition.
                }
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
        ~constructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
            #endif

            // If ctor body threw, no obj so check only static inv. Otherwise,
            // obj constructed so check static inv, non-static inv, and post.
            if(uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_static_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_all_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    this->check_post(none());
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* constructor.hpp
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
*/