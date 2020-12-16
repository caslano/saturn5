// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_FILE_DESCRIPTOR_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_FILE_DESCRIPTOR_HPP_

#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/file_management.hpp>
#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/core/exchange.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

struct file_descriptor
{
    enum mode_t
    {
        read  = 1,
        write = 2,
        read_write = 3
    };
    static ::boost::winapi::DWORD_ desired_access(mode_t mode)
    {
        switch(mode)
        {
        case read:
            return ::boost::winapi::GENERIC_READ_;
        case write:
            return ::boost::winapi::GENERIC_WRITE_;
        case read_write:
            return ::boost::winapi::GENERIC_READ_
                 | ::boost::winapi::GENERIC_WRITE_;
        default:
            return 0u;
        }
    }

    file_descriptor() = default;
    file_descriptor(const boost::filesystem::path& p, mode_t mode = read_write)
        : file_descriptor(p.native(), mode)
    {
    }

    file_descriptor(const std::string & path , mode_t mode = read_write)
#if defined(BOOST_NO_ANSI_APIS)
        : file_descriptor(::boost::process::detail::convert(path), mode)
#else
        : file_descriptor(path.c_str(), mode)
#endif
    {}
    file_descriptor(const std::wstring & path, mode_t mode = read_write)
        : file_descriptor(path.c_str(), mode) {}

    file_descriptor(const char*    path, mode_t mode = read_write)
#if defined(BOOST_NO_ANSI_APIS)
        : file_descriptor(std::string(path), mode)
#else
        : _handle(
                ::boost::winapi::create_file(
                        path,
                        desired_access(mode),
                        ::boost::winapi::FILE_SHARE_READ_ |
                        ::boost::winapi::FILE_SHARE_WRITE_,
                        nullptr,
                        ::boost::winapi::OPEN_ALWAYS_,

                        ::boost::winapi::FILE_ATTRIBUTE_NORMAL_,
                        nullptr
                ))
#endif
    {
    }
    file_descriptor(const wchar_t * path, mode_t mode = read_write)
        : _handle(
            ::boost::winapi::create_file(
                    path,
                    desired_access(mode),
                    ::boost::winapi::FILE_SHARE_READ_ |
                    ::boost::winapi::FILE_SHARE_WRITE_,
                    nullptr,
                    ::boost::winapi::OPEN_ALWAYS_,

                    ::boost::winapi::FILE_ATTRIBUTE_NORMAL_,
                    nullptr
            ))
{

}
    file_descriptor(const file_descriptor & ) = delete;
    file_descriptor(file_descriptor &&other)
        : _handle( boost::exchange(other._handle, ::boost::winapi::INVALID_HANDLE_VALUE_) )
    {
    }

    file_descriptor& operator=(const file_descriptor & ) = delete;
    file_descriptor& operator=(file_descriptor &&other)
    {
        if (_handle != ::boost::winapi::INVALID_HANDLE_VALUE_)
            ::boost::winapi::CloseHandle(_handle);
        _handle = boost::exchange(other._handle, ::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    ~file_descriptor()
    {
        if (_handle != ::boost::winapi::INVALID_HANDLE_VALUE_)
            ::boost::winapi::CloseHandle(_handle);
    }

    ::boost::winapi::HANDLE_ handle() const { return _handle;}

private:
    ::boost::winapi::HANDLE_ _handle = ::boost::winapi::INVALID_HANDLE_VALUE_;
};

}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_FILE_DESCRIPTOR_HPP_ */

/* file_descriptor.hpp
/lK3QcvelxqQ3cTvNJXGHsigpCVD/Z6s3K3DFNp+Fzn/hrhNFopZr9I5A75nO9vxRn6vVnqUHXmOk2AxVHliTxPxVH6GpI10YNCz2V+CH7PgFDgVU430lcBM+CHyafw+g9/TYT4mC/fl6t7N4HoNnAlnYezhXZoe0JsN16j0zkknjcrtZfxeil/Fyt1uzNx0KQcV7nW6MUS+p2f7N+iN1POGdDv5mLzXVpf1jxmeyq2FzrjYWgvdaEBwXXFrvf442ZLp9cff99cyvWa63JLpNdM7LZleM/24JdNrpu/WslZ6zfR6S9ZGr6O2ZK2DsrmWTK+jHmPJdDp6WDKdjrMtmU5HVUum01E0QMt0OgxLT6fjUL+g7FydjnctmU7HS5astc4XS6bTcZ8lO1fniyXT6bjWkul0lFoynY5eWtZSx6WNJdNxaWDJdFyqWjIdl0hLpuNyoq+W6bg8ZMl0/t1pyXT+rdKyFjr/FloyHecCS6bj/EdLpuM80JLpOHeyZDrOTS2ZjvMZlkznX7Il0+nwWLKmOg/66H0BdDq+tGQ6HfssmU7H05ZMp2PQAC2TdGQimx2Q8bEvp2h8Dt8E1GBYAnbPDQvaBdzv9cfx71z738n/Lp+KTM1dQibzTGRtuZ6fkqTmDyBTcwzSkWUjqyMy/a1f5NuQS9i2b/QJyGsg3yXhzxS9mVpPf3sU+QbkfM9Drr/niXyODs/6ToJcxttPSBqscXjZ1wD9Pj69r4Hottfp0GOyIm+j5Xo8VuRrdRz1u7j4XY58n6SFl64wsnS7zHo/Iy/OS5oi94w+VFrg+v1+gesPMgPXR0OuI/tXvN6bHbiuWiNw/erQwHW5su+QG7iemBi47q+uz1T6+8dp9zIS0ESt818pTwhz87D0wj/Di3z4K+1IqT/j88fPCrzTvVXdL5vJ5BvHNf7KjanH9039Ldz6jvWp6Ix2Wvev3Qe/gZnyDcx57we77i4JS+aAOOz3oHX1vD1Tyr7jfg9aV58vr78jO+/1oPXVeKhpm2sj8w1s+jUsff0N16TMB3V9Nl1fiN8nJC4VvzvVtenXtfut81/mWYluA5tuA0tXf8M0rW+Yot/Ypt/Yrq/nfuo5AqLf1Kbf1FFfj1WJfkubfkvHsmONVcp3Ept+Gyd9PU9CfXOx6bcPyZtkiY9UBqLbyabbya6r4y7jh6LbzabbzTke1G0MjKrylWXTz7LpqzmV/Crw9/5Et69Nt69jHup5aPp56jEJOadn+t0PtLkf6HSPQ743Z9v0s530Q+Z0jbDpj7Dpp+v42eY4KTejbG5GOaUpZB7KaJv+aEd9PYdE9MfZ9MeF5O9sNR/HPq7+g9jvMO3f2RlJVd9oZK0j9vUZCffa9xzT9i+LfXe++qTgp/52jdT6/vGNhPGshLEnUX+z1mNrR8R+p9nbuFD8nKTeI19W7y+epAAvTw/wVSV/TYiuYin2KWHOPk+075Wi+hG3F+h+hO4z+Ov0NFWnp9v3nrHqbtGNg+QXcqmTRYaasUt0pe7V+83o/oXyU+pJkem6VOQ1IHUmcl1nih8+eL7qDxhKty50avMb6PhKXSe6jZFJv8Gq00TeVPeRdN0l8pZarusokbfRflt1kfQptNyqc6RvBW19JpF1035LHSLus7R7q65AV55/6gTkUieI7kDtXj/7Is+GTn2jETC0j5aJfJT2x/aMKjejoVO/bJyW62eu4l5R7Qz58+9REQWHwJE+WQNs6zvk+HlK/Qfc/Wb/IQk+JzqpzvsGFZx6/6Gs4NT7D2UFp95/KCuoXP+hrKBy/YeyglPvP5QVVK7/UFZw6v2HsoLK9R/KCirXfygrqFz/oaygcv2HsoLK9R/KCk4=
*/