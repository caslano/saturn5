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
BwpjpWGmYaRh6cbTXlUpnBHbxR/3Nvfabopt+mxy9lKbcl60qzZhgGjOPTc/mtLV07e9WHp2XYkSYnTCdsRwfO6IJYTxl8pbhfXlhbRxDmC3BTPzF2i/dgnLD9eZux6rjajNZIb+A0rN1EpmtVVrxYkg3WioIaKdezErIh1jPGLgsSMMZ7LlCxPvq5fpF/Sr1O7VX5qaw6VWv84YR1MSrjTIzHmGnbXfOVbBRIn5anpI1aq2lxYbQsyHOifm1DptRF6snkia3mW2kJ9eGWj204t9+0By4G/KQyFYpOZV9SvttbTMq93Ku+u9KIxxId/sdOB8N4xWzFqE9c1382GGT/OON4vdAAJZy28a3fs77pAqCRCJUVS4PcBWVlPBi033qDE74rDFrvWkbbsHe2L7I0OirwN/IdDyQ0UGqUjASNP25prZhyeSj3nLZoN04JMmgXORFL8NUg1vEwHLfV8G+xs5OQgGh+Rr3rCQonzzJaqo9NOPcaMcfYtYa5q8BvOPnKwB8C/gAVqem25iRlQYcI8vlr71kaTlTy8LO9Rpo8VTkzYFcxq0Tnl9e1/5BMn1OhOUVDgvFoDqBHS61in/gOMX2zN0xhnbI95B0+rT6tnqY4D1Kzaopqd0cnXFryZIx8kfC9eGFtzn8lXzjFZPLMZlLuvApe1aXt8Xt9ra9x0m1A1j0bv75brHehgOd9tTrPV8U8FsIG95rrdg
*/