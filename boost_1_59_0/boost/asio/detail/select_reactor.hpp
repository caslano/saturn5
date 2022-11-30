//
// detail/select_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SELECT_REACTOR_HPP
#define BOOST_ASIO_DETAIL_SELECT_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) \
  || (!defined(BOOST_ASIO_HAS_DEV_POLL) \
      && !defined(BOOST_ASIO_HAS_EPOLL) \
      && !defined(BOOST_ASIO_HAS_KQUEUE) \
      && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#include <cstddef>
#include <boost/asio/detail/fd_set_adapter.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/reactor_op_queue.hpp>
#include <boost/asio/detail/scheduler_task.hpp>
#include <boost/asio/detail/select_interrupter.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>
#include <boost/asio/detail/timer_queue_set.hpp>
#include <boost/asio/detail/wait_op.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/thread.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class select_reactor
  : public execution_context_service_base<select_reactor>
#if !defined(BOOST_ASIO_HAS_IOCP)
    , public scheduler_task
#endif // !defined(BOOST_ASIO_HAS_IOCP)
{
public:
#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
  enum op_types { read_op = 0, write_op = 1, except_op = 2,
    max_select_ops = 3, connect_op = 3, max_ops = 4 };
#else // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
  enum op_types { read_op = 0, write_op = 1, except_op = 2,
    max_select_ops = 3, connect_op = 1, max_ops = 3 };
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

  // Per-descriptor data.
  struct per_descriptor_data
  {
  };

  // Constructor.
  BOOST_ASIO_DECL select_reactor(boost::asio::execution_context& ctx);

  // Destructor.
  BOOST_ASIO_DECL ~select_reactor();

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Recreate internal descriptors following a fork.
  BOOST_ASIO_DECL void notify_fork(
      boost::asio::execution_context::fork_event fork_ev);

  // Initialise the task, but only if the reactor is not in its own thread.
  BOOST_ASIO_DECL void init_task();

  // Register a socket with the reactor. Returns 0 on success, system error
  // code on failure.
  BOOST_ASIO_DECL int register_descriptor(socket_type, per_descriptor_data&);

  // Register a descriptor with an associated single operation. Returns 0 on
  // success, system error code on failure.
  BOOST_ASIO_DECL int register_internal_descriptor(
      int op_type, socket_type descriptor,
      per_descriptor_data& descriptor_data, reactor_op* op);

  // Post a reactor operation for immediate completion.
  void post_immediate_completion(reactor_op* op, bool is_continuation);

  // Start a new operation. The reactor operation will be performed when the
  // given descriptor is flagged as ready, or an error has occurred.
  BOOST_ASIO_DECL void start_op(int op_type, socket_type descriptor,
      per_descriptor_data&, reactor_op* op, bool is_continuation, bool);

  // Cancel all operations associated with the given descriptor. The
  // handlers associated with the descriptor will be invoked with the
  // operation_aborted error.
  BOOST_ASIO_DECL void cancel_ops(socket_type descriptor, per_descriptor_data&);

  // Cancel all operations associated with the given descriptor and key. The
  // handlers associated with the descriptor will be invoked with the
  // operation_aborted error.
  BOOST_ASIO_DECL void cancel_ops_by_key(socket_type descriptor,
      per_descriptor_data& descriptor_data,
      int op_type, void* cancellation_key);

  // Cancel any operations that are running against the descriptor and remove
  // its registration from the reactor. The reactor resources associated with
  // the descriptor must be released by calling cleanup_descriptor_data.
  BOOST_ASIO_DECL void deregister_descriptor(socket_type descriptor,
      per_descriptor_data&, bool closing);

  // Remove the descriptor's registration from the reactor. The reactor
  // resources associated with the descriptor must be released by calling
  // cleanup_descriptor_data.
  BOOST_ASIO_DECL void deregister_internal_descriptor(
      socket_type descriptor, per_descriptor_data&);

  // Perform any post-deregistration cleanup tasks associated with the
  // descriptor data.
  BOOST_ASIO_DECL void cleanup_descriptor_data(per_descriptor_data&);

  // Move descriptor registration from one descriptor_data object to another.
  BOOST_ASIO_DECL void move_descriptor(socket_type descriptor,
      per_descriptor_data& target_descriptor_data,
      per_descriptor_data& source_descriptor_data);

  // Add a new timer queue to the reactor.
  template <typename Time_Traits>
  void add_timer_queue(timer_queue<Time_Traits>& queue);

  // Remove a timer queue from the reactor.
  template <typename Time_Traits>
  void remove_timer_queue(timer_queue<Time_Traits>& queue);

  // Schedule a new operation in the given timer queue to expire at the
  // specified absolute time.
  template <typename Time_Traits>
  void schedule_timer(timer_queue<Time_Traits>& queue,
      const typename Time_Traits::time_type& time,
      typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op);

  // Cancel the timer operations associated with the given token. Returns the
  // number of operations that have been posted or dispatched.
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
      typename timer_queue<Time_Traits>::per_timer_data& target,
      typename timer_queue<Time_Traits>::per_timer_data& source);

  // Run select once until interrupted or events are ready to be dispatched.
  BOOST_ASIO_DECL void run(long usec, op_queue<operation>& ops);

  // Interrupt the select loop.
  BOOST_ASIO_DECL void interrupt();

private:
#if defined(BOOST_ASIO_HAS_IOCP)
  // Run the select loop in the thread.
  BOOST_ASIO_DECL void run_thread();
#endif // defined(BOOST_ASIO_HAS_IOCP)

  // Helper function to add a new timer queue.
  BOOST_ASIO_DECL void do_add_timer_queue(timer_queue_base& queue);

  // Helper function to remove a timer queue.
  BOOST_ASIO_DECL void do_remove_timer_queue(timer_queue_base& queue);

  // Get the timeout value for the select call.
  BOOST_ASIO_DECL timeval* get_timeout(long usec, timeval& tv);

  // Cancel all operations associated with the given descriptor. This function
  // does not acquire the select_reactor's mutex.
  BOOST_ASIO_DECL void cancel_ops_unlocked(socket_type descriptor,
      const boost::system::error_code& ec);

  // The scheduler implementation used to post completions.
# if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_type;
# else // defined(BOOST_ASIO_HAS_IOCP)
  typedef class scheduler scheduler_type;
# endif // defined(BOOST_ASIO_HAS_IOCP)
  scheduler_type& scheduler_;

  // Mutex to protect access to internal data.
  boost::asio::detail::mutex mutex_;

  // The interrupter is used to break a blocking select call.
  select_interrupter interrupter_;

  // The queues of read, write and except operations.
  reactor_op_queue<socket_type> op_queue_[max_ops];

  // The file descriptor sets to be passed to the select system call.
  fd_set_adapter fd_sets_[max_select_ops];

  // The timer queues.
  timer_queue_set timer_queues_;

#if defined(BOOST_ASIO_HAS_IOCP)
  // Helper class to run the reactor loop in a thread.
  class thread_function;
  friend class thread_function;

  // Does the reactor loop thread need to stop.
  bool stop_thread_;

  // The thread that is running the reactor loop.
  boost::asio::detail::thread* thread_;
#endif // defined(BOOST_ASIO_HAS_IOCP)

  // Whether the service has been shut down.
  bool shutdown_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/select_reactor.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/select_reactor.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP)
       //   || (!defined(BOOST_ASIO_HAS_DEV_POLL)
       //       && !defined(BOOST_ASIO_HAS_EPOLL)
       //       && !defined(BOOST_ASIO_HAS_KQUEUE)
       //       && !defined(BOOST_ASIO_WINDOWS_RUNTIME))

#endif // BOOST_ASIO_DETAIL_SELECT_REACTOR_HPP

/* select_reactor.hpp
Cp0RMCKuslqF/MklTMWBEC4jNb0LrOx6o/lt3Ds5Vk+mClnvPHEgHtoyGdnxwfgU7McZ+8n60Nx2MG5YfLbgNNBUh/EhItRnY4AJH0my1jdoN0A2bx6BCofibh/G1s/Ge3lx2o3oS/t3rQoZSoxJEKz49VaO2UhvHt7OvClhvALVx35Qd1otdW17HTcpfmHI75kmlTU9J7pXBIvZFzgIBUgiI1dpmQINS/OZSYnx9uM2POA4xUnI505OsS7lQogSTbDz5NseTguqzb4uTOHLlhy6eKhrc9QSdaKD+8Is0hnT1cGIv/Pqz5P4OupH1JZssDmKIJgZ7VMflLuUlaofOqeGoadnkozuujbVOU8hhXLhiVY+MD+in0jzvNhde4EIjGcHgyPZSjY0vsknRE1PYGBooC7gTMRGOMhTSSyonKC9Zu5SngyKDILTM/etSLWrZx+0cGAWbDN3REMk4voOTtZeLIdKMqYxTWIYfS6hXyYGEKAoXpQddwBP51FKVyUFR8gK0qiYm8g2q3AKn+GAVCMLTvSAK6B3gkkT4arocNOpYMn5YT3Dpfzb8/0jpaOnH4gHW3sb3NabLWgxocNh9UCyXe3LwJDuY3Hg06xKh1FZGd0YRxdiTRSuh3lNN4lh1YqscywF8BXgRjDfLztC1kw7tQyDwfNgZIdk0yJn0opV1zkHBKn7XW1fsH7ZwUm+MxI8oToIe08inKzD0PW2orfMuWQ7cbp+Oos2W24VqKY5nhNOqcLEHP8kLN6pC065WrAweOpqE1lLZByBavp+BD+3j/teohsxPlxWg4BhoS37P2KNsmSuwcv7evXTIBkvjqN9Cpj85D0LtBHLb7ZqXA+9oN35WklZPNYxDP/kMZsW72gptYlpXlW21LBJgO95++mlnlXEGrLwyNMgEOFvCOJfhLIVgHAMpumTKbAZbV5xMKSxXO9ShB3L6r4A6p7pHNw7c3jsuBCZjBI9ocYtOVYMXdqWXnaztEz7IkuGjVovllHlHt4Wok0We5/esqIn/9W4oeUHcthXj3INEApwV6uzuGMKDvZ90yxv2Ckr55N1O/YeP7SfbPBk+N4nJV6RqF28BL4Gm21kJV4y8RDTJMIPaSVQ2CoI33OfuEqvNzxv5guuEG6b61ggi9sBkb3wXGHT7LY+SczvCiSZYuN/QzfG+TPy4ShCYQtHUEidHlN8vdCvcEE6/L53t2+WhHxWUhJaJh+DZ7Frcl1h3a+zqKreFRifoWWKgPPnJAiTkkFpr2GT9lCThS1/CrVHTZnHvNAa25GnZantbzGPLpIpMpDiPdB4pGpL8zskW8V4sKaZAD97e3O9FcoTh1YJDaYZ5Br6hm8JSltQGVc1sSM6fGZTYEng/ClU1Z28GzBqSXI9BHJ39A8I9MJnjkHhqynxe0eLs12x4ypJ+HzXsBjbxgrMljH9Jwy3kuOb0vpqfqz3+iiRCA0daQZZ3VSRzkKYcQfYzPTKKgjqwteoMzWmf9yi9xLq4OVxBSE1BPZ6+6rB7LV6GAIs/dm9sDZM4XwChjzz9b46Adrh3VXzt+JzOBQLPG2/4yqn07uNKSeigiSBANuJBieOqSA0MoKe5vxgInfpACc+ZfqjV+DafWuoOFKuJO4zF+Vsv4e67IFeyEicW8CrhitvYFUpvAHDnRHszltMrwqZ6ys/G1lEAAIs/dO/81YYzdLMaGriqV/D3jAiRYsvjI95YU4ac9Al9DcjjkS2kjDLsjfzzaSRY4D9JLG8s9KZqRtsYo9rHQ8jpQMPz5eHndcrjEzf5lmIKY/JaZsL0bn2C4uDEfwM0ggz7IY+NQ9lH1m7Es1rpyFXcBuvNbQtgA1QYuEdsdrZywQp5fRVUpjCuXlzD6nZmPk3CzR0VOL6UGrzOlUOYMXhu/Rfcz1KY4HX2cPo6zuePw4BPP0DMAB/0jZ9G65FjSp2uRy+HwYxUv9FVwg3PS5LB+oSg11yTEALLkv0f4XUQMkElk+w/BnSEF33Mcw5ea7SAVRi0wgYPEOeBknXqbfGKF00NzJ2SRNTOiuJLrDtVD8c/0hFkBGasqW8J/Pc75CmPQoucYiiFVhdQ3jytSlLDGemV98TlxYQ3ury6BWylj7qv3c5PSjr6ijekcSphAhuNRc6UKH+NCA1WlYQNeJqwRXDhITJPyLnnKfDWBRhs+5rLPTEhHjRCwAAzNJ7sEbqr4KvykFIgXuADUamGaXhktPk/Jaj2MkZ3ZTSF6an6GOiSgWGZA0ZRUCemuuxZ7AJJAVd1UZ5njt8Krxeu6ghIHS86z+qANdhg9Jf/kxDVQxalG/qB8Vncjlj0N/jZfLirDwhxqblGorw6Hc3r8vO0f83I2lT4ZhVDchhkUKKo4WkPV1YSOiKACSq60P0d18BTQumNQ2P+/WWrErARlxHLauInMRwoSQYh/nSSXoLIcd6CmOfRKsEiGbo9vlfDj4s22ddnoYiKW1X9MlnX95a+D55fTRwJ7+6zTWFh+vhedI6R/I0j6vtj0eEARpy67i6k1vKWGb8JbqIVZtICmboNDWTRlDDuckAtzsk3IKNNry0OzoOg4ijdZd9/F9m6DYxkUD32YdXW5wULsaYbQJQ43WSJcqVU7IO7ZoMJHQLjEch/T9smdOaeiZLLai2rAT5NAbrs4Cg7bFyiu/5lhCnC1ri7ZBcWINJXqZ2J+83MyO5O3E6eLnPO3q5i3zSSJz0Hmyb+Fp/wgx6cLEQoWLU9vyDhzfodvpOwKVZg+Pfe4D62KeBOHtqJjsDZkBw7lBe7CDeq7C5A2YYjDsFWQplnX1HDp5lhMdoG1dJs4SGrFAelwzbQ6ht7bsH/iaJE6CWk5dejHMOkdvq9wC2FO6thVA3z35uzUwiu9Q5/1lZ0XUmsqOHteiutEbPIqOfUAq3HeWI+7dyYiKgx50eL3XLARmN4S4V4zNquJUL8JOyPGVEH/voNLof6RFPX3AUdaH2aSB5WDMS8fDRY3cnteVu+ZPTfrEEYxdxMEalLYCQnaLj/ldQx5qgJyO9y/6zA6xEK9l6Wk7/U5A1JEhHgzUeBndHrbqT668MXZKGkngBF3NubcZq1MjdeCEL+VuUt5v+6zoWdhiLr0lD2DrtFoZVO5X9rVVfBvIAZqRXVTMROkBQPV8rNZZHwolh5sULsQ2Df2du7uup9MHVulOjV9lWcxGceTenD36z3NLLGm6O3nHHlmoYRcNOMp24eViByFwjVhW2R541ufRJKj2HlvS83czaeJhz4xSkU5A73kooia0Ul8WhIxXbNCb/JS/8u2630o1SWENaBKm+794VISioQM0ycA1wcToslBVxhAjjVQ7YCFZ84dO/barWSvu/vSAlaPEb7Hlg29vyJbcH2tyWmvy+p7UHaRkjEW9G/vcyM0fVffkkrSZftuWEb1SfoUxeR1A36LJ/jBoHilreniOCDiT2Qj7FgM3ExSTsoDQEtdnvY7cZioEQJA772XkTcKUQMslsJ5LyzK4yGV7NwimFxmyB4KZbsCiNvk1KiDbAYNsyeaeTyf3XCsUQgVk8Akst2m1r3qOkLa9uy3tHxuyysIDS29A7PKRXb0bbPrzljOnPOwA3yTmTkHGCAfK4jAlTxSy9FktumcGY0kL0m/7FbVwkVzYX44UDkkI+1MuoT6ABkdWvvpwKfZJ9kUFCAVkAmos3ht9nnofyuM7YCv4LGFELosGSzcMfIrSD1l5pyRvnb9LVxj80OeFWaHdwRMaDwkLHTBEUT6vgLoMv0L8NnvHwQvY11ozMumK0XF5fuCO0AP1z2DQ4whroemdVMR/WcQj76rR518hYwzo6p938sMbhSMemd4flYTa8b/45hgOfQyvNELAsn7H2CY4HATnC78cIRZWqiDfDIZvQTVtRCQLezlFpcZb2V6L7g8OqaaB//5L7eVguzByaseiAShU1TYdjShPa97UeQNLcHIhhEcRKIDNuW76SgwjuAejVFC2ND49EzrImnDfwo+DYtzVJpH/l1XmaXnT8pUmuZDhO2tJJx38MRFKsAkdIBJ1Oj05aQPbss7SskNSuho1opBirHejB1H7HSz19nIniSkj95jLlxYpQuOrjC0xbbkX2D171FWeOPTJbHdiDa2FJIL+IuSUxxK2WHgLwv1DDURK+hlUKuUxCuHEUhaw4PwGo9+bKzOJDYcAxhs7ecsbz0ptmheogoqrJHKKNcOrmel1SipnlkJFJNy4HbOJ3UdX1g5vlLR2cO1t5BXOT4eX4vr9k9OXdiKYi5Kh2JuG5FBjTqAy0XLmHAJ+39ZCIG06FT+5vjmqjFwqFuk0UdVqh9eY4NnjQifu7C1l4eZ35pXpngp0KKx/5fTPRic/gqLKKWzUhX5lX+uEv2k3aJZBTt7DypGZ+7eOBw6P0boUMFnrKCWPBwLHNb3uwIXVEo+PvAnPkpUNHEG9oEp2Bp49AMxZNRxBPClv2A4KMCJz09bT3eK2Abq9BOl3kIeSEdflrUKHq2H8mp0LixWuGcutb+8tHM/UrpxuKRKTZYoCJqptC92U38YU2kFqq6jQeCq6oX9TZjnCaKvbY5jZVtIdK12QF3lC4d5C20FK/CnQk+nPPxg7q1OUhK4bzPRdck1EUt3UiLw2gk7jt0arDWPhIrS0bpINK/m3O2OLH31lvzn3Zp8Um7BkE37WI31Bk2ijIpUmX2BcK6otyuX9PEbGF714x/L3+Qo3W1WcsxFGs1wJ1UOxHdhFsPPGJ+loqH0+BcPtxqfh6Tgws5tWc5t9UPg4JCXs1HzChrYTYLMaGF3pzCpsOy1qqegkH+EwQzXHdIoslQZ/mx4c/0DUN9OlYPmP0xUkL8qa8YhYC1OjGbSul2HIdWtVyVjZi0YvEhbNB09hS6jdG5L2zZgWdOpHBir5LwC2SLGKDtF77ixgY4MIzxIiDmiveMK43B+H1JH+p1cMoUIiV0B/5YViKGiSnGI9hgmXSR9d2WBwGwhKC0Rd1lkd+E5xHZ1/vDosnMzOdb3n/TyE8puUQDnpnvZ6Ir1lvIIfgaupKQNHy+SDjYnMzWaRsQ8ox6+2KOS+EQsuJitmeUwchG6axNxwBz422M/GNQomhI6mYtVMZPH2lbuLEr8TRntgYD+PYKaTf/l//AC0OEf0umox778fmhA0huzV36ELo2qbZHmsyO8pzfeJeoeHbfJ3+DfpInLxGm/WiDtLpo2w+al8QYfSi/RBfT1J4io2Y0VfoV6YIXeMD/GYK78yqg6IxjVW8RbYKcYSc2i40qRt12qqjceZdFATDxwl1CNnFxpV8+wij9vEMIoTCKEKdjiJAO4O1IUxmVRsh7R4BsxdP0HbMmYwCVshoVRP9Cs/ObqCjDKjSQMsWpcUTlcF+QHhj1Kj/GCkYSn2L3AoQhpfKvHQjOJ8Hbm7BzHq0Sno2t35OSJEDmcqU+0D2th9sQ2agUqYOZhL+soJakpaB2E4xGXtvoTPDVr30Tqu8dVwKdIwdaMu27sWlQMPhVKND4wus455rtFpCzOZ4uXUTXCFS2cNsf+nejBU7wjIHqMXbfSPcDqbo0pB/bczhR9RqZE49yNQ1lRz4Wu07i6/H5tX9ColCpVNOjA3yG9+uolnlbNFJOGBxmg/zDjwMN+bB5s6oaRduYgf9LIqrMWcOSOZYSWBoEhhpDtuJ7vCjYpJtf7s5T9iGiNpa5LSpafnrOmwf+OOqg6u8eg+Mq9UCQ4ZFii39CmaAELGbiJFpchiQx9FqpPtFepmTE9Pgn+skvSyAMcBgZbqXdx27wXnOTfgf+JZnrqF7sSj9Acn+/s84RFtrv8is0YEvsa3h4We9ieaEQIxvmg3QF7t1VunbHvX3FmOt5R17m1o/ncCvHZPx4fud2DM9yAKIBzyYJz3GqvsUwgtgMggf//uSHeGwD6VnPeY3qQ+a79wQeeOD9xs2B4dvgLcZjL5AoZ/M5Lq+nye6Nz90JDw/p9DPB0jqgawqPjOfSy4dq9uS9/Z49UqPh2YfET4m92Ah7Boi01AaRZ36B2iIU2fId++ti/3rdn/+k1rZXjHrj9Nx9JUI7nAI58p0uTio7vSjn4u8735//Tc+hZ1L7Epuv553U4M9Y6MD/a+XCrvmHx2fhh+qp6n+e7KXqSmC8SGa6f6x/oEhgr4hWtJ+0mGKcSJKyukp2sm+/iFa8f6ZaYLpsWES6smBMQLS/knaaUrKSRrSSerxgSmC6cmh6U+1LTawEz2nHbzvNR87/4CDT10c+/neXge/k7uUvl6ImJ8SLDLBLyvcrKiksAe+BLCT/VefLxe47xmZb1+46eGByc8WbndKPZIj/Iy/70M4Tgdh82yGX6N0mpz6wa3Wpx32SmYAjI5y8PQR0uO7SUZWVmcooJqRvR8bA1/6x6D9H3T71S+2KHZRoaI3Q8UVc8gzwvonVi2p7yec0jJXsWrGNx7TJfvgXydYaQ165zS95I/DFkpRF0tO++uDayF/Q2HcNt7YG2JQxopCUi78wQEHCl3cQAS7YgV8dajSYtkLM3W4+YcU59KUIlUO7oAzn1K6iLrUoqBLiKNP3qe/MLyfUNVmtEKWtr7bvwpA5Hyq73Hgq82SJhhOMxWCty4lGzTkBy+1P7oCVZaegBNO2q7XGj8UrILfE3B21WtXTgpLqvJYIp/Q3agiqmGJ6R6Ba+jPCp/10TTMUIfNfMhG81jXhtk47JNHwNVR0Gdv5fWtY+zTo1Q8YZOonEhOdiDaZVYcU70bXDkV0cC7PDsWZgrFmzC5O6aQTw0sDdUaAJLb0jM3QI6jhg5ykb4w4a3rBap3a9sQM+DKkOdiX6L+0dERG9eTbGK6OtSizV605nlOuqaIEVnCpcjS9bNXtfF0S2aBGlPyEnd2LeNhgFefbwfds7+PU7pzpe3ypg4q3TDFkDKVaVw4LsbztYRjIb0z52fTPdBenMYYscx91GDXbtn06aRoxmHzPt+gwXxIj0Yr34qKkthrq7G13WoZ0NLCcGNFzKT5tkMrVzh6QnajKjfkRGX2VkMQnWqIy/dcj9AmXdG/z/1zJTkouy1bL+hk9PnoVUfWTyxyPjx0nf6jt8Ywv2vBzT//E/wZOyRtqYGrtv44eTBlbpq4FP9GdZ2Bi9K8XhteqlRGKk8b0gsoC/5iOTR9cmfgJ//zRTNz4dEkNYtV1hrTzxr9lWw8r4j/cSlb5dIsWZSqEAcTmgiaK+4/zw9ckdFJ5ztLOJ4kyysZwTCt9selln6tiMs/GMRw2JpK0WF0Aa0tidhiAiXBeEHunB9K83WestNBi2eo3KEsxtVzpmuD0Run39UYhGb0RzMJ8mfKsBFh02t1UPxMKxLSjRw3UD5C48TMoofF+dZOAib+jV3kD8B4nbT7J8BXiab6zocqY6Jpw6pU47goHLF3cZfWW22Eyv1GvF5ZEOiDmb0GFktEoYOTcMumMUrE1UurYSBo5tIT4rzGlhOmy+xhmsHnoatxuXs3g55fMr1lbhLjdqpND5IMhJ+ijs7eSUUIqE3UBN7innR2fprOJ/hEs91UjiN4Cgz99CFkk3/0ARZvZ1Bu76JusWOeuqNP6nO/CsVJCO+FzeHgVmYYZaArL91CJEAkiIN/IYDEGnm/UkITlWmplTwk3HGcIfp980XmRI7tqeYm
*/