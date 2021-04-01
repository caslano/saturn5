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
/5dKAOgudOngw0lKBEOdNqcMbBga/5XUF5xLG98bleXa0CR/ob1TayiJJxQsQu7s6nBp2ue8b6S5Wgjd6gXTSTVapyJRQFIScnXkwoAOhF6xOUrTvOhpj6JR7vPQOp715w5gEQRsg6pheGfgxc0mxihZPH5e+C6g9dfoZJ0BZU61E5rpUHubDjEIb+ucuX5PNI+yuazjVvxVhZscPp3Kd7n57oxz3swA8PhzRQkfWw8vmx7BebUGrUkYrVzMdVoiAEqnpi8DRS0PIzHDLFyQClisqlX5AnxtzSLXievT6X6pZ9WtiC5+6GXOedHXFO2yuEuT1xQP5iNtbFq7i3g3F4aNFB6ao4HuhYFHzt4wJH+Vr96N8nWmSiKefnaPzWJtF90HMAXMKE1f7s85lUSK37mtRZc+wvPzjcQpS6Az6fMtZJtI1RK7FoMOSKacGOLYNOOSoWS1QK6gMnwauHHQNflDlaEcE6KEuPt5UtlGHDkMo9vRxdV+IRYyFkLn2B7W/3pQYIzEAK4/X/MaIJTNQv/eOf2S6dO0CUUvJ0ezTLzX/Vch4TzsYlei3w==
*/