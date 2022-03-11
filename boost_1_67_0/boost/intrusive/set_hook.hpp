/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_SET_HOOK_HPP
#define BOOST_INTRUSIVE_SET_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/rbtree_node.hpp>
#include <boost/intrusive/rbtree_algorithms.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c set_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_set_base_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;

   typedef generic_hook
   < RbTreeAlgorithms
   , rbtree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , typename packed_options::tag
   , packed_options::link_mode
   , RbTreeBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from set_base_hook in order to store objects in
//! in a set/multiset. set_base_hook holds the data necessary to maintain
//! the set/multiset and provides an appropriate value_traits class for set/multiset.
//!
//! The hook admits the following options: \c tag<>, \c void_pointer<>,
//! \c link_mode<> and \c optimize_size<>.
//!
//! \c tag<> defines a tag to identify the node.
//! The same tag value can be used in different classes, but if a class is
//! derived from more than one \c list_base_hook, then each \c list_base_hook needs its
//! unique tag.
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
//!
//! \c optimize_size<> will tell the hook to optimize the hook for size instead
//! of speed.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3, class O4>
#endif
class set_base_hook
   :  public make_set_base_hook<
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   set_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_base_hook(const set_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_base_hook& operator=(const set_base_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~set_base_hook();

   //! <b>Effects</b>: Swapping two nodes swaps the position of the elements
   //!   related to those nodes in one or two containers. That is, if the node
   //!   this is part of the element e1, the node x is part of the element e2
   //!   and both elements are included in the containers s1 and s2, then after
   //!   the swap-operation e1 is in s2 at the position of e2 and e2 is in s1
   //!   at the position of e1. If one element is not in a container, then
   //!   after the swap-operation the other element is not in a container.
   //!   Iterators to e1 and e2 related to those nodes are invalidated.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   void swap_nodes(set_base_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c set::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if link_mode is \c auto_unlink.
   //!
   //! <b>Throws</b>: Nothing.
   void unlink();
   #endif
};

//! Helper metafunction to define a \c set_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_set_member_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type packed_options;

   typedef generic_hook
   < RbTreeAlgorithms
   , rbtree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Put a public data member set_member_hook in order to store objects of this class in
//! a set/multiset. set_member_hook holds the data necessary for maintaining the
//! set/multiset and provides an appropriate value_traits class for set/multiset.
//!
//! The hook admits the following options: \c void_pointer<>,
//! \c link_mode<> and \c optimize_size<>.
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
//!
//! \c optimize_size<> will tell the hook to optimize the hook for size instead
//! of speed.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3, class O4>
#endif
class set_member_hook
   :  public make_set_member_hook<
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   set_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_member_hook(const set_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_member_hook& operator=(const set_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~set_member_hook();

   //! <b>Effects</b>: Swapping two nodes swaps the position of the elements
   //!   related to those nodes in one or two containers. That is, if the node
   //!   this is part of the element e1, the node x is part of the element e2
   //!   and both elements are included in the containers s1 and s2, then after
   //!   the swap-operation e1 is in s2 at the position of e2 and e2 is in s1
   //!   at the position of e1. If one element is not in a container, then
   //!   after the swap-operation the other element is not in a container.
   //!   Iterators to e1 and e2 related to those nodes are invalidated.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   void swap_nodes(set_member_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c set::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if link_mode is \c auto_unlink.
   //!
   //! <b>Throws</b>: Nothing.
   void unlink();
   #endif
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SET_HOOK_HPP

/* set_hook.hpp
uqva5dUq1LlCL6eKMU6+ElNnNdKxcD6JAR9TibRLZZwbFSr0UjFly4uL6CwVEY3jMkjy2XzB+/becKWn6ZZxMpKR8lhfGjGb8YhcFSdSJ9bUUFOEBE+mQQnMPFallqLtGOmpQlzD7wVvryfNK7SzWmt0OcsPhasUAHQb1uv4YtSZVOME744GrXLyL+cysC4hOFWR/kItgTpbtVefJKs+GglherVRl4ZG+57RgJSgCMuZXMXJgHlZYKJnEUkYUZjNekbf/Xnx4iU+n83IlKsUDawppgg7S/A/Lmjp9AvBDvgYLPVG2wmz5JEpbCvlh3baA+fh1c7RaZEzArat3SDNHUfkrk5vKMu6KQu1m3qthjgEhS6qxGzaEYBk3zyHGHdPZi8nhPHWvf5cKGMRBdZ4VbwX5G58PMUzAhQEnPtWskI8Gm9jtoI6EL+t0I49hJ/GkI2J0tbM34HA5y1xCo4OegcUhoA8PneqIGPklQV7g/VlBHunlSH7XfXRuYQjgnJW02I5DqcO6UNbeWrX+0/rF/KeV2oESMSeR67e6TQDhnq5F77eqB2LaY6AZF11DvxuiZcL6HKEqZ1ca4tubX/oqrl1MXnz68dpK917Pvs9uJfOjkHXC5JuWXoVPKx5c97uekR2HYI99FG7BVM586rTary1rRIF9cQmO9piYnR/J+VPFNMuMy5YNgD20aplLpUPTMjPfePbhhlvpRPn5M7RVaWqEJAgXVDhrKqm5WlUl5LsT4O2kaIqWKu5EZzC1AwqlI1KZQR6LwxMlMEh7BDUISa2bXhmD0SJT3w+ZnTNc59FOwrKwjvd+AQltU0odHtG+MqUJDW7ngwSkzqNvJQ3RH5cXY/khCpBhkzVWacTX9vqWesi18DH801mrtC9lyWytKVStjz9YJ4AwwSlFdSYQ4VnLenbduBWViilMMYoxUdVd+VR0b4kABbTjk1kDVqQEnEZ5LyzlciNZ/bjzPKKy4wCncV98DXbjnzPb1Cz71CRvnnDblkxhUGBhAwBQeku9rvJDJe8qIwBVQEBgJ6IdMiReQ6AEFBc2RcBUD50eK4unDiUBm8JLLO4jwA0sphDZo2UOa86SbGcVaW8fUPK/b66xU674XEQ2TQqXf7JngafmXyDLv0tMxJPFyGvhnXSD0JxTtqLYeAAGMQQHpmqoIeDCcsR8Q8RV+ZycE1AEnQMbHMAt+xELUhyt0iOCPfH2SHo63PAp436FIk5nzXtZ+C74j5NOsArmiBYjUui2dyIcd8M8l2GVAEzFU5MJ8cilSuciYVz3BmIHv9InNVBl9it/IHORsiuj3kp4tf0pSB+q1jym/xFFeciHp8tExnb/wE0gMt/9kVySCazRjd20gKVC297/8MViVgHHmpcW+9LzDa2VWEu+X4krAtQ/QX+uXfnPQkOuiESw2FBL7rPyl6stZsW5Sm7l4NZ18KRO8M4G55v7qsNP3vZ6yjjeDMMkn5SiCs6so9xjiYNyhrfDAiLMA7LhHWv0nlPE8y6fOF0R/EZkp2idOQq0GrMWZbDTmXmg1hNV3Qq7+Tqm1rOxWjtHtKATvjpAYtdARuT/LCgVxu7XSGzsV6vTt5TLXRXqG8Us3BlSrG98dLIybzkf+VfxKoqEaMs4UMfr4mT+4ZOAT87NjceFDKoxtk9UMuizraqLrwl+840hOl5kr4yA7IiNIF5sCH8MTh7dnopfhbMXh8WKaXUStFgxMqZ1m9MpxcZniD5pKMMFCXCclqzhFGSFqVl8Y6jl1/SKJiur/pTZ123bVYnZWm0XFf+4qmwkTfHmsvN2fUNu4/36cxaidezubHTc/e6uVcdou4u3HCEvOZQb5SwYOb4HS+RlWE9Jw4aok48I8WQYYP3pmHkXlQj9McKwSSuOzaq+S/PFRgjrvuUPwheTcOz+kRzRorBa/g8OmaaM7gVjdunswseRJ5hPGqKek1pita2QuyRQJusZGz/CHly4Tw4kU/9oJj91G6Fas3pQ0Lh3kXU+jqRgOSjqh4DT+mytmS73McJZIkbD3fLC3hctlhlCm589Ug3v0R7r5WsmOtxmSo3MW7Leo/S5EkS+be90SsJp2lVvhde76ja6Y2nm4PHen6Ge5LwDqVNQ4NK3myKIfaGfycAFf/5Zc08ir0S2RvzmBgDfjI271eOHx0jjbhLJLVTtZkX1OriS9tjh5iQa/TPJe5N0BewqPTbSGjo61NRj4ku6+fM7sO9d9Ijzc0xUHw1KNFHT1Y+yxEN/vS230ccaBESsfZZaVBRZCMnfxgPY0+UHnkynuB1htGXgNy1MW2VMZduI+WzcDw9YF/pgrBwK3NjhBrCvdNtk8XJpur+paRnVB0NxqMIeU65DSTW2+CQSpFG21UkWIQ0xQ7+o6cOH3yzSgfp0ZdwMGrn6CNwFhaeSRvy6uzavoQbZ4DRirbxtcAv7kgUaRuHH/Kchm5ZG30dd8zkABckS85XZ4YKwwebRolVzXz2acEns+6KDauhQ2P3k430/L0A6LXIF7ifz9YFHNtbq7ZgngQe1y1rCOrzh57dxHHmo38OxEbC4DJ7wg5flSd2UdJT4O3XWxDWfnC9//Jyl+WoYCkDhQM4Ytk2DXeOG8LL7LqjN85caKlq5nF4FWHX7KK56JzRWDFiK7Ciz9yaZm2fjjbtxhlYWyCgN+husxYflxeUv2nofKiThGBq56/asqdi/PiNwx4cRTgaDyUc7oRjt+N5LkvP/k6LnvKbZDphPC6AR2wfT4b45zuCU8MsS9VWWD7Bs/uU9DxMmSV6xPSGunx6roq7FJx7bA+jDiYYw6WPUGZxsCbOUUw5clNHBNCshDeX2YSiS1958+/DlpIuHY5G3zDBvoeiKOkjzxqeI6P4zGvKuvUInU/5vNDsMrUss191IK11xteiT+YEtQiFHabDSCGi6NQtb0J0CultKCIZb4VH60p0DRFlhw53yrJTBXCH8i1FfrjQJmCacctk3v1y+zDxsuYd/3CqdK9QwtOHVm/hVD6yjFe65olB8ZhE8H6WVvVInS0djBCa5sOcB2fi58U9fW3Ed5P7kViIZlX28BR336a8rHzksTl+yPKumxf/CLs+oZstVcrJPvyLkRoUi457wtVyZwkdKEkj7mJusdZOMfau74Y5XCbKW0cktHlyahhe5uMMV3UNSExd8kv52iul+vB3zb/GLaa4tAt4jtl0//UXu49nK9kHiSFWWcBagqi3nxbfSxE8E9vy5k+r6Y/2LSVEWrYOsOItuK5UnrUQiDjlnLaAMvfSLXyR4D8inTdwdEmj/E7T2Us8pFv0oGUJt7eL8OIlY3G88YFZ1WOa+tkHim8OCpOBrBka0XPVKBpXB0/ZxAr3rLTitb1HxWQmPik9bzh7o+lWmTUvrPlEQCkrM8w/a7iLqif1/ORdkHMRomIHfb0M2GmtLvYEG9nDfBDj/lQLSLkT1bnH/zONfcLBS5oMGSf3Z+TH916QaCNW8d+DRr3zkQUsB+hTZOthFZ742Aa4Pm6SBN6TSwtTpVju0xbHxIEarEEEcHHJJQE2wj2nL2Ni7NVG+qZ62fqZc8KC4vLuwpc/EpSDddBtV0nv90EVWaYRD2e87sZnKrsnZ1bNa3qhtT6Cz4S7uojMTgPcCJ5jyMzlqGSWMCaZyX82/NKyrI61ikWlfuZ5jsm4CYXAgpJP1VB7xSvZyXYoDIXXik/6nbjH5VbPVAbYUly2chYNSg2tj1Zn7Js9DGB4CZ8Ca9z3Ql8GPHs1ERQX8478AZ1VX8xTThfqCXWOPAGewN5t0/SPpWQy4newb25Ez9KDizcZxT8msCypxxBPIV5vXlbkP+NeHiLPrjqVIijELbtoB9rPeuUgTSrSvmdIL4JyMUp9Tl1wI/HG4gXrUtWaM+NucJKBZGD1wOdKXfaRdwvNnyJME9HW2maZfT2tP84FOt4NxQRt23+wmmm/bp6JeSf+TPvy9UZBTg9qaaFHqYzbB3NUGBIUPISuiTUSft1GUZK3aNLibHvgmcaED36PH31M5hNX0hsqufZhJysqdImAndj49EqMmQzDCUjmtz2HQPMuHUBnabN8P38GxEOm99jSs3CA8xXBuHRw0DL+znUZFK5s9wO4BCN6WvlOvKJqZ9T9WoeJ19gu1CIhVgRXDnkSgu6HG7iFQ0eYFiEy+MEoQW+KlVO3sz0/qlIXtAbRE05rXbSrHnpS0hw4SrkQU71Mu2dokuEoblmK52GfrdxRjR+ESKSlX77xPFcW3BoKl0roLWZ8HdNC1XBqUVBFCL7CbPEuBHa5lo5GfYHZHg3Xks6Rz1IKCSTAUXTLsVO9v0NR1ttb+FDKX/01dzG5zjDH/oIMh4v8laLJnbpS3aFd1Q2x8DUeej3mSzqTEqGZLqTjZpj0wjeasytqB3WC2yPQGh2uJy3y0/YbkcFZJSMBK4xDLh09x14gNNQW3SIfGDlJKGhcGETA7WcIpCUE+OXzBED7/Rs6YJv/tvVg5GdkYhFiE6ZlYGJhp2VmMGKkFWB5yk8rJMzIKMIuwiLIwiDkRY8IIP6qBgXAA/ieBhWPMPdD/Wi1W/QRP0NaZSU4wB0k1HuKtwhoAVgQcQQAcaiWEPxLNfUOCA5bEADAAyD7juDWoMZ/j0DQxsrKxlrZ0cyS38HByErf0o3O0NLyV1w5hhV3P/+C64u4JsLt/a9w+iCEMBOTpYhhIAMAs3gA9t/gvBX+P8ARkpL6E4mv7VHByH9AUghBophqpXPNAbltBACEf0Oir4b83yIRt3Y0srexpRNXdTBVcLJ2NLMykjLTt9ez/xtBvqr6of8JVjAEVsSnZYb+GMhtERSA+zdYq1H/a1iKMvyi4koQRH+iAfAV6PwnNEAIGodPBCEVUAAAGgwAwPgbGiYKlP8WjZyegYWeiRGdq9XvjMC46n3F8L39Jwy3HmxLE2p5Yw8FsP0IA+D6DYM21X+NQdHA3sjI2kDPwVHWydHWyfFPQnaWD/+j/94Ssob2hUZBBgAQKQL8AWYiGfX/DMbMwOYfmfkPYLzfkSc6QgMAznAAgNhvYLK2/u9gvjfiBjbWdK56/zJn/wHZPVBf8zjkzhniOwK/Icvc/X9G5vp/wwQtiY5biwoHsBeBA/D+hgl6//+MSczI0pbOwNTqfwsoEAJIM+yMloEVcmcB+GMv5IVI/ZeAlIwMTBWtzBxN6WSM/ubVvp7Lz39Fgm77dyQkkCXWf9BQIRsCCRKaUH9Qs8H6f0DyF0l/AkoaYkL8/B8ABUGoMdYkcaO/D7mjBwAEfwNU1fT/BugfWAJgemn/zywBADihvwdz2p+g0CF/VlP/NShDI8iD30L6amkT+LbbH22pefbX9ldO8CDdY3QeKAtNQCbJDQog+Rsn0//b7v+2suyNHGyc7A2MHP7khowNAfqWC0B7bf/v4ODgv40eHbCBAADkl2FD7qQ1IgCQSAGAhfyBwQBA5XeQfID//MGDbBWoRNWogNK7vSSVUFK9JEqmZg7EtvY2JvZ6VsQGetbWNo7E+kbE9k7WxGbWxEKyisRWNoZGdCgoiD/IQJvENZGscWP+8UfWO8QsC2kFWi6+tuPHC8wSkFbu8Rqz4Nd2mFn46/svzDqQ1tILmln06/MVZr6vNlyZeapu74eYNb4+H2UW+doufrez/LVVMDMwve3v38YmB8ltpKDgAOpu8oo/ns0DoEmQoCCpYi3k5uLbM/eK7w41APhBLmR3AgDgIHNx+/nRAvagvpJMcwQFec0H9VUJ/bs3ov/ll7pKUIBUGgDgShAKsHf78C0UoBTqHwBCkg1HTAjOYQCA4H+YI18mqN/nEoITAebf5ekcjVwdb3eRmu+Aar87xy8fiK/p0tkb6jnqQXym6PvYi7/lZb9+IP3y0X0TA/DdZtgRkIHc+qA91J9yjXT2DvYGkO9fxwoZ8y2HAFeov9uzN7K0gQg28n7j4Ovg3P8mJ/BfuO///4F8OqB81wHoLT0/PsqgrRNhBCgV0H4H/O0bR0QVMHbeEADdrxUW1K79vBkW0PPrByJvDja17QSgG777um78thAUVVTfcUdCoTO1yYUJHxmm3z4HOSEwTSmaQwGfX4F49gYA6IqKHfARkA6A2rDgMcgLcyhFoAjCX1+RwWNAEXQ/npF4KHSwEwLHw3HIF0fFMOE9ufUKHwAAgqdd+AoKhCBvuj4FQDfdg1zM75niTQPQq2/X3Lo9RCgY0pvwnl/jnl8rVpgcsl8XeA+tCVE8oMsHEYQAuicHEoAFD7SLYEEBtfGA2gSgdpD0kSEQ5Rawuo62JmjlX8bL/td45f9xtPtAp71v42MCA72u1t9D8j2QCALo4RFk6FwdjvBy4GGgNwJIBBnoDQv0xgN6E/x8igwS+UsE/XY2/mkq/gUpBJ+Kql8/GLTP8ZU6p7t+PLfMARwfQfqXM2WH8GOaBLmYs//ClYj3LaFYIBkEc4A8GPsMAjKgES0AklsAvptB4ID7OgGEppU/LXD9YgH2qwV0kDACSBoZKIIHlCH4EwCxPKT7mR/KvL8od3jdKuOZA8xhIX8AFdNGTAA6GLsIMlagCOyfdojkTMd/mhH4xYyv17dRiMAGNDo6dPBR3G4Lf2oTmrLP/lAW+UVZ0OvbAJxhQSo0CmDsKwgHf+p6yZkG/1QW+0UZ/lvPf8pLm87/FJf4RXzM82tff4fGMPdDXOoX8axv4jqQ1Yfwuzd+m2/I2rqd8j/NyaqYBt/aa4RczOV/safm+Y9oiVRM13/KK/4iT/FNPuDE0eAfIM//UFH5ReXY4yvkdat/mAFp09afOmq/6DR5/AsrgIUf4hq/iEd9E9dhatR+/tf+pejXDeZ4+DfPx5Mz1b21kgG5mOv+YkXqqxUsP288AJp/362//01ZBlnedOCnssEvymjflEEqyKogHsAgAF0BPPanPilIBh3i+GqLPwwY/WKgz/2r44NU/kkT4ud7P7VMftGKc//WLc/tOl2ngoDwb3R8DBIhAMngycmb8i39ULL4RcngR1cEEDYUwAOQTWR91/2rKqHp2U8Vq19UGL6qoPt6YwEckSE0mCPKg8cCGp1C/86RCoKCqdzyDyN2vxjZdPu+KBFAPLAQiuT+lSKElR/6Dr/o57r9QpHOn6oycqZvf6o5/aLm+K3bP+UJTfd+irv8Ii78VRxds+XfN09kOVO5VYhuKeRi7vmL7l237y6EDHC0/Lv3DvxU8vlFacT123YDcS4w9i0vfyqqfR/ZrabpC8gy+kX5jes/LmDyW5JMddd+aPn9rqXn+n0m0FXlvu3x3wzoaP8yTjlT4vUf+gG/65N802/5bf8BQfmto4eJIft9ug2t9yQChn4NrS09HVClv+UXoKYOwK9Pftz/iLOgpt8jLmR/Uwx5jgDJR05aoB1pQSJXqqa6eAD0MO8rOXNYlXXiBADgpAXKEVEVjF36PTZ2QALibTjsgL+1/PXtb0mM5i9RHcSP3PLHfgqJYV/Tn0aIMkgMFigDC5JDAKoggMSQgTLIIDl0oArkORZQBgskhwdUwQOJEUCiHUiOOEyMLEyETA6oQrwO9xAS7/8hXfrL/v/Ksl8jWZgM2a1hyz8M39qTRgAJI3N1et4FCaNzdfpAg5qeNyMD/uqvCSLRAZi/HY48LFAOFiSPAJRDAMkjA+WQQfLoQDnIcyygHBZIHg8ohwcSJwCKEfzo4If+/17z9/lT/TaBNJAJNLXF/z5/xCrrunH/Pn8gESwmcAf8LXBIPoQi91MC6H0b5L8lU5B8CZIl/cyXYCEbzV/51W3y9Ovk6/wx+9/j574qyAv9W0eqHSJfjw86RPC+NV+LKzB2JcQAJLOB2IBkKFBAESzILJoDvmVu3xJayB0km5NBB4/dSkD+Qe5hb5NYBJ2vE/ZtRhRvp14ES/X/cWAQhlp++C8k2UGFTIYCSJ4AJI6lIH+77P7IV8Vaf8nPsf4xY50APt/rEL76+l0amVoaoTI3J4fqdGPwAtTctE4E0wwUXp4SXnaDn4ZzZYJCX+f9AABMo9hCvoIkEUAsZ18ZmHk+Lw8ehaSO/i8gO0aYIRkApAhrbqhw+8zxHkgQQpnc7Xen9Q1diABIEgsovf7P3TF1Vd+WnaeLaBFNpxNInfI/5wDkhQAU3gINUo990/nyXQfCH9MJTLMjL9MUCJkLpLwFRC6GyIKEuCA56R4XP4EDDJCf4NbA31RFYJr9WpC59uzbQc/3TgUJbsBgcIfw1/obLTDk9qh4ZwbudqwzwvOb8N8wUPdPNP8O+mvvkA62QFgfIT2iNWBJAJWXRSCsjR/MNkGsL49/WudKuP1VxxcM9rpTedtsIvOAIZWKN1zlbQOSXjcGQt3WLE3Qt9RIEvANbgCF97ia7IEz4zMTM+MgwW8TrgjhnUABpIglDwnmIOGt704EkoSF8PA9pkB8FCKLKPfX5ve3ogH9j/2pCOqP/Z0fAaJ+m9t8e/PVfW8ffbUvA2sO/l4vnI7jN/JptzA1AuEhfg/xeq4zJxjGxpYXECrBvM5Ipknrtzm90q1a//rt0dNXwTDYSojsX71C/NVvC52pMaDLUeTF+a2qC3YYbNhX1wVj134bBsSBKMOkr+TDpH+4LBh7GWLYlJ0HCj1MeU8BMndYkHpwHTkRQunK85a/7b9yoH0w9jREpQP+VvCvHbUD6vYeTL4OeffX/vBNCox9+/TPPeX3bb4DSuny3+rp2zf/qZ7ugNL9V33d/0L/2/iA/Mx/1YOQ9Q/V9le9+q/lqgjsLcDvhHaIINx2B/Hz2yq7Az7u9pUIbOXXBqH19pUopM5DBsmih6lAIhZ6mCyWwjoqDmTVi5CFyZLJQdSg17UxIcZlmYEyzH8UrL/Xq7erVBQZguKrvVtjolhhMljrPrfmRG9D37ohZFcGqTLrAFWYfxv2P+UHtqTf4wu7yjog6t/jy7oN9PeX/5oefOcPp/W/5g8ylh8Uwlt+Iy30K1sIYSrIYbLIChB3X1/FuuWJIEyW4JYnqPXR29HJ0gBlaEJUGYJVGECizECRf+Xsz/rvG38It/whhIkih8kgrwtj3zJHECZDsM6J/U+2db6z+I/5ldxf/DVG/A/8EdH9l/y5dv3H86FfKGSaCvNGAD6/6rjz1QWFEX53vzu33ncba7Wxvh3bALXJgNoUQG0aCJcw5uxAbeafOwVQ+NZ/YblaHO+COtcLaQA=
*/