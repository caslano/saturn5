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
template<class T>
struct addr_impl_ref
{
   T & v_;
   BOOST_MOVE_FORCEINLINE addr_impl_ref( T & v ): v_( v ) {}
   BOOST_MOVE_FORCEINLINE operator T& () const { return v_; }

   private:
   addr_impl_ref & operator=(const addr_impl_ref &);
};

template<class T>
struct addressof_impl
{
   BOOST_MOVE_FORCEINLINE static T * f( T & v, long )
   {
      return reinterpret_cast<T*>(
         &const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
   }

   BOOST_MOVE_FORCEINLINE static T * f( T * v, int )
   {  return v;  }
};

template<class T>
BOOST_MOVE_FORCEINLINE T * addressof( T & v )
{
   return ::boost::move_detail::addressof_impl<T>::f
      ( ::boost::move_detail::addr_impl_ref<T>( v ), 0 );
}

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