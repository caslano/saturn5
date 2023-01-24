//
// Copyright (c) 2019 Mika Fischer (mika.fischer@zoopnet.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_WIN32_UNICODE_PATH_HPP
#define BOOST_BEAST_CORE_DETAIL_WIN32_UNICODE_PATH_HPP

#ifdef _WIN32
#include <boost/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/winapi/character_code_conversion.hpp>
#include <boost/winapi/file_management.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <array>
#include <vector>

namespace boost {
namespace beast {
namespace detail {

class win32_unicode_path
{
    using WCHAR_ = boost::winapi::WCHAR_;

public:
    win32_unicode_path(const char* utf8_path, error_code& ec) {
        int ret = mb2wide(utf8_path, static_buf_.data(),
            static_buf_.size());
        if (ret == 0)
        {
            int sz = mb2wide(utf8_path, nullptr, 0);
            if (sz == 0)
            {
                ec.assign(boost::winapi::GetLastError(),
                    system_category());
                return;
            }
            dynamic_buf_.resize(sz);
            int ret2 = mb2wide(utf8_path,
                dynamic_buf_.data(),
                dynamic_buf_.size());
            if (ret2 == 0)
            {
                ec.assign(boost::winapi::GetLastError(),
                    system_category());
                return;
            }
        }
    }

    WCHAR_ const* c_str() const noexcept
    {
        return dynamic_buf_.empty()
            ? static_buf_.data()
            : dynamic_buf_.data();
    }

private:
    int mb2wide(const char* utf8_path, WCHAR_* buf, size_t sz)
    {
        return boost::winapi::MultiByteToWideChar(
            boost::winapi::CP_UTF8_,
            boost::winapi::MB_ERR_INVALID_CHARS_,
            utf8_path, -1,
            buf, static_cast<int>(sz));
    }

    std::array<WCHAR_, boost::winapi::MAX_PATH_> static_buf_;
    std::vector<WCHAR_> dynamic_buf_;
};

} // detail
} // beast
} // boost
#endif

#endif

/* win32_unicode_path.hpp
tesHLLjEq8P9yAn3QwXfqAOfAW5FeKwolXlvawe+FcHHPNAHHfjW3wD/Yk03XD+Iwe5B2IsB9lyC/eLYsN9jOx/s7jc7hn1D6X8e9rTYsN+yMCbsO244H+zrNncM+745/3nYPZfGhP1vdwHstgmTdJwe6m3jwrAXu6XN2dUkdjeL8FpP9P9Lt3TGWbnH14VpyHa9YRKqqDcL8qprYcEYxL6ObE/eUXeATGfebLHypPcKl3ROSi4Kjk0oknoUBdOOULdxfFzShyCI2oGUws5xqVIj+uuMhZ8tPIj7bU8724soo1tqcEnJLDuaRKB7xdi9u/5gCuseUcuEih8bmh6wU6u+28TUPJdez/u1mjRTpOrZnm0klcjm7Ex4AvAVBvjjMbA9sxx7YEMjh4hAVOAWapMPJ2BhkCKqfX1wBPJhk34nwZCw0pf4jgAPxbLpHyah+UncEldnC/CAWtzISxXjYJSIgaeziVMKPkhPmPR3alAXsEsMpk960SzICW/Ctkcc1VfIYkypzqs2dyGigZt6EGZVscz+B0k4vArUbkKGbchbK55cVvgp+rIX28PNsNS/LDsn3WukZ4pvICMpWHI1Y6aCli27TKgbhdIVTqx7JedybTwbcjzbKr5TFM4xVphFnoqglYcyh8ULcSu9ycMQHXxx0o/6SswqICoXyDryp9eB0fp51TnEX7PzXGA75alUKmyuWSNtruBaG6pR
*/