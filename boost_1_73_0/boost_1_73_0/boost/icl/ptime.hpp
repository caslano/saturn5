/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
itl_ptime provides adapter code for boost::posix_time::ptime.
It implements incrementation (++) decrementation (--) and a neutral element
w.r.t. addition (identity_element()).
------------------------------------------------------------------------------*/

#ifndef BOOST_ICL_PTIME_HPP_JOFA_080416
#define BOOST_ICL_PTIME_HPP_JOFA_080416

#include <boost/icl/detail/boost_config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4100) // boost/date_time/time.hpp(80) : warning C4100: 'as_offset' : unreferenced formal parameter
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4244) // 'argument' : conversion from 'int' to 'unsigned short', possible loss of data
#pragma warning(disable:4702) // boost\lexical_cast.hpp(1159) : warning C4702: unreachable code
#pragma warning(disable:4996) // Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
#endif                        

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{namespace icl
{
    template<> struct is_discrete<boost::posix_time::ptime>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    inline boost::posix_time::ptime identity_element<boost::posix_time::ptime>::value()
    { 
        return boost::posix_time::ptime(boost::posix_time::min_date_time); 
    }

    template<> 
    struct has_difference<boost::posix_time::ptime> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct difference_type_of<boost::posix_time::ptime> 
    { 
        typedef boost::posix_time::time_duration type; 
    };  

    template<> 
    struct size_type_of<boost::posix_time::ptime> 
    { 
        typedef boost::posix_time::time_duration type; 
    };  

    // ------------------------------------------------------------------------
    inline boost::posix_time::ptime operator ++(boost::posix_time::ptime& x)
    {
        return x += boost::posix_time::ptime::time_duration_type::unit();
    }

    inline boost::posix_time::ptime operator --(boost::posix_time::ptime& x)
    {
        return x -= boost::posix_time::ptime::time_duration_type::unit();
    }

    // ------------------------------------------------------------------------
    template<> struct is_discrete<boost::posix_time::time_duration>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    struct has_difference<boost::posix_time::time_duration> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct size_type_of<boost::posix_time::time_duration> 
    { 
        typedef boost::posix_time::time_duration type; 
    };  

    inline boost::posix_time::time_duration operator ++(boost::posix_time::time_duration& x)
    {
        return x += boost::posix_time::ptime::time_duration_type::unit();
    }

    inline boost::posix_time::time_duration operator --(boost::posix_time::time_duration& x)
    {
        return x -= boost::posix_time::ptime::time_duration_type::unit();
    }
}} // namespace icl boost

#endif



/* ptime.hpp
4PwQvX3FLqn4+9qLkOLrNu0wmHvrKDfaAOUE+5V2+NkB8RD7XuofpEHk3QZ+fSsSTwfbXjYJQSxmC5h9APzdrm+dBqskC3MQmgef3BZSbetzA9wgywN/EsazaO0HEz9EuYr9YiDg+i4sWg62J8Pe+ZvB0fFwcLDbmbwfDybji0P4r3dxsNsW2wCge+3dNsxwHiVefhAGQbCD/zcBwR0c+EGcpMsJ8BZgL6uAOBy8fv+Guise8oPp+pIoI05QTC2BGSrj9aLVwts57sFme9GNd5epTcxwLQCguoE9bociUXhyFOId1fR0dDwYDGhSTFVI4nSJFkbcgkSFMkKO/+plFRUfer8xX8uJIZTDo+God6HHISTjOGHmTWHJkZdeBl2UTYVOm/NVYV31rr0wwi7V5YHYirswdoc49K8H4sMP7p4WiDDmYe9MGGPSb2M0+o0qsDzE6eiXwfnrwflobPT+JUinQZpkJgR9rQ7K8Hh8wRPtp4GXW2wXhRlil8UBqawUhOKqhgmRyrD1DjDLzcE2CD0v7jCdt3eWHghyTeBH74dDHvRoDaLeD3IPVaIa7F7YIHc6QAXAoRnQSFYGrxQnEkvcYlp5e4b6sCOCa7QR5pt261uqACEuUH2CZJ8FPig1tg5YSyO0ChRpeeH8
*/