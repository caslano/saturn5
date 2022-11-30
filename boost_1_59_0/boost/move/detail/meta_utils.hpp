//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_META_UTILS_HPP
#define BOOST_MOVE_DETAIL_META_UTILS_HPP

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>  //forceinline
#include <boost/move/detail/meta_utils_core.hpp>
#include <cstddef>   //for std::size_t
#include <boost/move/detail/addressof.hpp>

//Small meta-typetraits to support move

namespace boost {

//Forward declare boost::rv
template <class T> class rv;

namespace move_detail {

//////////////////////////////////////
//          is_different
//////////////////////////////////////
template<class T, class U>
struct is_different
{
   static const bool value = !is_same<T, U>::value;
};

//////////////////////////////////////
//             apply
//////////////////////////////////////
template<class F, class Param>
struct apply
{
   typedef typename F::template apply<Param>::type type;
};

//////////////////////////////////////
//             bool_
//////////////////////////////////////

template< bool C_ >
struct bool_ : integral_constant<bool, C_>
{
     operator bool() const { return C_; }
   bool operator()() const { return C_; }
};

typedef bool_<true>        true_;
typedef bool_<false>       false_;

//////////////////////////////////////
//              nat
//////////////////////////////////////
struct nat{};
struct nat2{};
struct nat3{};

//////////////////////////////////////
//          yes_type/no_type
//////////////////////////////////////
typedef char yes_type;

struct no_type
{
   char _[2];
};

//////////////////////////////////////
//            natify
//////////////////////////////////////
template <class T> struct natify{};

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
//             remove_pointer
//////////////////////////////////////

template< class T > struct remove_pointer                    { typedef T type;   };
template< class T > struct remove_pointer<T*>                { typedef T type;   };
template< class T > struct remove_pointer<T* const>          { typedef T type;   };
template< class T > struct remove_pointer<T* volatile>       { typedef T type;   };
template< class T > struct remove_pointer<T* const volatile> { typedef T type;   };

//////////////////////////////////////
//             add_pointer
//////////////////////////////////////
template< class T >
struct add_pointer
{
   typedef typename remove_reference<T>::type* type;
};

//////////////////////////////////////
//             add_const
//////////////////////////////////////
template<class T>
struct add_const
{
   typedef const T type;
};

template<class T>
struct add_const<T&>
{
   typedef const T& type;
};

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template<class T>
struct add_const<T&&>
{
   typedef T&& type;
};

#endif

//////////////////////////////////////
//      add_lvalue_reference
//////////////////////////////////////
template<class T>
struct add_lvalue_reference
{  typedef T& type;  };

template<class T> struct add_lvalue_reference<T&>                 {  typedef T& type;  };
template<>        struct add_lvalue_reference<void>               {  typedef void type;   };
template<>        struct add_lvalue_reference<const void>         {  typedef const void type;  };
template<>        struct add_lvalue_reference<volatile void>      {  typedef volatile void type;   };
template<>        struct add_lvalue_reference<const volatile void>{  typedef const volatile void type;   };

template<class T>
struct add_const_lvalue_reference
{
   typedef typename remove_reference<T>::type         t_unreferenced;
   typedef typename add_const<t_unreferenced>::type   t_unreferenced_const;
   typedef typename add_lvalue_reference
      <t_unreferenced_const>::type                    type;
};

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
//             identity
//////////////////////////////////////
template <class T>
struct identity
{
   typedef T type;
   typedef typename add_const_lvalue_reference<T>::type reference;
   reference operator()(reference t)
   {  return t;   }
};

//////////////////////////////////////
//          is_class_or_union
//////////////////////////////////////
template<class T>
struct is_class_or_union
{
   struct twochar { char dummy[2]; };
   template <class U>
   static char is_class_or_union_tester(void(U::*)(void));
   template <class U>
   static twochar is_class_or_union_tester(...);
   static const bool value = sizeof(is_class_or_union_tester<T>(0)) == sizeof(char);
};

//////////////////////////////////////
//             addressof
//////////////////////////////////////


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

template <class T, class U, bool IsSame = is_same<T, U>::value>
struct is_same_or_convertible
   : is_convertible<T, U>
{};

template <class T, class U>
struct is_same_or_convertible<T, U, true>
{
   static const bool value = true;
};

template<
      bool C
    , typename F1
    , typename F2
    >
struct eval_if_c
    : if_c<C,F1,F2>::type
{};

template<
      typename C
    , typename T1
    , typename T2
    >
struct eval_if
    : if_<C,T1,T2>::type
{};


#if defined(BOOST_GCC) && (BOOST_GCC <= 40000)
#define BOOST_MOVE_HELPERS_RETURN_SFINAE_BROKEN
#endif

template<class T, class U, class R = void>
struct enable_if_convertible
   : enable_if< is_convertible<T, U>, R>
{};

template<class T, class U, class R = void>
struct disable_if_convertible
   : disable_if< is_convertible<T, U>, R>
{};

template<class T, class U, class R = void>
struct enable_if_same_or_convertible
   : enable_if< is_same_or_convertible<T, U>, R>
{};

template<class T, class U, class R = void>
struct disable_if_same_or_convertible
   : disable_if< is_same_or_convertible<T, U>, R>
{};

//////////////////////////////////////////////////////////////////////////////
//
//                         and_
//
//////////////////////////////////////////////////////////////////////////////
template<bool, class B = true_, class C = true_, class D = true_>
struct and_impl
   : and_impl<B::value, C, D>
{};

template<>
struct and_impl<true, true_, true_, true_>
{
   static const bool value = true;
};

template<class B, class C, class D>
struct and_impl<false, B, C, D>
{
   static const bool value = false;
};

template<class A, class B, class C = true_, class D = true_>
struct and_
   : and_impl<A::value, B, C, D>
{};

//////////////////////////////////////////////////////////////////////////////
//
//                            or_
//
//////////////////////////////////////////////////////////////////////////////
template<bool, class B = false_, class C = false_, class D = false_>
struct or_impl
   : or_impl<B::value, C, D>
{};

template<>
struct or_impl<false, false_, false_, false_>
{
   static const bool value = false;
};

template<class B, class C, class D>
struct or_impl<true, B, C, D>
{
   static const bool value = true;
};

template<class A, class B, class C = false_, class D = false_>
struct or_
   : or_impl<A::value, B, C, D>
{};

//////////////////////////////////////////////////////////////////////////////
//
//                         not_
//
//////////////////////////////////////////////////////////////////////////////
template<class T>
struct not_
{
   static const bool value = !T::value;
};

//////////////////////////////////////////////////////////////////////////////
//
// enable_if_and / disable_if_and / enable_if_or / disable_if_or
//
//////////////////////////////////////////////////////////////////////////////

template<class R, class A, class B, class C = true_, class D = true_>
struct enable_if_and
   : enable_if_c< and_<A, B, C, D>::value, R>
{};

template<class R, class A, class B, class C = true_, class D = true_>
struct disable_if_and
   : disable_if_c< and_<A, B, C, D>::value, R>
{};

template<class R, class A, class B, class C = false_, class D = false_>
struct enable_if_or
   : enable_if_c< or_<A, B, C, D>::value, R>
{};

template<class R, class A, class B, class C = false_, class D = false_>
struct disable_if_or
   : disable_if_c< or_<A, B, C, D>::value, R>
{};

//////////////////////////////////////////////////////////////////////////////
//
//                      has_move_emulation_enabled_impl
//
//////////////////////////////////////////////////////////////////////////////
template<class T>
struct has_move_emulation_enabled_impl
   : is_convertible< T, ::boost::rv<T>& >
{};

template<class T>
struct has_move_emulation_enabled_impl<T&>
{  static const bool value = false;  };

template<class T>
struct has_move_emulation_enabled_impl< ::boost::rv<T> >
{  static const bool value = false;  };

//////////////////////////////////////////////////////////////////////////////
//
//                            is_rv_impl
//
//////////////////////////////////////////////////////////////////////////////

template <class T>
struct is_rv_impl
{  static const bool value = false;  };

template <class T>
struct is_rv_impl< rv<T> >
{  static const bool value = true;  };

template <class T>
struct is_rv_impl< const rv<T> >
{  static const bool value = true;  };

// Code from Jeffrey Lee Hellrung, many thanks

template< class T >
struct is_rvalue_reference
{  static const bool value = false;  };

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template< class T >
struct is_rvalue_reference< T&& >
{  static const bool value = true;  };

#else // #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template< class T >
struct is_rvalue_reference< boost::rv<T>& >
{  static const bool value = true;  };

template< class T >
struct is_rvalue_reference< const boost::rv<T>& >
{  static const bool value = true;  };

#endif // #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template< class T >
struct add_rvalue_reference
{ typedef T&& type; };

#else // #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

namespace detail_add_rvalue_reference
{
   template< class T
            , bool emulation = has_move_emulation_enabled_impl<T>::value
            , bool rv        = is_rv_impl<T>::value  >
   struct add_rvalue_reference_impl { typedef T type; };

   template< class T, bool emulation>
   struct add_rvalue_reference_impl< T, emulation, true > { typedef T & type; };

   template< class T, bool rv >
   struct add_rvalue_reference_impl< T, true, rv > { typedef ::boost::rv<T>& type; };
} // namespace detail_add_rvalue_reference

template< class T >
struct add_rvalue_reference
   : detail_add_rvalue_reference::add_rvalue_reference_impl<T>
{ };

template< class T >
struct add_rvalue_reference<T &>
{  typedef T & type; };

#endif // #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template< class T > struct remove_rvalue_reference { typedef T type; };

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   template< class T > struct remove_rvalue_reference< T&& >                  { typedef T type; };
#else // #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   template< class T > struct remove_rvalue_reference< rv<T> >                { typedef T type; };
   template< class T > struct remove_rvalue_reference< const rv<T> >          { typedef T type; };
   template< class T > struct remove_rvalue_reference< volatile rv<T> >       { typedef T type; };
   template< class T > struct remove_rvalue_reference< const volatile rv<T> > { typedef T type; };
   template< class T > struct remove_rvalue_reference< rv<T>& >               { typedef T type; };
   template< class T > struct remove_rvalue_reference< const rv<T>& >         { typedef T type; };
   template< class T > struct remove_rvalue_reference< volatile rv<T>& >      { typedef T type; };
   template< class T > struct remove_rvalue_reference< const volatile rv<T>& >{ typedef T type; };
#endif // #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

// Ideas from Boost.Move review, Jeffrey Lee Hellrung:
//
//- TypeTraits metafunctions is_lvalue_reference, add_lvalue_reference, and remove_lvalue_reference ?
//  Perhaps add_reference and remove_reference can be modified so that they behave wrt emulated rvalue
//  references the same as wrt real rvalue references, i.e., add_reference< rv<T>& > -> T& rather than
//  rv<T>& (since T&& & -> T&).
//
//- Add'l TypeTraits has_[trivial_]move_{constructor,assign}...?
//
//- An as_lvalue(T& x) function, which amounts to an identity operation in C++0x, but strips emulated
//  rvalue references in C++03.  This may be necessary to prevent "accidental moves".

}  //namespace move_detail {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_DETAIL_META_UTILS_HPP

/* meta_utils.hpp
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
*/