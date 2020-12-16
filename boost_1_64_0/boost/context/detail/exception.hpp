
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCEPTION_H
#define BOOST_CONTEXT_DETAIL_EXCEPTION_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/fcontext.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

struct forced_unwind {
    fcontext_t  fctx{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool        caught{ false };
#endif

    forced_unwind() = default;

    forced_unwind( fcontext_t fctx_) :
        fctx( fctx_) {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_EXCEPTION_H

/* exception.hpp
Q1sr65bW5/6Vsdd2HvrAgnLvwFbmz/Xlb6QvLQ/K5zzh4cEFkoY6tYz6AJbvP4ht/qPUcYNXyX6M0NZUakQNSNz78m7mad+erwHbkB4J6CWUnm9iSrahtYxtWGJsw58WuP7naWVpE3iFzAMeiuiA1BXIGUHlz91OsyzfZTJj7mEz5h6R9MM65swYe9iMsUdN+afLfOzvZj6xGNYt7JrEY9K//4yUKb+e+m8p87iUeWd4zeh8iTWj60UbMpMaf0LXinZ1Du3pHTsvldqO8GqGe6X0HFpryhQDWkcQrfRkkTROy7j6dw2kSNajADva4U3QBhpn5L026XOvEec8yYHzBwa7NgzSI+fcaZAuu55WSO9I0b1Zxpe/CfdKar98K9CusV/fqDpMpk1hrV4ylctNZjBW5/HejkJR2jCjUc/2J10lLvhCCb6U9ydTQQ7QWO7q3u6PlbPF1s2ENp/Fujq6zY01jINroPJtwbsBo7vWZ6hvCqlBqhXugYzyYqBmOF70vNphWq9/56l77fquQNKaKnderTw+693sRllbiitboV+1/OFS/uTQfejCziQpDMZlneVgRQek9UZp15HYrjh9KHd/6QBk73icKzzq2cDFvr31YH2F1iGqHU/VT2qcTmxMv5ah0QuLNDvNjexUDVqxom2lPy90+oX2qbYxbF/qKL0oxE9xQuU1m+Uyxvq4SviaPy2+tpEyu3PPqUlfqX1+tF5cizzW8HeE4S/RKLEyAzzua52XLhC42tRGxx/90KY2CY1mwT37IGQ8UshNrFhx2mnO7h9C+WWuvLb16MbwXsaiRj3nGLXv0TXQau94adcJ0i4ta+28rhdi2SdL2SV+Wf774+YOdfx6FZ2zk7KnQNkPzNeyONeP+itPk7JLG6P41TVR/DbBP13w0f+87zhdYwnS/KaMiUHi8nHuvlxoPqMxuoYzS/dVhf+6GP/pLCn/LGwD1xOPf47gr4Q21Jn7Oqswz/DZiToufGU9s+chuKuhT044BvlTfeLyuqbC/K2Tsuc2xuOr/BR/g+D3CH4Q46j83mqflHl2hTJaj5YZkDKDUkbt1Ku5v2VOIOk5njs7ly3d/d3UaNdCCT+5I7VDjTSA1J9T+VbL2EFd20z0Yn3FadLms/umHx3tRaYfnys24dUas0LeWV0M8T6TjcH7UXwmQM9nSHpI8m+StMp3JaQRv9UL7tWuExmPsPz8WDqjja5sofR3nzfGf6fo7wvM3OxeeON+hZxzGoO++C3dMRranmobxps8AFJ5IV+zDJ9HU1rvOTqYJzEn9OCVwqvcvU0FEj8MZymPDU2Kn6WwmRA7aLyR15ZTQ2NaWOIez/Pje4+mkjJpDcrX+HAmgnRrvTS5irnQmbA00a8jfeXTcaM+7Fq3Lyjvsml6Kfl+uXyGrkuS7ydxhi4EWa4syVLmWiJNBFac50yzL5zuTqDuyjmLHeY7O0lptbk7zHc8q2nBPWmezFMFV2Mc47pwXukHNOL9sAOQg9OjnTB+sD1FL8zjbr89NTvB39iLchDen2/adnEjtk2/ayYuIsF1LOrYE9mxLHBt/kWEq/W5sX+s5kt9LxFax0o9rcYOXG3up7TCOH85jPNP8jy8UPp7iYzz77r3yMw4z8aM88tBN3dLn+SjupVH3frp/2EcF+aXH8dHlxnHTzLjWO1BjYxZTSdwzMrd5FeCXFpVLnG6mp/+mK0kVx2zr44Zs68xY/YKGLOch3fOQI9fU2aMXqn0tEy5MXoA7Xa6+sbGQFfdGHwjjME3Y7uEt6vMGHwL8l5mDL5Nxk0Rv4+UX4yMOx5z/NN8jhMpdd4NsZHwLmQn6VmPzq0YNgrr74VMNnRufJQuheI=
*/