// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//  
 

#ifndef BOOST_ASSIGN_ASSIGNMENT_EXCEPTION_HPP
#define BOOST_ASSIGN_ASSIGNMENT_EXCEPTION_HPP

#include <boost/config.hpp>
#include <exception>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

namespace boost
{    
    namespace assign
    {
        class assignment_exception : public std::exception
        {
        public:
            assignment_exception( const char* _what ) 
            : what_( _what )
            { }

            virtual const char* what() const BOOST_NOEXCEPT_OR_NOTHROW
            {
                return what_;
            }

        private:
                const char* what_;
        };
    }
}

#endif

/* assignment_exception.hpp
SRaxd75CUGTXwDDR/9M4oMSDyrOkEPJPxbLUtOAR4MkHFzYkAA714rGY5wtnkSnNxg1k0AEBPqEqnA/uZMXRbsjaLlNlHHwh/QnFXCmL/ZlgSQMK85G0j/RCDH4iLw1ANibGwk4sy+0/kVbV+UtWIEBl2CaLIMxXrpgNLjdc5RkyPaI1OPv8FW+dX72H/xRfM+SYbuG63idk/3JqvMUWXr3xp1mIDj87qopMWEVUMfNvmuWlzNFUDxj6sOzHsx6TlfOzGRCfA0eL48V1KLRh1MolM6NWRDZDxUcPM55/a+U1mINm+eW2H7wLi2wa6HrG/dGb2pVSDAsdZUv5FWIQKYyCcDUdqHol/8s7axVdrLKszUurPF63YlpdEV+N7NLTn2LIR2zZ+Xx0VQSSZ2oBefsKtZnECPGeKhd7X4JQ2m7Ap530A8eXCFRgRN1ivCcvyE2Blkq23UOqEAcIdgA00BoEsT5VuIoj8NAukK2htOk7syjK+laDcolra+SP6eU/WqTsk4Auc21m528Kpn9nby5tT3UJ02B1k0xJaf8P52cw7xbx03n+SE6Y3w==
*/