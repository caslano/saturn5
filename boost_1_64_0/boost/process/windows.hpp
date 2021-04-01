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
N6VMGny3L9c9Ue+H2f7y6QCAbAiFFmNvgdjf9iw21XBYHXBfAt5ULdkdhjnYwOabyqfnNKXjJ/n4liK51sMNti4czTQa4B82Nj3iq4dCVEjBtRmA6qvMgZHXD9DChI6diy8DwM1In7E/omO8eEw2U32aLKTTcaW23u7Xw9dBp3+PbXN/T8mtpvQTHvUuntKH3hIQB3oYe2H54rvTpvpu7pAyTKecSrW33acFsczOAOcFP1k+SjL4NRYDXJj+JOnNVIxbn7SBG7A5yUrf+mp7tpHug+Fko4uBgya2grfPruhjOPgBhbasK3EdhZUNWl/lz5ZGadSwcS41HtJIeKtqjvfP0KLuRiD+5lO/ScmAs+Kb1WCPtSLKEvNXpljQg4NHz0GtM/gtsPQojmVhe1wKaDSWIN+W2VDhafdHzQC1nO53VJIQSDzjlGcXs6kyBtEGBmP42aeCy/YCzqIPjQRpHiziYUcmRrQA3DtKgklTwz0JQVZmkpfSQ3A8H4nDJ2NV/yWqucejH3FN068b4Uu8s5QvxkCNRAEUo5J8RLBEabP6xNxkztda+IlekA==
*/