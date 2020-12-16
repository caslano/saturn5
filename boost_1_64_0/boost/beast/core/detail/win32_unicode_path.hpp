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
ncnbjd3X9WwpCW5dD9pVua7nY6nnuh62d6yXAU9DWzei1vU419BEuM8tY03F3PAE0M2N7fRzmyP1nBvbO+d2RIhrYnRzK4x0n1vq2oq54Wmhmxvb6ed2nNRzbmzvnFtui7qdG55Z9OVwX4+VVlL9eqy0ytcX7tfQ12Nt0IyptFSNSV5SmnGxnX1cw+tgndjYvdzHVW4ZFy5x7bjKXcZ1dB2Ma5tmXIVr1Lj6puj5xXb2cY2qg3Et2dt9XJsqxmXeNnrfDZdxTW8R+rjuauK+3q+gJLj1fminX+/Heut6vxukrF/vd12Jfb1fAcvWeY8J8bkdzHq/PuTP5qbu/IleY+GPXOk6HrGtnkeot/Ooq5T1POq8xs6jaJZtz54Qn/814dG2fdx5tN3KI7m69TzaXg2Ptjt4tNfaqnkUsdbOo+0uPJoR4nskGB7tQDmvFj4d/1Xfjfr20RgjPhrzh95w597Dnkk66tbJO9+6dlb27udz4e5bofMZqZ3PRbJBGZnyXbbVNk4fB4M+DpH0cQjQFVRBdwPpbiTdTRa6wiroVpFuNelKLHRFVdBtJd0bpHvTQldaBd0XpPuSdF+pfcIpw1E+zbbuE07bfSfa6rvRVt8P2B04kLb6I2ijHw3sQ5+IgcAZwMHA0xnj8S7u176OvhePA48Gvg48hjb/NGATjOF47qs9FtgROJ4+JROBg4GT1HpYyjN81mY71sO25XrcdlyPmwBMZJn0kBn09BeQ/kLSX0R6lEnP73IN/eOkf4L0T5IeZUWfxvG3daGPpc9GcyAyY4NKWdGXlurp55B+LunzST/XQl9eBf180i8g/ULSo0x6fidq6NeQfi3p7yc9yop+UxX060n/AOkfJD3Kir6A/BvgQt+S7VsBu6g9nKRMen4zaOjPJf1i0p9HepQV/fYq6DeQ/lHSbzTpWd4ahvuzFLH+kMciz0BeUhoZlD8K7P0OXxSX9djV+J70Q/7zzUZB+ZxsQd4xBBlI35JKfiUXAYuR6Uui9SOx+5AE4TuSrPcXuQtZ7yOCertfiM4fBCejkfiD0BfE5gNC/w/6fTh9Pqr396CvB/08Knw7Nr/RyO/fUYt1z5V9OOz+GwUOn42dyA4/DeWjMZm+GYXIN+P6K0PegrwNOWpNpNEROQV5FHIm8iLkQuRi5E3IbyNvR45aG2kkrPV8OLzkJS95yUte8tIutv/PycnLys0Mef1/q4A9X+z//k57D0hWMQAHW2IAHqixp6eWKDuy6qCmMQAbaWIARgdpK4yuxlaY6LAVRrvYcoaEqE/V2ZyWhWnsFaurtzmhTaVxDq0DW8WDmhiAm1YHZxNAO70ul/VWXe47Utbrct+UeupySe/U5aaGeH6C1eX+l2MAuq8D2/10vItFx7vquqWb58y/+6kTm/eIevKu2eN16wJ3nY63rtYF1uU6vGSDz2RNDMB+1Jn2p850gFVnVKKPAdieOr9E6vw6ABNZJj2eV/oYgC2o84oHNg/osFgmPe57fQzANmx/AHVObYG9WV4U5HqnlLVeDMA9bb1TXccAbNSp8S5b61RTfdjuusZpLO6jPOQlyMs83ZiXvOQlLzWc/D9z3owZdej/nyDyv9mpiP4i+w9MNJQPeYLOl351QPYHnQyqZnL/NvYbwQaNA7H/Vwcn9/vbRYhfNcbmKv+PdLSLDkI3YcqHUS5yZHQVcv6CMOdc6FsahJyfZp1HLcdn5WtBuGMslO8zgpTvM+zj0cr5GXa+usr3aY528bWcH/lfSY6P/x/K8TWV13dVPJ11Isf/1OH2y+OfbPdP4r6z7nxh3Gfj6k5u3lVyf0PE00k2+HzVyPG9KMcnU47vDVQ+YaSLcKFrQ7o=
*/