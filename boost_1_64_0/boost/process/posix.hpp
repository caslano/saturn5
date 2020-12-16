// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PROCESS_POSIX_HPP_
#define BOOST_PROCESS_POSIX_HPP_

#include <boost/process/detail/posix/fd.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/use_vfork.hpp>
#include <boost/process/detail/posix/signal.hpp>


/** \file boost/process/posix.hpp
 *
 *    Header which provides the posix extensions.
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    namespace posix {
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::posix::fd">fd</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::posix::sig">sig</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::posix::use_vfork">use_vfork</globalname>;
    }
  }
}
</programlisting>
 *  \endxmlonly
 *   \warning Only available on posix. See the documentation of [fork](http://pubs.opengroup.org/onlinepubs/009695399/functions/fork.html),
 *   [execve](http://pubs.opengroup.org/onlinepubs/009695399/functions/execve.html) and
 *   [vfork](http://pubs.opengroup.org/onlinepubs/009695399/functions/vfork.html).
 *
 */

namespace boost { namespace process {

///Namespace containing the posix exensions.
namespace posix {

/** This property lets you modify file-descriptors other than the standard ones (0,1,2).
 *
 * It provides the functions `bind`, which implements [dup2](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html)
 * and [close](http://pubs.opengroup.org/onlinepubs/9699919799/functions/close.html).
 *
 * Close can also be called with a range of file-descriptors to be closed.
 *
 */
constexpr ::boost::process::detail::posix::fd_ fd;

/** This property lets you modify the handling of `SIGCHLD` for this call. It will be reset afterwards.

It can be set to default, by the expression `sig.dfl()`, set to ignore with `sig.ign()` or
assigned a custom handler. A custom handler must have the type `sighandler_t`and can be assigned with the following syntax:

\code{.cpp}
sig = handler;
sig(handler);
\endcode

\warning @ref spawn will automatically use `sig.ign()`, which will override if you pass a custom handler.
 */
constexpr ::boost::process::detail::posix::sig_       sig;
/** This property will replace the usage of [fork](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fork.html) by [vfork](http://pubs.opengroup.org/onlinepubs/009695399/functions/vfork.html).
 \note `vfork` is no longer an official part of the posix standard.

 */
constexpr ::boost::process::detail::posix::use_vfork_ use_vfork;


using ::boost::process::detail::posix::sighandler_t;

}}}

#endif /* BOOST_PROCESS_POSIX_HPP_ */

/* posix.hpp
lP9De1dzGMeZxdT725br51fdXKL6vYO58vp/b1/Wui6s2/6Fwa6BKzvXAVbALOexRpYlR36PkZzqPPM2fkZoac9Lfu9lf5ypYdb9mVBnWRncqPtPpH8w90Tvs6t7c3jr/RWaZrQb/aX0L+iw/AbUqOsj0u83yh4zjvG7azpz/sa9Y2ekzB1KFJVcmJG7ITlzunnbkjwkZQIfGuYHGbc6TrKs/MQgTrPc93hRyv2ouvXh/DTn99a5VGIHjkorA1mfBQpo7m0BNldlElhX77IdeMZ4ewUU8Pbv5J3PM8Q72NPX28OzgreXZ4R/Gf9K/h28i3l6+Hf2juD/Uv6VKErDMEabxUvVd7VTze+cHvne2kPqrLNWVgsy7p/LlVyEbOPzXPfqGOVvyzLN0fowRN7ygZbjUnyeY79d271B+IuMa4EWTsmGWld1rqmPz1/qJUzVy3TqZYWz7nyiAzz9NM29nUR5H3mMtrlln1HbtL7fsO2Sk21Xzvvzy/Q1rUQx2Y9Y87w/ezIPJRmv49Sa35qtfy03t9flQ888v+D8OerXx5m/d2KX77wXx85u8+2tuOTny57RtN4ezvy15p0jh1SYOf2j8JiZfmfuX9K0vfmc+SZRibf+0XtAJc+hA/xHX0w8Sl7G07pTfMQPPW9U9suIPDOm9p2PNa2vpzM/Ydmbx37cFx09dl/34ckzll7RtKK1nXnPj4MS+g2u8vb8leufvV/qQLymVfNy5rMjptwc23V+r5eefHZhYC2/8+z3dZ35gqWXVpnn/5NjSu0oj6RaHzD+wZIPrLmsUZ007/jju7deXLpy8yrqx9eZX7Ju/idHPh98Z1TwltBKvrc7UhetnPkk7VTzAV6pn364a8ThmH6JlTinkvJ7A0J2xNaqtbtxvkr1BxdvRR1+Lvno6Hef/unI3fBux0dFdlsYuZ/zSqmHwSUqRm0sMmfdnyM2Tz445Xo3th6Z/86bl3c6/WB1u19XvD43/8qyC5xvJs78kVFHP3twc9aNEdNKFNkw/XnezLdJPuKT0dPvle754aTh7ddN3L7mAEdmycfcrlD+6VujJ61q0yv8is+0MZr2gkz3m5d/+Kx5YvKisb+P7Le+1Hvk6kg93++3NGlPZPkGh575yHf7oU0s10QZT74bRf5I7Zz0wnf5y8/IeHlsQeZHyu8+0vPyeynFLjx4ZXHL70pv4BrBdoczHxaQ0O5g1yupT5Z9Y8roEStuamxHzvzI4Dd27Roc0ePQ2wM/OFPxea7CHZDtZOVzI3te8Z757ovLQ84cWPryHo6xkt/QpMONew3qHH3t4tl98Y74L5lsfmf+vUXvthzv5Xm/eXzdFWnn6nIk+tbbmX/i63j/lD5PjT/lNzGjTMUuSzSttGxX777Rv9tGr6snP3yn3IP5cya/w/fMtZz5LYc3fH23WJtRe5tmHvy01m4+zHaU8W+eNfjVytO39D9b5F+rblYoSdmJkr8yPerNKnvS7o29nrt1XG6J1Zp2Vuoh41DqxJvXyn929JUWkZV/qMd2VVHqee0Pz5Wc13dF/pf8DzjCbi3byvFVxjN6+rMZS2qeSl695vxTK3NH9tS0lrKdeLyTXKrMi7fqR9yJCCr8Qb/vNO2W8z1M7czLQtiOqZd/+Lram11OLo6oYXntGcJrPEd4mK/5NGe8luPwBcbzhsZxxfJ6ieX1GsvrxZbXNS3Tilfjf4pIsLxO5PVsrE/0t7zuEyLnQpxlsB2q16kax3z1+gzBJkR59TwZ/EydPxXCCaoe1vPGXQC3YihuxAjVXRa3YXnVXUV1N8bt2AE/wim4C9fgXvwAP8WPcB/uxp24T3Vfx6b6M0qglZqvfFhLzVcWl08=
*/