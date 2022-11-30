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
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
*/