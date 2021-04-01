
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
kFrz0Lx1ZusXrQEB1Qb+EGBhnncNMuC20aAIG2TWGqgaksroDjSaAZ+B/eX+NgkB5uZd4BVd+FBG4pmEjoFiZ9BRaVA7sU2B8KuspHTiRzxvPd0r4owJYeNQw6aW08uPP6qa9uPfkthZIBnYnvUQAGqTdg1bQxIlYH+SMKVac9xONduv5cnPPE62/hjXJP0SrLW/nX9PuFr3aPm45UsLPcx60XBVs3XX2XeWn/gcfdCT+kCp1zMXFCdtvW25r/BdOZY5r9P/MvrlrGAgmynFY2i+EXWfBihtmMUo6Mw3Cwa1pHo29jgiUZ2G7jNJc075lEk/RzlXuySefsnKIqFyaavDaUt8IdUb7jhx4NWtuyZdgr+Qp8Mbte1WNZhSL8mKp9q1EF8L6QOcfGkw4rwgJ28CPX352PMjXVVDvNI3he5F6XB+zKXgWaWMm8RxSF2ZpV3rO4ep0xY3sUl23rSbGnXWfXAPQofKh0eRBtB1vdxnqdRc23MxcXHVYLM4Y4k1vM4K1tnw+LO2Ga5FWrw7piae+S28LUKBmgG/oJFXzMEGhL+vRAEEYUxelw==
*/