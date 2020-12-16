//  (C) Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <cmath> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/cmath is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_CMATH
#  define BOOST_CONFIG_CMATH

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#  include <cmath>

#  ifdef BOOST_CONFIG_NO_CMATH_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#endif

/* cmath.hpp
xub2uVfkIQ9vyM+xv8a1RskZNuK6mMq4LtQYqSeEwcjcH7/0ilzMm6AEx+PefQSlxrlQhufE4dmc84F8XRgIS7f+zisGoMywUslT02bgrjAHFqLPZoyXxTYvBym/SePjLAjbR5HnM3k5V8ln6Zaj8O0fgGuycZ/kWxfyilABNREWhtGx2/rEauRBPedd9W7jVKXyQcjDWh5fjR4j+bowELbd8USf0a3WKKlh1M0Y+3E/RPHNB2Sx2F3VIIvlz3TV9RwIxvbYzifubKA5eEt+Lt6yq0K/5Sxo5mOXHfQIi8jsr5kY9lnR3SfceGaqWJjwWV1xTdwHfd3ssmQlg+xgYRjd6myf+ArPinfk56yXB+NJORMG1hcPtJuDhWHOzF4+MRXr8r6r7K5jJ0/Sb3ovLPeg7MC3LirpZQcDYcvU5/pECHWLtarCxftzHtS990B3lCI28s2HOINyYTAsXfNCnzgN18V7ancckY95zWfAPjwzB/HxMGx4lFzXNBhWrYN+PtEbz8x1KpZ6yWldMFpU+ipZc6moMarcgUWEl1frYJh1IXmYhTy8r7IurViNN5Dugq6pfGR886EqTr4sDIQd39HfJ/KQh/VKnvj900t0753QHU+OEhebDJWIVVNPBwNh59O5zCf+xv1hg/p87Pw3dO8d0A117pV8smSiuqo9NQ8Gwrq/XOQTa7H+wwfqLlbb8FbdOx3yAihT852btQznhcGw5KghPnNf90MV4dPi5N76TW+H6fmY86Ixy92baIn8or3FbUHYvpsbfSaeeqMVTz0NNuJ8qHaz3GdPDpL0xq4Dwdw5meATR6Ju8ZHaGd/ukNBveRv08eDpyZPDVI8wUhKjKz9qQdj2lyk+49v/WEUMFy8amrJGLsjCe1g8sfXJQZLWynIgmP3xVp+Jc/nEinO5FaK8cbLJEVLGuRgAZ4yH5OA45OBTlfXk40U9de8U47fZzFMPRA9xSIzMcWUAnPevpvnEPpQXPlMeisVDT9W9k2FvA/TiuVliQfUQh0bJ4sYNgFN2vNsnvkAONilNyrO7F0b7wQ0h3Bl48tkmh0gqORoAx1qY5ROH4lr4XFWs//aclbr3FliBFqjlAcZ5QBj8aACcMuPDPvEGcrBZlf7wvbRU9SkP3iSM78jxSlmSiwN6UckgGA4e84li5EDlMvhldTFma50AbfBWSc8gS+xfcoS0mW4sCFuPetYnZiIPX8rn5b9OGIPZ0WAf7/275CApY74MgDO+RSYtrkUOvlIaZId7vtO942FSFtrcODmoKo4UtmtHFhNsgTjtj8/7RBi5UAUQChudtEP33gSdW2E+rAN49KhEWH0Ta1I2iJ1Pco1PXIxcKKW6aGrnGt17I1yD8cHLvDy6lB4mrTblxDA2yHU+sRx5+Fo+g4f//AtmA5P15Hj1CD1GWk3CiWHOjPfTusQ2S5e4HkqYdQk9RlJtIhPClqEkDz8jD9tVRYgdzQ7RveNgEGZDWhhgnQ+UGkUmhM3DjrRe9Y185j2Wqik2Fny4LmYz6VV6kKQSdQaEzUO3XWmZ+ltLph4Duw9K1dTikan1IEml6kwIO1b4V594C3lQAsS2Y4Nx3XsdTG+C+4OPR67Wg6SVrJ0Yxv62T56baH9TwsOdV/bA0/Ja6HMA2qR5ciemxliZSJDdQK2DYdaF129s0jvV/hA/I6LfdDQsaIhxP14eHUOPkVjLsEFsnTPHb2TsXWomtK0dpnuvgTIP2ud590pKTSMTws6V1tgvDkEevldn5/ztaHW4GvYx22RxkInSIeREGAxjj8vgYbeyTa+97wv9pqNgL+DZyctDTRWdRS4Nsd85NUeanJr5WSz5PaKJ5HdRlHCnTCE=
*/