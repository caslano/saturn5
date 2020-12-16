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
qp4rGRP0eJ/pVV1ZP3PJMldV+8GVMFfhsi60MsQX7AfRJ9Uypw8akqFZP6sPjUuxPJO2kZQL1wLtl5XxmMtaKly2d66ImttMLekfpT1hf32G4d0/VyUk9rc9ppplpU7s/9oHaW6fTWV5zO2HeSSn5tH6uUOmq+pObS87irlGutHZZpBylHN7cdVdatYAacbZcj4lTzyJzZCcHCNU2QXsWb2s9Ube/VxMXS9W1yWCMU3KLHUco+7vcIz2crxiU4fmuMKMcfGxJpsTM7lYbF+XfS31fkvqnfcetY2G4QrpP9DRkSn0cOSz+5zKOOyOdea+8rb0z3I8wzh6O3xsP7+qcbi/b9t+XqWsTfvX5vvb+FPOvqNk2EjLsJHWOrJet4tNSMyOS07JqmFury1kHB2o8WpuZdX6sbzv/iHj9FbDspal+zutjTbTWP+S49NAL8rlHZ9lW1HH6CFSdpGjuqOP67hN11WZnxAtIs+w1vVrHleWyvBpjq7U90ltrP2yVqe8en9bJeWTHE9R/geOrPmNY3+ymj7jlOm3eWh+yvHZ7FoY+xj7w065Vp0/wCfE348mmmt7ewf4+np7Bvj20x55XPiHTHs0R4ZetvVn/WzH+An752eGB//1Zzv9WprXafNaWuop43qY8QyptuTcr695m7kaeu7BybzX0sKsxxvzGEDeeq3Dun9bz6ut69K87sE+ST/ZJyUX6v7eRy7cei6lcpH/oW30yCc0+VtDFCDeJ5YwfJTUS47rg6n1q6THeP4Cw7pd15JBjXblq0v/t7SJmoftscs6/AHXc04yNMv5UmXpv0SbbrxPmuv+cLDx+Yd+3eX7sK87Ml5v9+/DWnA8df2Vk/H10Opqnn95vvLIZwNodKvltNZvvRKugeer3+O8jiMY9pC1fjPjhsXGJ2dwsV12CEv9Gp9pT0v5Sbaf/RmXecy1tiOv6ttxxtm3n8NuX24v/Yo51PkufzIPxvGs0Vn6Wz6bmueCUo4Nz3KdQMYVYTzj/hnpLugI0K4abdo3ldyTMi9RReWc0xi+n/RrajP8N5bj0ECj/APpX96uvPH8gW3qucKHgsxt45MQxEvSbW4vSKhncjzGc06Mz8QcSw6ynQ0/Ks+7is8aGpusrmFKnck5q6rXPNe5o9T3lw6mgS3UtpFx1rJtyJMihqSmxmWOcNv3jP1hjJSv5SjpsL3GzfjM7eNIYN7PnXLNV/qf0w6y/VvWi/msfenvbb0GI8unf7bso/WSbXSXOh7vxovBUr/SvYfun1VdjyCqBslr1od5jWKwWieh9LsS7FpvVzEZ5TPkY3yHZeyT1msRal6t9R5QRg2sngfRGDuy/naeM+tdPZlDvUPmqXdjvzos5ffZ1bkal8P2e4kieEH6F3aUZcw2x0CGN85N1HFKzRDftFg/f30j5WJYjoqW9ZOawLMBjfVX8wdnmULGPj9Uul8yrmPdlW4f1V9169eOg2R8WRmDko31HezMG9uRPI/JGPclmZ/SxjMoysm4jmtdmJ45XCa3fMjbnjGPIVIu0HItLdX55ifT/E2mqeezuGEknm/0Nel3nX7msUs+F0r+BnnzWRV8DpRe5jFxrkwvXnXLMrsdQxOMY5tz1IOlfymba3RDsuIGuObzd/I12Bf8yZ5npe21nJ+MUn5Kbh+xn7A+Ayjwf3jPcfsORdYN64ucrC/J/WZcT5P6lPOP60bOrEvKSp25f76+Y1xTkfqQ3O/G8LLseZ57M6eiJn9vefD+q1xejOPbedm3uLtmCOdCI4yLc+xg/YYM+Ovv/hneWD8lI4zvR2z3HbOs+V2z9fyhovQ/odVh6Ic+B9kNTx1nZ9l8L2dXVo435v5Q/ke5BmM=
*/