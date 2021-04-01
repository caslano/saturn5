
#ifndef BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl { namespace aux {

struct v_iter_tag;

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct vector_tag;
#endif

}}}

#endif // BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

/* tag.hpp
ShKV78ehsGMBilZ6cSL5d1pVvOx4cnNZVEbZeQKcKwUchJRRV1tH9gMlIFmj6dwMmKtebIkwn/h79JidkBggBf1W9IvLSlyMFtJm9m3RWHS+qI3V4iMlgpL/ehiN16hvkzILUaFecdHb2VkoWWC34/3UjvRrahlVt5uAnbA0uFbmW91Y3VkFJc3l9P0WGUVBVIgdVj9h+LAP2rHP0tEOXBppcKjQ4prck9NNF3bmEA5mJA/PN6ASCsLOuMHcnxgdb6SUjq3mgIynTBXGiVFtRDOe7SIwllGUUuZNCY7sV8LK3jA3JZ+L8NyqS5Md0wC+/VuPoaacwSEIaa5BFpD1zleRfAyQuWbRKvnjpbFJXG8eV0Y0/Z2+t18RjnpQ8jZXANGAEpky2pXFv0cAqZ9WHZmDRYhjPOiMCbywps+EgXawssE/Rkl+g8+RDx/CinZMegOQtu939DK1HfNID6x6gdo9yL9ZpSa7213p9K/tJvybyZYkQ5/jUIhwautwt6+M/MUxuLope68NMO3e5L/7owghf7kf5qJFMJN0X+E2WhvgoxPfHHuFsrnEJQ==
*/