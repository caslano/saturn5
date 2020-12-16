/*
Copyright 2019-2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_DETAIL_BUFFER_FILL_HPP
#define BOOST_IO_DETAIL_BUFFER_FILL_HPP

#include <iosfwd>
#include <cstddef>

namespace boost {
namespace io {
namespace detail {

template<class charT, class traits>
inline bool
buffer_fill(std::basic_streambuf<charT, traits>& buf, charT ch,
    std::size_t size)
{
    charT fill[] = { ch, ch, ch, ch, ch, ch, ch, ch };
    enum {
        chunk = sizeof fill / sizeof(charT)
    };
    for (; size > chunk; size -= chunk) {
        if (static_cast<std::size_t>(buf.sputn(fill, chunk)) != chunk) {
            return false;
        }
    }
    return static_cast<std::size_t>(buf.sputn(fill, size)) == size;
}

} /* detail */
} /* io */
} /* boost */

#endif

/* buffer_fill.hpp
cZ/VVNAEbFDK2qeXGVb0FOvk5qPcLhJ/2UY6pHQxYnLKjmHTHkVrqQd+W4eni9t5yGsM7L/11MqP/oP1m3KfyPjHGHEsC5fxqPkMPjtB380EDESeW4E5pqmnZ9z0uM5xPWO88e60mBbx7lhHmTBdN0oY3aQu1FMuQ7XlotiOR37xzC9lslwpE/XMg0Xckz+belwG8mEzVI2zTGhXIahts2W5Tfj90rZdotdjhKlpU5R68Bdxn2AMArfSBggd1rQBsQ7bA02SOu6XfOYXF+vbBDXvpU2dtlueBa9/f2jepxYU5Tn0UJdH8cs8Ut/ycktzNXuOyavahnihEfbonfWQ5c34gs59iNXns0Kbz+z8OUZkea1oRF4rfuG82mcEcc9+BvW5D2gz/Fc584p235FP26bHWuHvqd8Lz7zYfVfDtjHCtqFqOdU1py1Rpn096Mr2eO5Ie0FRSX5xqa5tbGP1KeLnReNSjjPWhetbGlGG4NX2Q8lsAyYdMN2HYh9nM+eYQvHfBv7LJKd5s8omZxeVzczOLTSDUsJqL2GdZZwkbQHayTZSY2f6zeSRLwk4XPg6Q6/cSBee4W6xPGt69BzKpIbbjkh1jXvvHX1e2QGlfVXKdEUc6xwjMx9WI466A44yLckumVVcmp+ntLFMB/N6WPy0gHTDlOWBxtkaeJl5DW0Xy9nJXEQ9nGDyor4mfhacZtqRkb6xIjBO1aUL/upv9zuK+3AjA//Z7mPcF5HNmVFWuz8WYbDdt21GVQTGfcHnw7Rw5m0d0lSuyxtUsxCGGLqiL18AmaTD77kIJc4V4/W0Rj/eNA1j2KbNYmLjE9Hs6NIeNs93KHlmP1+vDRe1fA4zDy3JkGDplCMPqFqGEV6fhL+50TScPn328+jTqgTbxq5t6+PCDtCLz0PT68cBK/o2ORmYIvypmrQyLKV/aZX80/oXVVe89D2OujIWVIZ6MFiX7nr6kzTgCPFzvibtDI/1g+9qeB05OkafIO4+bZtMv+r41O7DxojbCHn3qkIZrGzJd69e8uoV2n/95PFmcpANLqYdbWKOGT+fq/pwhDGkMOBWHI9UOeVaVjJdL9MkMw3CH6+TKcKKvF+rCtGd2JSfpjsNjU36sRPoRXsVPUEvQTlqHPmGASXd+yLzvVX4T0Aam+jH2SE64VJ04iNxO05vA0cvM11fDt7G2Z7SvJ+wDy1gn+qQm/3emNXKeba553jU+YMauWVPmemX1/kg+c0IakfEn08nO4bpUvs08WcmIU3ckp2yU/wl0B9mVwrzFF09XtxbNlavZqjyYn8WpFMTWYnOZBs1iG1rhlM20wumloadgzhV+AeE6wsYnkvea8e3Qn5TAm2spxXaEo8nrl9cp7gu5qst2sdw77VjJIwO0s78lPGY2aZcdlD/HpuSqh/3lzvlgEFW+HH/jQfDjvsRVoM6P6q+tC9n2ruGjBENn/79rNqR9rIiKcUI38+qD0beBlYf/M+0gd8zr+1B1phgI/zXOvIKG1hl+WHHLvuF/zjIzKvLO8LTtIGs/4dYFzVygL+fPuYJbdfUfK9oTds11M9u1M/EP4Xm+6r84lnh9TNV+Dvp8oywGtTPesc9/Xku3ZLjAszXMK3z+B6aFUhrQVFpfnFRbiFnRcLPa04Q/tlGmpGiSy/C0+qnndeZ4t4yqHzoxy67Nnb5oq0xdSZ7Fmb1ZxWVhLHdRv+cD5Q2ym6jXxa35vZ75Dy59wSPrchbJm5NDR95/XJ/GXrkpkjxGKTr/KSVyEQiZPmE2U6eHNfVfFmA36AzCP/oa9imZqT1rL36bhoqD7ZBt/9JaYNoH26wu/H20vR218LZjQt/7twCj/n8wYs2eVvc9MM=
*/