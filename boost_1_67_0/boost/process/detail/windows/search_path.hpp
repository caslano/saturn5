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