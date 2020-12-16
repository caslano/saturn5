// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_WINDOWS_PATH_FROM_HANDLE_HPP
#define BOOST_DLL_DETAIL_WINDOWS_PATH_FROM_HANDLE_HPP

#include <boost/dll/config.hpp>
#include <boost/dll/detail/system_error.hpp>
#include <boost/winapi/dll.hpp>
#include <boost/winapi/get_last_error.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace detail {

    inline boost::dll::fs::error_code last_error_code() BOOST_NOEXCEPT {
        boost::winapi::DWORD_ err = boost::winapi::GetLastError();
        return boost::dll::fs::error_code(
            static_cast<int>(err),
            boost::dll::fs::system_category()
        );
    }

    inline boost::dll::fs::path path_from_handle(boost::winapi::HMODULE_ handle, boost::dll::fs::error_code &ec) {
        BOOST_STATIC_CONSTANT(boost::winapi::DWORD_, ERROR_INSUFFICIENT_BUFFER_ = 0x7A);
        BOOST_STATIC_CONSTANT(boost::winapi::DWORD_, DEFAULT_PATH_SIZE_ = 260);

        // On success, GetModuleFileNameW() doesn't reset last error to ERROR_SUCCESS. Resetting it manually.
        boost::winapi::GetLastError();

        // If `handle` parameter is NULL, GetModuleFileName retrieves the path of the
        // executable file of the current process.
        boost::winapi::WCHAR_ path_hldr[DEFAULT_PATH_SIZE_];
        boost::winapi::GetModuleFileNameW(handle, path_hldr, DEFAULT_PATH_SIZE_);
        ec = boost::dll::detail::last_error_code();
        if (!ec) {
            return boost::dll::fs::path(path_hldr);
        }

        for (unsigned i = 2; i < 1025 && static_cast<boost::winapi::DWORD_>(ec.value()) == ERROR_INSUFFICIENT_BUFFER_; i *= 2) {
            std::wstring p(DEFAULT_PATH_SIZE_ * i, L'\0');
            const std::size_t size = boost::winapi::GetModuleFileNameW(handle, &p[0], DEFAULT_PATH_SIZE_ * i);
            ec = boost::dll::detail::last_error_code();

            if (!ec) {
                p.resize(size);
                return boost::dll::fs::path(p);
            }
        }

        // Error other than ERROR_INSUFFICIENT_BUFFER_ occurred or failed to allocate buffer big enough.
        return boost::dll::fs::path();
    }

}}} // namespace boost::dll::detail

#endif // BOOST_DLL_DETAIL_WINDOWS_PATH_FROM_HANDLE_HPP


/* path_from_handle.hpp
Ga969IAs0p3qMCeqF04bxH/FCzr+arC3cGlFl1imM1cSbXGaIvVV9fEV++63MbEb8P/4vChKpW5ZzqXqre/x55317aiWJZPCd26d8n+5p77yjuIjqLhVusu/ahv2N0kGRIaqOu3zl2wGRJrLOZJQ7e8HV6DXj5+28RWLgAf58736yieluANpFVq+k1eh83kVWrZOSHH0NDxCXAJ0U2Ypgz4Q0IX3p2wCcoIAMtsOJB+AoLInwFIs8IRnSIoNwpRru1NJsevBwqjmUutZimAGHWWN4jAIcdRY8iUShPrFUtqP6n/1Pax/mb3+Fx6Fdbc/Lbm5lO8eka/Snu9OzNdcVBVLpybOXIPt101Khr35G5iUaEdRX2wT48F8tcKlK/OodS++y105k1u35RHRle/xgZO4HvsX+iZKg87/KA7TeRKROazIHKYKZogKrrZXMA0qiM0hMudTvpDIV2nPNxLzHUf5IpRvf5Fvtj1fB8zXh3teoIIrsP+kV8oz4MNnXv4g0EDvrtYbfx2hyckPztnK/BLovzGXGANedMfVCxYrKeWlADI4zZOxhxGMvS0BVqcmJHvmy9sGYl1Vj0y+c59LTczq3epzXcRv29JQhfysZcfG1Jhs/d2Tr//cptfv6L6//Z35sfIYlGt+eKfkyQ2Xn+FWflI9Kwp3tQakDwHBNgbtkK5+WEJKWh4TAN94xgIYtkPs83Ay6w35vyIoVtkub3NZt/yFz2jr8aQ1tKUP3SLLJCnvCkgddUhtAJLlhgdhTlssYSYxP5/frIHashoC6pWylze7QQEZ9u232xJDd/r/00HNXU3tO+vmJrRviA5pwGpn+859OPn2xTZpoD66S2tf20TtO9nePp6AKy1QQXMFgmJ3xojVJTfhGi82UW2kVnfjZEzoslwK9cm0n/wf6DUNsNWUb5voUx7iOrtynfYsQ6+vTcLsMKH8fE+1hspdqxgV/Yh6WzVj0YWxEElgbZEB2cwZdyWLhAu/p9cxe1Sz/ePfO+uvY8onarrBcx2/oBVjKu7Q+ZITCnRferQXYt6/U7YBsqB4lBvFLC95yHj6Act4usrQSp0IoMEpHGa9w4OqklxcgYewSe2Or/ajHRilwC6dLs5ueoDFynOgHNMNCuWYlRs58U+QyKTLq8rRYcy5lrP10bNJOAFzv1WcoZne1ODPcRX/mVF/+0p+5vZtNrh9k7l9X37p3r737+eqy9Um1HoPNke8q3k/j45zEjXx2ms4zxgtT3vKQ7O+2MrTcwPWQER8EYwJNmBGosVTEFTqR36C8oEXhCS6fJ9Kok374XtBr7vz16ynNFbW9XbiryVVTeCvbzypQdpxm5O/7tiSPH8t10FddpvGXwesScBf17/mbB8fjjjx5RT+uSQlAV+guvMJDdV/riT63fh4E+h3vQ5p2Uon/VY+njz9xumgRq/U6LeNoTjHR4L2GTqoH2+l9t28rAntW/e4BunBW53t++iq5Nt3jg5q+q1a+wpWSigN8v9Swf8fZ/7/tOT/oByVLvqY+Y/1SIdZzPwP92h3gj+8xWL+lcz823sshxrajUg6nP9+aa3ijJ8Izpijc/6g+eYn+1EkhPlE/5mlzBYfk2f9WcSuzriVU27mOnZfxZHQmsS4nLuUXZNOkYhMZkT+5IbI8KXMNAdY/DSHEg+wEtsLFkoozq1gFgo6fOSfxbDX+o1uHur8b73O/26m8T1hadLy+s4qff7fROXH3NaE+XG9DmnZTc75Eb4r+fkxTgc1+iZtfjy8iaEksP/Qi7aS7Rl+d9L02P6YVv75FVS+/5Ym0OMyHdKCFU56tF6TPD2G66CGrNDoMeflBPxwycuCH3L4WUe4xXZ7eKw=
*/