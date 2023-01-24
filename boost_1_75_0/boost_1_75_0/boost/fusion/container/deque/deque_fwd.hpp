/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_FORWARD_02092007_0749)
#define FUSION_DEQUE_FORWARD_02092007_0749

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   define BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/deque/detail/cpp03/deque_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct deque;
}}

#endif
#endif

/* deque_fwd.hpp
XRXsVijpX6/ef1u1247EpKJRKR64Utu2UtsmrLjzr8K4UK2b4UbiRL75O84C2afd9p2WIMVYan4UTX7f7AZ7hwq+jrR6Sbd3iNPvHZAp9KkV7CGplthBAhzlg3/SWTU/bj5Dx3VwlCv41SB+z9u8dfEZX3uG9+9VjVF4RbF+Kh7T27+leV6gCi4F6P8TIASXQCGvDAFXgd3q5vUcPWTo19yubJVmE0GkQQpuNlMzpdl8GnbIFPL99m0RBlNMcOjBWFRfZrONQFQEO8GtQC7VwkPHk20XwhXVYbZQHc4vQOFA9f9xmS/sgr0AFfYpgDc6vUsxWM/6KIKr3uzKoqBXvYn1f75PkX7uSfHNSk7iOn7TaZLtO5zWyvacl6thTpyf39BPx89p62Z1CNnyyg6NoNpka6yiyge+fo74eu4M5OtPzUS+/thdxNehk1z4NfF1ZCPmd3dwvo5tRR9GKGKhkAMxD8I3UYpUJT48neH2okcQX+PvDCKxEgZziM1ziGBamM4RVVatggwGDXMS7E91KnKxtYBzE/psTzKq4SMKfVrivjRnnxBJqHKBrkxrdlg2GKAIT0Q1G2bAjtKdprJ1gQQUqRbRkYQrXxbmaqSO11EV95rwpUmVezFklK+7zUD7u1SX+TOk/TPohxQMVN4VJIC914qvMbIH6rZUROLdQ4gNp8qDNkZArEyas19Ty9og3pbL8zJsgDaZtUWp
*/