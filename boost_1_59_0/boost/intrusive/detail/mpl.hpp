/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga        2006-2014
// (C) Copyright Microsoft Corporation  2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_MPL_HPP
#define BOOST_INTRUSIVE_DETAIL_MPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/move/detail/type_traits.hpp>
#include <cstddef>

namespace boost {
namespace intrusive {
namespace detail {
   
using boost::move_detail::is_same;
using boost::move_detail::add_const;
using boost::move_detail::remove_const;
using boost::move_detail::remove_cv;
using boost::move_detail::remove_reference;
using boost::move_detail::add_reference;
using boost::move_detail::remove_pointer;
using boost::move_detail::add_pointer;
using boost::move_detail::true_type;
using boost::move_detail::false_type;
using boost::move_detail::voider;
using boost::move_detail::enable_if_c;
using boost::move_detail::enable_if;
using boost::move_detail::disable_if_c;
using boost::move_detail::disable_if;
using boost::move_detail::is_convertible;
using boost::move_detail::if_c;
using boost::move_detail::if_;
using boost::move_detail::is_const;
using boost::move_detail::identity;
using boost::move_detail::alignment_of;
using boost::move_detail::is_empty;
using boost::move_detail::addressof;
using boost::move_detail::integral_constant;
using boost::move_detail::enable_if_convertible;
using boost::move_detail::disable_if_convertible;
using boost::move_detail::bool_;
using boost::move_detail::true_;
using boost::move_detail::false_;
using boost::move_detail::yes_type;
using boost::move_detail::no_type;
using boost::move_detail::apply;
using boost::move_detail::eval_if_c;
using boost::move_detail::eval_if;
using boost::move_detail::unvoid_ref;
using boost::move_detail::add_const_if_c;

template<std::size_t S>
struct ls_zeros
{
   static const std::size_t value = (S & std::size_t(1)) ? 0 : (1 + ls_zeros<(S>>1u)>::value);
};

template<>
struct ls_zeros<0>
{
   static const std::size_t value = 0;
};

template<>
struct ls_zeros<1>
{
   static const std::size_t value = 0;
};

// Infrastructure for providing a default type for T::TNAME if absent.
#define BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(TNAME)     \
   template <typename T>                                          \
   struct boost_intrusive_has_type_ ## TNAME                      \
   {                                                              \
      template <typename X>                                       \
      static char test(int, typename X::TNAME*);                  \
                                                                  \
      template <typename X>                                       \
      static int test(...);                                       \
                                                                  \
      static const bool value = (1 == sizeof(test<T>(0, 0)));     \
   };                                                             \
                                                                  \
   template <typename T, typename DefaultType>                    \
   struct boost_intrusive_default_type_ ## TNAME                  \
   {                                                              \
      struct DefaultWrap { typedef DefaultType TNAME; };          \
                                                                  \
      typedef typename                                            \
         ::boost::intrusive::detail::if_c                         \
            < boost_intrusive_has_type_ ## TNAME<T>::value        \
            , T, DefaultWrap>::type::TNAME type;                  \
   };                                                             \
   //

#define BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT(INSTANTIATION_NS_PREFIX, T, TNAME, TIMPL)   \
      typename INSTANTIATION_NS_PREFIX                                                       \
         boost_intrusive_default_type_ ## TNAME< T, TIMPL >::type                            \
//

#define BOOST_INTRUSIVE_HAS_TYPE(INSTANTIATION_NS_PREFIX, T, TNAME)  \
      INSTANTIATION_NS_PREFIX                                        \
         boost_intrusive_has_type_ ## TNAME< T >::value              \
//

#define BOOST_INTRUSIVE_INSTANTIATE_EVAL_DEFAULT_TYPE_TMPLT(TNAME)\
   template <typename T, typename DefaultType>                    \
   struct boost_intrusive_eval_default_type_ ## TNAME             \
   {                                                              \
      template <typename X>                                       \
      static char test(int, typename X::TNAME*);                  \
                                                                  \
      template <typename X>                                       \
      static int test(...);                                       \
                                                                  \
      struct DefaultWrap                                          \
      { typedef typename DefaultType::type TNAME; };              \
                                                                  \
      static const bool value = (1 == sizeof(test<T>(0, 0)));     \
                                                                  \
      typedef typename                                            \
         ::boost::intrusive::detail::eval_if_c                    \
            < value                                               \
            , ::boost::intrusive::detail::identity<T>             \
            , ::boost::intrusive::detail::identity<DefaultWrap>   \
            >::type::TNAME type;                                  \
   };                                                             \
//

#define BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT(INSTANTIATION_NS_PREFIX, T, TNAME, TIMPL) \
      typename INSTANTIATION_NS_PREFIX                                                          \
         boost_intrusive_eval_default_type_ ## TNAME< T, TIMPL >::type                          \
//

#define BOOST_INTRUSIVE_INTERNAL_STATIC_BOOL_IS_TRUE(TRAITS_PREFIX, TYPEDEF_TO_FIND) \
template <class T>\
struct TRAITS_PREFIX##_bool\
{\
   template<bool Add>\
   struct two_or_three {yes_type _[2u + (unsigned)Add];};\
   template <class U> static yes_type test(...);\
   template <class U> static two_or_three<U::TYPEDEF_TO_FIND> test (int);\
   static const std::size_t value = sizeof(test<T>(0));\
};\
\
template <class T>\
struct TRAITS_PREFIX##_bool_is_true\
{\
   static const bool value = TRAITS_PREFIX##_bool<T>::value > sizeof(yes_type)*2;\
};\
//

#define BOOST_INTRUSIVE_HAS_STATIC_MEMBER_FUNC_SIGNATURE(TRAITS_NAME, FUNC_NAME) \
  template <typename U, typename Signature> \
  class TRAITS_NAME \
  { \
  private: \
  template<Signature> struct helper;\
  template<typename T> \
  static ::boost::intrusive::detail::yes_type test(helper<&T::FUNC_NAME>*); \
  template<typename T> static ::boost::intrusive::detail::no_type test(...); \
  public: \
  static const bool value = sizeof(test<U>(0)) == sizeof(::boost::intrusive::detail::yes_type); \
  }; \
//

#define BOOST_INTRUSIVE_HAS_MEMBER_FUNC_CALLED(TRAITS_NAME, FUNC_NAME) \
template <typename Type> \
struct TRAITS_NAME \
{ \
   struct BaseMixin \
   { \
      void FUNC_NAME(); \
   }; \
   struct Base : public Type, public BaseMixin { Base(); }; \
   template <typename T, T t> class Helper{}; \
   template <typename U> \
   static ::boost::intrusive::detail::no_type  test(U*, Helper<void (BaseMixin::*)(), &U::FUNC_NAME>* = 0); \
   static ::boost::intrusive::detail::yes_type test(...); \
   static const bool value = sizeof(::boost::intrusive::detail::yes_type) == sizeof(test((Base*)(0))); \
};\
//

#define BOOST_INTRUSIVE_HAS_MEMBER_FUNC_CALLED_IGNORE_SIGNATURE(TRAITS_NAME, FUNC_NAME) \
BOOST_INTRUSIVE_HAS_MEMBER_FUNC_CALLED(TRAITS_NAME##_ignore_signature, FUNC_NAME) \
\
template <typename Type, class> \
struct TRAITS_NAME \
   : public TRAITS_NAME##_ignore_signature<Type> \
{};\
//

} //namespace detail
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_MPL_HPP

/* mpl.hpp
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
*/