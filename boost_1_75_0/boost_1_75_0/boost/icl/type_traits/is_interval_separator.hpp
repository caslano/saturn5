/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_separator
    { 
        typedef is_interval_separator<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_separator.hpp
uMNHpBgmGeXCdrkbnjWHxzepdAR//0IE49ZSdUz0Z6GheL41agYXdSep7jd9y9dpnuyH4X6TRftK8g38vDDcdDYMT84fgpSHCNaRjSuJOe2VzvhbpMb4EN9ptHkNRfhETrDXNJmZXIo81DRfaMC4XEVJlse4t5Aa/zo5p5IgXrl6Ve0O1u5p3oRsdekgPO1x3B/wu3aggWxsx/3HkfcHzP7D4RfLKpL0twjEJXhcSaDw6vuXtqIqT60uoDx8B7iCTXS2zr0h54hZjKidbdH3u26Q1iLY8/5J6q3HS5kbOieQ5rhcdmfLTy2FeVjNrNRz46m+oEQF4erqewZYGv+X9oERqdX3d0D9hvBaCMfJaFVp/JKWrskVr9XKrgDf90j1m/0ZzXs51vqJa/KTf9CXPVIEMOc/vc/qSuf/Md29JS4Uawv/6ZSLYYndWEBoUNjL7gwA5JsOKo/+hM008IAvzg5QsLrNEuehtnltO5gBGRhW0C3Ihli4MrYvfpArohgp4UlqB6UYRShEc8Q1AJQDeReq87oPLp5sGgAuNb5H19VPQs5tYeFhf9efP2PUJRn6jIZmTVBYnxcpfJFjAz2C/BC6FfjYIvfqZoSw1GSu2INVkrDrlmy9Q928hSchGCBRTwHcmz2ULHpfTPiuP4QyddSMOs0Q8Wo3oePl/vsBel6jU2bxTCxJAVa6wwJnzApce52iyc1lf2xJw8An
*/