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
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
*/