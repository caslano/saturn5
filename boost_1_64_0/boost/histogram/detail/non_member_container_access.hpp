// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP
#define BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP

#if __cpp_lib_nonmember_container_access >= 201411

#include <iterator>

namespace boost {
namespace histogram {
namespace detail {

using std::data;
using std::size;

} // namespace detail
} // namespace histogram
} // namespace boost

#else

#include <initializer_list>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class C>
constexpr auto data(C& c) -> decltype(c.data()) {
  return c.data();
}

template <class C>
constexpr auto data(const C& c) -> decltype(c.data()) {
  return c.data();
}

template <class T, std::size_t N>
constexpr T* data(T (&array)[N]) noexcept {
  return array;
}

template <class E>
constexpr const E* data(std::initializer_list<E> il) noexcept {
  return il.begin();
}

template <class C>
constexpr auto size(const C& c) -> decltype(c.size()) {
  return c.size();
}

template <class T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept {
  return N;
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

#endif // BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP

/* non_member_container_access.hpp
NHHJbJJQSV8DP+98PEo0eUGchA5/aRCYIlIlTIY5HHOMNsqHmECe9c/HQ0JT1175C/FRG+utSQ6Msp0w3D877joUhEksz6JJvp4polfoKBJ1PQVjSm10YP2v5vrNmm0V5nc84GKpQC6pzB8GUAMXFdCj55MdnQgL8i5673BbcAvEjADqOw6IPBIwVx1s07MZK/4e/2Z0tL0q8Dk8SDiGzi2gtxeyEW4mEv9WuhWLwTkBSybJSztTLuBLtAiidgj9SaI56vCldnE+aRyuTj8zZX+DJnWJQyDhNBOTcmIeZpVN5KJQky1TRIdh4sbdjFACZFLnlvluNY6D6my5i7Whfh3cxiiv4KTfrib3GneOonRjp+Uu2pL9B2ApK0HpCZPioqMwQAGZOg5laGR2fk/5KLpIU+elQ7WINCpZcMMQ9XZAumsU8R4JopcI7TzcWy33St4N9C/YP48EqnRkDTF1/zLOebAt8t4x4nL/fvrMjpxrLp9YV9XT5zytEKn3la3x/yxFi8yRxnLwcqTP8PNBozlb4DpVJ/fOs8eOXMWhJY4qhkEia6w16AGd5g==
*/