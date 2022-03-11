//
// coroutine.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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