/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_CONFIG_11052014_1720
#define FUSION_VECTOR_CONFIG_11052014_1720

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/fusion/support/config.hpp>

#if (defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || defined(BOOST_NO_CXX11_RVALUE_REFERENCES) \
  || defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)  \
  || defined(BOOST_NO_CXX11_DECLTYPE)) \
  || defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) \
  || defined(BOOST_FUSION_DISABLE_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   undef BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   define BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   undef BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#endif

#endif


/* config.hpp
Y+it55Vzoo5jtm+f1Mu031baHGTf5nB1rDHXyFs+ttT5mM2mxiC3fMzs0+axohufyP7hyIu3DfTweee8DUMf3SxjP0+R7wP5fqjCUeRMyi3nxHLNzBNDsSemoje+gL1kDfHeOB998DDqsZJ9+OFq9Md1GICMZ9MF4l3YF3djEFa6Wq6F+La2XAsZjCE4GkMxD/tjGYbhZTgA16EBk/lbhuNUjMCfMBKVi9hReBpG45NufEfi2zgIv8AYbO1uuebcDWMxDONwOMbjxzgEf8EEvPFUzh1uxSQcdBpflLgZk/FhTMGEdlw7wx04Aj/GkbiyveVa9EYcheM7MEYOz8QxuBTT8Do8Ax/AsTjpdN53+D2m4284Htvy2cvAdjgBPTET63AivoGT8Dy+tSfj9ZiFtTgFn8ep+DFOw6VdeE/gxTgdV+JMvBNzMcjDcu36VjTiq1iA3+Is9OT9NBuVz+PeWW11B8lcR+FahOU6gOvstjovcp3B0nddF2npO12h9SdqSUta0pKWtKSlvzGd9Pifqd8RzFY8Uev/tenBPiT+r5Nxbxcrc0OwWFGZ/zpdjf85OrvIMRXnKI2QdecOOj8VyeyUtsR22oPjXFzMcVC9zBu2n8N+VI0h2afESxzQVhZhi/G+sJSVyVxou/nMheq6GibHOJe5yZtxG/v8lXzn9IZzk/Xm+meqc5PlfKjzlHwwGNuigfNRldv4fFimRp+E86H7869dGc+4hbb3Q5e85l/7Ect49ibnoTqfr3niYs+WxsItnRfbVOz8gznm/dJv0XM9Z75ysDjh0e43nz40jpjXfD7kMyCfjXrsTf7ZbjxyGEZgMkZiFkZhISbjZZiCNTgCt+BI3IWp6MXOR2MejsHZmIYX4hl4C47F7TgOX8F0HMDfNQMvwUy8Aifi1TgJazELH8UpuBOn4ts4Dd14PdnYA6fjCJyBEzEH83AmFmMucj7os5DPgHw26rEzea2cjw4yHrkzJmAXHIdeuAC740XYE69DbzyEPthW+gIC0BeT0A+vR3+swUC8G/vK+QjCzzAYf8R+qHxWQ2RtaMbtqfFklqxpnCrrEFvXIM6UNYaDZP1giTXVNYIl5pS1fNFurV2vqIbjeJ4kHj2oxaRa0pKWtKQlLWlJS/+LdPLjf5YdPkHxv3IPP4+OlgVXTtEVG42s7aSsjKaT+8z19ePBncp/W1iQO1c5apm5/Fflh7m5nAbllM3Nk3v6/dzd1pewTPoS8iU2mEHuzv5qJ1hjZ7kBPXuVw5pjZ69jrNmkd4iNO1AG1uutDe4nwBNzMkobcqQNhky1DSw0ZX1tx7+WlePx9WhycvzlcvwQWU8skBysnAP1+OZXb77wfjzr6cu1avvjS9zveA2/4b3E2sna+qOlHcOlHfW2dsi76sS3wfp+qJY2TJY2ZEgb0ic6tsHyvigwnvi2JEhbnnW1rc/viZXYj7bUNW5L+Xxra1pwzwHH9sxx0h7H8Q/WPh1/9b1s5HmDcQPmz14I7Vx2v/LZK5tTOMtUFmF7D0q9fPPzULv3ZIcGYyHKHMc8RIA69qK8jbntDf52aXIfv0nyORpPDqUdNdkNzpf9F8gJ+yxb/2Z7Wze+h+b7HKCjpV9GWYndWLwwp8H3yvGswe3HOTWh/kFlLmHOnEJjgeNO/tf9YiGlSvkl/ntWLZ4YOCMspfDI1+v3MvrFMv9fvs8xX+at28//HyrzVIdhKCbjBEzByTgcp+AInIHWe7Kl6uQ7Go2y3zbkeNnvmbLfedgfTZiJ5TgdKzAHF6rzyuU7F0Nkf/bzRs+SebxLMBDPRuvrq5ftRjt5fXrZzhd90Q8jsA9GoT8mYwAOx77q+mDyvYeTZb8=
*/