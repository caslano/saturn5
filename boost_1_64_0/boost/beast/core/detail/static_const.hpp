//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_CONST_HPP
#define BOOST_BEAST_DETAIL_STATIC_CONST_HPP

/*  This is a derivative work, original copyright:

    Copyright Eric Niebler 2013-present

    Use, modification and distribution is subject to the
    Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    Project home: https://github.com/ericniebler/range-v3
*/

namespace boost {
namespace beast {
namespace detail {

template<typename T>
struct static_const
{
    static constexpr T value {};
};

template<typename T>
constexpr T static_const<T>::value;

#define BOOST_BEAST_INLINE_VARIABLE(name, type) \
    namespace \
    { \
        constexpr auto& name = \
            ::boost::beast::detail::static_const<type>::value; \
    }

} // detail
} // beast
} // boost

#endif

/* static_const.hpp
ve1bTx2FYF1zCOS7HeVruNOS8W0OHNflYYeuY9oo7dORz3FRl6NsPHdW/KegTHbnjud2t38G1zVa66iovOVn8JuN5mcw0zs9gxlvfga/0dj6M/jVRtMzmHm09AyubzQ9g4W+9WdwXWPbn8G7bfJ/Bl+66d/3DL57k/0zeHqY/biV+51v22jbM3jBd7ZjF/NzHrsuRLx57Hrpu44bu87/zv4Z7OY59tPYL0ayX6jvrbzTvLVjv0gV+u3ZL5je0i+Qg+4XjDf1i4Hi78N+QXqffpEiNMnsF8zD0i+qFlSa+kWSxCewX3jpk9jWSc97mPoG6NreN04T2tl4Sm+v+8aXErY/+sawbdw3ICNL32CYbd8Ar0Jr7hvkn22ky2bdP6xn5ETY73Wq3ezXRlrd53TnZtt9TszLuW+8v9naN+J/6Li+sXGzfd+I4S7ek7jP6Vi4H5A26wcL3zS/7M8z2wjpK7HWGsW2yvZNmhxNk4/RdEdT+zTXpbR50h0GeynbW9s9aWZqmnKsBce22tZBa2nrEZBnkLK20cx2ypRtlO3Op42qrWujF0p5QePTRsOj7Ntoo21dtfzuGbTFto0yL+c2OnKLtY2Wbum4Njpii/27Z2ZP+/F75RZbvmlx3Hkcv3+LeRxnPpZxvAIPX47jjDeP4/eKn+O4pkcFmsbxu7ZYxnHmkeLbN/Q4XrfFMo6TPsm3n/i2bdC1fRxP+NF/HD/yx84ax0WmPuM45ab7iH9/KvDtT2wr50m5kc5n32ZmjH0fSW9qqa203FcmNdn2Febp3FcOabL2lRubOq6vLG3y9pXA/kS7/Yn2+/K2/b5F1yIjvNt9R4//bXnUGbmnXbVfQ+8Hb/jn7VvsyP2JJd75TuqeNeb9aLTHlgp8lPujnqS9yqeA1bTDdjRwLfBL2mHbHnmsAQ4DPg7MAD6n93Fxro/6TI3PPq6buY/rVt73Tu53ugs4nnbldgPez31b99BeyL3AHNqZm8X4POBt3KdWx/1x97MctYrzXMAjyXeU7I/ERbuW/YGJtN+XQnt6A4BLaceygvZSjwMOAj5C/zr636T/c/qjXR5/MnAwcDj9u9I/BdgPWMxwyotzSvbyepHyeonyeo3yep3yeoPyepvyWk95baC83qS83qa86imvVyivtymvOD1fAwyScsj+t3Cgor3HeOAHwALaNa0BfgtcCdwEvAi4GXgV8EfuD2yi/b6fuB+wj8tjx+9X2mn5DRiEe/zO/YBGfCQwFJhGu6XTgWHAvRk/DxgBXAiMAi4H9gQeD4wBnka6C4BxwCuA8cBrGH4bEN24ph74FfBVhr8H/BB+Bf4/BoYA+5jsN9Y1Ovejy1g/l7MfXc1+dA370Sr2o+vYj65nP7qC/aiW/egG3Y+orzu0i1PYLk7jfVeyXZzNdnEO28WFbBfnsl2cx3ZxPnAW4/OAp7NdnMl2gXDyTX0UMM2G7514/0zgHtz/uTf3fx4C3I37KyeS70nA7mK72FO/uwBHAidrvqmLAZfb8D2AfA8Ewqmh3DeZxn2gw7gPNIP8D+c+0BGUQzrrJ4P8D+I+0FSWM0PzTd2E+pcv3/txH+g8YAown3IooHwLaTdyEXBf7n8GrdofeBTwAOCxjCfffL+353sa+c4m33uR7xnke2/yPYd855LvmeR7FvmeQ773IN855HuOie+VW5zr+wjyeSTru4b1fSzr+zjmdwLr+0TW91Gs72NY3yeZ+E5vcuZ7MfkuJd/l5Hsp+XaT72ryfQj5riDfleS7mnwfRL7LgIczvDawvzawv7YT99fegr2zL8A1wkVeCTsqcPPhjoKrhXsIrgFO1cKWCtz02sBe28AVuAJX4ApcgStwBa4=
*/