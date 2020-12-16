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
OV0NY8zH8bCOB6d9b8pSvQaxu9MTrF3/VHSV1Wy+aSPt375gQtubmPNtMkIyZspB34+h4PUzeiUcQt5iX5ywNOLd5gawPPODGzUOM8LFmAn+B2SYmjPuyBxpsz8BfgP3ytwz1kx6dwTu7av4c2M+S40L4VN8Dwcsq/Cmh6ZsM/8TMwvGCpPFvzhbaw7E+ZWImNVTTLl0C37f3yGjqguvLLYRX3SnsTG4PSp+rYPJsnTcaa2CleO/iIBVxjDtdxyp7t/QZMg16qvsQtbOiwz56w5Xh7csjnqgOE9fTo+egHW7XzHqZw12DMiRM3RducErmTo77Li5WyS/21kz17W9OP9Ug7/LAuVCv1ksUPgetfR07J12Rs472IavridjeaUxtXvVKuaaF+MDp4vcVGX067hDuq/5gPvO27ntxglGJH4Wlxf2xeU3IyTfbkPCa385pkYJ75eMYEO7X2jWO0iE6GzBE31j0db1Mk6/DOHiAwO5v8EeffY6o3duH5kWNoudgmo5NVwXy3Q6S18FVzC/+pHL4ws5+Jg5o0414pp6W7w6msjT2r+Ei2p7JD7yQdHyW6xbf14sauqOtB+ubJi6mc+nDRB/p1twTN0MsXTxL5iGjhbV9oVoY7yAybbToL51sByVeo8ZZlcwdWwezqTmy1QrXezo8lzuC8iC8ryZOPFoMQcWPhVffo5Ad+1SttpogdIAJxnr04Gj/niJ8qFjedwhSbwrKqfO2j0Y2XIgG8RPsWxBIqyWL5OGzUZwftp+0XTtetY1nye8/5pSHrQR09qqY1T1fOFcUo6vBkOk277j9M/TEe3UMjilgxWutV6MwUODqFHzjNO+BtFzWi5NLV15v7iBA17kYtveBxxVHiG+LMpGxGRtuSK7Ay9Nf0Ybt1D8WnEOvdVN2N7KW544Zc3DNR0Y1f8ERvt3xfT0YH7yD2HK0wWsXXcDp5Meo2DNUHRbMZ4Jby+JNn4dUdi3nrLkAy8nZmPbjaHYkL+Sfqmz2eqpvxh6+jrvTAoWoa+H85L9LjnsiCW0fX/S62oZjbf3wPZBx+DtZiJbFu5HgvIqZrlb4s2WNUyb7oBHfwul4+3r3MzesiAzGqHqHdhhseK+PUnCx+rJjLZqyhN2L3AocxuTgibj2/RtTHs+k48sj8nbJxLR5vh92Z25GGdpL5KsljBnAJi1qozjNfPx8eUiatV0hnKlGdcrp4nOOin0e31f6B27AbUTA5A0KptdO3fGxsRPaFixiKYf/Tnadwem5qlDtbeXnKd2Arr5S6n94AX7LVsslWq80c+tVP4K9OCY5NHY+m03msfNZdDkODrNi0D5iAi01DuL6ScFVl/9DduxWzDhXSPzro9FTNeZQu/KCNoV/L8/T2ZQry/CYPwMNqQcYrN0XXw+7igdUxuRPdGO75YNxsJuz2CW6c1Bn1viZOpvaq7czo+X+uJWopP8ubgYN+e64K7TQi6rbi0NN9bCSSzm4MgmeLBhA3epvIJqkmIPqaGKh/5u4LJ9Ebyk+hBdTZNRfKClfLNZjznlFCPH2dHxpqv0bmiDnksdROe8XdDKU5Ud9Yfy6r41fD7wPXR7J8jjzwbQXNOFl4pa8qfPdo6/o48pKrPkjLDjaJWoIz54lOG7+nzRyaAASiUq3Fk7CioKn/jr8k0W3pzI8ra7Ie7c5Y7TQzh2zDKhdrKIeSlGYu7kbby0LQzn23Ri5BVDKpfFc+3LOk6eVonD1TuF8bhKWDS8FP2vHGTPR16IiGyE3eKVYpDNNtYpOKLTgQoaO/bl3Mg3CoeoKnoO+cej7b3puLwvfdWeiwy/pyx7HSjnLv3KBA9N6iR50P7rfxz/eQ0829dJ5crO6Hk=
*/