
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
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
*/