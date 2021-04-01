/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_codegear.hpp
pfnpRc9ML6PrER4E8mmK4JgDFNWCJePLleR8L+yhn8+LmNLbb9D7DPO4lwliqVPIWC14QrsTbZFEiUQRxrxmco40JFZJ8uQ9D3fEDhAR/hH1I2KUQrpEf4lYQwBBwgYXqF9aapAIyg2EYbLPj4XeZ94W/YsHZNDIcMJhjB3WMPueX0PJI09JPPBHuQWfjwhRQBg8qHku6E4LagDf1hwnSluEE1Q4NBu3e/RXzBBE6IL2TvsJnvWNN9DkMrRguIYF1OjU5b8ntoUpLltEkk7C+K103QYEwzzIueMt7xibZNk6FECrx0vA0bLF8MpC1Wk6vAt07XE02GKqOHg/qOQ1nyKV7J/A34mdI3dAp2DV2zvRR5GQQbf7MgSSiPDCOs9LKVuDKwRjQg5OgCkGFYtnnzbYz4rE3ik5gN2OX6VskX1vxR9xihiYjc2iO/KJxobLaYqNLCoJyQPlj9n2FtcD3ifrrPX70lq1oDIOcJYntr92Brjy2+6P9EKlz9E/Ze5hSySzL+ZpVtgc/usDorXm4rs42vHHfhOpgKX+DnLCagfkmpmywEobRA/Jhw==
*/