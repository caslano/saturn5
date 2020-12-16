//  (C) Copyright John Maddock 2002 - 2003. 
//  (C) Copyright Jens Maurer 2002 - 2003. 
//  (C) Copyright Beman Dawes 2002 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Comeau STL:

#if !defined(__LIBCOMO__)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__LIBCOMO__)
#      error "This is not the Comeau STL!"
#  endif
#endif

//
// std::streambuf<wchar_t> is non-standard
// NOTE: versions of libcomo prior to beta28 have octal version numbering,
// e.g. version 25 is 21 (dec)
#if __LIBCOMO_VERSION__ <= 22
#  define BOOST_NO_STD_WSTREAMBUF
#endif

#if (__LIBCOMO_VERSION__ <= 31) && defined(_WIN32)
#define BOOST_NO_SWPRINTF
#endif

#if __LIBCOMO_VERSION__ >= 31
#  define BOOST_HAS_HASH
#  define BOOST_HAS_SLIST
#endif

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_EXCEPTION
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

//
// Intrinsic type_traits support.
// The SGI STL has it's own __type_traits class, which
// has intrinsic compiler support with SGI's compilers.
// Whatever map SGI style type traits to boost equivalents:
//
#define BOOST_HAS_SGI_TYPE_TRAITS

#define BOOST_STDLIB "Comeau standard library " BOOST_STRINGIZE(__LIBCOMO_VERSION__)

/* libcomo.hpp
z3//bXxF82WOAXJHKjbQeXOFNMsCA0xicfm6xU2gubtYmUuf8HPROdv+oXFAK8us7vELF6nMJdjXzE668rionWh/MrudceR0mhNLDVBQo9jN5q1m0/gtF9dwYRvrvafzoA8tNzNH9LtV0mCFAS4x6zFge0Hqz5Wh+TVvPLAZjS0az+9DudqVaH6iVWG2pda5fZS7G89nzDoefUZt8aIVY2aafWqWNPjJAD5mUyZ/2k/tXGWA58zWz56Qg8Z2NR4rUYoVu5SvIx3vGwyQFxSrdCdyAc15tJnMvv+tUSPKYaM4boU9T6tNpjLRxmoU8z/9czPFbcZzK7Nit//2UDt/FutIYWPX9e9Jff2LASaCYhNi1+yi+rYaoDSzomn61aG5hFaY2eUvd3NTX6eKa/Gy6nVp4MG1DVno2saEJp/J+Pzf+E1++4M0x694LgDFtqf0Ok5zd5sBNjEr1GfrbWrndlwzMOt9rzvFeXdgf0YodrBMZ+oX/+7gOAgT98tFDnsMkJ/ZiQrDCtA4oI1hZrn8ZgYdK2hlmNnHe9dS7nsNMJKXudDVlfJD681s+ZH3fqpvX/h22tDimVXMsKYctUUlLoCWRzHxXY84F+wPMfEdkagPLbdi4rslMefRujM7Vj/t/6RBSvi2mNEcEYpdrNVsJ+V+KLQtJ231WtD5E601s9n3k7JQ7mj1IhSb/2HOUurr30Lnyzrbyg40J47gWj9KsUs/Jr+mPjtpgAiNYiOhwUk6/k4boCGzaZu/tqcyz4i1lLCoiVEp1J/nDfCKz6VpkJXm9QVcJzPb1ym/l+a1TznGvqQ6xnwq5lexgIrBxfBmUjGzillUzIpWm9muL/mV9TVaNsXE90eiX1TK9KG1YdZr/OJ8VN/vBuinmPj+SMShjWC26NiKL9Icf4jjQVjwb3dEO1NZbFF/aypTJQ4uhY+zoI3k/RLRuz6ViWaOUGz4wAtf6di8aoAXoNjpDTsi6Hi4ZoBDzDKM26yjHK7j/pZZ+o39K9HcvWGA11rFZqybvJXmxF0DvAPFxowYe4zi7oXP3YkWbvxcaOH6xatSZkAlznw/fJwtxELjnKEmvo8T/alifjSsgax35KwIGtuHBsjILNeyiCOU+yMDlIxg/Vn21g5q59Pw9TnRqkYq9nTaExOV+dwAgQjFyhX7+QwdD/+GlCm+/xNzXsXcaL8x+7uX4zjZKwPUZ5YmT4Zz0uA13l+KUKzQH9k30Ni+DV9fAK2bRrG5X88qe6D3ofM655iqU6ktHwzwSMR9/W8tPNl0lObuZwN9jwcaHPenSxdTfWjfMLswU7eMxu+LOIcIW76g0wPKAa0ls6oppxtS3Fc8L0UpdiSfbUDQOie6o4x0n1ajSUqab3mXR5ot2giLmS3Q6uKDBmDSGun+Z4QGgL83zYGWV1ikBuDvdE1uS3OjDWb2XcL7V9IsOiNomf0af/arNCtaVIRi6bNFbJTmMxihIyh2ueAIN8UZjXCM2dkdLUeRxRihN7MT44Z1kOZFi1ZM/O2qqC/Ugn9TKMwfasF3mQgLoEUxs+xq8FIapAm14PNnoq9TWaVqK6pIM6PVZtb6yNQC0pxo2Zgp91sB3GgOZoklK16lcUhrhKV8jPYlj5EG6YzQidniCy8zU31ohXmZgeyXpHnQHjEbHDu1IPVZ+tAyV5/6aaU0u8kIBZlNGvC/59JcaEV4WwqZB9H4oUUxu5Atykzjl8re3X7UndqC1p1Zmb03JlBbMhhhJrM6R1pE0BhlNEICs5+KvflM7UTLH6HYklm/r6c5mMUI1XifzfbOozi0XizuTsnhGrJsRojUsDn/8WB6yiG7EcqCYgPrHuxH8yWHEU4ws35+/YE=
*/