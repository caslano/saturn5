// Copyright (c) 2001 Ronald Garcia, Indiana University (garcia@osl.iu.edu)
// Andrew Lumsdaine, Indiana University (lums@osl.iu.edu).

// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FILESYSTEM_UTF8_CODECVT_FACET_HPP
#define BOOST_FILESYSTEM_UTF8_CODECVT_FACET_HPP

#include <boost/filesystem/config.hpp>

#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace filesystem { namespace detail {

#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL BOOST_FILESYSTEM_DECL

#include <boost/detail/utf8_codecvt_facet.hpp>

#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL

#endif

/* utf8_codecvt_facet.hpp
C2AiMpl82bW8L2hz0VZ9JeQBmss68RqYUSuAiz+fJ4SR5EMAxHhy1PFeob/5Q0U8GZTqrq6NQRUyiKyKNxeRmaKNT0K/IoEKDSFKhHBBc1Vf2cvgqs7OjUczQyKUfDlb4I/a2dwStXo2aDt3Kxv4dfxcojfem03XIT7EppKPfi6ajT/7zm3KTlDdgwOOhOxB1VpwHtt+82BOxk9s0rvXUvF2GOf1l4aRaQ3NU5RmwCJMWZ8Ja86UtetE/YQ3Z8260WjNmveIZs26a4LVpJmpCOtUkeUNv945rDmb1iUTmrFpbUCbVkIjZGZ6zeAWzUwtFRegA1njSj1WduY0oKBcyFzfAYsO74zUzFhLxbO8nzlIL5dzeZc+HMfLvwiwn86lvCWI8akEGASc+VmUGMehv4SLa0t5/werz8WuKNEBcBNWPzQfZeNDcqHFBa3Dx4dOMHTcccFoj5sFv2ncwrKWJMfQG0iaEFhMV51Nbdh4zaY2avxFNl5LlrViX92VZthXOsta8v+dpfr/zuLxf/g1aQ7Pf0MEyRj+eAS//lmBj3+toJ9HvXT9ptH5xkPknvhKPdcLdTtK5dE63NvMjuoilP2X8pUv4CuPRpQclbVv1kR77z0cnAv4MrhQhip2EuA7j4SMEO2jtVE8WSGrW3GPVds/ECkEv7VMt+jut3QLHljkPW32RMjnAhEGf/5r77GqTV6vdUfAW4F+NV1N
*/