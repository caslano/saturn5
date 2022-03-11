/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Joaquin M Lopez Munoz  2006-2013
// (C) Copyright Ion Gaztanaga          2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace intrusive {
namespace detail {

#if defined(BOOST_MSVC) || defined(__BORLANDC_)
#define BOOST_INTRUSIVE_TT_DECL __cdecl
#else
#define BOOST_INTRUSIVE_TT_DECL
#endif

#if defined(_MSC_EXTENSIONS) && !defined(__BORLAND__) && !defined(_WIN64) && !defined(_M_ARM) && !defined(_M_ARM64) && !defined(UNDER_CE)
#define BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS
#endif

template <typename T>
struct is_unary_or_binary_function_impl
{  static const bool value = false; };

// see boost ticket #4094
// avoid duplicate definitions of is_unary_or_binary_function_impl
#ifndef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R>
struct is_unary_or_binary_function_impl<R (*)()>
{  static const bool value = true;  };

template <typename R>
struct is_unary_or_binary_function_impl<R (*)(...)>
{  static const bool value = true;  };

#else // BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R>
struct is_unary_or_binary_function_impl<R (__stdcall*)()>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R>
struct is_unary_or_binary_function_impl<R (__fastcall*)()>
{  static const bool value = true;  };

#endif

template <typename R>
struct is_unary_or_binary_function_impl<R (__cdecl*)()>
{  static const bool value = true;  };

template <typename R>
struct is_unary_or_binary_function_impl<R (__cdecl*)(...)>
{  static const bool value = true;  };

#endif

// see boost ticket #4094
// avoid duplicate definitions of is_unary_or_binary_function_impl
#ifndef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (*)(T0)>
{  static const bool value = true;  };

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (*)(T0...)>
{  static const bool value = true;  };

#else // BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__stdcall*)(T0)>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__fastcall*)(T0)>
{  static const bool value = true;  };

#endif

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0)>
{  static const bool value = true;  };

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0...)>
{  static const bool value = true;  };

#endif

// see boost ticket #4094
// avoid duplicate definitions of is_unary_or_binary_function_impl
#ifndef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (*)(T0, T1)>
{  static const bool value = true;  };

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (*)(T0, T1...)>
{  static const bool value = true;  };

#else // BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__stdcall*)(T0, T1)>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__fastcall*)(T0, T1)>
{  static const bool value = true;  };

#endif

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0, T1)>
{  static const bool value = true;  };

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0, T1...)>
{  static const bool value = true;  };
#endif

template <typename T>
struct is_unary_or_binary_function_impl<T&>
{  static const bool value = false; };

template<typename T>
struct is_unary_or_binary_function : is_unary_or_binary_function_impl<T>
{};

template<typename T, typename Tag = void, bool = is_unary_or_binary_function<T>::value>
class ebo_functor_holder
{
   BOOST_COPYABLE_AND_MOVABLE(ebo_functor_holder)

   public:
   typedef T functor_type;

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder()
      : t_()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(const T &t)
      : t_(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(BOOST_RV_REF(T) t)
      : t_(::boost::move(t))
   {}

   template<class Arg1, class Arg2>
   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_FWD_REF(Arg1) arg1, BOOST_FWD_REF(Arg2) arg2)
      : t_(::boost::forward<Arg1>(arg1), ::boost::forward<Arg2>(arg2))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(const ebo_functor_holder &x)
      : t_(x.t_)
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_RV_REF(ebo_functor_holder) x)
      : t_(x.t_)
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_COPY_ASSIGN_REF(ebo_functor_holder) x)
   {
      this->get() = x.get();
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(ebo_functor_holder) x)
   {
      this->get() = ::boost::move(x.get());
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(const T &x)
   {
      this->get() = x;
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(T) x)
   {
      this->get() = ::boost::move(x);
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE T&       get(){return t_;}
   BOOST_INTRUSIVE_FORCEINLINE const T& get()const{return t_;}

   private:
   T t_;
};

template<typename T, typename Tag>
class ebo_functor_holder<T, Tag, false>
   :  public T
{
   BOOST_COPYABLE_AND_MOVABLE(ebo_functor_holder)

   public:
   typedef T functor_type;

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder()
      : T()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(const T &t)
      : T(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(BOOST_RV_REF(T) t)
      : T(::boost::move(t))
   {}

   template<class Arg1, class Arg2>
   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_FWD_REF(Arg1) arg1, BOOST_FWD_REF(Arg2) arg2)
      : T(::boost::forward<Arg1>(arg1), ::boost::forward<Arg2>(arg2))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(const ebo_functor_holder &x)
      : T(static_cast<const T&>(x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_RV_REF(ebo_functor_holder) x)
      : T(BOOST_MOVE_BASE(T, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_COPY_ASSIGN_REF(ebo_functor_holder) x)
   {
      const ebo_functor_holder&r = x;
      this->get() = r;
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(ebo_functor_holder) x)
   {
      this->get() = ::boost::move(x.get());
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(const T &x)
   {
      this->get() = x;
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(T) x)
   {
      this->get() = ::boost::move(x);
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE T&       get(){return *this;}
   BOOST_INTRUSIVE_FORCEINLINE const T& get()const{return *this;}
};

}  //namespace detail {
}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP

/* ebo_functor_holder.hpp
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
*/