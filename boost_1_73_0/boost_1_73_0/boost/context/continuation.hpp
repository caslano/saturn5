
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/continuation_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/continuation_winfib.hpp>
#else
#include <boost/context/continuation_fcontext.hpp>
#endif

/* continuation.hpp
HUZXqvRwbB0dW4c4oN7CTcUkDQWRqsr4w4YSiOlfgWvfOMZXgJcHEFdCYnkKTnOpbOfYnUKXTVLsCYgjxlZR/Fnj+AvXm/pj37Dy1PiR5jGrEgKnir3uxeyDUfPEHCdeqerqOehn2CgM++W1JBPuOU2g3+jpnWjeC8cfzcbTYOy5hg1JJCNYpudNzDKd7slWjbMnHTtXwhbLqeaMZTrep72cuyOF3D3qKajaOMswdFu1vmwpY5BzCStE51WsWnb1CG0hsNfqEJ6zRxWj1DTHhJZk7EsSPwu1AtyHZaFIo3JdbUgurWa5l/Z8EhjufDLRA9OZF3gjb+IbttqDOOL8Zd9MJ44uhJCRpDGsV5wzgs2uqHglw3jVXbf6FVOojOsZfxuAuiSUVZ7TfH2iXtPuLgBUAMA6TEtCno2f6OHXNdUj/1dRtQyd/cXYz+fxZyLDKFaGd/VYDRD63ujaqTFwm5pwaMJPjVwNVBKJBwd8xMD5bOSEM+fGu3VOjC9Ga4ZaoLY8rfK4bbuGgvF8/a9JG9G2nC5Gbc+6Uvl9HD3TzhUnRu0STXqNOYJXZUzCkmz4PeliaE/HDPpwMMTDNMKjb0vaL8An3GT48WAET1PMq5VZ0B/UqDstcHaG+S9KoLHVu9aj3GzNJEyQJhZh
*/