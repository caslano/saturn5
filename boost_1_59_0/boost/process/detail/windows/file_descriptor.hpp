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
        return *this;
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
+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
*/