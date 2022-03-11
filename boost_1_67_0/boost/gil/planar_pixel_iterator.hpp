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