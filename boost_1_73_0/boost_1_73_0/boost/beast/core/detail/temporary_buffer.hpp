//
// Copyright (c) 2019 Damian Jarek(damian.jarek93@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_TEMPORARY_BUFFER_HPP
#define BOOST_BEAST_DETAIL_TEMPORARY_BUFFER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string.hpp>

#include <memory>

namespace boost {
namespace beast {
namespace detail {

struct temporary_buffer
{
    temporary_buffer() = default;
    temporary_buffer(temporary_buffer const&) = delete;
    temporary_buffer& operator=(temporary_buffer const&) = delete;

    ~temporary_buffer() noexcept
    {
        deallocate(data_);
    }

    BOOST_BEAST_DECL
    void
    append(string_view s);

    BOOST_BEAST_DECL
    void
    append(string_view s1, string_view s2);

    string_view
    view() const noexcept
    {
        return {data_, size_};
    }

    bool
    empty() const noexcept
    {
        return size_ == 0;
    }

private:
    BOOST_BEAST_DECL
    void
    unchecked_append(string_view s);

    BOOST_BEAST_DECL
    void
    grow(std::size_t n);

    void
    deallocate(char* data) noexcept
    {
        if (data != buffer_)
            delete[] data;
    }

    char buffer_[4096];
    char* data_ = buffer_;
    std::size_t capacity_ = sizeof(buffer_);
    std::size_t size_ = 0;
};

} // detail
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/detail/impl/temporary_buffer.ipp>
#endif

#endif

/* temporary_buffer.hpp
fTNFKL2dCp5I147S4Yl+TMm4fkoJygHuwdA8ZaF4FRCONUs3CqIGw8sRguzgx960D/lIR+0Xr+tfXvbPp4Mf+w5GsFqfS0mgVCVthm3s9ExYu37b2JheYNMGbA7D2B7FoqYMSqHKkPTOa0olocr581QyHINQXZJqK14o3ahIrO2r2pWPlCaODEHld5S7kVugXClSE4SojuRiqLLmxSyOiYvOCbyZtUhirsE4fVSW3DBuHF7D2ts0rzRvZZ4eW2fqNa1Mh08VICul7Ihv/HCsVyDnTAfXfRyTLbo4w6023gh2LbOt42cFwdGmXlulF2tOrQgqrBGXvatJ/0Qr+jbBrlX6zmmUUp9w56S4WimDU0hdFCyU59XVTq5fMA1Hnw2pvp6t2Y30waGKkZGng2IxTdS56EyF5twja6ynGr97YkyCpukVB/m9k0k6rYrd4VG3212bU6hJVjVrl2a1O2puHZA6nc7mBsVu6JNb4c8xXWISuVbNAOrbbQpnrwvSZoaHHVrdoayoWktFz/6RLX4pkKf4kqBedXDokHi+WnSJWBBzOwPqK3T/qC4BN3RUnyxDwhVTgsqb6lT0uE9B1LjmRsXLtHjoUOVRNcHOTkW3zfuF7dbScGh1USoKpaK1rgiyYYB63SC7J7/j9SZF
*/