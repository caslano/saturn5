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