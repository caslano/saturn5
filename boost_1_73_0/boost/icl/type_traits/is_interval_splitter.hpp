/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SPLITTER_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_splitter
    { 
        typedef is_interval_splitter<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_splitter.hpp
2oNi0yOGo9EoYqPhWxLFc5kQMdt66ffVb8rSA/IBG01+PDglOFs+iS9IjPxYTFeuClDi+lyd6xEwiquj9X5Ke34dr75lfj0w9IysVDuCdZTVpmCg1m8Lz05U05SZNJ52ogQo4gBE3PpxJMEetf1OVOUHId1DH3bfXRqzVRZbO9RiaxKibFmvRuJleq1VC9istahvFbK+2vtsX29Jc9INgUZniBgPjzO3qE6jMLUOht+ex7kn
*/