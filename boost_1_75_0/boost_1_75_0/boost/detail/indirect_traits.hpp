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
AffR0Kz/qgwyH/iS+43EwBjIXI3mlP9BTeowj6mg3hz+dcRXc61RdCUH1iPoDzMSk1LIfpgoEF3NIem5SvC4XYjiD67S/+HRcpa87PSRFJL14egdi86PA5OZUTkicgjVL9Dzuzfny/jPRTVOrr/t+vj5YYuOAJosRGX9LctKHsXub7uuIkEzyljwTpPSF4q6hJc98NuuHzqqpm2IirL+xa4zuJNfxr6clI+nb0bfH6Ku8XWw8/eDfKfyUt6BBogV8Duzl5Dy/dWuB9aSpYvdhst/Ri9M/Q3gxhJnuVMa01Y1Uyx3E5bz7iT2mCaiYq57klK3e3ffi3g9476wM1/ScArC3szwH7KzXzOvKGEUfv7uiiY+gf+bv2s9Kgfkkhfu2CR/8/dXJX/t8Y96zel6o3aCs4l+mze8zoFcAo4ZHeLoaiPjfxSPoMdUJgp6o6TTUZ1XHc3ehXP0CVfyRy6g6jvp+/GTPxpdJCiX6b/9Y0GWOz9h7P7mnwgTODbfkFC8XowCzuIet5+V4yJe+RNLZuvAt+GvpVTsNmYfJdF+eHgyFkzUzcTUTxWUUO2LHpTAJRYngoHSYd2HwIO0xc/SCiGKIXEMMMHF9z3h3Vvr++rHOMg3SJX14rPM6yi/x41chcdzFbZtbDPINjajkuQbgeTXajM+yKLLOJnixy3XtETmzGpfi5h47D9yMS7WbSUMcCUDdOndNIboIFW+
*/