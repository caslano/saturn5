
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PREALLOCATED_H
#define BOOST_CONTEXT_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) noexcept :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PREALLOCATED_H

/* preallocated.hpp
48DaAv1krnHgJMTPOHxW7z7Sj5iYpr4rHg25fbGVnPd7KX3MpSo5TJb2T33eftVsg+Z8vykkw/2NX8HYjfvrAyx/cyC1gYrn8H0d4U+r7nu8Uch7BlX+9Gpxjny1iZVmWLZfX60ub6w0k/hpyOdrC5h7UzRmW3WfY/naRirrYCG7MsH7XAt/HuGDz0b8JsJvZjiMj0x9D7Xq21oNl1Xf+USjza2vnLtm9yS+m2qNe0vpG8K1ZKcLpZ32MU6NefQ/sjQRAMOQY3NMC3UHUykzPtdp8VgKxu2hdCQs94JhXiIov0NcqtJozxifEXF4tTwjAsoMKBhlf8ilTMj9bqEAPPWe8shq/Z5yDawTOctT32iPv77RHn99eU0c11FN2getNYPmfJmjsG/BOkdTabNn5+Z+KDdcOsfvV45mOeA6FmY/mOzk6vAz1Mb4Ae4zZV8M36omPQoYXcS5JP+57rrPYf6D6Ou646Eg9YPk89qlz/uGY4inhC2ELVuIVKvLWrtPdegk2F09fOOXr8U7C//3s6OS5wLePWXtY4v074rfxdJ2zffc5StU1J9ulHU04SGk+OCz9CX/Rb6bnVFA3N12RIv2A/5kpGFizezfdU5Q+xzPfYUco/r5zj7iNyNWX9/GOs3lpam8TLVcW8k2wN/8tfYpEM5SwvnU8nHpgLXXFdPMnOPDuO7V7K9eiWMkxIssIbwdcc0r4rnfjExW477W2ijBvIzf7ojWcllfAc8T4JnfGU6txr2sLvyx8Dwd8nvpubda7TvrdfOXwXML5CddfLU3Ncn5KI9jzZwn+sxh6r2b0KmuAt95PCvsdrlltydVw2XZ7ckk81Pyxa5FjiMVvdOqvd93XYF1CUdT6URcnRtl5kySkWAKuiSWBcav8K0r+uSY+RZbOBEgUHyvRzH/6TLmL2AclzVGKkLvVd3OpLrVZvMZLclIR1Tv5T+LY12mIeYDVv6Hce4qK849W/qf4ufuMEYKWjHWuaQbq6vz7DHOM54434rBdiP6F1AMtoboX2jBqXy59uxigrtExtUIp/1IubUW9jKCv9zQRV44NrzSsourkI71jo1oXJMFNmGtX1xLsOuy8DcuC3/XEfwGgn9YnqMlYsSLsI1DyYg42+bSavf8G37Gb+im0sn4MsfAjOY0sX/2CsUPxAvBcKA9SmfoXVuNa0cyPQn9vB59WzQViGV62sn+1qN/S8cD4my765WPQ1r4jgb3024UOthSxLg5KnzWjZa8b6pWl1feN5P8buG+2yM/qDWI0Hv2gX3ugY4dOe6+TdqOyvN8ypuf83z/u6D5KfjORLU3pvuBKpfmvsBrkE+kOD0Nrh3wOD66Q/JY0Jq4fmoMZb49IcZyd1kyvrtaXdZ320nG91i22WXNr91HcPdbcF8SnHrnjt+fILgHGQ7Ht4anhyyeHq6Gy+LpEaLxqFXWQxZPjxHczxgO5/2t77awryNf9CThPEU4U6mNgpjfHkx53qn3gAH2ZHrE3H+pmvvHNDMX+7QczxW9bkPz+alVt18Qn89y3fhdIH+/wZLjr6rVZX2/gWg8b8lxL8v//5bgXmCZ0NrIy/X5fl1ixioAHqRnGfZgWdKpP7hP8PmSxeemargsPn9P5b8s/Hi7mB95RejPqxa9P1bDZdF7jei9btV7gFXvNwjuz0LG0y2ctyyctwnnHYFzu6Vzd1Bbvks691fCeY9xsE5enPepnBDZ0QeE86FpE+OPimyTctLxzciPhla6C+X23yJ0d8g3mLuss+rxMdXjLar7J1SPT0Xd54r2/Nxqzy+q4bLa8x9E40urrL9bNvMvgvtKlPUDoYtOjShLYdSoy1tW/xpNYwDC0reIrPYdRDg=
*/