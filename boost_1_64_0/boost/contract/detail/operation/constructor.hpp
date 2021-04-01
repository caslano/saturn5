
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
dKUKwjNPbxtrLHstPBV6FM2f/ibg3o3h2ECG5Oo91jjcxZL7PyogQzNBJq/7DGPSguCjis8sec/dQvtM37mZ9ZuRzC+Y4mmgNCsTTjueeG/xVBEMjgu0IpXtXnN63U9pE4SdLjizo0H14K2t127Nt0G60IAZNZkBTO2lKd48FVxGPt6O3NqZNKIMRl+0i7gIFLjsyetPISP8QJ195nqYDdtXGYUTuAfbE4spIR6rDY7eUBuNXkQSUrUlawBnUx0E/9ohB0FK3nUVZQOJ2uVJEGSwWmS/pLx30nlaO13waLqodDK7fAYHSRrWESMY66xR9zY2eQ12cKIkpL1JuLUK8ZL79LuvTni+7UBh6NPK92fit2b6vY9jbybSPWjPoBV5IfRj0pPf7wdrXq0amIz5gQt1JHULpyo+aXOZwb/YasPhPXNODt6GL8mOKTLMeRPiKkIqUZ9CdLPw9kjEv0NZOkyEQT0+wXtCw7nF4O9/4emPmOBicLCDxRLv+ltif8GFMcu8V8Qb2YkvqqpAZLWGAfKmrnvPsBijq3bqtE7yCwU8Zwqi3JMzWdMyjQ==
*/