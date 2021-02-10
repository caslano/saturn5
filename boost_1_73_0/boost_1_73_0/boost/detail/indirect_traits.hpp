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
Q1VSTE9QVF9JU1NVRVJDRVJULjNVVAUAAbZIJGCtVm1v2zYQ/q5fcfC+2IUiN+uALFtXTHOVVYtiGZLczoABgZaoiKssCiSVF6z777uj5MZJC6QfqsCmfCLvnrt77lG87QRefLfL8cgdPHvl9pPjhevh0ErJf3hhvn4gzz/B8IcHt7h+Q6g5PJz6lM/gm059gqk9lY+xXtN9nn9DuC2BpK85Hd7mdIuW4eR4fiG7eyWuawPTxQxOz89/hhP48eXpTy59n7nwlrWCN5Aa3u64unbhdWktv9fs7s7T/I0L3ABrvEdus1po0LIyt0xxwPtGFLzVvASmoeS6UGKHP0QLpuZQiYbDIl5twuWfLtzWoqhHP/eyB13LvimhZjccFC+4uBncdEwZkBV6QP+l0AZ99kbI1sPwHAxXez26IRCs0RLYDRMN22E4ZqA2ptO/zOdFrxrMZF7KQs+LQ0G82uyfZLVBNHt2D7IzYCT0mrtA+13Yy1JUtGKJ0Nj1u0bo2n2AhQHbci4VaN40ozs8KrgeUuCQjtVyaSd0iF4YWrRsNUW7reX+0UYs6+io6lWL4bAsuK+UWHgX+rbkyu63hThEGatsS/5Myx6wlyBbRAUTP4UwncCOaaFd+BBm7+J1Bh/8JPGX2QbiC/CXm9Hf
*/