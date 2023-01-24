/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205
#define BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205

#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost{ namespace icl
{

    template <class Type> struct has_inverse
    { 
        typedef has_inverse<Type> type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (   boost::is_signed<Type>::value 
                     || is_floating_point<Type>::value ) ); 
    };

}} // namespace boost icl

#endif // BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205



/* has_inverse.hpp
/epPtcCTDtvi4e8I1aJtD10OvDZMUaacOtR7xdnky2i/x5zTRPcYLFvP5i/Evdj8tGYe4oRfawjioACpB7qWNh9z1sEbVvIPonEnyFRm/pzMb9Syps9S/2rqPSEk3FpIRVJ8xXS8a0tXKITGdFHFR+Ov88D/h9ORtyTM0BR/Eras8vZwNneyCRFlnnw2YjIllUaZWewe8/HxYtjSr+7gMzF9CLIOzkc5L5xCZFEceH2jMXdfeZM+dxvFovS2BYjhTftAp/PigbaxDmW4506dBg+I18kazNfKqCvCK+YSg54RgD+BPqFcthJnvDg7i13Ssp2VHepgWMg/tABxyYsXEMnN/uX4lMblmslK7Ycz0T4r3w5xKp5xIS6t/LKBPKOx6utH/W6UN3BPSKKw71x6GuK3+ezkHh52RRqX8wKCvg06RMlWKd3d3ddziZ/iD9ZifebcSXodaKdzvcb+nDbMJcrap4k51xQNG2t8W05DXUQOhLQq0vYvzaNx+sspXnAIaf25QBt7Xsi3Ulh15WuDVfALP2qgz2kb9Xg7Ik93rtKmGuUMBmkuBv7O1TWwzR2r2TuDQW2d7jAt45ii0MrGsC/Qzc6pEXkFs1COy6812oY5laBNno92+/vptK6qfT4EYRqXN/i7lvnDoO9bCPrAT1lZWMRc8+zoO50YYz94gu0HYTLXLkD/2PAMeV9DT4jV32ANyvbhhbTMFKuq
*/