// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef INDIRECT_TRAITS_DWA2002131_HPP
# define INDIRECT_TRAITS_DWA2002131_HPP
# include <boost/type_traits/integral_constant.hpp>
# include <boost/type_traits/is_function.hpp>
# include <boost/type_traits/is_reference.hpp>
# include <boost/type_traits/is_pointer.hpp>
# include <boost/type_traits/is_class.hpp>
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/is_volatile.hpp>
# include <boost/type_traits/is_member_function_pointer.hpp>
# include <boost/type_traits/is_member_pointer.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/type_traits/remove_pointer.hpp>

# include <boost/detail/workaround.hpp>
# include <boost/detail/select_type.hpp>


namespace boost { namespace detail {

namespace indirect_traits {

template <class T>
struct is_reference_to_const : boost::false_type
{
};

template <class T>
struct is_reference_to_const<T const&> : boost::true_type
{
};

#   if defined(BOOST_MSVC) && _MSC_FULL_VER <= 13102140 // vc7.01 alpha workaround
template<class T>
struct is_reference_to_const<T const volatile&> : boost::true_type
{
};
#   endif

template <class T>
struct is_reference_to_function : boost::false_type
{
};

template <class T>
struct is_reference_to_function<T&> : is_function<T>
{
};

template <class T>
struct is_pointer_to_function : boost::false_type
{
};

// There's no such thing as a pointer-to-cv-function, so we don't need
// specializations for those
template <class T>
struct is_pointer_to_function<T*> : is_function<T>
{
};

template <class T>
struct is_reference_to_member_function_pointer_impl : boost::false_type
{
};

template <class T>
struct is_reference_to_member_function_pointer_impl<T&>
    : is_member_function_pointer<typename remove_cv<T>::type>
{
};


template <class T>
struct is_reference_to_member_function_pointer
    : is_reference_to_member_function_pointer_impl<T>
{
};

template <class T>
struct is_reference_to_function_pointer_aux
    : boost::integral_constant<bool,
          is_reference<T>::value &&
          is_pointer_to_function<
              typename remove_cv<
                  typename remove_reference<T>::type
              >::type
          >::value
      >
{
    // There's no such thing as a pointer-to-cv-function, so we don't need specializations for those
};

template <class T>
struct is_reference_to_function_pointer
    : boost::detail::if_true<
          is_reference_to_function<T>::value
      >::template then<
          boost::false_type
        , is_reference_to_function_pointer_aux<T>
      >::type
{
};

template <class T>
struct is_reference_to_non_const
    : boost::integral_constant<bool,
          is_reference<T>::value &&
          !is_reference_to_const<T>::value
      >
{
};

template <class T>
struct is_reference_to_volatile : boost::false_type
{
};

template <class T>
struct is_reference_to_volatile<T volatile&> : boost::true_type
{
};

#   if defined(BOOST_MSVC) && _MSC_FULL_VER <= 13102140 // vc7.01 alpha workaround
template <class T>
struct is_reference_to_volatile<T const volatile&> : boost::true_type
{
};
#   endif


template <class T>
struct is_reference_to_pointer : boost::false_type
{
};

template <class T>
struct is_reference_to_pointer<T*&> : boost::true_type
{
};

template <class T>
struct is_reference_to_pointer<T* const&> : boost::true_type
{
};

template <class T>
struct is_reference_to_pointer<T* volatile&> : boost::true_type
{
};

template <class T>
struct is_reference_to_pointer<T* const volatile&> : boost::true_type
{
};

template <class T>
struct is_reference_to_class
    : boost::integral_constant<bool,
          is_reference<T>::value &&
          is_class<
              typename remove_cv<
                  typename remove_reference<T>::type
              >::type
          >::value
      >
{
};

template <class T>
struct is_pointer_to_class
    : boost::integral_constant<bool,
          is_pointer<T>::value &&
          is_class<
              typename remove_cv<
                  typename remove_pointer<T>::type
              >::type
          >::value
      >
{
};


}

using namespace indirect_traits;

}} // namespace boost::python::detail

#endif // INDIRECT_TRAITS_DWA2002131_HPP

/* indirect_traits.hpp
zrkRhBk8AJ479gtyWLtUO1Q9cwAh6A+XSWRVWlOxZKHCtaf4OamkDMch7SmEqidnkxhuZdb+Z+rq8sa2ibtmrKZWi1oYi+UZJrolQPGB3LyWvbP/uCgY/l4uLQ72gmLRFaVD+DjGMc4PGRqQVkuG2yuEAo6Pok2/vYB9bF8IV3PpITe2v7J9GJhm/Vc4aBC0o2cDpG8Ebx9Vo1r/qY9oJIzvX8YvzYiIH8p3FQVsri9icDUH9rpu+Qx23mjFgQHM/tLpb1jUX5AiyEIWWcTc/xKOIYT09RBeRtCia2Edpy3aIczakYu6NXpSxCkmJbmhuDTbfxRb8nsOFtnR5rEnRHxPr7X0PYIkZBrksD1ztC2PYsu5L4/mZ08gTAFaW0NepA3qbnf4TsA9Dy2gjUd8EOSSaHSAmXMDruyZiN7j1SGPSw5vD8LFU5GdDeWou1LOap5TDxjKnbfaY+FzjKTx9NjWaB+ze6Mfp3s9VLB813CRSmLjW88Q6MVKX8+a03+nOPwCsgycFHT/Af3pGW2Ndov6AM8AlfKD790qfV5GLrI3c/5pICWPZ4En5g==
*/