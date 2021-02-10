//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PIXEL_ITERATOR_HPP
#define BOOST_GIL_PIXEL_ITERATOR_HPP

#include <boost/gil/concepts.hpp>
#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/utilities.hpp>
#include <boost/gil/pixel.hpp>

#include <iterator>
#include <type_traits>

namespace boost { namespace gil {

//forwarded declaration (as this file is included in step_iterator.hpp)
template <typename Iterator>
class memory_based_step_iterator;

/// \brief metafunction predicate determining whether the given iterator is a plain one or an adaptor over another iterator.
/// Examples of adaptors are the step iterator and the dereference iterator adaptor.
template <typename It>
struct is_iterator_adaptor : public std::false_type {};

/// \brief returns the base iterator for a given iterator adaptor. Provide an specialization when introducing new iterator adaptors
template <typename It>
struct iterator_adaptor_get_base;

/// \brief Changes the base iterator of an iterator adaptor. Provide an specialization when introducing new iterator adaptors
template <typename It, typename NewBaseIt>
struct iterator_adaptor_rebind;

/// \brief Returns the type of an iterator just like the input iterator, except operating over immutable values
template <typename It>
struct const_iterator_type;

// The default implementation when the iterator is a C pointer is to use the standard constness semantics
template <typename T> struct const_iterator_type<T*>       { using type = T const*; };
template <typename T> struct const_iterator_type<T const*> { using type = T const*; };

/// \brief Metafunction predicate returning whether the given iterator allows for changing its values
/// \ingroup GILIsMutable
template <typename It>
struct iterator_is_mutable{};

// The default implementation when the iterator is a C pointer is to use the standard constness semantics
template <typename T>
struct iterator_is_mutable<T*> : std::true_type {};

template <typename T>
struct iterator_is_mutable<T const*> : std::false_type {};

/// \defgroup PixelIteratorModelInterleavedPtr C pointer to a pixel
/// \ingroup PixelIteratorModel
/// \brief Iterators over interleaved pixels.
/// A C pointer to a model of PixelValueConcept is used as an iterator over interleaved pixels. Models PixelIteratorConcept, HomogeneousPixelBasedConcept, HasDynamicXStepTypeConcept, MemoryBasedIteratorConcept



/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

/// \ingroup PixelIteratorModelInterleavedPtr
template <typename Pixel>
struct dynamic_x_step_type<Pixel*> {
    using type = memory_based_step_iterator<Pixel *>;
};

/// \ingroup PixelIteratorModelInterleavedPtr
template <typename Pixel>
struct dynamic_x_step_type<const Pixel*> {
    using type = memory_based_step_iterator<const Pixel *>;
};


/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename Pixel>
struct color_space_type<Pixel*> : color_space_type<Pixel> {};

template <typename Pixel>
struct color_space_type<Pixel const*> : color_space_type<Pixel> {};

template <typename Pixel>
struct channel_mapping_type<Pixel*> : channel_mapping_type<Pixel> {};

template <typename Pixel>
struct channel_mapping_type<Pixel const*> : channel_mapping_type<Pixel> {};

template <typename Pixel>
struct is_planar<Pixel*> : is_planar<Pixel> {};

template <typename Pixel>
struct is_planar<Pixel const*> : is_planar<Pixel> {};

/////////////////////////////
//  HomogeneousPixelBasedConcept
/////////////////////////////

template <typename Pixel>
struct channel_type<Pixel*> : channel_type<Pixel> {};

template <typename Pixel>
struct channel_type<Pixel const*> : channel_type<Pixel> {};

////////////////////////////////////////////////////////////////////////////////////////
/// Support for pixel iterator movement measured in memory units (bytes or bits) as opposed to pixel type.
/// Necessary to handle image row alignment and channel plane alignment.
////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////
//  MemoryBasedIteratorConcept
/////////////////////////////

template <typename T>
struct byte_to_memunit : std::integral_constant<int, 1> {};

template <typename P>
inline std::ptrdiff_t memunit_step(P const*) { return sizeof(P); }

template <typename P>
inline std::ptrdiff_t memunit_distance(P const* p1, P const* p2)
{
    return (
        gil_reinterpret_cast_c<unsigned char const*>(p2) -
        gil_reinterpret_cast_c<unsigned char const*>(p1));
}

template <typename P>
inline void memunit_advance(P* &p, std::ptrdiff_t diff)
{
    p = (P*)((unsigned char*)(p)+diff);
}

template <typename P>
inline P* memunit_advanced(const P* p, std::ptrdiff_t diff)
{
    return (P*)((char*)(p)+diff);
}

//  memunit_advanced_ref
//  (shortcut to advancing a pointer by a given number of memunits and taking the reference in case the compiler is not smart enough)

template <typename P>
inline P& memunit_advanced_ref(P* p, std::ptrdiff_t diff) {
    return *memunit_advanced(p,diff);
}

} }  // namespace boost::gil

#endif

/* pixel_iterator.hpp
K3RUw3UyPnHdvvGJu3ceTu1FWLtf96KwjSPwOq3DN5t3MzU+EGdQnxCn25LcYdqQ+Aa+sGuskf3aSDW1+QB8irrBeWWNwsQL/lyKoYbn6YkHX1PV3CbfLVT23IktiElOjMUT6r/RmsvT5WoePcuzpG0yA2r8aCB4rX1qt3syAIalRUbVDWQ0HScux0GFduHbOuK1sz7+9nkrkN9or15qaeR/I5Pjzs8JJv0LjSEDVjKAWXe1jciJ2vn41JPt22cj3G/evCoO6V5rM7cNBL9NHpWU5h1hYBsxO8Uq3NYKDYw1KNmKynxfS11MhqFYa42QsUfT1suE7YoPTawBjC3CnnosjJHYnoA0tZ2A19veMxMPkeJGrHDZlInh1ccuvlbmYn7ce0WuxfdqzPyrXlPEu32vLpB8o9hQkbb1RBCx88Es7ofeF4ns7lTB5lnuKFvZt57oWj/GFJqBIqymcCo7q8IpIqxxPEUVBlQMl+tot9yF6BEZjomMIGKY3JU1reqj6y32RcYlKy/XlfHm1MUb5aGXzRLPZN5IvrccubcYxRzJnAJIuVJPCXBL9gMScNFE7zJHwF2JCwhCcyK+fxevjn/8/f98v1eUd/CeoFv3nlgmJBad7prZGd9wMdHt9ulAeuc//7hlgYwHf/JE
*/