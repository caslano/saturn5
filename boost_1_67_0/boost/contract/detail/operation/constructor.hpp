
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