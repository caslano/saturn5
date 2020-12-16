//
// Copyright 2010 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <csetjmp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4324) //structure was padded due to __declspec(align())
#endif

class jpeg_io_base
{

protected:

    jpeg_error_mgr _jerr;
    jmp_buf        _mark;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* base.hpp
M28MauOvAF3TB6wVY1AnyTpDPjghY+4rSfYkS7WfSrLvDuh3H1Hjfg/PIUhfSe5BfiX7ECfrsUB+4vPqfn5U1KNHa4qqx4FwqT1UvN5FUvF5dh0L5v53I8kJlesLb97XKWEPmjYdAs7fzO31fB40c142ATF8Fnq06J+PUbI1+b1dtYF3IHwedLWy3kiiv20g1t+7IYrT1Q09R/T0HtVj+kkTVyHjBrr7Y5FNA5Ee+96Rja+U8e5lYIHi0pgicXrb+vvwAlprX3ekPRaN9Pf19vRHzN2rqXa+Yfg7FrzlcMPXvTgas4U/aomEoNDg70kf/xth+ocn1ZCtIT+woR+3pZErXP5TOQJxqLix7t61DpUnCM+FcHmCcbp6LMzSqSqZH17N7+roirS78quegC9gW0l2QD41JJ/NJJ/t5k583M6wjB+zQo5FFRgJqUHOLLNopLW9Y0NPm0P1fFQU/kQMgOTQO9AZiZqwzXsK5b0FebMNhHlm840enZVu3iUi3bxp3uTuFdlpDoWRPzY3IF+9d7SMzpqHuJ8MtMvY4INQm0iI/mo4XPSX1sEyMMaZfvH3RaLru+CnZGOE5DIWx77f1zbgPD0KuVSSXEbGyGU82iSrSSRAkWw5qmjfsMlxStjkpQdzmRjuN5oL8oVEjo1RNbw4Bz6ex+oK85v7kW1h/zp9lPqQVNhxa4z68gzhrSvNTw69VcpknctgnGF7lxJxVH9ZwUtOzCHyqn8rhPGp/m078bZDzEOyqjy71HxpN6U5kfA6SpaHmDW7cUneYAuK4P3Lk1Xep6i8T6W89xDeitJ5mzmuzFbCuE63CXmdoeR1Zth86m1xyv8sLnvJu5WpdPr4QkbtLgbEcD2eLurxXMHXeYqv88P4FF8XEF8Xino8XcnyYiXLvZTm3UKvTxY8XCp4eI/i4b1hfIqH9xG9y8L+N3ayMxBt/Tq5D28bWIFh9Mg2v93N8HSe9pA9nyhXhMuzNVvn2TNYWjmn+D4S3OGLvjMk/NwOgvZMYZf2/rBddzre3vOVY9aW8dwuMAnvZO4k0Q+idxbHbRe6gauWTXqg6vAqkvnF1Ld8iGR+9cR9C4yXkoNBOcsonf+lKv+PUv6nUP4fo/yvUXgppWsfJ7zrhH7mVJrrKc0uov1JSnND2L8W2lNHe+SOi4+wnY/eSPgfUPvrQfYN8yntfM/PktevBKSd7fnDp7SZ6eRPV619blbtYc5MlgHTkefBa2nP9/PThc00ldXgfTHMeDb8eMhP50imI2yWRfgUFb9XhVdNZ3qcXr1Hx2eZHI9yfS0sZCfona3oP6f43Xc6x3NdQp6B6+P7xfr9OYqbRem/7fVboq4uF2WR9fwFtTZ/MOyPR5l88d9X8Y+rddkPwpL3IL/5sGlVON+U+RDOjyVOiXPqnyheUJ/+9wsUjWsD8vmFwjmYcCS/j6l8VimZPa5oBK0Ff61o1Cq7+9+q+EqVx+9UHvcGlOX3CufuAJw/qnzeqvL5k4qfoeKfVvENKv5Z2a9RG5f4Z6s6+qui95zSp+dV/A6V/h8Bskc78pX5RYHjhP3+9g4knH9Rm7mC2ow8p9R9YcVsxxd/muJ5CuLtXG2GsDed7rvrQXuU/DFP8q7H1Nlu2ODKd7xmK9+6yN/ePymoun41pa+Zzen9+dd4H72hpu6a7EfpH+f8SQ7q7KNaxUPnfDZl/SF/eK/CR71xvJUV+TP02bLM1vxNccLEXy/T530ekSYobbUzh+uQbUxEWfBmKNHeK2gLeQfq0DxKc5EqL86Bubw8rih5yXCdw+mZZ8kT8DkseZoSwNPrKU2IZSx0WYSPVDxPVeGzRVjKDbY2Prk1S55K2AG0EE/PsR4=
*/