//
// thread_pool.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_THREAD_POOL_HPP
#define BOOST_ASIO_THREAD_POOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scheduler.hpp>
#include <boost/asio/detail/thread_group.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A simple fixed-size thread pool.
/**
 * The thread pool class is an execution context where functions are permitted
 * to run on one of a fixed number of threads.
 *
 * @par Submitting tasks to the pool
 *
 * To submit functions to the thread_pool, use the @ref boost::asio::dispatch,
 * @ref boost::asio::post or @ref boost::asio::defer free functions.
 *
 * For example:
 *
 * @code void my_task()
 * {
 *   ...
 * }
 *
 * ...
 *
 * // Launch the pool with four threads.
 * boost::asio::thread_pool pool(4);
 *
 * // Submit a function to the pool.
 * boost::asio::post(pool, my_task);
 *
 * // Submit a lambda object to the pool.
 * boost::asio::post(pool,
 *     []()
 *     {
 *       ...
 *     });
 *
 * // Wait for all tasks in the pool to complete.
 * pool.join(); @endcode
 */
class thread_pool
  : public execution_context
{
public:
  class executor_type;

  /// Constructs a pool with an automatically determined number of threads.
  BOOST_ASIO_DECL thread_pool();

  /// Constructs a pool with a specified number of threads.
  BOOST_ASIO_DECL thread_pool(std::size_t num_threads);

  /// Destructor.
  /**
   * Automatically stops and joins the pool, if not explicitly done beforehand.
   */
  BOOST_ASIO_DECL ~thread_pool();

  /// Obtains the executor associated with the pool.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT;

  /// Stops the threads.
  /**
   * This function stops the threads as soon as possible. As a result of calling
   * @c stop(), pending function objects may be never be invoked.
   */
  BOOST_ASIO_DECL void stop();

  /// Joins the threads.
  /**
   * This function blocks until the threads in the pool have completed. If @c
   * stop() is not called prior to @c join(), the @c join() call will wait
   * until the pool has no more outstanding work.
   */
  BOOST_ASIO_DECL void join();

private:
  friend class executor_type;
  struct thread_function;

  // Helper function to create the underlying scheduler.
  BOOST_ASIO_DECL detail::scheduler& add_scheduler(detail::scheduler* s);

  // The underlying scheduler.
  detail::scheduler& scheduler_;

  // The threads in the pool.
  detail::thread_group threads_;
};

/// Executor used to submit functions to a thread pool.
class thread_pool::executor_type
{
public:
  /// Obtain the underlying execution context.
  thread_pool& context() const BOOST_ASIO_NOEXCEPT;

  /// Inform the thread pool that it has some outstanding work to do.
  /**
   * This function is used to inform the thread pool that some work has begun.
   * This ensures that the thread pool's join() function will not return while
   * the work is underway.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT;

  /// Inform the thread pool that some work is no longer outstanding.
  /**
   * This function is used to inform the thread pool that some work has
   * finished. Once the count of unfinished work reaches zero, the thread
   * pool's join() function is permitted to exit.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT;

  /// Request the thread pool to invoke the given function object.
  /**
   * This function is used to ask the thread pool to execute the given function
   * object. If the current thread belongs to the pool, @c dispatch() executes
   * the function before returning. Otherwise, the function will be scheduled
   * to run on the thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Request the thread pool to invoke the given function object.
  /**
   * This function is used to ask the thread pool to execute the given function
   * object. The function object will never be executed inside @c post().
   * Instead, it will be scheduled to run on the thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Request the thread pool to invoke the given function object.
  /**
   * This function is used to ask the thread pool to execute the given function
   * object. The function object will never be executed inside @c defer().
   * Instead, it will be scheduled to run on the thread pool.
   *
   * If the current thread belongs to the thread pool, @c defer() will delay
   * scheduling the function object until the current thread returns control to
   * the pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Determine whether the thread pool is running in the current thread.
  /**
   * @return @c true if the current thread belongs to the pool. Otherwise
   * returns @c false.
   */
  bool running_in_this_thread() const BOOST_ASIO_NOEXCEPT;

  /// Compare two executors for equality.
  /**
   * Two executors are equal if they refer to the same underlying thread pool.
   */
  friend bool operator==(const executor_type& a,
      const executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return &a.pool_ == &b.pool_;
  }

  /// Compare two executors for inequality.
  /**
   * Two executors are equal if they refer to the same underlying thread pool.
   */
  friend bool operator!=(const executor_type& a,
      const executor_type& b) BOOST_ASIO_NOEXCEPT
  {
    return &a.pool_ != &b.pool_;
  }

private:
  friend class thread_pool;

  // Constructor.
  explicit executor_type(thread_pool& p) : pool_(p) {}

  // The underlying thread pool.
  thread_pool& pool_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/thread_pool.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/thread_pool.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_THREAD_POOL_HPP

/* thread_pool.hpp
X2PV8/AeASdiDntyQRszHbCExgopaWh+kiJLSeF4oF26rkp+mgKgMlJqBFapJilic7wwaAlR4iKXT+9aBFI8td0j10CcHY4gR9Zp1/ExxKAupmzLUG3xy78TtOMetvjQ2uAOsozYcFxevdppcT2RG37I0DmZwsS0ByPYlldQdUHgzqGhVD9PUx1jp2fMLFMqEfbZZuk/sqZLQlnab3Mx4bwABCz70x09hViwIl3fe1K/UfNpSmY9+zzTzWJkNLdvUIcCMGl2QuihBAhdMWw2P4C2Vj2MOT+RYXGGrTOhjpWXj0uEvz4G3D2gElVX1URQWeJWLUVaZkwBY9CEW3iWu8C75toROjS+EM8oTB57SUWyOmbugtp4aVN15TjTBl6Q3L+5FuHbdd16M9nkbwHZ+O0cbPWLePFLOb+hn34rlq5dt4UKWZ8K2kNR68eb9/QwrZZMD9UoOHAAQ05a+WeSdMxQSkYxCZOCScG/1HvoB4unbp+o6wvRxYsUUmJ6PKglN65ebSpr5KbMiJJ3B3lHfk/fA3XZO5hZ3b5T1az7+JS/ibDi/3McEuYpKUAzopQ+9epcbWklnIdRJdKgRNM3JSbMRoFl6Iof1YwAT7sSDiMP/jP/1/Ozi6e5HcEsyVpodI5YtyXOiOOfF9gDKvwIGdxlQw+GIs6BI/cRCNUhRf4A+uVNXx2C7Vd/E4DX0A3FcNLqfh/k6HDR6uxUs14K9lW0R+pF/+PN2IfDlcXCrqtNW1sBOUQosrxYN/OAHWc9/psq4x9TA7UDvEqQr7awXtYS8pJd2epBBttgwy5innIpjH/rSq6vw8nJlElZvUzldWZH/qPJCZSMIgLMQDbSy2gVtJJyOUjUzJb1J7sAW2g1tKoyugISdSh+nI4V0pOIuYyGAjz3U4DdtBY6myH9rClmymIcaROJsiaHLvA4wuqiDpz7CjdmIhEo5B1m8rnD1Js41IyWRdJk+FpN5KCCTnInqGNkmTFcOME7yMD5rSUuUBcJS4MaNxx/9TeROU3Yw5dFuZ5f+T9ju3UT6Oo0vEieEM0OcwJhP4U57haIQ71uCerFWqchNhB1ELaMGlM/dXD6xCfxQMOOGE9FsPjnEwkYEgq1e6dIwzDoBame0quUy/fIxyzLz3A8iJOb3IdxRInTm9KW9ayQKkmXjxGwJb5dEAOn5ZqWSoF3RYgv25JOLk2J59smHy6xrSaV0jFIKg6bPMxrPfJeGTHcaAy/byfpS+Sc26QzEhD5mBmP826LhEz9uAT2JCQmpzl9+hIxc7ocA0cTitJwXQIPpFKoM7gc73unkCIo89MknPrzJqz+DC8l4fHNH8ekU625Aa3EF3EQLSeV/2F6JKimMrWS1s0idSrYhy6kz0tT4qTqMHjaPYbOo2cEZsOp2tz1nH0YMp6omOrFl/BCcAk+9zUblQKMwb/a6fWIcwm+GC+f0sRj3bL3unV5s5FcP1bDkeMkdAa1kdxAa5y8wzHZmvWydw5WRt8Czo3VtevNhSBOzc5+ZQPh8CcUO5SLwt6BvG+MgbJNy/nT9WUTcRhAKubEvirXuD33ee/ZBtObVHiH/UhueUORGZjBEVMYhd1O7nqDkJkgtfs19wB7iDwXEkd9u0O+jZe8Wcvt0PUOXOR5/3RsHeuce6pbCHj/0gAixsiOIkdTI2A3zwvK4wQkxsEOc8Xx2lY7InwWIOi4KpquuIO5sEw+F5FeGEP+ODYCW7gYnUC+YBVJXUdbwmKVSD23Mf9tce/do0Z6fibsZeNCOv1nTfFKhPTyrFRsy5R0/uxVaQvbZtJonQDkCkKcmEWcWN4aNIoHrc++9Tl1iRzLh2wp3v5J+hGMIqtut31HVf5P4b5Lg6qe/XDoeXUlAZPo6IVo1a57gonMcUq2tj2zr0imwmKxhsEsBkvlbnlMNK1Vw4h0xpVWgFW0PD1yRUwKPXY7glpavQoZ/WK8hsJd0BymAgsFbWp2Xbv9A8hsevoSO01N1l777MOgsUzFcj+9VAeCS9C59Cx20WIs/U1uX1ucS1DNi2qmKk1DtkX7roux3eM6htMibVY6G7jd41pa42JV1W72WJu+q7H1I/2yV7V7LuB1L7cROlZW1euy59qFUMrYDcYK2S1sYwr0dNr1H56vKpnDC6mUk+naG3OewrfiH7mGIB6hyim6i5vU3BmCm7Bl37bFEZoFdrMsbASWUfrUrLpNB54Pr1hX7HPWVbqL7TkeMS+5nSVEmpEshc06bvCuGMAoTyyQ78yzw7R1cHtLG6FpNldIU7X9bOkF8Hpbycx4nFBnW6bMPVrwZVvNzDnaUHdbpLWv7ezSVGRcv3Iuh+IX9s14NuRrt/ZNSDalaze9rbsbXGL9LUP4mh4iHb8IwAAvRCSYwU8498/yDatFzEiPoTH723Q+RIuWnztkP+9J2T5iND/HyetrYhS/rE/ZfmIsfzazysPz1+BEPn99Td/Mo3jVlpnLjApmRlLbV4VMPtN3+x1obbug4wB1t8b9PgR+bafe5fROZ5FjEVKE4Voph6pH+ed+qF00CP0/LMCs3JWfTTVB/NLTjev4r+AWAApypdsgAzcos68D39A4/pXk2naKV+P3+WfBWjwmhSuusQeWe0ONXO4VM649R5ZXiDcicP5riXVLPSD33o++gJ0Bb4N0T34NexvnRwDB3HE9jLbZKtcHNyOfVD2vld3D7BkNxH42z7O3/U/DFwcr/wM0gMt/M6K3w3Ct9lDxwtYd1TO1tW0LanlYe8HrzuoZ39q9vEZ6CPGC3RoV2Ol4sOkO8ZkQ+J0Dmn44fIF/I3sP95ns+e352PLC88a3NeyzLQDKeZh+wXyjeY96n3rf9gH1PAAAvgR7IW6KxChJqQNkUijxtFTx1Obx9NjxVCZSUYVDis3zohbUbAnpMnSFyYo0ZU3z4hY0TQmrMni9PaNxXooUZQ3zYifUzgkORReKSGUl8zIndLdxT9KvhW+K+A+CyWix/ordaPF9iqLh0pCFfkDCP+EwMiKFEFTk6NJiitrUySjbNAgJwTIkvXrfyKKShySNiuyBbub+rArppLLJxZLD0kpF5kCnY07zYKdOJ39WpXSyJMmGIi7FMmXyyaQDqesiB3O/xh/lsRhSSYpJjercCuXJFoWaZXKaxHRJcvHJUhQyJZIl0iVSJTJmkuNFLEUNhQ1FjoWORdeF10XoQGig9LHwMfGx4THKseIx87HDMdyx9DH1sYV5klOUU5VTllOXU4BTgVNCo2a7hibJBvEG9Qb5Bv0G0QbVBtkG3QZJVdJF0kXCRQp+LH7iSZEz0MM8oFHBQ3KVlI/WOhk/rlkyRjpGKkZGXlKriKKopLCkyKzQrOiw8LAIsxCzKKUwpUitUK1oqdAaeArEAWYAtYBrQB6gy7HOMd+x9zHksYh5SKPSk+Qq2XnynSSBTI5kjnSOVI6MnqSetJ6UnsyWpGeRbdFl4WWRNxAJGAOUB04DGYA1QFvgJZAAmAPUAwKOfZ1+cJOSQSMrM/4KIg2MDSJWzvusg9WHppEf95O2Xgx1VpkVdVIMflaxEaVKDGdWtRH1XAx2VmHvU84RKXcEfX7FEbmDmOusyA1al6jtrMQN+quoTxzFSx8KODLaIzFpHzFxvqEvFiVMmNGAPpMoWmgqJZoYMX24mPAX9P6/t1BBKxj4ySQeib474MYk9B0tYcCYSQyXpjjc3LCdU27i63AE6sB3JpnE0BXDvxYmGFanUhxEONQJ0qKhG8aVoqkY1nEqKEd8U6A5GUCpU84kTQ5LGKTaUbZP59TJJEqOYBnU2LGyj+ZUy6SYwqQZgDYsav2hTUqPkRIqM2iy42Af1KqoTVaNUTHAtqNpn9Wqu05og8YRtrBjWie+TmyD3hK2Noi3I2ef0qq1TrIY7jnovQO48nX7MR/hbNi1TMgeHjJAflW7TIuPrDVQsMN01eombIUuH14yMLeDfVXpJsfLoPuVITxlYHwH/arcTdYKtSaCYyBjh+6q2U3CCvMy/H7geQfyKm+ZyCU8ZoC+TusMmSBCfqBkh+Wq7UHYi+ojaoiwHdC9qnqQ82K4C/to53YorhoexF6oAag9EQIDOTsMdXq4X2EHieISw76bkDtqxAfRjodXjqVXjgdbjWk4kLTVZdJxxGWMTe4dfHTWitalbeha4tbGzvfuHGDbCjJJnvfkHMzaItZVLsgPxzb28R3k21LWtS5I7pOeR1/3eVcYtBwEEcceHSQRx5G5qJFiYccC9oz2foG+tglGjwY5xOGmROwH8irjkyOlSIyQ7CuAfrpH8qriU8SkUIyg7kuBjN3DvSp5VbLJ5VNiEsxGhscpRlj2NRzCeLWySVLGTEDa7tm8evQpmCPw+3DucdpUaqMR+6j7Fm3i1Umne2QgxUdS9zSveq9wr3KvdK92r+BObX4lfhl+LX4JfjV+eX49XSI9wppEhkSGeIZkhjiGJIYEhpSa2JrEmviaZLXRpZGlsaXRpXGOEY4xjtGK/Yx9NhAdqApkDToH4YGyQDqgDRAfSPNR95H/EfAI/ijUpqtLUZPCMYKzH7InC+oHmT4iu0e8lL6kvrS+BHaqABQB0gBNgDhAFSAH0AUIARQAUgANgBhABSC7Sd5D30PUQ9VD1kPXQ2KbspW0lbCVIhArkOg6wrMfs6cDsnGPeal7CXspe0l7aXsJeil6SXppeonqVHtTfZN7092keCd8p3wnfad9J36nfid/p38neqd6J7tMQRqB3RdxUCSCU0ntQ5dCDq+kDC//GV6NFV5mTBWVOCTdDBQ1L/9o+2joEpOlaYqagOLmFY1KqzR4idHS0TtK3FRZSfTSakUZ8RVOah6UfEm60rZFMUC145IbNRBajyEVOFnpHg0RWaVoYimzIHbpF8VoBRgakUQIsmI0ajFpbSpVlLEfJqnM2th5kcriVAVJTGPqJpnMumm535XJqRKSqMbqxpRN0pl1uOTS8nBrMnMnlE2pyMasTKIVyxOpHJPcx7yKtDVyaZWpE8WkixSLaFXllMuTvhWpliklU8okJSSajI2OUY2VjZmPHY9hjznsf9+n3bfax93X3ufd9zIJcvCrV2z70SbZpt4m2qbc9r1Nu024TbFNuk1To0i7QLtCu0S7Zj13vXS9sFLVRnWRsoWyhbqFqoXGldKV2pXKleae0jLJ8+9t6WATYZM8TLLqdVdyrZTxFdmpkGgykiQS6cYKxozGdsdQx1T3pfap9s33sfc19rn23feh98X2yfZN9tH3VfbZTDJA7aBgUDEoGdQMiq7XcVdzl3fXexR8/LGSd6bMr+hC1ZHENzY8RjFWMmY2djiGOZYypja2NMYxpruvtc+z72mSAwoAFYASQA2gCFAFKAPUAQoBlYBS6vW4cnGVEamkkkqVTajVyFRK68tLy8vL2i1Ki9OL2BVxKlYsUJvKVr9bVzf/0Cqvml+0wGmqWpWzrnH5wVPOVS5/Xuii2lGqs2BjUb2qc553p+xZ1rXAb6HXlLOqN6n0Wl4EM5+bXhM8X/tNoeAEzDmXW5JPHK8SUQF+PlWz9B+LaRcMTuycA7kV8YqiVYdLjRbsT9yc/bkVsgrlVEtKh8uVFsxPnG45nYM9Oj38uZWyipJLGxa4LMo0i6dUDsuuFxyc/dp/VP3ALEuySGpX51OoUrWc12yS08mnV5FXTCmjqCgpLSkvKSupMCsdX2BZaJhvWHCcd1y4nr9eQD+BPpG+Fb4lvjW8RblVvGW+dbiFu5W+pb61cE7yiPKo8sjy6PII8CjwSGjX7NLQKdjM3yzfLN6s3szbLNss2qzaLKhWuVS5VLpUI/hBoHy64Hzi4RzQruAtuVHIX2mjSqDQUhpTHlMWUyFfqrVAsVAyX7JgNm+2cDh/uIA5j7mQMp+yoDavtrA0b31yeoJzknGidbJ2wnPicqtzy3frfQt5K+Ic0q70KrlRdKF6X0pQkVOaU55TllOhV6pXrlemV7FV6rlgu3A5f7ngfYJ0EnMifzJ9wnBSc2J7cnlCcJJzoncCuPX1+MFX+PcaWHPtBNa80fT8svTi4/S8NM3kRUnLShNL2cZiTZaqtkVhy7ImoKaldWOzJk9V16LQaen+T/6qhEWN03znhXbzNk3XqpBFpdOi28Wnn/+Hta6NfquE51jWteyiNDOGmnmqhYNNhnR5CAvB5v1NyKuS1onsmjgFUQtD5rtNn1dFrePZNTLy8SpkF4rN55p2G7FXr1Y/f1S2ZNX8ycWDn0WaaexqGSWTS2NN0KvCVcJahSoWKquG56JVmhWzFk3c1mHNyjxSWsVZlVn5WeVZxVnVWXl0S1PzU8CpxanZqYWpuakl1Z+YP2ma4JsiGiOaZBplmsYbx5toGmmaKhormlRW2VabVp1Xb1cRVqNWZVctzk2to1wiXCpcMlw6XEJcSlxSXFpcYppVO9Q65Dv0PAU9f1QsLZqfNiGsip8TWSfc1TZreIqu5fOV8xXzVfPlWS9kz2cDsxezZ7MXsueyl3RndOd1gbqLurO6C7pzzeY1lrY/bS1szW0tL3+uNbk23TfeNyE1IjXhrcqdk1inNGutFXhXeud7l3sXe1d753mXeRd5V3kXnC90L3TPdS/dmQv8FLAQMBew7PnZY9Fj3mPp89PHwsf8uQlyVeg8Nnk+TM652FEHGER/Gl59kl59GmxzouFB0lWXXcUxm3EyeXPgAd9V9BGJV7XMrp2c39x5wHYVZBc838h5mHVFbKpcFh+ebNzie8h3pWxqXRbcLzwfv97ybtRoeQginTx6SCKdIvOVI83AngTcGN38evraJRhzHOQRh78UcRvIr0xQjLQkcURyq/BRNyL5VQlKYpYojlBvpZ6MvcMBlfwqOcXySzFzZkfDpxRHLLcaHmH8WjkFKScmT9re2fx6DEuYR/C3cN5xumVqxxG3qLcWXeI1C6c3ZE+Kr6TeaYB6QDigHJAOaAcEd2sLKAnICGgJSAioCcgL6Onl6eXWzDPMMwAZFhlmGRYY5hiWamZq5muANYtqx0tHSydLx0unHEccJxzHFbcZt2xPdE9VT9ZP5094T1lPOk8bT3xPmq+6r/yvgFfwV6EuXb2SmiWOI5zbkBvZp/4n01dk74i30rfUt9a3wG4VH0UfaR9NH3EfVR85H10fIR8FHykfDR8xHxUf2a3inuqevJ6ynqKeqp4C26Wtha25rSWBGYF51yOe25gbnScb75i3urewt7K3tLe2t6C3orekt6a3qG61d9V3uXfdrZL33PfS98L3yvf89/L34vfq97z3sveiyyWkI9hbEQ8gIQxb6i+E0a/BVpTBFj+DbbCCzY2xoyKHxJtnB35a/L0HQ2SyOE1B0+zQT8tGllUcvMho8ejfLNzYWVH04moFGXGWThweWP+8E8GXHgNscJKfezhEJFaikaVMvVg/vzBHM8HgiERCkJiifRMTX6dkRxn6YZTKtI5lEMkqjl0QxTSkbpTJtJmq/52VHDshimqobkjZKJ1pg3Mq1QDXNlN/gtUUm2zIyihawSIR2zHKfcirYF1dn5aVOlJMvEjBhJZdjrU86lvBYilLMpZMVEKkydDoENVQ2ZD50PEQ9pDD7vdd2l2rXdxd7V3eXS+jIHu/OmDrTOtI63LrQOt860TremtfK7B1rHVV3UTbSNtS20zbdl1//ee6cSW7DfsiVgtWy7cW7BYcVyzXb67Yrjj3WJZRnlHPkc9RsJGwUR5GWXWby/pWrPjM7NhIOBlREpF0QwVDRkO7Q6hDqrtSu1S75rvYuxq7XLvuu9C7Yrtkuya76Lsqu2xGGVftV8FXxVfJV81X0XUbbktu025bD70PM8sGZ6z8zC7YHVF8Q8NDFEMlQ2ZDh0OYQylDakNLQxxDurtauzy7nkY5VwFXBVcJVw1XEVcVVxlXHVchVyVXKXVbnPq4rIjYUgmp88bkHGRKqfVlqeVlae3mqcVpJuzMOBkrpqgNZSsTVjbNjFrpVROLpjgNVStTVrYujDzpXMXTZ8Yu7B2pOpM2ptUrG2cGd6yeaV2T/KZ6DTkrWxMsr8UmMBO5abbBE7XYTAUHYI65XCO8Q7hWiEzwE6kaPzHS7BuWv6eKTBoc2DkGcgFxTaLZh1ONJu0P3Bz9uWYzjeXYS1KH05UmzQ+crjkdg9073f255jJNklMbJrlMyzRMp9gO064nHRz92mYqGTHTkkyT2pZ5ZyvZLSc0G6a0DenZ5JlT0igySlJL0kvSSjLMUscnWSYbJhomHSccJ68nrifRD6APpK+Fr4mvDa9RrhWvma8druGupa+pry0+unFR7lXuWe5d7gHuBe4JbaudK9pGm4abFpummzabBpvmmyab1ptG1WyXbJcslxwEjASsp5POBx6OAW2zXiPrxvxWNuwETC2pMekxaTEZ8qlakxSTJRMlk2YTZpOHE4eTmBOYkykTKZNqE2qTSxPWB6cHOAcZB1oHawc8By7XOtd8197XkNcijiFtcy8j6yYX7PepBBk5qTnpOWk5GXqpeul6aXoZW6mek7aTlxOXk94HSAcxB/IH0wcMBzUHtgeXBwQHOQd6B4BrX/cZXmPyBkmMSUMNXpkxFA2H5PgiU3MNj+Q4k3/s7ZC1QFphrtpQeaBBV69p2jRmkbVAXmGt2lF5p4FXz226b/xYz23iPHUSv8BWofXR6byvxNfga/AwuZ06SVjgqNBTfa/spPVJTkIfgTPdNwuq79OIq/y56Fvpl69noiMGrad8eBgx/up19iImrWPSZrIfNF8fHg4aZNtnU7TXcU7i72wsbzaeyqwf03TeyawHgsLDUdqc5JxVpKpUmwor203lVJzTOks70cJH61YWTGTG9lBgqerK3VWSTOCT4tGSdx2lyyuofxvADmZxJxrSKgcHhSu5jiv+VB7NbF9lbiMOEi9ipsEljYKIVgyadPl+4mICFyWVVO70Y3H50TnpWrr8FEMlcX7BVMVdCRQ4D7lAxUp0q+0MJ/vdZJFzJJO1xGI2Pz4Ra0JTXjg7kVr3lJCprb3TIbu0oUYjAWlX2xXr8LhsVd4lln8DvQ5QLxOeR9Yr9j1dT1Wrb3iSAZMMPeIwJRRYH76KUvTlqQTiYSFxWku5z1Lm5GHncV+jzFHUJSRxqnpmTC5dSaF+pJja8gQjRSVFTWU8Ytwil7uqsL3dwlxsZV1zMO8E4xSxuhnJrMhm9dBWcf4=
*/