
#ifndef BOOST_MPL_VECTOR_VECTOR30_HPP_INCLUDED
#define BOOST_MPL_VECTOR_VECTOR30_HPP_INCLUDED

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/vector/vector20.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER vector30.hpp
#   include <boost/mpl/vector/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/typeof.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(21, 30, <boost/mpl/vector/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_VECTOR_VECTOR30_HPP_INCLUDED

/* vector30.hpp
z38sXxjEZVfHArlfLr5ZrR94nXGmKA8l+p2fJPP+P3K9EvRH/T2lI+vl5+Ya7zkl3JfMj9Tj7lOl/GCKeKGo1n6c5+FT5bdmJhrnll/YqN+pP9dwWXh/xzHPdfLdxktHu27K1cgR5tfJs5Z4r2H2d+7DPPGTuLIU/pP2zcNcdZl8FfqZ+YAv6G+xeOI17R94ivevCOM+ubvk5cQFnW7RLpWq3+6Qh+gq/paPKvT7xYIm+ehCz7PvlZFfQ/1X1PP7reKgd81nd//qxLmjxc2H26gn5qRqD5Uf7immv0rl6FJKnhNvPsJ7rKv68hP1143iFeLvPDdMP3qUcm2+fFaG7fbQ79nkfnOueV8eKnMi/XEPi79fvUU+kbgS864L65c8q59+TH/iJOPBfBfO3yM+/kLvj7IsHy6u85xl1xpX2y8u0G/oYn7dYc99zHhY0XrtYIn25GzXZ6z3ELykXf5CPcV68v/rEr0Xy3PpvXxV0feBF8qXfipOPkc87vuji/WTo++Rb9duM07mt9A4gzziVwny0kvV9wv06+fzHjyoduKIOEY5aIrux5X/Kn5duzPNv3ueu+KvURbqD040z2ey53KqPLX3RR78yTyilz0/tyW7fsaZ8uQlBqjPXwv0FPte7/zVt83D9OdXqA/kKbNYB+bfUd6W93heHqMHcTnqg/ysJMZxinLQrP+sXx3znoJC/F1K4ytlzicmTs1YJ78/UZ7on5T8nre/368dzn5HXvlLefWI94oZb7o8xOf5++W1J5k3LX4e+XP1/Vme63aJYZ6jvHkJ/TEv5JpxECehXjxatEc9/qP7Otl2HHdTjJJ7w8Ube+XvyAPk/bGuN3LH+OSVYs3+/solzvOP4kfjiFvWKAfePz/pes+Fcl4TfUe2z33inn6eD85VCuPkfeb/ln7dt8brJ/A8vKJ89wDzjrxftP4O8f/nnusy7X2aeQvw+fR/g3Zigbz0a/JSaz0XD0e/I0LJPZrGL/X3ajfH/d3WKH9VPb5B/vdH45N3Wa+9LfPcJjfK17ST/883Hgl/Sf8blDfzbXNamm+PPPD87cbd5SkL26rX/2Ieh3qpzjyxQ/pFGe7DEeW6UX++nnxx3hsizgrsbZz+v/Lcos/5ew/v7djn+kXnKJt4YtAO9oX5va58/TpROUHOyWtUzy9SLn8wn/uodmql9XPUb61dP+bPPFLFc/s9hw/Ify7zvVnmPZofuCWwE3Hm2UJebrz2/j3x/fvq9Q3mPVMyrygP2TJvo/rJskZ/aNl2Sr5D1N7u1m41ixtPeE7l2XKa9S+vCMcVW+v9oeAd5itPtmY477EufncS/S5VpCfGuy+d9F8PJPm7cX6f/kflZzr12Gv99xbGOa6QJ92hfWPcvKf8VF7v/F5Qfm72HNlfYfAddJx+yTOk/hXt1lp/f0W/LH+h83W8XcSvFRGP9qnz/dB5nBD/bHJ8nq/uTerxIuWf//P+28pXb+WevF32jbxm2nlMPvRz+cYs8yEj/NjT/JdLHPctnt+AN9mHHXrR/JSz1avgaPqFB6f9mL9vWap9d1yjz9ZfmCdu9PeKt3QwD3OE/gO4h/6+0f7LLx1cF5cnERc6vnXi6yXwCtSjN5kP54j2PEf9PEe5H8rvXeLfGSf17mtMfzItK6xP/p1xk5nm0yzUH5qnv8v+MF/uRaB+a1jfpVI5i/vdp3k2zUE+UQvmsUA/sMH4THBPww30f784MEk+K1N/vpd6dYB4MliPUD607wG+7k+einag6Fb1YKbyfDMlcWbx1qchDqmbJi9sPHs5/6ddSp6nZBwV3gMQ5VMF9bw/Mtv4+mz1lf5Itn/PSgvH35X/89xFwTlnHvyf+jw=
*/