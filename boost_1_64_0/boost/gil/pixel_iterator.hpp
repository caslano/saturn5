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
uRWhD0laX6KPCvHvTZFmwdgH+HaVpvZ31l+N71+unXX5ghz/xo/zPDaB1z95u4MdthE8nDn6pwf61xT9OoXqUaFK7XDBbtL57hbANq1vOrvUOOaBievGLzx+SeMOXXQu3RL3zw6X6vj5aRLWhfH+S7XEZFg7HBdFtJMKN2JZpxJ3a8Nt7tds7Z2z4lHvFOiNc3BkIddgU6Z51QaJ7MfJoHIxrdNaEH3kXuwnOMBN6Dl3k64Le/qxk0avx3Oij8KORWAQ1+850/g+TrbT3MfFnW8DD5cVftrYutrIgODe8B1pGJ/BhXOw17LM1xdClinToIhiJC3gr6oO59nDPPxoIe/qqMmLNMH8dyUyQAuuJqOcp2aT5cz8M+/nRN6GQVCjji89zA68PnW4uxbyHkgCk9S1Hzi6euceG/BuvyfxmraMsqg1HtJo8DdOR+/Y8J2H96Scb0yOusDIpHBmH4rJ+a48Xi+Hbdudu75t3Tpea2Vy2GhZTVKj6KcFUk8UxnjqqdnRH9eHwEtwz7epH5Vxh0f01NSC/9VhfeyJ8z1Icz9tUJBVvkL3aMVwPohv9r22KeK8SnNHExnLsab66pMXtuxp1/WDOd6n+4Xo/5L3BXUrCsq2iIzHX7kd1xdIttmT91mRhdgVWePog/jS9752oPd3+b1ZBpG+SjNvY7fzYHTVq3q0YFgb+/IsSJDzNKnSxNEDGi7D6bqo21Rzc198Z1L6aeFHsaVrEwNwsptUw3BfjnOB1B9FGpf/ne6xLtfNMM7DmJ0S3xBjXwRtlpWB1321eyJxD3YOd2/4/ovq+03c5kFSh4oP0uXoVuP1MvflWRimscmLxpHvD7OhMgDEdqp/SOeJwK8xcVUUJibSPGi9TMszf96X+wyVhRNkv4kdI+cgj+ydRsKkYQzoXlH0mwpVbVHQdJn+4FPrjnZHfxiHw69WsmNWhE2YDvOAq2VI+Hz2wvrN53FVy7XoCfzCi8oEFcGbiTUx3z+NopBWwNPy1SnRh/HyuqmjOCIWeMLpzQ23KBZyPi+LPjLPlDEmNJtYE70v7HA7kl4k8BOvibMwropWMcEXJNXC/KXARXH1sPKLtm4FbfvY7Rak1v/+7PCpHmqdplWcZT1tVzzgtXub7pOfTWtA4LVeieK0td8CD1TwtZt7r9m0t1on4q7v4NtdKIKqx3pY1fwNiyKJqyDl9EmqZWN+/DVyzNowLVMTVo7+tESGK2LAf6HAL7wkLrPYFCXR3YND/+L81p4sf30uGPQQgV95bRbVbVg4vl1xNtjZOv9TN4J6H3+P9xHaufNNHYXBRL3jXs4VxbVHXfzPvB9MRWFVqMx3SYY6SWhzR9lz/v4aOe9xGhY4BnFvnTtID9qgO+Ai59sWfM+LKvDD7tv7F9QL+2eGKKpBIIPtzJttFINOe1Ge5yZv/Cg3DejTdnXKLU2mUh+PBcNcXpTjWJQVdJzM1/x0gv7ow/gqmAF3SEe4KPdRFJZNXWJBDkdodyxLDYt0BIHbeGmeFyYo656+i1mBpnDe3sJyPe3QPhZ9QHaCMQ9airF94LMdkpuV01s367P0xkV1L/llg8xRbgzcESJGQO6n279WycZBkMCU6cEJY9vdpVJrUPv4iMAPMAdREMRZ5Gkzvpo7T9FtalNBN6o8sgs6IQaum71lCdeJGzs6w3kfMAlFVRBHPi7UXff+D2u1c2/uD5Rub8MjFH0kw34WfLTQdaukqH2wYRekXSy2ULpjo9c0MCvQX9V98iPFC2wEWAlhy3lxbh+aF7IX3FBjWec1LGXQlTY3p/cms2HOXid13cgEsfGha1hiPX14SthLeZP0q2EMbnqdGscgyrMoyjxr7H/t/7A=
*/