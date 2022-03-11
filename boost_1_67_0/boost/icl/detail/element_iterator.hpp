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