/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_separator
    { 
        typedef is_interval_separator<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_separator.hpp
rK+h2gak0Z6UwFDtAPiYM2mGfKhKv0ygi1XchKniFcKS7aYJVDV8jaE3nFu7TBN6H8xkAQ5VCVNxHpQrpXVfrkNVzpbBSt3hFh7iAcDY4YZHcIIzT582Yz1Uhbxr4FIAQ1XB48DWywIgo2Mn2FtVlcyuq83neoE+WtY10+VeNVSFTBHaETNvghGydzlWFb3zUSpipMoYj//cw02TN1c7UsW8Y5LdaKRqGY/muOvZC8yFYXqYaSGRqpQD+8bGHIc+t2xsW051WJVgZQkNUIinCJ/dSawqb+lkX6ZkpGr7xQlVAlWJTzBlmLYpPYXUEFXgVNR4iMTTJCEP8ztSBX4AxUbdjLQqdcHtZvsZqSrH4M4PEYPOKW33BxKhartUJPd8PFVcW3y2gx1xXDfdKd+ZOiptRlQScUzTKH58kkDx2/hou4vpoKOKupSfac+ZZRp0jpK4F7szRlCY/8XuVJ7CZTQRqCyAuiC5eBhz3MuOxZwgGNvbXXcYdFRFH+SRDoBNUlXUloPAxqlm0FHV7FPHblYPglQJlN2fezJLXVXEHm5EuDkaprjB3mDJqHVVEZdEpmXxCdthXsiYMLVCTelSV5VwbbHswfzOFFLsiDzmvO2IQJ9iLmQZdVXpYoHMm0nqqtotIR7/ewdQNbsv
*/