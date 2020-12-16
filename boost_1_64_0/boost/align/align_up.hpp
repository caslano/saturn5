/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_UP_HPP
#define BOOST_ALIGN_ALIGN_UP_HPP

#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_up(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T((value + (T(alignment) - 1)) & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
uPVCYpcUVf5W1xyOL1CAJmQPyvo/yw9XbftJO9bmleBBQv2X4puav53fE/D+/iK8PyfvieplvNGoqDEf80OK2vwhP6SpVfLgViV4cBU+IQvVsWHC/ZLAxk+8va3xA3HPln2b9f609W4//weropw/zkCjD6NRn3usinvbcmQ9Fzgeg8+E8om845hm7jheWxtwBVatD+mZ44vKwV0DeByMx4PyOBKPu6P5cTIMVfXbgtRHXuc+wDKqx8ZFfDEzxWVUGbvV+A8EwRmI+1wwIUXdLu9uvKSpQXjBA4nB7VTfrxn2FHbcEOtbyVdMg2n5fqSfJ+lpHJRZ+OOfJD0B0eLuUg0l3U3pzeQOp4c43XsND7V6XyBhMHbJi4CxDi+s0yVYgOmoWwXTuLYaVP0uqLpEXbWGIxhFBabDabg/c0198G36P39VTR7IJGonzYlavIVVMPGsggGmriRWvqKYkRHvJsaDLvW4RbpUSs7k5HFuks9dq08H49G/vKMNJjoQy6FgQI4oLOri/1/q/hzBlpR1SVELhXFkbtYRVjXsE28W2D8m2GfYYH9r1W+EHbE5JmcVPERDX6rfByMG6bDSEPB2/9K2fwaYvpwdkHjV9WA48N33XFCUp1ni08ISi3/HS9IBX7/5KiIYULcRo+L3cncRM1z1+odmldyB+sGu4Y0VRNeUH6d9EeCVRznk7+8+YY0vKXLUS+X1EedC2QcEG2ejdnERoyvWjiTvwvxWilXJcpmJ3PnkNLaoX3bRJNQx2jFTR6iPV1jLjUeuEUrH3XutR8wx7V3kY+eiaIkXeX/UBq+tzIZLeL5fldVrkhPr2J0fWeGiPF0lluRm9fQnnOfMTONxubVnG+SzLev4Y4N034RweMTP1EN1lUgPcUNp9XoLo/WpuhGwsVMZeAJv1bHMs0TkMpaLUGR4Aj5A9Rumev9q2NOKdtmFJIwlPHloJXfS+vfdTuZu7bKMMkZPcBDp0WtO1jIGehoJ+h9bWvM+T+3/K/AkV9I0KHhjtlh18UTg4Q+Nukr4Ow3LLP4E+DoCwx8OkSmcSxx10APs8ZXhUruxES8/hHzJm1hB8WcuOFsX7EQ+2zexaOrLiVAvrgaXjkIaDc/uUpT8RHvEp8ETftSnFk1hk03eXzN38Ji3dQshEG2sW2PzxaxJB02HBOig/3IZ/1xInNjrzv4WJQ/xDsLjJgA2Yk1FVZfTc1xzBtjTXQdB/x6BH9APIIM/x9O3khacvwk9D2pJz947ih7Q7c+V9n2Dqf0FaN+v1vNGXiCHFj5FHzzaB1FGW8EuHWKhZuYq/tpSF1AxPxEi35Vuvyh/Hme0yke15GupXT5Ritp1gD89bcu1jo0ypXilr+x2iilwOhxb/kU/uu+0kEF/aLtpwR3bzbpvbSxCOEE4wSNNZwXKdeUdaRAzy6/NuTn+uOvOpXA9G5iFKXw23LFAdTugOt1wt/KXGLDJl4zClX+oI83oHYk/KUZvJ/4kGb2bFLUJ45REvnKZPOStm1NvpvFERDYfeco7doAPDvTdEJFurEX1XwwWKbMX8rCCMcVRy/1pzAsd2634WRgc/+rpqUmeg9NTL3THZGwfUea4CZ+lUTe0kE1VE2sP6jmDdp6DiQS//AdTTG96bliOifWwJsWHHUyKETcQKb7BbsnppQJWFhAIM/Y+cESYsQnNdM+r2yj7V5hKT4v91LSfT9jK1ABUfzCIUL3Dl/Ot6l+GbscyFlezFfTEMR2r7f+kThCR8m2xeE+HonDt3ByFjySJVj99VDRa4zlFpIRnBxKeS4DnzepvWN0A4hJ8KorQfO7N5dYm6hRmnX09SeP737aY/hnwB+ULHLGg+OMGdgTVIwA=
*/