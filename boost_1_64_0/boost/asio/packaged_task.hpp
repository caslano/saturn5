//
// packaged_task.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_PACKAGED_TASK_HPP
#define BOOST_ASIO_PACKAGED_TASK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/future.hpp>

#if defined(BOOST_ASIO_HAS_STD_FUTURE_CLASS) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)

/// Partial specialisation of @c async_result for @c std::packaged_task.
template <typename Result, typename... Args, typename Signature>
class async_result<std::packaged_task<Result(Args...)>, Signature>
{
public:
  /// The packaged task is the concrete completion handler type.
  typedef std::packaged_task<Result(Args...)> completion_handler_type;

  /// The return type of the initiating function is the future obtained from
  /// the packaged task.
  typedef std::future<Result> return_type;

  /// The constructor extracts the future from the packaged task.
  explicit async_result(completion_handler_type& h)
    : future_(h.get_future())
  {
  }

  /// Returns the packaged task's future.
  return_type get()
  {
    return std::move(future_);
  }

private:
  return_type future_;
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   || defined(GENERATING_DOCUMENTATION)

template <typename Result, typename Signature>
struct async_result<std::packaged_task<Result()>, Signature>
{
  typedef std::packaged_task<Result()> completion_handler_type;
  typedef std::future<Result> return_type;

  explicit async_result(completion_handler_type& h)
    : future_(h.get_future())
  {
  }

  return_type get()
  {
    return std::move(future_);
  }

private:
  return_type future_;
};

#define BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF(n) \
  template <typename Result, \
    BOOST_ASIO_VARIADIC_TPARAMS(n), typename Signature> \
  class async_result< \
    std::packaged_task<Result(BOOST_ASIO_VARIADIC_TARGS(n))>, Signature> \
  { \
  public: \
    typedef std::packaged_task< \
      Result(BOOST_ASIO_VARIADIC_TARGS(n))> \
        completion_handler_type; \
  \
    typedef std::future<Result> return_type; \
  \
    explicit async_result(completion_handler_type& h) \
      : future_(h.get_future()) \
    { \
    } \
  \
    return_type get() \
    { \
      return std::move(future_); \
    } \
  \
  private: \
    return_type future_; \
  }; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF)
#undef BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_FUTURE_CLASS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_PACKAGED_TASK_HPP

/* packaged_task.hpp
+2AswbVy0WTxasYdL6cCMgTTqvYEfQHIwFergswGuQnZ1cQzL2hz6WsjvXz6sE6B2Z98crwKeegN1PqAWVJ4PGMgh2qjinjhNgTV0Hg4kJmqBgInLOpvxDkA/ibJMsksFVM8fd2CTz+bCKWxSUwi7bjOoiDFeL5CMgT6RScpuDEbhOEUuZEDL/rlxq8FcjaihePcTHGICQPaHV+wMVXC9BzOYJu1PryzTfQyHIcWLjTRJ3p81P84ZIB7sMPl7AWBE5WPJmVWNJ4uLPRYrsZ8wN+94QMEJIyV32pBMlQGakO1GjMuadyIxyhUDhYO5RcNokTjGoIlrDfweAHwG6s2C2e5bs9DGvNr5nBfWmZWo78YH6Vljgz4kuWnxvNYlZwHuH8GtPW0kOmcIaLPA8Y2aJ6cB0x0mgdmyGmgER5GemySia3NYSUQ+41NHvPnCaPHJKWFVIYU7Fxe4foIiixXBo3xuDLBTEFmiq5plJTkaJQWSY9PuUUxGtSwB0G3eQeRVNQxUqBJvCYllzh6MMkfxIrA2UpS5aBtUrTeKEe8d6IhgNIrR0FjAInDwaikcMmuC+th316BgAphnAdqqjgL1UJ6S6ve6pDJa5OMH3DDslvwiequCAHFgxwShx6OwDFT1LQfYSmiEyU1Y8sK8OiEWUgAPBnhJr8PzpF0yeaWD4WZ8WIaIbQVD0dfvOycHic97DwkWOJJo9kgQuHoyoy3mnkAP7SIFyQY0cW22ogGh3I10LmhuQpM2WIG96oB/d10j5fZ0/Gp9dzwEuGZMRrc78k8xKPzlcZ6DQtjGH9Bh4F5BohnGcjx2NejCQGJ6ZjwPiDEw5/kD80zsHw8wiYsBFWH9oCWaESPRhugvUXsYEhumprn+1o//M/2Q/JdfJtNt/xkaQ+DL+XUrVkOlebB7CbwkhOMfoGpTKs28YbQ1ODh5lXDyEURwvsWWhYo0t6w2P2iaa6gDG7cM8czUqUWxAGQIX6lx3wwJA2ii5wzYOXD8STkjIVZsc1pc9iKbC74r9Dmts2wFYBvmC0LfpfZSm2T8Es/OegfWOL1xd/QRH3Z9/Buc7qtq8/cRrBPn0V99rtvUj+Czz9/zPOn/7xkNcGdO8/feVjopV8Jnn9+v/MLbzzsBYKrV7+9+o6KmkMJtmrVtlX7/VofQLC4uFfxxOD1BxEcOXLbyHu+DlxL8LbbbrptZttj/yS4dWto6/tPPNqB4I8/fv/jr+1+OphgQ8PPDd/M/+5KgqHQjSH3y+9nElyy5PQlv31zTA3BkpKykjv3v2U3wTlzrpvT//d1+QTXrNm05oI6dQTBa6+dfu3dLx09iuDFF7e+uO2iVhcSvPnmh28+qfNxWwl26JDZYc64bgGCp5zy7Sl/XvjPcwiOGPHaiFUfnjifYM+e0Z47/dk/Ety+/fbtrvz3HiT45punvPnPux/sRfDpp4c8fcJXVy8jOHjw6sE1V87OJTh16tCpFSdfOYDgH3988MfNvT48nuCMGfYZZ3W593WCnTuXdl5hH/gEwXnznpp3w8Nf7yQ4atS7o279IngpwU8+efCTU6a/eT3BG26YdMOit/ocRnDXrn/serXr730ITpkyYsqJZ1yuEHz77eK3r7/ijjyC5eWnlf+StvImghs3ttnYbtMlrxAcMOCWAWUXlZxKMCUlPcXZu9Msgvff/8f9Hxaf4SS4fPljy/2HH7+R4Ny598894+03OhE899zB586+q+tbBJ944uUnztSqxhE8/nj/8VuHP3YJwdTUCanzncpigj/88NMP37f5cX+CL7xw4Atd1i18j+D48bvHf/X8qa8S3G+/TvulH5qSQbCq6syqoz59uZ7gjh2P7NBcr18=
*/