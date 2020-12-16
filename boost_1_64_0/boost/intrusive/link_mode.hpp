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
xt8V6zGKuXP2ExL3InByd5SVd/uEtiU4mcqxxsNdhd59Lfrt56wvamuxaqzFInPzesmn1iqSlVVaW/kj+8h+7kHJv9oaApxSOMrUYV8l7sx6i64T4VOTOS6R5i+pb/bFnph3ilc5vN4/ro8VEGfVKkeenAYRi5KAx6+ZnfQaVnFOz1oW5X+nk0+nSVo+0XEPu3F3vqr8p9L/GIwCNUpfzfBf5B/g3+CfCnFIjlqR+yAcLvCvkf8vSvV5c7A67utf41+fGgikqTu5PI8WXcSL4SbS4bfkxbse+KtVV1XceeZpqdfPgr4usK3moz/ajO03AH7VVqrx/O+nErcR669czDGj3TmgQOLOR6zxUv9HUN4Dq90yT5e6oP9Rxz97Z5ny1+vpNTcs9GvdvzXif1D3T7/a9d+r/J33/FtYB2r/sJW/xyh4jut1834c962Ed3EHheOPd1L0eDQ+5ntpzPenYr5bY767TI7+vm6yeS9fXB4uwCWU0YyHq1DvcS6NHt9krZWkHjyJy3GH9zMxl8qyw93/NwpOjmHcMsYHARLdjd8kOH2Mshk9PvfEiN9Qro8Bd17KPh+1bxakyBmt4BQKX74Pfpld5tyb7BM/9xKntsy5sxkMpKYaxgTi7XPT6pIwraNuWnYgNSU+Lee7+hxlRXn6fcxIG1HPBP21utf55u014cQf5HuGz8MtVPd/Y/iGUeNlKqzj7wr+PqsT2mKE+a4b0kzu/S7x4tdj5JmJU1T4BdLmNQUOX0T4eBvPVUeXY3xH+bbJeQ5E1n4lis/SdR3E6khw88iVPAaxHVdKWbYD/1q46+DmsK2aErUV92xLpzi6cpJ7b4w2E/prFI5WLr3N+leFM/kBXICwVL2vnxLdZrwqnlAO9iXBfxlzewpOqdPNa5gpiWWxQcDPSfh3rCol94Izrl+mxL5t27S5ge9rHP45LDjfwoljKnixk3E8YDqx85p77/xZCf+yzGvTQP3d4EPTm4a3BO8TqN8caxLWNOusnu485rtM5EKokdlyV/g0+KehMjxvpHq9C8FB/jSL/ZvhzW54IO1DDEs4N599Djqrjg13DorTJcN65dz0jynRc8Ulzlp4bTij1UIr+gjfqR2+TOMfdTUmkW4+rd2+KnFKrHGo6wVIzcBDSNf4ztfd07+kwkHdEBP/aPFNd7jU5w8lvKu7DkyZyvVm9D0fF/+o4PeIw8/W7oA1oBYqNbnWLyVOEJzliY8HPhiM9FvWOuvNwoTywh3nOMab3jDrY0JDdTiBt3lf9RT17hVPjW1TJT+Ne4fr7sEvnRruz4287wM6mEax3qbwM8rF3TqeIeFp7nj6C/nuL/3xF4VCsdv+H5aw9Thv6kI/26oTvwmWH75x7U66ygTniFGmvknC7oIcKhDLB678Z57gPGNVIAX9vZHsTrQ7hDWCd9CS+RxtvHc9zza9FwTSTXdriHdkvXM+2TOQkm7Y5xPv9fWOzD70JZ5NGtPzVaOuVL6dplK2H7PXIN7gauduRehY3N0K3pn+iHueSdljO9fDOu+1XBNG/hjPkT4KV610BUzTea+qpqG8VBkq0eYS8XTno6WC32R1UjOE+R4z07Rj7Ri57V4p4VswpvmMYwnjU+9XtC2Yi4PiYP9FueT7qYzHLEvUGE3adDnElJpwAtcxvWvhNqCuMqdrdbV+cz1EVvo6yVQXjKPredpSu1Hry7kS3mhtSDCuMr7Wfza59ThAwlZjPk4z2i6aJ+HjMCqkam8UoRtEG2dXCE6m9JsD4JFncVJwkfBlOmTnhjU18U4D73rh8ylxPE45k9g/CSWxl4s5T4zWU8X60s+60zeHI0N8gpLjj2cth/X2qa5MKJ/+quA=
*/