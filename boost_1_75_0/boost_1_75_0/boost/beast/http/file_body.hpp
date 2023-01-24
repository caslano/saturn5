//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_FILE_BODY_HPP
#define BOOST_BEAST_HTTP_FILE_BODY_HPP

#include <boost/beast/core/file.hpp>
#include <boost/beast/http/basic_file_body.hpp>
#include <boost/assert.hpp>
#include <boost/optional.hpp>
#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/// A message body represented by a file on the filesystem.
using file_body = basic_file_body<file>;

} // http
} // beast
} // boost

#ifndef BOOST_BEAST_NO_FILE_BODY_WIN32
#include <boost/beast/http/impl/file_body_win32.hpp>
#endif

#endif

/* file_body.hpp
uTST/WEXN9kX9PYCD/MQ9tEtGVByxxgMB0tPf1KqvAcsbTXfaSvGhxLUm4qosZcv7Yx5/431+pkLd/bjb6iz05rDeKmpJma+Gd5ZOroLbNClHd8Fds0xdW/8fXeBJa/XWfTPcxfYmBPavk4xtbSAzS9uVu2TbZrFv91R9MiLm2da+eXHdHGzqF3cvJ2xT9M+M7GLm29ARuP8FzevIjTlFzePwoG4oye7uJm5z2DjuRGNL8n9jWua3875jWuaP3xWh8szGQ1ac4LRnOxvkju6D3P5GxGo3O64+6ScGIjMT7Zbwz6PZfyEECccvoE4m7r1mJSjP8OerFhODkSc7aJY0nJYUNjrQvt/A4F/eCbm0ePnoXPysy9h5Ft1nU7k3DqXfZ/8R7TsS5ofZATLaack+Xcg62h5WPdTzs8R2+Qx3yWr4Rrqv0/WlA7m1XkYJcq/T8FLJ/BGnaH8PueeZHhhYpwLRcNH+Kt65YGbAolx7h/2zqI3UtB6c6VeEMxQLLUDTFo94VMhiuW1AXS98zEKwROAjcolTcllWpvL1/EQPrrrnSv49c67teudP8SSINJV+MZoSpc0VTejymk6QIZ1AEj/AeolzzfGRV7yvJtd8jyUXfJci3WTMi2XVAPIhGuXPFv7sQgoI+O0S55tpFRod8lzHiWrlzyve4gf+i5W04rl8gvoIPYxdlu3hH5tlYrqgLaiv+aAtkDUZE8S
*/