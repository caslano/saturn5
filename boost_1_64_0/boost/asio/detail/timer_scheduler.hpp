//
// detail/timer_scheduler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP
#define BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/timer_scheduler_fwd.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/winrt_timer_scheduler.hpp>
#elif defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#elif defined(BOOST_ASIO_HAS_EPOLL)
# include <boost/asio/detail/epoll_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_KQUEUE)
# include <boost/asio/detail/kqueue_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
# include <boost/asio/detail/dev_poll_reactor.hpp>
#else
# include <boost/asio/detail/select_reactor.hpp>
#endif

#endif // BOOST_ASIO_DETAIL_TIMER_SCHEDULER_HPP

/* timer_scheduler.hpp
zYSO8b3FOJgaEx6JE/FW66UsvxTyCUI+9grjGgv8oVyX/XqIOvTff7gODHWYLW3lUPlQHeb46SfrUxT6HeF+sg/uH+KZZaGnvuQWY+s6Y/mhss5Okv8Bkk8jebcBTK4zlr+E6ignnsL5K6bn2f0dkllPfoeM08OyXkukTEfyXwv/IfL316y/zS2prKqWfe8tCn/Mq09dDod6YOefS0CUvcOkPmYC0+iaW/dE5hGAvrgm9aXrxeb1JN+94rq5M/yc11jfBn4kvgFe7+YDKXKPZvk0nOWzrVG55lGBoVTWFeJ4P5d8Sv56mwV3BuS911hPkv8Zm7ouauN10UQeM09Q+E5waODNzLaD609NpzvLoZZuoLHR5sCXl+ttIZ7vHmgrCzR8F99SvHW2zcpkubZ6gOKexBvba5p3v7mI55n3vqF4221ma69tgR9RGvNwP8Jvfj/1VPpIluNdLuZfknsJ8eCXetwl43neNQv5XdOjy8MkOxmtONJUF7E2W5eCbyd2/sYSWjMzJjzCOG6w3DE7f7uJrHFI/hmdzDmPTI6VjB2N6sNMyMTUrJRrzDqZMZDJ60vvv2vk+69Ophgyl2aSzK16mZ7wRyq0RkzvxxOR1tfM2TGB35Wv6OP/fVmsH4+9wXv92CHX1NDW/fB4oM3imrqWPyz+e2onWItv6z2XObq7Mx3MfDUZwJPII2ux7HNyZBRtpcq9hiSucV8TsnxWgvvaOPJ3tnVETrzO4WUvdqKM09XwzUCkUY7w8RSeZEtUwky/cyyl8FfUsRe/a8TZCjk2P07hNbL91ZF/HcJrKE7ISHo3uKZM8xz0BmTkmQ4ZZyNGEdy3bO+VRASUwONEHsmAaQP/ineIthjD1qaq3ylGxYS3wzvEz3y8Q3Ccfanqd4oKYz9gmcZUdW2mpoOhbfIcW47wq+PQxgJ4RhVtbPwS4zeKKhq7qY51azRUh15j9unuihnHFPa+Np1jqn7J+eOYUvmYGnoY7+8byDaa3J+Gio3r23CPHI+52BJNudggEzwXG/I0crElWnOxbeypmHJoKTc2nUMLcXxxaCH8h+HQattLpxPvBbJLneRyjIZOMHg+wd0m+W3BDeaY5Kdtw5uyDWWIOMG3YaRn2obXpBnvL0zY4TS5P10bxlqo8R4RT7bhduZtGDLBt2HkaWjD7Xy04eJ0o34R0M9lqh/oBK114ziJvP5j4BNEePB8gsjP0IaRhymf4MjeRp22IUKdiU7cLy3bVJ2fflnXjH65Kdt/v1R1Om6i002DMW5LnbxMzqOnuHV6NdFkrG9GP0F6pv1kX4bx/iLFeq75/cmews/WxrFe00/ushrrm9FPQk3G+rt89JPaPkb92g/GP0vN9UNPsdQNcWSbKjD2E4QH30+Qn6FNFch+4l1nxX2NOv0EOtnNdeKeYtmuEM9nX0F48H3l1UT/fUXVKybTqNdzQzE/SL1mYts0KYWzyXnTZml4ah1DDHohXvD9Bel59ZeL1Wc3k3t8CHvLnFb3qOOqDTcpf8SVfeYrc65ayATfZ8JN+gzyMfQZrgec2zPquFcY3bTSkZuYVT24/LQvVzPal2OI//aVqY51bFDyT8ikB+NCKJlTJHlGxXcBH2v2LIsUE+CfAX8Z+ettXythVhyjHCdDvuvNJ/8rtm9wb2b71xwyThrFyYO/mPy/tP0dGqnjT6RY71Q8+0ArSWaf7RNIrLeFI+5oeu+j+6dvNuo1COMXNVdccxj2i4p6X0FpbbYtU67mtVEby09UnyPwE8WFcuf1jyUUZ7ftYyVSjqGRvCabzO+LFSTzrK2HslD5LfY9uGypSgq/O95HYWts3fHFYy9WHb/C2upCW2fEHY11GN4=
*/