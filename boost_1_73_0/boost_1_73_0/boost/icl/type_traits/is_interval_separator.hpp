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
VV0iUrYloW+1r9MK5Vsd+VbHsaIjP0ntGemkcstzxhHnaiUzVU/PlU5+B1g9A6yeEkk99a3PCRfdEGZ+A63EQCtxqidxh3Dt50gMshKDrMRZIYlOjsRgKzHYSkxwSkjmKCtUsIToCzS/A62OA62OSaxj4iFnzSgvm14xo2pmaZkEK6buP6D/gP75556F4Fnl40unlFWOnTqjdGr/Sap//7PwXwK2isrxlWXTNIytmDlrZv9SVUiWDf0nT3xyfFI=
*/