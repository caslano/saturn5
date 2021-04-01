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
GsWp/DTlr9xgWjmr28qkZpDLl9YHrdjLee+1hmKkWgyNrfIT21lWzRYTVieW4eByvvxRjJjKUJLpuHfV2mIboE1ja28PtGajx+5MU4+FnBTBC86t7TkUk6sQMn9/jCmfOcauQMsVhf/tvIBDqKAN0rSs5cQVJPp85i8qlx5gqxDzhGm+uQYlUX5N4ycD6w435P3LVI1+//oqs2+M+UHvCxIpmv/ShMolKkPkhh0DNxtisXgSE7vS85wVF21/8VsRK9Iph4/rpArvng57rXmzKWDobmFHyK8ZiXfb1ok61vtKoz+5qJrL5g113HC2VVUI6VvziA+rkkx4sTLGH6ookqcqvtDscubLXcb+xqJLtuLoja5fIFDKj/7JKv1nWAvZ9wnehbiU3frkyYs3VKnWVdhke/j0Gkee9BzhiPmUXCInQZkI+WOTYvXl41hw4uUyvCgW/XQVCZbMmxofwGbgKduRMFn1LR72ApbkKq5QXmJwqXlrwb3M1LVbONikop+vXZIGWfJlNcQbnKMbiawF2/bI2AHI05pOaG8su1ynqEC3l6p4yn8iXd1G/w==
*/