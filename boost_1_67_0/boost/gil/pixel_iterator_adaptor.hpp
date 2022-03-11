//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PIXEL_ITERATOR_ADAPTOR_HPP
#define BOOST_GIL_PIXEL_ITERATOR_ADAPTOR_HPP

#include <boost/gil/concepts.hpp>
#include <boost/gil/pixel_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <iterator>

namespace boost { namespace gil {

/// \defgroup PixelIteratorModelDerefPtr dereference_iterator_adaptor
/// \ingroup PixelIteratorModel
/// \brief An iterator that invokes a provided function object upon dereference. Models: IteratorAdaptorConcept, PixelIteratorConcept

/// \ingroup PixelIteratorModelDerefPtr PixelBasedModel
/// \brief An adaptor over an existing iterator that provides for custom filter on dereferencing the object. Models: IteratorAdaptorConcept, PixelIteratorConcept

template <typename Iterator,    // Models Iterator
          typename DFn>  // Models Returns the result of dereferencing a given iterator of type Iterator
class dereference_iterator_adaptor : public iterator_adaptor<dereference_iterator_adaptor<Iterator,DFn>,
                                                             Iterator,
                                                             typename DFn::value_type,
                                                             typename std::iterator_traits<Iterator>::iterator_category,
                                                             typename DFn::reference,
                                                             use_default> {
    DFn _deref_fn;
public:
    using parent_t = iterator_adaptor<dereference_iterator_adaptor<Iterator,DFn>,
                                    Iterator,
                                    typename DFn::value_type,
                                    typename std::iterator_traits<Iterator>::iterator_category,
                                    typename DFn::reference,
                                    use_default>;
    using reference = typename DFn::result_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using dereference_fn = DFn;

    dereference_iterator_adaptor() {}
    template <typename Iterator1>
    dereference_iterator_adaptor(const dereference_iterator_adaptor<Iterator1,DFn>& dit) : parent_t(dit.base()), _deref_fn(dit._deref_fn) {}
    dereference_iterator_adaptor(Iterator it, DFn deref_fn=DFn()) : parent_t(it), _deref_fn(deref_fn) {}
    template <typename Iterator1, typename DFn1>
    dereference_iterator_adaptor(const dereference_iterator_adaptor<Iterator1,DFn1>& it) : parent_t(it.base()), _deref_fn(it._deref_fn) {}
    /// For some reason operator[] provided by iterator_facade returns a custom class that is convertible to reference
    /// We require our own reference because it is registered in iterator_traits
    reference operator[](difference_type d) const { return *(*this+d);}

    // although iterator_adaptor defines these, the default implementation computes distance and compares for zero.
    // it is often faster to just apply the relation operator to the base
    bool    operator> (const dereference_iterator_adaptor& p) const { return this->base_reference()> p.base_reference(); }
    bool    operator< (const dereference_iterator_adaptor& p) const { return this->base_reference()< p.base_reference(); }
    bool    operator>=(const dereference_iterator_adaptor& p) const { return this->base_reference()>=p.base_reference(); }
    bool    operator<=(const dereference_iterator_adaptor& p) const { return this->base_reference()<=p.base_reference(); }
    bool    operator==(const dereference_iterator_adaptor& p) const { return this->base_reference()==p.base_reference(); }
    bool    operator!=(const dereference_iterator_adaptor& p) const { return this->base_reference()!=p.base_reference(); }

    Iterator& base()              { return this->base_reference(); }
    const Iterator& base() const  { return this->base_reference(); }
    const DFn& deref_fn() const { return _deref_fn; }
private:
    template <typename Iterator1, typename DFn1>
    friend class dereference_iterator_adaptor;
    friend class boost::iterator_core_access;

    reference dereference() const { return _deref_fn(*(this->base_reference())); }
};

template <typename I, typename DFn>
struct const_iterator_type<dereference_iterator_adaptor<I,DFn> > {
    using type = dereference_iterator_adaptor<typename const_iterator_type<I>::type,typename DFn::const_t>;
};

template <typename I, typename DFn>
struct iterator_is_mutable<dereference_iterator_adaptor<I, DFn>>
    : std::integral_constant<bool, DFn::is_mutable>
{};


template <typename I, typename DFn>
struct is_iterator_adaptor<dereference_iterator_adaptor<I, DFn>> : std::true_type {};

template <typename I, typename DFn>
struct iterator_adaptor_get_base<dereference_iterator_adaptor<I, DFn>>
{
    using type = I;
};

template <typename I, typename DFn, typename NewBaseIterator>
struct iterator_adaptor_rebind<dereference_iterator_adaptor<I,DFn>,NewBaseIterator> {
    using type = dereference_iterator_adaptor<NewBaseIterator,DFn>;
};

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename I, typename DFn>
struct color_space_type<dereference_iterator_adaptor<I,DFn> > : public color_space_type<typename DFn::value_type> {};

template <typename I, typename DFn>
struct channel_mapping_type<dereference_iterator_adaptor<I,DFn> > : public channel_mapping_type<typename DFn::value_type> {};

template <typename I, typename DFn>
struct is_planar<dereference_iterator_adaptor<I,DFn> > : public is_planar<typename DFn::value_type> {};

template <typename I, typename DFn>
struct channel_type<dereference_iterator_adaptor<I,DFn> > : public channel_type<typename DFn::value_type> {};


/////////////////////////////
//  MemoryBasedIteratorConcept
/////////////////////////////

template <typename Iterator, typename DFn>
struct byte_to_memunit<dereference_iterator_adaptor<Iterator,DFn> > : public byte_to_memunit<Iterator> {};

template <typename Iterator, typename DFn>
inline typename std::iterator_traits<Iterator>::difference_type
memunit_step(const dereference_iterator_adaptor<Iterator,DFn>& p) {
    return memunit_step(p.base());
}

template <typename Iterator, typename DFn>
inline typename std::iterator_traits<Iterator>::difference_type
memunit_distance(const dereference_iterator_adaptor<Iterator,DFn>& p1,
              const dereference_iterator_adaptor<Iterator,DFn>& p2) {
    return memunit_distance(p1.base(),p2.base());
}

template <typename Iterator, typename DFn>
inline void memunit_advance(dereference_iterator_adaptor<Iterator,DFn>& p,
                         typename std::iterator_traits<Iterator>::difference_type diff) {
    memunit_advance(p.base(), diff);
}

template <typename Iterator, typename DFn>
inline dereference_iterator_adaptor<Iterator,DFn>
memunit_advanced(const dereference_iterator_adaptor<Iterator,DFn>& p,
              typename std::iterator_traits<Iterator>::difference_type diff) {
    return dereference_iterator_adaptor<Iterator,DFn>(memunit_advanced(p.base(), diff), p.deref_fn());
}


template <typename Iterator, typename DFn>
inline
typename std::iterator_traits<dereference_iterator_adaptor<Iterator,DFn> >::reference
memunit_advanced_ref(const dereference_iterator_adaptor<Iterator,DFn>& p,
                  typename std::iterator_traits<Iterator>::difference_type diff) {
    return *memunit_advanced(p, diff);
}

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Iterator, typename DFn>
struct dynamic_x_step_type<dereference_iterator_adaptor<Iterator,DFn> > {
    using type = dereference_iterator_adaptor<typename dynamic_x_step_type<Iterator>::type,DFn>;
};

/// \brief Returns the type (and creates an instance) of an iterator that invokes the given dereference adaptor upon dereferencing
/// \ingroup PixelIteratorModelDerefPtr
template <typename Iterator, typename Deref>
struct iterator_add_deref {
    BOOST_GIL_CLASS_REQUIRE(Deref, boost::gil, PixelDereferenceAdaptorConcept)

    using type = dereference_iterator_adaptor<Iterator, Deref>;

    static type make(const Iterator& it, const Deref& d) { return type(it,d); }
};

/// \ingroup PixelIteratorModelDerefPtr
/// \brief For dereference iterator adaptors, compose the new function object after the old one
template <typename Iterator, typename PREV_DEREF, typename Deref>
struct iterator_add_deref<dereference_iterator_adaptor<Iterator, PREV_DEREF>,Deref> {
//    BOOST_GIL_CLASS_REQUIRE(Deref, boost::gil, PixelDereferenceAdaptorConcept)

    using type = dereference_iterator_adaptor<Iterator, deref_compose<Deref,PREV_DEREF>>;

    static type make(const dereference_iterator_adaptor<Iterator, PREV_DEREF>& it, const Deref& d) {
        return type(it.base(),deref_compose<Deref,PREV_DEREF>(d,it.deref_fn()));
    }
};

}}  // namespace boost::gil

#endif

/* pixel_iterator_adaptor.hpp
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
*/