//
// execution/allocator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_ALLOCATOR_HPP
#define BOOST_ASIO_EXECUTION_ALLOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/scheduler.hpp>
#include <boost/asio/execution/sender.hpp>
#include <boost/asio/is_applicable_property.hpp>
#include <boost/asio/traits/query_static_constexpr_member.hpp>
#include <boost/asio/traits/static_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(GENERATING_DOCUMENTATION)

namespace execution {

/// A property to describe which allocator an executor will use to allocate the
/// memory required to store a submitted function object.
template <typename ProtoAllocator>
struct allocator_t
{
  /// The allocator_t property applies to executors, senders, and schedulers.
  template <typename T>
  static constexpr bool is_applicable_property_v =
    is_executor_v<T> || is_sender_v<T> || is_scheduler_v<T>;

  /// The allocator_t property can be required.
  static constexpr bool is_requirable = true;

  /// The allocator_t property can be preferred.
  static constexpr bool is_preferable = true;

  /// Default constructor.
  constexpr allocator_t();

  /// Obtain the allocator stored in the allocator_t property object.
  /**
   * Present only if @c ProtoAllocator is non-void.
   */
  constexpr ProtoAllocator value() const;

  /// Create an allocator_t object with a different allocator.
  /**
   * Present only if @c ProtoAllocator is void.
   */
  template <typename OtherAllocator>
  allocator_t<OtherAllocator operator()(const OtherAllocator& a);
};

/// A special value used for accessing the allocator_t property.
constexpr allocator_t<void> allocator;

} // namespace execution

#else // defined(GENERATING_DOCUMENTATION)

namespace execution {

template <typename ProtoAllocator>
struct allocator_t
{
#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)
  template <typename T>
  BOOST_ASIO_STATIC_CONSTEXPR(bool,
    is_applicable_property_v = (
      is_executor<T>::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_sender<T>
          >::type::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_scheduler<T>
          >::type::value));
#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = true);

  template <typename T>
  struct static_proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      static constexpr auto query(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
        )
      {
        return T::query(BOOST_ASIO_MOVE_CAST(P)(p));
      }
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
  };

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, allocator_t> {};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename query_static_constexpr_member<T>::result_type
  static_query()
    BOOST_ASIO_NOEXCEPT_IF((
      query_static_constexpr_member<T>::is_noexcept))
  {
    return query_static_constexpr_member<T>::value();
  }

  template <typename E, typename T = decltype(allocator_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = allocator_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  BOOST_ASIO_CONSTEXPR ProtoAllocator value() const
  {
    return a_;
  }

private:
  friend struct allocator_t<void>;

  explicit BOOST_ASIO_CONSTEXPR allocator_t(const ProtoAllocator& a)
    : a_(a)
  {
  }

  ProtoAllocator a_;
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <typename ProtoAllocator> template <typename E, typename T>
const T allocator_t<ProtoAllocator>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <>
struct allocator_t<void>
{
#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)
  template <typename T>
  BOOST_ASIO_STATIC_CONSTEXPR(bool,
    is_applicable_property_v = (
      is_executor<T>::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_sender<T>
          >::type::value
        || conditional<
            is_executor<T>::value,
            false_type,
            is_scheduler<T>
          >::type::value));
#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_requirable = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_preferable = true);

  BOOST_ASIO_CONSTEXPR allocator_t()
  {
  }

  template <typename T>
  struct static_proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    struct type
    {
      template <typename P>
      static constexpr auto query(BOOST_ASIO_MOVE_ARG(P) p)
        noexcept(
          noexcept(
            conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
          )
        )
        -> decltype(
          conditional<true, T, P>::type::query(BOOST_ASIO_MOVE_CAST(P)(p))
        )
      {
        return T::query(BOOST_ASIO_MOVE_CAST(P)(p));
      }
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)
  };

  template <typename T>
  struct query_static_constexpr_member :
    traits::query_static_constexpr_member<
      typename static_proxy<T>::type, allocator_t> {};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
  template <typename T>
  static BOOST_ASIO_CONSTEXPR
  typename query_static_constexpr_member<T>::result_type
  static_query()
    BOOST_ASIO_NOEXCEPT_IF((
      query_static_constexpr_member<T>::is_noexcept))
  {
    return query_static_constexpr_member<T>::value();
  }

  template <typename E, typename T = decltype(allocator_t::static_query<E>())>
  static BOOST_ASIO_CONSTEXPR const T static_query_v
    = allocator_t::static_query<E>();
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

  template <typename OtherProtoAllocator>
  BOOST_ASIO_CONSTEXPR allocator_t<OtherProtoAllocator> operator()(
      const OtherProtoAllocator& a) const
  {
    return allocator_t<OtherProtoAllocator>(a);
  }
};

#if defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)
template <typename E, typename T>
const T allocator_t<void>::static_query_v;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   && defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr allocator_t<void> allocator;
#else // defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
template <typename T>
struct allocator_instance
{
  static allocator_t<T> instance;
};

template <typename T>
allocator_t<T> allocator_instance<T>::instance;

namespace {
static const allocator_t<void>& allocator = allocator_instance<void>::instance;
} // namespace
#endif

} // namespace execution

#if !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename ProtoAllocator>
struct is_applicable_property<T, execution::allocator_t<ProtoAllocator> >
  : integral_constant<bool,
      execution::is_executor<T>::value
        || conditional<
            execution::is_executor<T>::value,
            false_type,
            execution::is_sender<T>
          >::type::value
        || conditional<
            execution::is_executor<T>::value,
            false_type,
            execution::is_scheduler<T>
          >::type::value>
{
};

#endif // !defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT) \
  || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

template <typename T, typename ProtoAllocator>
struct static_query<T, execution::allocator_t<ProtoAllocator>,
  typename enable_if<
    execution::allocator_t<ProtoAllocator>::template
      query_static_constexpr_member<T>::is_valid
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);

  typedef typename execution::allocator_t<ProtoAllocator>::template
    query_static_constexpr_member<T>::result_type result_type;

  static BOOST_ASIO_CONSTEXPR result_type value()
  {
    return execution::allocator_t<ProtoAllocator>::template
      query_static_constexpr_member<T>::value();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_STATIC_QUERY_TRAIT)
       //   || !defined(BOOST_ASIO_HAS_SFINAE_VARIABLE_TEMPLATES)

} // namespace traits

#endif // defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_ALLOCATOR_HPP

/* allocator.hpp
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
*/