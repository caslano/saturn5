
#ifndef BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // BOOST_MSVC

#endif // BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

/* msvc_never_true.hpp
rSexe6jwTwjnIl1DkkNzSVQIsvSed4lKoJTSqdMoqKa9P46rr8tHdb0ojw8OxreaDdW62/9wz/Km712Yg9jDMRO98ANTq0YPb15RATqzJ9nRMOutmt7ZSSAV5heZgU8QXzadrhisR1f8IT1U17GRMIOglqYAoVkwyP7/hWrzxnSdmb3Ofohtl5LoljDe9Aq4KaHr4kFYm6W3S6MF0eAJGKFmZCPjNDzVKMzd9+BuGKNiN0wWGmlYE9zrNEGj2nhXFYwk6bADerfQBgkQqdLxCX3k2OlmabPzv/yeI+9QJVNK4SBnqyx4U69X5FeCpbZ35qNGZt0oLMinbXJa3S+F6NyJBUFobaH6EicnQTHeVoXm1lzYJV4vDW+OzTMkaBOnq2LfVH45Gsd9tv8NTp34xmBBcm+xnZKE2GXGa5YJhWAU7qdy7/6AZDTXT+gsDvx834tIPLLwwhQaktGYII3VOVMpNiTmR3LHpw3+5IBLWqkNB5SShYsSgA6M2F5kXyClwwPCvo1uXixEm3ZXFAbLeQxQYPA7sxWu+MydtOkuTYNREzNi4nFDLX5pdQ==
*/