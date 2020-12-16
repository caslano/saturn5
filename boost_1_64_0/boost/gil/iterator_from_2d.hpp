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
efiUnLr2o60rH1+jx6I/DIgmTeF6l+PvM77WwcM0hLNTvCl2Z4cXH5ZGRwlZxDnj5VBbFHUws8HloVmLfD7l4vHT58hoU77hxi4cqlcyjbd6uL7yfdMmD8/J10138XMoX1nW2zp4ZMSJfOi7K3Hip9qppzb4eyXOsMHX341wpYNnvHqTD8ffY3Nxb6vzsnCdj0d1EFlpjW1X4EIu14fX3V1xxxuHTCdIAVBOom4F91C8qQk5MGtbvZ84N3s4ZIu7JhKf9z1yT08YxzbXOtzq4dJ8gtNzQ5+Ho+cMIt519/LwWv543xZx7bGapoFsU01sBmeJN6wuduLUqxsZ4b3B8dzNoOvrBYX77WzmBFvA8b9Jz5xH3gcc5016t14P3A8cz72FdyRdfxXhqk2JNx630je0MxqrgdEaqjhvjbn9DO534bNXPfEZ7aEkvUGi5yS34e/cLjnMOo3RHex6rnJH9T2y0oGFeHkeNRre14y/N5qzwr8nvuCGTuqZ+fzFH1v4FBy4mcR3YF6Qd0mycrMa38Y6CAUE/kjgCJ+uq9BY0oue6Qeu053S4eOKoGZqh7V+BX/6rPle1Y2fCHId5CEXef5Kt4zG1Dq9xa91Gea5H08rJ3U6zv/YxSKFWY/H/8yL15N795v3bzo4dsKkzoc6uZL4DHOfnrkr03o5i35XlhloPDc9+iHbv66YymC1N1zmmyOIBpdtyLnp6Q/Z6/bpSjrIlkvw18sOqoviqrnanl14JZl8EngsuBE/m9g2xIqvSJ7s3wdWdOdFU3TB3bKyO5cOQSJ+4q5yuE5RaPvpop/nqsD806uX5pMarMeZNS5frMGKtO2/zRI80qKfuNddtQSXlnBID5Z/aqkwxOa3M9Y6XKeu8RrsbbvzSCTaD6XvdsT11AV+36sLh5LPvIvr/Dw3zgvXEM9T/joNL7+2G4eilXO/23flUtRiDbiXuG5eSzuxG4di1nXuzB2It2RZC1v8jl34xNR3lBXuBJ65u4ztjnPRd6sscfcR750wr/fODo+uLqGLKdheOLLB4eEyX2XJS9vt/EYPB1uRSABYZly+cRN45n0apM1ghbtIrIne39hIq++qsCXzj8fEP0bjSRWvTueo141XNzX+1wiP4OnZ8fmphkqM6Nv/afBJIkAMXTIlxucf/pDGZ4Snh3hoiiDe1zi+kvp/vKrTQEE0xnm5Vfb7fc6aZCWo5OBNsfw1yemxmYTq50heKOUNqI07eMdWEpQV6hkDe/90Ykbya5ViOluu4ITrNtphMiF6pnQcBygO8o3MpUvJJLa/MJ+X9J6k5k9YOkGhZBUusAloryZhhzr4beKTTzScc6rwXYp0wnq6iULzn23x4QVTxtnkmD82PW74G/DuwadQ144/Xt2hoaJXKsNuw/d7q7UW+zuUm8d0On4L4QsIp2qGXjf9Af27jhVauFpE67A/xTeVILrvAqWNOo7vKzbG32nNnBBj5/4KPxu5P1bMSWsfbGIF4VF9g35UfWMbidZ0NEeE5zdYVwJTNn2k8L5ksDdr3Tt32oNTpec2mlgFDt1tRlGw/KnVhJFeNGVg/EFrHFzlj5C99irgnO9RrwXdaK18H5XJjrghqdvX6QksyKd9yxMo/yjttGyiukZUI433iD27+tPjBzV6gOt+YeCnzl356IYk/mgHd/ePbr7g4Jg2yf7iSBQ+uoyPFmUpBaLvevIP9V0N7UaLHnWS9vriDwinoNFGp7DXN3B4nqc0NfainxIGxdH3YtjAtenaBtfh4nv22vr7y3WYODFtLes19J027TCvNvHsZFkoQtJQy3u4xuJHkdo6b3L6Oy0Ft+eeET18oHpJLfdNHCcWbWejFae6xvY=
*/