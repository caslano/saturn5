//
// detail/win_iocp_io_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_IO_CONTEXT_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_IO_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/thread.hpp>
#include <boost/asio/detail/thread_context.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/detail/win_iocp_operation.hpp>
#include <boost/asio/detail/win_iocp_thread_info.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class wait_op;

class win_iocp_io_context
  : public execution_context_service_base<win_iocp_io_context>,
    public thread_context
{
public:
  // Constructor. Specifies a concurrency hint that is passed through to the
  // underlying I/O completion port.
  BOOST_ASIO_DECL win_iocp_io_context(boost::asio::execution_context& ctx,
      int concurrency_hint = -1, bool own_thread = true);

  // Destructor.
  BOOST_ASIO_DECL ~win_iocp_io_context();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Initialise the task. Nothing to do here.
  void init_task()
  {
  }

  // Register a handle with the IO completion port.
  BOOST_ASIO_DECL boost::system::error_code register_handle(
      HANDLE handle, boost::system::error_code& ec);

  // Run the event loop until stopped or no more work.
  BOOST_ASIO_DECL size_t run(boost::system::error_code& ec);

  // Run until stopped or one operation is performed.
  BOOST_ASIO_DECL size_t run_one(boost::system::error_code& ec);

  // Run until timeout, interrupted, or one operation is performed.
  BOOST_ASIO_DECL size_t wait_one(long usec, boost::system::error_code& ec);

  // Poll for operations without blocking.
  BOOST_ASIO_DECL size_t poll(boost::system::error_code& ec);

  // Poll for one operation without blocking.
  BOOST_ASIO_DECL size_t poll_one(boost::system::error_code& ec);

  // Stop the event processing loop.
  BOOST_ASIO_DECL void stop();

  // Determine whether the io_context is stopped.
  bool stopped() const
  {
    return ::InterlockedExchangeAdd(&stopped_, 0) != 0;
  }

  // Restart in preparation for a subsequent run invocation.
  void restart()
  {
    ::InterlockedExchange(&stopped_, 0);
  }

  // Notify that some work has started.
  void work_started()
  {
    ::InterlockedIncrement(&outstanding_work_);
  }

  // Notify that some work has finished.
  void work_finished()
  {
    if (::InterlockedDecrement(&outstanding_work_) == 0)
      stop();
  }

  // Return whether a handler can be dispatched immediately.
  BOOST_ASIO_DECL bool can_dispatch();

  /// Capture the current exception so it can be rethrown from a run function.
  BOOST_ASIO_DECL void capture_current_exception();

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() has not yet been called for the operation.
  void post_immediate_completion(win_iocp_operation* op, bool)
  {
    work_started();
    post_deferred_completion(op);
  }

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() was previously called for the operation.
  BOOST_ASIO_DECL void post_deferred_completion(win_iocp_operation* op);

  // Request invocation of the given operation and return immediately. Assumes
  // that work_started() was previously called for the operations.
  BOOST_ASIO_DECL void post_deferred_completions(
      op_queue<win_iocp_operation>& ops);

  // Request invocation of the given operation using the thread-private queue
  // and return immediately. Assumes that work_started() has not yet been
  // called for the operation.
  void post_private_immediate_completion(win_iocp_operation* op)
  {
    post_immediate_completion(op, false);
  }

  // Request invocation of the given operation using the thread-private queue
  // and return immediately. Assumes that work_started() was previously called
  // for the operation.
  void post_private_deferred_completion(win_iocp_operation* op)
  {
    post_deferred_completion(op);
  }

  // Enqueue the given operation following a failed attempt to dispatch the
  // operation for immediate invocation.
  void do_dispatch(operation* op)
  {
    post_immediate_completion(op, false);
  }

  // Process unfinished operations as part of a shutdown operation. Assumes
  // that work_started() was previously called for the operations.
  BOOST_ASIO_DECL void abandon_operations(op_queue<operation>& ops);

  // Called after starting an overlapped I/O operation that did not complete
  // immediately. The caller must have already called work_started() prior to
  // starting the operation.
  BOOST_ASIO_DECL void on_pending(win_iocp_operation* op);

  // Called after starting an overlapped I/O operation that completed
  // immediately. The caller must have already called work_started() prior to
  // starting the operation.
  BOOST_ASIO_DECL void on_completion(win_iocp_operation* op,
      DWORD last_error = 0, DWORD bytes_transferred = 0);

  // Called after starting an overlapped I/O operation that completed
  // immediately. The caller must have already called work_started() prior to
  // starting the operation.
  BOOST_ASIO_DECL void on_completion(win_iocp_operation* op,
      const boost::system::error_code& ec, DWORD bytes_transferred = 0);

  // Add a new timer queue to the service.
  template <typename Time_Traits>
  void add_timer_queue(timer_queue<Time_Traits>& timer_queue);

  // Remove a timer queue from the service.
  template <typename Time_Traits>
  void remove_timer_queue(timer_queue<Time_Traits>& timer_queue);

  // Schedule a new operation in the given timer queue to expire at the
  // specified absolute time.
  template <typename Time_Traits>
  void schedule_timer(timer_queue<Time_Traits>& queue,
      const typename Time_Traits::time_type& time,
      typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op);

  // Cancel the timer associated with the given token. Returns the number of
  // handlers that have been posted or dispatched.
  template <typename Time_Traits>
  std::size_t cancel_timer(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data& timer,
      std::size_t max_cancelled = (std::numeric_limits<std::size_t>::max)());

  // Cancel the timer operations associated with the given key.
  template <typename Time_Traits>
  void cancel_timer_by_key(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data* timer,
      void* cancellation_key);

  // Move the timer operations associated with the given timer.
  template <typename Time_Traits>
  void move_timer(timer_queue<Time_Traits>& queue,
      typename timer_queue<Time_Traits>::per_timer_data& to,
      typename timer_queue<Time_Traits>::per_timer_data& from);

  // Get the concurrency hint that was used to initialise the io_context.
  int concurrency_hint() const
  {
    return concurrency_hint_;
  }

private:
#if defined(WINVER) && (WINVER < 0x0500)
  typedef DWORD dword_ptr_t;
  typedef ULONG ulong_ptr_t;
#else // defined(WINVER) && (WINVER < 0x0500)
  typedef DWORD_PTR dword_ptr_t;
  typedef ULONG_PTR ulong_ptr_t;
#endif // defined(WINVER) && (WINVER < 0x0500)

  // Dequeues at most one operation from the I/O completion port, and then
  // executes it. Returns the number of operations that were dequeued (i.e.
  // either 0 or 1).
  BOOST_ASIO_DECL size_t do_one(DWORD msec,
      win_iocp_thread_info& this_thread, boost::system::error_code& ec);

  // Helper to calculate the GetQueuedCompletionStatus timeout.
  BOOST_ASIO_DECL static DWORD get_gqcs_timeout();

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Called to recalculate and update the timeout.
  BOOST_ASIO_DECL void update_timeout();

  // Helper class to call work_finished() on block exit.
  struct work_finished_on_block_exit;

  // Helper class for managing a HANDLE.
  struct auto_handle
  {
    HANDLE handle;
    auto_handle() : handle(0) {}
    ~auto_handle() { if (handle) ::CloseHandle(handle); }
  };

  // The IO completion port used for queueing operations.
  auto_handle iocp_;

  // The count of unfinished work.
  long outstanding_work_;

  // Flag to indicate whether the event loop has been stopped.
  mutable long stopped_;

  // Flag to indicate whether there is an in-flight stop event. Every event
  // posted using PostQueuedCompletionStatus consumes non-paged pool, so to
  // avoid exhausting this resouce we limit the number of outstanding events.
  long stop_event_posted_;

  // Flag to indicate whether the service has been shut down.
  long shutdown_;

  enum
  {
    // Timeout to use with GetQueuedCompletionStatus on older versions of
    // Windows. Some versions of windows have a "bug" where a call to
    // GetQueuedCompletionStatus can appear stuck even though there are events
    // waiting on the queue. Using a timeout helps to work around the issue.
    default_gqcs_timeout = 500,

    // Maximum waitable timer timeout, in milliseconds.
    max_timeout_msec = 5 * 60 * 1000,

    // Maximum waitable timer timeout, in microseconds.
    max_timeout_usec = max_timeout_msec * 1000,

    // Completion key value used to wake up a thread to dispatch timers or
    // completed operations.
    wake_for_dispatch = 1,

    // Completion key value to indicate that an operation has posted with the
    // original last_error and bytes_transferred values stored in the fields of
    // the OVERLAPPED structure.
    overlapped_contains_result = 2
  };

  // Timeout to use with GetQueuedCompletionStatus.
  const DWORD gqcs_timeout_;

  // Helper class to run the scheduler in its own thread.
  struct thread_function;
  friend struct thread_function;

  // Function object for processing timeouts in a background thread.
  struct timer_thread_function;
  friend struct timer_thread_function;

  // Background thread used for processing timeouts.
  scoped_ptr<thread> timer_thread_;

  // A waitable timer object used for waiting for timeouts.
  auto_handle waitable_timer_;

  // Non-zero if timers or completed operations need to be dispatched.
  long dispatch_required_;

  // Mutex for protecting access to the timer queues and completed operations.
  mutex dispatch_mutex_;

  // The timer queues.
  timer_queue_set timer_queues_;

  // The operations that are ready to dispatch.
  op_queue<win_iocp_operation> completed_ops_;

  // The concurrency hint used to initialise the io_context.
  const int concurrency_hint_;

  // The thread that is running the io_context.
  scoped_ptr<thread> thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/win_iocp_io_context.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_iocp_io_context.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_IO_CONTEXT_HPP

/* win_iocp_io_context.hpp
HXNqseq+584Gfn4+kdv0xSMUhWVwQLyMHSskcptsaY0WRjn6dw0ryvhZMbm83UV/E6JZv3FjCVMsbTpKe8rJqmfUltyPu5FFiMWWKQwpwjIUfJPmpulVI7gL1qiq7Aia+M65eXl/9HTV8n52nzjW1tp/B6x+9RqW1GZru+R9fXiC/mERQy81jvLfIwJAyAoJfTdWF+QbNqAnAAUn0Y9h/6wr297k/vL65eIfV7wlQ+tg+04ZKNE+EtfnOjgpCpHnXYvGDUNUCppFpF5R6CFzYmCYPyt75CTElsmo5AwH+UDXJ79rx2zAaL5Lq/UyEAixc4uOQGkzNgj5t9uLRn19WHbHuVsv4s2wf4gXFqqgfPcv6INR4bZNoeazmiSp5CKW5iGE7B9e5U1Cz1v7kDKCSKqMWqhyMSBX3itAKWtb2V6a+TomvrLuYuFUVijjSGUa8NgIDhX9wtMaghqRX5T9yBLe6mahCBsJ2Bo824DSipjsTliZbvF0tmd/H3esqwWEQcSv+QayXxM39RwKUR2r2PAMCEy2Xh8xgghm/jOd0hz/rf3gzrL6fUXH2GlsfJj9gUQmBnl69BEHamG4ezSFCvIDsQ3hJyCHZhQ6822pvZxPjHBmR6U5XPcXnpYSmxD++S/CPd1tih1rxE89M6vnmeE5W20h8kiRc92iVqU/TyaUhCBX9uGEemXbMdwf8BstyqTcTmqoL2keZ6L1+HygNN7FaBOH2gzXs92XYEaFkze8c6PgP8Gfe//rbfA+PIsw1VfEpDor2UquZbKovWpeKoqhJ+scm2viU8HRKjikK5fuo03t/tzfdv6b82A8I1M0+KgzsJ1Fv/iG/RH7o7bL7xdOQCjfUbaPXS/Vhp/dpnNuWw7fFrC7FiA/P/9P60X/IL+AkKCPRgF+gcLGn4Zj9rh68t/JEqTTcoNVF9JhPRNHmr0WZgZfai0UBisN8fLt5vaParXuCgbE+qZzEaP2hunLCtAaHsmKesFtWoTrZxjq5xDm2AAt+zuxgLPMS2rJN5XSqamWgFQLJaM5lcypK3EAZCSBRj1fskXTlMSf60Ud0OPJCVSDi7e3qCxgKDxA0IYtqLmpte7VVI9ZLFStVO/GKLH1kKd/X1nBDo3B9qu5pLeeWbwbXHEoUAW9uHw/CSQ3ucjlvyNOLOYgs9aH2iCNRrUAmu35xFjXhwWPT1PCVs4JnFwi9jNGwm0OzgkjQLjI4eGS/5GnDDtHeZjQP1CxBsSSdUvbrrAQFnPvjWEKMBaGEReIN2cziX5e0dbZesDXQR9HLbF8rQs1P+WVkkfr6wEMZkcDd0cPTG5kTA7V+tKu+OQcPBTrxw51gJIxuxC9X+EldxCFf/63EoD3WI+wsQv8OyGu8QuHQQF190tI9B0JDnXli6L/ThaILWGuBgZg18MhNaD0NQcC8ARJKiF+AA8NAI/rXuED2JDkA5C27XSsZwH5s+zU+F19nsLk5MBIMg/YCTnbH9DL9I6IL/Taa6f3m/b7a2fSNo2BtSf6MXwGVdw/VssP7SbO4LFOZAI5e7oQ5xCeDvZYyZCRTrLAy284TlZZXFRC2xjiJp9flBwiuuet89gHDSfvUQgFAK6B5Pzzmbb+2/hISEhScXBzZmTxiO0PmKoEkJ4W0CcLBYGHxQaGBcYVik6GBcZGhkXGxtQIsNbL1grQug87AxrgOMyhzr6We0w58/KyUsI6qzQE/bLYJ6lyTVwkfAx9/bv/9XUww90piQ/1eUqOfLcK3n+7CFfzoL3nbq7+M/EN+OO55Rd8zPddqbVtRjDpcpJqADlVkyt9uS/QwN7RJlg+Map3LDia7zFiUkdqYP8ZnwJKT74tSoCegee9mUg60XUNFPqY2X5KqCEP0ubQjlGNwK3n/hkuDD29SyUptlnSOLG+l1BPcKq2x2lj0J7CqJsjdOsiPBOU1w75PwAXgOh/dss71WSfS2AEh2O9Q46E1Tq3GEtKhldruyzGWN5yZnphG9qfAr/3FfUKkYMnJa6sgyocWo4yq+wmevRN28MZsargjH47esnymzG1i3tI7bGrux9yVCvqfYwDY3mNjZh1asf+1cNSwC+KNVAazd+s5v59wf/kWws9O6VOYJeXmYNJyMX8VxNk5wAyiRja/x6uBXL85rw6kTCwPs+mtaG5IwnbL1Mv/BznYeDgYP8li4SFmZn5F2W6v+SC590U7ET/em/4LPjFsf0X25JyMrS2MBayNbc2JWEGf7Xcfu0EC1gpkwrY5NRJuLj+WOs/bINJ87cOsgO5/2QBXP9mAazg8bD/xgBJuJmBHP/JIg4e4JwwJcZp/Fw+ZdC/5M6iNB8ZKuEAwBZXaoNQYMORIRFewiPQ+Tl0oIU7/sBbs16jCLBphUhjjeTyh9jys0nDMNQftD54p7k2vOz7dDfEe0Xol/LtcGdnt6AE/BxqwVMGsZH0w1Ozhsh+Uj0eNWXtFhqqCaqssx0I8lGvdjZiJ7UZDmxMrsDBZuLZGj94IHnAIyVUH9Z7u9ZQdeB5B4/nhEJ62sEdtsnodVK799PnXle448qxP2nI3TbPnYe0PZMyaHOIjoHR/ahzmIjcpINJUf8dkQkbChuvbE9PRvQhn53hIG1LejwfYGc0CHqZtjRNV/ZVxhk/qblr0PkdUpiC1oRb9oxIT7uvkLu+2MmPsbuMJFuy9ZipIDbL+vzyerMfxvPIwnrbMj2U7dhqCYy7p4f5xUHyb4U/nFCULatRF+5ok30s/GiOtryfo7ZhsrrwbQxmPds9p+Jbz/3pagoiCDH+a1xXt3c2P2kvhdJP7gjcbDQL4fJ9zPUCxVR52bFoNio5oYDXMZ/jvUNqMSkHcvBihLoUj3pCRbyPZXebg66ge6kGzYb1aj/QO5bgcE2Hpe+93qqfq1tSUdbjSCrKVFFXkuXgnqbuf91n2VMxdLFRvtsHOn3v6I2DiB2nO3SBEW3CfdNX59PyvTI7/H717dO3gPl4Lg28lJ1KuNKFL7hvD6Z6JdYnVDCXFgAELPvTmi0zClfqvmVYJW5945pW5a/fslytQtuR9YgjwZNcNaFIlsyNQ1eWt+zZWecDAetSFkQPSViq+kskq5I55A1vZPOSCuaIxjDtzTs02nkBUxLzGq346ZfK3ryrurRpiwLBqUUhW4AayWz7fvcCD21bKD1F335O5ge8ZjFjv0iUo/ckeLDFRGIfxvR3jrJfybArI9N0FYwVBElrSGug5WLnr4VmyyvlRZvtFuzuZNd5JHpwWORkFGbIzH3rn0SS4r0AXVCtqlwVCsYIiKNm4Zzg14kzIrxafrUcy3emdcaNzqLPrE8SUySuNSjFVmiqLsPySRG4PEUzFwPjLpwiPBf7mO33gnqtl40lbIBabV0VhCJ5CAIRaokckjqvo51SuGdYUx/FLq6z4j60RAeqfs09hV/pe+iD6stC8VGcXf8ZEj+IUqJSDfAB5HcT3Pud1gYSq2bYH4v0xT2L0WHd8LOJgsYUuK8hNizgBPP51sA1zAnf5vHB5YALhkyIKN7CwAl+btz+CZeQRHAffVoeuBev8flcpK8w+lvgWCm4omkDWKeeK1gnPljnUtCYMx56sgR22yf9S32pdYatwSONJfHexsDYWf9YdxzKM6LjOn134o0ziL4Nkfh++fh+xvgeCZqYRZoYfpqYJpqYKMJQrwD0G0zKUzzpdcf4HhyaGCawKBj95hXlKbK0CbH0uk58j+sTWYyaCXtdGN91FPoNEWU5MeUplPS6RHyPAk1MJmHoPVgFFvsmZ/zAEU2yoCKLL8+rM5y+LUDfFknfxsu+DWZpiuRYeNxXEmSv5aRETWlD8xcSP7zOofj6MV5UlZsSTU1KSlRNBV2p6slfNIOyNNa1hzG6h3Od+hTHVFXjAlyGnBJtUlZKdFBaStQmOvbD3Ejih5R0MKWhRKtykCazjIsXncgFqx20Bn/AinSyKb5Wy1qEz72mxKtylmaxxNcxnqimvck/UBQ4UBLgpklivEz9JhAvAxcvIxEvQx0vsxX/9rEb/WYqQVIjXpIzXtI1XhI1XlIhXpJJgqxJicxbkcxbiexBkayOBq2FHA2JEv1NKLQSmTtNzEtpin1JigD00K+it1misJ+7Xoj2Emy9GyCJHzCIlxWQpkqMfaHpYlkzn+xfEpTcSoHFDJPPjF9JqSvF2EMnLx5HuzlvsIM06TCWsMkrqWt6aJ9/En3FqKyRfAShth7vSVxQOIBK0Md4RaqsAZE5xSxySYm2HRVjwpKMoN70Pk1K/ROvrnzDW3niujSXhrTL2rTL+jQBF27v2E2TQyjLD9rw7stkzgk36SJYQktXkg952N671dusNWKZDQy3P2xGk2zDmkE651XzX+0WsA9cdc4D578SL2I/rFfDdwkcyLRhmBRrWQlrUU/1Joe1OfYj8ui9QX4Dcw2ztAR5FIJKGv5wqCiia/lJBtm1AA2F8uciflziTzoXl4z7Xvdd861Q/bSxFh5K34qq4AdohZk5ELvFhatWDH5rqXu0NZld2/UNlHikVKoK8YFUoNNLQmmNubcReV9K9gh38ZI8OOTKpv3qh75UN0zsMV68l2naUazWsCyvsU7xRpxWG2qqWVQ+qp1ACVklaYLNpvWcdv9h20s5YNvJLp98xWeawtogVzjjGCTSq7bvXZOL+nZXJGluR7nh7S550tyBsudby1IR2p+cNRQC203NFKKwLMfIM4OtR5Qhe4P7MDTOrFAK/sXvz/vlDy0vydZLzIgbnL0DyhVncvZBI0ns+4w07qgNmdv7QpckFj27MzyxgxzfI7KBnkE2EFGZvBkOKiOvpE8JW5jmLy9XZnVWurz3BfIdyeO39hEuoa8/fnbft4zGMOQsxyfkD9KCc+rWi/FLN+X8ji/J64LREFoZwlMdSyACdhdmZqytA2/xtnGTkvpxmD2rWuvaM/YIpjAW1nNViON/6vcf1BbfqA7F8M4wZI/3evMNOLq5LoVdbWCjnjheu997NQeUried9l9P3r/y4dcftFtzPfG88b6HeHyp3028mXqDcU/7SOCbbLdld0p4D/WI9vTJd6hlZfn06Br1nnpU9xy7O7SNjApR7C1FBzPwbTj2WqcJUC6Nwiy0zsg/H3PSKJRLLo02MdSxw30Vsky4CBMnTKZzY1XaoUqTsgSD80Nqh2WZ+ALpIdpVGE+ZEt/r6g/dHeon4W5CjWR6OHYfXTvujPJmyAWw9EPtOlFXcU5CuEhiWZKwZqPx+yLWqUBIdVULREvz1K7RvH3pGyUg17q8BZ1Duq0+CG6FyB6o9TaQLGN8Xj/rhnLdnKadNRsRMJk2tX621dqag1MnlduMuqJwdnHf4pLjwSwDjx0u5cYshnuAwDSSnTpFZWBnU7aigx6OdnlQzbaBgJsP7vYL/pE4rmQdzrkI8RLcfmDmXehPd76onntrHw6l67r7t18DzoepX+kPJWGk6/cwUcC2BOkLy25H9EtityB6fIc472PPJj0fuKBIXR6wo4q4Lr5XH/u03HtEIfc575BS7kvNIfng524iksEv00RkDJ+3pmISRzxR49RHAlOlrLY7qSXxt3vzJHW2B7ckeR/RfUMrt0pPpiVRzvdTO+CaGgKd/Ige/ZyC9B4/OAVkPOIWzW7dO44F+w62UOneCDRHOQVmPEU6bd3d+IwFPvX4UvALIdXH6X1GaJKyAyq+oPDuIAF+OMe6Ics8x4D56rce4NIRSsxGIUQPVH1BCTESv0IBP8eSsu7fFU5NOpLSS/EihTVC9I2nPJnSyGet7JZP5JvREEYCRe9gPyIqCUViqH39+AI9rNOIRTPttTzlzWdd81jcdzMsygBtFxRaaDneqA6heUYSsc8OdJKQlbaUeJAprkA8xDlXWjzYV27ceCjabpR4EClu7HgIc7UfwyEjGiPDYYsb/cMhBhtDw2EO3sp1+b8vIV0TkjkiwXijckSKIaRzRB33xnivx2RkLmLd7eSDW5BsWVWSLMzDorQ8gNDnvSwcv49/Gnz9PSI3wvmNMwuU060ci0ojwxJV5yr/CVEyzG1T3AAs4bKI9JthQcqcVZkTymTyy1Bvk5IZpss491XzE1ZajJaw5V6vkScoE3/JjxS0IQ6tvcK4SIgFficG0dK4GMi9ZLg4ET29zBwp0a9xiRkkqxakbcUs111AvMpIxjnkWi/Ic1i5scRlNECvwj8drjvhsvP34jGDPOJYDc/PKc3b4Pso+01kqntmQYoosY4GbGI9dSDfOkFuBSIKVLKt/huQQN0bxmikHhCu4XgvIq4pa28wKPStsHqfGgirrkfTvIgcBx8/HHkdfc1wzRBEGy4gzhiIRhPXb4i5u46IG4rck8D8Cj+u0ECUg1qjPd9argQ4n3rQ+7oiazbmLRJ5JV0diriFK4g/fCJjHRa3uKk3wqwkWcaWJdAsesFafABeCznLlaQORtxeQMu4a5CrbpLAEoWyJpl8MGbdBXfUuJeQ+Rt1LK+hiQKpa9t2hvzhezSBuAWorMagBavEdk19pKwHHeVB3mMiviS4m+F7Mh+YlsTlHruVmrOGG9hHGt9wO2f6zcJ75EcU38yjdc+bvHuZ70nLH4nuzUdFzldxQmOMij7R5H7YMcqlQTsTrdOksOygXXVySK2VKcJC/XjxWSZVjOkk202bj0kPe/6G128Zi/hjVEf3quNJxLXePYUPhm9oO0ucqVZSxXWSUfZCuGv8fM8GSFIWepfCPZFPw8vamoVShV2Odd7aspptPkWgomJ2+sUnQ0c/7hl6tpBP5APATTfHcu5Bvt400yEg3U/dQoJUcTAQWnURWHURWlFxq8twXUq70Cesar6eLFNNMS5w6lbGixRjIQyL39DMho0Us9zWzLbuJmMH0Ssbg4kDvbIKmDjSKzt2k1XZ0yvLgAk4zwpMHKyVdLqxqxytlTy7sTe4XLq2ZpJRItN3tmeS5cFkfyaZEUx2Z5JtweRwJpkITHZmkvXA5GAmWSASZntP088nEqbHmd5vuQyQaAwBGQkDz4NNMlwGMOyGFCVAeulM/8a3G/KFPX3rm25Igi1NP6FIGNx9TT+vbsgOAiTFn5p+wuAUIZLiuqZfkDHEey5sg3ww4cY2qDWGEAdz2WAC5iqNIbrAHH34AwHLEF7/WroSXxteJ0Z6DG8vXl1ceoxnIysojyvL+Rurdh531gW0eaW8q/he6NA7sPUXs6aN8ozjFXcOvUvfCB+cHZqhd+gyK2Dl2OIydiwBE27jigG81LP0srpWvNSNoZm32+GDiObW6jzGjjGsHAouXWYJ5taXa/5PXBz6K6VnNTeezBxXXMYYTvDdZsNPHta26PydGKu0J2luUo1dy7CNIl5+xmdWJ+nXSvevHzFDTF4jaTl2m8HhpiKllc224aU6GlgLeEyUWSSTVrRw99AzY2zaO56XlblbWz8K8nHQmnb4XVxImSAPfMXvjVsXM3e+g7lpC43j2jMbw5hS+u6z1hLAmNnuG7Lnfq9QW/IT7qdHQWMAs0OaF+JbuP68H+xUmSjTP7ImjlNV2onlkX252QmcLGtHCgwLVNot5JHNudhbbxUExhlXFM3rJliSeOZzhhwKHHV3+ZJ4lr+kYVXdVMiltmQ7ts7tU4oSoIcgQDUA9kS/I7PEtAlsiwY7
*/