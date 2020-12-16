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
TxjP6ZgZ7va9VgPnnEhrWy2r9lT7Eamfs6May8hR3uhnWkf8CdZjhtPibgK9+JJ8caq63fXOXpLoVaRpKNR7fZxhGGwPVOdzcA/9nuM58Wcl/pQy7AmdNjF7nKtNh+J+tD2Te5VxhzMj1XAG1A+i08dWmhCG6fNLOKfX8L35aPiY6H1K+9VJxQVXYlbXfhfrJ7+TE9TZOzrc7nCN0s82DDYR++r28rQQL9N/cfUH8gn0x4Yz9MuEU+fAKtBl5i+/MS/mXCfpar2vU+e3UJU/MNP5xrx25s4fxnx+YoI6LxgRqndjcxsa8vmMtJwJE435nIQ15I/5olvSqi7CH/OZp5ziap2n0S3uez/BgG+piL77eru+9g/d4PztOJtcrp/R181NaShxMX03iDCa2v+Dk5wBeB5PSsNNsE8Uz6uRSqecHDIua70c+D4qOWUcKuYz1KzSB/fmcoxuToZHW/i06JSz2I9t5d55fIflGrBJv3eUmv9kGdA4LmgrOjP5opWPlNUQ7e55e6Ktj5770+am8wBzDGWupthH2ofa/PT4tuNdkofEzSg5C2dKhnFvTgNxs8jOGe6Y6TXFbL7n57iFnocdKXqD7Gqco3WS2NIx0fB+TnvRizHUMaTxaJsu6x3FfpphX+NE9fzUeaNi/4eea9gh4ffnLLAhUv/4EGhfxFG2/aA/UgIpiazGLACWUuY9DH2fvWpsAHHnrg/8ivEOsj7Tzdz31/nHXP51vtDzhDx/zNXzN72fGJfjvOkwxI4MRXrR/u2RuOc6Jnw4MIeNKBQfXlOWtI2J+cszYnBr7udSR09Js6wLtK5+ZlMJpbvO+Unsowz2Odi7890xse9iC+J/b+8AlI2TuW19lgv1Nu8t3tmZHcTZ+vwdFTc5X/wu9zehjGncbvKtaXyVDBcb50zjiZkZKRnurl+xzsPCrU63qc7zNjkqwf0uRZzYd7dV0GmSNj3LcR+GLxPhDEO93lx0Y22u85qDSJtglc9LwzJIWWHx3202nttkbIcuTXEq5yMlkSXIs452yJkWkgQca5mdPMP6DJhouER0H7JMF/wxf3szY3KmZd5D19xmucc94XCB2C+0rF9xq/vOjcpJe6fr8RfEro/VXDHuvPe5C8RurM3Y/9VSrPGM+XwZc16VtMDMWF+oOKu6grhgluqRfxtMd97kTcTH9W2zKty/seGZjeIYuCnjk6YmZ5ufmy6rFUR/h609vli2kY0N3zqJ8BwfR8GGYh9vq289nhH35non21v72Njy2Vs8M62r+5x2aVfSso1txwjRGWG9D6Kx92c+XuySDHaZOh+li10/5/m1Kj9ERAhFQqL+d/mD9FZjWPP+YdJQz7Ea84x7/zBpgplKE1N/qr+0UNQHiIzx1Pkkhwx5R73wlp6WMo7WyFju3d80jIQ/iptllnkH/8xnP+k0/lzsNljlGdyZzyKTcDhehtLP9rTotLfKR9p9pKf7tPHJGZnG/FGliaxVWeQvr2HIyDK47yXu61nkL+1efwspVOWLMMVyUf9J/pC0N59PZTqvzJ1WFYxz8MY00PnEaEfcTO1Cs1nOgBSodmG9WrPNbeLOJ2oc7rV+WSK6j9uSrL8HhF/WbYMe34h9mHVb0cTy/EmLPKF19Rkr1C2OD5TmGOuyp0RnDqfh1LXME/p+xr6soU+zT+xr67rhlPmcMsVGofAOvhNb3LZDn8Fo6GfKWS/uuHrun33QebMUxBcZhYwjsrFN5flmJ09wr2cEqjl9yr9+trVFbyD3st7nLP4YziuyO+f69bMdLPZBVs9Wu/W2N6Gu2A+2MaYxrDeMoh/qngO6S3QSiXNJViX8VBvuXCsIR6EwhDxdrOfgH5o=
*/