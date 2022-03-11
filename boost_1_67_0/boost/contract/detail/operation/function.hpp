
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