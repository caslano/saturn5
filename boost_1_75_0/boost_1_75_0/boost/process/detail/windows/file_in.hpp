// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_FILE_IN_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_FILE_IN_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/used_handles.hpp>
#include <boost/process/detail/windows/file_descriptor.hpp>
#include <io.h>

namespace boost { namespace process { namespace detail { namespace windows {

struct file_in : public ::boost::process::detail::handler_base,
                        ::boost::process::detail::uses_handles
{
    file_descriptor file;
    ::boost::winapi::HANDLE_ handle = file.handle();

    ::boost::winapi::HANDLE_ get_used_handles() const { return handle; }

    template<typename T>
    file_in(T&& t) : file(std::forward<T>(t), file_descriptor::read) {}
    file_in(FILE * f) : handle(reinterpret_cast<::boost::winapi::HANDLE_>(_get_osfhandle(_fileno(f)))) {}

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        boost::winapi::SetHandleInformation(handle,
                boost::winapi::HANDLE_FLAG_INHERIT_,
                boost::winapi::HANDLE_FLAG_INHERIT_);
        e.startup_info.hStdInput = handle;
        e.startup_info.dwFlags  |= boost::winapi::STARTF_USESTDHANDLES_;
        e.inherit_handles = true;
    }
};

}}}}

#endif

/* file_in.hpp
L2xF0GGaq3jrnczVTU3tjHdEjHcMnG4MnEb7k5O35tU0mKeRalHCqt1ympt1fhuJgSe0tjqxszmztebXV9VVSdfWIlG3QBwqEyqtEp5VVNFUioWQfC5AhZfic6Lm4eu3GBpjw1NWUVbmXCaKavn6W+WspSWXpYblXGm+in9wScn9ORyMaOxL+M/V1Uu7DsMGpy8UaVGJs0WGupQpG57erkMlpdhre+vr96WlorXNnbUnOobSPvUlnPrGjPzT02oQfAaeviEX8x4U+qR951j6TXdli9RpgymrumAtedOABrWykt9wB9bJlRzGLvS4cEXRd0XJrze7CdUr838EdS2jE6NY6Wrglf/q7q6OBjp8mr/2+4MGTUhIEcm9DTsBi4uLyx9VUVxcsqrK26amp5Vt+c0Zy8vo+PS1E8rUDo7iZe+eYYSFdQ0MLP8Y+dwn/ZtQOy3dcGJOxSe7orMsvFYZzYrQqhkq2ItF2wuhP6O80eRwprVaY9w3Bsr6ctIlojE4bTax6HuZDaxGfbgLdknf6EZycano74eOihoXF29HiSI2NbUxNc1CQXkDAsWHh5e0bNysrESNlB2lWAXpkJWUStjYjjDikpb4DI64LFXrlTWJGaoSB//4TTztS09ZUvgUscDpGuB3SnqgEYcTU/72LV0HVQ1Z1tEkn5qW9nwobggaYIRKrPz4VPL6Vk8DOoaOzhxlnTu6q4cTixLV
*/