
#ifndef BOOST_MPL_AUX_CONFIG_GCC_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_GCC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if defined(__GNUC__) && !defined(__EDG_VERSION__)
#   define BOOST_MPL_CFG_GCC ((__GNUC__ << 8) | __GNUC_MINOR__)
#else
#   define BOOST_MPL_CFG_GCC 0
#endif

#endif // BOOST_MPL_AUX_CONFIG_GCC_HPP_INCLUDED

/* gcc.hpp
jUZGmoDsuU+MrSPy/edyeR+sRSh1YEHhhjFH8zCESGhYowbF5QlpsYO+oe2gL6LpG94q8X1UCg5ci0dci/k8uAGP5go8iTDjEQKPQG14QuhFH8F5UH2Pc4mxDvd37XDEt7ij4QfoL/74sv3NSu8Uts3ddNHQ1UKeum6Hzt9syGBLosICrWMyf9nakbfEynvjvcOWFun1oG897Bl6OpFI837vOEa112ThdBxLDIU3ZSdTnCRzMj5YEQKi9FRhrfq4N2i0utV6Odsb1c2QT9JzyMzRQqW7NNtcqZwSrDYctMaOO7wdU5JxbdCoO+XTjttqj6shyXG6YbINa/tiuaQSVZiRWDRJ0Z5NStkyzexD13GbPSubku11B65ZzJeuKMLekZY7uUjGR5R8toZUZPBmmhqANIEUKQSeggliBKcqEJpAPG1sKUAshRa+CEmUhgubBPDSXhn2IJS24A2ODHs1E8fN0FyUhm6jMOuPVvH34pB3F8Hw8e622nabX1o/qkm7drnq/mh+7Q/vbv+pq18uZ9iQutSozqkiFviJDM3sY2PgNLsdUoxOzJheX5gXGZb5ULXb/73atnnoc9vcN795+J34DVBLAwQKAAAACAAtZ0pSdjoPKUMDAAB+CAAAHwAJAGN1cmwtbWFzdGVy
*/