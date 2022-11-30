//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_ITERATOR_FROM_2D_HPP
#define BOOST_GIL_ITERATOR_FROM_2D_HPP

#include <boost/gil/concepts.hpp>
#include <boost/gil/locator.hpp>
#include <boost/gil/pixel_iterator.hpp>
#include <boost/gil/point.hpp>

#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace boost { namespace gil {

/// pixel step iterator, pixel image iterator and pixel dereference iterator

////////////////////////////////////////////////////////////////////////////////////////
///
///                 ITERATOR FROM 2D ADAPTOR
///
////////////////////////////////////////////////////////////////////////////////////////


/// \defgroup PixelIteratorModelFromLocator iterator_from_2d
/// \ingroup PixelIteratorModel
/// \brief An iterator over two-dimensional locator. Useful for iterating over the pixels of an image view. Models PixelIteratorConcept, PixelBasedConcept, HasDynamicXStepTypeConcept


/// \ingroup PixelIteratorModelFromLocator PixelBasedModel
/// \brief Provides 1D random-access navigation to the pixels of the image. Models: PixelIteratorConcept, PixelBasedConcept, HasDynamicXStepTypeConcept
///
/// Pixels are traversed from the top to the bottom row and from the left to the right
/// within each row

template <typename Loc2>    // Models PixelLocatorConcept
class iterator_from_2d : public iterator_facade<iterator_from_2d<Loc2>,
                                                typename Loc2::value_type,
                                                std::random_access_iterator_tag,
                                                typename Loc2::reference,
                                                typename Loc2::coord_t> {
    BOOST_GIL_CLASS_REQUIRE(Loc2, boost::gil, PixelLocatorConcept)
public:
    using parent_t = iterator_facade<iterator_from_2d<Loc2>,
                            typename Loc2::value_type,
                            std::random_access_iterator_tag,
                            typename Loc2::reference,
                            typename Loc2::coord_t>;
    using reference = typename parent_t::reference;
    using difference_type = typename parent_t::difference_type;
    using x_iterator = typename Loc2::x_iterator;
    using point_t = typename Loc2::point_t;

    std::ptrdiff_t width()         const { return _width; }            // number of pixels per image row
    std::ptrdiff_t x_pos()         const { return _coords.x; }         // current x position
    std::ptrdiff_t y_pos()         const { return _coords.y; }         // current y position

    /// For some reason operator[] provided by iterator_adaptor returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { return *(*this+d); }

    bool            is_1d_traversable() const { return _p.is_1d_traversable(width()); }   // is there no gap at the end of each row?
    x_iterator&     x()                   { return _p.x(); }

    iterator_from_2d() = default;
    iterator_from_2d(const Loc2& p, std::ptrdiff_t width, std::ptrdiff_t x=0, std::ptrdiff_t y=0) : _coords(x,y), _width(width), _p(p) {}
    iterator_from_2d(const iterator_from_2d& pit) : _coords(pit._coords), _width(pit._width), _p(pit._p) {}
    template <typename Loc> iterator_from_2d(const iterator_from_2d<Loc>& pit) : _coords(pit._coords), _width(pit._width), _p(pit._p) {}
    iterator_from_2d& operator=(iterator_from_2d const& other) = default;

private:
    template <typename Loc> friend class iterator_from_2d;
    friend class boost::iterator_core_access;
    reference dereference() const { return *_p; }
    void increment() {
        ++_coords.x;
        ++_p.x();
        if (_coords.x>=_width) {
            _coords.x=0;
            ++_coords.y;
            _p+=point_t(-_width,1);
        }
    }
    void decrement() {
        --_coords.x;
        --_p.x();
        if (_coords.x<0) {
            _coords.x=_width-1;
            --_coords.y;
            _p+=point_t(_width,-1);
        }
    }

    BOOST_FORCEINLINE void advance(difference_type d) {
        if (_width==0) return;  // unfortunately we need to check for that. Default-constructed images have width of 0 and the code below will throw if executed.
        point_t delta;
        if (_coords.x+d>=0) {  // not going back to a previous row?
            delta.x=(_coords.x+(std::ptrdiff_t)d)%_width - _coords.x;
            delta.y=(_coords.x+(std::ptrdiff_t)d)/_width;
        } else {
            delta.x=(_coords.x+(std::ptrdiff_t)d*(1-_width))%_width -_coords.x;
            delta.y=-(_width-_coords.x-(std::ptrdiff_t)d-1)/_width;
        }
        _p+=delta;
        _coords.x+=delta.x;
        _coords.y+=delta.y;
    }

    difference_type distance_to(const iterator_from_2d& it) const {
        if (_width==0) return 0;
        return (it.y_pos()-_coords.y)*_width + (it.x_pos()-_coords.x);
    }

    bool equal(iterator_from_2d const& it) const
    {
        BOOST_ASSERT(_width == it.width()); // they must belong to the same image
        return _coords == it._coords && _p == it._p;
    }

    point_t _coords;
    std::ptrdiff_t _width;
    Loc2 _p;
};

template <typename Loc> // Models PixelLocatorConcept
struct const_iterator_type<iterator_from_2d<Loc> > {
    using type = iterator_from_2d<typename Loc::const_t>;
};

template <typename Loc> // Models PixelLocatorConcept
struct iterator_is_mutable<iterator_from_2d<Loc> > : public iterator_is_mutable<typename Loc::x_iterator> {};


/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Loc>
struct dynamic_x_step_type<iterator_from_2d<Loc> > {
    using type = iterator_from_2d<typename dynamic_x_step_type<Loc>::type>;
};


/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename Loc> // Models PixelLocatorConcept
struct color_space_type<iterator_from_2d<Loc> > : public color_space_type<Loc> {};

template <typename Loc> // Models PixelLocatorConcept
struct channel_mapping_type<iterator_from_2d<Loc> > : public channel_mapping_type<Loc> {};

template <typename Loc> // Models PixelLocatorConcept
struct is_planar<iterator_from_2d<Loc> > : public is_planar<Loc> {};

template <typename Loc> // Models PixelLocatorConcept
struct channel_type<iterator_from_2d<Loc> > : public channel_type<Loc> {};

} }  // namespace boost::gil

#endif

/* iterator_from_2d.hpp
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
*/