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
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
*/