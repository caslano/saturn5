//
// detail/signal_init.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <csignal>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <int Signal = SIGPIPE>
class signal_init
{
public:
  // Constructor.
  signal_init()
  {
    std::signal(Signal, SIG_IGN);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP

/* signal_init.hpp
85F+7+P32/r9TqJzP+2WgO4G0n1HxqwZvzcGdIZzUqD6WPhdeBxcCrvAO+FJ8HI4E14B58Jl8DtwOfwpXAlXmzjCtfDncB28Ad4B18BfwhvhBngTvAfeDE0Y1sI/yJ/98A74T/nfMEjbHpp4YFf31ZBOikcTY1/xIEuqO8DjYCfYGfaGXeE42B2WwZ5wOewNb4B94K2wPyQ/aW064e0H79bzR+DxcCscCPfCE+Hf4SDYwOxnNv7DIcZ/eBLU/cC6d8V+8wl35P3Ak3U/8BTYEE6FmXAaNOXxDMVrmtzLde8zIU5yrw4cLvfOlnvTYSN4jtzLh22kPxbOgMeZ53J3DmqH3L1C7to5W7m7EbmWcBNsBzfLncdgD91jPEL6XPgwnAEfgRfDR+FCYy7/sgO6xwI2l3+JsKP8G6p4nKp4DJO9PFOmZK9C9lLhONkbjZzhabCJ9Mb9sbCbkYM58HQ4FY6H58EJcr9L6N4F3QuRqzPE2qjOeVz59KTyZ7vi/SwcC38HJ8A/GPdlPl/ml8j8UpkvlfmLMn9N5n+Q+V6ZJwcd87SgY54RdMybwxfhAPgSHAxfhifLfLjMi2V+vszLZF4l8w9lflDmX8g8MYG2GewAd8Pp8HWTrwmYK71yArqHAS5RfiTD/sqPP6nc7IVd4ZtwFvwLLILvyJ1lofsN7F0JqttMH0zpfgC51vAz3Zv9ue7N/gKOgV8q3RPpjFwEU+BymAV/DDvAG+y3w6mfusJNsBt8EHaHW2AqfBKmwV0wHb4OG8E/w8ZwH2wKP4LN4D9gc/hP2Dro1AdJsC3sA9vDvrAb7Ad7w/7wFHg8HAo7wYmwM5wM68OzYUN4DmwBi2FLeC4cCOfCE2E5HAQvhIPhQjgEroEj4H1wJHwKjoK/hafAV+BQ+D4cZuIDT4Mf2vMNdR4/vEz5WhdOUb7+NOjkx/UwC94AB0D8tO/BjXCq9HnSnwNvgqVwreuPznOHD/n4U5rolJu5sBcsS3T8mQ/PhRfAKrgALoYXwaXwYngrvATKH53tTd3k48+Z8ucs+XO2/JklfwrlT7H8mS1/zoW3wTmJ4fp+v/wZ4FPfX5bo1GvVsDFcDJvB78JWcAnMll71vc5XtudCx9T3lyvc31e4fwAHwuXwDfhD+Fd4FUw3c2FyFxnnjF3YVuFMgj1C723QCecbsCn8M8yUPlQP75H9s3zq4QuRs3sPYUe4EA6Ci+Bw6UdJb+xcCieY9JH7ywI6RxbeJ/cbGHtyf4ncXwqbwStgT2MP9oXXwpNMusBcky4qf8tV/n4I58MfwSskdwNcGXTy8yfwDrmj75XORXXiuSDg+V7pe2o4E9aBBd7vv+y1MekeVR52yd4rMAG+qu/ea7AF3K1673Xvd1PuzUQdjPpuLkx1ysMiONbIwg/1rQzorMLGKkdp5hsne6sSqafMeww7S99N+t/CtfB5eAt8Gd6mcrUOfmTea/gxXA/rm/O7VM52BXSGIfy9/M203zXn7y75twH2gBtVfu+DQ+EDsABugufBB+Fc+AicJ/186RfAh+DF0vcM8r2GOXArPAM+Cc+CT8NZ8LfGXfgMLIfPwqVwB7wSvgCvhzvhrfBFuAG+FH7fdcYbZcDnfX8l0fn+7YadTD5CY/YmHGXeMzjO6OXeqoDOS4Mvy70MuFzubVO5fwZ2gM/CE0zaqrzv0Pv0HJwId8JZ8CV4iXETXgV3wbUmfPBeU+70HXwNPgz/AJ+Gv4PbpTfh2xM6pwqWKz9bGn8UvjcTnPj+BbaG++CJ8B04Ev4VjoXvwkkwKdHpX7yHvhi+n+CE82/we/ADeAvcD9fp+Wb4IXwRJmJ/N/wE/dvwU/ge/DzBKY9fQtM=
*/