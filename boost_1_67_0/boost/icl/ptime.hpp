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