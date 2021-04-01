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
hWNQmxsw2JxyAWKwN54csyS8ipeJyuBFYvTeIdzF/NeJNsE+HLbG9x0H4p/5WJtEQNXJXNUDCOtf3P29b+n3fWj7Cyhhy78rlsbWn+lJCxTwFUtaB1N+UHuZ1AuV+cWpDArkNWnrrvMfNFWPh2cQLwZgXRLDIoq0Ha9yXThInOkbBqBZEt/FogCHGpXb2WznJp8ZU1VY68vBC/U/GUDx2ZlU2eRlRTTSvheU5U8izCp/cKJhp9DEWg+IfKscEa2U4BjNZgy04cZGlVyhSnQ3BDesoc1PvkeyIb8YHKIDOoGCCOF3na4YgnNuF3vbFA7EgnIltXoY5944PjYZwstNUKmt3vmax8LrGNXv2mKSfZuH3eGwVwwdemvnwEykbi32L10JEW2yHBPDyRDcpEpucQ7hB9nM1zrVEE989tHeA9kGYJr/ogXUIByVS3mScR4qZYwsEViFeZy2zB4WUvYvx9DYKG8qI1qw6vDgZVQJPZ+MoyA8TztHydwjgt/2vx+L2coOwDuDsAemWezjuzlMHC4x39aOOFSmHZAQOl3WIONOiSE43C+BSTVzgw==
*/