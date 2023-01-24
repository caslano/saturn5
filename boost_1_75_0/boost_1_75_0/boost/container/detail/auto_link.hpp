//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED
#define BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

//Define BOOST_CONTAINER_DYNAMIC_LINKING which is independent from BOOST_*_NO_LIB
//and is needed is some tests that need to disable some checks (like operator new replacements)
//that don't work across DLL boundaries
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTAINER_DYN_LINK)
#  define BOOST_CONTAINER_DYNAMIC_LINKING
#endif

//
// Automatically link to the correct build variant where possible.
//
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_CONTAINER_NO_LIB) && !defined(BOOST_CONTAINER_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_container

//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_CONTAINER_DYNAMIC_LINKING)
#  define BOOST_DYN_LINK
#endif

//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif   //#ifndef BOOST_CONTAINER_DETAIL_AUTO_LINK_HPP_INCLUDED

/* auto_link.hpp
ATZkRENj2mtoSI2A+uRX4PfIDI5yf7vv+/AG5WOgg/J/xPXNRvwEUL52iF84np+dIsgreEfpoO3lB5rPfWHFYVWYs2kXzFi/AxYZ2cBsfWv4UUWH6gdKfk48NGbFYh3eQGNGVLcOL5+aU+NB5Pvjzzw/SH/WfhJbqkohr7AIFL0zYNuZc2CL++D3TTuoq+QpbVjzMhcWRtTDlIBaGKr9vNtPXiPphwyiQzQ0YB3IeKjheUHkB9vd5fpraOf6pOL6IOL55CL+uPjmBvF7oLxnG+wPq4LZ+05xrntPUtfflTSo67qXH0HC8z3lJ685NwkacT80ZeN+yIiBxvQoCMZz4tjWJZT8MEee3wn4y/a3cX1RWZvpg+SM8VCSGg8tH4shLsgXdC6ehdgAL2CV4Pu2KBOaC4n/wBRoziM6kH7AOlBjEQOhjlZwYttSSn646xP+xy3i8QH/x/ULRfyvkblB/DExe+bGG4YDtSbyfEBR6wbPFxa+V4gvLGZxBl4/0qj1oznvLTQRHXI4OrxyeQwndy6j5JP1jhf+qv08/1xxvi4c+d3rVkm3/yXiC4vowCI64H5gvuvRoTkXz4XsOIjA6+vp3Sso+WTN/WroAmpuUL7jOnrmBvGTScnvzxcWVwcW1Q9kLEg/pOK50NMPUR62cFZ+FSU/3s+1n/b/htv/K7junEW1n+evKyMqCNJevYTkYB84slGa4xOM+G3s
*/