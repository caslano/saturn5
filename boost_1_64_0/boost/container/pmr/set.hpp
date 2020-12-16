//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SET_HPP
#define BOOST_CONTAINER_PMR_SET_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/set.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
using set = boost::container::set<Key, Compare, polymorphic_allocator<Key>, Options>;

template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
using multiset = boost::container::multiset<Key, Compare, polymorphic_allocator<Key>, Options>;

#endif

//! A portable metafunction to obtain a set
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
struct set_of
{
   typedef boost::container::set<Key, Compare, polymorphic_allocator<Key>, Options> type;
};

//! A portable metafunction to obtain a multiset
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
struct multiset_of
{
   typedef boost::container::multiset<Key, Compare, polymorphic_allocator<Key>, Options> type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SET_HPP

/* set.hpp
8b64I/DzoRmLWtGUS2D7KgzijsLP2x/PVNCywJzeNj+Gn488Gvc6mm2Cb13phJ9Tdz12mcfuC6gASw/w2Bfw87XOF7/1WHFAxU9gu+yN+xp+FvejmSb55ny3ZDawLm+coisOOLk8yIlzyQnftaseE4coiy99ZB7OibprfW0adMtW0/nZSCwI4nz23XetYBavhfvZIqWbxEXqlrjQxFwypvssSpc5l84lCzGzbuRKsv4tsROL1i1fTi2FmJWa2DeC4bZgANT5ke3XR7HOLLAK73oUC/Zq2uIk7F/XDb71dhDtH6wrphuh7708cQ7dJZn7R1/6tMfmLHNk+pbfZN2WgHce23QtxlUQuxLiNu3Z34bjYroV5qfRY+m6zPlNR3ZE4Fxqvh3mizfuTl0hWe6bAxxwxs/ltXzd5oDkf0z5vcfuCagDs3n7sFF3T8AzvT78HK0dDMdsE5ivzeyRnWC4PuyA5Te26+glOJ5dxHbqls1v/vpPJWhiI1/jraUMxuy7uBUu7F+7ML3HHtVlztuoW7cS89lyYV0xeGw35LNF7bwK9w9ZSz2NC3tdB/vw3NYcNGWFb/m9DXbl/kdex31OyRrfNusdMPEP45rBsO/7dQHEYL8F5vTaAbDcPt/0wv4lrvX1/T1oU2xfMJ8DrCTQU8sxnU75ptnxa4+NVdILfcuoQ7eY5IPfjxE7qRur/Ml+w3GPwd+LwhnGKq/9TbeMxMH7PMMedLLX/q6br0zfYBqN29YSsPZeHtPpM5UnUm6b5LEVSsX9vnHppR/lt49rB8PlZ4TnaifvGNKG29b6B2DZ6zwWAq/zT3s8erbH4G9UtsKxq7fNUP1Y0qZLyQKr85pJP96/D9t88zpKv5LYcqWCmBlqoW0q22HMvP2zis9YWTDmdexD0c9926U4/c+U5+JjrsI2a8DSvX0YpF+tLB0wb4HH4PP7H/GNi/hcfJqvBKzZGyfeM8444vMuHOv6R33zZYo0nqZfwDzzxom/f++dtft3OJ7pj0EfvCb+huqd6Zdux+MJ0+OwHLwmXg/W+LMJU3AuWXb51mnxmoUHawY2Yv+cYF3eOSjO3e93vzUFa2muhtUzwGPiefjkod31uD501fi2dQug78lXH+rAOW/Y45vzC+G59sm9x59HMxKD5xZk2wrtgWGb4vi66fSLq3Adc5C4TWBiPcK49hc866ZbbOcVut7qlC5iMQh4bPqizwaIltDgOEBFg3wz/I75YK6AqV6Tj88cYFU6MBizG2R7SfTPk+82auK8DZjda+IYjFo+mMVrm5TlxJYtKCNtiuMzNDE/a8Cwfy8oS/y2IfUkrhaMxrWAGTz9g4fNIbZSaQVTvXGvKMtoLcopMJvXxLEUXW9NLytKmNcO0Djx+yMwzNeirCZWGGAHwz4cg5+ppRA7TQ2Oj9KInYGfyXjOzSDWXzdvkc/gWBTM7LU4Xf54uvzcYDhm8brMJfTYpgzMKUze94v3SCb9GyId25witQyVjm26idn9jm0WLDa+4rNhupHziGVbiA2HYwa6n7YTG0FrEecSiCXCfppsz5akERupo8flK5dnEBulG5/ks/nzcoiN1q1YRut0g5n6CfMcE5FltKziD2Jb7rHrdHT53ZGr/NHX5iyIo3PCRAyPe9BsYG5vmz/zs7sD6sGcXnPp7vY7XjK9D+u0t82VcLxErR0M58Q6ybqJbZDM1OozNzU4zkoAw/kijsHocreDYf8egOVOl0MSidsOy4Eu9xQwnNc7pOWeTtoUx2dkDo7NInU+DMdgdNvqBltuEJYuHS/B8/Ajvu1Zk07xM+NRXy0f4LEUbgvAsJbjuhw/c5C4L3WXEHMoaWC4/n2ty/OzCjA=
*/