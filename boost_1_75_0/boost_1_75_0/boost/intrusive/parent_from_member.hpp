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
lwgGlYWO9b5JoT1unVSAoG+HNjPWzloD21FsQfHX8fq4rs7KdHfJYZ3Ad+oYoUvV8E40GGfM6w1ZSCdOg+U+a09kbDeIHge806u06V9sul/0RokDPuDL2Q3Oj319yM7p1IAJ44DPu3FdwQb3Z3g8bZ0dWlYBteB39smKgfsbjmd+pUG6XcHNkPw5rP7E5vYfb203DM8khyShbLCNmulS6SNHN9bKRKnpHrOaLRSi4IV9Z+4/gq89GkRNVuVZ6p8EJnJMf1IECjupzOHVMgbdVAcOl77k0N6c9RnxAhF2U6wuGPvLp01QhLvuQRxRLEBeNgG7udZRZdcm+ld5say63576LeLnfLQ72zCsFKoDHpBKU+o1LtHZ38UdhFv8yS/gKr5BWAd80sDxQ7IfqUP8SQiBsZ+Mwmxf1WFYPR1FU3X15csMeUVNkiVheyfezHZGELlt1YFfGmvsEkggKwlvihcHhcVp1Zl8n3/hW/QZ5nNllQ7PtgkyzT3kGl/YtlcoQHmmjr2fdLB3Bqy5ZrF2yNF6ys/Wf9XeCTctmR70IKZNC3+NF1Av7h88vrUXhO6/8idZnahteOrdoChsI6vmRPkbLynH40aRITOHnEJr9YdT/FXbJ+rrgL0Gmw6Gznz9NSrw0dCB4vOE4zU0n6S4puSyK7OJr+RYRsv4QSwp3voPPqKC6X2kyoY910aqB9UUcfPCIp6uk4XfnNQf
*/