/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2010-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP
#define BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/parent_from_member.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Given a pointer to a member and its corresponding pointer to data member,
//! this function returns the pointer of the parent containing that member.
//! Note: this function does not work with pointer to members that rely on
//! virtual inheritance.
template<class Parent, class Member>
BOOST_INTRUSIVE_FORCEINLINE Parent *get_parent_from_member(Member *member, const Member Parent::* ptr_to_member)
{  return ::boost::intrusive::detail::parent_from_member(member, ptr_to_member);  }

//! Given a const pointer to a member and its corresponding const pointer to data member,
//! this function returns the const pointer of the parent containing that member.
//! Note: this function does not work with pointer to members that rely on
//! virtual inheritance.
template<class Parent, class Member>
BOOST_INTRUSIVE_FORCEINLINE const Parent *get_parent_from_member(const Member *member, const Member Parent::* ptr_to_member)
{  return ::boost::intrusive::detail::parent_from_member(member, ptr_to_member);  }

}  //namespace intrusive {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTRUSIVE_PARENT_FROM_MEMBER_HPP

/* parent_from_member.hpp
BMoVSF0C8XglMIGSbGlMoFvWZCZQii2lCXTLmtgESrGlN4Fu2ZOcQCvWVCdQLnvCE2jFmvYEyhVIfgLxeKVAgZLMiVAgHZ90KNCRR1IUqFg8NQo0ZEuQAt1Y0qRANR7JUqAiU4QKNOSQOAW6ZYxOgWrck6hARabIFGjIK6EKxCsQlQIlOSRXgW55IlIgXQmJVqBjxmgUqMaQdAU6ZYxEgWoMCVigU8YoFKjGlIwFSmWOQIFuTIlZoFTm6JP90C3oWCjZilf7heZVGlwXOs3v/Y3f7w+6Qb4R20vO0j0+ah21Xh29Ov6lddxpR52xvPbL3Ota0Ziqbqv1ffXf7Vw3Jt8X33z/1js+/b5d4PdOe1ktlzZExyoVa9HA5KLK84NlqYeOPaZVLEvlUkVMp5MqHOrmXwNzbJMpMV3NKNw5P6fRVrF8K4vpZmLVBWf0YrWJnj1vTiXMZw7tKTibly0QNpfTq+M1k5c1SZjHGSpmmEMREdXC1+XUSGXh63KUKpzncnqny5rNUZ0rbT6nd7PMGS1nXU6xe4Svy7uKCJvL5a7Lux2TMI/LW5dDv6WSsion/EZJypocVqSEWZzU4TJncbhjpc7ipC6WN4vlrcSxHk4p6/CmGoLmb/lr8GanhM/dctbfnV9LS/FWJPwK
*/