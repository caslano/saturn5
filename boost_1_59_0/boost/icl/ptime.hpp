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
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
*/