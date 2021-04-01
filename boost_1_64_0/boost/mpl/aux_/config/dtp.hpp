
#ifndef BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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

// MWCW 7.x-8.0 "losts" default template parameters of nested class 
// templates when their owner classes are passed as arguments to other 
// templates; Borland 5.5.1 "forgets" them from the very beginning (if 
// the owner class is a class template), and Borland 5.6 isn't even
// able to compile a definition of nested class template with DTP

#if    !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x560) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif


#if    !defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__MWERKS__, <= 0x3001) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES) \
        )
        
#   define BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES

#endif

#endif // BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

/* dtp.hpp
nUAvCo2TcKpm9dxQYXR4R/WhJOwSkcB3yc9oOBM9jtwaqveFt4FEmfGEQ3HMWhMLaxm3MHwarsyR17+6hFtNc7GASlJOZbIDdAG+AMo1NbfaBJgBKHv+qk9C1Ca+iZKBISmCm+SJeHphAzRbiDJUk2CtvcTXihsBHs8Jp7XRVvpvKPCuE49hrd/wde9qjt+rO7EF/51K8XlfyK6LVvlgBQj9XGzwBW3SluUNCsTNOFUm0rqCDE8sAWvbgguFjnrrWdgBCyh9230K9aHDsxXZpDscokMpbWr87vBX5DPqGXz+jCUU3+Df3+xGEfQw4uWssaAbSKK0evUTuYu7w4+LRheyiYUO+1jS24uGOeIFqWYZYK/pzuSFvj5+cT8dxwc1WGVtibGGQ29rz+zMoSi5Z/97WBvw62FvDYNxHWZkehXkGQNNxc0vmqYy31UUCxVv3xckm8yC/KIXa1+llVECb9UJlzTNdOR5uacQypWyInG477J02UPRzoKy+EiXI6e+sv6FDOjj33jJLMalQxtrLtVRzw66eb96MyFCOzXRhSLxKpfV69run8SEYw==
*/