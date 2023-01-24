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
gy/qQt1Pa8EnptXAtEolHSqxYImB8D/kZMGr+9fg1Y1LkJ54GjIvHwd57AGQ/xkKb09sg+yo9ZAdsRoU4f6QE77478fPy2F1KMh6CQXpqZBxJwF2rPSDggdXIP92LOQnxcD7xKPwPj6S1YHw9fmuLo6Kxaf3nawOcjgeHgqdv2kDt84dh4LHN3TqQHwg/JvhGyFp33pI2rMWru1eA9dCVkLizuWQGOwPCduXQkKQH1zesggub/YpGZ/7RH9w5xa0+ro59OrWGd6/fAz5afd06kCyIHzS8WC6NjdFnSfSd8pKOAXyy9GQeekoZF48DK/PR8LloEXS8JFOnTwBrVu1hAaWFhB9YCeTRdE6UH+gPkm+P0n3jNXhhqoOp0GecBL7TzTXYzwCCVv9JONnZmbCvN9/h48/rgFtrFvAmch9rA6Jkbtgq9dUVgfqkzQuyJf6HuemEEy+7Pt8yXzZr3CwhGXdLWFRVwuQxx9nfEjctlQyfn5+PuA0Bp07fwc1TKtDl04dIGTjKnD90Ql6tGnG+EDjgsYm6VjkkM4P6brcJlnEMT6QDl4WjiHSS5THR7P+IBVfVYe9e/dCq9at4OMapmBe7zNo3sAC2jdrxGRBY5PmB6bnQbomDwr1bd7eihN1v5j+22mmA3gV+2Rp8IlwGoSdO3eCZYMGUL58OahsZATNLOozWdD8QHMU8X+vcxMI/r4x8r8R538DWGZn
*/