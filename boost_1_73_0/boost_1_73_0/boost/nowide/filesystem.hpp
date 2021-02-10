//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED
#define BOOST_NOWIDE_INTEGRATION_FILESYSTEM_HPP_INCLUDED

#if(defined(__GNUC__) && __GNUC__ < 5)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <boost/nowide/utf8_codecvt.hpp>
#include <boost/filesystem/path.hpp>
namespace boost {
namespace nowide {
    ///
    /// Install utf8_codecvt facet into  boost::filesystem::path such all char strings are interpreted as utf-8 strings
    ///
    inline std::locale nowide_filesystem()
    {
        std::locale tmp = std::locale(std::locale(), new boost::nowide::utf8_codecvt<wchar_t>());
        return boost::filesystem::path::imbue(tmp);
    }
} // namespace nowide
} // namespace boost

#endif

/* filesystem.hpp
y/TXswm5h/0PUVucj5H48AC5Jy4ch9zD0EJIz/LCrAk5RrQ12szFN8gtMUuMIMwgz0V7J/mu1DA8d2F8evo7/AaTp5OnHsxow1kFa82alMmdBy9yG/mrpLe3I8X+9IBpoNWoL5WUXIEShb6hkgGuK56xRrEcqIKcqUzyFDe8AV0yKHjF4DxabebLCw9uSp6Vpsid6ECVoqtyKOk1A8kyxq/3NVoqNYgC4Vg850pjwU5z0YyQm4FmslamhqGnlRJArymvaIpEVEOpdaue+37WyQrV+7nIlJ8dHn9U6vrTk2xQRE3vQLQatIBOMQ9Mpge1yHlhZjQEg22XVlyV3oMapGpyX0hQrKpMLcRxpvayGax7ezyTBi0q5tpMSjTKUN2Uov4sEX00VYpONkiEPmBSLtBmD7omZ9Im2yc/UPSeWoO/2ZoHvTmIBsXAIFjDfD2AlCquPHg7Ty6jqwTeBnEcLJMNRC8hWG5MsVfz5Qxbz5FMArttJVNILoHXbcVZ3nP+vOE7zi+8yaouZzDQTGGvBo9DNatzlnY7G+YNtgxzhllJJZxcxQvXee8AnOMKTkzv4Q9YXi0W0z6YidycMoVhsw3Jy2C+CGdkvpwnJsfWSfHOv8/Gk/9MpFZNK5GnGJqwB4q/Y2K/cT3n8as3
*/