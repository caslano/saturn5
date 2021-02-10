
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_FLAGS_H
#define BOOST_COROUTINES_DETAIL_FLAGS_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

enum flag_t
{
    flag_started        = 1 << 1,
    flag_running        = 1 << 2,
    flag_complete       = 1 << 3,
    flag_unwind_stack   = 1 << 4,
    flag_force_unwind   = 1 << 5
};

struct unwind_t
{
    enum flag_t
    { force_unwind = 1 };
};

struct synthesized_t
{
    enum flag_t
    { syntesized = 1 };
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_FLAGS_H

/* flags.hpp
RUoracDo0u54KwCfa5kLZUQB3EAhTN7KNb5IBbYSUMpawHk8W46nvw5hV8m86uPsdQem0l1dQMW3AlqRC7n1YRreWtAlRsD4hTQWY3ZWahVgegFWtBvTh6EieG008C2XNV9jOm6hsrYxL0ejvGtr3Mmo0LkZ5QcMgspuHuxqidVs+B50Y8Fq6IwYAtkPYaMLWdIdIcLFplvX0lTDu7IwoSpGugUj6roPh65SGL8FAUmP1pAsocHqpaWb0cpQtl2lN/cMEdY+UNm1CtMhLGhXaAR+CJ0qROvsHRCHLD3KDvIvtOyu9gK0wqpgECYwTgaw5kaaIXwYp5fxIoUP4XweTtMlxO8gnC77eO/H0wvkhsSsLYjbphUGq2hBbppaiuJe8m8qcRakl3C+mE/iWZpdxJcZPsJzGDx7Ab91ytF6AINarqnv8FPw4w/BU1ygt0xws8+MsNRh/CCZDMZLLmEaXkXsYdDVGTSt3spCOGwvpsmZ3or27DJNZwmghXNNltN4lowT9p1Ued2h8WvK5WlXvWEubK5x/WEJJ/QLPKmQEDXy4kF65F7FW3iCj6evXKaLKDmfj2fpOJ6yGUe4UV8cGi2VJS4g/WFVjtF+Vc6g1J4eGA1J2W69BXLa/aL4RjBsma63Ut14RaHgcJVC
*/