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