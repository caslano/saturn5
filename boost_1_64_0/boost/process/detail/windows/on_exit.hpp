// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_
#define BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/windows/async_handler.hpp>
#include <system_error>
#include <functional>

namespace boost { namespace process { namespace detail { namespace windows {

struct on_exit_ : boost::process::detail::windows::async_handler
{
    std::function<void(int, const std::error_code&)> handler;
    on_exit_(const std::function<void(int, const std::error_code&)> & handler) : handler(handler)
    {

    }

    template<typename Executor>
    std::function<void(int, const std::error_code&)> on_exit_handler(Executor&)
    {
        auto handler_ = this->handler;
        return [handler_](int exit_code, const std::error_code & ec)
               {
                    handler_(static_cast<int>(exit_code), ec);
               };

    }
};


}}}}
#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_ */

/* on_exit.hpp
/LyL8JQ1zKFlpaWNS/PQy1R6QY4UcL8zNJVj43JU3SRr+Y70iSnmXgHqGgmfI9wRhnBjLn5xD8z1PSTNWkaq84nUOsBodV1XXU+K9Kw7pkd6rgM8oa7XV/asS0bKyU9yBoLYL0eaoLPdmeZSjajKxFyX6PXWV0V3qbxT8rC3fYSRnnusvpV9Z4r/Rd3SQdUtqa2cys2VIzkDrxx1WZQhHo5lmaQeCR37JSTd07tnIirO+sC9V8oq7MoPu6duE6txtNaVcplK2kYTrpWOcsaBYzEhwZx6qN5RKWZ/+IrFPiNt1sQzDRq09iybZZFrXCzzkgaO/25JA29jGBUvR/2RTpwuI4WOeJV194Mvhv+HcTP1e6+1vvVZTg21epYpMm8tdXaohP8vn59bb5SXZ3fbd2vUfj9Vr4VK+OU6QF+P8thPnd/m1nmqQO5TYI4L23WTM7FznyFs3Re9fRg76TC6z1rzyCez2joV/RGhKivbjWHKYaSbnGkoLcUrK9vvoKwoXZ1/ThWj7/yflIuR7dR5HYhQlYs9VvHVJaN45WKPfh6sqZOudbjXaeIRZCvhw66OoLqgVAmeq27fJ+g+x35xG/1flhk1d9jeqdxTOeqhykyhRRwpNbctM4XFLDNKz9B/GaX7mWHwT7EP0u+lBkTLmbnE2s/gJjnZuD70o7ipqs5aVW64jmBlsvId5H3v5dPd/rXrqFz68MzUvpPxRC5O7pnr3E/PGFvC57HnxD2+Hie6e+0W6Yg/XveZ6D7e3aJz0V6TQFiksfYjUt9fRv3MSaRkZ2RZ7j/BjXmPlMTC3acV+39S9k/p9eglMo/1jHEOWL8zEUn+Xkcee/5utZek5NTgXDYLNsH8IIfbbMD87UgxDwpkN0ld2U2SoHeTdNa7SYr/3o0rrL9KWB+nPahyS1hlPYP7592t9luFzfEP9g2/Zd9/mNIrQO9DzILL5b5g3CcSpuJ30OVPSNItfrjSICCeNSaHHwH3BnOumt7jw7P1WOecIeEO8FhPOYO775EfkB8RY/w/Crn9mqdjPeW38sZzNs17T7zvO6lgnDcz5aEy6v0TNacifcZp0Z59ypnquoXqcz5msreV99wrEsC1cW9JK66N+okm/UFa33MPZJ3OzgTYblffDYZ3EYa4Cp5lNIllA1kg8SirMp7U6w3x4mat/SqxtCyvFdzl5nBFGfc5vNZlfa7YD7FblVOj2+wqTrfcXK8pthT/IqzLq3arz4GemKPebziv9kYnVJayweSoe0x5n7h7xO52p+dnZV3VPbZh/3FSTg7B0WXasBY71Tg3ME38TLG7yyPTM4azrzuJfX97MH3+jbZn9Tr+GolfCb3mmyB6q41hm0hS6jOvu1ImHN6/F+acD+wS4dxfcpbEOofcy/U/4U+m84kdgegR4blfK/w2a5A9Kno7i0DlD1VmeOaYyTPXe1B4lmKGopid12fIyjMSs0vaTNJfv88lZVCnvelcWkkP01xZF8++SmWkIvEvrOiZ13Ms2iPLdryiO1+VlzGYuLZuyyve4Z5dg9/36Hc1LNYSLHUdVY/VOoLW1fXv+TvoF7rrQfczJd6YSbxvu99V3Es8nGbh2kzC69HnSu+hzqOk7xAFN8P2VfkRY3pWSbJWan5eeu20ouhH2hvwxK4jlvOdMXe2XxV9q2cjZTNY27ew6+cpZlbPyPp56vDofJWlsqW7X3R3JfHDbvWMjfeKUe5JJF1XdhW3w8RttMFttOne1aKkbzMqKVVeddZn5pve4Rc/HhI/p+q9FnUrc636oWOkwE3PyDHMa8wS/SdYE0qwLUDL1V9r7PTH3t22Q6dnCzGbYjfVqdovu9xrI/o+fL2iHMRch6E=
*/