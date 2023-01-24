#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/int_to_digit_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class N = boost::mpl::na>
        struct int_to_digit : int_to_digit_c<N::type::value> {};

        template <>
        struct int_to_digit<boost::mpl::na>
        {
          typedef int_to_digit type;

          template <class N = boost::mpl::na>
          struct apply : int_to_digit<N> {};
        };
      }
    }
  }
}

#endif


/* int_to_digit.hpp
JMoA7wgRtR8Z4ZOOHcAfu3ZsqLT8x2bHG88FYtfyDeZZVZ6YPbOe1E56ALbPfWhtBPd9CLy9/iWB4KpoZbMDGDlyew6y0Swvm6ksue6ANryNie9feZUEejaomLgZHWD6/Lfh02aG5EDVBU+4PvgCwJxXoI8MDsZTKJwARb3dLVrtKZeO6Ytop9L2ImvVIAXyOQ43GaG2gTFcRv9G9e36HgCq787kur2TBBJy0c5g+HkFrnYA5HX5bpuinUUHkSMqJpIn2mXE8aBbLrJOMAC9aBlA6/lxoeH2BPpgulo4vl1xDBGxI+JYJ+KuDjFpz6gN1Pa7uNNLbMXgwGwWqYSXCFTHxzot6VTNFokzAnoOSE04xQFVQCX0rRbiv3wP4mCjTe2XitEyv3d7eRTkMvRBfiV2GupptNBHYmMXSguziaZxswo+NIA2UsDyVhrT2Jye0on/tR03hfB30mrfs6XzdSib8NXvnPkJnmKqL7Qsyx6Xp/Lhs3I5HsLP45fFaFQt/c5aTpffWQXAfY7GSCXkK6jftkvC8RwAEYUJNf7Vnoa1JszB/ZvLyJNu894gcZ+NqFhkznJb0c6SSgCHeQDvpyVvzOg75P1iEd62fw4YFYONg8cM36KhHoECEuZi3SdDr9Yq2VEpinDMr9PKzR4Q/EYiaFeYz04Pt29I+3KMXI/QEuS0YE379qpixFAV2r+ULXCM1SRZJxZZmwTv
*/