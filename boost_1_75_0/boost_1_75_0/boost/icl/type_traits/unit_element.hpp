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
d/ws4+Hd8f1+I9Tv1jzTj22BNAXp7TeoHeb84vvL2j5uuCcf523MG5LpzDGF+9DtfozHdcG8ReO6/OiVGx9/P3rlxsff2j1uufHxh3mLzi1bvXLj42+rU+4RwP2wSq+q9JpKr6vUOQq4V6lPpUGVxlQi3KTptdfjvfX3/Sd73Pkp3veY1469E+/7a1658b6/5pUb7/tvIG+lIO/FvOsK8l7xePG+x7xFeW+XV26c93Z55cbPp0Z7yzdGuakYwN1Q7l8CffyVShdV+muV/rZKb6v0dyD9J4peb6jUeZxSt0rsJyxOUEI7y/oTVF9pWULUv3bj2rIuAGwfQfrqOMHCNqyPRVo3TPue2rqhLyvEdcPBxW65cd0Q85rl/r0WSn9fJZ7zPllMycX1O0vQLviaOCLegP/Pi1fg20FxWLwEvw/C/wPowAbX37T8X/+Ro3NsEZv+F/58Rmj9mm0+fP2fi/GNI6Im5sSkmBanoLRJkLDHoeRpcVL6ev7PMg9afXthiODns1LPHBS4L+g5yHMa5tZRyH8eoBmFX+Oy7ENQ0gkod0ZUIZ2EOioy9xzkxv+jcGcSvqFP6bTAM8W47v2QqvLdScirc4XLfA3uVcU8lDcFv7At8yAP4zsVWdIs3J8B2BCuaXiK15+K+436XoM0B2XoevaIHmhjj3gU/j8mdkLqkVHmKtC7r0CvH5LP9dNt8mkv/NHGXYxwt0ji
*/