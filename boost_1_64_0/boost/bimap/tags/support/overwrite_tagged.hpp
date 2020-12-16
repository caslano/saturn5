// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/overwrite_tagged.hpp
/// \brief Hard tagging

#ifndef BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::overwrite_tagged
\brief Hard tagging metafunction

\code
template< class Type, class Tag >
struct overwrite_tagged
{
    typedef {TaggedType} type;
};
\endcode

If the type is not tagged, this metafunction returns a tagged type with the
passed tag. If it is tagged it returns a new tagged type with the tag replaced
by the one passed as a parameter.

See also tagged, default_tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// Change the tag

template< class Type, class NewTag >
struct overwrite_tagged
{
    typedef tagged<Type,NewTag> type;
};

template< class Type, class OldTag, class NewTag >
struct overwrite_tagged< tagged< Type, OldTag >, NewTag >
{
    typedef tagged<Type,NewTag> type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP



/* overwrite_tagged.hpp
E8hjnFLv6rer0T/+sdjjjvv+V5RxI3n9oCz6GEnuGj2v6UvD8irfdPPML/5D81uw9Lj5ndFcfvOWan7Dvnv2UlYg8D7t69/BbLfnZ81v2KZPWVWU/p6p/f0sCXOrNYD4Zzl9XuPKilgP6VhX9zOsQvxEW/+UOH7kSywZ5lrqrPkz9Rq9SPx9zRrC/wUY1Tmu4TPD903MuLhB3M+W74u51sKsVbSPn+CcE77uKImyh1Fqrp9aHh0P31sauh/xRJj9dWMPbdODqsN/lc7TFZgPGEOF5dqm4RsU0duUttMwxDSQufpMTJR9CfE70+X3FHrSRK5iOl9Qj8F9hRObv0O/n2XSDRl3s7pHrudr7ec+EWWWBb3nnP1qeeR6nji81/Pq7r5P/HX58dfzL5ZHrOc1nm7udbjRwfyGuM22vwxo1uILl8m1X+/xguv4Func/pf7bci9dg+dMLW/jcbcRpxNy7TuzWJY57uIewL1Swz0s4i1r84Txg/9K+r9dInjh3pq39L7hpDr1HUnsB61x+LPJV3WGGHXg005kXVzI36Oat2ELlC96+eoUz/ha1JTP0dbUD9HW18/M5qvH/dazrt+BlXoOi2sfpbmqg42Hbe7bGPfh1eE149zr3VdlHFbI/4voX7NuNU4csy91u/E3slz7bayImTtRniPtZuO83WBPJr7uxITpq/n/ZnmwfP+7DJx32gN0/uzzfSfl3oG1vi+Crk/s7dsO5zs+7PrTmCdJ9egiujr71m9tPNov5+KuR4/hZWudkU9Macj13raHkXiN915nqt27QNat47/ksrQvcq1Yk8w1/Pns47b1506CV07SllnS3zoawq73nbtHQg8QJ9R5mC+QfmbKkPkEqbPmb4geJsq19Gv9QpcRxsauCLVO2vK2yRcBy13MJ6M435DKlPv/YiXfJt4Je93at57pgfs3zb20PG4t3eojEUuZjfxHYwsizRfOylHZFu8If7bH/f+2s7LYc3LPb1s+xK1J1o+vcZPC9azKiZciOmofWuPnXZVRN5k7W735hXnlekHN73rnDrWOLqacdi1Kvjtqjjvb6SacH3VHmeNEnsbK9Ncw6klE8yZrzqLv9HUT+IJt6vH92WlTnP1nf6B6VKnak+06tR9bJVpfyPjUhR/8nTWeshSeMiCeMmmeMnWeMnKeMnctF6XbWtlKTxkZTxlNfKvsM9/5qrri2/fWDJ4wuriDTf3ObjVS8bIS6bES5ao9TJDHjIuHjIo3rI7H4o+TDnkOWM1+furJfvQ8jvboq31t+g00980kfUb/X3EfkakvxMwL+vv3phn9XcRxugi1feMzsLg5ugiVV1lHeHdMFvtuWofBXfBaWqfqfY58GuQ+Bkv+l4QvE3jT3WV8QbVRbodDoQ3welwh8Z3K1wEb4bXwFvgF9XepPatcCe8Uf1ruSiQ6vaLUi7iaGwPm2Cm2rPUPgReD8eqfaLap8AvuXUmavwfaPxunYkX46+HbYcF8DI4GF4Ox8Cr4GS4CRbDL8AZ8BpYpvYquAFeCa+Am9R+rdqPajzvwxIr+FybODQ/SZA8y7FMy1cBc+B5mn41xFjnw3q1N6pddTHqc1LaXuN162KswV8vWAv7wjpYAtfBpbBe42uAV6h9k9q3wnUmHX2uBrdESWeQ5vs0OBSOgCMhRvrHKFgKi7Q8Y+E6OA5+Ts9rv9BnR6QdpV8swF9XWAp7qj1f7RMdXbhiP0PtZ8ElJn59/gCvixL/VC1HsZZjOpwHZ2h8c2EFnAUvgLPhpXr+fSmv7uHDthq/HxZo/P3wZzMfJsH+MA0OgEF5tRINP03Du+XVsnS8Z8M82E37bQ84AuZo/+3pKu8ejW9ylPI=
*/