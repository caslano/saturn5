
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_FLAGS_H
#define BOOST_COROUTINES_DETAIL_FLAGS_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

enum flag_t
{
    flag_started        = 1 << 1,
    flag_running        = 1 << 2,
    flag_complete       = 1 << 3,
    flag_unwind_stack   = 1 << 4,
    flag_force_unwind   = 1 << 5
};

struct unwind_t
{
    enum flag_t
    { force_unwind = 1 };
};

struct synthesized_t
{
    enum flag_t
    { syntesized = 1 };
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_FLAGS_H

/* flags.hpp
51NF3FBfEb9EayL/MVUkNlNEhkMT4WdU4WOdsusQJ9LeXyk1WxBDUq6mNKA0ojSjtKOMoqS3gL8UOyWPsoUy7Qf4hwz8wFq8WayIa2I5tTJIEb8dYe6s7dOFiiguUMT1PWhjkxALfarY+psm1B818eB9qnj9TU0suVETjen/gxJFPLlEEzf5OPE/UxXNFoAbaXfyAU18Fs4+bCtNPNZdZaE18VfmH7ZBEyeQqYbPsF+8VBEjv2ZNeHH0y1sU8WAVcB683eHTRMfmyO1BTTxJMDxwF/d2ZG24lkf9tSNYczfyzBo9N0AT7R5WxZPhyGueIs7sUcWJeE2MQt573KOKwj6aGLeBL0XGKKL0UkXcWYosN9FExhTeA36Q8z+nwK/IxfZWqmj4qCbe+04RWWGquP2sJh6or4kXtoJ5q/OefeY9lrX/mYDlpxTW/jlk9TNN9L6ftRuFrvFS6+TrVXFDKWs4VBWutzXOjZHPvEkVc5/mWyK5yC08aHtYE6uu4ptulHspvT9hPx156HRKFW3voO8elHaKmPGkIt4vU8WascRN09g/GEtbu1UxhPGNKEDG1ipiDvS1OXwzfzbxB7q2aSv6fZkmpqJv29uyXhtUURf5zbpNE7/fp4jeyOUz1RVx9ypBPVX0aaYKN2v+OPyKf10RmxlPgyvQZ0ozSgtKxGD9xbmqyFmqCtsDmshrpIm7Wmvi8GhFPBBHG00UsXg+a3eFJu6Mgg9Rqrj8Kk3sCtPEWMbzxAuqeKwb79G9UxN9pirCkRZ4z7uNF5n2fVoV97+DfB7TRPQhTexBZ5/bjgw31cS9E1TRZKAmklVVvNxdESde4V2WNyDHr6qiabomZvRG9ruq4ivGdhd135qjiW9WKqLBA6oY7FNE3V7I6hpFLCxgT4o13pSviTF3a+KGe9nH2aaKXT2Rm8mqeBQ9eGObEDHHWJNdqjjC/BLhyc7Vqmg8QRG3/RXb9ZUqOm/RxIttsC3Mpx6632og8jVNFQXRqnj6M/TgZUUc+VYTW+DZTsrCo6pYfQR9G6mJL6LQlyPcj9xno7/fNNdEi+qaeGe9Iq60c74jRhMtkaN+d6hiCYGODRs98ihr9LIq/vQ8enVUE60HqOL0V5r4ZIomPkA35n2qiuvHK2IPY5p8GnmD/7+vwYZhwxXi6jPVVHGbU0OHNTGlkPaGsqbwf1p/Rawhxkqoq4rwBFWcikPGmcuxy/AD2P3L/wIfxqhi0gxNeK9UxIR3NDEnXBGrR2nCV6KJoj6K2FWftZpEe9TbPAHbB0+XsZ5jJ6MPqdjJydgmdO2XvehOMe0uV0WC/m2qRdzbBZ9QS//+gCKmY9uqz9PEn+MVEX2rJvYfV8RTxIA9MmijAT5qloIj0MR3azVxCptzK/b0Ctb8uWzqfA2vNE3sa4s8kKT6yqOIjt9ijynZ6Oynz2oi/R305U5FfHGJIt7uhh3lGzvXUbIpuZS7KY9R5lAeorxP+YhyGWO4glKf0pDSkjKOkkPJpwyljKSkN6U9SjZlNmVuU9qizKcspuyg7KN8QnEg10ePY7efR16Rp/0LFGSDaHO9Jl65C93APnUerIr16xTxXIwqBsxjfZ7gnbDrVHFyGf6AtfgZXjy8QxHt8Uull2NHRqNXL2PH5imiGUmYKsx7JXZ1TC30/BF8XxtF/ElRxLFH+a55Gf4YP9LoT4p4BD0biT+/pSfPdeZoojr+buG9+JdOyO8wIYZv1UTtJdiOmYpYj7z/hG2YhQ2tRt2hHTUx5CueIfiY8TvxXdiQvHu4/q4qPsDmHO6LvKOja0cq4ux36Avys7UjfMIn2ClZlPspCyhh+IUvGG8fZPSK19jjqANPsX+Nv0Y=
*/