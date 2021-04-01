/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_FORWARD_MAIN_07212005_1105)
#define FUSION_MAP_FORWARD_MAIN_07212005_1105

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_DECLTYPE)             \
  || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_RVALUE_REFERENCES))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   define BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no decltype and variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/map_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct map;
}}

#endif
#endif

/* map_fwd.hpp
k0/6vvZQZrE+C+TkO6YHH5uAojhwnhVqHFLn01f6Sk6pcJyid1tfhZa8htzXlKbdUcCL7/LaQ8OhsMhuF4uKyF+wZIO9Rnh92XEgIQHVoGjVtlEj9nVrYt4Nm544oNcd+5TBVESAfsbYQcSWfOvsF/xQnfS87iUeXoYvt5NHzHYEEAhIUNBN4r4jZk03PTjcG3740f8J7Jhu74no6F3vZKVG4TxAChchBHnI985CAM6zYD2uvc1BJM0/xOxW/gvYZWHFteyPkjLyOBwemcC98B2mGTVxjA4I4qYEM01Xue39h/JtSjsEUsS6o5gv+ndECct2GfSU+o+0/KvAeM/T9YqDBRrE3Qe8eLzurI2LGPftU9AwB32kbkl9Q0yTOnsYCqkZcyg/TAhC/cN9it6G30nspBtcuO5Mudl/mHQE1E9yrvNEyspEQyqVihdaUv/8268r9+x2iIMYYrLXAfrUhK7bkcnpUMcOFPVYpubNLQSb4h+uS4T1rcvFffG/9GMDHHfZt79fHHj+Z9x66JXlgBkDdxEQClYtzktGcAbzHQB4Zvxn1hlh5Er20w==
*/