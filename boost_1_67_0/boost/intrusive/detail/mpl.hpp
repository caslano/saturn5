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
   struct two_or_three {yes_type _[2 + Add];};\
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