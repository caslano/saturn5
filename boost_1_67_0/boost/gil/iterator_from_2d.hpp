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