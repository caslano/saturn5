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
dnnjWsxeJ+c0DAwsJWXaZY7Tp8LeKB+Szv86JWOWcRvhfvGcJXJS5VZ9XH6dnE9YPCBcmGzgAZtZuFDZWN1zTtSi81n1gSs9i/Im9HoNF3oLs96QpYsUT9Lbfs/7OZGb2o/jJnec7F1wczjKujcAz2WSujFxWFbxQBdKiPVmHiUL+/6ysWtrky7pNIdeL+8Gvw2zJKgG4hcZA4th7A6/Xo5/VkKpCKoWNeTP4BllYeW6i9gKg1CGbfm64b2A9jXvA/RsdYe2aZuOsHuL7vxdmFCl68+eer2Sq/wqb7LU7/joXJTpYCQeuL5/SfGQtoFpoixzPOwuX1Bnlni4JvpAPj7UKk/xMOB1Ptf8FU2c6x7ZfhR+4QdQpsOOhd7r2cVoYlc66rSP/ixwE6+oEjyUQ9dyl1D3/AZkzEDn3jS8ETh8PBpLPSPJSzwA5mVPnOJbbE7Qzlqr8Q8rfLyGmCotjTfMvOWhP1fd84iSzwV+DbnWhKZqc0nfJYpwdfwG2wmdBaKPDDastqhL1Hq/edd+didWWnET57JV8XuB0/Xx1OEseIPSc2CTQCb+gY09qeqNMtI1gRdjH5RlCunUO7e3N190p9/F16oXoWHsfqT4rrO2qevUjT0mbQwqHmce9zm9mXH8Bku3MXgxCDrSiuQayQCKZujb1VK7zQ5tcr6/xyKMiSbJAG+U+CkE+irG+b+1vb158/q2fTntHg8C0iylDCDwYQuJK9T1D918a1VitklvsIpubbqK162H7THHIMMg2QkgZ8VL6Izk31Mcv/Zg2S1aGBQYWfrW7YHmXNAsvLyN2yJpGtC0AmMnMu8JmUfqbFfeqPQPHy8fUZr0RHFC78/HjaXfIARuhPsxiMKsLhVtnDDn3VgxfU+NVVg1kW8iTteNNFTWife+G2qOTNRkTRhEoN05GXaffB6XojvP6Sx5kzwLkNw1gvG1YnSd0iMJk21Q4OMRAkZ4OH0QXSVeqht55g38Z6KfwAvhIliHbrIdB2yRrZOMyPHAdhDWWRnnJadvi8Xs40jqOEAg9iDb0Vup6AO5gpuqKmJGmgJh5Tl4VdFumqaO8zBjtDHdzseTDOFyvf1I0YbXQAwjcneeWLPgxL5+7TB31wVu6kW1SfwkJvLOPoAaRPyzx/X6d4Efwx6c+LhJQ0l7r3Mu1nrJ7d8s103t+1BLMjbuC3uWwQNUPlHT28ObpW7XJkmT11VMtNkbjghJBhOk6yseYjyh+FnJxn/01eZmErL5CfzKOjD4eBstJ3kQz0gjD1dFHwnk8hqPh1XjeBjesPfBCZuCUZb5kRiHAL4CSRVV9SQL6GTNyuprYIT7R/xZj0MOUabi49An/Mf94mLTxDhgA0j9IMybOgwgT0G/cy6Gg+/7/ulXQEdY2EWBPtlb0solOZZxFDdZkbBx6GvvdorOguR8wYe5pNZEgAfgLCI2rEoyxYfH/R4uqbsqzVMIJ4k3/ap5hvayop0kPl6PY9oLTrebXI/0jqxo15GBYFFG3rRSQ9/9ZzV2uOYiP0taRXtyHZJ++Bblh5BWEMvLVNJeIHcR4ZIsdtNb5BqMijCu/aRR9KcWId3VHu+j9toyMXiUijx6PUSguCO8O+AYjgN1CP6ffpIaT0bNSPnrnPjODPpfHMBPoB0J4dHYmhYGxW2h3ozfot6+g6I0URv2RPe3tpdP3EcM4/R1gVt4EPihwma5ZwMrO8VtY7FOxozR+4nv1V+qPuCxAhW6dh+NC86uafbWqf0ybgj8CvdtFuOVxYw8bJ45iAs6u9+qZCQ8hvlF1Y+BBbeTvuKKHBL6KKsceavSH4K6sLnwRx7gXzTxUER+vG+VfmqwRyQJngd4RYrBv44=
*/