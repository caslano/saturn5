//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_BIT_ALIGNED_PIXEL_ITERATOR_HPP
#define BOOST_GIL_BIT_ALIGNED_PIXEL_ITERATOR_HPP

#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/pixel_iterator.hpp>

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <functional>
#include <type_traits>

namespace boost { namespace gil {

/// A model of a heterogeneous pixel that is not byte aligned.
/// Examples are bitmap (1-bit pixels) or 6-bit RGB (222).

/// \defgroup PixelIteratorNonAlignedPixelIterator bit_aligned_pixel_iterator
/// \ingroup PixelIteratorModel
/// \brief An iterator over non-byte-aligned pixels. Models PixelIteratorConcept, PixelBasedConcept, MemoryBasedIteratorConcept, HasDynamicXStepTypeConcept

////////////////////////////////////////////////////////////////////////////////////////
/// \brief An iterator over non-byte-aligned pixels. Models PixelIteratorConcept, PixelBasedConcept, MemoryBasedIteratorConcept, HasDynamicXStepTypeConcept
///
/// An iterator over pixels that correspond to non-byte-aligned bit ranges. Examples of such pixels are single bit grayscale pixel, or a 6-bit RGB 222 pixel.
///
/// \ingroup PixelIteratorNonAlignedPixelIterator PixelBasedModel

template <typename NonAlignedPixelReference>
struct bit_aligned_pixel_iterator : public iterator_facade<bit_aligned_pixel_iterator<NonAlignedPixelReference>,
                                                  typename NonAlignedPixelReference::value_type,
                                                  std::random_access_iterator_tag,
                                                  const NonAlignedPixelReference,
                                                  typename NonAlignedPixelReference::bit_range_t::difference_type> {
private:
    using parent_t = iterator_facade<bit_aligned_pixel_iterator<NonAlignedPixelReference>,
                            typename NonAlignedPixelReference::value_type,
                            std::random_access_iterator_tag,
                            const NonAlignedPixelReference,
                            typename NonAlignedPixelReference::bit_range_t::difference_type>;
    template <typename Ref> friend struct bit_aligned_pixel_iterator;

    using bit_range_t = typename NonAlignedPixelReference::bit_range_t;
public:
    using difference_type = typename parent_t::difference_type;
    using reference = typename parent_t::reference;

    bit_aligned_pixel_iterator() {}
    bit_aligned_pixel_iterator(const bit_aligned_pixel_iterator& p) : _bit_range(p._bit_range) {}
    bit_aligned_pixel_iterator& operator=(const bit_aligned_pixel_iterator& p) { _bit_range=p._bit_range; return *this; }

    template <typename Ref> bit_aligned_pixel_iterator(const bit_aligned_pixel_iterator<Ref>& p) : _bit_range(p._bit_range) {}

    bit_aligned_pixel_iterator(reference* ref) : _bit_range(ref->bit_range()) {}
    explicit bit_aligned_pixel_iterator(typename bit_range_t::byte_t* data, int bit_offset=0) : _bit_range(data,bit_offset) {}

    /// For some reason operator[] provided by iterator_adaptor returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { bit_aligned_pixel_iterator it=*this; it.advance(d); return *it; }

    reference operator->()         const { return **this; }
    const bit_range_t& bit_range() const { return _bit_range; }
          bit_range_t& bit_range()       { return _bit_range; }
private:
    bit_range_t _bit_range;
    static constexpr int bit_size = NonAlignedPixelReference::bit_size;

    friend class boost::iterator_core_access;
    reference dereference()     const { return NonAlignedPixelReference(_bit_range); }
    void increment()                  { ++_bit_range; }
    void decrement()                  { --_bit_range; }
    void advance(difference_type d)   { _bit_range.bit_advance(d*bit_size); }

    difference_type distance_to(const bit_aligned_pixel_iterator& it) const { return _bit_range.bit_distance_to(it._bit_range) / bit_size; }
    bool equal(const bit_aligned_pixel_iterator& it) const { return _bit_range==it._bit_range; }
};

template <typename NonAlignedPixelReference>
struct const_iterator_type<bit_aligned_pixel_iterator<NonAlignedPixelReference>>
{
    using type =
        bit_aligned_pixel_iterator<typename NonAlignedPixelReference::const_reference>;
};

template <typename NonAlignedPixelReference>
struct iterator_is_mutable<bit_aligned_pixel_iterator<NonAlignedPixelReference>>
    : std::integral_constant<bool, NonAlignedPixelReference::is_mutable>
{};

template <typename NonAlignedPixelReference>
struct is_iterator_adaptor<bit_aligned_pixel_iterator<NonAlignedPixelReference>>
    : std::false_type
{};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename NonAlignedPixelReference>
struct color_space_type<bit_aligned_pixel_iterator<NonAlignedPixelReference> > : public color_space_type<NonAlignedPixelReference> {};

template <typename NonAlignedPixelReference>
struct channel_mapping_type<bit_aligned_pixel_iterator<NonAlignedPixelReference> > : public channel_mapping_type<NonAlignedPixelReference> {};

template <typename NonAlignedPixelReference>
struct is_planar<bit_aligned_pixel_iterator<NonAlignedPixelReference> > : public is_planar<NonAlignedPixelReference> {}; // == false

/////////////////////////////
//  MemoryBasedIteratorConcept
/////////////////////////////

template <typename NonAlignedPixelReference>
struct byte_to_memunit<bit_aligned_pixel_iterator<NonAlignedPixelReference>>
    : std::integral_constant<int, 8>
{};

template <typename NonAlignedPixelReference>
inline std::ptrdiff_t memunit_step(const bit_aligned_pixel_iterator<NonAlignedPixelReference>&) {
    return NonAlignedPixelReference::bit_size;
}

template <typename NonAlignedPixelReference>
inline std::ptrdiff_t memunit_distance(const bit_aligned_pixel_iterator<NonAlignedPixelReference>& p1, const bit_aligned_pixel_iterator<NonAlignedPixelReference>& p2) {
    return (p2.bit_range().current_byte() - p1.bit_range().current_byte())*8 + p2.bit_range().bit_offset() - p1.bit_range().bit_offset();
}

template <typename NonAlignedPixelReference>
inline void memunit_advance(bit_aligned_pixel_iterator<NonAlignedPixelReference>& p, std::ptrdiff_t diff) {
    p.bit_range().bit_advance(diff);
}

template <typename NonAlignedPixelReference>
inline bit_aligned_pixel_iterator<NonAlignedPixelReference> memunit_advanced(const bit_aligned_pixel_iterator<NonAlignedPixelReference>& p, std::ptrdiff_t diff) {
    bit_aligned_pixel_iterator<NonAlignedPixelReference> ret=p;
    memunit_advance(ret, diff);
    return ret;
}

template <typename NonAlignedPixelReference> inline
NonAlignedPixelReference memunit_advanced_ref(bit_aligned_pixel_iterator<NonAlignedPixelReference> it, std::ptrdiff_t diff) {
    return *memunit_advanced(it,diff);
}
/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename NonAlignedPixelReference>
struct dynamic_x_step_type<bit_aligned_pixel_iterator<NonAlignedPixelReference> > {
    using type = memory_based_step_iterator<bit_aligned_pixel_iterator<NonAlignedPixelReference> >;
};

/////////////////////////////
//  iterator_type_from_pixel
/////////////////////////////

template <typename B, typename C, typename L, bool M>
struct iterator_type_from_pixel<const bit_aligned_pixel_reference<B,C,L,M>,false,false,false>
{
    using type = bit_aligned_pixel_iterator<bit_aligned_pixel_reference<B,C,L,false>> ;
};

template <typename B, typename C, typename L, bool M>
struct iterator_type_from_pixel<const bit_aligned_pixel_reference<B,C,L,M>,false,false,true>
{
    using type = bit_aligned_pixel_iterator<bit_aligned_pixel_reference<B,C,L,true>>;
};

template <typename B, typename C, typename L, bool M, bool IsPlanar, bool IsStep, bool IsMutable>
struct iterator_type_from_pixel<bit_aligned_pixel_reference<B,C,L,M>,IsPlanar,IsStep,IsMutable>
    : public iterator_type_from_pixel<const bit_aligned_pixel_reference<B,C,L,M>,IsPlanar,IsStep,IsMutable> {};

} }  // namespace boost::gil

namespace std {

// It is important to provide an overload of uninitialized_copy for bit_aligned_pixel_iterator. The default STL implementation calls placement new,
// which is not defined for bit_aligned_pixel_iterator.
template <typename NonAlignedPixelReference>
boost::gil::bit_aligned_pixel_iterator<NonAlignedPixelReference> uninitialized_copy(boost::gil::bit_aligned_pixel_iterator<NonAlignedPixelReference> first,
                                                                                   boost::gil::bit_aligned_pixel_iterator<NonAlignedPixelReference> last,
                                                                                   boost::gil::bit_aligned_pixel_iterator<NonAlignedPixelReference> dst) {
    return std::copy(first,last,dst);
}

}   // namespace std
#endif

/* bit_aligned_pixel_iterator.hpp
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
*/