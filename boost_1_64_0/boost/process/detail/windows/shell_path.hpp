// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_SHELL_PATH_HPP
#define BOOST_PROCESS_WINDOWS_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <boost/filesystem/path.hpp>
#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/get_system_directory.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

inline boost::filesystem::path shell_path()
{
    ::boost::winapi::WCHAR_ sysdir[260];
    unsigned int size = ::boost::winapi::get_system_directory(sysdir, sizeof(sysdir));
    if (!size)
        throw_last_error("GetSystemDirectory() failed");

    boost::filesystem::path p = sysdir;
    return p / "cmd.exe";
}

inline boost::filesystem::path shell_path(std::error_code &ec) noexcept
{

    ::boost::winapi::WCHAR_ sysdir[260];
    unsigned int size = ::boost::winapi::get_system_directory(sysdir, sizeof(sysdir));
    boost::filesystem::path p;
    if (!size)
        ec = std::error_code(
                ::boost::winapi::GetLastError(),
                std::system_category());
    else
    {
        ec.clear();
        p = sysdir;
        p /= "cmd.exe";
    }
    return p;
}

}}}}

#endif

/* shell_path.hpp
JX45P5xnM5wBwH0d5VI/F+LJNfE09en3POQ+cyQQaYpcZA57mSutpyWxbpCq18+kvb3N+BW3pvZSBh9W6al1A/UZQxP03m0Z9xRjv7CvHveYx+zc17BXX/Ic/staWlPPc4VeVtd5VU3f55h9a/oUkT6H3OkzLTtjsiwwUhIMZ2d4T59Dd5A+h/4H6XMl5M7T5ydT+hSp6yWm9FmRq8+Ak79QZA+BD2km6aO+4J+UNmEMX3XEzmrfQ7joliG+luUVvzzXdGaXu/1eclUO9JqusX7JnedU/MqH5wnfgRPRi1Nhnjg5ebI6Sc56z7cqxyNF/0mrPSn4ZW7rJ6RNS8qh35MxXe8b//3mzTGi95yPq+1OlOveevwS1Fz6fBZ5w+oeEzNT9T3cfaFB6h4W7Y/2w+q90Xyxq2OwG6uf2Uti15KRYKDk4/yqpvVQ4jaA5xWu+qIrw26VCOlrGGn87f1a1kv9i79eerbF7fd8VzC2X8ZnZT4/wpTGlCeJK/H3WDed1Nxz7X666fqp5npdVa6/Ml2Ht/DUr2i67sa1UX+HvjadKbVAnaWKZVM4DTryekhLQ17XranX/QE6z8eLu0SrM1/wsxh5nu80d2up5tFVno+T695WeRw/i5fHWyk/LfI4fnjP45liV8syj+eLXZytssrjj5jzOHFxj7e852udZ32Kn2cfalW8Nf7/Kt8S/kdM+dbeynSWiem6IdfGfDfGcG2sY+fnqTPdsawPp8HhpEOB6OfmJE9N8/pejXG97IDo/9PWhdi8b4u2PhuslXlMZIines5HRGerrS3+WOUz5Yf5rD/dr9sj9hn2vpbnmGj3xnyky8zLrWVPs96XX1qufQx7VqQPrfWPiX1fHfbZcj2QvmI0ZkY/1uDLbKWnzZBc8bt7rCm/ksHUOzbmOlnvTRsre7T0tftdSt/i593SrW9f33qece2ZL4NN5x1iJmEnPh559eHWnnnxe31tmkdc4gzsZFUH9of+PLj4Njov3nZ/lKuuGiNumuv1SvEDn4fZ/Ix5EnOveVLXWZNEp774FeDFrwCjX3quS9fX4vYy7yTNEJ229uq41d+RErOqohPsxX9lbrlHK0y927bIGU57OXHn9DtXzAIwO633aeW1lX1aan3I+n7a3HIMxV577veI2Ne2Mzay3I8VBReIji/L/Zt1mSgQMz/7c7Yu5vpc1nwyxH4iKV7PuWar3YxjnNmet1v9zWVSl8EpolfOXts2T5nhVoVhti1D3C01tw83PMvbGilz7vfbChGH+UnklDrfZ5XrXJ87eKctr23x2grrMudeEyJvaTf6fUqrfWLEa6luN0zvU+br75zq7yp05r89bZ1lLU3N4LnOVa0mY0mZBrBeH2pr8V1my7GS1tXjhMio248TXGMkwkFYJRy3ftdYfXt2BXEukL3tEoXJozI9+1q7ltpsQsSOvIZ8QtoVmuLOZ2dlPdQw/6jbu8rtHNczbOXJi0O97Ylra65bZO9WKj05XT6+F52BttZW7Z2lH2yzFR/c72gMkrDUJf+FWbZ5+GFex0+eYbnvXevqOagoApkaCWF5lKJhBQgxv/3akel7Oqa8rdPDNAep4mieo1bhNubjM4+qNgMpgeQg/Svx/NvpZ+nY3uf4SI9znd3P9D0pq35KO8u8rPfCbxT7CbYYUrc9MgKxenbKn9uuR+qz3SVv67BZ5m+ZAxF/2Tujvvn1men6sr72PJ8gdbnzpleRsorLKSux7XVayS4TvmQ6mXQ0l3u9r2eM6G/ny1FRVumHf5bpp9u7RmJf0fnemNZvof1QZjrfP1bVuW4kJdngzyLRKWmV53Fv2XbpfVDNxH6nrRQhjrf11mfCtRLzb40=
*/