/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_ELEMENT_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_ELEMENT_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> 
    struct element_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_element_equal(lhs, rhs);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::element_equal>::apply()  
    { return "="; }

}} // namespace icl boost

#endif


/* element_equal.hpp
POPiU+5tHzfYvbV7zjeXj0Q8fK17s6JPj7w/P/Pd/AcWvzTJNNGR2TdpzP35cxNaROx86ecWk04l3jfUEnuh9OvX1r9T1OKP7yN+olbPPHDbCnpj5Oxm0+o+/8mp9LtN/e4feaD/sTltLc+9e+COzusuZd9QdKhpnW7Hwv9aRfzcQ3qNSs5Y36ZR8kxzoykbjX2bbHlvWvh9x09um/W36cvXk+1ffTz+SftLE1/Z+Uvq7b9udzZc+Hn+Q19/1vynm2q9nT5tcNHSzP4XenVZc8ehX1uGLRWTrqTRjO+Pn0nb0zprq1jY5S8Na68a1jCvdy9r7cOjbimadetLu1++4e09a66+POOhVsPfcJx6YkvBfNz69pz+8j3eUSd6Pb1sw/i1Hz7SzfrT6u9Nn7pu2NZ4Q5u//bow4fjIrP4fLPlxc51V+/96p/2hjWdeGRjdaHuD+NK6MZHLnws9fO7jxc0fevXb5mM/avL98b/PXNM22vnOL45X5m488+iLTennF2L/2eNRGkIkeJV1CxJfijTuBv0oo+2g94A2+hR6OejXJbmK3ivZFyj0QdBvgC5R0W+CHl6o0L+D3geaxit09MuRxv2gVzB6NOi3QBeNUeiFoA+EgF+k0HtBvw2631iFvgz6IOiFdoVu90qkcZmBqNSm0KNAP2YgSnIq9KOgHzcQ/ayilxvgr0uh94N+wkA02+2nnzQQjR7np58yECV6FPpn0IdCiL6aoNAdd0YaD4POf8BPvyPJGT0K9BGpfhNZ/UC/Czp8kkKXgj4qxZfRv4N+D3S7ySy/XZHG90HvYPRo0B9I+U3x0x+CTpzK8gf9EWia5qePgT7G6IOgP5biP52VB/o46NkP+ukTEv0QO16vRho/AX1khp8+GYLtLIW2gj4F+tJsP70R9P45LN6gN4F2z/XTz4FuOM9PbwZdyuj9oEuk4z+fxRv0Fkn/YT/9vOSPit4m+buAtYfXIo0vgk5aqNDDQW+X7Bf56R2Svyr6Fcnfvyr0bNA7pfa8WKF3gN4l0Y8o9FegXw3BdolCNyyNNL4m5b9UofuB/rtU30cVugj0ac3xPqNpP59q4vWZ5vz8XHM+fSHFv1ih1yH/L6XjyehjoM9q2sNXmvZwTrJn5YfvjjReBH2a+ZsI+hupPS9j/oJeFgq9x1j99uD8Ar1QRT8OuuHjCj0R9HLQO1T0E6CHL1foEtBPgjY+4aefAr2f0Z+DXgH60Sf99ErQ+U+xeL8eaVwl0Sv89GqJXqnQGaCfluxX+elnpPxXK/RU0Gskf54po//n11v5M/2Z/kx/pj/Tn+nP9Gf6M/2Z/kx/pn9XykpL6dt5WHZGliCvcCi4CkWPYBZiYmKFHJtPkBdiFOSFFANtglDX049NDE6/S7RWvxp16BIdVB26BleH2Nj4SvQHpmdldw7SSEc9oUvwZcQlliujSpuE2JgqbIZ37dQltnOwYSPZLAgLHf3YuK5V6HcOLnJ67TdO0gacZk+xol51+4qLURlVXYa+ujrGFTZkPe8C/QvGQi4rSCO9A1+tMnTqExsXbH3QBKpTlsYoUaeYKmzio7sGbZNwp96BVbfPIOKsp39nl+D0uwbnT2x0YnD6cV2D078zNij9uOj44PQTgvMnrktw9Y2v7MSVWncwfUmQl1oK8rIm6wdxyaGaEemZWaKlc3r/tM6DzGPtYjGzbhlXVmBCQrkKdaoZMdDlE7wFNp85x45sXR5BXjoagnsKRK/P5nLKArHIJzq9oBS75qRO1fIjvsyPxH+DH4P7pAgJXeK6BhNzbhPEZa7MJphjxW2qf6WryCYuNvj6xCUG71tC+bYd3BrVUmYBa1TbnIVmu80quAp87gI=
*/