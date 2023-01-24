/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    unwrap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNWRAP_H
#define BOOST_HOF_GUARD_UNWRAP_H

#include <type_traits>
#include <functional>

namespace boost { namespace hof { namespace detail {

template <class T>
struct unwrap_reference
{
    typedef T type;
};
template <class T>
struct unwrap_reference<std::reference_wrapper<T>>
{
    typedef T& type;
};

}}} // namespace boost::hof

#endif

/* unwrap.hpp
B1TxhxsnEwWuUOUir+VfmgErO6PNb3yQJDP4AcaZWsu/nI2xD51Nr247mx2x6oFwVM4/Uc3XWUIG7da3K4Lq76LOHHVRG6Ph8ghe4E4YrIayOJLufN2mWv4qBKRlfMKxS1gJwG21uy3DqiFfDiAz9wMArhHVcigKc9eruwBLlCx1VcjoVPUXzU/B/aiP+BVUjcdsxo8RWoHlNr+As9UOgeSkEeRowGXIrwIshQvQ/ndu+IAvJcUa5cHSn5HweLonPXnnRiVywFuOWMJd0qB5ctGlg5Ccs8D7coGt5F2oxjtds7VPuub1idub71rarUvinKEvZ5rOOGbqjkEl55umu+29WrUYn6qIomrpO9DzGYutvyVCkkrK+XjkvsTTdlAIyCbc0VWiImsoIZwqiHviHjA7loSGz93R8s0lobr+2jZzwTIZiBXd/vx6+4/XZK8YzvHCFkfko23ayAq4+wl6dspWwF8TL5vsXeuJkDYIB3xP8xTl9eeGrDxwPXfqQoXumd5m4w9MGxEUeeFy2d1O8itqGk1k6uaFObQU9yy5TYXM46faTTlXnOqNXwq8HwCpCHfzBZGYH8wQmQdFtc3EtOGs+ZJjm+rCvWsppjok2GRf+IXk6BoKHbSGK1KeBrqp2DibsXzhgi3Myrvw5pze67jU4pf2Jdwz0Jb9NCcvxhrax6Hc01ZSXXRdsoKWO9u7og06P+PBvcmLrm52
*/