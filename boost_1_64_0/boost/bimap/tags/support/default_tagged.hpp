// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/default_tagged.hpp
/// \brief Weak tagging

#ifndef BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::default_tagged
\brief Weak tagging metafunction

\code
template< class Type, class Tag >
struct default_tagged
{
    typedef {TaggedType} type;
};
\endcode

If the type is not tagged, this metafunction returns a tagged type with the
default tag. If it is tagged, the returns the type unchanged.

See also tagged, overwrite_tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// Default Tagging
// A metafunction that create a tagged type with a default tag value.

template< class Type, class DefaultTag >
struct default_tagged
{
    typedef tagged<Type,DefaultTag> type;
};

template< class Type, class OldTag, class NewTag >
struct default_tagged< tagged< Type, OldTag >, NewTag >
{
    typedef tagged<Type,OldTag> type;
};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP




/* default_tagged.hpp
6+Pfo/VyM0yFW2BPeC/sreaPbFo6bg4/V39SkQ3qz9ta7/4Gx8J3YB7cq/XtPVgO34dL4AfwOrgf3gA/hN+GH8Fb4cdaHg/AO+CnWi4Paf36DL4G/wn3wH/DvRI2CS8zeXR8Gj6p4e2CrNDwdiRevWASHAQ7wxNgFzgapsBzYSr0w+7wSpgGV6v5WjXfovY2w17wfpgJd8AeUNcS1/FOyrqGx72W+E3arjbC7vBmOAB+R8O3Ttv3W7Re3arhuw0uhuuhlh/GIbWe6H3c5ecyzefLYSZcru3xCvX3Cnimmj+S9NaxOR1z3K/lcp/61w97w2A2HAMHw3x4HPw6HAYvgcPhjTAH3gxPgN+Ho/U9ZQzcCsfq+8o4+AicAJ+BE+Ef4CT4Z3iKvq/MgnZ9mw1T4FzYA86Dw+F8eDo8B54LC+DX4flwGZwMr4VT4Dp4FrwNTjfPHR3DkbGm8OfOL/Q58wQ8CT4JJ8Gn4OnwaXgG/A38BmyGxfAZWAJ/q+30s3AZfA5eAZ/X9vr3cBV8QevHS/CH8A9ws9b7B7TeP6/1/h/wz3A//IvWh42WjgHAPI2HzE/QeNyq63Dcrs+b7+tz5g6YDzfCc+Cd8Hz4Q3g5vAveCO/WersF3gt/BH8CfwwfgvyWdv1++D58APb3kY5wIPyphjPb0n5xmI7k88MHg/N4T3bZK2qjvYY22tvYRntNbbS3pxV74132rEvbZi+7jfby2mivqI32Gtpob2Mr9vq50+8I9rLiAuu3NP0u0drzu7av4fL/uH7LF1275WjXbVkzMLZda7esuD7hqNdvae/aLesHxv5P12+JezbxmK/hUrL3y1nDZcXejl/5Oi69SJ9G2w38BrIauQ/ZiRxCsp9jDwrEjzQi25E9SNzzidYgZCbiRxqRLcizyF4k7ve4RSYhBcgyZB2yHdmDxO1k/wpkJuJH1iGPInuQuBe4hkx7IbquTPSIHtEjekSP6BE9osd/2TsT8CqqKwBP8l4WkgAhQCABQgADASINi+xLWA17QMC4QAhJMAgkkQTEpZoiWqxYYwtKkSrutKVKLVXbakvVWqq0Uot1r2it2koVLVrb2uWf8867M2+ZkFC025t8N/+7c/d15t6ZcyZ2xI7YETtiR+xo7fHp6f9DIsdWAPgv6v+zdfe9m2UZ3VE8L5AjT9/P6q4ysnW8W+HS7S+CIHZJUJdvpGKCcplLM3gPBvMe8b7fAt1IMR3xke/n/FF0xPt3DB5278JXlx88Z/uQVxZX7vd676v17015vA/m8T6V13tirX/PqrW641urIz76+1r/Pt3x+gxRxw/jKoqO+M76zLkLzIBdoehmgd1hD5gLu8O6gC72Fu/h/y/rYT/RvfzW7OOf6B7+/7sO9k9i7/7T3rdv4veq2P547IgdsSN2xI7YETs4/iPW/6tWLDsZ+v9t/f79MnmXTfT7BxXyB9QeVjVU11aqfv9nspzv/21W/f5n6bvWczDX2zK2Z8oegQSuXLu6rmzZitqgjFn/gMw/OTcyXOo/18jsHxb7SPG/XWT2a9c2uHQivCzuw42sIOGNfv6BAd2XKISzRD6e9ZLo1n0J3oHfZ7M4n5LWdlSaL0P0gKjbc3EY3NKSOqa2Tc1L9Kclp6GjKKGz5chzPo97IMwZUlfnXmFXStS6MjoiXpC8pcveR9Fx9NSUwP4iby/1Y3R+UAecow7UXy4cKP6knKLP40NJh3VpZsCeWhqwfzWon0fbbJcqNr9N2+xGzA20WWFpWJstr4tor4zgdwnF74XWCOLVNtTwWRLmyx1Mm5l6mCbubU2b4d9TX24nuE/c04J9gGMZZXX0XS0S90vQpBEnOmqb6IvHfOy70EY=
*/