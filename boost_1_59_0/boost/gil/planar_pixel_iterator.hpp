//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PLANAR_PIXEL_ITERATOR_HPP
#define BOOST_GIL_PLANAR_PIXEL_ITERATOR_HPP

#include <boost/gil/pixel.hpp>
#include <boost/gil/step_iterator.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <iterator>
#include <type_traits>

namespace boost { namespace gil {

//forward declaration (as this file is included in planar_pixel_reference.hpp)
template <typename ChannelReference, typename ColorSpace>
struct planar_pixel_reference;

/// \defgroup ColorBaseModelPlanarPtr planar_pixel_iterator
/// \ingroup ColorBaseModel
/// \brief A homogeneous color base whose element is a channel iterator. Models HomogeneousColorBaseValueConcept
/// This class is used as an iterator to a planar pixel.

/// \defgroup PixelIteratorModelPlanarPtr planar_pixel_iterator
/// \ingroup PixelIteratorModel
/// \brief An iterator over planar pixels. Models PixelIteratorConcept, HomogeneousPixelBasedConcept, MemoryBasedIteratorConcept, HasDynamicXStepTypeConcept

////////////////////////////////////////////////////////////////////////////////////////
/// \brief An iterator over planar pixels. Models HomogeneousColorBaseConcept, PixelIteratorConcept, HomogeneousPixelBasedConcept, MemoryBasedIteratorConcept, HasDynamicXStepTypeConcept
///
/// Planar pixels have channel data that is not consecutive in memory.
/// To abstract this we use classes to represent references and pointers to planar pixels.
///
/// \ingroup PixelIteratorModelPlanarPtr ColorBaseModelPlanarPtr PixelBasedModel
template <typename ChannelPtr, typename ColorSpace>
struct planar_pixel_iterator
    :
    iterator_facade
    <
        planar_pixel_iterator<ChannelPtr, ColorSpace>,
        pixel<typename std::iterator_traits<ChannelPtr>::value_type,layout<ColorSpace>>,
        std::random_access_iterator_tag,
        planar_pixel_reference<typename std::iterator_traits<ChannelPtr>::reference, ColorSpace> const
    >,
    detail::homogeneous_color_base
    <
        ChannelPtr,
        layout<ColorSpace>,
        mp11::mp_size<ColorSpace>::value
    >
{
private:
    using parent_t = iterator_facade
        <
            planar_pixel_iterator<ChannelPtr, ColorSpace>,
            pixel<typename std::iterator_traits<ChannelPtr>::value_type,layout<ColorSpace>>,
            std::random_access_iterator_tag,
            planar_pixel_reference<typename std::iterator_traits<ChannelPtr>::reference, ColorSpace> const
        >;

    using color_base_parent_t = detail::homogeneous_color_base
        <
            ChannelPtr,
            layout<ColorSpace>,
            mp11::mp_size<ColorSpace>::value
        >;

    using channel_t = typename std::iterator_traits<ChannelPtr>::value_type;

public:
    using value_type = typename parent_t::value_type;
    using reference = typename parent_t::reference;
    using difference_type = typename parent_t::difference_type;

    planar_pixel_iterator() : color_base_parent_t(0) {}
    planar_pixel_iterator(bool) {}        // constructor that does not fill with zero (for performance)

    planar_pixel_iterator(const ChannelPtr& v0, const ChannelPtr& v1) : color_base_parent_t(v0,v1) {}
    planar_pixel_iterator(const ChannelPtr& v0, const ChannelPtr& v1, const ChannelPtr& v2) : color_base_parent_t(v0,v1,v2) {}
    planar_pixel_iterator(const ChannelPtr& v0, const ChannelPtr& v1, const ChannelPtr& v2, const ChannelPtr& v3) : color_base_parent_t(v0,v1,v2,v3) {}
    planar_pixel_iterator(const ChannelPtr& v0, const ChannelPtr& v1, const ChannelPtr& v2, const ChannelPtr& v3, const ChannelPtr& v4) : color_base_parent_t(v0,v1,v2,v3,v4) {}

    template <typename IC1,typename C1>
    planar_pixel_iterator(const planar_pixel_iterator<IC1,C1>& ptr) : color_base_parent_t(ptr) {}

    /// Copy constructor and operator= from pointers to compatible planar pixels or planar pixel references.
    /// That allow constructs like pointer = &value or pointer = &reference
    /// Since we should not override operator& that's the best we can do.
    template <typename P>
    planar_pixel_iterator(P* pix) : color_base_parent_t(pix, true) {
        function_requires<PixelsCompatibleConcept<P,value_type> >();
    }

    struct address_of { template <typename T> T* operator()(T& t) { return &t; } };
    template <typename P>
    planar_pixel_iterator& operator=(P* pix) {
        function_requires<PixelsCompatibleConcept<P,value_type> >();
        static_transform(*pix,*this, address_of());

        // PERFORMANCE_CHECK: Compare to this:
        //this->template semantic_at_c<0>()=&pix->template semantic_at_c<0>();
        //this->template semantic_at_c<1>()=&pix->template semantic_at_c<1>();
        //this->template semantic_at_c<2>()=&pix->template semantic_at_c<2>();
        return *this;
    }

    /// For some reason operator[] provided by iterator_facade returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d)       const { return memunit_advanced_ref(*this,d*sizeof(channel_t));}

    reference operator->()                        const { return **this; }

    // PERFORMANCE_CHECK: Remove?
    bool operator< (const planar_pixel_iterator& ptr)   const { return gil::at_c<0>(*this)< gil::at_c<0>(ptr); }
    bool operator!=(const planar_pixel_iterator& ptr)   const { return gil::at_c<0>(*this)!=gil::at_c<0>(ptr); }
private:
    friend class boost::iterator_core_access;

    void increment()            { static_transform(*this,*this,detail::inc<ChannelPtr>()); }
    void decrement()            { static_transform(*this,*this,detail::dec<ChannelPtr>()); }
    void advance(std::ptrdiff_t d){ static_transform(*this,*this,std::bind(detail::plus_asymmetric<ChannelPtr,std::ptrdiff_t>(),std::placeholders::_1,d)); }
    reference dereference() const { return this->template deref<reference>(); }

    std::ptrdiff_t distance_to(const planar_pixel_iterator& it) const { return gil::at_c<0>(it)-gil::at_c<0>(*this); }
    bool equal(const planar_pixel_iterator& it) const { return gil::at_c<0>(*this)==gil::at_c<0>(it); }
};

namespace detail {
template <typename I>
struct channel_iterator_is_mutable : std::true_type {};

template <typename I>
struct channel_iterator_is_mutable<I const*> : std::false_type {};

} // namespace detail

template <typename IC, typename C>
struct const_iterator_type<planar_pixel_iterator<IC,C> > {
private:
    using channel_t = typename std::iterator_traits<IC>::value_type;
public:
    using type = planar_pixel_iterator<typename channel_traits<channel_t>::const_pointer,C>;
};

// The default implementation when the iterator is a C pointer is to use the standard constness semantics
template <typename IC, typename C>
struct iterator_is_mutable<planar_pixel_iterator<IC,C> > : public detail::channel_iterator_is_mutable<IC> {};

/////////////////////////////
//  ColorBasedConcept
/////////////////////////////

template <typename IC, typename C, int K>
struct kth_element_type<planar_pixel_iterator<IC, C>, K>
{
    using type = IC;
};

template <typename IC, typename C, int K>
struct kth_element_reference_type<planar_pixel_iterator<IC, C>, K>
    : std::add_lvalue_reference<IC> {};

template <typename IC, typename C, int K>
struct kth_element_const_reference_type<planar_pixel_iterator<IC, C>, K>
    : std::add_lvalue_reference<typename std::add_const<IC>::type>
{};

/////////////////////////////
//  HomogeneousPixelBasedConcept
/////////////////////////////

template <typename IC, typename C>
struct color_space_type<planar_pixel_iterator<IC,C>>
{
    using type = C;
};

template <typename IC, typename C>
struct channel_mapping_type<planar_pixel_iterator<IC, C>>
    : channel_mapping_type<typename planar_pixel_iterator<IC,C>::value_type>
{};

template <typename IC, typename C>
struct is_planar<planar_pixel_iterator<IC, C>> : std::true_type {};

template <typename IC, typename C>
struct channel_type<planar_pixel_iterator<IC, C>>
{
    using type = typename std::iterator_traits<IC>::value_type;
};

/////////////////////////////
//  MemoryBasedIteratorConcept
/////////////////////////////

template <typename IC, typename C>
inline std::ptrdiff_t memunit_step(const planar_pixel_iterator<IC,C>&) { return sizeof(typename std::iterator_traits<IC>::value_type); }

template <typename IC, typename C>
inline std::ptrdiff_t memunit_distance(const planar_pixel_iterator<IC,C>& p1, const planar_pixel_iterator<IC,C>& p2) {
    return memunit_distance(gil::at_c<0>(p1),gil::at_c<0>(p2));
}

template <typename IC>
struct memunit_advance_fn {
    memunit_advance_fn(std::ptrdiff_t diff) : _diff(diff) {}
    IC operator()(const IC& p) const { return memunit_advanced(p,_diff); }

    std::ptrdiff_t _diff;
};

template <typename IC, typename C>
inline void memunit_advance(planar_pixel_iterator<IC,C>& p, std::ptrdiff_t diff) {
    static_transform(p, p, memunit_advance_fn<IC>(diff));
}

template <typename IC, typename C>
inline planar_pixel_iterator<IC,C> memunit_advanced(const planar_pixel_iterator<IC,C>& p, std::ptrdiff_t diff) {
    planar_pixel_iterator<IC,C> ret=p;
    memunit_advance(ret, diff);
    return ret;
}

template <typename ChannelPtr, typename ColorSpace>
inline planar_pixel_reference<typename std::iterator_traits<ChannelPtr>::reference,ColorSpace>
    memunit_advanced_ref(const planar_pixel_iterator<ChannelPtr,ColorSpace>& ptr, std::ptrdiff_t diff) {
    return planar_pixel_reference<typename std::iterator_traits<ChannelPtr>::reference,ColorSpace>(ptr, diff);
}

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename IC, typename C>
struct dynamic_x_step_type<planar_pixel_iterator<IC,C> > {
    using type = memory_based_step_iterator<planar_pixel_iterator<IC,C>>;
};
} }  // namespace boost::gil

#endif

/* planar_pixel_iterator.hpp
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
*/