// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/tagged.hpp
/// \brief Defines the tagged class

#ifndef BOOST_BIMAP_TAGS_TAGGED_HPP
#define BOOST_BIMAP_TAGS_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {

/// \brief A light non-invasive idiom to tag a type.
/**

There are a lot of ways of tagging a type. The standard library for example
defines tags (empty structs) that are then inherited by the tagged class. To
support built-in types and other types that simple cannot inherit from the
tag, the standard builds another level of indirection. An example of this is
the type_traits metafunction. This approach is useful if the tags are intended
to be used in the library internals, and if the user does not have to create
new tagged types often.

Boost.MultiIndex is an example of a library that defines a tagged idiom that
is better suited to the user. As an option, in the indexed by declaration
of a multi-index container a user can \b attach a tag to each index, so it
can be referred by it instead of by the index number. It is a very user
friendly way of specifying a tag but is very invasive from the library writer's
point of view. Each index must now support this additional parameter. Maybe
not in the case of the multi-index container, but in simpler classes
the information of the tags is used by the father class rather than by the
tagged types.

\b tagged is a light non-invasive idiom to tag a type. It is very intuitive
and user-friendly. With the use of the defined metafunctions the library
writer can enjoy the coding too.

                                                                            **/

namespace tags {

/// \brief The tag holder
/**

The idea is to add a level of indirection to the type being tagged. With this
class you wrapped a type and apply a tag to it. The only thing to remember is
that if you write

\code
typedef tagged<type,tag> taggedType;
\endcode

Then instead to use directly the tagged type, in order to access it you have
to write \c taggedType::value_type. The tag can be obtained using \c taggedType::tag.
The idea is not to use this metadata directly but rather using the metafunctions
that are defined in the support namespace. With this metafunctions you can work
with tagged and untagged types in a consistent way. For example, the following
code is valid:

\code
BOOST_STATIC_ASSERT( is_same< value_type_of<taggedType>, value_type_of<type> >::value );
\endcode

The are other useful metafunctions there too.
See also value_type_of, tag_of, is_tagged, apply_to_value_type.

\ingroup tagged_group
                                                                                    **/
template< class Type, class Tag >
struct tagged
{
    typedef Type value_type;
    typedef Tag tag;
};

} // namespace tags
} // namespace bimaps
} // namespace boost

/** \namespace boost::bimaps::tags::support
\brief Metafunctions to work with tagged types.

This metafunctions aims to make easier the manage of tagged types. They are all mpl
compatible metafunctions and can be used with lambda expressions.
The metafunction value_type_of and tag_of get the data in a tagged type in a secure
and consistent way.
default_tagged and overwrite_tagged allows to work with the tag of a tagged type,
and apply_to_value_type is a higher order metafunction that allow the user to change
the type of a TaggedType.
                                                                                    **/

#endif // BOOST_BIMAP_TAGS_TAGGED_HPP





/* tagged.hpp
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
*/