
#ifndef BOOST_CONTRACT_DETAIL_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DETAIL_DESTRUCTOR_HPP_

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

// Dtor subcontracting impl via C++ obj destruction mechanism.
template<class C> // Non-copyable base.
class destructor : public cond_inv</* VR = */ none, C> {
public:
    explicit destructor(C* obj) : cond_inv</* VR = */ none, C>(
            boost::contract::from_destructor, obj) {}

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
                    // Obj exists (before dtor body), check static and non- inv.
                    this->check_entry_all_inv();
                    // Dtor cannot have pre because it has no parameters.
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
        ~destructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
            #endif

            // If dtor body threw, obj still exists so check subcontracted
            // static and non- inv (but no post because of throw). Otherwise,
            // obj destructed so check static inv and post (even if there is no
            // obj after dtor body, this library allows dtor post, for example
            // to check static members for an instance counter class).
            // NOTE: In theory C++ destructors should not throw, but the
            // language allows for that (even if in C++11 dtors declarations are
            // implicitly noexcept(true) unless specified otherwise) so this
            // library must handle such a case.
            if(uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_all_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_exit_static_inv();
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


/* destructor.hpp
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
*/