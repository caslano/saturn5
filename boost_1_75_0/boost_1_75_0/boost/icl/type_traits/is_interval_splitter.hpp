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
3bQqAr++Tjrbpp65u8qiAm0D57OBSfr2PEqFxPAkDnvx6sJOft4610iChBvOOTJ+3ya7b1OlT8VP3KXv8CoikGxxoL9h60VP0iXzt6TkV7/t2nwiNjM5/xCnvHopDzS6Y9ptmmMrjfRCJLiQfqAY0cLbslMfCRcONKPwrvKEu0HNNybFU5Icfc3uba+4TSorbeBcyulVLtpOr0mNKU42KJRWrO8EJ8nX0y7vWBuROkj7dyjc+dtwKcjdE8EBvEYzpcRY9ieu8IwTPsFjHTz3hUchRYsbvk0jDqu2PbHsXvn+J2BhQ8LdPljWuTtO48acD3SaGmMO/YmWq6fkuSO+b+9/3dGi2vaYY35p8dRMqHAFX9DdktCdvrgK79GvWryfAL6yepUJltY97SNkSbzIf3IWCI3LyeaF6x87VsjJrF7V17yfHbbSIbt6NdZWNC4wo5TlH1c6HVQEYS4QL0ZPDQjBf4hYjBgn7o69DettqZYq0FGJkjq/F9CZ73HSTVc5FjlWvg8XpXQbsdEA5oHNb7vdAObBB0xRw+dtdRxZoyrO2T5wlInzPmc7vJjHGICZDWGsEg84E7fP6Ce2LcO2SuN6B61tWXAQErfUftn7V2OiY+h1HyRNNDHstDOX9cipRi+RJmOnwmcKr8J3ga879dnidwlCT74H0UUKF5hO2k0qofYFS7Ekgw5D3rlNE4FwVjZvj9AaBkwA1VLn
*/