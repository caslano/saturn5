/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/execute.hpp
 * Date:        Thu Dec 06 13:21:54 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the function boost::iostreams::detail::absolute_path, used for 
 * debug output for mapped files.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED

#include <string>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#ifdef BOOST_IOSTREAMS_WINDOWS
# include <cctype>
#endif
#include <boost/iostreams/detail/current_directory.hpp>

namespace boost { namespace iostreams { namespace detail {

// Resolves the given path relative to the current working directory
inline std::string absolute_path(const std::string& path)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/' || path[0] == '\\') ||
           path.size() > 1 && std::isalpha(path[0]) && path[1] == ':' ?
               path :
               current_directory() + '\\' + path;
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/') ?
        path :
        current_directory() + '/' + path;
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ABSOLUTE_PATH_HPP_INCLUDED

/* absolute_path.hpp
Y0jh1Gk0+0OijHkgXt0eHsesiZMyZ6k6scum9yOcJ6XqN3+NUb/rqL1jR9g79nlJeG/tEn3gIHkUu3P/H8ZP6bMzezoV7s4JNfkTYRmNi1PPNOw/ydwfrcDEzNxSG3Hzlb85Hvv85/VxoNzsHXf1RG+OqTR87Ykinu7UxgwrsqyOyR653Squ0z3a83y+U24J8KCKK9xbj9IZjlyBlOYta+LcmYMmzp2m8qb21Um755QbrYj2bSBVVossr/bMfw03aS+d9E2d0l7SKPvxNqs09iCNznVzibw03jfV+d9alxviPRddtIM8S9zPIdw/6r55XtrQF+DOUnclafzWZRfybWKJLidUsJfu9UfK9hdsfUwUfaSdVTqg7kfRDcf9mOOulat+L6yXDsIJD3HDY5B7gY1K+r1A0xviXkgS/bhe+T/PMwS9uIL4jX2Ibcb7QPk9KTrcVaUqZ66j24cC6j+XL1/T78ssfZYdUnF2odxOde+FYB1PEh1frfz+xTOQ+/Q3VkSw/rr6FnwPJIneri8Jb/UhN7MRtZcUl/GP2e7JVrC+Jzm23FS45z3tuOYk7h+DPrv7Ui9/1Pb7gSlu0VMqV9Jqtw0GHVfnTujlybq3udoz4AN1jZ7uN7rqq2uMJW3j+C16LXo6B6WYVydQd3cjLyIvIS8jfWpZxKQU1vX/Cu57SsMrfe8p+p5cgb6T53L1HTelL8rupugQbkpXyC9uZFe7L1T/Q9cduS/sckuUusdNlaf7TJPwJxx/WvnqfdgUycC9SDRyD3K+rXuP6/cPfdip2aoOF6h7Zy75MD3vJBz/GXTeff5PVH6SDfWs8u36u1T5i5N7heeK+t2V9KdaQTruvjs2VH6WMt/iN+mcKveG6Ek4v/dSLsWiE6+W1rWq48hK9B8WqDqlLNyyNtfVyaB60dsvJh3VsUzKf7GUf3Fg+c/PnDN9Ct2AStWBCst/oZ6pYdtL7p+a3MvNrchAfx2knEztiJTxJyr+WdYZXO1cUzlLvao+mlPO8jx5DR7/iWUsZSllrNKq3E6UU77FXEvlwEPZwVlwjP182O6WL1mze6y5c1E+V688kmenf3GD8t/bZIOWuIL7rNwu3GrSHhufCycCngs88fJkLEDqKOoJ1Qchzii3rQxqn9029251/Q70BdSaIQ7yoo3FrFbne3nupLadNnOUij/CeddTdazb31yvwnT0GNtn0Q+nH/F6UN/guoQSuYi/30DeRHLwmIs47e5b0r6+rbWr8RW0q88/UbZdtesqUeoqoF2UOlD6YWhXj7h6JGUv7icN7aWuTxtlEdd2uV8fQyahIPsfdPVpel5mVkmDKfp0cbLYZzXfr4Q1rEsyr+XCb/C6pIlzjesydb/6e1h74ziX2W8Hsx1q3W9X5ZfcShqSNb/Jmt/y+kB1H1LjXqQjK1Tb4+rycRXfBr7PN9PV5WEqvM/S7zOy6YZpqc5PZ81HWLlhyK6bprPU+cZWTUq9FXoehds72rPi5dpKb+WZ4VBsKVeiXUMnxDasvHcb1nbFuGu7qGNxi9ffW9uXuCXobtIm2mWvdF7Vjei24fmk6/Y26dhcjHjEZucE3NIDdVseRpXT7fQq6HZ6FXRb/Mp7l+gg2dfHoDOVn7Hoiseo8+lGPTbrvPgNGhsz67z4lbGp0veo1yrx7ZSfox9Jun5o5SE6ouuDqyPkxTjGcN8p/KPZUe2InGfvmXvS1YWsDB6bJSM+JbowoWQ9Ji5GXSBs4HPSQ9/VqAviVy/Di5NK+urv1q38+J6dnkRJj1OGep9Zz29BfUsdT8reou2S3/XB+bUfC1aZ/Lr9z63K/+9YrxNhnvdw8yVlIM8Z/ZvCDyk/f6T18Ro=
*/