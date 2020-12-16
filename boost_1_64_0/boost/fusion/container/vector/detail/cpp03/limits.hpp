/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_LIMITS_07072005_1246)
#define FUSION_VECTOR_LIMITS_07072005_1246

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/pp_round.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(FUSION_MAX_VECTOR_SIZE)
# define FUSION_MAX_VECTOR_SIZE 10
#else
# if FUSION_MAX_VECTOR_SIZE < 3
#   undef FUSION_MAX_VECTOR_SIZE
#   define FUSION_MAX_VECTOR_SIZE 10
# endif
#endif

#define FUSION_MAX_VECTOR_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_VECTOR_SIZE))

#endif

/* limits.hpp
+uGrWFW+xbLcFJ3yrZDyPYaB+C5eju/hMPw7XoUf4HX4IY7DjzEFP9HyR9uE5/w18iJ/6IN+6Iv25QhZ7jKd5Y7Ifr2NzfAdx/vXXWR7HWR7gbK9jqiWoyznp7Pci7K9/dgUD6hj1aSuLnX4Epexat9IOZ7D3ngeI/B7TMMLuAJ/+jd7dwIfRXUHcHw5RKKAASNECGW5AwQIEEiAAOGOECBAgHC5CTlIIMeS3UA4hIAoEVAjgqAicgloVUABpVqNllJUqrRSiy2tKLTFSttoUbFF7W92/5ljd5bsYvBj253P5/HNDrPz3ryZnd2Z+b/31P0i1+K4yGS/NJP9GI6dsLmsrwVOwgiciq0wC61ox9ZYjG30McKST6ZJue+X/V6OsfgADsd1OBEfRBuuR3eMs1w7yzX1Jo8Y52RZ33jshhOQZJmIk3EyzsMpuAxT8V6cig/jNNyC07Xycx3su/xPSn5PSfl/LOV/Wsr/jJT/WVlfKWmrrO+Psr6G6JT1bZT1bZL1PYzD8BEcj4/iTHwM83ELrsPHpdxb8XXchkdxB57EJ/B93IWUg/XL9alct24ihfL3WinH7VIOm9RjmtRjOk7FTHRiFi7HbLwPZ+MjmItP4Rx8B+fi7zEPv8V8rEOehdgY52FTLNLqiWtT3/W0X8r3nNTT81JPB6SeDko9vSD19KLU02Gpp59IPb0k9fRTqadXpZ4q1P4R5RoUS0ibPPpHHKyUG4dgGxyG/XAkjsBEHIOjcB6ORgcyT7ZTrifxSZPtXCLrvwNjcBkOwFJZ/3LZLytwKq7EWXgXzsW7cQGuwqV4D27H1bgT16rbKdeSON9kOxvUohzYENtgI+yGN+EYbILTMQzzsCnOw3CU7x+uEX1//8yX758FGI4l2A4XquWT6zrMNilfH6mnWGyJcTgY++Jw7I/JGI8zcACm40D1fC7XazjR87wsseNNsDaOxbqyXQm15FpLrsF4n2v7YlCZrPK7pjW2wjYYiW2xH3bGYdgFkzEKp2B3XIK9cCXGYDn2xo0Yh9uwLz6J/fBZjMc3cQC+gwPxLA7C8zgYv8RhqHz+huNNOALD8DbsiKOxPyZhAo7BFByLU3E85mEW3o3ZuB5z8Cjm4SdYgJ9jIX6LdgyhnoqwITpQ7a/0V1q/ptEk835N5ToJu1Sz3FZZrpOP5RLrWgx97TR4ghhRjMKqPkuT+buEtJN0nHSRZN1VM33yXKs47+RdIcFY7+8x1rtBRZ1gvPcPJN47j2O/jLSHVEE6R6q7mz61SMkkJ2k96QDpNOkyKWJPiCWGlEoqIW0mVZDOkOo+yfmAlEyyk8pJ+0inSBdJoU/RZ+pTwfjx4BScglNwCk7BKTgFp+AUnIJTcPqhTN9D/L+9qKBm4v+duvj/k3IfcQ+ptTzzeJw/Eg5zb0uLySfz3AKnH/EkVTEUxSbj/CWajPOX7DnOn8xP1caMy7KnF6U7C4tc89OYP7YqxsPmYHaWaex+Ox+x+/uYd4INS8F7D2ux+5HeMaCGOJhNEp9/EFvjPtzGH9afSD1JFQUSn9XOMz7LpH7SfNRPjkk9SIyEFgMj2zFC4jESJOZ+IamZrHcHy5b/1CSOKD1vdmFRrjMn3+H3vveOJTLZ7zLP6hWLpsU7RUks/GZSE3En64x+RS2nV8w0UMrZ1ZaxkaUB8BxHWZfEJG12/90uaWxf1+sH1ddxrter1dexrtfL1dd9XK9L1Ne9Xa8L1dcxvuOrZJ9s8jU24Ks1FxdUlVf4dT7GBnz12sbj9JH8T0n+yvO4DvgtaRfvt7vzV4Pw5IBzlaGkmvE60pDxOqR/Te94PqVMZSbHX7Tad9vsrAJdHF58c5nnHqrSMF4=
*/