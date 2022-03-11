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