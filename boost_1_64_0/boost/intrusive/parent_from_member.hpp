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
pK8uGfmuvMK04v/Sy4WwJf6l1wwEvlQ+rgeJa5B9XKVkKhffoLTKl01Q2qWXTc+QC5eNK737bNJ7oiEhmukdFtd36IgRsUkj4ocPHNrf2m6ebVhxeiP+QPkQtm35bD9QPr5TGtFPeoqvLqHKxTfqIson6g+Uz7MNL1w+5nrYl8un9041DjTTm9A5qnvSNcNj3e1mWaOK0xnzB8qFsG37swGvlI/nItzGlY9nxrSMpPGZqanyjrqiuIp/eZd+v3arvI6fPnWcfbmIe8t9tfJpIy6SNvd8s7pmqOWa1jRHHyyf5hXq26ryaZZaWLnySb6Iepj8B+rhskYXroeutBbbpHXkZdzHSqd1eN/rhg3u28ddF0dcVnFaM/5AXSRs2z6i6FD5uF6P21z7uErZVC6+uRdRNrl/oGxGXFb5stn3avn0xqtvjUqnl4ma1GzOdsjOlLTuqbjtiX/re3bt1/67oTJpnRhS+bSa3zaW+2ad65VdB3S4fFqHqXNtyqR1eobD6F9CK05jQZl4nw+ufLwJW+JdOo4+r5WP4yu4LSwVR90HVqocCsvE8cxF1CNr3lrvK+k2cdzNBfeXjuPU1JlJ6lnA/SxTiWtb8yLoSPnr7OM6RaWvQ39RufIq+gP9hafy2mUTxzg1N1A6jty3KtduisvEMfUS20Kp96Svl49jFeJYUi6Ola9XJZZ76+zgC99bS/7AvXWPzb2Va1ruraXLZOkb5dO7U0VkUun0Ts+aWKm0OiZVvi8Tt+5n/IuoYxfTl21/s3waR6g9E0qnkYUylat3QZMqf28Kss8P+3XnZfKj7kX0kcTZ432s3ByoxMFa7/OLyufRi6FcpXQeyT28cn1IxEXkU8SkS7+H7w298D3cNWbp81b5dA5WzzWSTuNgpuz0LD4zYy4/xfocNrDi8SRhXHqfSdi2Y6zot8vHd4J6LvEUX11ClYtvzEWUT8wfKJ+BlRj/tpb0HpX0VnG42Uc93xjpVd+I6Pj21mlLike3S5u4d1Y6jr11HHV4+r2v9o95/0al28n6o4bvK5FqcqbHENwkG/Ezps+Sxo2V+QuPZ3lM0e7b2j+XSNztztpI0Xb17MpI/Nmvgw5WY0VtH2rT99j4lf3BXdddou397deCiN9gdd4+5dfgqGt+KKRUfbnUsz7KvJe3W1tZZv9SiTvlmD/Jfv+rNe8aF23gELrO3StbjvbnUJt5uku7r20/nrTPU/v9/i9YXy987kHZtB+eZL/uLv99I8AA+UbD37UPtTXt8mWOp3ngL7RbX+eX6gqe9p2eVPEZBumTlf10feZlqe+GLOsylmk3HalHVcllX3MNzvPavIVesdfA3KuacbO+5j+Zo1hmfpvxinbrI2UmusxhrKcenH7PvefzSiZga1R36Lq8HfNTiK7L/rkr7eY622Hmr97T4n8rsg3ZLmsoVyOLkceQx5EnLvFsBVWW/XSceQaT+czbRR8u+roy9h+4dXmGDdJlv/+4cbHOTsxhNExV9790XfY56ibvnoDVp5Z6rANdtJ+WzrqUwhz7eU8J136P6ERlh1G8/RkY4tfz/s4Z2v4bRy/bs2+s/u3P3r5G2zd2ejEBlFnmW8wmrr0ntJvX9VkmLRxN9ReJY1lP9hihNpT69YR2s4tYdGF9b1tSWJd1KbX1N5hraGtxH7jm5n+R7Xzd8+mB2MUiMp9uO8cfLuHkm+F8YMzxyz6G8ZjnmWHkFlcUxjEzjDv0XojBdQlD2WF+1B3GqorCaHBcwhhmBqHDOIH/sOOuMEbbpsV2feglnsFamfuCagsPp5duK5+W0YdOKd1PnuH3KRrHJ9WJh7PHzy1bxJ+ds2R7/9Fhp6sum8d4poYyf+k=
*/