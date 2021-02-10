
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
K2TjQt0igb2gJjbZBpFKHgXxIAyhrpgpFLK+D/MitKfGImj0nwpZqIMnh/NiAitRVSgoBpuHQliY0uvhNMaELQZQcIZPOSywExExEJ3YOCZQj2BatyInNnukObbKmMqCbwpPIqdJ5xgs2qLAszsMbKsu1vZsmCMWjlJCSWNLjgj1rTu2VK20GrdxvKGT9ZmLjJGnnRtX87uegNTQ26VjXSF4TcXW2hoKWbcdQztB/mqqmKe35xpDEmrDNLqkoMsWKb3gHaho2NYIk26zDHu/aKsufW01GoIdMbsq3LKqRRB5IaQ7lmO9Ty5KkvxtPEfRIBwNzzCw73V82Y+NxULJ4k2DmrNCW2q1lthnqzUvXt1DdzpQh5r+rF93rextlvoQ2ro0/K9WNFYzqzUgDSGOR0QUAoH2eV5YuMFGg3PXA3vNMZ6NRj6JZa7k9x33DI0s3Ot3FRKVORLS2+iWoFy3faQduxEPHFI5go0hL4LrYRpaYhMeUpkt1KuS7zzRQ+veTSKpdimW9IhzhFUbZkccz/29qtqo3q6nYK9a0+HvZ105qOYOhr2caOK4dJwSuWW0RR0ZJml0nl5EceI4Zmf5YkuVvneuaMYwHC38J8+D+YPv3KN/89QLX10dnTz64WnPNa9D0PIR22CLBuGI
*/