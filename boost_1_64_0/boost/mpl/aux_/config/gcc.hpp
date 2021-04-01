
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
94y3iZl3k+4ldvpAFYUGyGbGMgjBJXigP9uPWC2qoV01SdEM0tzOOJY5KaFjSlU+Yq5nA5A5rsrQqGauiea+0apPugcOgysxBUzqfGjMR8C4zulQ38rNCQ/kTr+Ta1Sd7xQOxCp3rvFFWwJg0HOr8I0QEqdg+8gw7IBsm5WLlndh8f1EVNzn2QzFCdvDX8oKDInRaEi+It+XubTuQ8qhkYZJ5dllwvon9uNXoXZso2nsgQnyezDsPmnCY2YHepVwKOrSDjHF8rXqkLXc7aZ1s3TeLitH8s5AHmNhc6FYRSoTr69QJcnG5sNVVmbHvValdaCr81TPbBq0o1ePLvKwBec0PZeYuOKSbAmZJGUX40FfmrLCW2JqT/MRVaehnmtZv350fStuOKpquPRcJsdOn8dh2oseySY+GBMZGngZzljWWmj6QU2A/40s3SZSsLCEU/s6yMKLLuw/GfHCGgycYnzano2oAeKm+w0WdNpaLPYGdW4WFcq+sM8Gy5VNk3COIWOlBB8Sv0fdpoEhM422ItRoxi2ispGCM9lpJ1yty4wiZw+iver0gYxEPA==
*/