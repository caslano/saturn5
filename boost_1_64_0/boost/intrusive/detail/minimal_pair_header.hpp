/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#//Try to avoid including <utility>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_pair.h>
#else
#  include <utility>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_PAIR_HEADER_HPP

/* minimal_pair_header.hpp
FvHfBL+CaT8gbX5vw9lj2vmEjYBVcC0u/wx0wfeR2QFjpvvHu9Oupm74nYUbxu9c3CbCi6zj/F6Hs8fDt15dPyZ+mN9VyKzHjcZfC/OhbwZlgH3gsFXkGbcafzXMJqwct47fa+Fm3B7ceo7vImwjPACXc26+Itx3jX98vSd0G2PPJrwIpuWgjziV1rEcwnH2uPt8ft9r/Ua2Bpnd8ACOsXie0AnHJV9LPiyd8BDcTFi+FWbphYehjNefQ1lx+bhadK2CG3D2OP4OftfhDuNqiZdFWPK5nAdcKb/nwGpcDW4/x6sJ24ueQzhr3L+W8D04c/w/8zqZAyCbG026jji4e3Fp+LfCwTB4fkAd4bmEV+HW47bgigjfA4PnDRwgLGa1f/5Acjk26Ffjz6UOYTdYCVfjJvG7FLfJ8sPd0JxvUEPYaJh2PWnDTLiDsBxYhdufS7rQnI+wCX8N3AM9s6g3WIs/fQ3nHP9oOB7m43YRXom/mt/rcXX4N+IfTJ7n4FbiNuJ24Q7h0i6mf8Ll41bhNuH2XNw8Z6H5r/mv+a/5r/nvP/f3bxn/X1xRrnMAjnr837LzfybfCWNkDwB0V1QWVC6pyKssrqqkCHL8LI6n28cvLCgpXbLYsv13YZnuA8ALV/1YY5S+q+Ba4YbjZmdYAfXzB2Zka+5ZAFtRzoYCEX43RYfzTTFXZI34+v3UJzLt3L4xEt9co6ZzA4zxlQQ53keOP+svTdmC4kWODYE4Od5X0h+bIccrKrUi7LX/bUWmtzNG46VuonCR2NA5hbg6tt3gt+xcCXPKHvDdukjH+pJJ/BT4OQrzkc92rf+KknmLCio5nU6ZvVpmu06qJN4bXpfzgc5w493YlPnrt99eLsff9drnpkz8qa7nxtSl38Tlg7rYpkDXtXL8dUfXVfiRdh8vUF2p6LohWXRRzuLFeX4zAqLzK3TeInIveVNV543iX+LtTY5OZfVOkoQzgjHCCu/BNZUSavPRpR4Yt5tfULLIsYNziRy/3dvLc1Di15F2aBvEBgbhD4jss94A+zSav12niY1K9Xs9teKP9dTLXuTIvi3HjnNkTxwhsmpnROa2DJ1bUua07dWnqt0djhdaCrTOTPsRy0Xnreq3dbamnJTbiFOh5dlPeX4iereLTYqCDLVjodf3YY5bcbdqXC4kotbbyfhK4vbwrnRJ09LXV+PZNpwOoK+n5HGE92PKKuPvUawfa0HflSr2755wsWkhMruQ8VkyMdXbzXWppswhZD5NFPt4ncPJpLXku64lE7uidXBaqSqThczf/DIHEqITjXXfgbqKdN4A6b0ZPG/gDPwMS8j4L72/sAX5b4lrhYvBxeLicPs5Hg8z2/vl3tWxlfRE17k2ozhMnk4Vmy4pHq/0TSePCOmbZP5OivYXLnNQdIxNx5z0eu6o9ii5LgkLvC6Rl2tDdeg11E7aCW2HMNpO0Pj6Zh1fH4Jrqd8NlyJ7cIRbfyd5jehe44/vDe4XnXlkn8vx/tRja7f+jPgN32vany72/NzuJY6Nl29ER1du7VHOXjkJej9p7XJPiYlgHFDOU9C5k/rUscCNsapAx8uzcMszoOS3uriiQowrWieO5wiZHaXXor+fdR8P1Pg65vlRe+l/RI42Jn3heEm9oJLRWcfm1uzT/eWPMeaUtKHcbbXsgW/87vMyyJe0M7VnIemRPmHlAWvj03QM9K9qq+kjeIE1x8RfbkbK8yorImhL9vn9mcTb7XbfRKdr23JtRyrrtBOv0U7sfnnT6Xpv5LQnOHF6OXo0zL09qu2gV+X409764zIZwnmu+YUc/43cH/7U3t9eC/IWFSwsrp8b+ZTIjPcOYcVUbwmjpz7DCps=
*/