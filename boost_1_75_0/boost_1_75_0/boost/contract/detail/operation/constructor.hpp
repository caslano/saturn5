
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
XTHI0RWEkIvH4YYCPxjK8L80kuXX+5/o+47dZb0EK/XZxw4XwOMaG6hdYwQFLUHw1BaAYt3jkKfDDzeVeEFfinf2v80hBWvAk2Bz6WWTuza89lKGBqdTcPEmHfB4MoCK3lEwuyQCeXrHIVebD8/B4sJJCMOaQaynNUS4WkAour5lZwj+1nrgc00bPM3Vwc1YBZwMlMD+sjzYaMmAlQAqLNXTuiRcljwMf9T/PSdDbKWnEXwMvgQTAVrw2FUFFB2EgD+SEQRu7gMTYwF4aCQKHpoCcFFDELSUxSDKxQIeZyRAdXocVKZGQ3lKJJQmhkFJAjqDxQVBfow/5Eb6wIMwL8gO8YDMYFfEReEP+09zNq7oDbkCi1Gm0BNkAKY28nDuLi/IJnEA9vYhaLSRAhN0Vj1zWRQ4bbeCtiE3hFzThKL4IPj4YQreDvXBQHsLvKqvgonHOavtPc9+uv6z/u+7mr6ffxgEb+/awuUbGqATKQWamcIQkiAIfV4XoQ2rCHKmEsDvehAO+G4BAXtacLkkC4+z7uJRkRKF7weHLDTm79u+v/6z/rM8zN8vFEVCZCQWTiXLgEreGQi8rQ4joaYwGqgL3V5qcCn+AAhFM4JwyC446UkHvibn8WPC9fd1fH92fe+WK1hrSv9h3zjJ8b5WNfAwHALy3ED2iTFIN1yBG/EWUJhgCq3h+jDsfwkSQwRAOvEAnIjdC/LeByHg
*/