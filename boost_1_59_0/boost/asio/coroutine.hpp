//
// coroutine.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_COROUTINE_HPP
#define BOOST_ASIO_COROUTINE_HPP

namespace boost {
namespace asio {
namespace detail {

class coroutine_ref;

} // namespace detail

/// Provides support for implementing stackless coroutines.
/**
 * The @c coroutine class may be used to implement stackless coroutines. The
 * class itself is used to store the current state of the coroutine.
 *
 * Coroutines are copy-constructible and assignable, and the space overhead is
 * a single int. They can be used as a base class:
 *
 * @code class session : coroutine
 * {
 *   ...
 * }; @endcode
 *
 * or as a data member:
 *
 * @code class session
 * {
 *   ...
 *   coroutine coro_;
 * }; @endcode
 *
 * or even bound in as a function argument using lambdas or @c bind(). The
 * important thing is that as the application maintains a copy of the object
 * for as long as the coroutine must be kept alive.
 *
 * @par Pseudo-keywords
 *
 * A coroutine is used in conjunction with certain "pseudo-keywords", which
 * are implemented as macros. These macros are defined by a header file:
 *
 * @code #include <boost/asio/yield.hpp>@endcode
 *
 * and may conversely be undefined as follows:
 *
 * @code #include <boost/asio/unyield.hpp>@endcode
 *
 * <b>reenter</b>
 *
 * The @c reenter macro is used to define the body of a coroutine. It takes a
 * single argument: a pointer or reference to a coroutine object. For example,
 * if the base class is a coroutine object you may write:
 *
 * @code reenter (this)
 * {
 *   ... coroutine body ...
 * } @endcode
 *
 * and if a data member or other variable you can write:
 *
 * @code reenter (coro_)
 * {
 *   ... coroutine body ...
 * } @endcode
 *
 * When @c reenter is executed at runtime, control jumps to the location of the
 * last @c yield or @c fork.
 *
 * The coroutine body may also be a single statement, such as:
 *
 * @code reenter (this) for (;;)
 * {
 *   ...
 * } @endcode
 *
 * @b Limitation: The @c reenter macro is implemented using a switch. This
 * means that you must take care when using local variables within the
 * coroutine body. The local variable is not allowed in a position where
 * reentering the coroutine could bypass the variable definition.
 *
 * <b>yield <em>statement</em></b>
 *
 * This form of the @c yield keyword is often used with asynchronous operations:
 *
 * @code yield socket_->async_read_some(buffer(*buffer_), *this); @endcode
 *
 * This divides into four logical steps:
 *
 * @li @c yield saves the current state of the coroutine.
 * @li The statement initiates the asynchronous operation.
 * @li The resume point is defined immediately following the statement.
 * @li Control is transferred to the end of the coroutine body.
 *
 * When the asynchronous operation completes, the function object is invoked
 * and @c reenter causes control to transfer to the resume point. It is
 * important to remember to carry the coroutine state forward with the
 * asynchronous operation. In the above snippet, the current class is a
 * function object object with a coroutine object as base class or data member.
 *
 * The statement may also be a compound statement, and this permits us to
 * define local variables with limited scope:
 *
 * @code yield
 * {
 *   mutable_buffers_1 b = buffer(*buffer_);
 *   socket_->async_read_some(b, *this);
 * } @endcode
 *
 * <b>yield return <em>expression</em> ;</b>
 *
 * This form of @c yield is often used in generators or coroutine-based parsers.
 * For example, the function object:
 *
 * @code struct interleave : coroutine
 * {
 *   istream& is1;
 *   istream& is2;
 *   char operator()(char c)
 *   {
 *     reenter (this) for (;;)
 *     {
 *       yield return is1.get();
 *       yield return is2.get();
 *     }
 *   }
 * }; @endcode
 *
 * defines a trivial coroutine that interleaves the characters from two input
 * streams.
 *
 * This type of @c yield divides into three logical steps:
 *
 * @li @c yield saves the current state of the coroutine.
 * @li The resume point is defined immediately following the semicolon.
 * @li The value of the expression is returned from the function.
 *
 * <b>yield ;</b>
 *
 * This form of @c yield is equivalent to the following steps:
 *
 * @li @c yield saves the current state of the coroutine.
 * @li The resume point is defined immediately following the semicolon.
 * @li Control is transferred to the end of the coroutine body.
 *
 * This form might be applied when coroutines are used for cooperative
 * threading and scheduling is explicitly managed. For example:
 *
 * @code struct task : coroutine
 * {
 *   ...
 *   void operator()()
 *   {
 *     reenter (this)
 *     {
 *       while (... not finished ...)
 *       {
 *         ... do something ...
 *         yield;
 *         ... do some more ...
 *         yield;
 *       }
 *     }
 *   }
 *   ...
 * };
 * ...
 * task t1, t2;
 * for (;;)
 * {
 *   t1();
 *   t2();
 * } @endcode
 *
 * <b>yield break ;</b>
 *
 * The final form of @c yield is used to explicitly terminate the coroutine.
 * This form is comprised of two steps:
 *
 * @li @c yield sets the coroutine state to indicate termination.
 * @li Control is transferred to the end of the coroutine body.
 *
 * Once terminated, calls to is_complete() return true and the coroutine cannot
 * be reentered.
 *
 * Note that a coroutine may also be implicitly terminated if the coroutine
 * body is exited without a yield, e.g. by return, throw or by running to the
 * end of the body.
 *
 * <b>fork <em>statement</em></b>
 *
 * The @c fork pseudo-keyword is used when "forking" a coroutine, i.e. splitting
 * it into two (or more) copies. One use of @c fork is in a server, where a new
 * coroutine is created to handle each client connection:
 * 
 * @code reenter (this)
 * {
 *   do
 *   {
 *     socket_.reset(new tcp::socket(my_context_));
 *     yield acceptor->async_accept(*socket_, *this);
 *     fork server(*this)();
 *   } while (is_parent());
 *   ... client-specific handling follows ...
 * } @endcode
 * 
 * The logical steps involved in a @c fork are:
 * 
 * @li @c fork saves the current state of the coroutine.
 * @li The statement creates a copy of the coroutine and either executes it
 *     immediately or schedules it for later execution.
 * @li The resume point is defined immediately following the semicolon.
 * @li For the "parent", control immediately continues from the next line.
 *
 * The functions is_parent() and is_child() can be used to differentiate
 * between parent and child. You would use these functions to alter subsequent
 * control flow.
 *
 * Note that @c fork doesn't do the actual forking by itself. It is the
 * application's responsibility to create a clone of the coroutine and call it.
 * The clone can be called immediately, as above, or scheduled for delayed
 * execution using something like boost::asio::post().
 *
 * @par Alternate macro names
 *
 * If preferred, an application can use macro names that follow a more typical
 * naming convention, rather than the pseudo-keywords. These are:
 *
 * @li @c BOOST_ASIO_CORO_REENTER instead of @c reenter
 * @li @c BOOST_ASIO_CORO_YIELD instead of @c yield
 * @li @c BOOST_ASIO_CORO_FORK instead of @c fork
 */
class coroutine
{
public:
  /// Constructs a coroutine in its initial state.
  coroutine() : value_(0) {}

  /// Returns true if the coroutine is the child of a fork.
  bool is_child() const { return value_ < 0; }

  /// Returns true if the coroutine is the parent of a fork.
  bool is_parent() const { return !is_child(); }

  /// Returns true if the coroutine has reached its terminal state.
  bool is_complete() const { return value_ == -1; }

private:
  friend class detail::coroutine_ref;
  int value_;
};


namespace detail {

class coroutine_ref
{
public:
  coroutine_ref(coroutine& c) : value_(c.value_), modified_(false) {}
  coroutine_ref(coroutine* c) : value_(c->value_), modified_(false) {}
  ~coroutine_ref() { if (!modified_) value_ = -1; }
  operator int() const { return value_; }
  int& operator=(int v) { modified_ = true; return value_ = v; }
private:
  void operator=(const coroutine_ref&);
  int& value_;
  bool modified_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#define BOOST_ASIO_CORO_REENTER(c) \
  switch (::boost::asio::detail::coroutine_ref _coro_value = c) \
    case -1: if (_coro_value) \
    { \
      goto terminate_coroutine; \
      terminate_coroutine: \
      _coro_value = -1; \
      goto bail_out_of_coroutine; \
      bail_out_of_coroutine: \
      break; \
    } \
    else /* fall-through */ case 0:

#define BOOST_ASIO_CORO_YIELD_IMPL(n) \
  for (_coro_value = (n);;) \
    if (_coro_value == 0) \
    { \
      case (n): ; \
      break; \
    } \
    else \
      switch (_coro_value ? 0 : 1) \
        for (;;) \
          /* fall-through */ case -1: if (_coro_value) \
            goto terminate_coroutine; \
          else for (;;) \
            /* fall-through */ case 1: if (_coro_value) \
              goto bail_out_of_coroutine; \
            else /* fall-through */ case 0:

#define BOOST_ASIO_CORO_FORK_IMPL(n) \
  for (_coro_value = -(n);; _coro_value = (n)) \
    if (_coro_value == (n)) \
    { \
      case -(n): ; \
      break; \
    } \
    else

#if defined(_MSC_VER)
# define BOOST_ASIO_CORO_YIELD BOOST_ASIO_CORO_YIELD_IMPL(__COUNTER__ + 1)
# define BOOST_ASIO_CORO_FORK BOOST_ASIO_CORO_FORK_IMPL(__COUNTER__ + 1)
#else // defined(_MSC_VER)
# define BOOST_ASIO_CORO_YIELD BOOST_ASIO_CORO_YIELD_IMPL(__LINE__)
# define BOOST_ASIO_CORO_FORK BOOST_ASIO_CORO_FORK_IMPL(__LINE__)
#endif // defined(_MSC_VER)

#endif // BOOST_ASIO_COROUTINE_HPP

/* coroutine.hpp
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
*/