//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_QT_QVECTOR_HPP
#define BOOST_COMPUTE_INTEROP_QT_QVECTOR_HPP

#include <boost/compute/detail/is_contiguous_iterator.hpp>

#include <QVector>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename QVector<typename Iterator::value_type>::iterator
        >::type
    >::type
> : public boost::true_type {};

template<class Iterator>
struct _is_contiguous_iterator<
    Iterator,
    typename boost::enable_if<
        typename boost::is_same<
            Iterator,
            typename QVector<typename Iterator::value_type>::const_iterator
        >::type
    >::type
> : public boost::true_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_QT_QVECTOR_HPP

/* qvector.hpp
HZF9aPwr+j1jGmW+Zydy3rVXSe99do0F4wSvjfszlTez3NShHpxHchmZPjxx9PBhZSzKufGMyncsoA2AmyeJZONwxLh/H/mGAXtfN0sJSv1UduiDiKumlSOjuSuoijQvtXsd3qZ0UyEL1eTtCOIOa3JSK8mqxPXiSNSHqEg2qn0sJqgakiPL+FG9jHlSxb4f1GU8LsqojqtbbNYMa/RYRJt0ujk+ro5qdIwB+LrckOjdbw7gfPW3bkznW+g/3tmNNc9EZ76o93VaT9w0cZ3r7euJvL/X5PkWiy8XBH5i9HW4tlHwSLqOqHfgpCBmou6HvdkX9TtMJ3ETurIu9bPJfz7u4E2ULxpxMNPUo3EdmfLW/sNJB7EOv6TZyRRFFXlunmpbqvbSMOJibfiSft8XRWmcJoHgz6ZZvdTx3JkUI96+xutaZeaXLDI67Udq9mKw3sHuyr5fqfzHaJX1ssLNLBZ0QOZzHfbVejlpbfdSX4YPbe/XcAe9/CXzHJh5QelaJ0Vk8zH0CW3uch25R/mSsdfJWCjIIOTxHLuFYAXHXbomw7eiNKN2Snyr5wyKmlL1BpqMzPIy23H9Km7t/fSO7aHmDfvbq5q8wKr8wi5yOxUVysxXu+rVU+eim+NOpT0X/WGLTjfnmmPbGH3jd6a+3cbgnSn0/y8ae0jHyV0W/z3jBxJuwztGaTNbh2lSPYuC/OtWcr+3HTFGmBqM3aTlss4PafNIZiVumjmVc926GnaffILWp9e/lN0ns6/82k66xvN31I8foL46OE9XacPhk/gz62ebew/6udlmzZmR2BV/1k2gtw2n1f3LljbOxOzZrmMgRtG5Z6MMo3qnjDRvIN6QaGizuAjKulGxxuxs0bF0oG/samGgN0zk+ntJj3+bpV5eBFnJ2x1GGedWls7XnUDYeEwL2y1uH3M7OY/taPoAewZ39fix+aNHRspCntG0tFIrTLw8DEr7evuBI88Fl/Q526+CNMjSZlM9w3fW47SCHMO32twCfclq+hIVCF2J96UHEd15BLspr+24WZp76XvRfI/syYi/h/80fFP6Cf3s0/obv+WhdJo7nmObCNNxx3OFf1c9pJq+Mb6daNRveI75FMPbHfQ9OxQ6T5JfjYH+WZNesyNPZ0YZXboXNd9ffEP2nWF5ftDPFnay7x3ORcpd1htvyjCkPa5Zsbd56j76zvqoWtEd/sx/6MTxIQFZz79ZBwbDQsnvzTtwhu+zdYsOjPHm3P79wKAzmH7Gf+jASB9ivKN1yzamyz949VZtnOkfHN26jTH9o29zG4bZ2D/6WgdGymHjfTMD/WQvxTJ60tz8ysLy0tLC1FkR++Hmyj3fTTc/LIpPZlVZZk2s1M3a9ylnXjx1o8a72aZjgnl6/lKhP3CHTo95tCDFVsGgywT20ri//XEq3/vY3OGuM+wNafweoP+vjdd/34n9ffwYZF1m435zu5x3lPvul7A5RDw6SSmRu8bjTxnxY9/OxuVmiaHr5sHq2mPnZ/l88nmK83E6Fq9Vivy8n38b4fSP1/TcPxWVHtHVvcONNxPl9Kk4Y2ZVpAB4knKH9ePNHXQZsFiNcf8+XT+ZuF4aeEVklTQXU3ZhD8osJJlmkT9Hem56RuwC7i76Q/asm1N/mKKUmI3a1Mo0RZ/it9TCpJggA7lfuHCDZq04N7PAIjaAtqzSBkvnVL45jcZfBgbtjEo7t8AGBmgPV2k0VQ0VmZFKY+uPQnuOSlte43xy331YobEFb3Z+icU+PU+R5Z54ju/Uzo3cStSNdXQn1Q2+T1Ffnrq5oF0eYzRBoe8ozyjk14qShZEp2ec+uLmhhYPVydXZiL95QqQn4lygY/zFJ84=
*/