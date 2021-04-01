
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
ZehbZM6nJ303nL8SvZOsyxCqL9SHCkZBvW35V4t9tNXQ9agTVg6EmbBaN4vnSTguMgVR/zoaVBBK8LwAlla53jI7V5O4oUZwcX2aZLFkbTy3cVgmxrmbb8yHRNqLp6CCEasvSfJtkc5iXJjXLyS8lLzOw3kG0Aoz/FNO6MebAlKNPoQb8X4dZ+8BsfPQaEzS3/8rurWa1rKFPBH0thsvMw8hzOj36Z1ihpQawr2EJOpwW62zjsOxLhFY5Bv0fekNyq9xOE9vW3co1dDp6v8iq2RIfrSSFnpgEaAhsCTUUuP3PLLH3QzcxICXfM2EHsaMaDaGkMsdKF7L4kwbGHz7OiramCeFI5eXVWf5OLo2v40d7YP4P0N5gW+oFzYzvKN0exKyj1alb4nrIg4BCB+DDWCvUbxB3zLd5malqj6OjKbXhxuhoPCi/RnHD4dORxRE61f4dR1iVmtf8L1JO2ww4FW40C1rB1S8gQKUtidk9YBTCSQMlBZBr2O4e1x8D2w2RcXMIYTMTrW66F2WWDMQImKfQUafurgZ5vkoy/+K9S0ytgGPezE+91n3tQ==
*/