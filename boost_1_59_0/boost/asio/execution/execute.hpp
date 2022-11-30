//
// execution/execute.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_EXECUTE_HPP
#define BOOST_ASIO_EXECUTION_EXECUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/detail/as_invocable.hpp>
#include <boost/asio/execution/detail/as_receiver.hpp>
#include <boost/asio/traits/execute_member.hpp>
#include <boost/asio/traits/execute_free.hpp>

#include <boost/asio/detail/push_options.hpp>

#if defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

/// A customisation point that executes a function on an executor.
/**
 * The name <tt>execution::execute</tt> denotes a customisation point object.
 *
 * For some subexpressions <tt>e</tt> and <tt>f</tt>, let <tt>E</tt> be a type
 * such that <tt>decltype((e))</tt> is <tt>E</tt> and let <tt>F</tt> be a type
 * such that <tt>decltype((f))</tt> is <tt>F</tt>. The expression
 * <tt>execution::execute(e, f)</tt> is ill-formed if <tt>F</tt> does not model
 * <tt>invocable</tt>, or if <tt>E</tt> does not model either <tt>executor</tt>
 * or <tt>sender</tt>. Otherwise, it is expression-equivalent to:
 *
 * @li <tt>e.execute(f)</tt>, if that expression is valid. If the function
 *   selected does not execute the function object <tt>f</tt> on the executor
 *   <tt>e</tt>, the program is ill-formed with no diagnostic required.
 *
 * @li Otherwise, <tt>execute(e, f)</tt>, if that expression is valid, with
 *   overload resolution performed in a context that includes the declaration
 *   <tt>void execute();</tt> and that does not include a declaration of
 *   <tt>execution::execute</tt>. If the function selected by overload
 *   resolution does not execute the function object <tt>f</tt> on the executor
 *   <tt>e</tt>, the program is ill-formed with no diagnostic required.
 */
inline constexpr unspecified execute = unspecified;

/// A type trait that determines whether a @c execute expression is well-formed.
/**
 * Class template @c can_execute is a trait that is derived from
 * @c true_type if the expression <tt>execution::execute(std::declval<T>(),
 * std::declval<F>())</tt> is well formed; otherwise @c false_type.
 */
template <typename T, typename F>
struct can_execute :
  integral_constant<bool, automatically_determined>
{
};

} // namespace execution
} // namespace asio
} // namespace boost

#else // defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace execution {

template <typename T, typename R>
struct is_sender_to;

namespace detail {

template <typename S, typename R>
void submit_helper(BOOST_ASIO_MOVE_ARG(S) s, BOOST_ASIO_MOVE_ARG(R) r);

} // namespace detail
} // namespace execution
} // namespace asio
} // namespace boost
namespace boost_asio_execution_execute_fn {

using boost::asio::conditional;
using boost::asio::decay;
using boost::asio::declval;
using boost::asio::enable_if;
using boost::asio::execution::detail::as_receiver;
using boost::asio::execution::detail::is_as_invocable;
using boost::asio::execution::is_sender_to;
using boost::asio::false_type;
using boost::asio::result_of;
using boost::asio::traits::execute_free;
using boost::asio::traits::execute_member;
using boost::asio::true_type;
using boost::asio::void_type;

void execute();

enum overload_type
{
  call_member,
  call_free,
  adapter,
  ill_formed
};

template <typename Impl, typename T, typename F, typename = void,
    typename = void, typename = void, typename = void, typename = void>
struct call_traits
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = ill_formed);
};

template <typename Impl, typename T, typename F>
struct call_traits<Impl, T, void(F),
  typename enable_if<
    execute_member<typename Impl::template proxy<T>::type, F>::is_valid
  >::type> :
  execute_member<typename Impl::template proxy<T>::type, F>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_member);
};

template <typename Impl, typename T, typename F>
struct call_traits<Impl, T, void(F),
  typename enable_if<
    !execute_member<typename Impl::template proxy<T>, F>::is_valid
  >::type,
  typename enable_if<
    execute_free<T, F>::is_valid
  >::type> :
  execute_free<T, F>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = call_free);
};

template <typename Impl, typename T, typename F>
struct call_traits<Impl, T, void(F),
  typename enable_if<
    !execute_member<typename Impl::template proxy<T>::type, F>::is_valid
  >::type,
  typename enable_if<
    !execute_free<T, F>::is_valid
  >::type,
  typename void_type<
   typename result_of<typename decay<F>::type&()>::type
  >::type,
  typename enable_if<
    !is_as_invocable<typename decay<F>::type>::value
  >::type,
  typename enable_if<
    is_sender_to<T, as_receiver<typename decay<F>::type, T> >::value
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(overload_type, overload = adapter);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

struct impl
{
  template <typename T>
  struct proxy
  {
#if defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)
    struct type
    {
      template <typename F>
      auto execute(BOOST_ASIO_MOVE_ARG(F) f)
        noexcept(
          noexcept(
            declval<typename conditional<true, T, F>::type>().execute(
              BOOST_ASIO_MOVE_CAST(F)(f))
          )
        )
        -> decltype(
          declval<typename conditional<true, T, F>::type>().execute(
            BOOST_ASIO_MOVE_CAST(F)(f))
        );
    };
#else // defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)
    typedef T type;
#endif // defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)
  };

  template <typename T, typename F>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(F)>::overload == call_member,
    typename call_traits<impl, T, void(F)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(F) f) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(F)>::is_noexcept))
  {
    return BOOST_ASIO_MOVE_CAST(T)(t).execute(BOOST_ASIO_MOVE_CAST(F)(f));
  }

  template <typename T, typename F>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(F)>::overload == call_free,
    typename call_traits<impl, T, void(F)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(F) f) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(F)>::is_noexcept))
  {
    return execute(BOOST_ASIO_MOVE_CAST(T)(t), BOOST_ASIO_MOVE_CAST(F)(f));
  }

  template <typename T, typename F>
  BOOST_ASIO_CONSTEXPR typename enable_if<
    call_traits<impl, T, void(F)>::overload == adapter,
    typename call_traits<impl, T, void(F)>::result_type
  >::type
  operator()(
      BOOST_ASIO_MOVE_ARG(T) t,
      BOOST_ASIO_MOVE_ARG(F) f) const
    BOOST_ASIO_NOEXCEPT_IF((
      call_traits<impl, T, void(F)>::is_noexcept))
  {
    return boost::asio::execution::detail::submit_helper(
        BOOST_ASIO_MOVE_CAST(T)(t),
        as_receiver<typename decay<F>::type, T>(
          BOOST_ASIO_MOVE_CAST(F)(f), 0));
  }
};

template <typename T = impl>
struct static_instance
{
  static const T instance;
};

template <typename T>
const T static_instance<T>::instance = {};

} // namespace boost_asio_execution_execute_fn
namespace boost {
namespace asio {
namespace execution {
namespace {

static BOOST_ASIO_CONSTEXPR const boost_asio_execution_execute_fn::impl&
  execute = boost_asio_execution_execute_fn::static_instance<>::instance;

} // namespace

typedef boost_asio_execution_execute_fn::impl execute_t;

template <typename T, typename F>
struct can_execute :
  integral_constant<bool,
    boost_asio_execution_execute_fn::call_traits<
      execute_t, T, void(F)>::overload !=
        boost_asio_execution_execute_fn::ill_formed>
{
};

#if defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

template <typename T, typename F>
constexpr bool can_execute_v = can_execute<T, F>::value;

#endif // defined(BOOST_ASIO_HAS_VARIABLE_TEMPLATES)

} // namespace execution
} // namespace asio
} // namespace boost

#endif // defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_EXECUTE_HPP

/* execute.hpp
3VcRzoyMuDAAqqyOSUtjenfYNz6mtqxqi6VR+/lvc6/lRKW9etOHYm8eIbXYsqqu2nwjVTz1HzA+98raV70Jt/JrrSOZYfeohjKmjnk7Rn5pZWpyhPghf4sy0cHke3Vx1dzCAl9pzepO5CRSXnXV2HMloPMjnPgY14XIhHNpEwO+v1EkdZWhr2TsbkbgZRnYBElrz0SSpXd+PwV4yIrcRQ+E6CU7Sw9dehSsv2uXXeZnU6u9mJp51Ayz88RWVfzaLi4SSmFqRZquAEh4yc+0IfXJhh+2RWA9AqAj9rpPIBEGc/yD636v+G2zMHjVm/IGuQdHFd5pZc5Gb4R0TxTBE7qPz7sZIIdVuY/nuXjV8wLsZaLSvam1p/8RBGdbKC8m0XBWNJNEevaUCV02knXmlCldMWpV6pQZXSPKZeKUO4EG7VsQuSQi9RRuODb1f1efU5Emqkj+hJTGQPNmscbBVACH1FEoQ+0I0pxBJ7SUewFeBL+EHzlb8gdSBEmJd6l/6S2PfxARQ8nvV97m26dQZTHdqaD6/F57S17L68z01ErLrB4Aoyh49RQAxTyYSfzaa48HPDUx9uDeh5Y1K19XPT1GAZWKLI0Yiz2gYb//WqUBxupejYPQkbg4zHhYC0boHoKrkNl7CUEudnpNoRp+GUE6CgtvdCXBacBSchaRnDQzhgM7CAcrdpXAXW8Ak3xdrz4WhmXM8l4jkYvUNeoJ13x9p+xe0lICc42hI9Q11iTWhLn07af09Sp8yLCiXyOhDH7gVh5VNAMmUwXsUcIsMXoIAGzIbZI2fQNYo+RFguqIA1wxytKnj9QU64z7xHLiOPeEdEROGhGJJVId94jkFqnJKvbBZN566AEJGfWMZEuu/+ra06+dbFfmgSPAhAYwwuMLlOguInxVrn8QsJgXoudUYQ4egdN7iDQggTpJiGMm/nUtWlvi8ZKt6Nxesv6Bb3rCIR35zEl+okBZaNtCQp5nNT2jJIIzAygNScdZdfJGLpSr7NWCUwT6hSYFBIEcApEUg4icTE4Ur9xvvVgiM0wzvmkxLSl8hcOkxllOSUguxrOfTwlMLsdDeE8pSq7G8++H0pt8x0Xw3acZWOnmCGY/CPIY2Jn8woXxHJjcrm9YEvymvQGf9SThnMhbWWlb0SoJbTsD0ylV/2zSyS6735V0tGnwJanOknf9PYipeMx5EE5g7ZYnYjPo2QSjseQ1hafcZQTDKQzerc6Qd3xT6NmEuvG0LO7FPptgq7dWcv1nL311h77LzD5ON0k572hDvq/0dc8CWiuJb6ojK2yzzYPgCe4kjXA87gLu5xCUg5zv1sGvY5om27fhBMFvYhr/Ycnss3QG8Gsxg/NwKeC73roR3Ow2wI3yOzvKMu5bhTxTteEZv3Wp9pN2zWfm/PoBSBNEWfHzW06hKhFog/aTbUZQgDIwe9oy7LvYOhO89VQg30U87nQgB3ngcW0JKLBi+vveOiD8NjpZXm6sud/vhDVYnOUnPh84GUWfsCNezJKBabRcNiOYCWx5aXdszx9TxMIHgy1uXiQr2pwZayUkK1oXc6kyk1q0HkevspM2FINtOSvakU2HxhSTzWLznQF9z6axcj9z/VYxQxGKA6tHJk4KD9NfnJtAhltIhvtJYUNPqh/ZyRisAFDOmEbro0cdmKz6pAqVaVbCwLQVFW02XcM0BpVr1kLfNAWVbpbD03T7gPwFQXMpSKrSGBX9arngi4r05WlhjqzEsmiUFVrNSrePKkvKWDxWRVpZbAbKqn4lDJ71rZmbsUoTLUJ33HNwUXwM5qWyDg1G903bxxX8DBaQdRG6/Pm+UzhSdQgajk6HdtcFfAp2xZoG/SKuA3dPi2mSz1nlgGYSL6uzv4Wk+qVClZ5eqUugZbjmJTdzR9WLzgsf2H6gWfw+9l9lEJpkHOop1ynVZfVd89h9bKEVBRrf8pgG9qQ6Oo0Mvn+1fCsbRt2OdjtXWDfpC4wl9gJzeXmuPgeXWDupPl5lnZWGBt9oV8lrTCMbd5WgFgQXWYep1o1TRap+fp08L+N4NZ7+OndYF6k3zDOeLbtGHZ/2fNex9g24n59ODFdpu6knTP/ntmJPr4NbjIv0PUaYOU6zwd6B/GgH5hzT6jKllH2eTFFTNO/u8shaFFPvv+1Jk60cL8vNSdOtEt+K1UmzT+f3xZKU2+qmUsYJV/L/Yr9thhdif6q7jhdLU8x9suZk/WivbtAtSvRfXOBx/MMhftGhfmrbsn60VMzmDlE9quj3EjXsh8tX+vBJxvFjnqSP9AL5cSzjj/SC+Fku0hZ6wPxNlvE2v/PRHc3gR1IeeLkStAiE/Nw3Y6mcp6+yNeXpDtGhI1L5Vb+zp6J7jU4nYYsO1lDP8lkdfhK17XEc8O5AdvGyOTl6Td2OPXafhrd+eJ2zDYEdMN12P0M2b+bqs1wsH4a3c0v51RoK/DSd+D9DYIsvI5bx1fnHOuI9iNYktK5b/7Ntl/BwsoTXveXacuyxALznPQeE5GIC5Vqpyxcgkgejn+e7x8lZZ3P5+H5U/37dkme41vUa8gnO2FVR16S6TOtidh+jfxFwkC+kL+ebwP3vowsV/ZEgm3zjBWTLdisaDGEu6Qb652P9A2+AE0nia6L8v1sb8kedtWjj77J+u5MRDog7ku+g+8yDx886E7rNXJ6tIj3u21oIgQd5M3oHoBy+Llz0S4Ig8nf0gH6AxZE5cgvPM3nN23ksyAJ/hEEVc0F08wEW/7DRubhIMqawWAgCdLVZudz5dyGV6FpQZbR+uuqcHL7A32SpLdHDkFnYJgobMRK+gAWYGmwD4ispkj55l9gbwCW0Pdcf1dLo/R5/NCartrsyAw37XzfDwMd5cA6IX/cNqOTyAsBd1AjvzuUGyX1GYF9uDdP6s6F/IwbOX+RdDTBSmMf1GCYJxwwThodf4F0VnQvsqmyasFGYppSMD/saXxlNrr3KsfmZg4Yuh1jJ1Aqx+aif2hjNW6zUCdP9XNBtqlBWCqWIC4VxBfEFcYZxBTGGMQWGg9cDgPmA9QAYADpIzc3+eu567I9kTYJJukm6Abq5ukG6Obohuhm6nbraJQ5FCkVGRSZFZkUWRVZF1WArUL6UF5QPlB9/8YRyknKUcpMSAF8TFg4SDRIMkg6KCwqtAHsrv1pJLjgwLTstN20cKgOXbSWPKL+/j6B/2r8Z21nZOcl6yRfZSdklyWbJBNlY2TXJdskT2VB5Nb9YaVV2U3ZLdlv2v2tbilYmD0QvRa9/Xgt4xF39ZkJtb3Vuh/ZU9o02XHaDtlL2izZadgc2VvYPGCrZbaqTu9C0DDyKfP/4FvgQD4mAGQMsBPqhH6A/oKmIbBJ+5+xQiIiW0xUycvBDCvglwv0Q0H8J+L8EjxaIzTDecqJwmVk1WteW5xuoDAQnoqrxnDnXO9dG5psmb7kzxO2LCUGTXhiv6/bIhAVUJ4KuGL/rEHpzYYTDKsNuYeDzkuuG+jMogL2pGhScYCArqdCOPEnjMRH+7XuFVJFYMMbCCNcDKBT48epqj7+EZjO1P/0bPyjg5E3S1ngpyXZqh3Eaf0hHKXDkDdZW0T5Dp0KvfhnJbmzGADWk4Z1W5bJUMS43M8TQbn85xlIxtiDlRXu5tpvBInEumA2zjQ3iSsYUeSo/PDssP0w/pDjEOLQIqO9hEGAgQEEAgpCGSr2Z2JrcMuo1aLV3snaCdphylnaoco52oHaWdre2RrFDtVK1SbFZsUG1VbVNWSnQKqIX5xXmE+YX5h3iEeYc4hDmBkYgqAonDCUKJQgVBRUPJbIx3EpjnTxnuEt6XHpE3iBwDil9UXhCe0J5ynyOsTPUs9Bz0G3XF9CL0EvQTdcx0CnXq9fl0CfQGd9MY5n0kvS29I70rvCeqJtvYwaADEwWUCK4pmy0tjBzkJ67QPsJfQCdCj0E3Q59Ap0JPQadDX0Bjfcd8dUu+kqahxqCPoY+h76GZuRrhA+Dz4TfQ31H/UZFpWQpPz1Fg0JGlIpInlajMZSgOTegcVSkeRek+eddm65kwIOqbRQVYpNbkWis2B+TCKqpe5AY4pobnWj+T58nw1uvGAk05YXwulYkCSm/3ETsJcFPPZGeXTiyoJwwF1Ck0ocSVk4UM0E7Eu9RODK/3EgsV/shAZAQi029XSKIa+GO3+/ZMcoK6lvgOGClO101lYtQP5M0rUOCPNSKZVUFyxhqrVvnb1vLsTbY/V+FZqiJ2qRmRY2aQjRTTgSdG40fjRuNI40ZjSENnLKXPBYBYAKQBFBxEkmx82Ppw88c/Ty7NJs1WzRbFduUlWLNYtpIrljeaN5oLlnuaDZZ9mgO2b54lSSxJKEkkaS4pIgkoYxhVtrKpCXj3b/HhUdETfEm6ZITpSPUI7SjjOM4OUM8CzwH3HZ8AbwIvATcdBwDnHK8elwOfAKc8cy05UkvCW8L7wjvcu9x+oU2Rg9kL2WvJK+lXJEuCVOp5qNauX18Cvx6HA68flwJ/HkcDbw9HAv8u3R1nbaVSX4IWkYeZb4kviU+5ENRYOQAx/7itLO0tzQNkYr87TxlChURiwlhpr5KyKFKyfCqSOnKifjKSB73YRygpXIOJGVwE3dZXJwsILVkm3EspDTwanddHJ6sr8VxHndiXIr2ZnnLV7BMHABZUurGsifvYB9uTDgYWVhLmPjRybahPZ1kQe6UdkZOOBBZVOqHr8QyGIkFB+5BWaSnSDE4wnZJBWE/bt208ZvQbqa3J8WFA2FO7qQ0jZuSbqc3mIeFh0gUYUfu4DSVtDMCVIQqb8Y6Gl+hAYYpOOckObAVj+oNhlHSWu8OuBUPnYm4UO8u9Sa4ia+EJmHtqnw8UzJE4SuPL48rjwOPaY/BrePBux0GAwAGEAwQGHJYidsj3RNdpuD0/7K6M7uBuh+6kbovuom6J7sXeza1QrdCN1G3SLdYt0S3VLdMn8tXz6mN5grnDuaM5pDmjGaRZg9mEyEKV8L/hSWA/QsrAisMQ6Br+G9K6/gJA2Qc9Aw0wqaIM0zJncIN2g3KbcZNjJ5RMJOALoEbAokEigg4I4BBoJKALYEZApDkUm+RCjoZzAp4JPBC4J31Aw4MXwhfCl8Jf7PJYq1gOjA1Z0XaJ4EpAvQIIghYMthCIJUAJ4EtYqznoKJG9UfUInY/5SHlKeUlJZ1gk3yAfJb8nPWD9YcVzZLC4vSUFEqdzQmgZdrMQs3B4kbgLH5w/ut73qbNg7Gif51IrQVFagNEmXKsO4CS9LFbq4VU6hIEnXKOp2+9jZNWKSpI5jPfJbxREipBnYnUW6FXeAQ9j3AkYQ1B2zG+1kcQWE7tDF8/svJNOIqgzkgqV/ohH0gPkE2PQz5IakaBCkT1G/j59/gXXqHiZKl+mPn0nAQ9liJj0QBmPzOZGjWWAn1MO72Zm4X6eFqBW7pFFdoKrdR0iSq2IoYytiKWMq4ijtJ48WoBgAJwGYAKQBapxMVnR2EH4ZGuSTJJOEk4QDhXOEg4RzhEOEO4U1i7xSFJIckoySTJLMkiySqp2mxByrNisWKwYvIvblYcVFxUPFRw9QZhwSKxIqEiyaKYorAOIrRKarZkm4Ha89lz2remAHG7WvGICgn6CAZpfp0hnNSe0K3VftId1Z7RbdRO0I3WXtBt1T7SDdZWS0q2VHc1d7V2tXd1dn0ZeVqHqqeqF6jXqp83BEG7kplKf10g/NQ+0E3VHtJt1z7RzdQe083WvtDFS46YarfwSFg0HFTcUb5WPJ2D1wIpoJbDqPgreih6KgoVw0X9coYIpcZmKtA0aWejamVzq3wVtXP81nNsGYtNEzGUROjStii4rS4PNtAZSE5w1enZdsx7rY4MNs3Sk84Zsy0GBcl+Fj+pGyaB5teaSL4Uf6kj7sqEgQrrCkuNBEc9yEJyaBvuyZC2GsWBCuqOJPLkHUmCFgJtxzjkgORk/hOFaOVSadiVWSNsdCZsg9HzLA7ycJydPiJMdaZsw9ELzQ7qxhJ13J7eI1wh/IidhK1yZmyjybEShJyCcc6R81pIT9SEHP29IwcI6gzF3HiSOqQ6lDq0Oow6rDycDEjsQRIgzMdQAKGQpErOneCe5jbpNXSze7B4gLgbf5S4K3+MuKN4lHi1sEazQ7ZStvnrRGyQbZVtk1Zotajp1bmUOZQ5lbmUuZV5lHmV+ZTJFRToBanEqISoIqliqMQ4ht3orFOXavbmTulP51oV9yjkcgrSadMp01mzMHmHuxe69zsd+wK7EXsIuxg7BtoVewy7HHsF2/+50lmmPqe+rL6gvaq9purT2tcBmAFCB3b0LyqDrh1MD6ZmrAh/YR9jp2KPYbdjn2NnYk8AAiz902FnY19j451GhbeavZsXrESlDaZtpy2m4b9B8VXyTfJd1EHVUdVJSYwIMvPDK643KhLRmLQqNwopOYEr+6GUHOEXm3StRVmCkqE1zJT4/KthXnGigU5XbpyuytL+MNI9LTzWPElLP9VDrxAVLPNV6fwskYRWUGMi91bptZ5VzyoYUVhN0AA0Uu1tBCmjhimvGc7+KhBVUGMknyP2VAlkANSm1iETZDYvRw3i/B0YrGu1htzoTNAFK+MxEpomKnNzgpzqTNaFKxNyE7KL2yaqdXOItIL8FjkOWelM1001Y9tNLEntkCFvsXCZXEYyhlzr1KmxcOlsXx3s/K9Ek9Z8dVCzqkZPoYuBN8vOysbMxsrGzsbJxs0Ga8lpDukO1ACQAVyDzPdf7Yz2pLYRn2Gr3f984eMw4SzpUOEc6UDpLOluWYVuh2ilaPPPZsEG0VbR9t8KnRYtfRZXDkcOZw5XDncOTw5vDl/OWJ5Ck0ijAJN4Y8wHkmlgfYitrhp9me5A2pz6bJot74DdPy1pRXUFbQVzNe7OEM9Cz0HXAz8gTyIvITcjpyDHQq9BtwOfIAcia10l+kvK64prypuKG8o+nR21/Zxj3bOcS10vpn2jf+8lJW6ukL8i7yHHw/cgNyIfISfDDyCnIp8hY50HrTV6P4oWHQcdd5yvHU/v4DsgDmgcsNn+GR4ZnhlCzRCV3x0hQmmxqX4UTWvZqKvZ3NtfRcWcv+WcW49a08QMRRHGdK76L6PLQw20BrITbHWGdp67H6MjQ00z9MRzj2SLwUHyn9Uu9n0TwPNqjWTear3u/e45+wPzqwmK92fFPu4gs+oYLrqR/BmHgvNqDWT0BJ5qgSyA7rTbZAMM5keIQfzwrmfu/z0HXOmO0wsr4LES+qU7874HHOtO0osrEPIT8os7Yrjzvgk8B/xUP0xf6E7TTzFoOww7zWyXJmmy8Jm6hdwHXOrWqrPw6TrZ7v8HZ7M6lcHv8mJhjb5MPz1tlo6Vh5mHlYedh5OHmweGc40L+AIYHgDcr7jY++S6I7wD/Mjc5I5cD4kBMO3NzV0BLAYwFXDe3+q2D1cANwI3ATcDtwC3Aqf5Xfj8EFXRFNmU0VTR1NE00bTRdN7kGQT5TFwsXAxcXFT+XS4cAm5z2+jG+Q0V6BPoFGizBRk3tGwdlRV0GYTddLkAPm0+Y15r/mo+br5g3mieZB5jvmLean5qHmKueZvopolviW+L74jviv/+/BAHlUeTJ5Snk7fYBLk2NP2derkC/mV+bJ5qPmbebn5unmk+ZZ5t
*/