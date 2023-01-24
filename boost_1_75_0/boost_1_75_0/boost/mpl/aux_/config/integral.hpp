
#ifndef BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS

#endif

#if    !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
        )

#   define BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC

#endif

#endif // BOOST_MPL_AUX_CONFIG_INTEGRAL_HPP_INCLUDED

/* integral.hpp
VEfKvFbf3KLpE/W+Z53azwGRChdYvKxOD4g/FWfMTewec/up/bzu7tYhrNDgAcgZ3eGGe51E6tLx4WturRGUtlp8bV/vk2Kfcs3lts1Xqhwb1Ffp1ur+LdPQAFobwWerzQ0+6lTp1GZrW7jlZ/u5ommFySUa9rxCMikUJqRSmvRtklCET1ml19j4bgXWi/6x/TQHMvH5kmWxZSp47JF75e3oQBp9qqc+37Pv+1HL9JvtRejfGCZtu5PzD85/YpiKglTsXIQtsb++H7G/+4qkcu2/2vM3iV4/cwgQjFzwmbStNGeRCgYu8F+KWneeTl5XCHXV7oqzX2cKp5ZJ+25HEYWthu5NEG+4Lp+jXuYvWfoqHJp4/bgdrbrt+Y1H5myPzfgw/mZ5FiJGFtwzVxZyekjjJbJDR5/g87qi119c2jm+/TmroAx/9cNSJZ9h7SOppLpkOyi0uuQMIi/VfIZep6nudwvn68s9XEYWquHaIp2KAMjhJ5VZxYy1g49LIAqsQ/n8XSZXno6uIDeaNtmad1zCmOTXQjaj+wZ+Hncff/bj+Tr/ybif6Ea8Oxsz8SQQOuaxjyM7kwtOEiOd08aA2R1vWIaFGcGv0O10Ga5qEH8NT7Wdgf3OQ7bRqN5/xB++IVvH8pTnqok6BYh1Va/f+jUd/kjmy6hty6XKNd7pjcjh+nXTdh3b9lK9qcXg16sY+BR4sJc0Sbf99bXm
*/