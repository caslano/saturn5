/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_GREGORIAN_DATE_HPP_JOFA_080416
#define BOOST_ICL_GREGORIAN_DATE_HPP_JOFA_080416

#include <boost/icl/detail/boost_config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4100) // unreferenced formal parameter
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4244) // 'argument' : conversion from 'int' to 'unsigned short', possible loss of data
#pragma warning(disable:4702) // boost\lexical_cast.hpp(1159) : warning C4702: unreachable code
#pragma warning(disable:4996) // Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
#endif

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>

namespace boost{namespace icl
{
    template<> struct is_discrete<boost::gregorian::date>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    inline boost::gregorian::date identity_element<boost::gregorian::date>::value()
    { 
        return boost::gregorian::date(boost::gregorian::min_date_time); 
    }

    template<> 
    struct identity_element<boost::gregorian::date_duration>
    {
        static boost::gregorian::date_duration value()
        { 
            return boost::gregorian::date(boost::gregorian::min_date_time) 
                 - boost::gregorian::date(boost::gregorian::min_date_time); 
        }
    };

    template<> 
    struct has_difference<boost::gregorian::date> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct difference_type_of<boost::gregorian::date> 
    { typedef boost::gregorian::date_duration type; };  

    template<> 
    struct size_type_of<boost::gregorian::date> 
    { typedef boost::gregorian::date_duration type; };  



    // ------------------------------------------------------------------------
    inline boost::gregorian::date operator ++(boost::gregorian::date& x)
    {
        return x += boost::gregorian::date::duration_type::unit();
    }

    inline boost::gregorian::date operator --(boost::gregorian::date& x)
    {
        return x -= boost::gregorian::date::duration_type::unit();
    }

    // ------------------------------------------------------------------------
    template<> struct is_discrete<boost::gregorian::date_duration>
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<> 
    struct has_difference<boost::gregorian::date_duration> 
    { 
        typedef has_difference type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };  

    template<> 
    struct size_type_of<boost::gregorian::date_duration> 
    { 
        typedef boost::gregorian::date_duration type; 
    };  

    inline boost::gregorian::date_duration operator ++(boost::gregorian::date_duration& x)
    {
        return x += boost::gregorian::date::duration_type::unit();
    }

    inline boost::gregorian::date_duration operator --(boost::gregorian::date_duration& x)
    {
        return x -= boost::gregorian::date::duration_type::unit();
    }

    // ------------------------------------------------------------------------


}} // namespace icl boost

#endif



/* gregorian.hpp
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
*/