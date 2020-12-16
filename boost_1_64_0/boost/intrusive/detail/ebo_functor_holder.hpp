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
VGtYBvlNVup3Wqm/o5xDv/kXO8QG++4cokAFW/zmX+w/dnT/4aMGjRiuz4+5NKUS/50tJ+9rRNrGOUTbxAXndwm6RaHyWzCnQOY9lWeJivNcpI3lnKDswY48dcHsyQa/I02/vH0Jv4zkRZVR9zPjmIQ5x/Q7V41qBZf9Xc7VylBlV65W4Z2rlVvC97VaueXkfa2WpoTna7Xtf9jX6uj1dnjsHRfnVW/0z7OvqzU1YcJbK1787/e1ivhUiU+V1jdvP38sJ91R/L1b+3uP9vcM8a/ai4jfDO+6of1mKEIRQN/r//ICJJ5Kr0TicY5UvOHIEsIt8SeIg+1lrrnzYCbsAsfCbrAQ9oBLYE+ZKy0TFsM+8AHYV/yJBsKXYBb8h/jXJLk4r7ADzIZd4CiYDcfAmfAiOBeOhdfCcfBO8avZBC+FT8GJ8GmYA/fDXHgQToLvwcnwUzgNHoczYB3Kmg/T4SzYC66Bg+Gv4Ri4Fl4C74Gz4L2wCD4Ab4C/gevgg3ADfEj8ZR6GW+F6+Ae4AX4O1Vye4teSIP4sZ4qfzPnwcTgMPgnHwm1wOtwOl8Ln4d2wFN4Hd8LfwAK7/HA+fAYugPvhQvg2XAQ/gFfAb+GVMJnzfpV9fHgN7AavhwPhL2CObOfB5fBKuALeAm+Hd8BbYAm8Fe6Aq+FeuBS+Dq+Fb8Dr4BFYAD8XPxy+l5B/8ZNxnps4twY/mRTxW0mFybCh+Mk0gm1hM9he5nzrAZvAITAdXgibwvGi5/hfbCn3v1ge4H8xStMrClNvZSV6a39kf47/dV+On8KP43T7cPwY/hv/Db4bP7bfRsRn4+R9Nvb1x08DiR7gsVohQ5FFAyI+GpFf5Bf5RX6RX+T3c/n9NP3/k+fln6b+/5la//8et7cMJ1x8V4TfwIFp9oty+Xf4viOHVjj/X314m9L/wGX8Bruh/Jv8Gm0OoCT23a/2nW/s85Z4pj4qZ1yxnWZ9tW+e8+3+X4+qeYGcvsYytf0Lqw5hfv1Y2thlO/yLZJVO3uVaf+c2Oy5v9KY+6Ic3GPugnbIdVnHXqn0F6tGtwMljbbXvz8Y8+uaZK7DnYqxrr8e6tEvgGoepolNcrjMhzlUYup9N9PewY4etX2NpQWA/241sN5V5vfK1/rNZ0pe1nXivJfrP7dWNgl4gut2TEG3bltkyR8tz2vwxc9j+s/SZFSSX68/16nIsGdsd9pwA/vPbrdHm47BtxNA3pc55qL6pE57g9TsHpfHPJr9rosp9U8QPug4Mdo9exX1Tw9hv7ptCR+0bYjWrYM6Teaeh70nq2G/c+Ppqwf0ZYxpzjjfp/Rl06104Ykj/fqrnSZVxVOMK+zKIf/L9TqRtXJftrurBeb0I3SJzXqXnJbz8Fm0Kv++laNPJ972Mahzpe2n8Czv81g+Xf3FL17un9t5/7Lac1Qt+iPS9/C/1vTQS6+c+xzdb8mKRT+1vtS6HS54X5FnmEGxmx7UDZExmbRmT3Bi2k2/THeBA2Em+PXeGl8EMeAU8R9aVORfeJ30sG6WP5RnYFR6QvpbD8Hz4MewOv5M+lxjy0AvWg71hB9hP+lIGwP5wIBwKB9n5gENgARwKF0ofzDI4HN4KR8C1MBs+Ai+AW+FIeFDivy99NJ9JH803cJzzLV/uM2C84Vt+knzLry/f8hvIN/xU2EG+2XeSb/uZsDEcLN/2x8i3/XGi53zL3xT62/v7ml5RJXp3Rb7R/999o/+xxllGvtNHvtOfynf60YM9ViGyCtk2OPJ9PvKL/CK/yC/yi/wiv8gv8ov8Ir/IL/KL/P5Xfz9F//+kKyZOpQPf9gA4pf7/NCsu4flG9PNn2WMQ7KRVuhPz58yZuaA=
*/