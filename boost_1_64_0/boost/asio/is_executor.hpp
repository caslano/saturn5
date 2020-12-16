//
// is_executor.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_EXECUTOR_HPP
#define BOOST_ASIO_IS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// The is_executor trait detects whether a type T meets the Executor type
/// requirements.
/**
 * Class template @c is_executor is a UnaryTypeTrait that is derived from @c
 * true_type if the type @c T meets the syntactic requirements for Executor,
 * otherwise @c false_type.
 */
template <typename T>
struct is_executor
#if defined(GENERATING_DOCUMENTATION)
  : integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  : boost::asio::detail::is_executor<T>
#endif // defined(GENERATING_DOCUMENTATION)
{
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_EXECUTOR_HPP

/* is_executor.hpp
ANNAAlPCKGC3EdPbvZgGlwPO3gIoPY3pJYSpYTqmggOYAu8C7LZj6hvBNHwIMHsGkNUEeGrF1PZBdMUt6IK9MK2vwlS/hqaE0Iy5UP8jaMoSqPP16CY/1LkGXTAPqnQ9umMcZnACahCD+emAhGaoqC5UEF1/DqZ/D9RiDKY8H+Z4C4rdj6GsghqZaNYHYALzYTZfhcncg2HPoTtHYNYNMP8jaF49VPYOmPP9GO4cVPEcuudGmFgVTCkMNQwBdsIY3vdhWCvQbB2QUgOzNQEHo1CbGqjVGNTtfjT9Dpiqju75IUw9L7oAQ/xKmNQdML99GILjgLZedG9ImASG54eAjQoMwfuh0q/AMPrRRR+A+nZD/U5AZXOAyFuhYvMAi2+GKt4Bc4sCAk9CJY8BQnwY5m6Y8y6Yz16YvAbImA+ztB7TQk3nwnQ1DE8YsPJbQNoPoAK/gQrnAUkWNEH9jgF29mPYK2Gib4bJ3Qoz6sNQvxLm5sOwR6EWOah+BYa4Eib6AUDoD2FWvwW8HMeQ74c618Ac7ofp9ALKvwpzXAqo9cO85wGCK6HCSwDfMUBiHyClEpDzG5jmKwA7+2C+GqD/A1DTPODhLCAzD2jwAwZeAbP4AVRwKaBwBJB4C+D1a4CDW6DCXqhhA2DuVsB6PUx6LmBqKaYWLyB8HNPAmwHhPqhhM+BmL2DyB1DhEZjWK2HqdVDZk1DLE1B/LyBtF6aKuZhqTsIk9wISdgEefguT+SrgdBzQOgpYux6muA/TxBjg87eAEx/Mow6wHQOEj2EKOwm4/Bqmr2OAtipMFfsA8y2ArGWYim7EVNMLyPwazOUIINyLqeA3MPdmTDUnxNSG6aUO0+ESwEkzoPT9mFbqMWUdA0QfB+zfCmh7P6acFkyJ18OUGgCrZwHHvYAuEzA4iinnLMyrBRDTDXgwMR0eAQz8AHDQginyfZiOlsHco4Cm+wG3P8Q0IKD+fYDKVwKeujF9/QbwfQ8g5f2YEuoAdfcAAqOAmzCg4RygbBxTyHFMmyOYJucBdusBMSFMY2cxFfdhCl6CaaEKU3IDpvZzgKr5gMIKwNkuTAOjmFr6ZmIFgKngFRii6RA5jebOhmq/AF33FajMl6EC+9F9B6HmLxcmgqYGMSSfq8ZiH13UBfURZri5CotfFNmCoqrQtBtQ9Aw0dwQQcALD/kJAysm5YtGFRR1UbypMdRa68hDUZCpUcjNU9ytoxkEMSTvM/yAgY1o1FnZo1lSozikMyQmoThCmchwQ9VnAxBwxPBjSl8HcDwJ+pmMoOgEXnxULNcDNDei+z8OMZ0M9v4KhOI3uvgKqvhGqfB1MbBpMbQ6G/DggQahFC7rtVAUW71CdMcCIH2q0CfB3CGb4Epjp56DqL4XKj8CU58zExgeQMkuoAVSnGjB2AtB0BaDsy1Drz1+FDRNU9ADgcjrU9TQgaxPM4mWAgulTsEAH9FVh6L40FRsQDPuLoL5fAVx0VGBxiaGugCl+ZiYW4hii66ASewFVxwGtGtT5czBVYVaVgJBqqFsrTMWHYZ4GVf7iVdh8PQIbDcCRDyr7MqjPZ2EmbVdhMwXI9mHYR6CmZzDkLwbU7Qe0vATmPVaBBTlMZM40LPIBDzOhjicBuWcAXy8FtLwcZv8CwPZmwG47oGgfzH3vMrHxw2IacNQBmD8NqHwZ1P4Q1HAm4GMW4OZKmMiLAVudUOmXAz6vAxyfAMTsA0ydnIEFO6C0FTB9BlAxBeb9RUwDzTD1IEyoC5AwBTCuVWlVVYCwAFS/Yyo2YJgOAoDczwBqD8AkvgAInAHo3AhYnQG4+7KGBTuguRJT0Bimh5dC5afAxL5QoVVUwGTGxKIX5tU=
*/