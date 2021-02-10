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
lV1SYgxeqblWL767Z7HYaTR8Dd/eZ3oFIpn+jkOxnA+BXbddaNQu4PCSqioDJ4StB78N2ih56wj1b8Pj1/Y035x+2KKrNqaa5nw+6A3ZPPn6dgNKoNBjINo+kcbEYX8oxnfLaRJZhtL78+Gk3z8cHI0PnNkECDBNJrsH1160DnbFp45Q1/b42p745Lru589O1Qgw7RMgAdxA3w/RMgP7si8IjDYwlR13HlyHmWW87XUPB/3u3vPnLzriZPwLWaLCUR6AI8BIzKQhWGEuMG3BUE3SK0bBEs25j8kavsHMcFeW3p24BuVPvXdfdN/1TnGol3KoJZigPluGBWlLHf7JXXmzK6QQF/yPz0KrvPqJoJxZr3wQQz7aMAAE7AggEP8GCcsPgFZBbUkricXQ3k/181E2OqMuQ9MmUT/QD6IJvOoeDV6bfVfgG4QxrjZM1pllyoPtwnbXT92T3rnZCRcKfs48vOyik7V4KqkS5xwnN3BvJY11bAkchuusR0CWzjSOkAmBLNG8mjB4d8Fb8H15Bj2g/WTOE4Hmy+zyqatmsfDAK/SiLGEXSe5WlSXoQ7somUNtFcmt4E65RKXlwIzrQen+0AfoKmCwDEy4MEXWoAVUdo0a5pWIy4BFrguSShIqawD26OjWgijIzfyI
*/