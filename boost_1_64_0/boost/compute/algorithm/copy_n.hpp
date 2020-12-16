//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COPY_N_HPP
#define BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Copies \p count elements from \p first to \p result.
///
/// For example, to copy four values from the host to the device:
/// \code
/// // values on the host and vector on the device
/// float values[4] = { 1.f, 2.f, 3.f, 4.f };
/// boost::compute::vector<float> vec(4, context);
///
/// // copy from the host to the device
/// boost::compute::copy_n(values, 4, vec.begin(), queue);
/// \endcode
///
/// Space complexity: \Omega(1)
///
/// \see copy()
template<class InputIterator, class Size, class OutputIterator>
inline OutputIterator copy_n(InputIterator first,
                             Size count,
                             OutputIterator result,
                             command_queue &queue = system::default_queue(),
                             const wait_list &events = wait_list())
{
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    return ::boost::compute::copy(first,
                                  first + static_cast<difference_type>(count),
                                  result,
                                  queue,
                                  events);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

/* copy_n.hpp
jalDps2mtLfk85a22d9iXgvWIZ/UoeDSkEIZhRYWlRQXnW/ez7VF32jqj8q3Ns+wD8X+mHWPZfR/6icyT9EA4k9+A3YUXShu2G72+8RXZPwqKTDt+APx8yi1L8nULcKJ0acukIjCdeuwXF9u9dJ4StWPWUth4k20gvPJc9owZ9GWvpf4A74JzGt3C6ob68SPqbXP8puwsDNjI3Z//Bhb09NCrrcMzelqfPPahePLDcaVmJaY1lEiRd4r3r9pHjI13iwJt6NVBze3uBvIupxI3PIMqcH+6KHnQOieZzne1zT31NRd0ml+u2jdVVm5J/IMmSLptKy7dK/eRTH2jcbuHHft6WDJZxQXW8A8+EY2fYc/Ul+ZUQvuKyKKBESMvogxFJdMnVU/Hc18R+ME7OxaGvfeupZ1I7neRuwTjP/2puzXy/WB1J8U1/fmC4yfNua3Sab4aWlnGr3TEk135PdDC5FpJDLcB0JnrB5KmumvzxCZavndQHHIp764dVE32+KjabxTx3FOXXmZXPOZcztmib2hGSvNEPtCy4/LKFKRKXJh91xxj9Knmz5zglzvGzW2Iv0US/SzoqnIpNnBcVKgPfeC+zxZxlbrXwqkJptx0iwdJ4XPXt2JHSP7Fcw3pmZjozcT4sdGn0jdlXqidde514f0u849QaS+zk5wvj++yNid+9Rs1hc/CzUxczFDuFKZ6Ky/RUvKpSwHyfNtvtZZlcMmdurcPrH7o2QXaP0My0446T4e9fR3PP7J03yxpxv7Asfz4ngn3WdHz5bNx9xChUtPcqaf3UZ0DC9z4VzDdWVkHNVD5HOpMbbmJRxGK6/9d/R6c9e56Zz4uWkz7j9D/GUhlyTz0Vu4BxWddD66Tj8rbj5aZbZ2CutMs13no2tybksBJP+Uo+Yft1nxdUrSf4XISZ4cZX6wsyWf5ZgGyuP4L48tc04PcfZ3uEb9nr9U5GdreYf9Z5m6dEDstpSRRZzXY6aKDmt8vN5T1onVuM053v3/xKzrcraNym4h4fP1N/U0+HbwPic787m0+ALXOkKeVHa4lal52iD2Baw0ONO1T55g/OSaPjlX7MOMjiZFnhuRvvawXF/t6Gvb4ibrFaL62nniZtuXO35Xmr7b9O+dRC7fjuqTTd29QK5NC5a59rdcFbeF9MyDrKYiZ2tcm6UPPpPcngVljZW5VsfmGu6OPtq0x6mhMmauvL26hcvu97h0OWHf3UXkekrffagz8xcoLc4SvdL66mj974yvse/OSIntu+Pb1FiXfro42dlPL4+xPxBjf9zYnW1yevf4frwOV/amROqqPMilJ7ekzFOcfTmyzr48MzXSl6c4+3Jka9eXpzj6cuzxfTnvK1vymaB9+SjM3UGdaWpMHqQ3j+tXTN1ZIPIDrA6RvlzDyPTqy/V6jmef/W25ni19dtzaEO3vRbfIfcjvEV4bckZ8X64yJT10bUgqfTl068vzTtJ35Tv6Lq1jHn056cVN0uso83Uaydla5pMwfbhSFVvm2pvreiSuiavpy58Q+fzIHImWdy37ZccYn3hc07ymf0h4CwF3UD4anMev40jzSumdLc91eirf2crU8fZ4sY/x9/b7T7SO1WMdnM7tSxi9/E39yVHrwrS/1v51ksjMtJrqflO3iv0D305ys9W+2NrvS3SsHW2jv5OeFLmmvsXMMV3M+PUT+s42zK0Os5+zOutv1UNpcu4Rrs2sPO7oOOsq6zCrRFPt+sjW43dKelR/u9zcv33BsLF1F3s4Te/4euB2Fb9Bf4/pavPeOCG396VZ5/gSrAd8HR19t5nXEr9P+lb4RqhbOLyf4GNF1Lk3KyvYAlHS3hjbwyLTnhgSrY48Mzc=
*/