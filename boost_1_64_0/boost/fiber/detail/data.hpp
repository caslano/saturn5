
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_DATA_H
#define BOOST_FIBERS_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class context;

namespace detail {

struct data_t {
    spinlock_lock   *   lk{ nullptr };
    context         *   ctx{ nullptr };
    context         *   from;

    explicit data_t( context * from_) noexcept :
        from{ from_ } {
    }

    explicit data_t( spinlock_lock * lk_,
                     context * from_) noexcept :
        lk{ lk_ },
        from{ from_ } {
    }

    explicit data_t( context * ctx_,
                     context * from_) noexcept :
        ctx{ ctx_ },
        from{ from_ } {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_DATA_H

/* data.hpp
jv3Xvr6q2hSDmWHv+fqZ02Qaxq3DK5N+2fXJK+zaJLU4s+vYvq2u9oSA4Sx/Peykje4Un3aGaY3FSKNHx00V05FJdOC4XeiOQQRQbUeaOH/0Y3b35EJju9vSdU8fLgjZGMSASLvZj6iG3tYuggb2D95JQPujSJRcrp4YNTx03sgKVQsZEvwe/epQ8IvkY+k1iMXNUIdXibLdmSX3/JItRpRCosvSQYqolmvdI81OTOzhuJAWdUh+sDhIKIbWc1Fp0JRkwTwyeyUMP1oQ1MD54w2ozoX7ELFUbtGq2IVYd9JLMoDaTgvJmCjU7t6q3OtusgWN0laJAR7fteTLxLelreUHQZ/IGqsoCRiPuGHTu9oTd9quDuGH+77nFBugkiZ5trC+1lG1vQDn0T/H4UlztKFoML9l9dAmvcXRFLA73RLoBBG/SBHTqdxtZUKKPqShCI9hHLZqKCABNRSaH+XO51C9Pvkcjz6ef8dxPgbMG1lQ570e9rUL57noknmUt92bTSI1vLnfjxvb7IjJQJf4kd7osnnPDdNhOA2qtb7gw0/HJe30U7ixENUGug==
*/