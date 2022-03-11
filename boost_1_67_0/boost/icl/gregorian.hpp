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