/*-----------------------------------------------------------------------------+
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_ELEMENT_ITERATOR_HPP_JOFA_091104
#define BOOST_ICL_DETAIL_ELEMENT_ITERATOR_HPP_JOFA_091104

#include <boost/mpl/if.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>
#include <boost/icl/detail/mapped_reference.hpp>

namespace boost{namespace icl
{

//------------------------------------------------------------------------------
template<class Type>
struct is_std_pair
{ 
    typedef is_std_pair<Type> type; 
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<class FirstT, class SecondT>
struct is_std_pair<std::pair<FirstT, SecondT> >
{ 
    typedef is_std_pair<std::pair<FirstT, SecondT> > type; 
    BOOST_STATIC_CONSTANT(bool, value = true);
};


//------------------------------------------------------------------------------
template<class Type>
struct first_element
{ 
    typedef Type type; 
};

template<class FirstT, class SecondT>
struct first_element<std::pair<FirstT, SecondT> >
{ 
    typedef FirstT type; 
};

//------------------------------------------------------------------------------
template <class SegmentIteratorT> class element_iterator;

template<class IteratorT>
struct is_reverse
{ 
    typedef is_reverse type; 
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<class BaseIteratorT>
struct is_reverse<std::reverse_iterator<BaseIteratorT> >
{ 
    typedef is_reverse<std::reverse_iterator<BaseIteratorT> > type; 
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<class BaseIteratorT>
struct is_reverse<icl::element_iterator<BaseIteratorT> >
{ 
    typedef is_reverse<icl::element_iterator<BaseIteratorT> > type; 
    BOOST_STATIC_CONSTANT(bool, value = is_reverse<BaseIteratorT>::value);
};

//------------------------------------------------------------------------------
template<class SegmentT>
struct elemental;

#ifdef ICL_USE_INTERVAL_TEMPLATE_TEMPLATE

    template<class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval>
    struct elemental<ICL_INTERVAL_TYPE(Interval,DomainT,Compare) >
    {
        typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) segment_type;
        typedef segment_type              interval_type;
        typedef DomainT                   type;
        typedef DomainT                   domain_type;
        typedef DomainT                   codomain_type;
        typedef DomainT                   transit_type;
    };

    template< class DomainT, class CodomainT, 
              ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval >
    struct elemental<std::pair<ICL_INTERVAL_TYPE(Interval,DomainT,Compare) const, CodomainT> >
    {
        typedef std::pair<ICL_INTERVAL_TYPE(Interval,DomainT,Compare), CodomainT> segment_type;
        typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare)                       interval_type;
        typedef std::pair<DomainT, CodomainT>                   type;
        typedef DomainT                                         domain_type;
        typedef CodomainT                                       codomain_type;
        typedef mapped_reference<DomainT, CodomainT>            transit_type;
    };

#else //ICL_USE_INTERVAL_TEMPLATE_TYPE

    template<ICL_INTERVAL(ICL_COMPARE) Interval>
    struct elemental
    {
        typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) segment_type;
        typedef segment_type                        interval_type;
        typedef typename interval_traits<interval_type>::domain_type domain_type;
        typedef domain_type                         type;
        typedef domain_type                         codomain_type;
        typedef domain_type                         transit_type;
    };

    template< class CodomainT, ICL_INTERVAL(ICL_COMPARE) Interval >
    struct elemental<std::pair<ICL_INTERVAL_TYPE(Interval,DomainT,Compare) const, CodomainT> >
    {
        typedef std::pair<ICL_INTERVAL_TYPE(Interval,DomainT,Compare), CodomainT> segment_type;
        typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare)                       interval_type;
        typedef typename interval_traits<interval_type>::domain_type domain_type;
        typedef CodomainT                                       codomain_type;
        typedef std::pair<domain_type, codomain_type>           type;
        typedef mapped_reference<domain_type, codomain_type>    transit_type;
    };

#endif //ICL_USE_INTERVAL_TEMPLATE_TEMPLATE


//------------------------------------------------------------------------------
//- struct segment_adapter
//------------------------------------------------------------------------------
template<class SegmentIteratorT, class SegmentT>
struct segment_adapter;

#ifdef ICL_USE_INTERVAL_TEMPLATE_TEMPLATE

template<class SegmentIteratorT, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval>
struct segment_adapter<SegmentIteratorT, ICL_INTERVAL_TYPE(Interval,DomainT,Compare) >
{
    typedef segment_adapter                         type;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) segment_type;
    typedef segment_type                            interval_type;
    typedef typename interval_type::difference_type domain_difference_type;
    typedef DomainT                                 domain_type;
    typedef DomainT                                 codomain_type;
    typedef domain_type                             element_type;
    typedef domain_type&                            transit_type;

    static domain_type     first (const SegmentIteratorT& leaper){ return leaper->first(); } 
    static domain_type     last  (const SegmentIteratorT& leaper){ return leaper->last();  } 
    static domain_difference_type length(const SegmentIteratorT& leaper){ return leaper->length();}

    static transit_type transient_element(domain_type& inter_pos, const SegmentIteratorT& leaper, 
                                          const domain_difference_type& sneaker)
    { 
        inter_pos = is_reverse<SegmentIteratorT>::value ? leaper->last()  - sneaker
                                                        : leaper->first() + sneaker;
        return inter_pos; 
    }
};

template < class SegmentIteratorT, class DomainT, class CodomainT, 
           ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval >
struct segment_adapter<SegmentIteratorT, std::pair<ICL_INTERVAL_TYPE(Interval,DomainT,Compare) const, CodomainT> >
{
    typedef segment_adapter                         type;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare)               interval_type;
    typedef DomainT                                 domain_type;
    typedef std::pair<DomainT, CodomainT>           element_type;
    typedef CodomainT                               codomain_type;
    typedef mapped_reference<DomainT, CodomainT>    transit_type;    
    typedef typename difference_type_of<interval_traits<interval_type> >::type 
                                                    domain_difference_type;

    static domain_type     first (const SegmentIteratorT& leaper){ return leaper->first.first(); } 
    static domain_type     last  (const SegmentIteratorT& leaper){ return leaper->first.last();  } 
    static domain_difference_type length(const SegmentIteratorT& leaper){ return leaper->first.length();}

    static transit_type transient_element(domain_type& inter_pos, const SegmentIteratorT& leaper,
                                          const domain_difference_type& sneaker)
    {
        inter_pos = is_reverse<SegmentIteratorT>::value ? leaper->first.last()  - sneaker
                                                        : leaper->first.first() + sneaker;
        return transit_type(inter_pos, leaper->second); 
    }
};

#else // ICL_USE_INTERVAL_TEMPLATE_TYPE

template<class SegmentIteratorT, ICL_INTERVAL(ICL_COMPARE) Interval>
struct segment_adapter 
{
    typedef segment_adapter                          type;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) segment_type;
    typedef segment_type                             interval_type;
    typedef typename interval_traits<interval_type>::domain_type domain_type;
    typedef domain_type                              codomain_type;
    typedef domain_type                              element_type;
    typedef domain_type&                             transit_type;
    typedef typename difference_type_of<interval_traits<interval_type> >::type 
                                                     domain_difference_type;

    static domain_type     first (const SegmentIteratorT& leaper){ return leaper->first(); } 
    static domain_type     last  (const SegmentIteratorT& leaper){ return leaper->last();  } 
    static domain_difference_type length(const SegmentIteratorT& leaper){ return icl::length(*leaper);}

    static transit_type transient_element(domain_type& inter_pos, const SegmentIteratorT& leaper, 
                                          const domain_difference_type& sneaker)
    { 
        inter_pos = is_reverse<SegmentIteratorT>::value ? icl::last(*leaper)  - sneaker
                                                        : icl::first(*leaper) + sneaker;
        return inter_pos; 
    }
};

template < class SegmentIteratorT, class CodomainT, ICL_INTERVAL(ICL_COMPARE) Interval >
struct segment_adapter<SegmentIteratorT, std::pair<ICL_INTERVAL_TYPE(Interval,DomainT,Compare) const, CodomainT> >
{
    typedef segment_adapter                                type;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare)    interval_type;
    typedef typename interval_traits<interval_type>::domain_type domain_type;
    typedef CodomainT                                      codomain_type;
    typedef std::pair<domain_type, codomain_type>          element_type;
    typedef mapped_reference<domain_type, CodomainT>       transit_type;    
    typedef typename difference_type_of<interval_traits<interval_type> >::type 
                                                           domain_difference_type;

    static domain_type     first (const SegmentIteratorT& leaper){ return leaper->first.first(); } 
    static domain_type     last  (const SegmentIteratorT& leaper){ return leaper->first.last();  } 
    static domain_difference_type length(const SegmentIteratorT& leaper){ return icl::length(leaper->first);}

    static transit_type transient_element(domain_type& inter_pos, const SegmentIteratorT& leaper,
                                          const domain_difference_type& sneaker)
    {
        inter_pos = is_reverse<SegmentIteratorT>::value ? icl::last(leaper->first)  - sneaker
                                                        : icl::first(leaper->first) + sneaker;
        return transit_type(inter_pos, leaper->second); 
    }
};

#endif // ICL_USE_INTERVAL_TEMPLATE_TEMPLATE

template <class SegmentIteratorT>
class element_iterator
  : public boost::iterator_facade<
          element_iterator<SegmentIteratorT>
        , typename elemental<typename SegmentIteratorT::value_type>::transit_type
        , boost::bidirectional_traversal_tag
        , typename elemental<typename SegmentIteratorT::value_type>::transit_type
    >
{
public:
    typedef element_iterator                                type;
    typedef SegmentIteratorT                                segment_iterator;
    typedef typename SegmentIteratorT::value_type           segment_type;
    typedef typename first_element<segment_type>::type      interval_type;
    typedef typename elemental<segment_type>::type          element_type;
    typedef typename elemental<segment_type>::domain_type   domain_type;
    typedef typename elemental<segment_type>::codomain_type codomain_type;
    typedef typename elemental<segment_type>::transit_type  transit_type;
    typedef transit_type                                    value_type;
    typedef typename difference_type_of<interval_traits<interval_type> >::type 
                                                            domain_difference_type;

private:
    typedef typename segment_adapter<segment_iterator,segment_type>::type adapt;

    struct enabler{};

public:
    element_iterator()
        : _saltator(identity_element<segment_iterator>::value())
        , _reptator(identity_element<domain_difference_type>::value()){}

    explicit element_iterator(segment_iterator jumper)
        : _saltator(jumper), _reptator(identity_element<domain_difference_type>::value()) {}

    template <class SaltatorT>
    element_iterator
        ( element_iterator<SaltatorT> const& other
        , typename enable_if<boost::is_convertible<SaltatorT*,SegmentIteratorT*>, enabler>::type = enabler())
        : _saltator(other._saltator), _reptator(other._reptator) {}

private:
    friend class boost::iterator_core_access;
    template <class> friend class element_iterator;

    template <class SaltatorT>
    bool equal(element_iterator<SaltatorT> const& other) const
    {
        return this->_saltator == other._saltator
            && this->_reptator == other._reptator;
    }

    void increment()
    { 
        if(_reptator < icl::pred(adapt::length(_saltator)))
            ++_reptator; 
        else
        {
            ++_saltator;
            _reptator = identity_element<domain_difference_type>::value();
        }
    }

    void decrement()
    { 
        if(identity_element<domain_difference_type>::value() < _reptator)
            --_reptator; 
        else
        {
            --_saltator;
            _reptator = adapt::length(_saltator);
            --_reptator;
        }
    }

    value_type dereference()const
    {
        return adapt::transient_element(_inter_pos, _saltator, _reptator);
    }

private:
    segment_iterator               _saltator;  // satltare: to jump  : the fast moving iterator
    mutable domain_difference_type _reptator;  // reptare:  to sneak : the slow moving iterator 0 based
    mutable domain_type            _inter_pos; // inter position : Position within the current segment
                                               // _saltator->first.first() <= _inter_pos <= _saltator->first.last() 
};

}} // namespace icl boost

#endif // BOOST_ICL_DETAIL_ELEMENT_ITERATOR_HPP_JOFA_091104




/* element_iterator.hpp
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
*/