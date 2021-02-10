#ifndef BOOST_METAPARSE_V1_NEXT_LINE_HPP
#define BOOST_METAPARSE_V1_NEXT_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_line.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_line :
        next_line_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_line.hpp
/vsfUEsDBAoAAAAIAC1nSlJcfAmwRwIAAAAFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI3MFVUBQABtkgkYO1UTWvbQBC9L+g/DC7GELxZ2SlNqiqG1PkyJLWJ1dBDoWzX40hE0ordkR1T+t87suwkkF5760HSfunNm/eeFBN6MtrjSMRZubT8eMTN2rqFH4nrJJltb3B1kQiHi8yhoR+1y8XS5rld59ZoymwppFy7jFDamkSsXhBi1YKKdzBHt0InfbZAETus8g1vLzRpKK1J0TyedjboO21VNTgcwFE4hLGuKFshzKwjnQeiRYnAprnOtRqGYRiIc00YQVJjHwbHcI4GhuHgIwyOovAkOgrh6jYJxFhzFTm2JTmbR1xUmmalzwNP1mG/qD1JhyudZ0wL+5Xlecss7FcO9+NA3OzajiAlqnykVGHt4e7iSlwDS5LJpmJahE+kUiryT2BS7TzSaU1LeRKIb/LS6QLltGrAfATzs9uL6d3kavKFGyWXGcZwuvQVNy/naGrWeBNBoZ+kfsDTD+H7k6b9fb0bLB8ojaBdKtmqLUeTW4+BCNiMRu7GlJ387Mo4z5pXW1fMdsIH/FblkWja4+P7KcQl8x2Jz9pnBnqvA9HjTdXuQmxsUehy
*/