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
Qn67JPqxCblzWIWrbm2Q+W2QJexowYF7c1v5XXxWrQ8T+XB9TSZ4QXCXvPt+qr4jDeDfWEXdaUevE5TJHC94OPl57hg6rxUPcQKtK6myCR7wDqfi9z6nYlEyZDq2maM7jQYGIMzAa9Yv7LiTdKFj6Y58Tr29VWmOsGW1P9zJwbeqN65R8zk1n6aCKwmSb+z3pwK0qyE2za7x5SzezLZ58XNKrjcBTp+6neaHJSRhuVivfk7lKC3gS1PkkeZHJQ10bDGfXNFP6NnkQiau1bxMnKreKOv9XY1vBA3Dh/el4AV+KuClf1VCFSHsIvg5QX5djLzc9Hn1JheWPt7T8kleePYvJut4n5ffU8WBDZ7zD+TFVtohZljc7eeVr3RhpYtGnSOU+4RifCjuVuDjnd5P26KJc2/CUqz1z2tqHFI88NsM5t5UGjiZx3+L9GjRR2jtNXEFhylBX+aL2aP47M/L+WzCJI7z1lf0ycuNrNbebGt12LPXhO5SI71xUMIPVThXqHxNN12TdO0Wi5JYrkUSMvg+Hb/bu6ZsSzWiskucl06aI2mLUlOMcuELr6kc5SG8X/F4OE1/Y3dH3aUXBX4BP5cowU0Yj7QZz5wDdlZdvab0FXiT42m8muRBng1blLPnmpLT4MSNkLTS8UHu8doznmxs15TuFtVx4xszyQM/E9g8zL4g7ax1CYtQExrNw1SOkJsEboI7HGHLAWK0hjSEbt+snd7dcAcA4R4XuHYNlRGS21dEV6cHYbqmEbgZ1g48RfDWuETXFvAeY3x2yE9O4MMuCEc5H0Yboq1y0pCPlcBr8X4OjSKN+/vJyq5DhOzElUA+t7wP45VhXiLKPiDSFBWl9vovOV6YYKOiqA1eBw+iTdPNZOB/fUHZuhIs/DLPB+Lu6nGLRK588pn7orxf4cBQw9Gr3/uQjnBvbU7c0Mv+sV9U8X02yz6eyUZe5mBGsHCGZLYvKj0/KXEV9seeG4UJQX5vuRaJ4CGAz1wcwo+Z1v6oaqt8yl9Utty6btKszpYYWHN6kbMFk5/dF1VMZRJbP02aB/4wpWX464p2CQHLb9tG01b3Lskjsy8pORFJiSq4A3H8yTx1+r31S2o9lmEdFpWVsxbrZ7F2rMB75rXcQkJVB/hbzQsFPzHmEkYbRCtxfkgj0rWNvqTOv9RgSeP+ZcrQgSE9jIergofUC+E2C1Ev5DxorYj8cr6k4uatjxSCRyUPtiDffM8Kd521Q9lNf/8l5bfcBEFmCrGelCb06gH3XwoXhucIdq+U09frmO7xL6v4tiIzqD9UCbrTmo9H7yJfVjqxzaubBpz81HL2KTf6l9X8w4cXQr/hPJDGo9/KFG24K6RRXZeSuNuDE/fXVUU7aCF4BbncS07T0fEB31O0qxyZDuHgCONQH1fpNGFyXlf+KtcFvsF5HhRV0ASc9v9zjv5L9BOgHxS6SNGPG273nHRu62Z6wzlDOvhXpByEs6+EkS8nHqavMspzuCLw/S5OE0ZbX9GGWVB+e/YVFRtYQpuJ/ZLRnbQP6bfa+VeUHIBNE/rwF3YVXg6Q4jYpp57AT7zUwCmyyMW+U5qDT/MvcFPs+zjG1mmJtpLcdP6I63rs46ypTS3HgH+8jsHi+DDPJpi6NvOJPB0z7N6cfVWuOeSES3wIe5zmhLawJH8d+aqKT6lNWpU1jTu5CsvXQ3rXzRQ+nGPgZBNrPi7u9f5/S+/C5wR+gnc/eMXEfqHpU5ZWpZNfVuOQBoh+zDNxB05oL0vj8D3FRwKX5bxMfM0HrT71Hde/quT/MAyqpBVnwLIWw3Kqf1XJUGWKIzyviD4/dnWevK8pP4MmxM0p5YgJ7YV4P/I1+e1wkkA=
*/