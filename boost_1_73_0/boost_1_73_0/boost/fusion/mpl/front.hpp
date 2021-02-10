/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_10022005_1618)
#define FUSION_FRONT_10022005_1618

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/front.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct front_impl;

    template <>
    struct front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<typename fusion::result_of::begin<Sequence>::type> {};
    };
}}

#endif

/* front.hpp
6327mVX1iLS85HT/teHBCsFzu05BlkvEjiYhWbsdu6LmQKmOy41qOrT+5ynIG+GXtlmRra6Ud9izkQSVYcWvtux2eu40lWxyXbec4OoW+k5SWUbp/Ytd5q7tN43/AFBLAwQKAAAACAAtZ0pSzB1dJhEFAADWDQAAGAAJAGN1cmwtbWFzdGVyL2xpYi9keW5idWYuaFVUBQABtkgkYK1XbU/jOBD+3l8xWr7QKtuWLoe4Y3W60haotrTdvmhBWslyE6fxXWJXtlPoHvffb+wkQPpycNIGQdrxM8+M583miIciYCHc9Nrd3oR05pMB6d4PL+dX5KZyhCtcsP2LjdrPeypQgzcf4n4JPvh2GmMl/2S+2Y8m5AmyH9T6ju+3jDTgReWJVOFtlSc4diokt/LZfibkLUPfrW/2T8Nqfif2I0pQzWp25Gqj+DIycNypQqvZanrQpYKzGKaGiQVTSw8+B07yR0QfH+ua/e4BM0Djes4xi7gGLUPzQBUD/BxznwnNAqAaAqZ9xRf4hQswEYOQxww6o/F9f3jtwUPE/ciSbGQKOpJpHEBE1wwU8xlfZxwrqgzIENWRPODaIGFquBR1tM3AMJVoy2HN01hLoGvKY7pAQ9RAZMxK/9Zo+KmK0ftGIH3d8It91yOTPO/k
*/