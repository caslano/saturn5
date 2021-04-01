
#ifndef BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// MSVC 6.5 ICE-s on the code as simple as this (see "aux_/nttp_decl.hpp"
// for a workaround):
//
//    namespace std {
//    template< typename Char > struct string;
//    }
//
//    void foo(std::string<char>);
//
//    namespace boost { namespace mpl {
//    template< int > struct arg;
//    }}

#if    !defined(BOOST_MPL_CFG_NTTP_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_NTTP_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

/* nttp.hpp
4z/NurEHP9aSmqX8iqOEfQOfhpMVaChsgs8qG7fMSwpJDiSeHkUhZGfve3N3BO/aBuhg7yv6HfVRUYhlzm2qJCZJi8aqfvZ93IJqrf9Or6nflNEnlRDJ6snvgPQng6Ds/daUD8M6lRh5Tx45rjhowygyWykG+xDy+qfcCZRgV8LHk2mBGKbIHEY9PeG2q1ORMeO0nHcslJmZOH5LK66mIjmxYepnuVYUxtloSMcL+rlA6doEVdWGLr9V3mK0eHHrSm2XoFvtl7ory8iVw54iCbRg7wdQgxE8Fuv1YzdNqo8Kfacfq6dy6jj12jQXJ03X0kwShnifMEu/OdbA9h+BgRkw0v4ggy7rHGxLXVp7pVoF1QcX9OMv+DcLItQZny3lRhMnjRZk8bF7WESUcDHPIZ/dofqgB0H8W7irXvsI7iDnfEyaxLErKmmPQf7TSpUpYFQFf8PjuCiyLwsG9Z4wDrWUOG2ZGFBoJW59fFIhio7eOP14yKU5PodO2/3e5E6OiLMGy6khG2hDAhZvvjbWZqTN8a/+jW8/21sjgLCBVbxzDTaJkwU9NooTUA==
*/