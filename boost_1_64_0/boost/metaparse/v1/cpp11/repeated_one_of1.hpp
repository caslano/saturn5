#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of1 = repeated1<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of1.hpp
FDlM/lPofEcum8zQOAkd9GHRvnWhTNsnuJVUA4h24r6t5RP7MsrOv57gkbbBospcuvZjzTz/kPKh3zy7ATqM8EMddqOUK9D6yWb1rh3rMcwVXHv505Cbmzfx291Sjm5ScvQQCv/+/yBH1N5l5ai2jBytjJCjz9u2zafMm0LWrsEb9nVWtjhcL2UL/k1uFrLVFfR/1c4KqGRL9+Vo2bq1nGwtqsyla29r5jY1snObkJ0vS9kBLV9RsvNVITskH6HsnIL4r5u5C96q/qwVBt9vedAGd5xlbUw6UDZGJrt8S4Z2p2iLC3jYq4OPdYSpr0+VihO52SzD1sBOYb9++ZR5MzqfShZyAm+92Rfh/TTjx6aYR3i61tgtxramjZOcB5gZd439bWE8j6D8J1NkIJMTFfledr3J35Rq5AewJgsjN5tF3xbLrzZ8Tx2yT+IIWvpgM5n3qqnYJd+Udr1HxfMGZE7KD9GI+a1zDhLv/LO9sQprAN/hMcR5K+t7aHe0M8Xh3A7F/QBxyN+3OfR8HO85/Qh2+u0RaVbWRqe5A2l+0uyuMdu9X4zdCBO24e+M14IzgXcKPtVYPhE++cnnXsCgecftCtMaOn8OOuU4/Y8N8jypqYN6sxH6FG+PmX+OyL2carHOZHBWRdxB+C349DuUD3za24nG/wPw/wh88/2SE+03y4R4X+we4Mm4Czf4cX+WegE0zqg63ovy/irKe/s6SSvkBumx329p/TvS/sORG7ZpSkgj91b/hTT3yzTAK5emqsVPs6RF0lWuv5DPDuAf06L6B84kWJ+UOi+Uq22xY5HXgyLwo2y3FcB/cEvAz2NW2X0II4f4rl7Pvs2PbzHpLshlcX621oZ3pcingEdhyJ1/MDV4/3Nli3y7L95Lr+slBvqs9AcBK/evRxkbLObs+alk3kPYnK7cncvyGLvB5jXblzw8NHleKnWxhC+zcA9h02dnd+ZKnNeDKK90tkTaktOs8GbjKTqeOyFgDzF4mUy6YCP8NZ0aImW1qE+tl4ifHx+N7TbPudsqiTDVKvrtwwLp4eTERN4mCAJ4438+fHpVpRFpGID1tAXS6WTiHMjaFosb+mk4wQ/bwkz4xDBMYwf8V60j2Hqrz0x+UGajIkz5O2etFsSNot+80E1rVZZ2fBNu4EfxZEvXTCrwt1WyckttlbWebcRaXoIW77I5fmPe+pMrltDWD6V8tvjjsinEWIghvN7yMMUxIo8mU/bFtDhh1kPhI2i9kI02W+eJ/cY0mhC+PeZAy8nJPH3lxU5fKVBTJSaT0+nMYSG/S3z4TC5fDPtmNXAzudk0naW08AtrqY/4cCuUvDZjYYVx8haSgE/6h7coeKGYL40XvUasdz5C1H/9UcvtvH3K6qsN0FdbnTP3xYMJ6qy2jQCrNrASAc3ZP4znpwgaa8rImBw3qc+Ha5krA36D3SiL+e2z2/c7VQt+W7b6sFNbwOvEJak82XsNOLu/WeqU+ftttH2+CFkz/NsC/p3snAWDfWu/0945wR5zSyV7rrYUqumBEs3I8uMHgx5jN0GtTUP9yVn3Or3FXSc9o4XtMt/OL2XC/eQ1JjxZlHuyZxleLkjXfuq8WGu2JPn0hPte4R4e7Ab1Xus2jI8NLWxvFM9w67GxxR2zH400jVxfklee/zS1uHZOM4V/uFmWu8RrQR6twI2gF7auS2870nUgXcdRtOF4MZ9padm2zfTP/yB9Y+D7ca2oe4/gyckC3qdkIwae9tJfg9WPep2seLeTwoTj2IgDLZzPaS2urXku4zr5rlXl7wTeIMofauE1Vz03IRwlN8u8xyLfEeSLtHqOQrSbv27aUaTd08L+xpaYUdfrGRhKDHc=
*/