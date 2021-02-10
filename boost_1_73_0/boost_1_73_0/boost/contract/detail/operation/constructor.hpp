
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
FIjzvvmLrsmIlvvu1HAy8B6dF+jB/3lO+Kd60mmhEJYSwS1uIHgXjsPkzgt2x3Ylqw2xsdPs9DIaxja+m9WxHeZMPxApeCRSjqqzYTKfTeA2GM+H3swiqHcgd5Q/mO+6rWtFY9NJnFs4n1xPoveTNLJnGzJCiXTue/FwCME4jvC4+G72EKwkenxO7OFZxIfeF1Clzn20zvsfUEsDBAoAAAAIAC1nSlLJsi9EbwYAAK4OAAA/AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9DT05WX0ZST01fVVRGOF9GVU5DVElPTi4zVVQFAAG2SCRgrVZtb9s2EP6uX3HwgC4pFKdpNzTd2mKq4yxaHMuz5HQBDAi0RFVcZVITqbhe2/++O1J+SV+WYpgDRzLFe+Fzzz2n/rwHD/+3j9cnd3DvJ7XfFD943RhNGvUnz8yXDdL0A7g/NJzj9RtCHcPO6kN6CN9k9QEOrFXaxXpO92n6DeHmlCT9OybjeUq3uOIsO/uBqteNeFMaOBgcwsmzZ6dwBI8fnTz14YxJwSuIDZcL3rzx4XluV34p2bt3fc1f+sANsKp/x2FSCg1aFWbFGg54X4mMS81zYBpyrrNGLPCHkGBKDoWoOAyiyU04/tWH
*/