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
U6E5Io6bxeguPJtkHHcrvM0gMY8PYbaejwXjBQ8eJ3gNO/v+laFhktPK50n92D28bHpTEdMSJYBx/ezN+8BtPsa1SNQQXjlsB1eLhURNa6BL3lqbteYki7sB9UUi+2attFn4p4UVKS60IGhBQexn8Nc7Ajm8xK+V5t8Ud5M86z1y5N0V5+WW38kLiVN7yFfYafwZaw6XiOuGuhoDmYiKY5jtMupZBxeammNYyWUR0ySN5+YjrlGz4/YEsk3ItlCxWtGN+e3/aKwF3Hre/jkGXvi8jgraozC+zuCXEC/ApTs1PS8XPa/UwE39axheV1A2eY7OJiIoWjQ2/VAYyioirjpPU8AAOPd5c+e8Ji1l4uwLkpcB7pRpW0RMf7o1njcG7uyPQIoSDAVkAonohth2ybZLvCsfy4n7cWcogyBJareKvEGH/Mfy3/rrRCsDYWT2wc9xT8liK67jCiSql/O3Ul/HcAoFRX11xujqk1SN5m4nis+fD2lIigOoALDAxf2Ut1Xy/mm/9a0/TdaG62zGrboyqWSQNZx+F5qhyvfoMSP1f1mKPGDb4TZi4Moi8v5Sk7CRyDPqZ97mk3GNi/ZHcb0HSdOBbAcZw4Yqnie1Xg6lxH2txdVR8WF7YcvWL5Y3aslfrBMMudX3n1QJHUfdge0q2n4ZpHxBmjAgts5p7zE07GTUxtSquuBv6Xcj/uKJHKhfoYAlDHYTAeoQ
*/