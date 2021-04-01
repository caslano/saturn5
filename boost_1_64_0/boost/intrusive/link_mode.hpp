/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_LINK_MODE_HPP
#define BOOST_INTRUSIVE_LINK_MODE_HPP

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This enumeration defines the type of value_traits that can be defined
//!for Boost.Intrusive containers
enum link_mode_type{
   //!If this linking policy is specified in a value_traits class
   //!as the link_mode, containers
   //!configured with such value_traits won't set the hooks
   //!of the erased values to a default state. Containers also won't
   //!check that the hooks of the new values are default initialized.
   normal_link,

   //!If this linking policy is specified in a value_traits class
   //!as the link_mode, containers
   //!configured with such value_traits will set the hooks
   //!of the erased values to a default state. Containers also will
   //!check that the hooks of the new values are default initialized.
   safe_link,

   //!Same as "safe_link" but the user type is an auto-unlink
   //!type, so the containers with constant-time size features won't be
   //!compatible with value_traits configured with this policy.
   //!Containers also know that the a value can be silently erased from
   //!the container without using any function provided by the containers.
   auto_unlink
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

template <link_mode_type link_mode>
struct is_safe_autounlink
{
   static const bool value =
      (int)link_mode == (int)auto_unlink   ||
      (int)link_mode == (int)safe_link;
};

#endif   //BOOST_INTRUSIVE_DOXYGEN_INVOKED

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_LINK_MODE_HPP

/* link_mode.hpp
oCoACGmy3Ty2Jk3Bwphxcix43Ds90YOU9BPnqgz7EJ+7YVzzpZfjvp7LZCwVOXnzLFTHWoN4D476+USElPHpfTjAlnCRGD0HJkx0AThEuCDw8+c3oWK9f5PzE/hRgKDVxPqQFRr3QsXQxlylGVcKEjRD7jbP7nTaLQh2s7vgMfRwKPQmeN+CTIOk7xWnBOTZWSgRknHBcfKzy/mZoZZ702eMaPO5QFbbTgBpxQggdaffXHqkNaFM2NqYAwMeVlytrges7gqHpF2e2+fgWrASUbmM63FbCrM7V31JI822Rm56+hwJJCJoF0XCLrQbeG4MZY6UX+HM649U+ppcaJe0XAcxIKqXujaHlo1VEr0o+NkXLLL9qoJN5a/WvZMnY1/5nqFYrFGMxLhrGBUA5E8IP2Ie9/3X265BggkTAbzm8TVdvybEA3wkIlD6nh6BvZCwdO2kK0I2zrZymrrB8Akp6E91x6VVRhgbwyq5dANCTKEE9hPe2cKOb9B8vJvYZQopqPrvWvmA4gySe0fx9HRFD0Bo2gxAvFnayxPeXlbLkbVq1at5LAk9m2Wjlg==
*/