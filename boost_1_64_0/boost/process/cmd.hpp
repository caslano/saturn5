// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_CMD_LINE_HPP
#define BOOST_PROCESS_DETAIL_CMD_LINE_HPP

#include <boost/winapi/config.hpp>
#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/traits/cmd_or_exe.hpp>
#include <boost/process/detail/traits/wchar_t.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/cmd.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/cmd.hpp>
#endif

/** \file boost/process/cmd.hpp
 *
 *    This header provides the \xmlonly <globalname alt="boost::process::cmd">cmd</globalname>\endxmlonly property.
 *
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::cmd">cmd</globalname>;
  }
}
</programlisting>
\endxmlonly
*/

namespace boost { namespace process { namespace detail {


struct cmd_
{
    constexpr cmd_() {}

    template<typename Char>
    inline api::cmd_setter_<Char> operator()(const Char *s) const
    {
        return api::cmd_setter_<Char>(s);
    }
    template<typename Char>
    inline api::cmd_setter_<Char> operator= (const Char *s) const
    {
        return api::cmd_setter_<Char>(s);
    }

    template<typename Char>
    inline api::cmd_setter_<Char> operator()(const std::basic_string<Char> &s) const
    {
        return api::cmd_setter_<Char>(s);
    }
    template<typename Char>
    inline api::cmd_setter_<Char> operator= (const std::basic_string<Char> &s) const
    {
        return api::cmd_setter_<Char>(s);
    }
};

template<> struct is_wchar_t<api::cmd_setter_<wchar_t>> : std::true_type {};



template<>
struct char_converter<char, api::cmd_setter_<wchar_t>>
{
    static api::cmd_setter_<char> conv(const api::cmd_setter_<wchar_t> & in)
    {
        return { ::boost::process::detail::convert(in.str()) };
    }
};

template<>
struct char_converter<wchar_t, api::cmd_setter_<char>>
{
    static api::cmd_setter_<wchar_t> conv(const api::cmd_setter_<char> & in)
    {
        return { ::boost::process::detail::convert(in.str()) };
    }
};






}


/** The cmd property allows to explicitly set commands for the execution.

The overload form applies when only one string is passed to a launching function.
The string will be internally parsed and split at spaces.

The following expressions are valid, with `value` being either a C-String or
a `std::basic_string` with `char` or `wchar_t`.

\code{.cpp}
cmd="value";
cmd(value);
\endcode

The property can only be used for assignments.


 */
constexpr static ::boost::process::detail::cmd_ cmd;

}}

#endif

/* cmd.hpp
I9gaHgfbwjawHewA26u9Lo5Tew3UXryjp/bO1uv+EJgCh8J6cDisD0fAT2Er3Gi1E692ArhmaucStTMPxsFLNd58XIXGG6jjsFTcrFA/nkB+4H2wKXwAngL/AIfCDXASfATOh5vgcvgofABugX+EW+GH8AlYg+M8CbPh03AA3AGd9LTw6d50fH9b09MUF/q9zzVjdjK8GWbD5bAjvAWeCW+Fg+FtcAi8A46AK+BcuBI+CFfB5+A2+Ap8En4Mn4I/wKdhHY65HdaHz8CG8B7YBK6BreC9sCdcB/PgejgG3g9LNN54+CCsgH+Al8KH4XXwEXij6t0MN8O74KNwA9wCt8Kt8FX4OHxT9Z3yGu3Xfdl0L7kDMC/YXvhwvGSu73DzX9m797AqyjyA4+/hHK4CAiJyUcBL3sXLmpqZgYpKIhAX85aAgIJyE9DMdLO00rTUsjKzNLW7W+alrCzNbHPTNS1rtcw0LS2trKwsTfc7v/OemYFgd5/9b59n7fn1Yd55552Zd2beeWfOOTMYizuwE76FV+NOHIa7sAh34+24Fxfge7gM9+Fz+AEexEN4HD/G0/gJfo+f4kU8gsZ2Po6N8QS2xS+wP57EIfgNZuK3WIk/4K34I96FP+FyvIgv4+/4Dl7C9/EynkYvzj/foRN9WXcfjEajvA5olNcdG5GehIGYgY0xH0OwBENxJkbgQozCZzAaX8EY3InN8VOMw2MYj7/iz8zH32gPsTm2Jr0rtsGe2Bn7YndMxB6Yin/C4dgTM7EX1uDVOAuvwYV4LT6CibgGB+AGnf6mTn8bje36LoYx/AE2wWMYjscxAX/GFPRivxmOYZiGMZiOrTHDc33ieYaZfqbZWezB+q4gXT5hcLr7+6UYgWXYASswARfgdiZegt5Mdx8G4lJsgg9gS3wI2+My7IWP4DW4EgfhKhyGqzEL1+NYfBE/xY14Ejfh97gZf8aX8AK+jMpJO4be+AoG4KvYGF/DcHwdW+Ab2Aq3YV98EwfgThyJb2M1/hVX4bu4HXfjm7gH9+J+/AWP4CX8DEOp36PYG4/jtXgCB+FXOAy/xnF4Gufit7gQz+ESvIBr8SK+i7/j1+h00Y5hAIZ5s99jHwzEMRiGlRiBa7AZvo2R+C5G44cYgx9jLJ7FOPwJW6LyoW3GEGyNLbANdscrsBe2wyTsiNdjJxyHnbEKu+JN2B3nYA+chz1xCV6JD2JvXI198CnsixvwanwZr8G3sD/uwkT8Aj90Ug/4Ebp8uT4wlheTsSkOwThMwZY4DLtgKvbANOyP6TgQMzEdszEbR+AYHIl5OBpLcQxOwRtxOubiLMzH+Tge78VCXI5FuBIn4nNYjOtxEm7Byfg6luHfsBz3YiUewil4BKvxa6zB73AaXsCbUPlxnY+NcAaG4EyMwVkYj7diO7wNO+OD2AsfwqvxYUzG5XgdrsAcfBRH40oswFVYjKuxGtfgdHwC5+KTOB+fxgfwGVyOz+Pz+AJuxBfxddyAO3AT7sHNuB9fxk9wCx7FV/FrfA2/w7fQ4c9xij64C4PxbxiLu7E1voc5+AGW4r2+7Je4COfgYlyCS/BRvA+fwfvxBVyK2/EB3I8P4kl8CFUA7Rk2wYexLS7HrvgI9sQVmIKP4jh8DKfhSrwNV+Hd+DguxjX4JD6BW/FJfBufwr34NH6Mz+BxfBa/xXXo04jrQAzBFzESN2AcHmL9O+DHmICHcTB+isPwBGbhFzgST2IensIi/Bor8TROxW/wVvwWb8MfcSWew8fxF1yHv+LzeAFfwYv4Gl7Gd9DhzX6PLjyK3vi9HqYPIO1wcCD1yHATfBQjcRX2wMexN67GfhiMSdgYMzEER2MYjsU=
*/