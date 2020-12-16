// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2016 Andrzej Krzemienski
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
// Revisions:
// 10 May 2008 (added swap related forward declaration) Niels Dekker
//
#ifndef BOOST_OPTIONAL_OPTIONAL_FWD_FLC_19NOV2002_HPP
#define BOOST_OPTIONAL_OPTIONAL_FWD_FLC_19NOV2002_HPP

#include <boost/config.hpp>

namespace boost {

template<class T> class optional ;

// This forward is needed to refer to namespace scope swap from the member swap
template<class T> void swap ( optional<T>& , optional<T>& ) ;

template<class T> struct optional_swap_should_use_default_constructor ;

#ifndef BOOST_OPTIONAL_CONFIG_DONT_SPECIALIZE_OPTIONAL_REFS

template<class T> class optional<T&> ;

template<class T> void swap ( optional<T&>& , optional<T&>& ) BOOST_NOEXCEPT;

#endif

} // namespace boost

#endif


/* optional_fwd.hpp
nqvRTxp/DeHH+sh87x69VxX2CX7vflmOQ7rYxRz/1TWLW/ANKNAm3PNS3WDaKvsofQskdqlzjBN94hjn78nw2OxI6StcxzXT8tmhpo2d5eTJ8hNOyDmWTXouu5B2QFT82PgLE87naQ0+BPPnIrRhJ1rfF3gjAY+3nbSAw7q9bbZQPtqsS5yn5IbqNZKM9csrqubG3jfjiO8VMT8der4dbbKA8lqyBqVBXj2zyF8mgKOOUK9QYeh8eXrkEfZYtRLuvkeS6Eq8+hFvj837LshCXfz44LL0pPR8t7LQmDmdNbXa/6dGjZd97uc8lv0GoeOc3/WbdV/se4ppUu+XYwUFP2TK7dyKqjI1FBxzRbbeXyN8aZvjd/crMGSxsK2kr5daM3D4rjhKb490v1OW4+lZHuupMnoeOkzp3VxlmWnN/rHH0HuUVoAe8jj1blMfddxrwvXnvpB1yuU6xX1LkcqZcOfu/YppX65bH27zgocT25zyiLtH19STCh9Wbdbavc2Jn3ub8x0llN5BtHFtc6J3b3Pus26U3svZ5kSbvM17UFp3tLqn2TVAfJuj/i1uczU/56xjprymu0zqJtKvzGhz8hzljyg55wB6L1JZokRTJKQO3CfZnRdc/9gcVVFl3u37BUrPsNfLdfTsEeSzD/l4+bM8P7XFcfV5eFmn++SnPzPd2vMzLAc5oDd91s9HYscU1pN55lmjUV/zvoqT65zfXx0lzyjc2q8Eda1OOo/SPL6HZcD1bMIpO3a7/YTbTa9B9slnkuBQUz5L41OtZ7cHFMGVViwcIfvvkYR6SlWCdv6NehrfFXHWS/JI1bcqrOZmwo89F9nP/qyh6m98G2UoPV9oPw+h5z7282B6Ps9+HkTPXezngfR8jv1cmNBOuk7x+s6E9arAX+OCfxXwa/lti82J7eSu7+h5ewfhP+HSXszLXD+Trua+P2fitrJ1nTrXuYlxmx0XTX8rj8rC8w5wCYfyjGunnAcVQ5Jjpi2CPK3dktBOspmqyqRQ8t2iVAdb7v+6Jdl3oJgX193bVn9j1b2dTNx5WcBN2MdbR+khZ7uZtOa+YUWZfc7/LUofI7qTd3bCt5GAaK6NjhJue9pz0b5AH1Cc8mkuhnz1/DyvazoW4top55pm9QYI7OfVmsY7ItTVXtJkiKRrmtcoj954xmke551l5+1xXeO8QWn5MX2Ny7ft83o9lR06N5a5I289T3+J+PSVdowp5buF0s53tI95jt0jhfmd5Zj1xRpbjiEr5nduqb/nZal90cR7Fzp8QTG8gBn3AvhB3+9Rpxyj0g5ZdMot0/J3rtthnBx4ULdnONSN2lMkbcuhRNsFEmS5tt3FlN6R2sqQm2bfEaxvGG0T/3449pBC7mwp+46OCMcCt8Zoh4Sv/Ta7ziNaHlclCq8ctM7xS7iONV1tdC6fPep0lK5QvGfTcby5nmO6+HupbyWcHs71nGu+pTALvslp8+LMS+NSZnpdlP8Y+e04v6HqpMevCmaNc8qF8c3BRsJpbV0vysRv0cJ67+d2ig9bxp2V+n5uymcVpfutmMzcYOuzHR6j+tt7PNX0bNqAlhIv3V4FlH6ZvRe1hXj/DvLyCs1PBRgzRQ/xmrZToVeeKge87WlF25L17D7iO571fp3PYfTrtyif4i9CR3mI9cVBofKYvpjeqqm17GPEZwivZc3yv+a6lt1O6fku5fiuPTcmfovWdwrr2hJ6pjEQv64lmXWsa7UcE26OxlUyR7jtNK4hh+aYPrpJsCQgns9O+ss18GOxMc2DuYQ4RMuaHdNE69z7d45pwk0YWyyzep32HqXPxmm9z319y/Tu8oPwcZn+aX5G78hnvg/yOORmySY=
*/