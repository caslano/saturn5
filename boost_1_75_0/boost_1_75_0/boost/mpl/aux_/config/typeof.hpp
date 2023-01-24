
#ifndef BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>

#if !defined(BOOST_MPL_CFG_HAS_TYPEOF) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   defined(BOOST_MPL_CFG_GCC) && BOOST_MPL_CFG_GCC >= 0x0302 \
        || defined(__MWERKS__) && __MWERKS__ >= 0x3000 \
        )

#   define BOOST_MPL_CFG_HAS_TYPEOF

#endif


#if !defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && defined(BOOST_MPL_CFG_HAS_TYPEOF)

#   define BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif

#endif // BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

/* typeof.hpp
FBZjmGlu0yemooWSPwxkPeX0Yo9hsTHLzZ5qo9MdGVSZ/KSo+QtlheSqSaNbUHs0TdnMzJAF+6ISAxus21PbxSSqVXEMFdPIkTIBjnjA4Sqv4jBEpMIQok/yQ4rctYNxgEMcTBgI4sLdf6PoIaBstkGKIPEow6SRXFLX2TQJo6Vk1XhvWI3XzOxzgOGnoPn28g3skJK9WGgF88lQ+9KJJ27AEAL3MHQxVY73FG0AYwYqMfCWw25bNZ/CKsS9tAcHtJL7pcczaqjRb8QOC2PW9Qs3Rq0YH0AfKYTggm9UjnfZ10YKkggiL2KRqZVY3dAOohXoFKYAzCZfuNDnw/jCbP3Z4hjDHx4dykCnsH5WK3TNHMWP6cLN28OJBJnxgssFoUnF8MGdj5B+e1lv61rCi1I7J4klHRkSfWecOj/PvC0XU5Z6km+apI+Yj7s+JuL3D5wvATbmyyTQ38iQTbFsvQsYMxblvwiQJVCEcolcyIoNUmd7q/bEZgG2NWav+VQT3XBpS+UskJo58ZB6YPTJVAMa+z+yF+uRsCC+EY8WIimmRHZ4ebazz/TpJwyRV7FDf39B+q5A0FfGmCKIbM6e16wN6WIg/hWCIpSJymKYB729DOo2yFGJLizAMundQMjr8S5S7QpB2ziED2SYRCOgg3vkDfgVTxWmhriNj0rQHCWfAFxVbTjucG/0sxNfbnhBHJHjEKx4zu+Hzrau
*/