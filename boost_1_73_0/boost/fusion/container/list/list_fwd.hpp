/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_FORWARD_10262014_0528
#define FUSION_LIST_FORWARD_10262014_0528

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if  defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   undef BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   define BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct void_;

    template <typename ...T>
    struct list;
}}

#endif
#endif

/* list_fwd.hpp
/7gXZTqIllSvjy84bkdzfVQ6eXqdfifpngqd6azjfIIWuOs4Z6OfoTslreNcgH6P7op19ah3jXWQ69JbsjQs+eSy9bnk80roYq7jZejObnfnUvQ7dPek7s6VaFKouzMBvRn13wvy9F6wTPJ4OnQWLf9TdBt3Xecc9HN0VNK6zoXoD+iY0LrOVai8R5bylEgeXnYd5FzdFzqNa3opOtzt7JyBfoxun9TZORddhu4c6uxcjnaS
*/