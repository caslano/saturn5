/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_UNIT_ELEMENT_HPP_JOFA_080912
#define BOOST_ICL_TYPE_TRAITS_UNIT_ELEMENT_HPP_JOFA_080912

#include <string>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct unit_element{ static Type value(); };

    template<> inline bool   unit_element<bool>::value()   { return true;}
    template<> inline float  unit_element<float>::value()  { return 1.0; }
    template<> inline double unit_element<double>::value() { return 1.0; }
    template<> inline long double unit_element<long double>::value() 
                                                           { return 1.0; }
    
    // Smallest 'visible' string that is greater than the empty string.
    template <>    
    inline std::string unit_element<std::string>::value()
    { return std::string(" "); }

    template <class Type> 
    inline Type unit_element<Type>::value()
    { return icl::succ(identity_element<Type>::value()); }

}} // namespace boost icl

#endif



/* unit_element.hpp
GL8jw0nKMwi55uyeF6aatfM0CqPlWQtJpHGcoytFnIxGQJKNF6U5QIUvKqYBkIoJGXI15TMBKJg11k1UKVQ78GjLRULHn1R2PPJI8CiQa2googcZKoBDg5KHyjqoOUUc+jkGFhQ/VPXksBj66VSWR7QoykRTrKcdqTGslzKBNdDSX0PF9chZypewwELFlHegrspRfqU5sFOWQdqitZjmI30QK6AqSlZDFhRmKI4sFJo6B2kIq2rQmAeaprAulK40VAmdKqSyg/PFKXSnAJVrvDBBLaBv5bYiAt2EIdYWYAF/FeaKVRCmu2XCi4oJ3+2b0ISsuxsaEhwL13uOOwRVuco6WcXLN/jfMY+sBBFRPRpG9T56QsBrERHj+0Kyw1KKKAhX02/KCv+wsFWZ+2JKMRFHEClxmkM5dWX0TawbsfTEnRZuPSDUwJLsyV//8qfFVLmw8HFA3ZbEnIG9lV02y9RTCoHKsnXWhno5gchsmZZr9PRLSAUFo8T0xjJTnvMAqoZu6wACuRGiSZA4aCeK+QIzCCKBRCsRQXhj8UFFCYRJq8YycsVpbJjNArWVHCVWmeAlRHVODf9KbNx3oRBC8gxbIFqZWrWTbNgFkyRo0lZL0mm1sA6BNTeH4gN83c9zvkyK3KAkllVBHR+T
*/