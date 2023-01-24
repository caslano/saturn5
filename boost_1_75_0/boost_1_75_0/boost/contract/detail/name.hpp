
#ifndef BOOST_CONTRACT_DETAIL_NAME_HPP_
#define BOOST_CONTRACT_DETAIL_NAME_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/config.hpp>
#include <boost/preprocessor/cat.hpp>

/* PUBLIC */

// NOTE: Explicitly list number of names to concatenate using ..._NAME-n
// (instead of using ..._SEQ_CAT or similar) for optimal speed and reentrancy.

#define BOOST_CONTRACT_DETAIL_NAME1(name1) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_PREFIX, name1)

#define BOOST_CONTRACT_DETAIL_NAME2(name1, name2) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_PREFIX, BOOST_PP_CAT(name1, \
            BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_NAME_INFIX, name2)))
       
#endif // #include guard


/* name.hpp
TUN750Zm6b0UmAdmfWWFnybL4ejY6KjDyf1uqqaFJPN9jkJz77s8cg5ml5ZenBnT6a/dZMKjV+d7yJljp2yJ0Og6nsaJC2lHpd8rI59Sz+xIm3d7tnmzFoXHCWNjY6ldHaRL9GpBjCIhl1tUdHR0iBoaGgqsP2jTrzk+vTDk7zjx7BTditZs+uOQyyWkzFh/f5OujmU1++KXp2dMCMu2vzPaqfCpbx8hfRM5sZFwFdHF82/TL5+WU14vxhN7nXKXzK3EROOJmL1PlgcdAq/zGWcwXlLNMiQy1vIMpntEW7xz+6TImjUBLpy0TYo9ZqyX/VhT/VQwHNhUxyA3CUGXIdp+6qZFZrp2whFz/VrV8/n5GsfzcyznFrw+joSGHGWPLbzkre35hK57qzEX5qnLBsGFjMTExA2n90825UjtFrSjOeVHW+lERDaeYlPel7l3jKBN5e3+gNrKMl7KFp9DbY7iexc6jhixY3dlnlibIc37tLl5cmqxi5iif2Xe19d3v9Ym4jMFsvuZ+KKbFOfjzqvfIMksmV47LXBU7Jrk/o8edLBQW941HZV73PGBmqx7dFx5DEafe7KL4bPJnevQyIbBRgsZ160l3kM/IJIxQBBbtc41K/rkJ1Yt7DGmMZvTll0mrK/KM7kdaw/JT7669T6649WyNvMleX5ayq0H1WLixyuGtt/wya7PP5U7WhYhu1AgHL4Tuz140dLx
*/