/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP
#define BOOST_MULTI_INDEX_DETAIL_IS_INDEX_LIST_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/empty.hpp>
#include <boost/mpl/is_sequence.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
struct is_index_list
{
  BOOST_STATIC_CONSTANT(bool,mpl_sequence=mpl::is_sequence<T>::value);
  BOOST_STATIC_CONSTANT(bool,non_empty=!mpl::empty<T>::value);
  BOOST_STATIC_CONSTANT(bool,value=mpl_sequence&&non_empty);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* is_index_list.hpp
BzxTfN3YsdMUdSuopOMjQW2LG+sDDm1u5QDLt/SjjhLYi3RFvP9zh6su7qVW493GbHtC4fjK/bwofonQF05HRGZh+0e1lcBbJAeVGBdg02l3KuokGatBn99GHFpa/MAhGW916BfELLzr6tYSGEs4bITxV97bnzwetobqTPVtLsnDEl9wSCRdelozC68/6T4lECccJmJMhZPvuFtRJ0OQbgZB3RlxmBH1AwfXmgKzsO2xe5bAioQDXvb78eF77E8thdyVKOMKCodeX3Boci8PzMLoF9uUsI8YLqYz75iUp6hToYcu1IsHSH92P0+IXw1dcYfb/czCg0Pv4mJYmKVwwM2ajX7K+1VRt4GeGeRTu63Sm5aOcGyDpEo2O11HMAsLh696iyFB8rApjoW7nnWgom4LT5FkVA0hvWGcP/IwwTkME2zb/JPF8BPJAm5gbtN74/104gDeEDZHHe9zVUzZz4+xoSHV7XpsYBaG7vBgMaxDsrA52mArZ2+uqNvBEbS2jg8hXdofWUglHO5sMwsPDiPvK+a5Ygvx+VL7alMVdXtYsgKNDTlKHhb5Iw/u5wpmYeBwW1oetsRTi6dU0VntHeDSoWRvG0LnV1t9wcGxuYlZ2PtVtxTjGkLisBVaXGO94xW1BvIzyQ5NuuQCn3Co6HaOA7Kw15jXFcNngxQOQfH3/YdlH6ao0+C8LPKrpnFydJsvOIgKusZBFO89u3hiMQSpX0zCXcthr+2pqDtCLi7CkbY6zZnjfRkn2xw6j1ocWJ8+thhGEQa4b3fVojrSFnaCKXSPz5W5NFf4g0HE/ZyJLDz2+GOK+Zz7ZOucey3MyKAxUnwOxbzubZBYSacH3ZmF1xdM4KBtsVMsW+zOMDaL9rFpjJzvz9gQjjh0lWQWXrv80cVwPeEwFT3Krzy8TVF3ge+MswaIQ0m7PzhUOIehwrbJdhfDVMJgG1w/nXHBK6qV02EJ2Ry+Won8RTf0ZWxoanfo0sAsvLLQVoxzgMRhW4xo1P4OUevgtALSG/RelT84hFLOx0hk4bG97FUMr9HZ7mo82331MzMVdVfIG0L69Io0X5a5xiHlet+WGVhrq12K2Zd8O/E5Ys/8uxR1NwjQGhODhMj50gcM3CrSsnzbPj+tGO4jGdgeY55/Nvlc1cLdoZLmhwXah7zcffvd7lNx+emxYGoxjKE1xA54J8i223aQNR666f335qi1VI/zeaFxDgY3dWmGZQ6mnWViMdxNfaBGfD45K+8c1co9YOFK5Ce9IvUB5zIgahiOutSUmIFlbxtXDB2EwTSMIX7iPNqf2VPe5afvVEb7Q3BrF3HfqIqzWxJt8VisrX52vCE809VhCi8XO+bH0GLYu0RhsSPuVF7w9LuqtXvBlZnUO8QnwpK7u8OzRmYtGx2ECRuQjS0b+wo8ckg2dhKfj8/58QxFrYe8jHTGXNQhXZ5b7nR1iAIL9uxPrVQMd1Cba8Xnqe9f0KSoe0MbyQDaWPJQr/zDaZvFPxG8KupoXjDKt3zaMsSYSPPCzuLvK/KXXapauA9ci7oR5hEvHF16ep4vdzcmqvqpzE4hoMze/ZgPimBtkgO8B/adY5dtoagNgE7ich9CjBXiH8xY5DCuh6ykO9dfLt7ryyTar+0I0y07wr4cMbU7g/rB287lwJkNgYv3xgt8qQgS1A/q8G6wvVdqVdQQzCXfzvkrqvefW+pwHBDbIg3hRvXhSAYsFl57Um8R3E447Irhwd69mOxqjVCVQ3tRObRWqnCoI6WS4l+DuHwn2iz8kVOOzM39cmE7661FQvoVFugEv+Hum/2oWtsE3xWRHUGfmXGPhbiVRdbU1TZtv1x4D+LaIt6Twgsjp84=
*/