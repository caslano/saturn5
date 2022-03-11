//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_LOCATOR_HPP
#define BOOST_GIL_LOCATOR_HPP

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/pixel_iterator.hpp>
#include <boost/gil/point.hpp>

#include <boost/assert.hpp>

#include <cstddef>

namespace boost { namespace gil {

/// Pixel 2D locator

//forward declarations
template <typename P> std::ptrdiff_t memunit_step(const P*);
template <typename P> P* memunit_advanced(const P* p, std::ptrdiff_t diff);
template <typename P> P& memunit_advanced_ref(P* p, std::ptrdiff_t diff);
template <typename Iterator, typename D> struct iterator_add_deref;
template <typename T> class point;
namespace detail {
    // helper class specialized for each axis of pixel_2d_locator
    template <std::size_t D, typename Loc>  class locator_axis;
}

template <typename T> struct channel_type;
template <typename T> struct color_space_type;
template <typename T> struct channel_mapping_type;
template <typename T> struct is_planar;
template <typename T> struct num_channels;

/// Base template for types that model HasTransposedTypeConcept.
/// The type of a locator or a view that has X and Y swapped.
/// By default it is the same.
template <typename LocatorOrView>
struct transposed_type
{
    using type = LocatorOrView;
};

/// \class pixel_2d_locator_base
/// \brief base class for models of PixelLocatorConcept
/// \ingroup PixelLocatorModel PixelBasedModel
///
/// Pixel locator is similar to a pixel iterator, but allows for 2D navigation of pixels within an image view.
/// It has a 2D difference_type and supports random access operations like:
/// \code
///     difference_type offset2(2,3);
///     locator+=offset2;
///     locator[offset2]=my_pixel;
/// \endcode
///
/// In addition, each coordinate acts as a random-access iterator that can be modified separately:
/// "++locator.x()" or "locator.y()+=10" thereby moving the locator horizontally or vertically.
///
/// It is called a locator because it doesn't implement the complete interface of a random access iterator.
/// For example, increment and decrement operations don't make sense (no way to specify dimension).
/// Also 2D difference between two locators cannot be computed without knowledge of the X position within the image.
///
/// This base class provides most of the methods and type aliases needed to create a model of a locator. GIL provides two
/// locator models as subclasses of \p pixel_2d_locator_base. A memory-based locator, \p memory_based_2d_locator and a virtual
/// locator, \p virtual_2d_locator.
/// The minimum functionality a subclass must provide is this:
/// \code
/// class my_locator : public pixel_2d_locator_base<my_locator, ..., ...> {  // supply the types for x-iterator and y-iterator
///        using const_t = ...;                      // read-only locator
///
///        template <typename Deref> struct add_deref {
///            using type = ...;                     // locator that invokes the Deref dereference object upon pixel access
///            static type make(const my_locator& loc, const Deref& d);
///        };
///
///        my_locator();
///        my_locator(const my_locator& pl);
///
///        // constructors with dynamic step in y (and x). Only valid for locators with dynamic steps
///        my_locator(const my_locator& loc, coord_t y_step);
///        my_locator(const my_locator& loc, coord_t x_step, coord_t y_step, bool transpose);
///
///        bool              operator==(const my_locator& p) const;
///
///        // return _references_ to horizontal/vertical iterators. Advancing them moves this locator
///        x_iterator&       x();
///        y_iterator&       y();
///        x_iterator const& x() const;
///        y_iterator const& y() const;
///
///        // return the vertical distance to another locator. Some models need the horizontal distance to compute it
///        y_coord_t         y_distance_to(const my_locator& loc2, x_coord_t xDiff) const;
///
///        // return true iff incrementing an x-iterator located at the last column will position it at the first
///        // column of the next row. Some models need the image width to determine that.
///        bool              is_1d_traversable(x_coord_t width) const;
/// };
/// \endcode
///
/// Models may choose to override some of the functions in the base class with more efficient versions.
///

template <typename Loc, typename XIterator, typename YIterator>    // The concrete subclass, the X-iterator and the Y-iterator
class pixel_2d_locator_base
{
public:
    using x_iterator = XIterator;
    using y_iterator = YIterator;

    // aliasesrequired by ConstRandomAccessNDLocatorConcept
    static const std::size_t num_dimensions=2;
    using value_type = typename std::iterator_traits<x_iterator>::value_type;
    using reference = typename std::iterator_traits<x_iterator>::reference;    // result of dereferencing
    using coord_t = typename std::iterator_traits<x_iterator>::difference_type;      // 1D difference type (same for all dimensions)
    using difference_type = point<coord_t>; // result of operator-(locator,locator)
    using point_t = difference_type;
    template <std::size_t D> struct axis
    {
        using coord_t = typename detail::locator_axis<D,Loc>::coord_t;
        using iterator = typename detail::locator_axis<D,Loc>::iterator;
    };

// aliases required by ConstRandomAccess2DLocatorConcept
    using x_coord_t = typename point_t::template axis<0>::coord_t;
    using y_coord_t = typename point_t::template axis<1>::coord_t;

    bool              operator!=(const Loc& p)          const { return !(concrete()==p); }

    x_iterator        x_at(x_coord_t dx, y_coord_t dy)  const { Loc tmp=concrete(); tmp+=point_t(dx,dy); return tmp.x(); }
    x_iterator        x_at(const difference_type& d)    const { Loc tmp=concrete(); tmp+=d;              return tmp.x(); }
    y_iterator        y_at(x_coord_t dx, y_coord_t dy)  const { Loc tmp=concrete(); tmp+=point_t(dx,dy); return tmp.y(); }
    y_iterator        y_at(const difference_type& d)    const { Loc tmp=concrete(); tmp+=d;              return tmp.y(); }
    Loc               xy_at(x_coord_t dx, y_coord_t dy) const { Loc tmp=concrete(); tmp+=point_t(dx,dy); return tmp; }
    Loc               xy_at(const difference_type& d)   const { Loc tmp=concrete(); tmp+=d;              return tmp; }

    template <std::size_t D> typename axis<D>::iterator&       axis_iterator()                       { return detail::locator_axis<D,Loc>()(concrete()); }
    template <std::size_t D> typename axis<D>::iterator const& axis_iterator()                 const { return detail::locator_axis<D,Loc>()(concrete()); }
    template <std::size_t D> typename axis<D>::iterator        axis_iterator(const point_t& p) const { return detail::locator_axis<D,Loc>()(concrete(),p); }

    reference         operator()(x_coord_t dx, y_coord_t dy) const { return *x_at(dx,dy); }
    reference         operator[](const difference_type& d)   const { return *x_at(d.x,d.y); }

    reference         operator*()                            const { return *concrete().x(); }

    Loc&              operator+=(const difference_type& d)         { concrete().x()+=d.x; concrete().y()+=d.y; return concrete(); }
    Loc&              operator-=(const difference_type& d)         { concrete().x()-=d.x; concrete().y()-=d.y; return concrete(); }

    Loc               operator+(const difference_type& d)    const { return xy_at(d); }
    Loc               operator-(const difference_type& d)    const { return xy_at(-d); }

    // Some locators can cache 2D coordinates for faster subsequent access. By default there is no caching
    using cached_location_t = difference_type;
    cached_location_t cache_location(const difference_type& d)  const { return d; }
    cached_location_t cache_location(x_coord_t dx, y_coord_t dy)const { return difference_type(dx,dy); }

private:
    Loc&              concrete()       { return (Loc&)*this; }
    const Loc&        concrete() const { return (const Loc&)*this; }

    template <typename X> friend class pixel_2d_locator;
};

// helper classes for each axis of pixel_2d_locator_base
namespace detail {
    template <typename Loc>
    class locator_axis<0,Loc> {
        using point_t = typename Loc::point_t;
    public:
        using coord_t = typename point_t::template axis<0>::coord_t;
        using iterator = typename Loc::x_iterator;

        inline iterator&        operator()(      Loc& loc)                   const { return loc.x(); }
        inline iterator  const& operator()(const Loc& loc)                   const { return loc.x(); }
        inline iterator         operator()(      Loc& loc, const point_t& d) const { return loc.x_at(d); }
        inline iterator         operator()(const Loc& loc, const point_t& d) const { return loc.x_at(d); }
    };

    template <typename Loc>
    class locator_axis<1,Loc> {
        using point_t = typename Loc::point_t;
    public:
        using coord_t = typename point_t::template axis<1>::coord_t;
        using iterator = typename Loc::y_iterator;

        inline iterator&        operator()(      Loc& loc)               const { return loc.y(); }
        inline iterator const&  operator()(const Loc& loc)               const { return loc.y(); }
        inline iterator     operator()(      Loc& loc, const point_t& d) const { return loc.y_at(d); }
        inline iterator     operator()(const Loc& loc, const point_t& d) const { return loc.y_at(d); }
    };
}

template <typename Loc, typename XIt, typename YIt>
struct channel_type<pixel_2d_locator_base<Loc,XIt,YIt> > : public channel_type<XIt> {};

template <typename Loc, typename XIt, typename YIt>
struct color_space_type<pixel_2d_locator_base<Loc,XIt,YIt> > : public color_space_type<XIt> {};

template <typename Loc, typename XIt, typename YIt>
struct channel_mapping_type<pixel_2d_locator_base<Loc,XIt,YIt> > : public channel_mapping_type<XIt> {};

template <typename Loc, typename XIt, typename YIt>
struct is_planar<pixel_2d_locator_base<Loc,XIt,YIt> > : public is_planar<XIt> {};

/// \class memory_based_2d_locator
/// \brief Memory-based pixel locator. Models: PixelLocatorConcept,HasDynamicXStepTypeConcept,HasDynamicYStepTypeConcept,HasTransposedTypeConcept
/// \ingroup PixelLocatorModel PixelBasedModel
///
/// The class takes a step iterator as a parameter. The step iterator provides navigation along the vertical axis
/// while its base iterator provides horizontal navigation.
///
/// Each instantiation is optimal in terms of size and efficiency.
/// For example, xy locator over interleaved rgb image results in a step iterator consisting of
/// one std::ptrdiff_t for the row size and one native pointer (8 bytes total). ++locator.x() resolves to pointer
/// increment. At the other extreme, a 2D navigation of the even pixels of a planar CMYK image results in a step
/// iterator consisting of one std::ptrdiff_t for the doubled row size, and one step iterator consisting of
/// one std::ptrdiff_t for the horizontal step of two and a CMYK planar_pixel_iterator consisting of 4 pointers (24 bytes).
/// In this case ++locator.x() results in four native pointer additions.
///
/// Note also that \p memory_based_2d_locator does not require that its element type be a pixel. It could be
/// instantiated with an iterator whose \p value_type models only \p Regular. In this case the locator
/// models the weaker RandomAccess2DLocatorConcept, and does not model PixelBasedConcept.
/// Many generic algorithms don't require the elements to be pixels.
////////////////////////////////////////////////////////////////////////////////////////

template <typename StepIterator>
class memory_based_2d_locator : public pixel_2d_locator_base<memory_based_2d_locator<StepIterator>, typename iterator_adaptor_get_base<StepIterator>::type, StepIterator> {
    using this_t = memory_based_2d_locator<StepIterator>;
    BOOST_GIL_CLASS_REQUIRE(StepIterator, boost::gil, StepIteratorConcept)
public:
    using parent_t = pixel_2d_locator_base<memory_based_2d_locator<StepIterator>, typename iterator_adaptor_get_base<StepIterator>::type, StepIterator>;
    using const_t = memory_based_2d_locator<typename const_iterator_type<StepIterator>::type>; // same as this type, but over const values

    using coord_t = typename parent_t::coord_t;
    using x_coord_t = typename parent_t::x_coord_t;
    using y_coord_t = typename parent_t::y_coord_t;
    using x_iterator = typename parent_t::x_iterator;
    using y_iterator = typename parent_t::y_iterator;
    using difference_type = typename parent_t::difference_type;
    using reference = typename parent_t::reference;

    template <typename Deref> struct add_deref
    {
        using type = memory_based_2d_locator<typename iterator_add_deref<StepIterator,Deref>::type>;
        static type make(const memory_based_2d_locator<StepIterator>& loc, const Deref& nderef) {
            return type(iterator_add_deref<StepIterator,Deref>::make(loc.y(),nderef));
        }
    };

    memory_based_2d_locator() {}
    memory_based_2d_locator(const StepIterator& yit) : _p(yit) {}
    template <typename SI> memory_based_2d_locator(const memory_based_2d_locator<SI>& loc, coord_t y_step) : _p(loc.x(), loc.row_size()*y_step) {}
    template <typename SI> memory_based_2d_locator(const memory_based_2d_locator<SI>& loc, coord_t x_step, coord_t y_step, bool transpose=false)
        : _p(make_step_iterator(loc.x(),(transpose ? loc.row_size() : loc.pixel_size())*x_step),
                                        (transpose ? loc.pixel_size() : loc.row_size())*y_step ) {}

    memory_based_2d_locator(x_iterator xit, std::ptrdiff_t row_bytes) : _p(xit,row_bytes) {}
    template <typename X> memory_based_2d_locator(const memory_based_2d_locator<X>& pl) : _p(pl._p) {}
    memory_based_2d_locator(const memory_based_2d_locator& pl) : _p(pl._p) {}
    memory_based_2d_locator& operator=(memory_based_2d_locator const& other) = default;

    bool                  operator==(const this_t& p)  const { return _p==p._p; }

    x_iterator const&     x()                          const { return _p.base(); }
    y_iterator const&     y()                          const { return _p; }
    x_iterator&           x()                                { return _p.base(); }
    y_iterator&           y()                                { return _p; }

    // These are faster versions of functions already provided in the superclass
    x_iterator x_at      (x_coord_t dx, y_coord_t dy)  const { return memunit_advanced(x(), offset(dx,dy)); }
    x_iterator x_at      (const difference_type& d)    const { return memunit_advanced(x(), offset(d.x,d.y)); }
    this_t     xy_at     (x_coord_t dx, y_coord_t dy)  const { return this_t(x_at( dx , dy ), row_size()); }
    this_t     xy_at     (const difference_type& d)    const { return this_t(x_at( d.x, d.y), row_size()); }
    reference  operator()(x_coord_t dx, y_coord_t dy)  const { return memunit_advanced_ref(x(),offset(dx,dy)); }
    reference  operator[](const difference_type& d)    const { return memunit_advanced_ref(x(),offset(d.x,d.y)); }
    this_t&    operator+=(const difference_type& d)          { memunit_advance(x(),offset(d.x,d.y)); return *this; }
    this_t&    operator-=(const difference_type& d)          { memunit_advance(x(),offset(-d.x,-d.y)); return *this; }

    // Memory-based locators can have 1D caching of 2D relative coordinates
    using cached_location_t = std::ptrdiff_t; // type used to store relative location (to allow for more efficient repeated access)
    cached_location_t cache_location(const difference_type& d)  const { return offset(d.x,d.y); }
    cached_location_t cache_location(x_coord_t dx, y_coord_t dy)const { return offset(dx,dy); }
    reference         operator[](const cached_location_t& loc)  const { return memunit_advanced_ref(x(),loc); }

    // Only make sense for memory-based locators
    std::ptrdiff_t         row_size()                           const { return memunit_step(y()); }    // distance in mem units (bytes or bits) between adjacent rows
    std::ptrdiff_t         pixel_size()                         const { return memunit_step(x()); }    // distance in mem units (bytes or bits) between adjacent pixels on the same row

    bool                   is_1d_traversable(x_coord_t width)   const { return row_size()-pixel_size()*width==0; }   // is there no gap at the end of each row?

    // Returns the vertical distance (it2.y-it1.y) between two x_iterators given the difference of their x positions
    std::ptrdiff_t y_distance_to(this_t const& p2, x_coord_t xDiff) const
    {
        std::ptrdiff_t rowDiff = memunit_distance(x(), p2.x()) - pixel_size() * xDiff;
        BOOST_ASSERT((rowDiff % row_size()) == 0);
        return rowDiff / row_size();
    }

private:
    template <typename X> friend class memory_based_2d_locator;
    std::ptrdiff_t offset(x_coord_t x, y_coord_t y)        const { return y*row_size() + x*pixel_size(); }
    StepIterator _p;
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename SI>
struct color_space_type<memory_based_2d_locator<SI> > : public color_space_type<typename memory_based_2d_locator<SI>::parent_t> {
};

template <typename SI>
struct channel_mapping_type<memory_based_2d_locator<SI> > : public channel_mapping_type<typename memory_based_2d_locator<SI>::parent_t> {
};

template <typename SI>
struct is_planar<memory_based_2d_locator<SI> > : public is_planar<typename memory_based_2d_locator<SI>::parent_t> {
};

template <typename SI>
struct channel_type<memory_based_2d_locator<SI> > : public channel_type<typename memory_based_2d_locator<SI>::parent_t> {
};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

// Take the base iterator of SI (which is typically a step iterator) and change it to have a step in x
template <typename SI>
struct dynamic_x_step_type<memory_based_2d_locator<SI> > {
private:
    using base_iterator_t = typename iterator_adaptor_get_base<SI>::type;
    using base_iterator_step_t = typename dynamic_x_step_type<base_iterator_t>::type;
    using dynamic_step_base_t = typename iterator_adaptor_rebind<SI, base_iterator_step_t>::type;
public:
    using type = memory_based_2d_locator<dynamic_step_base_t>;
};

/////////////////////////////
//  HasDynamicYStepTypeConcept
/////////////////////////////

template <typename SI>
struct dynamic_y_step_type<memory_based_2d_locator<SI> > {
    using type = memory_based_2d_locator<SI>;
};
} }  // namespace boost::gil

#endif

/* locator.hpp
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
*/