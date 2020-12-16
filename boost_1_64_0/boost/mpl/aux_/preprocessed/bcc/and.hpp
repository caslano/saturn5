
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
S7PZBXas1fNxTsvvQmj/t/z7fBjb93q057UFOg4mZal8WKf9+/xZw8dZbH/08cwHfVwC+3Sf5yNt+LiG8H1aGS34dmvw5+sDVTaHbDGY5EPFO2z4WPZtfz7WYLs94s9HDEzypvJxyfCRRvgezX4K2ws7A2Be3vaA3W25y+aQ7aed8tX2ddZj+j1s5O3Et6Vu+cv5s2C3eCAZ450x9mEBdIFM6orajytgel3Zg/RvoR3ned9pWC9Zf1i+sPlnJwnTWgaGtHz1bg3Y9FKmT/99YHr6877hpb8I2vodo65i+6n9+jlb32ZYDdqMJQ3ajD3f4HnB83y3sa/7sb32fv5z8CCYOi/nqGPEfa2VKfzO1cri2Hf8x3Ap2hOpo7fQj6GUoXa+DXzTX79Of+f/o43/f1hk/n4k3r9+MJzYNBx1mdxQqr1awHk991WfPt5qUgzjWUHKTyQ6nOAN5rK9nUMm9bdDOC3i+5OXjDc0GB2OPlrFE6tiNTlvm+8vcLvOC/3ASf/guiHZrow6vnmYIh52Nf/eiB5vU9R9OoZ/2JLdf29bs43Heh6XYIe+Fs6/vOJjPdOYndfjDQ3GpYgnZcS0fJT37L1t/lEyz55l6Y21+Hq4j/FRHy/eY4Y2RHtZDvQ9XpQZam/b/XOfQNxmb147jpi3Q42Iq/dBMFnj/ur7WclkHfePAfM+Im5Ycls77v5Dxfo2uH4gKnuolVda/hiSej8nPZHC6y0Vf3k63rru1V9mvfi0MY+/f/qONj3heH9EDNW7R/Imnnp3pvrLQqY9Bp08DIEc/4yjtx/R4cf0R6IDQ5Hr99lSTqn6z0gqp/fX0h3ZkSouFDmjRN/Vl4VkqNc+4rDMjTAZqpqs+k31aYHk7hNr2bSM/4S5WZA/cDmSxluD8hlw1gw9DBGcesZp+ppvcvWQl2efl8/p0z6b9uxxd8OxRyZQ3h7jCc29qefcI4/zqI6M25V2d69V/l33mUqlhGFmwW4X5t4PsuwyM46VYhkftreksk5UK6vFPxLoD5fK3TRcUpJZB+wKeR57K0T2X3alGqo9N60lN2rjZrGtJRBQNsWKVd0hS+2k4pb2cKIjucNsbLbgxatFsOAvScaT3JJpPWXnTn1ZeALKa0stpOsGcCdrzmQiC+k4FmJ6DQ7ToG0RkVPJqg/5O6WsTnwm28tXtdzAG4WhNDUL2rCdRunjGWD8krvnAqYiSvyIv8ckC9OYr67Wx4DfvlIsWnz12Zu7UH8fSX8WQvuL5VbtWiQPSFT/ytINjs9q5zoOunayc4o8JNeWh1pJ72XTh4hxiMnddr6yG8C3OCqZh1r3S992/m3nBwL3cyz835dIxB6C5G47/98eN9bylfFNLsWG5NrnPtf9cPwucy8pD79xf/5ZHTkD5be7zV2XpqSrq9MbP/6gNXgTfk/gdw5+T+N3Ln7P4/cW+L2E31vi9xp+xX7BD137hfgV+74v3KPKLfI28rX4nSv7g98WyQd+xd8UfsXfK/Bb7WPiNzDD4kxU7zqMTeR4bidz8niHneYR0t6Pzqlai+dYc0kg1l2xlArKOsUnSp7iAnU15gmq6p3vJQ6coXi4G1dCNCy2+x6vvhlI4p31XNZ9VVnuzDBaALXXxtmUVtuyI1WrobEhhPhmzLVGpY8nB/KUL07a65CQ+3Dy/R7k+L4p2ftQVDuXS8/PqvUTH2pV+XwEuPdz3e+WixGD9DB0dbQghuG+BJ5k53upDFm6aXDD4NBjBx/I9l891mTJVZ15sbDwbxLiZMlNWEvbpu6Xm0IU+hYDxiu6+aL3ujDpZ9JrIEBsuW83WHV9TobXBfj+0LSeUebVH+72qJBxR+WbxsreM3UbDpc=
*/