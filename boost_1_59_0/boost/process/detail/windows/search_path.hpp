// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_SEARCH_PATH_HPP
#define BOOST_PROCESS_WINDOWS_SEARCH_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/system/error_code.hpp>
#include <string>
#include <stdexcept>
#include <array>
#include <atomic>
#include <cstdlib>
#include <boost/winapi/shell.hpp>
#include <boost/process/environment.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

inline boost::filesystem::path search_path(
        const boost::filesystem::path &filename,
        const std::vector<boost::filesystem::path> &path)
{
    const ::boost::process::wnative_environment ne{};
    typedef typename ::boost::process::wnative_environment::const_entry_type value_type;
    const auto id = L"PATHEXT";

    auto itr = std::find_if(ne.cbegin(), ne.cend(),
            [&](const value_type & e)
             {return id == ::boost::to_upper_copy(e.get_name(), ::boost::process::detail::process_locale());});

    auto extensions_in = itr->to_vector();

    std::vector<std::wstring> extensions((extensions_in.size() * 2) + 1);

    auto it_ex = extensions.begin();
    it_ex++;
    it_ex = std::transform(extensions_in.begin(), extensions_in.end(), it_ex,
                [](const std::wstring & ws){return boost::to_lower_copy(ws, ::boost::process::detail::process_locale());});

    std::transform(extensions_in.begin(), extensions_in.end(), it_ex,
                [](const std::wstring & ws){return boost::to_upper_copy(ws, ::boost::process::detail::process_locale());});


    std::copy(std::make_move_iterator(extensions_in.begin()), std::make_move_iterator(extensions_in.end()), extensions.begin() + 1);


    for (auto & ext : extensions)
        boost::to_lower(ext);

    for (const boost::filesystem::path & pp_ : path)
    {
        auto p = pp_ / filename;
        for (boost::filesystem::path ext : extensions)
        {
            boost::filesystem::path pp_ext = p;
            pp_ext += ext;
            boost::system::error_code ec;
            bool file = boost::filesystem::is_regular_file(pp_ext, ec);
            if (!ec && file &&
                ::boost::winapi::sh_get_file_info(pp_ext.native().c_str(), 0, 0, 0, ::boost::winapi::SHGFI_EXETYPE_))
            {
                return pp_ext;
            }
        }
    }
    return "";
}

}}}}

#endif

/* search_path.hpp
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
*/