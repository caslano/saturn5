//
// executor_work_guard.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP
#define BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// An object of type @c executor_work_guard controls ownership of executor work
/// within a scope.
template <typename Executor>
class executor_work_guard
{
public:
  /// The underlying executor type.
  typedef Executor executor_type;

  /// Constructs a @c executor_work_guard object for the specified executor.
  /**
   * Stores a copy of @c e and calls <tt>on_work_started()</tt> on it.
   */
  explicit executor_work_guard(const executor_type& e) BOOST_ASIO_NOEXCEPT
    : executor_(e),
      owns_(true)
  {
    executor_.on_work_started();
  }

  /// Copy constructor.
  executor_work_guard(const executor_work_guard& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      owns_(other.owns_)
  {
    if (owns_)
      executor_.on_work_started();
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  executor_work_guard(executor_work_guard&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      owns_(other.owns_)
  {
    other.owns_ = false;
  }
#endif //  defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  ~executor_work_guard()
  {
    if (owns_)
      executor_.on_work_finished();
  }

  /// Obtain the associated executor.
  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  /// Whether the executor_work_guard object owns some outstanding work.
  bool owns_work() const BOOST_ASIO_NOEXCEPT
  {
    return owns_;
  }

  /// Indicate that the work is no longer outstanding.
  /**
   * Unless the object has already been reset, or is in a moved-from state,
   * calls <tt>on_work_finished()</tt> on the stored executor.
   */
  void reset() BOOST_ASIO_NOEXCEPT
  {
    if (owns_)
    {
      executor_.on_work_finished();
      owns_ = false;
    }
  }

private:
  // Disallow assignment.
  executor_work_guard& operator=(const executor_work_guard&);

  executor_type executor_;
  bool owns_;
};

/// Create an @ref executor_work_guard object.
template <typename Executor>
inline executor_work_guard<Executor> make_work_guard(const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return executor_work_guard<Executor>(ex);
}

/// Create an @ref executor_work_guard object.
template <typename ExecutionContext>
inline executor_work_guard<typename ExecutionContext::executor_type>
make_work_guard(ExecutionContext& ctx,
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename ExecutionContext::executor_type>(
      ctx.get_executor());
}

/// Create an @ref executor_work_guard object.
template <typename T>
inline executor_work_guard<typename associated_executor<T>::type>
make_work_guard(const T& t,
    typename enable_if<!is_executor<T>::value &&
      !is_convertible<T&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T>::type>(
      associated_executor<T>::get(t));
}

/// Create an @ref executor_work_guard object.
template <typename T, typename Executor>
inline executor_work_guard<typename associated_executor<T, Executor>::type>
make_work_guard(const T& t, const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T, Executor>::type>(
      associated_executor<T, Executor>::get(t, ex));
}

/// Create an @ref executor_work_guard object.
template <typename T, typename ExecutionContext>
inline executor_work_guard<typename associated_executor<T,
  typename ExecutionContext::executor_type>::type>
make_work_guard(const T& t, ExecutionContext& ctx,
    typename enable_if<!is_executor<T>::value &&
      !is_convertible<T&, execution_context&>::value &&
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return executor_work_guard<typename associated_executor<T,
    typename ExecutionContext::executor_type>::type>(
      associated_executor<T, typename ExecutionContext::executor_type>::get(
        t, ctx.get_executor()));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTOR_WORK_GUARD_HPP

/* executor_work_guard.hpp
peRQgJFH5koTgiwej2X7nokWkDjiXcV4wK9pgL1oMuPPpqFN1BiigS9Dql8KqQxYbwGr8D6sdz0F5xIwTHzdp/h6j5MfSxlYPNm40x32eToCjYqtpeONANkEyEE55djTJ9mFWB8M71GmihWdaIZAKpiGjc1hSdcFI5+20EwnASceAQFRUQIVBUbWOGWx4Nnjh2lhyk3KTQXp3bqhBj1ksfXz+XJz4SjVnc7n13vU9oPstdsY8g3RSCo5YbGgZ2NUccEXNu/oB0zVnm3rPGvqCa86w236tnWrVDwnlM6DTUhKLhMEMEcxMNAIoLunsDtrM6k/jJhc5qk1l51P3bp6wmI7Xs/iDY54fcM6krfjJK/ibvnVa5S8EYubUc9uqIAn3OqzJwCgRmfUsTLuSMbyWTPbX9DB0W2WLxj21NU3eYL+FtlPhiniaFyfKx7ri7nkuza65bP9Ul7x/Ywfc/DRfHd5iFN5Kk7l2fJUnuJTeTbfz/jO8tBdrvJEnMpTcSrPlqfyFJ/Ks/l+xlflJbBabxNKPigWnQCIuOzoVtB1B0MnDl08HWa8MumIoy5eXjSVajPNQdrGlioXEjqJlM0Hmz0FduXycUjEaUWRA1gMxlJaLplS05C8L2KbgLZSdLmAoSQ2X0KuP4Utoou+SayKyA/iWx1GJpkBlkUsisXsQCabN9q4BM/fjoes5Sbhplj6WTzC9tigmrWwB0lzehhIYaM2ZDb6m+rrU0CkFHa/jnw6w2p6sOcMdHcKk1rcUZ9+ZJeJp/b45QLUnu/E1thQs5xKwPstPxDNJJ9FeGrTA2Gfkts1GE0hg/Zon5FKGfHionAL1lODpnDK2H4YzCzZOGrXLbw8juV82jGf5vtjaK+YYfuyw6L+0aGsqKIRQNfvJCHqO3iC+pT25RLYvCIUZdJAQxftvUtarBcgzPubO42IDndAAbBvx7diSKkXXHI+LNzFSozT22kOse0ibfRgjs4lYHdUcVp35A1MXmpkstgH5O3ma2hKoSMbFzWMKxcFp7c45g3sXmPZPHV6SbupXys51C/b3AkyYYorPenyEYHsodPXEXRQ0NPZWFIoXVEdGV3NEXY/hDAu0ZRbCdQOTfV7OtuXTJXsMZIXo1mezfW+WImsrdIo7fz18DOjGaNA/a90M2R51bBkIQeLU75vMJkSm1pVQDzsu16aBPUfeCmj3RgyUoqu1k+FvGF0JDPJ9GDayXLzo8OMz/qLuVO0eFtPtyEW0WTOwhmbdeiltdQwoWMkP4z1/JZMEvtzbgmkH2I5k04U+6ijrSOod7SGOd+TMKKiH0xO78vGCdBovQPJYU8OWJaMpjxp8qxxfnowVUgKIS6BDbiRt0ZP9IldXbhhB+PZzJ60zMM0Co51vKEHsTqGtzmDPWKPcuUojwvZITa5YkWt9BzeafSHrhbZgp82B4LDlC9VSzeY90bIiSW6M1+5prXjwlGmMsI9+at4XrZ8H2oct+Nim+3rJKQtxpWLkct1ZVJ7ivEutWtX/DYmL/ksviUj/NIGVcEp39oVaMvkBgucLlARO+SW6MAAjV0p/hD8S0yE8ykLzvdHc1Z7w+RutOubSRaQSrXCpnt6WsKOOMmUrtcuktV4ey5A36ZxulVBSsHrTWVzuhK384nt8kfzcbHG6zAHyvcjVZnTeSs5n5rkqoedVyn6thJ0KoPTVbXK0beVoFNWNh2PMuxcOJ1y4XTKhdN5P3G63TbOL9+PIb/0eROX000+ni3RQizhi6fFSo0SleWbJfiWMggdV3kzfofh23UhfrcxsBEb5PPGnTWD00mY081S8tiD7zqvn4P5fDZPJIY3g3IOw+qmJSgYjE/YQ1xupyoJt8c=
*/