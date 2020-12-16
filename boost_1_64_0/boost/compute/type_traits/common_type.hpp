//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP

#include <boost/type_traits/common_type.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, size) \
    template<> \
    struct common_type<BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size), \
                       BOOST_COMPUTE_MAKE_SCALAR_TYPE(scalar)> \
    { \
        typedef BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) type; \
    }; \
    template<> \
    struct common_type<BOOST_COMPUTE_MAKE_SCALAR_TYPE(scalar), \
                       BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size)> \
    { \
        typedef BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(scalar) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 2) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 4) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 8) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 16) \

BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(char)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(uchar)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(short)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(ushort)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(int)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(uint)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(long)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(ulong)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(float)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(double)

} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP

/* common_type.hpp
ezDvyu1jz5zuUsCr8h7Oi7kuT1ppeK37+7eFmWZyZRV/156H7FeEC221UJqIjfMxACSeThZ7afEU6HlZGMrp3bmOBdZWNuYhEO6KvRofLMqp1dy31nfp20g7/w53d1OY3bkVOC+SQ7vMuQ3xtmkdawyJYSZbO9uz006hXeZ4R3jtVOO1JqvxFOIYr7iRXXi5P+Tjcs65QivDA2s14aX//hEu54ZxrTS3hMcuRakd4qFzTktcYEbytAaOj6PF+zyuhtuGkVXd1E0zPf1xelBm2gcdy6Db45Ef8Q5t+Gp5njz3tXe0Is2QJ4iDQ7YsUY7pSoZka2pkZX91Y+Nc3AeU3jj+yEbh/IWc70gjBdc66ukO/t84yDO4AedQ5PcABdLSplG0vzcsxiF346Cn7cFGvUcOeXpibmuhoZXgXklytt/OcAXM22H9oqoZE06D/uUFrB/2M6GykMTVgleqTcGx6d78vRhe+tQYkr8OecpijC9jm7VoW+ZlGGzGsQ6yCXcFPw/VU1u1pvFtTfwwzoG7WlDaDNG8oo2rizu+Hrme3ovujuLyjDHEZ0Qz7oJpGnTG8Sxj6xDLh3iKWKd444zHds/urq/GTjBYnfnSb+I6axspFWXEP2qKXIa5E2SHk2CYTSu2yA4KOMz26hVl09C2pbQtjm+OOysOZhmEcerVsd2Wala12mC7OIgU/H/BlVwIWjuBuDgYFMrF5NxTQrm2laxJXUGcvlDYEN6JtqIa28DBn3C2cc5tSe1ZaJ313Qe3/34CBfopOachjNdt5VuaBmdxJW4Z7rXJOa/LOYFUXDPKmAY7ea1Be0T5YiTIujZMVoOh6blIAsxBHxrbqhWzRjEGtvKagnliZEsSRa01bRhMrW/H86x3dsEaKsNfYXvcpBWSWoG9vHbBf18Djz2bVsqWB43zFrsuElnG96RfA9lVTV1zaijYzWsczj9AdhnhlVPMCAuVt3Fhff9gzjmviEeJbnhTaW1IbGGT1MAmONAX1hsQr5uyr6mq3GAPtq7OTK7A2ZuFTdUq7rmm2Ca8cxTu8ch5i5w2PHimkkVYODcwPsuxy0LqWlDZkKdd3Njb3N3Z2RxcJLQtXOaGt5YxycjaxbiHm17YW8/usx5sfAPZCNxUyjWWTPcG7+6N7vL4UY5/kPW8qVjd7UtEaxyA/xPSX2nmgtGD/ujsS/3Xumauv+GNoZzztIUErYPcVQ3+L8dzSRSnnlnPuw+X3omXy586HVecl5dP974GHp6MM3jZHZ3Ibu1sQ9sK9ghBvparYc4N2TWkDXUdmOZE+7PnYnfqzOKp02cGy4ud5UUsyuYjkO2KMVMFplKe0bjvCtiHh2xz0nAatKj/uzwvZ/MVN7xqXtaiqipFLYEBSZnnzyC7igSqmdH+/8rzr1CebaAqjaZTntG64hUQm3UtNMdpfaW1EnGkO7kQ8wYLw4D/CspbK7lizFPYwgT6Ybx1Lfw+10KywFo3zhvYgvvs75m4YCvYprJcz7Y9jWwtIVuSSMZ8LbTt6i8NWXEd4hhNNBekZK1qrirI1+BDTsP+ZWRLEGbqRtdOk2Snrx6cNXyXyMWcv9RUnDXO15C3wd4ZuFsW4es20JbxQFIlLZw8CfFFgH8iyk9bOWmpIFZIitrgGVj/QPnhxDJnDbO4mrp3G6wRiP/CeeGBqop3uwZW8kZ3ZvDVH87xD2ShCjqoimQNLrsnH+lm3AbHKj9kBBwI5OPzRXurPE85cWVGskohMA9RlLHnLW3ckA9wGCdh3wjKR90EYRouunwsLRf5+BPSLRgPsq2rPh+Ss0E3nFlybTwn6GvjGtH02VhYuuJ0/JBGK+W83S1z3pINkitn6y4PuaM=
*/