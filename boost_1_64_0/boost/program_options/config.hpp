//    Copyright (c) 2004 Hartmut Kaiser
//
//    Use, modification and distribution is subject to the Boost Software
//    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_CONFIG_HK_2004_01_11
#define BOOST_PROGRAM_OPTIONS_CONFIG_HK_2004_01_11

#include <boost/config.hpp>
#include <boost/version.hpp>

// Support for autolinking.
#if BOOST_VERSION >= 103100   // works beginning from Boost V1.31.0

///////////////////////////////////////////////////////////////////////////////
// enable automatic library variant selection 
#if !defined(BOOST_PROGRAM_OPTIONS_SOURCE) && !defined(BOOST_ALL_NO_LIB) && \
    !defined(BOOST_PROGRAM_OPTIONS_NO_LIB)

// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
#define BOOST_LIB_NAME boost_program_options
// tell the auto-link code to select a dll when required:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_PROGRAM_OPTIONS_DYN_LINK)
#  define BOOST_DYN_LINK
#endif

// And include the header that does the work:
#include <boost/config/auto_link.hpp>

#endif  // auto-linking disabled

#endif  // BOOST_VERSION

///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_PROGRAM_OPTIONS_DYN_LINK)
// export if this is our own source, otherwise import:
#ifdef BOOST_PROGRAM_OPTIONS_SOURCE
# define BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_EXPORT
#else
# define BOOST_PROGRAM_OPTIONS_DECL BOOST_SYMBOL_IMPORT
#endif  // BOOST_PROGRAM_OPTIONS_SOURCE
#endif  // DYN_LINK

#ifndef BOOST_PROGRAM_OPTIONS_DECL
#define BOOST_PROGRAM_OPTIONS_DECL
#endif


#endif // PROGRAM_OPTIONS_CONFIG_HK_2004_01_11


/* config.hpp
0LMe/J6mkqkkfrR//pT589R4spRPXAIvfxvCw9GhOzbZ94pgfzXfWsjOkA/MGWjvz7B9VU3p0In93Z5jHrgmCr4La/7A+tzY2/ybja0P6Gbz87rWB0cn/z7SJ0hT2HdUMo8XcC6LF3ORPkD88T/fAz/Mvcdk4h/++5xf8zYkph1y2jbG31PkO2Or/WVf31ftX3jDfy7d+HOTDqSv3ntRZt5vUg/ZCBLnHXmgovO/5H9/0zwQZPN7Q/NvRqLzdx3rI8n8W1hT7TuSLebvtvV+xv+dZH7e0Be3YMt4e/N3+3o/27jmPXnzu5ALef/bdZuYvx8UP1Ioh7/yJozvLUijYzDP7mYBPQDZCXIj5NXtET+UZ8ZLjcm0+nX2XvNvtonKM/y+P69j5o1F1rEOSFR9avoH9alevfkRYdN69f2CRPv5qO9nItofST2/F/X9bcw+Vf3znvc+Or/9pX3eevaF3NXLfr31jXr+SP6+v5Zofyf1/WFE+zWp77cm2h9Jff800X5Q6vk7+fv+bKL9wfx9vyN/189NtN+Xv+/XJ9ofTH2/ONH+der7H+K+gfnW4fh1O8S/b4D+yOwf74CwBeGOCI9CuDfCAYT7IDwH4b4I4wj3Q3gpwhaE1yE8AOG9CA9EeB/CgxE+gfAQhK8ibEf4GsIl9n4W+1kEoyY9wf2do2lP7ERo3o5j+roR7ovwFIQHIuxFuBjhMoTtCIcQdiEcRngSwrMQQprOYbrPtfZM9lkIHzD8oD1zOe+Fxfh7xxEegTCN8GSEGYRnI5xAuBxhjvlxMcIb+fMX6/+5fTL7ENZ0ENgkjX1y0bnz2yNph/TbIP+S/fHv2B6foc1xTYTdsQxZEW13VLU5zmdv7IKc8yf2Rp+tUcXOmIXQvhi2LUbZFSNtirQhhu2Hf8leOI+d8E9thP/EPniAtQvi30PecGwXpE2wnj3wX9kCaQe0NsCQ/e8v2/7+zO5Hm5+199HO95dtfD773ny2vT+16/1dm97Kib9myxMb3oPV/gqy5qGGzanxoV5BduD6P5sZxaL+9O7WZNYM5Xh5xfjpXI9xtzSr9eBavW9Z/2lN/6Pf0fgaX+NrfI2v8TW+xtf4Gl/ja3yNr/E1vr+3/m9t6rTrbv/Ku6kpeu19UNO65vdMMfZZ+fXM/mpTpiMZGx7uiw33DA8vG+jnHp8693vGTgs32ZFZCG56HS/2FVlyR/qGq48U42krvqnlhvsFuQ/7uYlsJpUrO+HuTe4gz1KclyMXeextQuvyWslbTd6teT8Pr4fghMjcAyK67Bayu/gPbvfrioItZfI57fok+q7kP3g362NWSinzIm1mLJPAs6jabKlTh9Ms/HaYPVjMTIJ7WupyVa7o/Ay5X/i5pTKI+G8RBY2TIblxXZ2ljPfdgPepc352ulKuviSmnM/CvI/M4/11Gm+Yee/h6eZxB5k7bejFng4zS8WC9FeFeDE+oayz1K3byV8Z4rvKa9F7Ef6RObET4kJK1XYcyyRjCZxmwiPBqnzRe8VGjJ6r5bvoR8i1B8gunghx8bYvsCVtrrTlq8gthLkTpfFYIp7NjsYTlzhiryX7lnBeo4BzqUS52qdoj1PSprObeLG/Dus9msm7yuuvyXwyXLfjiUSqQHWV2VK/LtqU7/CE2dVw6cg52joL9xNyX/GVsW3LxRRGq6QqV/J6ZDP6Xw6Wb7ZarXLoPGKFYr6cd6PzarKnfDpD11xqPF/OOJgPyFyvc3P6MA1y40lHvKfIG/XNA5C5l2nrJ2PD4i282Kf667A5hMqJ9NITqycr1fNX+oxHyO/y16lMicOxLlPq8W5berFb8kFmJld9kA//LaVT2uUr+t5O9hsBfXM=
*/