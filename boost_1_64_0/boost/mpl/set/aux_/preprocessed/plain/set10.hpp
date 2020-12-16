
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set/set10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0
    >
struct set1
    : s_item<
          T0
        , typename set0<  >::item_
        >
{
    typedef set1 type;
};

template<
      typename T0, typename T1
    >
struct set2
    : s_item<
          T1
        , typename set1<T0>::item_
        >
{
    typedef set2 type;
};

template<
      typename T0, typename T1, typename T2
    >
struct set3
    : s_item<
          T2
        , typename set2< T0,T1 >::item_
        >
{
    typedef set3 type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct set4
    : s_item<
          T3
        , typename set3< T0,T1,T2 >::item_
        >
{
    typedef set4 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct set5
    : s_item<
          T4
        , typename set4< T0,T1,T2,T3 >::item_
        >
{
    typedef set5 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct set6
    : s_item<
          T5
        , typename set5< T0,T1,T2,T3,T4 >::item_
        >
{
    typedef set6 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct set7
    : s_item<
          T6
        , typename set6< T0,T1,T2,T3,T4,T5 >::item_
        >
{
    typedef set7 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct set8
    : s_item<
          T7
        , typename set7< T0,T1,T2,T3,T4,T5,T6 >::item_
        >
{
    typedef set8 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct set9
    : s_item<
          T8
        , typename set8< T0,T1,T2,T3,T4,T5,T6,T7 >::item_
        >
{
    typedef set9 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct set10
    : s_item<
          T9
        , typename set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::item_
        >
{
    typedef set10 type;
};

}}

/* set10.hpp
OQydZV7LKHTpK9//Uk7GOx8xFqsn43/4L0fW/0M/mQ83DR/09nnwDH6WcZpcYtRc9v+gPenXXjSWKc+hS9ClwPtgKTk5wbNV2CF9xJvIHejlvk0s5Xl6E76S/US2wKr6uh/SnowZ7SAeA33MP0dnOQd3GcuW92V7KLdOxv/waVvPCtFF1uM5gA9k/ezD+KCsz7W/KCfvnVOvYa6kL1fKWES+fS1vLDbZ63yysWw5V6sZK5R3IrWMpcl+/qcbK5B3GGchV/YqO99YfJW3raGxHHl+a2ws8wNf7lLKydz4DGO5Mv58Nayc98G12CbvlG5Ev8e83PbG0mWeamd0kXcT3dGlhez/QXvJnvWl3L0y/89YVPLlbvx3QNb/I0ayTu9IY1nny/6/xGhT1LGHKSfPOI8TN/FVDvmS7f08lXJbvc5PY9szvtxs6j5U1rG5+LnQ27bAWN5pvt9dTIzkeeZVfF9Xxv9gf5Z27A3slfUj3qKczD3aiAzxwXuUk3uBrdg2zOvyMUzWsfmMWC72cguIkZwfu6m70NvxAz5oL+N/xjLEp78St16e/U658r69o+SQPLOntDK5O2o4VtJYnrw/L2cs/T0ft5OMZZzn+6GqxrLlO4dTaE/mQdU2Fvvc63Kmsfg5Xu55xjJlHch0YzmyH2QjY7lv+HPwEmNp//C6XGksS97Rt6Bcsj9XW1Pud1/3BuxtIvt/YIc853WCSd/ZDTsu8nV7ITfLl7uduuVk/w+Y3IcNgsneqEPRb64/V+/DV3EvNwaTOZVj8b3MG36Mcl/5/JtEuVFelyfxfZ6XMQPbBnv9njWWv8b3sc/hlxe8jPm0J+vhLcLeMzx7hRjJXM4VyC1f2bHV5KSsm7yW9uRZd4Oxgrre95uRUc33Q3Fj0TTPtsNkfepPaU/W1P4K/Xr6ct8aiwzzbK+x9EU+n3/G97Iu537KyTXvkLHCXbL/B36W8bXk1lbu3iTHShjLkXHlssZyr5f5f9SVd4FVjGU9IPP/jOV19j5NM5Yv75TOMJa5Tdb/Q4b0uw2MxR7w8b3IWIHcAzc1lnGBz9MrjMVl/c7mtCf3xa3Qb7bPlzbYJmMZ7YylybvPjvhP1ni7Bf+95fO+J6yB1/k2ZOj6f8ai0g9lG8uu4fW7B7nSH4wwlr7G130ANki+/8UOGTscZyzSx8doIjrHZf9f4vuX98F07LjGs1mwM2X8D51zfE6+QCz3el+9RIzkGeJl5N7p2XLqyvXydWTIPqP5sEtl/w/0u0XW/8Nemff6ATk5MerYNvLqgG9vJ/kn939fYsdiz77B94/7WH6PXJlz8hNxy/fsF+xo4n1wkLjJegBH0E9yI+las2OD90txY+m5npWhnMx5jxrLl+fBysayZZ5HDWMZz/v4noaMVd6ndWFjvB3nIEOe6eobi97j5V4IO1f2/zAWk37ocmOZxbxfrjKWVdPn+DXGcmRtr+sp95mPW1tjaSU8u9lYRNYj62osPsnrl4Vf1vpc60O5T/25egdM1hofSDzqeZ2HwOQ8Gg5bIuN/sDdl/h/+k2ecR40VyL3KBHwgsXzCWN4zvu5T+FnWXZiJr2aUcGwOvpLrzPPYO0vm/5EbYlseTMb0l6FfGRn/o5ysEb8G2yQ31sFkDOAd9JM1IN4nbjL28BHlXvc+/cRYdgVf7gtsezjJsa/x/RbZ/4O6rb1tP8JKeRn70EWeZ34zlpvkr41/ILe6j2XkOouHyChmLL7Et1cadq6M/xlL3+L78UqU2+nPmerGMsXeU6k7Qsb/jEVGyv6/1JVviOoZi80t69gFxvKXeL80MZYl4+2XUbeBZ81gD3n9WtJeL++X6/CVrPWcaSxX9pXpgA8=
*/