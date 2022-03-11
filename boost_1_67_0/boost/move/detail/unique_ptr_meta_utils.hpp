//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_UNIQUE_PTR_DETAIL_META_UTILS_HPP
#define BOOST_MOVE_UNIQUE_PTR_DETAIL_META_UTILS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>   //for std::size_t

//Small meta-typetraits to support move

namespace boost {

namespace movelib {

template <class T>
struct default_delete;

}  //namespace movelib {

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
//Forward declare boost::rv
template <class T> class rv;
#endif

namespace move_upmu {

//////////////////////////////////////
//              nat
//////////////////////////////////////
struct nat{};

//////////////////////////////////////
//            natify
//////////////////////////////////////
template <class T> struct natify{};

//////////////////////////////////////
//             if_c
//////////////////////////////////////
template<bool C, typename T1, typename T2>
struct if_c
{
   typedef T1 type;
};

template<typename T1, typename T2>
struct if_c<false,T1,T2>
{
   typedef T2 type;
};

//////////////////////////////////////
//             if_
//////////////////////////////////////
template<typename T1, typename T2, typename T3>
struct if_ : if_c<0 != T1::value, T2, T3>
{};

//enable_if_
template <bool B, class T = nat>
struct enable_if_c
{
   typedef T type;
};

//////////////////////////////////////
//          enable_if_c
//////////////////////////////////////
template <class T>
struct enable_if_c<false, T> {};

//////////////////////////////////////
//           enable_if
//////////////////////////////////////
template <class Cond, class T = nat>
struct enable_if : public enable_if_c<Cond::value, T> {};

//////////////////////////////////////
//          remove_reference
//////////////////////////////////////
template<class T>
struct remove_reference
{
   typedef T type;
};

template<class T>
struct remove_reference<T&>
{
   typedef T type;
};

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template<class T>
struct remove_reference<T&&>
{
   typedef T type;
};

#else

template<class T>
struct remove_reference< rv<T> >
{
   typedef T type;
};

template<class T>
struct remove_reference< rv<T> &>
{
   typedef T type;
};

template<class T>
struct remove_reference< const rv<T> &>
{
   typedef T type;
};


#endif

//////////////////////////////////////
//             remove_const
//////////////////////////////////////
template< class T >
struct remove_const
{
   typedef T type;
};

template< class T >
struct remove_const<const T>
{
   typedef T type;
};

//////////////////////////////////////
//             remove_volatile
//////////////////////////////////////
template< class T >
struct remove_volatile
{
   typedef T type;
};

template< class T >
struct remove_volatile<volatile T>
{
   typedef T type;
};

//////////////////////////////////////
//             remove_cv
//////////////////////////////////////
template< class T >
struct remove_cv
{
    typedef typename remove_volatile
      <typename remove_const<T>::type>::type type;
};

//////////////////////////////////////
//          remove_extent
//////////////////////////////////////
template<class T>
struct remove_extent
{
   typedef T type;
};
 
template<class T>
struct remove_extent<T[]>
{
   typedef T type;
};
 
template<class T, std::size_t N>
struct remove_extent<T[N]>
{
   typedef T type;
};

//////////////////////////////////////
//             extent
//////////////////////////////////////

template<class T, unsigned N = 0>
struct extent
{
   static const std::size_t value = 0;
};
 
template<class T>
struct extent<T[], 0> 
{
   static const std::size_t value = 0;
};

template<class T, unsigned N>
struct extent<T[], N>
{
   static const std::size_t value = extent<T, N-1>::value;
};

template<class T, std::size_t N>
struct extent<T[N], 0> 
{
   static const std::size_t value = N;
};
 
template<class T, std::size_t I, unsigned N>
struct extent<T[I], N>
{
   static const std::size_t value = extent<T, N-1>::value;
};

//////////////////////////////////////
//      add_lvalue_reference
//////////////////////////////////////
template<class T>
struct add_lvalue_reference
{
   typedef T& type;
};

template<class T>
struct add_lvalue_reference<T&>
{
   typedef T& type;
};

template<>
struct add_lvalue_reference<void>
{
   typedef void type;
};

template<>
struct add_lvalue_reference<const void>
{
   typedef const void type;
};

template<>
struct add_lvalue_reference<volatile void>
{
   typedef volatile void type;
};

template<>
struct add_lvalue_reference<const volatile void>
{
   typedef const volatile void type;
};

template<class T>
struct add_const_lvalue_reference
{
   typedef typename remove_reference<T>::type   t_unreferenced;
   typedef const t_unreferenced                 t_unreferenced_const;
   typedef typename add_lvalue_reference
      <t_unreferenced_const>::type              type;
};

//////////////////////////////////////
//             is_same
//////////////////////////////////////
template<class T, class U>
struct is_same
{
   static const bool value = false;
};
 
template<class T>
struct is_same<T, T>
{
   static const bool value = true;
};

//////////////////////////////////////
//             is_pointer
//////////////////////////////////////
template< class T >
struct is_pointer
{
    static const bool value = false;
};

template< class T >
struct is_pointer<T*>
{
    static const bool value = true;
};

//////////////////////////////////////
//             is_reference
//////////////////////////////////////
template< class T >
struct is_reference
{
    static const bool value = false;
};

template< class T >
struct is_reference<T&>
{
    static const bool value = true;
};

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template< class T >
struct is_reference<T&&>
{
    static const bool value = true;
};

#endif

//////////////////////////////////////
//             is_lvalue_reference
//////////////////////////////////////
template<class T>
struct is_lvalue_reference
{
    static const bool value = false;
};

template<class T>
struct is_lvalue_reference<T&>
{
    static const bool value = true;
};

//////////////////////////////////////
//          is_array
//////////////////////////////////////
template<class T>
struct is_array
{
   static const bool value = false;
};
 
template<class T>
struct is_array<T[]>
{
   static const bool value = true;
};
 
template<class T, std::size_t N>
struct is_array<T[N]>
{
   static const bool value = true;
};

//////////////////////////////////////
//          has_pointer_type
//////////////////////////////////////
template <class T>
struct has_pointer_type
{
   struct two { char c[2]; };
   template <class U> static two test(...);
   template <class U> static char test(typename U::pointer* = 0);
   static const bool value = sizeof(test<T>(0)) == 1;
};

//////////////////////////////////////
//             pointer_type
//////////////////////////////////////
template <class T, class D, bool = has_pointer_type<D>::value>
struct pointer_type_imp
{
    typedef typename D::pointer type;
};

template <class T, class D>
struct pointer_type_imp<T, D, false>
{
    typedef T* type;
};

template <class T, class D>
struct pointer_type
{
    typedef typename pointer_type_imp
      <typename remove_extent<T>::type, typename remove_reference<D>::type>::type type;
};

//////////////////////////////////////
//           is_convertible
//////////////////////////////////////
#if defined(_MSC_VER) && (_MSC_VER >= 1400)

//use intrinsic since in MSVC
//overaligned types can't go through ellipsis
template <class T, class U>
struct is_convertible
{
   static const bool value = __is_convertible_to(T, U);
};

#else

template <class T, class U>
class is_convertible
{
   typedef typename add_lvalue_reference<T>::type t_reference;
   typedef char true_t;
   class false_t { char dummy[2]; };
   static false_t dispatch(...);
   static true_t  dispatch(U);
   static t_reference       trigger();
   public:
   static const bool value = sizeof(dispatch(trigger())) == sizeof(true_t);
};

#endif

//////////////////////////////////////
//       is_unary_function
//////////////////////////////////////
#if defined(BOOST_MSVC) || defined(__BORLANDC_)
#define BOOST_MOVE_TT_DECL __cdecl
#else
#define BOOST_MOVE_TT_DECL
#endif

#if defined(_MSC_EXTENSIONS) && !defined(__BORLAND__) && !defined(_WIN64) && !defined(_M_ARM) && !defined(_M_ARM64) && !defined(UNDER_CE)
#define BOOST_MOVE_TT_TEST_MSC_FUNC_SIGS
#endif

template <typename T>
struct is_unary_function_impl
{  static const bool value = false; };

// avoid duplicate definitions of is_unary_function_impl
#ifndef BOOST_MOVE_TT_TEST_MSC_FUNC_SIGS

template <typename R>
struct is_unary_function_impl<R (*)()>
{  static const bool value = true;  };

template <typename R>
struct is_unary_function_impl<R (*)(...)>
{  static const bool value = true;  };

#else // BOOST_MOVE_TT_TEST_MSC_FUNC_SIGS

template <typename R>
struct is_unary_function_impl<R (__stdcall*)()>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R>
struct is_unary_function_impl<R (__fastcall*)()>
{  static const bool value = true;  };

#endif

template <typename R>
struct is_unary_function_impl<R (__cdecl*)()>
{  static const bool value = true;  };

template <typename R>
struct is_unary_function_impl<R (__cdecl*)(...)>
{  static const bool value = true;  };

#endif

// avoid duplicate definitions of is_unary_function_impl
#ifndef BOOST_MOVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0>
struct is_unary_function_impl<R (*)(T0)>
{  static const bool value = true;  };

template <typename R, class T0>
struct is_unary_function_impl<R (*)(T0...)>
{  static const bool value = true;  };

#else // BOOST_MOVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0>
struct is_unary_function_impl<R (__stdcall*)(T0)>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R, class T0>
struct is_unary_function_impl<R (__fastcall*)(T0)>
{  static const bool value = true;  };

#endif

template <typename R, class T0>
struct is_unary_function_impl<R (__cdecl*)(T0)>
{  static const bool value = true;  };

template <typename R, class T0>
struct is_unary_function_impl<R (__cdecl*)(T0...)>
{  static const bool value = true;  };

#endif

template <typename T>
struct is_unary_function_impl<T&>
{  static const bool value = false; };

template<typename T>
struct is_unary_function
{  static const bool value = is_unary_function_impl<T>::value;   };

//////////////////////////////////////
//       has_virtual_destructor
//////////////////////////////////////
#if (defined(BOOST_MSVC) && defined(BOOST_MSVC_FULL_VER) && (BOOST_MSVC_FULL_VER >=140050215))\
         || (defined(BOOST_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1500))
#  define BOOST_MOVEUP_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#elif defined(BOOST_CLANG) && defined(__has_feature)
#  if __has_feature(has_virtual_destructor)
#     define BOOST_MOVEUP_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#  endif
#elif defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) && !defined(__GCCXML__))) && !defined(BOOST_CLANG)
#  define BOOST_MOVEUP_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#elif defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)
#  define BOOST_MOVEUP_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#elif defined(__CODEGEARC__)
#  define BOOST_MOVEUP_HAS_VIRTUAL_DESTRUCTOR(T) __has_virtual_destructor(T)
#endif

#ifdef BOOST_MOVEUP_HAS_VIRTUAL_DESTRUCTOR
   template<class T>
   struct has_virtual_destructor{   static const bool value = BOOST_MOVEUP_HAS_VIRTUAL_DESTRUCTOR(T);  };
#else
   //If no intrinsic is available you trust the programmer knows what is doing
   template<class T>
   struct has_virtual_destructor{   static const bool value = true;  };
#endif

//////////////////////////////////////
//       missing_virtual_destructor
//////////////////////////////////////

template< class T, class U
        , bool enable =  is_convertible< U*, T*>::value &&
                        !is_array<T>::value &&
                        !is_same<typename remove_cv<T>::type, void>::value &&
                        !is_same<typename remove_cv<U>::type, typename remove_cv<T>::type>::value
        >
struct missing_virtual_destructor_default_delete
{  static const bool value = !has_virtual_destructor<T>::value;  };

template<class T, class U>
struct missing_virtual_destructor_default_delete<T, U, false>
{  static const bool value = false;  };

template<class Deleter, class U>
struct missing_virtual_destructor
{  static const bool value = false;  };

template<class T, class U>
struct missing_virtual_destructor< ::boost::movelib::default_delete<T>, U >
   : missing_virtual_destructor_default_delete<T, U>
{};

}  //namespace move_upmu {
}  //namespace boost {

#endif //#ifndef BOOST_MOVE_UNIQUE_PTR_DETAIL_META_UTILS_HPP

/* unique_ptr_meta_utils.hpp
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
*/