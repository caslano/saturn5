/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#define BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <string>, as it's quite big
#if defined(_MSC_VER) && defined(BOOST_DINKUMWARE_STDLIB)
   #include <iosfwd>   //Dinkum libraries for MSVC define std::char_traits there
#elif defined(BOOST_GNU_STDLIB)
   #include <bits/char_traits.h>
#else
   #include <string>  //Fallback
#endif

#endif //BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP

/* minimal_char_traits_header.hpp
FIuClwoN7rA2nxzPvZg35UFZoBatnbHFE3wYFOIWReWosOfk5x1gWYzFpcUtvaaP2YHf8ohaoSaPMZHvlISyHVmMIl9MZTsypaHJ3jUR8d+lqI7bDdWfnbks7H1kqBnogERukZvHTeQ756vvTcg5OaSmwemjugevQvaVNDT5tcWQ5+mPXUtIJK+ZOl9ZQtDPCxc8SiYeY9fQC75bf5m1uNyk+UBRF04GCNT8eRfMHxQkBBbMUPQ1vSNpQjZX+HU/Qz7LTUA6VXc7fuBJXDxueQiapL2otFLHUi8/oZYypkgr7v5VqH8AnFX+woGLBlLu/lo7HyN0znrjz0LzI9E/8J6vsf5MJ0AVilz5ezaCM6xsP1dzIXqfclicEpPZyADs59LdyUh6S0dM8gpslEgj8UbkxwOwQRHUWaPMbPoXuhmgcT25OhkQlrnW4HPloVHjhw2TTkDP8UVd01CPh9jUfzMSzeGrBI16XZPdwuce3seA53TbzXi2MII2kEsEs6Tdnt87bhbp2yqnSyAOHjbuhpbUip/CmgJL73SQ/Zm5MSI0Derm/0f4/ai3Ww==
*/