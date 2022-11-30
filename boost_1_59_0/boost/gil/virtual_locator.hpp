//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_VIRTUAL_LOCATOR_HPP
#define BOOST_GIL_VIRTUAL_LOCATOR_HPP

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/position_iterator.hpp>

#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace boost { namespace gil {

/// \ingroup PixelLocatorModel PixelBasedModel
/// \brief A 2D locator over a virtual image
/// Upon dereferencing, invokes a given function object passing it its coordinates.
/// Models:
///   PixelLocatorConcept,
///   HasDynamicXStepTypeConcept,
///   HasDynamicYStepTypeConcept,
///   HasTransposedTypeConcept
///
/// \tparam DerefFn Function object that given a point returns a reference.
///         Models PixelDereferenceAdaptorConcept.
/// \tparam IsTransposed Indicates if locator should navigate in transposed mode.
template <typename DerefFn, bool IsTransposed>
class virtual_2d_locator
    : public pixel_2d_locator_base
        <
            virtual_2d_locator<DerefFn, IsTransposed>,
            position_iterator<DerefFn, IsTransposed>,
            position_iterator<DerefFn, 1-IsTransposed>
        >
{
    using this_t = virtual_2d_locator<DerefFn, IsTransposed>;
public:
    using parent_t = pixel_2d_locator_base
        <
            virtual_2d_locator<DerefFn, IsTransposed>,
            position_iterator<DerefFn, IsTransposed>,
            position_iterator<DerefFn, 1-IsTransposed>
        >;
    using const_t = virtual_2d_locator<typename DerefFn::const_t, IsTransposed>;
    using deref_fn_t = DerefFn;
    using point_t = typename parent_t::point_t;
    using coord_t = typename parent_t::coord_t;
    using x_coord_t = typename parent_t::x_coord_t;
    using y_coord_t = typename parent_t::y_coord_t;
    using x_iterator = typename parent_t::x_iterator;
    using y_iterator = typename parent_t::y_iterator;

    template <typename NewDerefFn>
    struct add_deref
    {
        using type = virtual_2d_locator<deref_compose<NewDerefFn, DerefFn>, IsTransposed>;

        static type make(this_t const& loc, NewDerefFn const& new_deref_fn)
        {
            return type(loc.pos(), loc.step(),
                deref_compose<NewDerefFn, DerefFn>(new_deref_fn, loc.deref_fn()));
        }
    };

    virtual_2d_locator(
        point_t const& p = {0, 0},
        point_t const& step = {1, 1},
        deref_fn_t const& deref_fn = deref_fn_t())
        : y_pos_(p, step, deref_fn)
    {}

    template <typename D, bool TR>
    virtual_2d_locator(virtual_2d_locator<D, TR> const &loc, coord_t y_step)
        : y_pos_(loc.pos(), point_t(loc.step().x, loc.step().y * y_step), loc.deref_fn())
    {}

    template <typename D, bool TR>
    virtual_2d_locator(virtual_2d_locator<D, TR> const& loc, coord_t x_step, coord_t y_step, bool transpose = false)
        : y_pos_(loc.pos()
        , transpose ?
            point_t(loc.step().x * y_step, loc.step().y * x_step) :
            point_t(loc.step().x * x_step, loc.step().y * y_step)
        , loc.deref_fn())
    {
        BOOST_ASSERT(transpose == (IsTransposed != TR));
    }

    template <typename D, bool TR>
    virtual_2d_locator(virtual_2d_locator<D, TR> const& other) : y_pos_(other.y_pos_) {}

    virtual_2d_locator(virtual_2d_locator const& other) : y_pos_(other.y_pos_) {}
    virtual_2d_locator& operator=(virtual_2d_locator const& other) = default;

    bool operator==(const this_t& p) const { return y_pos_ == p.y_pos_; }

    auto x() -> x_iterator&
    {
        return *gil_reinterpret_cast<x_iterator*>(this);
    }

    auto x() const -> x_iterator const&
    {
        return *gil_reinterpret_cast_c<x_iterator const*>(this);
    }

    auto y() -> y_iterator& { return y_pos_; }
    auto y() const -> y_iterator const& { return y_pos_; }

    /// Returns the y distance between two x_iterators given the difference of their x positions
    auto y_distance_to(this_t const& it2, x_coord_t) const -> y_coord_t
    {
        return (it2.pos()[1 - IsTransposed] - pos()[1 - IsTransposed])
                / step()[1 - IsTransposed];
    }

    /// \todo TODO: is there no gap at the end of each row?
    ///       i.e. can we use x_iterator to visit every pixel instead of nested loops?
    bool is_1d_traversable(x_coord_t) const { return false; }

    // Methods specific for virtual 2D locator
    auto pos() const -> point_t const& { return y_pos_.pos(); }
    auto step() const -> point_t const& { return y_pos_.step(); }
    auto deref_fn() const -> deref_fn_t const& { return y_pos_.deref_fn(); }

private:
    template <typename D, bool TR>
    friend class virtual_2d_locator;

    y_iterator y_pos_; // current position, the step and the dereference object
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename D, bool TR>
struct channel_type<virtual_2d_locator<D, TR>>
    : channel_type<typename virtual_2d_locator<D, TR>::parent_t>
{
};

template <typename D, bool TR>
struct color_space_type<virtual_2d_locator<D, TR>>
    : color_space_type<typename virtual_2d_locator<D, TR>::parent_t>
{
};

template <typename D, bool TR>
struct channel_mapping_type<virtual_2d_locator<D, TR>>
    : channel_mapping_type<typename virtual_2d_locator<D, TR>::parent_t>
{
};

template <typename D, bool TR>
struct is_planar<virtual_2d_locator<D, TR>>
    : is_planar<typename virtual_2d_locator<D, TR>::parent_t>
{
};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename D, bool TR>
struct dynamic_x_step_type<virtual_2d_locator<D,TR>>
{
    using type = virtual_2d_locator<D,TR>;
};

/////////////////////////////
//  HasDynamicYStepTypeConcept
/////////////////////////////

template <typename D, bool TR>
struct dynamic_y_step_type<virtual_2d_locator<D,TR>>
{
    using type = virtual_2d_locator<D,TR>;
};

/////////////////////////////
//  HasTransposedTypeConcept
/////////////////////////////

template <typename D, bool IsTransposed>
struct transposed_type<virtual_2d_locator<D,IsTransposed>>
{
    using type = virtual_2d_locator<D,1-IsTransposed>;
};

}}  // namespace boost::gil

#endif

/* virtual_locator.hpp
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
*/