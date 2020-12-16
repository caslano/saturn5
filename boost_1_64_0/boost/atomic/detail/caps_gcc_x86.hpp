/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_x86.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_x86.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(__x86_64__) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B) && (defined(BOOST_HAS_INT128) || !defined(BOOST_NO_ALIGNMENT))
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

/* caps_gcc_x86.hpp
KLLHKl5iy9eRb0uj3tcs+JT4SYhZHiLvN7dKw12hduFnph6S8JJN2ZgubpeatugvYt9Zv0WGxzEzFEfa81L7tpp9TJ/FH3CUa523ps+1FAnntphlLpMy59MyNzXz3ytvdywJL2/bwstbm8qWpse6JNguBcK21qtcrfI1WQH5cmRnWSq0OkgubGln9vUQdQr6LdJWEBgrKKUlp3EOfMOL0b6r224x2/NCse9ygr5mj+mO9W2aJ1zD0bdc7D1556hEPy8l9vkqtR1s8889MXpD3lvV3/jZ7TPn5Gw6+PNP33kp35O+d9n9L/6iw+jjA9OmTJn8xubHDsY6B6bt56v8r57PY/cJtWDyThPoC/+S30fRhyx9p9V36R78yLGIa7C+UEmGw26wCObDHXAA/BYsgN+DQ+ArcDjkt1UE58FR8Co4HX4ezoDXw9lwN5wDH4dz4fNwHnwdzodH4ALYiXgthL3h2XAYXAKnwnPhWXApnAlr4CJYC+30vWzeAeTdQ9LXhd/PoS3tU/eCl8C+8DLYH26AhXATHA43w1nwCrgIfgEuhtvgdngt/C68Hj4CvwIfhzfBl+Gt8M/wdphIHO6AKfAueBq8G/bUbwh94B6YC78B+8N74HR4L5wP74Pnwe/qN4b9lj7v4HBNZydL3Iu6X/cyOgiL4GNwDHwcngWfgXPh3+Eq+A/oh14P32RgHNwJE+BtMAk+AJPhszAF/gJ2gIdgOjwMM+FvYCp8GWbBN2AnSFhWZ9gF5uj9mmZpewu76XebBDha00HYG23+Enrhr2Aa/DXsDA/DU+CL8LDHcp7zE/MsoOOjWj4D6JM+/yfnTOJagDsYeQ6QfzXn9az++M4Dem7tJ38m0INntnwu0K78eOsA+lV0XH/3W5WrXOUqV7nKVa5ylatc5SpXucpVQfWfHv8vXVNVe7LG/z/v2OvvZU/oe36azhFdXMj3uJLQGFHl6spaP+b63R7zqlmNF5gz5NRtpoyBFNhhmDH/NSVlDWU1lpmHF+62SN12FLfVYW5LItwyLmvW0fuJ/5U6/zgPuaV19E0yLheIc7auo+8tZiZ+Yl4MO4q5xiVizmK6juE8QNx6wlvgqE58M3TkVX1ddTVWjn0D1kj8R4fyBbWypKFudVUF90PyTPP2Zznh40kb1XxRoYWqafSr+TTYl/F1e2/yQ17yKdceX/em9GN0PalDyoyUOn4ktONfx3aaZzr+2TxeRRrXeXKNapPXZkzd+DVa8v1p68TjWfut4HhWhqS9VyC/JZ8LTP6bfDDzjskDzMPH3kk/ZqRfx7T+JvnNN2sdw+o8NyAvU3mmymUq1yI73V8V4f7BCPdPq7xC5b+rnK/jrafOC8hVan8mstqHlRe/lpdsdJrq3di8PS9UXhrLGyoZBDPn9/lbUa6d43L1+vmuSsOv0Gukz5drNFSWVdAIkMHhZdLsczFY3E1zlgGxK3LYhZehE8aP8Tmz14S558gSHuEjVzMfM1XGXwdcQrm1VnJOZGl9ZcOKckvvb//54fm/eH4wfz8d43zJcbb515esW3wk4fO3X7a748tP3PHFA5++cb4/yjjf4quXbsl9657252X//YNp1xfe7I7ztWWcj7ZVxoDW6ThfkXneyTNT7OLgAHV/to6jLIaZ8ByYDZfAo3CHpc8LfY7gX661Vf3n6dzmEXAaLIJlcCS8Ap4Jr4Xj4D5YDJ+B4+G7cKLOZZ4Gl8AZsALOhJfAOXATLIE3wXnwFjhf41dgafsEszV9Pni6xu88TV8pzIDL1N9yS9scWKX+nPvEVKi/dZofl+g42npYoOOF4+AmTfdn4Fx4OazQ8cL13taPQ+0ezRgK+jA62pjUzDGBcak=
*/