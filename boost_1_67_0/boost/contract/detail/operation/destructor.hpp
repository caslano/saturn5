
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