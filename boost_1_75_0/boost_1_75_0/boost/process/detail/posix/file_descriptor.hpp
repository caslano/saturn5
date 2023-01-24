// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_FILE_DESCRIPTOR_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_FILE_DESCRIPTOR_HPP_

#include <fcntl.h>
#include <string>
#include <boost/filesystem/path.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

struct file_descriptor
{
    enum mode_t
    {
        read  = 1,
        write = 2,
        read_write = 3
    };


    file_descriptor() = default;
    explicit file_descriptor(const boost::filesystem::path& p, mode_t mode = read_write)
        : file_descriptor(p.native(), mode)
    {
    }

    explicit file_descriptor(const std::string & path , mode_t mode = read_write)
        : file_descriptor(path.c_str(), mode) {}


    explicit file_descriptor(const char*    path, mode_t mode = read_write)
        : _handle(create_file(path, mode))
    {

    }

    file_descriptor(const file_descriptor & ) = delete;
    file_descriptor(file_descriptor && ) = default;

    file_descriptor& operator=(const file_descriptor & ) = delete;
    file_descriptor& operator=(file_descriptor && ) = default;

    ~file_descriptor()
    {
        if (_handle != -1)
            ::close(_handle);
    }

    int handle() const { return _handle;}

private:
    static int create_file(const char* name, mode_t mode )
    {
        switch(mode)
        {
        case read:
            return ::open(name, O_RDONLY);
        case write:
            return ::open(name, O_WRONLY | O_CREAT, 0660);
        case read_write:
            return ::open(name, O_RDWR | O_CREAT, 0660);
        default:
            return -1;
        }
    }

    int _handle = -1;
};

}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_FILE_DESCRIPTOR_HPP_ */

/* file_descriptor.hpp
S06QrCeWQSDvSqidbt2BwW/Ex6vm9/Wdxly2Ic87xisoPr3I+WFI7/v+8ikI/+qjMMYeO2Zj71yOGI4kQgfLuhODXzZ23toK2wZVKbngdQZbfJBj0GrwnWViHZUttriQMBLnXb/4+8/huKbvSTVz2uaU2uRU1nqIVFQ60HV2KNuwKUNldpwcJbHJ3wA+9n2P7GXkR/ug0PeRWwLDNgxy9eY8dKQAv2NH9kr8U3yv06ewRkdKVrGPMAq4gaimTY0H8nmdxYt4mZbp+npS/9Nbb3Mhg6itcLIrrC4UQwnr3i9zXb72hx2jAmtk5z9OZXsAiTagef9euDxPnWB7wQc7SjGfhKyWnncZOx98KQ2kbtiV9sPSEvIvZchlahxZcmo5i5nSiQZiwujQzzCWP8i3PTsQDVJmEGMcaqE5zxWlZjgjy4fRLWOupdVUq/ag7jflKLEIN6lE3P4Z/q65szJkWxvmclRbWkvIXlPw4mt8/WLijfu8tc1bUs3jD3pbrhowZOmIXzyu+heGv2AWxD7kcAnyQ36E8Xrjw98aSLYZ4fa8ZyvENIjQ3HHpndQfmEMh91uJtd/xlclbR3CqkhJtm+0POBWpMyo3ysTo7ZktT52ixMbVtphy92tl2ICSCG7eov7RfIOVBRqMfBrspM5zBrPnW/7cdD6DygZlAWnk8FmO2GpZ/e6eTedZLvVrLRIuYVug4y7bzpj89Vmy
*/