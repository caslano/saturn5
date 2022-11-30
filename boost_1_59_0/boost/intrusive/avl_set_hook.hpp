/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_AVL_SET_HOOK_HPP
#define BOOST_INTRUSIVE_AVL_SET_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/avltree_node.hpp>
#include <boost/intrusive/avltree_algorithms.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c avl_set_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_avl_set_base_hook
{
   /// @cond
   typedef typename pack_options
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <hook_defaults, O1, O2, O3, O4>
      #else
      <hook_defaults, Options...>
      #endif
      ::type packed_options;

   typedef generic_hook
   < AvlTreeAlgorithms
   , avltree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , typename packed_options::tag
   , packed_options::link_mode
   , AvlTreeBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from avl_set_base_hook in order to store objects in
//! in an avl_set/avl_multiset. avl_set_base_hook holds the data necessary to maintain
//! the avl_set/avl_multiset and provides an appropriate value_traits class for avl_set/avl_multiset.
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
class avl_set_base_hook
   :  public make_avl_set_base_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3, O4>
      #else
      <Options...>
      #endif
      ::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   avl_set_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_base_hook(const avl_set_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_base_hook& operator=(const avl_set_base_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~avl_set_base_hook();

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
   void swap_nodes(avl_set_base_hook &other);

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

//! Helper metafunction to define a \c avl_set_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_avl_set_member_hook
{
   /// @cond
   typedef typename pack_options
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <hook_defaults, O1, O2, O3, O4>
      #else
      <hook_defaults, Options...>
      #endif
      ::type packed_options;

   typedef generic_hook
   < AvlTreeAlgorithms
   , avltree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Put a public data member avl_set_member_hook in order to store objects of this class in
//! an avl_set/avl_multiset. avl_set_member_hook holds the data necessary for maintaining the
//! avl_set/avl_multiset and provides an appropriate value_traits class for avl_set/avl_multiset.
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
class avl_set_member_hook
   :  public make_avl_set_member_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3, O4>
      #else
      <Options...>
      #endif
      ::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   avl_set_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_member_hook(const avl_set_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_member_hook& operator=(const avl_set_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~avl_set_member_hook();

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
   void swap_nodes(avl_set_member_hook &other);

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

#endif //BOOST_INTRUSIVE_AVL_SET_HOOK_HPP

/* avl_set_hook.hpp
kNnorkHU9sGvVpTijqa2cvFXvirg16KayL18oYfQIKq+WK9e5ZIxv1QH2Q77eQTQSViljGe/jd3VcsZWfjwOwXn1r4Pv+vwrcsP3NGgx6RCLBTuYehUWqmyel0hDgDKG0m06OMTfbyOUc0YqwFHEFuJGygEwOQ6fUC008sJfIcaAIRpUxc4QxiEwhIAQxpUbLnWMrSXi1FlyrQAMSACsP1UiWhQdizgEoeAITRfKkVDJzhkhiJw8lWZv3RJQ6IP+trEtFo2la56IJnV2VJxABZ9FKguUvqXN783jzQY+YvTUHbkerDdWxh0gqwfbzvcURzJhlV74UIOPnrgrd69Tttm3uam/oXhhjGcgZRhhOo5BwptQ3oSFqOgZRo4EQHASVN2V20Hbds8XagPGECYXBpbvZj/MvETJSECwDhR3Vm+ZSr9HFzRkGilHsxMMM8aB8mmaRGEwdbZWFLLZu+yTwo9fkH2JEjfTfLeRCRmwTOdXdzKEcYMs7v2/btMwXwM8RLf0tiKXiaW/qVu+JkZ+3//lsE60KiGQkUpxAnRWHgALlWgAYkAEARHNIRnU5bKNYaGwoIw4EooEogBNF6q6wu7mVJai8oDsm+TR4E2IdPYPF63ViRplSIIhFnQmy1OB80PjtL+Pl8i2ZMeAs/q/oaHm7erxibxa9qn4x9kM7OnXhy2j1FVfLttTY3gYTZXcXrNvB4I6uW/bgLXumHtm98NwN11zx+W39SVW5qfyYb5aIKR0NFcgZRk3F0mqU6+jeimti9FeoFSZqdadcJN947wrr79TtWqAoVuUY5jkFMGVeArM4SBUUjWIsCVTyQgDWJAhwlo1e6r/aJeQDE8c2PVXtRWVxer0Mrevl4booFq5KMtRj3x8eMx81YLulAEZz5cXxLIhGJyS47L145tK8a6qYsWUoroSAS4kYw/p3nOYXgTNlKuKuqSgnxSHgAAFHQAAAd4BngQN0TW/ACoaU+DyMBVJU/hAFKmscj7DJoGf8DhUM+ST6JZVhiRbBjJ8PN9kNn1Xe8vOEpV6UWVQYfXrj/0Y7zAcQoy8iRgbPre7KelelKtWQWLKkCmHLo1PMuQlyDuuGQQRavy7wFrH4fEixDyYrlsUXZ2pX7R707kiIWybnCICCAd9sKE9s95EVlIpPYfJdvmncI9Yy4MAYghcod0kIGsLowXYxKdxYZ6BTig7qzVUYiuSb2dF67Q2s3bpoXuCa9H3XZ2Uc9sQXnbH8KBJ7RF7a+2EHzr9/3SamQ6YkZlXHHXeOwVV5cGoUP7MsYAdDTXjeRQfp/K2jOP4q2zYZQdpn/z8qIA3435fJh9arlAfyJHFOzqUBSIk0OG7dpsuHLfI1ssiFfzUbQGZITmCFF+HEHI4p6YqEkO96jwOEN9iL+BjhpCQGyc0chbbSWIviN73DJpjEkNsaqeFCrfT2wskPaXJlWhO5VJvudvpDoVzBc4nx7Ve1DNR8K6zZiaYqeUfHo2f9YK5TvIF3gh7sU+kfiQoXp9nkWJ6kl1mV/JLdizNqdJMPHRiyxouHWflY4beTFmeLbSffb6hsr4QrHe2CQhyBcI4i/guxrF6RFCoDeuQronaQkTa40nIIRoUtd3FQoEwoIwhG5KaGfBcxgvgtIyVNxQUvbf9EhTM7+NCCcHU6sdZ3lkMkyWAVsck9NEAZrOAOzzlzAi7+snsnpyaZa9e1QmhOEOlZjKMINf4pGMwwhYgy9YGZpG6kjpbmI/s2oQeG9xfAZy3TFNuqHZXLFJcYvj/139u7ZT9dMJfjUW1HTr2kGAbVx3IuDDLKutOJ8rhUZTrP4l7DXeYrBK9MEo9dWgV5kab66pjftVxWKYyDSSRZQXhgsL5Tk5x9VPac9obG7F9M5mBg5uMMzw6o5tRqz0KSwae1kH50s1ETgXzyE0akiOahLG88RDpJGOGK+20dYyRwpDcWZy1OOgcYK1tHVBq3UaEFrUcqM+NvdwXIZq6+DTA7kIYcuVh9vv/D0+vPr1CgI0jAFQQTAQGQQYIQUAm/lQYELvQ4GcdIRpUnbaOxYCyEEJQCmvMTXLtzx1c26XlVTY0XCZZIPfXZQJglgnYjkBGIGAS3ehs7TEVEIPWRymCI0FW4GWyXSaWR3cS6R2KO8SIRESk5VdP6XARNjz/Hot6x3vvrm6o5btmjf7Q87pUm5TxuVVaSnaWOrSeucqbvk84eRnZmc65Jbe0su4r4kA55Aio7JbBmjqQQuvDqickr4pzSvoeVaDuYSVHXBEZIIiMRxqrTA7YLKaKJDqy40ZapKrvCLka7DqhemdlhZdXKc0UIcrLSdLjleqUsMwwFaxkYDhjgoKAoniuRyrsTtNTQBBCGIBSKS8g2O//DQ1gpPxfHT70M0EqzCGePvQWtachznKd8vYAmAFCADAmKaUGKQEGnRpqVtRrQutZRRC4TLJB4RWtnHA+McY8yYRfTceY8XGZ51lUBFT3vMZki5iSGqjT3+MdXGsxv7y2NM7HvbHTwHm8yAQPr6v8qUZAjD8C2IxX4D/ws6B//PgFGhx/fnqS0K6WeNKfvCvCwA4LIgAO7MQhCUc1VnAHy+IAAKlGuKQHgACAQ0sBAID/fwu8QZoEIUwS2z5lw4AAAFCgHYABlPXuG9yKx4tRuyjVVKX5iBnu7gLiHZUpp3JB7gU5lzGSts+gRKytdsaNoepiUkuBGRnV0EhqQxnZpcjMDFnf03wJBZqGntPFRlgfvEF30Gbyc1k1zqRiNP8qKaUuguDvEAR8jRRBMW//BSnMEvpxgEh0YZ7tH1dx3Z/+Za6/RxH8rio7/FcRsDRvZbXrWYyx50Gb8qWT3SAOLC6Mmxrk/pXsw5bjyEuul6zL4WDegtGBQzdOC9TTBimsnRPnZNGWH5OBuqvphzDg2LU5D4ukFmHthkC8ZoNuVRZQzTMtWaW76DzCXvGIU9HVPKoiNb3m740XsWA061DadbxrreR6f12FIgIn+NIe8HJWJJ2LBJoaydPqkl8/uty00qrDUCFINWuMo5oWLxn70+G1P2qzFFrlX9k2uq2hc9saBW6ffg4Q9Qo0Fp0Knf2BV8TSXd8Fhy6ykoP1rA06Vqif52kfeF62Szfk+BNO7KSjeesY38p+gPlky+mnARa8u041BLQkBVMMECDlHuKnSatYxeIZPYx/iq1OdZ1iKYLzBj0FRqvDgdCOHHXKHprs9iqExKtQqtfwdkP/pe4YO2PWG8dLGyun9h3a8ipzMB12qj55HM1gvbQGYsgDUvUSiVPVJ99jiSWTxK0YlC1b+hxhzepsMpkAyAU7mf0qCyYAR9HvLRJGtb4yX4bMzUSegMHsxgYjXkLuBXp3RoybVyBouhKbNQhi48yXkN5Z1RjEVS417OQOixJTpZH4k9H2v8havSZvJQjbj1/0+0Set2OHMdu/AeA+n466VV+O7n/om6MnJarTPxwC9l/X+sGrqQimd9yuYGof0VmCYjI02T6M8O/dkerZRPqv5EfsGgcYmHHB/qDpSUrV2sDfws+UDz3UMGnv8wwOQw7GdDPrBXY6DtrfQuD/Ml1l707qrW2r2/XKKcDpxDvXl9kpRoXD5yawoyYsGcvDURUIOCOuRgKdOOpeQ5Q77rTYENB6BUOQwL+209ueCMela+CqbdLJIoFZNQ4waSvQv1cNXWoxHzm+GqxOIgvbZOQjgxu/owlhKc6g3tay2Gcbb1WMIXweLb6AWms7AtC3PkjaNVuAzOncc8nXiXIy1/FpBQFW3yw6W8qszrmxZ5M1bkd6d7z8aBkEgbNcBqbD1f/WvWz4D7vrLenj2b09ZagePL8iY8OzoV4oGsiUJ/uIR6jFO9z7DuyLMNkZyBrgtp/+2j2OUIGLcSlo9o+8EoQnOMa/PRk7ZyFTHt8Cwa+9lVvx6OmJGT6BRYjH3qe/ONqTa0INxfBUDL0Jg9JqGGJnCOrA5LN6Y3cy0FnwBIssQMr70EfL6FAtNn80p4dGB3papnPNqsXzt5X0Acg2Lwu5k7DzPtuUxzqDocjIzc770mLEeaV17jhBiKxdD63zDJjIOIQJ5WgvbA5twk+Rz0ETRdp3eo1/V/0X61zg39JB/FPCyHfhMbTpHH4VlFXZxSBZtLVrUBTOzUYkbwAfOrDhsatMXCWunFDOj5bQ6cG/YIU1lOWecSvHVqqwm9WfJIWDxky74je9gR9zmuHkIRP2UyO8BCGdqVZQdLtFI+uc54yyVwkP1CjXr52r17jkCL0uere7FwzdjHNXhUNWGvOQZBT/jO1G7jPlDa+BsOQ2GY0IRSYUTDbEZJOzvw4dp2FBb32EanYqn+hc01uOBVn3IjDK2cHBL2Fxg223whUQHGoitt+AfzMLmajr8y3wVVpNlRZaFPg7MLxmZ8zCvNRRVBC7lsQ0GxbnLxygS0Y11+HpSGyOgB0RT8GZ8XrGoTbPMr6C8m+LLNKsxpg5xkRQk+RqKDeCq8GMLNafDX1PW9AUdd61YMx9W0W0ytKHQzW9h5sLoIs4EzzgoHDkvOMtxZ0lNVhE57QllTvjxF/I31ZzcGoM6lhf3XSI7SdJopxLp85Aw13EQj+0v/SQxAaZd94Y3OWrzyEk+MSZzpH6cJRZtAvVT16/ilJZgOsbcMDMKyhUgZLDcIdcmFdy0cMxBFIlnqQmsX4sK/e49ORbIacSg58gJz/N/MHm0PmKQEazHEIK347mdqLhRvEx7B8f5ZcGdQg/1/wmvbk1Sc9nkjTdY38eGUO0clIC+fJbKmpkT6D/1Z62U01lsp9SvrdUnJ1AYQDsOuUDH30S1sUHZJrZucJjO4F1zr6MnnqRfornSmU18IJoRpmlCCY7QbdIPa+pW5PnjLAeg7J6Ky48yXGmu8yv8649eLQ6GuAELQJparz0+HxhK+bTKmTax7ac3X/QQ5VpKVnyzESJIQclGFXFRbuuxw/yOTOJPCsRuMivGQtjRoW+2/+dH3wyqRt3n5vD/dvSlRpbwBacJDXM/ZbVzqaS1tWmbBlvDG3PZIH6fcQPcOZLDOFlIlxwLPJLPl/dmthAo1brCy9lqMbB0VJf9E/C1EZO4fFmKMWbr6NAXhDoHz6ZKiazgEG3pw/Fa2gRAJzT/7DvL2DdD1gHuUF5PbUXTDyorhFYKsq2uSXDcNbk8R6Fxp/pf6/fRDK7m8Bj20P18lsIJ7W7UEEXdTq3uGZuu6ubcerZAK6R5fFoKTARoqaKunlEIK39Lo8qUNEfGQhAm4QXidlPPgDJVvs9ckdoWJLquV5OXiybEwzUNkvR9hd4QcYMc49PJFeEbwRSLxCrZLXBj2KkMc+ET553kkCNWrl2ZLj2oqmvEQcwWFHkpMayoQsksbiDTMxakDBOcFwfIXNUeYn+QP3HDtqfrThRGu070ULnBWbJtYCuqdSY3HHA3ICYQ8ke1XLfHu/Nc7BKJ+0IZr29c72Oz6ic9AFfC7v6vs3tsLX4vq8ir+O2lT7RQXK64VbAkv5EE12466mcwMMwUf5YMBfo0bKAhua1WQAERmuQvLV7NwhnRznGLU3nS7gvrbxBSC4s8mtEyWc8iAOID8G0PaxDXUvgLRcbB1zQvU3/B1Q7VGfw95oy3MZRQDYjDJNJYM3aUZZZaIxwsx5GZ2qsBGSn8xGpoTUDNAC/YG6rUEHuEycr1w0rap9321gQhvWDln+m0XhfaWbpioN3Ul6yVi5FrPqOdAO510zb7Jx0+MAjskkHBsG+J0YFYha+p4YBCzPT1+dFtgN6RyjZgi0DrgQqNJmDj9GJJtl/mpL14tJFgxMip2IP9wKFugVUX00BpdoBcChEFqxHWQVvpPDfchNtgSvsulcAjqa7nB8LahFYZIl+2sW1kd0tzfo2OM4TzUYWZ17WId7In+fG+BbuAdDwKTYmrMWVWIA4VuuESs92YzOdPH+mAfAlu7T30euI5XWTJySVnxNDMD2mefyAyITA9Sq9FFudvG2t+wZaywJjU8/cQFwkXRk3xCXmPKCW/LyPKGVX1xFnTEe8Ea/dVEbYKxKN5f02fTeEVSp+g2OOQGTyOIhKdpho1pHeTUAi4dowDGCiYc7db3JEm+y9/fBYujUtXNN03/Eb7tTKYagTVXWO8Dr+sRSOCriMs4dUESpf6PsUQCYYSdYvHbv+nSEVpi3u4WFdwy60MOdkn6aH6jqpHpvoVL1nSwRaSjcoiNo4pr4DBDdkqXlIFhX6A+Oi3YSDkJzj7/l5SwzoIjdnWlo/m8BDGPjiYRJdLZ4NdtpDQC0mmEqoWIy2Z0gYw1wAEq3N820hE4zSPNFI4azvlmQmmijeee8y5DzMWTQRBM0jhhSkxDVY94hT1uwN84S9ApBDhO8YIcnlZBT2bONC0l0/Ju9bSLI1LZXhqZb7LDXY1gtOBcSuiGZ70VWKRLCtkQyP5qPx60WZG/8ZTOIU03AnrnLEXLUOMMEwGzIxQHIRjCRrysfWLqHtQ2oaLbXE3sqeo6UEFDb7BObP4f0LRkS4LcxwiRNzb3Ysd2FDx1Qo6PEIhoGR5KO5Qf/zX/qDQIZPGyonRS0n4pj/bY9YwIEPClGnf1+XpTMyj/lRWnoTIKn3hI9kmN979zdJmCcyZFtQYtTLBNM/LzdkeDECMuntNG5PkSEaFL22ksdBkgE0mrta8kiXUQ3GFAGHxDXxJSKJLk45FbufqPrYH59bvXyOI1EP4TkNU9Mq1zVVkdijPMwg/jOZf0PNvOkba8aE3oWS0uu+RI2bk44w8btgH2QqViS6tSCEQbiQDfDEk/sphi/nVMwmQp8Nu20svTtnldtKb/DF7d+A123pFvdohXMTopZqe+enj1ndLfet2nnMs2d0li5OTUxoqynNtMZWBV9JNrMJ0bymX9K9fQdhL+Crd9Npbnc8hxoZz4GxsDTbJ68HBHULAkA2VOoRL6MkhzKEHgSqQoDIXzVKh4wAtACcVTQChbNQopR0L6F3RoatkoYCA9T1FqnA+FYLO7CUZFE4IIHbtMjyT5tM5QOAv0/ACbXCBojKhCEKDjjbOsrFAPEsxsNwmhoiEZlchmrgk8odxKU90yGT0TPPWxfsMGk1RdCfsHZOlv7dQN9yi5pPOMsnuVr4rRVsF638cGRyMEbsNMslo5I2T0T2Rgu8DMNGbvELVJpK5MPDxfhfNx0gAOkhGhSlro0HYcBYahIQmB0GmTSLSVZSrphhYUtdoeOkItikqQcCNkyF9Pw+MaKZ3zpfY3jJNAaFH1+r883NrnYGGG6TOWsDxS7Q1EMDelWlLkkc/lsqKcUU4cq9ZVVn4beMxQhRBpcwUQkO+NOK1nMsBFG2EBngpBmFYSW6qwhJ48sLna6Fpr7kmbC6NF5M0u13FC5pvBn2kDSLsS7ngEhcd4ByqKkhvaTxFARJNg//JdNlX2o3zoG069J1o9bQrJ05FMrRMJXI73onc7UZn6SS1XxXltzEOK6c4J3jaTEm0NBxjeV6UmqGqUiArHC0KxEKKgGlog0LBRQARtyzzPebXNz+ApnS/Z89mAIBKWAncNA/5VWUi+thIJlzEVuV9mFVPhkVLvSqDjIk13drpEVW6DIgNCBKgWJDEpEikHaF4IFiMvTrs0skNeulK78hALqW2IfZaar50b1HxcB0bU2P0asSans2
*/