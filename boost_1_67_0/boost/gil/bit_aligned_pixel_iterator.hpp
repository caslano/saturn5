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