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
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
*/