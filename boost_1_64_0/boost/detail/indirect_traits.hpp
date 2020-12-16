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
TgAk3kosG5XLyuLEEyKLF1eHf7Ie4i+52MtfPjxNyvbna7pwk25T59Y6O63/P8v1/yuaTH+WXPNHfczzbfBBnG+Wc6pIKjjP4+P/U5pQAJXp4/88zp8vWBHDrPVZTktUZ6Urq60/BbgT5swj7/I5A6tT4HxIFpFStr+srtA0Ef0ygk3rvZylzwsx2erTZLOLyYa1nvtSn2gXUv+isX83GPuXuYPx9zuGTcSw4gNj54qbao8wfHsYm8whNtr0Yxq3Mmi11Di7yPqNWl/0I84uY+sVFYz1R52saZxT1PpLRIiIQIfsUpEjiJiqff7w0Ro5zmIyUcUZoNWGgjgREPUrCfUfj4oZ0PLz/4YZYOlfkon3P6/Tdeb+F0jNEP+ZtV2AGr3Ewy9a1CtXN5C2nc1mZ8d2uv9xk9oMhhLNNRrzRPgIJoQBoaAImImHso/XyHAoy4XlBAbIoJX4+79xG1LDyuWWBhYcDwfgkQUMKDyTSl/SvSHTKVm6a3XRnZQCdJqE1GaBJACAw/wWIuX4k4IwmDRHzx9Qb4pshUny+kfGfAoM47n2wixTrpxXSNP3pdZn6WfBy8fzMFLw5Rm5daGasDF+JyVFOWgCpTs4XE/JzBzQZMGg5ldEi2lUczeUF+qlE4W4Al1EqpyNR9KEQmiDnNwfbUPdeQZuO3Ow+GAqPguL32gs/hQVj/ojg8qo9/+v4ljIOwjVpjqq6q8262idnL+c2jCm28WAIcwRQUmexJL1k3VxpqMwAVsgXXDglkBLnhFZSJer7NusBrxIJBRZErJZnFW/inbTsV2Z3ggU81KaBPaJUxuOCGw5heuTWj/KAnR4v3q14pgZpXDoAnZDyDMiWcaukxDXg2rD8ZG8l1dhL2U6GADqjooMmj8Gv0lCezgVrw604RloH4Y1PE7Y8RvwYhFQrFhZGWPlYc5YiCMewZSYItl2phYO1f5lH9FPIpSwYDWkX7uaFvS+H1kv6Div2tO8avet3GNny3l1+TM4r8bIZV419G/ygoDKhFiSaO3SZvNCtoJvT4Fi3z8vG7dLOIEYGt1tr9Txljcsety9F+khkVnxAlg/p9CVXTPqb/dvoL+ToL/Fsr8TtmB/60s8a7UHwvZcanu4Vl6I39W10t9VJoGhbFswlHUKLqf1UT5lM7seK9q2Tt45Bv+Qu0EoFFHYji9W/EpC+8uMpjp4usZ6vd4N2x/FpbZ3h7G90P5fe3gl2eLXD/Oa4fj3bNxjwvf2d8LGt2CPgu+H94RFnz7m9prW0h5Vi6Jq5YkioEZZ3FvdW9tKY+3aM1speFBzeL+UpXV7RYtm6hP2a1cv/PXPyjqEmwwdH3L+bkSBtOyI0ztGs7UosuQh68c0KSD7ZGy0PfcdrQFrKJcNNAEy+anH+LFkia6itFVAIRLiNnKJfwVZFP8OpJB3hOfGizpoxLPIm8itJdpgKi020Hn5E++5WEEn3wj5eqQWAdGDFeDGdDDbfTTbo3+Tq9sDcrYXPcXvarVdC8+ExVbY8/PILhK4P1uKd1WEQ/0FnJ/qYO8BJEvk5lTsH0hBcyppEQZ7WBcolcrlN6egZCr7S/ZYLn5T4+JWUIF0rMB3stR9GEaOF0w2wHDhF4Li5nYubkSD27mcDjWJVC9XEqnKl9BWNkWsSrXaB5ZSzWDtbBmfwrnasHsVLeSsiEA6KBhFfK7MLJy0FW+LUErar08JHyijxrEtMNpEYrQ1xySjrZGMlsBmAuw1OA1mHhNaya/eoXPjqfGd+RR3/4uyvy5hA+flQ+v18o0bOqONeZahsz0RD7O/87t73I3vOKT6B9KxKEfru1hyqVt77Tbj7WU03v4H2vPWErA17hzId3mXNnY=
*/