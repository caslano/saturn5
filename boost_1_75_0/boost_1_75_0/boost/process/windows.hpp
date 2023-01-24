// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PROCESS_WINDOWS_HPP_
#define BOOST_PROCESS_WINDOWS_HPP_

#include <boost/process/detail/windows/show_window.hpp>

/** \file boost/process/windows.hpp
 *
 *    Header which provides the windows extensions.

\xmlonly
<programlisting>
namespace boost {
  namespace process {
    namespace windows {
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::hide">hide</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::maximized">maximized</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::minimized">minimized</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::minimized_not_active">minimized_not_active</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::not_active">not_active</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::show">show</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::show_normal">show_normal</globalname>;
      <emphasis>unspecified</emphasis> <globalname alt="boost::process::windows::create_no_window">create_no_window</globalname>;
    }
  }
}
</programlisting>
 *  \endxmlonly
 *   \warning Only available on windows.
 *   See the parameter documentation of [ShowWindow](https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548.aspx) for more details.
 */

namespace boost { namespace process {

///Namespace containing the windows extensions.
namespace windows {

///Hides the window and activates another window.
constexpr ::boost::process::detail::windows::show_window<::boost::winapi::SW_HIDE_           > hide;
///Activates the window and displays it as a maximized window.
constexpr ::boost::process::detail::windows::show_window<::boost::winapi::SW_SHOWMAXIMIZED_  > maximized;
///Activates the window and displays it as a minimized window.
constexpr ::boost::process::detail::windows::show_window<::boost::winapi::SW_SHOWMINIMIZED_  > minimized;
///Displays the window as a minimized window. This value is similar to `minimized`, except the window is not activated.
constexpr ::boost::process::detail::windows::show_window<::boost::winapi::SW_SHOWMINNOACTIVE_> minimized_not_active;
///Displays a window in its most recent size and position. This value is similar to show_normal`, except that the window is not activated.
constexpr ::boost::process::detail::windows::show_window<::boost::winapi::SW_SHOWNOACTIVATE_ > not_active;
///Activates and displays a window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when displaying the window for the first time.
constexpr ::boost::process::detail::windows::show_window<::boost::winapi::SW_SHOWNORMAL_     > show;
///Activates and displays a window. If the window is minimized or maximized, the system restores it to its original size and position. An application should specify this flag when displaying the window for the first time.
constexpr ::boost::process::detail::windows::show_window<::boost::winapi::SW_SHOWNORMAL_     > show_normal;

///Adds the [CREATE_NO_WINDOW](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx) flag.
constexpr ::boost::process::detail::windows::create_no_window_ create_no_window;

}}}

#endif /* BOOST_PROCESS_WINDOWS_HPP_ */

/* windows.hpp
L9HAYt7GiZ8fDD2WF4nJ56g4mltPeNWNjZSpmOsrP1aWZbqGOoN2fhOoZtMOjJPXYkXXlfL6l+E90F1aamanL7wKo/d4sDRgybke9tTnBltuh58KDfyBaeSGblZJhxKNF3yPue1uPp0hryniTjb1PcBmnrxqnipHj/XL5pTjRJZAc5XWW5NS3+mHaSs89Xmqb1hEDJcw7U5vO6+0KK8yQ2WNEZ8gGfA+X5PVsMA+L/ofUzEsJ/S2doeoUW0nlbTvp+x9Qk5Xvsz1H67SEdSXjlE0YvK61o/N+bsR8FEu87h6yZ9mjZxvMUuiwumasKuSAdiFYbYrsMxkHpog+buS6MsYvH3H1ph+MlkJ2bb6E+5iZQxifSVLUdHM7dRzkRCwVj1hynJnTRbOMa5BAsq+Fre5rc9oekMwjk7IEHQr6y1dudwCU4Ebpn6eGKV/eJnwNr0I22FHFVFz4UNqTCOftGuFf833P2P2dfm2vb7rOZz8E6T/sufnCYoVA6CCMssq2Bz3lSSoiZGnii62tt90WbdH6YfO0Ktu9EzLy/WKoyiAgjX3FIowach1Xsk2asU4T1uBjIcZ/8qmsEhDB9oKiSaDqM1kmQfltE2nHm0RpbMyGfVfCLum4EoYMxobm41t2/Yfc5M0xsa2bWdjJzfOzcY2N7Zt277RbTt96EM77dM3Z+Z7PC9n5oAAQZ9ua7WQT92+uz+YfHbfEZJP
*/