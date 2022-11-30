/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
itl_rational provides adapter code for boost::rational.
------------------------------------------------------------------------------*/

#ifndef BOOST_ICL_RATIONAL_HPP_JOFA_080913
#define BOOST_ICL_RATIONAL_HPP_JOFA_080913

#include <boost/config.hpp> // For BOOST_MSVC and more

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#pragma warning(disable:4512) // 'boost::detail::resetter' : assignment operator could not be generated
#pragma warning(disable:4800) // 'unsigned int' : forcing value to bool 'true' or 'false' (performance warning)
#endif                        

#include <boost/rational.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/has_inverse.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{namespace icl
{
    template<class Integral> 
    struct is_numeric<boost::rational<Integral> >
    {
        typedef is_numeric type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<class Integral> 
    struct is_continuous<boost::rational<Integral> >
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, value = true);
    };

    template<class Integral> 
    struct is_discrete<boost::rational<Integral> >
    {
        typedef is_discrete type;
        BOOST_STATIC_CONSTANT(bool, value = false);
    };

    template<class Integral> 
    struct has_inverse<boost::rational<Integral> >
    {
        typedef has_inverse type;
        BOOST_STATIC_CONSTANT(bool, value = (boost::is_signed<Integral>::value));
    };

}} // namespace icl boost


#endif



/* rational.hpp
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
*/