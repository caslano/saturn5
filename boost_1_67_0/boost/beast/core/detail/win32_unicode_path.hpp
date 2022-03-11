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