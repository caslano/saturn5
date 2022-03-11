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
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
*/