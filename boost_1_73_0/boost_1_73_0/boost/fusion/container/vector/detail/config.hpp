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
v6xZWr2Rzol6c5ZjzT+7FJ9fgRtmNxrtsg8r/AgtO0xmQpvN76Sqg+0poO7rIbLPO6TKz8Lijob8iB1K0om9u6bLSoK+37DCpNzsdBXElGHMNSZIFZlFp6Z2t+MPhXRK/QdQSwMECgAAAAgALWdKUsXzh1p4OQAA8scAABkACQBjdXJsLW1hc3Rlci9saWIvY29ubmVjdC5jVVQFAAG2SCRg1X37W9tIlujv/BUF/QVs2hhIMrk70EnWAZP218RmsUk6d6avPtkuY21sySvJPGaT/33Po56SbCCTnnsvMx2wXKrHqXNOnXft7/64nw2xKx78Cei/AH7gN71xkSb/KUd5desg+Cr4f/DW3+H3Q4PsC/vK16AuHn7lq6jRK4Ea5Rf8OwgeGujvODf8Zx/f/HuAf8ITeA3fPEkW92l0Pc1F7aQuDv/6138Te+L5wfPDhjgN40jORD+X8VCm1w3xy5ie/Ps0vLtrZvJNQ8hchLOm6mowjTKRJZP8NkylgL9n0UjGmRyLMBNjmY3SaAgfoljkUykm0UyKk97F5073fUPcTqPRFDu5T5YimybL2VhMwxspUjmS0Q33sQjTXCQTeB06H0dZDh0u8yiJmzC2FLlM5xn2gcOHsywR4U0YzcIhDBTmYprni+xof3+0
*/