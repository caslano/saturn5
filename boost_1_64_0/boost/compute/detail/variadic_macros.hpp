//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_VARIDAIC_MACROS_HPP
#define BOOST_COMPUTE_DETAIL_VARIDAIC_MACROS_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

#if BOOST_PP_VARIADICS == 1
#  include <boost/preprocessor/variadic/size.hpp>
#endif

#ifdef BOOST_PP_VARIADIC_SIZE
#  define BOOST_COMPUTE_PP_VARIADIC_SIZE BOOST_PP_VARIADIC_SIZE
#else
#  define BOOST_COMPUTE_PP_VARIADIC_SIZE(...) BOOST_COMPUTE_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#  define BOOST_COMPUTE_PP_VARIADIC_SIZE_I(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size
#endif

#define BOOST_COMPUTE_PP_TUPLE_SIZE(tuple) \
    BOOST_COMPUTE_PP_VARIADIC_SIZE tuple

#define BOOST_COMPUTE_PP_TUPLE_TO_SEQ(tuple) \
    BOOST_PP_TUPLE_TO_SEQ(BOOST_COMPUTE_PP_TUPLE_SIZE(tuple), tuple)

#endif // BOOST_COMPUTE_DETAIL_VARIDAIC_MACROS_HPP

/* variadic_macros.hpp
T07Sbvb1hbyHH+f72dQ87eELuRXm3HKdNJvOLZaD/m/9Xh50Fz9+NW5O5L5THX9fvxeIiUeK0ecb8/1d/Mb3V9T/AbswPuXNU4ov6qOcM/2lvMUaRXg4G/wPe9+NTdbQbYlf7UT2/D88igzsPVA6TezN0XNSv7rIYwvx5WTljza2naRPrxo/1BM+rbzx5m/ORb9n64+StfYWjzFO1LI56zKZfufkd4VpfMa6b+jewFheNsYmOquVy3820f7H6F2OGXS4Jv79upw5ymlyo73FXO8W97Wy1xPlPuZlSUSfhN4rkcuIT/kCm1qhLMcbkJa/Z9lF9iTHuulttVjhuvTvtHm6fj/GVsXm6Bb27jeB/P10d5A21huf2UHmKBzmt6gf8Y1Z2sK3g18694h+fa68c5Q7YN3eniQ5aw3lWfzvKT53Nns/0jifFgO66WERG7L+ED0oVtNlKaPcV+Qk4nZ4oHYbE1L2WkknNuZf1lbpNZszpsivEny2cCBZHalPM8lFXM9qU3KuGPEen7F3VnIWPzyRvKxzZCrJlB+kNnfvSdo+Y4K4Tv8/NH6YnxT30nZzoKCJXC8krxQZ/Jg9yYfKH/KZx8bTOX0fa43RumVmsbzgEGW8Z6ztUE+PuPkQGU1y3wnacYtcyBwsu734cgjdKic9Xv+NqYlHlHEfO2BTpWb+ujf/zcqR2+nwUdfzlfLxZPQDsjPWZcz/pjuXqTfW/3wEP+FXkb5vRKZJdqK/0Twx/XUy2Zvt70gG9hMo2Otl8QPKnCWX2JvfBKPEJf62pzzWOkee30bT6OFZshrPt3rJ4QK2fzmZNar3L+S/nXHthv+/X19mt4l92HsTn7JXfOI2seEFsthvgvutRY2cQhfV7Nm4cKEy2tjV8WxtprLNffNssrijOLktOR1sDHg8xl8dv5StuS6/PXlfbHx7RNub2MIKMrfWU37ZeOd4A90XDxMvXzLH+Qk77algD2T7Bl+6gmz+rb71xjRxrUCG0WX0O5t8d6Rjaw/Bd/Kr2+LWQel6nHh7prb6DSj4nJ800Nv+4s3OfMD8OWOumN+xmj7NCegmtZI8DmEXO8lNd3F857i5nfJ+Iqb/UT7lfMKcrbyDttkfPTUUWm+mp6nG4CvZtvZnrS+XjIvFj+Q7h1iTWESG19DDt2yFTady+nafubG/i+yqvJW49IbcJO7cW3Rxh/45V54gFj1RKZ5uZP1S+SeKfVfRq3MlJCaOsv8RnTie9r1c7fNbZXqeKn0RG5eD5xwLjxb/nU9u0IYf8JEt6IDcoxPEG7rJuyYnP8g+Z43CdZmzjScHiJv+LiD0PTxN/8k6ezCdH81er9FXsijswR9PDNmfnGpktXgiJllfCfhC8hi6NP423ku2xrByLR1OiNtCS6wcw64/4wOeY8/Mp6c+MfJwdv68vPxuOgn061zj8o+t2Ub6Otnvqz9iHwl6PY4tI+9/JGV283fSPHOVcsr0QLYJY3j0PLnfP9YaIBu8Wvn36/8X5k098p/DrN3Yeztqsi7ygBh0pXY+5zcrdp5LW//+LR/6moyVnf2DutvJ5HZ+Kn6mHlVm5/frXTHt5MtPssNtxIvzyM86kGfR7TtG7ifzzW3dcx/Zy7sSM0eLZ/xoAVleqJ5x/Pgfyutj97eIK/LD7PZj5VPk8LpyPgr9HsI/xJDE4u/nXH5nc01uJzYvnkWfu7dKWd53zlzORsXrkj2lAjlrQP+pNH8TH7Jltr7UfbPUd5b2ytuT7L7IxvJx48rO7rMeWrqeXq4l07fZwBmjzdHZ6L7GwbeV5fem8DayrzEWOxa8IEbLUZLOhY3GzaRzj5oHXWQc4cvZP4prb9HfO/q2wr1P+U4=
*/