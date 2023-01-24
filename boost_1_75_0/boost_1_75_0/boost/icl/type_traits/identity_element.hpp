/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IDENTITY_ELEMENT_HPP_JOFA_080912
#define BOOST_ICL_TYPE_TRAITS_IDENTITY_ELEMENT_HPP_JOFA_080912

#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct identity_element
    { 
        static Type value(); 
        Type operator()()const { return value(); }
    };

    template <class Type>
    inline Type identity_element<Type>::value()
    {
        static Type _value;
        return _value;
    }

    template<>
    inline std::string unary_template_to_string<identity_element>::apply() { return "0"; }

}} // namespace boost icl

#endif



/* identity_element.hpp
yv7uS1SuynB7FkEfHFhNpnZ9yU0MWiJmWlWHc2hZsyETZ4vCRP01YX9BJIqIeE0wwNZawIv7EVKVPd9hSLcLuDLaLs89zkOU/FGWeY72j1SUYeS6kE2SOMhY1wgZOfOb/R1+HFETZSBHb1kDynjPnTZlNHJn4XvOQd03v6qdkNM+AGVBfuXRys9uZ2uA9l8LOXMWYsxvPWNxd1iSBDkOokNHKb4VXyBGxX0n6xYiVlt/R2vsNGUq7j452Iw4+bJC4zgLz7tFaP2nYV1J8bWa0mMi3rC1GXGbYXtbren5VNyFMgd93/lgkUBXcRdKwWLIHH+k1ZSSDfehOBZAF7//gUFTVcT3E2cj39rJ+Fab4+K4G6WzCf2z75xWORWYivtRNizC82PDrTYpi3BXSt0C+JHb3m+VU8GpuC9lL/S188LPOU2ld6VgbdG5/2CrNa2ZCv9m/ELIe/4i09FiFfemrGtB3PuFUTZHNFXcobKmCfspX/10iCN7Ku5UaZuPer6+RVhYVnGnyl4P9ou89qdWaxo5FXertE2muW6SWq2pMVXcseJrRn3+6fJWORWSintWijEnORu/32rKJYQ4Zvsi9KdIfKucNk/FfSvrWkGbPKNVTp+j4s6V8vNA2/5Mq5wiR8W9K5vOw/sy3m41peXB3Sub6vGdJV9rtaY+UXEHi+c80MsPtlpTlqi4i2V8G957wyutcsoSleqb83Cu
*/