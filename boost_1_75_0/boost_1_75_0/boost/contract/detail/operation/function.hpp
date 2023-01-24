
#ifndef BOOST_CONTRACT_DETAIL_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_post.hpp>
#include <boost/contract/detail/exception.hpp>
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && ( \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS))
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// Used for free function, private and protected member functions.
class function : public cond_post</* VR = */ none> { // Non-copyable base.
public:
    explicit function() : cond_post</* VR = */ none>(
            boost::contract::from_function) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_OLDS)
        void init() /* override */ {
            #ifndef  BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
            #endif
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                {
                    #if !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && \
                        !defined( \
                            BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION)
                        checking k;
                    #endif
                    this->check_pre();
                }
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~function() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef  BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
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


/* function.hpp
4f3oEIxcFwC47wSQjgVItVvlEm+2ygHZ4VOgKkx7KcFr57PQbSMJK8HqyB/ugpvpxW/9S0VpgmTYxb/sn/fqSThieuJbvb48HybfjMCYNeL08CbAAy+ATDfEwwEgGXGIM0G2vgwrtzTwNniHbNCP5nbRXwUfH+5mmt/6l4nXAelozb/sn99aAu8TX6WhshA+vH0Nb+xOAhQGAxQEIR4+AFmIQ6rt6lzg/AHZANfnpKciDDlIw5zPeXjyMAWtSZe+9X82SRdkEy79Zf+C9tLAh3zoqzRWFcHM+7cw7ojayqIBSsIRj6BVO6Q7rvpDrBGabx1YClSDD6j/UawMTHkpQkNeGloXDb71r5CqD3KIw1+JsOtZEET8v0pTdQnMTr2HcRcZABQbUBaF+r+9Ohc4f8D5QSyKiTAd5ANqeB8YwcrCW1c5aCzMAH9bw2/9n8swAoU0w7/sX9RbEXGQ+1ZvRv3PTU/BuLviat8lEatz8MAb9Y/Gn3R9NSbR+D8FoPF7ncOPfwShqTgbAuxMfus/2wTwHNINQC5FD84mXgbZLz6B88tTwSogdzYLpE4ngbhoDIgI3IaHiXdgYe4jjPtpwmvbEzBqJQhDFnzQZ34EOo244YU+JzRfYoM6zUNQeZEVipT3Q44SC6TJM0NrRT6EuFz71r8S6h+Hc5nGiIMhyN/Th1WfQBxiEIdwdbhwoQjk5bJBSjIFTp2IRWtP
*/