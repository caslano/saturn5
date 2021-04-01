
#ifndef BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__BORLANDC__, < 0x590) \
        || BOOST_WORKAROUND(__MWERKS__, < 0x3001) \
        )

#   define BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION

#endif

#endif // BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

/* overload_resolution.hpp
qtg4rBiMTSDK+Ky1MmMdWvn+5KUBR/PvLJ5hqRNRR98VaXzCgUrv21gvTZbWaMihLyAYaknmwRKgUXVCCr8V0b0cZG7cbwnTdFV7aXcsAPDwfoZ6FA7zOgoNo0GtRJdfc6k2b6WhhSxNk8TR26IYxfTKf0VQMhm/jCVpmluoLsQSDP37qJLzsLcHLBMyER8smIomcs/CFAAL3mD5roKAIGoBPgDO6OMuDi9iqDrI+qgQHe7AGxorgVMXdZ/MZmzcU4j+Yn4ydvDp4osVNMJLuX/KmmpdfvwPCt7d3GhxpUupCqeu3fVwCn7wAz+JM07CQm3/nnpeBUJJVMlSkz9mfmxHSLztuvygCnw1WH52ra85d0FKNKgsZ0uLoZOANWWGgPIvC9gNddsmKpgMSpzgXjGNqk2E2nlKA5eiFuSQ5hslymzuRgaoZ2cLxCGDBMpgoyDE/zd/aaBYYb5rlAGOXruTgPum34tU/2Ak5oQo0itNMmH4l4dDYNkQBJqMbx/aql3C/Y5zkBlXbfKqSVaeYD64cgUELQCg5jxfM+I114fSeYKBVmi85frvBg==
*/