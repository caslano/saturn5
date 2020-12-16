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
compatible metafunctions and can be used with lambda expresions.
The metafunction value_type_of and tag_of get the data in a tagged type in a secure
and consistent way.
default_tagged and overwrite_tagged allows to work with the tag of a tagged type,
and apply_to_value_type is a higher order metafunction that allow the user to change
the type of a TaggedType.
                                                                                    **/

#endif // BOOST_BIMAP_TAGS_TAGGED_HPP





/* tagged.hpp
Yye2mg9VeTo48/E7az4hIf4extxF7l1s7t01M9RONvdJse2QW04bEGrnDMzdAuH7dcvnWNAc04Y13rRd0HXaJE9C3hvfTjN6plZPOBH25Ud2pZPH/uKa2tLCStXVNnvHYS7UtQyD9v188Wea9Q0b5dwJtMo9nHLBnAW/6SdQd7o2YaWPOIp5qO9EQum4qaqu9S80e9mdInZyfCc7zxr1p4+0J1k9TfgWLtB7zTF2CJ+2JxOMP3yLmHep4ppF6uZc7Fwvdna6dfHxx9HFJy6ez7cTl8jacLrXYTA9/kR70Z9x9DXkvaQlh9+sO/AbsXOTmtUNI5Spxm4lG5/VcBunHZoSiLuPHRtd9uqW0HFW4n6G/UnsTSdl+0qfz1oCebi79sk0PJ40IGmIdPp4rQf0F3Hf1+Tvv8V8PPHp47lG0Btip0dIuf1GG/YG07ZJ2ywta5wrMGWZcqT2isy5QDlJ1z3mKAec03Kgdv3mvZZ81neyuypD1yzcoeYL1Ry3JPR6zxbm0WrmfiFrMDX2iLwGU9OStq/BhN1W12B6YskR12Ca4b0Gk/PMj0tX29rW99T3+f2BsGq3qr7P15SWyhwX511H2qJObWiP3Omzz76J9oH2RfYiT9l9MVVyT/fnauC9j2s+q6S22kkftTva1Ne5Yv5dxO/bs439keYdYLaYd4R/72p9nCnXfy3mfOM+J/z7V+vYdLn+vNPmiPl417OsLuTbZ00grvLsSsC/SYShu7T7Y82z4UPn2SB2irCTJt8gDXcE7RSoneA8qA9SpC9Un1FHfpcIPidIY8qHpLF+g4d/l+dF+C6fFv5dbvK5V6Ylx5NIL+XfuE9RtTuf+Ur07pdQu8RC8+VKMd9t3c59QtPWae/eETuTKNM99RwtuZz7GmeyQ949UvXd4xq5/n3WD0jievBbwm/8vE6uj7A6Os8njqqFDExIWHvZaVhtnjOYQ+9pf4PuJ+3KMwLtbnLMaLvNjU9KDDS+ia20BbeJP8d5tgXr5PqYwDuM3md9hr7ndDw3OT45ueOY5PjESN8n6Wq/KUPfTbr4k2PTrLD3k7aWI1eZkTaS/AppU99X84/TQvfX3Kdl5RKku/JZu8z73WVFexTcfXIt+hQuE/vnOeVHzBlqJk/E7HN977eprswwcTR9dHpf4rTKb77tQ8r/ht6hcyDzkNdxuz80TrSqlpZl08do4hNzieSthj/oNtX1Ptr+8L9q+hhDw3tfX0uO73GfIcq9dh/pJe7w2uNdllcfldodY+rN1WIu903wJXm1zeomV9zMx9wg5sW+s3w+lxv5Ntf2OOhmmHmnu1zMl/im++Ij9o/MMW6mmn1UbxXzOb6Rvtiwd7lU/V65QuxU+Sb6Ulx7WpMGvFvwVl1aov6nw/ga6b/GLWZ+JYr5TetHVo+WfWDmHW6j+H+2r4svU54FGykz0/rwHA58AzwT9ixQOxuw08u2k7RymftZwH0Ym5Q2ZLG7n6RvjaSx6ftoFnNSyBhaoT47EN3L1ZEB1jzx98ZVWOwQcczT3CtF/O7Shne9+G5FYtcaxCrqfMoGvm1n1YTuDZsf2k+p74Phz6cic07KipwrD+kb0bUJJc3lWSbmi2pM/Q1pk/ZqZerExT5wP7LPfn7VuuuD9ITw4PTsl1P7Y73Kv14faN5Nrhbza+FlX9O3odbpP8s37rPNu4nlvJuI/Q/lejfM5rujuK7c+a6+Ta6/6NonmJSXXYydPpGbxM4fwr/N9R4xddo3reWro5gX0ndyunnHspx3LKl/u8XPkWoOupll3vksfecz6wGL/TusYZTXRMvpK8ukHvRWsccdOutexK+24XvDLm/cN2wvYleZ0fec8PKWH1o=
*/