//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_STEP_ITERATOR_HPP
#define BOOST_GIL_STEP_ITERATOR_HPP

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/pixel_iterator.hpp>
#include <boost/gil/pixel_iterator_adaptor.hpp>
#include <boost/gil/utilities.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace boost { namespace gil {

/// \defgroup PixelIteratorModelStepPtr step iterators
/// \ingroup PixelIteratorModel
/// \brief Iterators that allow for specifying the step between two adjacent values

namespace detail {

/// \ingroup PixelIteratorModelStepPtr
/// \brief An adaptor over an existing iterator that changes the step unit
///
/// (i.e. distance(it,it+1)) by a given predicate. Instead of calling base's
/// operators ++, --, +=, -=, etc. the adaptor is using the passed policy object SFn
/// for advancing and for computing the distance between iterators.

template <typename Derived,  // type of the derived class
          typename Iterator, // Models Iterator
          typename SFn>      // A policy object that can compute the distance between two iterators of type Iterator
                             // and can advance an iterator of type Iterator a given number of Iterator's units
class step_iterator_adaptor : public iterator_adaptor<Derived, Iterator, use_default, use_default, use_default, typename SFn::difference_type>
{
public:
    using parent_t = iterator_adaptor<Derived, Iterator, use_default, use_default, use_default, typename SFn::difference_type>;
    using base_difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using difference_type = typename SFn::difference_type;
    using reference = typename std::iterator_traits<Iterator>::reference;

    step_iterator_adaptor() {}
    step_iterator_adaptor(const Iterator& it, SFn step_fn=SFn()) : parent_t(it), _step_fn(step_fn) {}

    difference_type step() const { return _step_fn.step(); }

protected:
    SFn _step_fn;
private:
    friend class boost::iterator_core_access;

    void increment() { _step_fn.advance(this->base_reference(),1); }
    void decrement() { _step_fn.advance(this->base_reference(),-1); }
    void advance(base_difference_type d) { _step_fn.advance(this->base_reference(),d); }
    difference_type distance_to(const step_iterator_adaptor& it) const { return _step_fn.difference(this->base_reference(),it.base_reference()); }
};

// although iterator_adaptor defines these, the default implementation computes distance and compares for zero.
// it is often faster to just apply the relation operator to the base
template <typename D,typename Iterator,typename SFn> inline
bool operator>(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()> p2.base() : p1.base()< p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator<(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()< p2.base() : p1.base()> p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator>=(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()>=p2.base() : p1.base()<=p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator<=(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.step()>0 ? p1.base()<=p2.base() : p1.base()>=p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator==(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.base()==p2.base();
}

template <typename D,typename Iterator,typename SFn> inline
bool operator!=(const step_iterator_adaptor<D,Iterator,SFn>& p1, const step_iterator_adaptor<D,Iterator,SFn>& p2) {
    return p1.base()!=p2.base();
}

} // namespace detail

////////////////////////////////////////////////////////////////////////////////////////
///                 MEMORY-BASED STEP ITERATOR
////////////////////////////////////////////////////////////////////////////////////////

/// \class memory_based_step_iterator
/// \ingroup PixelIteratorModelStepPtr PixelBasedModel
/// \brief Iterator with dynamically specified step in memory units (bytes or bits). Models StepIteratorConcept, IteratorAdaptorConcept, MemoryBasedIteratorConcept, PixelIteratorConcept, HasDynamicXStepTypeConcept
///
/// A refinement of step_iterator_adaptor that uses a dynamic parameter for the step
/// which is specified in memory units, such as bytes or bits
///
/// Pixel step iterators are used to provide iteration over non-adjacent pixels.
/// Common use is a vertical traversal, where the step is the row stride.
///
/// Another application is as a sub-channel view. For example, a red intensity image over
/// interleaved RGB data would use a step iterator adaptor with step sizeof(channel_t)*3
/// In the latter example the step size could be fixed at compile time for efficiency.
/// Compile-time fixed step can be implemented by providing a step function object that takes the step as a template
////////////////////////////////////////////////////////////////////////////////////////

/// \ingroup PixelIteratorModelStepPtr
/// \brief function object that returns the memory unit distance between two iterators and advances a given iterator a given number of mem units (bytes or bits)
template <typename Iterator>
struct memunit_step_fn {
    using difference_type = std::ptrdiff_t;

    memunit_step_fn(difference_type step=memunit_step(Iterator())) : _step(step) {}

    difference_type difference(const Iterator& it1, const Iterator& it2) const { return memunit_distance(it1,it2)/_step; }
    void            advance(Iterator& it, difference_type d)             const { memunit_advance(it,d*_step); }
    difference_type step()                                               const { return _step; }

    void            set_step(std::ptrdiff_t step) { _step=step; }
private:
    BOOST_GIL_CLASS_REQUIRE(Iterator, boost::gil, MemoryBasedIteratorConcept)
    difference_type _step;
};

template <typename Iterator>
class memory_based_step_iterator : public detail::step_iterator_adaptor<memory_based_step_iterator<Iterator>,
                                                                            Iterator,
                                                                            memunit_step_fn<Iterator>>
{
    BOOST_GIL_CLASS_REQUIRE(Iterator, boost::gil, MemoryBasedIteratorConcept)
public:
    using parent_t = detail::step_iterator_adaptor<memory_based_step_iterator<Iterator>,
                                          Iterator,
                                          memunit_step_fn<Iterator>>;
    using reference = typename parent_t::reference;
    using difference_type = typename parent_t::difference_type;
    using x_iterator = Iterator;

    memory_based_step_iterator() : parent_t(Iterator()) {}
    memory_based_step_iterator(Iterator it, std::ptrdiff_t memunit_step) : parent_t(it, memunit_step_fn<Iterator>(memunit_step)) {}
    template <typename I2>
    memory_based_step_iterator(const memory_based_step_iterator<I2>& it)
        : parent_t(it.base(), memunit_step_fn<Iterator>(it.step())) {}

    /// For some reason operator[] provided by iterator_adaptor returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { return *(*this+d); }

    void set_step(std::ptrdiff_t memunit_step) { this->_step_fn.set_step(memunit_step); }

    x_iterator& base()              { return parent_t::base_reference(); }
    x_iterator const& base() const  { return parent_t::base_reference(); }
};

template <typename Iterator>
struct const_iterator_type<memory_based_step_iterator<Iterator>> {
    using type = memory_based_step_iterator<typename const_iterator_type<Iterator>::type>;
};

template <typename Iterator>
struct iterator_is_mutable<memory_based_step_iterator<Iterator>> : public iterator_is_mutable<Iterator> {};


/////////////////////////////
//  IteratorAdaptorConcept
/////////////////////////////

template <typename Iterator>
struct is_iterator_adaptor<memory_based_step_iterator<Iterator>> : std::true_type {};

template <typename Iterator>
struct iterator_adaptor_get_base<memory_based_step_iterator<Iterator>>
{
    using type = Iterator;
};

template <typename Iterator, typename NewBaseIterator>
struct iterator_adaptor_rebind<memory_based_step_iterator<Iterator>, NewBaseIterator>
{
    using type = memory_based_step_iterator<NewBaseIterator>;
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename Iterator>
struct color_space_type<memory_based_step_iterator<Iterator>> : public color_space_type<Iterator> {};

template <typename Iterator>
struct channel_mapping_type<memory_based_step_iterator<Iterator>> : public channel_mapping_type<Iterator> {};

template <typename Iterator>
struct is_planar<memory_based_step_iterator<Iterator>> : public is_planar<Iterator> {};

template <typename Iterator>
struct channel_type<memory_based_step_iterator<Iterator>> : public channel_type<Iterator> {};

/////////////////////////////
//  MemoryBasedIteratorConcept
/////////////////////////////
template <typename Iterator>
struct byte_to_memunit<memory_based_step_iterator<Iterator>> : public byte_to_memunit<Iterator> {};

template <typename Iterator>
inline std::ptrdiff_t memunit_step(const memory_based_step_iterator<Iterator>& p) { return p.step(); }

template <typename Iterator>
inline std::ptrdiff_t memunit_distance(const memory_based_step_iterator<Iterator>& p1,
                                    const memory_based_step_iterator<Iterator>& p2) {
    return memunit_distance(p1.base(),p2.base());
}

template <typename Iterator>
inline void memunit_advance(memory_based_step_iterator<Iterator>& p,
                         std::ptrdiff_t diff) {
    memunit_advance(p.base(), diff);
}

template <typename Iterator>
inline memory_based_step_iterator<Iterator>
memunit_advanced(const memory_based_step_iterator<Iterator>& p,
              std::ptrdiff_t diff) {
    return memory_based_step_iterator<Iterator>(memunit_advanced(p.base(), diff),p.step());
}

template <typename Iterator>
inline typename std::iterator_traits<Iterator>::reference
memunit_advanced_ref(const memory_based_step_iterator<Iterator>& p,
                  std::ptrdiff_t diff) {
    return memunit_advanced_ref(p.base(), diff);
}

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Iterator>
struct dynamic_x_step_type<memory_based_step_iterator<Iterator>> {
    using type = memory_based_step_iterator<Iterator>;
};

// For step iterators, pass the function object to the base
template <typename Iterator, typename Deref>
struct iterator_add_deref<memory_based_step_iterator<Iterator>,Deref> {
    BOOST_GIL_CLASS_REQUIRE(Deref, boost::gil, PixelDereferenceAdaptorConcept)

    using type = memory_based_step_iterator<typename iterator_add_deref<Iterator, Deref>::type>;

    static type make(const memory_based_step_iterator<Iterator>& it, const Deref& d) { return type(iterator_add_deref<Iterator, Deref>::make(it.base(),d),it.step()); }
};

////////////////////////////////////////////////////////////////////////////////////////
/// make_step_iterator
////////////////////////////////////////////////////////////////////////////////////////

template <typename I> typename dynamic_x_step_type<I>::type make_step_iterator(const I& it, std::ptrdiff_t step);

namespace detail {

// if the iterator is a plain base iterator (non-adaptor), wraps it in memory_based_step_iterator
template <typename I>
auto make_step_iterator_impl(I const& it, std::ptrdiff_t step, std::false_type)
    -> typename dynamic_x_step_type<I>::type
{
    return memory_based_step_iterator<I>(it, step);
}

// If the iterator is compound, put the step in its base
template <typename I>
auto make_step_iterator_impl(I const& it, std::ptrdiff_t step, std::true_type)
    -> typename dynamic_x_step_type<I>::type
{
    return make_step_iterator(it.base(), step);
}

// If the iterator is memory_based_step_iterator, change the step
template <typename BaseIt>
auto make_step_iterator_impl(
    memory_based_step_iterator<BaseIt> const& it,
    std::ptrdiff_t step,
    std::true_type)
    -> memory_based_step_iterator<BaseIt>
{
    return memory_based_step_iterator<BaseIt>(it.base(), step);
}

} // namespace detail

/// \brief Constructs a step iterator from a base iterator and a step.
///
/// To construct a step iterator from a given iterator Iterator and a given step, if Iterator does not
/// already have a dynamic step, we wrap it in a memory_based_step_iterator. Otherwise we
/// do a compile-time traversal of the chain of iterator adaptors to locate the step iterator
/// and then set it step to the new one.
///
/// The step iterator of Iterator is not always memory_based_step_iterator<Iterator>. For example, Iterator may
/// already be a memory_based_step_iterator, in which case it will be inefficient to stack them;
/// we can obtain the same result by multiplying their steps. Note that for Iterator to be a
/// step iterator it does not necessarily have to have the form memory_based_step_iterator<J>.
/// The step iterator can be wrapped inside another iterator. Also, it may not have the
/// type memory_based_step_iterator, but it could be a user-provided type.
template <typename I>  // Models MemoryBasedIteratorConcept, HasDynamicXStepTypeConcept
typename dynamic_x_step_type<I>::type make_step_iterator(const I& it, std::ptrdiff_t step) {
    return detail::make_step_iterator_impl(it, step, typename is_iterator_adaptor<I>::type());
}

}}  // namespace boost::gil

#endif

/* step_iterator.hpp
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
*/