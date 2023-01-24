//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_POSITION_ITERATOR_HPP
#define BOOST_GIL_POSITION_ITERATOR_HPP

#include <boost/gil/locator.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \defgroup PixelIteratorModelVirtual position_iterator
/// \ingroup PixelIteratorModel
/// \brief An iterator that remembers its current X,Y position and invokes a function object with it upon dereferencing.
/// Models PixelIteratorConcept, PixelBasedConcept, HasDynamicXStepTypeConcept. Used to create virtual image views.

/// \brief An iterator that remembers its current X,Y position and invokes a function object with it upon dereferencing.
/// Used to create virtual image views.
/// Models: StepIteratorConcept, PixelIteratorConcept, PixelBasedConcept, HasDynamicXStepTypeConcept
/// \ingroup PixelIteratorModelVirtual PixelBasedModel
/// \tparam Deref A function object that given a point returns a pixel reference. Models PixelDereferenceAdaptorConcept
/// \tparam Dim Dimension to advance along
template <typename Deref, int Dim>
struct position_iterator : public iterator_facade<position_iterator<Deref,Dim>,
                                                  typename Deref::value_type,
                                                  std::random_access_iterator_tag,
                                                  typename Deref::reference,
                                                  typename Deref::argument_type::template axis<Dim>::coord_t> {
    using parent_t = iterator_facade<position_iterator<Deref,Dim>,
                            typename Deref::value_type,
                            std::random_access_iterator_tag,
                            typename Deref::reference,
                            typename Deref::argument_type::template axis<Dim>::coord_t>;
    using difference_type = typename parent_t::difference_type;
    using reference = typename parent_t::reference;
    using point_t = typename Deref::argument_type;

    position_iterator() {}
    position_iterator(const point_t& p, const point_t& step, const Deref& d) : _p(p), _step(step), _d(d) {}

    position_iterator(const position_iterator& p) : _p(p._p), _step(p._step), _d(p._d) {}
    template <typename D> position_iterator(const position_iterator<D,Dim>& p) : _p(p._p), _step(p._step), _d(p._d) {}
    position_iterator& operator=(const position_iterator& p) { _p=p._p; _d=p._d; _step=p._step; return *this; }

    const point_t&   pos()      const { return _p; }
    const point_t&   step()     const { return _step; }
    const Deref&     deref_fn() const { return _d; }

    void set_step(difference_type s) { _step[Dim]=s; }
    /// For some reason operator[] provided by iterator_adaptor returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { point_t p=_p; p[Dim]+=d*_step[Dim]; return _d(p); }

private:
    point_t _p, _step;
    Deref   _d;

    template <typename DE, int DI> friend struct position_iterator;
    friend class boost::iterator_core_access;
    reference dereference()     const { return _d(_p); }
    void increment()                  { _p[Dim]+=_step[Dim]; }
    void decrement()                  { _p[Dim]-=_step[Dim]; }
    void advance(difference_type d)   { _p[Dim]+=d*_step[Dim]; }

    difference_type distance_to(const position_iterator& it) const { return (it._p[Dim]-_p[Dim])/_step[Dim]; }
    bool equal(const position_iterator& it) const { return _p==it._p; }
};

template <typename Deref,int Dim>
struct const_iterator_type<position_iterator<Deref,Dim> > {
    using type = position_iterator<typename Deref::const_t,Dim>;
};

template <typename Deref, int Dim>
struct iterator_is_mutable<position_iterator<Deref, Dim>>
    : std::integral_constant<bool, Deref::is_mutable>
{
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename Deref,int Dim>
struct color_space_type<position_iterator<Deref,Dim> > : public color_space_type<typename Deref::value_type> {};

template <typename Deref,int Dim>
struct channel_mapping_type<position_iterator<Deref,Dim> > : public channel_mapping_type<typename Deref::value_type> {};

template <typename Deref,int Dim>
struct is_planar<position_iterator<Deref, Dim>> : std::false_type {};

template <typename Deref,int Dim>
struct channel_type<position_iterator<Deref,Dim> > : public channel_type<typename Deref::value_type> {};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Deref,int Dim>
struct dynamic_x_step_type<position_iterator<Deref,Dim> > {
    using type = position_iterator<Deref,Dim>;
};

} }  // namespace boost::gil

#endif

/* position_iterator.hpp
gxfbK3vOlN2QvFeoKDqEA50tK3UpTiKzTgz9nhNZChURMBHVSfjdwIkwyyL0K9njMeMe8XfazYqdQAuKTLOigPSskj/n5ll7xgRtUGobLpvPuaN1+/iI5yKKHTui/ROQruNpI2fZi4xpytODZqb16krDZBX+2QpEzcTTeUAzxd6XLpMssWyoCS5467JUbFSv8cOesbhxMbhvPRMI1z6u9gjevePBBSZRFIOLwYTWwiV5Q0gbXzG3aOMpihzv+O4YXaRoYGy/6efMPaIoiBoF/UISYvLMT64EWyDkJhFXZpaCchXHXzD/ak3c+m7FH7usAImCOFqooOxqfqPBm0beoGIUEoZl+vIFRu5F9rYZfydtsxoXIJNhWx70F3jw9O/YJKjkuSBG1hGdH3FlPc6oJlyxfu7sjuaFExb2higwtWyrFZMD6luiFWTweGWCYbwqZU3Pz5xsnWC+IMJS3gbDIjZDlHJM0+V+AGn21zFrKfum1cWd33+3dPB+zsrRSPVt7A7wfVVztQSTAL4bjLVJEch+K/1LyTUBBZ9YdUplB62lGGDvKcIMjzObQ7sYIeqH+EIx+3VOt4V+N/OY6kc7hqoOYcOm7z/4p6tiUDE8PaBRyoU1Io7FYiVFQtrCrUQzqX4nWSwZ8j+6K4DqqLLCWfKfUDjoPBxDAxu0utmS5QtnvnqPU0Rjqro7bxayGOESnYzZGFxdGGn7T2we
*/