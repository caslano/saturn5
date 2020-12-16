
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_TAIL(set, i_, T) \
    typename BOOST_PP_CAT(set,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, T) \
        >::item_                           \
    /**/

#if i_ > 0
template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(set,i_)
    : s_item<
          BOOST_PP_CAT(T,BOOST_PP_DEC(i_))
        , AUX778076_SET_TAIL(set,BOOST_PP_DEC(i_),T)
        >
{
    typedef BOOST_PP_CAT(set,i_) type;
};
#endif

#   undef AUX778076_SET_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
Ah4PAsbcZ2X+D3HIc91psLFN3v9Fe7fL+j9jYVnLOQ/lZvB17GL4dwvbfR/xNuHYVoO9xjY+MOYdzWwTyhXkvrEFOS/BOdqO2GRP8l0oJ3sm7UccK3gcOoK8jZfv/xrzfy7zf4hNrpu+hX6iwQ/wRZ7TXYDdd2X9nzHHJT7P/IFy8l5qvtrWntzH32DML9+RLWosvIXrFjeWKfN6pY2FbuL7sgrGHPIN7ipgl3jcqGEsuIn70B3GIjJ/74Z/8s3EO+GL7E1wj7HoVPn+rzHnHta0hTH3PmaPgf2F+0FrY3ED5f3f2tBe3v8Fmyjv/4Jd5jGsK2J7jtvrgXzIOJRszCvXG32g8z7Wrx/qxjMbDJ/lPSU/tJJvAIyCpmnMxsK/UfL9D2gq+9pPNuaqwMfHVPi8nvvB29A0v8z/IR/y/Z65xhytuL1FiFe+07oMNh7lcqugc3Mutx7tOeX9X2OeOHn/F/7JPNI2aCXfFw+jPTkv7IMGD3O5w/BF3vM/jnw8Jvv/QXt55/s0fHmfy51Ffg/ysfqjsaCMG5fgi4xNvyNvsn9Y3jtMv76y/s9YprxvX8SYT/You8WYS/YNKGXMId9LKI/26rHPLtiVMba6Mb+8Y1fbWFTek6sPu7IffGNjEZlza2rMKeey+1FXrhMfgg35rmBLYx6ZV34CccieF23AOjNrZywscwodoV+8fP8XTM4V3Y25e3K8vYw5hjHzgcm+H31hV+ZBBqG911mX4caCHu5rL8KXKI8bY6DLMWYToMtq1nQSdC4g83/I5SLuV28h521k/s9Y4A32bw5YW9ZqIWzI3ixLUS4q7/+CbZDvfxh7axXXDUGDnezzx8ZcslbjM2ORIcx2Qit5b3YvdHmU4z2EfLRhG59D01Mc71dgdbnuKcS7h/P7PfST72SeRxzy7ORnaHBWvv9rLCR7SeWpY31DxrCCxkIlecwubMw7gXPuNBZZy3ZvBbtP1v8Zcx6U9X8oJ9ed1Yx5qvE59HYwWcddD+2lc3uNEIe8l3W3sUz5TuF9YDdxPh405jrF7T1qLLhd3v8FS+J+8JSxcCv5/q8x/2BZ/we778j8nzGfXLcnGotrzWPiC/CvOseRaiz6JMebAV2Wsd2ByJuDcz4MvsRx3b/Cxruy/g82ZN/f8cjHIc7Hq8YCJ2X/P2MhmbN8EyyF/ZuBvMnc4WxoKsfbAugi7ycHjUV2y/u/iDeNY1uLchv52P8QGshzv83wb4vM/9X513Wgf0d7slZtD5is3T9ozL9Nvv+BeGV+7UuUk/c/vkF78i2XM/DvMrNzqHufzP8ZczTn9n4z5nuS7TrqWmzybLuAscht8v6vscAW7gc3G3M8xTqXNBZexL6UNeaTdyQqGXOmyfyfMdd02f8PduUaqa6xoDwva2jMK/tR3GUsVJPtNgOT7242R1153viIMcckmf8z5unDsXkRm5c1fQb+3cX+dYAu8v3uLmCbuA8loO5F+f4vfJG9P1OM+b/j9tIRm+RjAPyTubShyLmsSRgJJrGNNhbpxXbHwRfZM+kV2OjP7U2BVvLe7HSUmyHzf8bcj7EGs6BLnHz/w1jm09zeEmi1lNtbDhuyxn8Nyu1gGxuMxf2V+/hHxlwfyP5/0GA3sx1g+v1ftLde5v9gtwHXPQpd6vBx+QW0T+K+9jV0ke94fmcsIDai8Fm+EXkRdeO5vV+NOeZwP/gTduVZZf56dlzO4fv4G425R8n7v8ai8o3XEqg7kn0pY8wrz8EqGouT9cBVjfnbsi41weR7aHVg44Ls/wdfZI67ibFAKrd3L8rJPmMeY+GS8v7vP9g71wCdqjWOv3Nxv73KXWpE9zAqpOuIRKWGyC0MUlQ=
*/