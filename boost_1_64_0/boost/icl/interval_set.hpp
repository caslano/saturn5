/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_SET_HPP_JOFA_990223
#define BOOST_ICL_INTERVAL_SET_HPP_JOFA_990223

#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_interval_joiner.hpp>
#include <boost/icl/interval_base_set.hpp>

namespace boost{namespace icl
{

/** \brief Implements a set as a set of intervals - merging adjoining intervals */
template 
<
    typename    DomainT, 
    ICL_COMPARE Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC   Alloc    = std::allocator
> 
class interval_set: 
    public interval_base_set<interval_set<DomainT,Compare,Interval,Alloc>,
                             DomainT,Compare,Interval,Alloc>
{
public:

    typedef interval_set<DomainT,Compare,Interval,Alloc> type;

    /// The base_type of this class
    typedef interval_base_set<type,DomainT,Compare,Interval,Alloc> base_type;

    typedef type overloadable_type;

    typedef type joint_type;

    typedef type key_object_type;

    /// The domain type of the set
    typedef DomainT   domain_type;
    /// The codomaintype is the same as domain_type
    typedef DomainT   codomain_type;

    /// The element type of the set
    typedef DomainT   element_type;
    /// The interval type of the set
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    /// The segment type of the set
    typedef interval_type   segment_type;

    /// Comparison functor for domain values
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    /// Comparison functor for intervals
    typedef exclusive_less_than<interval_type> interval_compare;

    /// Comparison functor for keys
    typedef exclusive_less_than<interval_type> key_compare;

    /// The allocator type of the set
    typedef Alloc<interval_type> allocator_type;

    /// allocator type of the corresponding element set
    typedef Alloc<DomainT> domain_allocator_type;

    /// The corresponding atomized type representing this interval container of elements
    typedef typename base_type::atomized_type atomized_type;

    /// Container type for the implementation 
    typedef typename base_type::ImplSetT ImplSetT;

    /// key type of the implementing container
    typedef typename ImplSetT::key_type   key_type;
    /// data type of the implementing container
    typedef typename ImplSetT::value_type data_type;
    /// value type of the implementing container
    typedef typename ImplSetT::value_type value_type;

    /// iterator for iteration over intervals
    typedef typename ImplSetT::iterator iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplSetT::const_iterator const_iterator;

    enum { fineness = 1 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    interval_set(): base_type() {}

    /// Copy constructor
    interval_set(const interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    explicit interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
    }

    /// Constructor for a single element
    explicit interval_set(const domain_type& value): base_type() 
    { this->add(interval_type(value)); }

    /// Constructor for a single interval
    explicit interval_set(const interval_type& itv): base_type() 
    { 
        this->add(itv); 
    }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        typedef interval_base_set<SubType,DomainT,Compare,Interval,Alloc> base_set_type;
        this->clear();
        // Has to be implemented via add. there might be touching borders to be joined
        iterator prior_ = this->_set.end();
        ICL_const_FORALL(typename base_set_type, it_, src) 
            prior_ = this->add(prior_, *it_);
    }

    /// Assignment operator for base type
    template<class SubType>
    interval_set& operator =
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
        return *this; 
    }

#   ifndef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    //==========================================================================
    //= Move semantics
    //==========================================================================

    /// Move constructor
    interval_set(interval_set&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    interval_set& operator = (interval_set src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }

    //==========================================================================
#   else
    /// Assignment operator
    interval_set& operator = (const interval_set& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_set <interval_set<DomainT,Compare,Interval,Alloc>, 
                                        DomainT,Compare,Interval,Alloc>;

    iterator handle_inserted(iterator it_)
    {
        return segmental::join_neighbours(*this, it_); 
    }

    iterator add_over(const interval_type& addend, iterator last_)
    {
        iterator joined_ = segmental::join_under(*this, addend, last_);
        return segmental::join_neighbours(*this, joined_);
    }

    iterator add_over(const interval_type& addend)
    {
        iterator joined_ = segmental::join_under(*this, addend);
        return segmental::join_neighbours(*this, joined_);
    }

} ;


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_set<icl::interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_joiner<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_joiner<icl::interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};


//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};

}} // namespace icl boost

#endif



/* interval_set.hpp
Xp/pTctGrss8Ob52WQu9wKnvkm1F2rAwIFXr0Nqh7dikn4Pv3ugOzmsbTO+lDuwmMazTiJXfvPhR71qfOta/TF0++lhS9ZBJkXIfzyRqmcWL6277lqq1fbGbZjGw+cnZjbFLvrvwvKJlVcLN9wv2Eq5p/aKNYbjf3dGksfRK0NHvd1rULefzrzx7D5WnRg1fX9e59vox5J6VZ5duIQZtLEtpWHrgPCKpIL7k5XvyR5GsT7sff1VFXfzeJ1/1Tf7cKrd2S8LxXXnbN5y9vW7JNxNZH5KGC/r2GXkOmTl9MxAbXJ63z6b2zGUb9+Xem1nUpNi813szGyzImtK+T7kMda2H7xG6LhKGOl8m2YQHxNKi+FeVAxWPf1Fn4lJxGC1BdiYGP02sp95/n/h5UT2nn1RDRF67vUzv8+3Pfb8/p7tqSWyy48Xy51tO9qc3X9TkhWCV7rn2ht3gqR6uCCt8vnvR0s+TLH6yKzlc67Uv0v6Jwo75lmFLlxrtqfzqYu9Fu1PrHb9La4jp8vww1USx9qDtme/z75UtHpFUbdsTcI32yn/dhtpE56GyO9rnPnD3j+sfyx4Ma40wKdixvOZjr9wQ+f3sjfsU0iMFz0RfRxMsaDfqlU2+/i7QrWf05TVftetPXpDvIEQrXa79arji6RXyarnnv+7K81ML/bKtetJ+9amTzP5jW/2Uf1hHWeix+pOGL4Za+dyVXu8nX5vf5n79hcLjPX/ABwvr533HFC/1UD216UKLntL2xqUGY2RrvSup1o/uhFSLLMsZhBZfRtSVR3mByJ6r1Vcrq7bxsFoe839Uet1OjxfpdxF/+aQto2rplc1fih5MatQc9jF2HK8La+rpDYld/3Q5pmJvtjA6y0KJmX5mt/Mnyf0hNoPXP7m6vn5H0LHvv9bvT0nyUHr08F7ws+6nvh83mo59jgwlIiT0vuVHVKt3nX+hp7gnKHrXptp46zNl7hHyGuvszvpUkL55b9Bz0nHe2aQldV1UXiFJ3S75Gf599hAnq+zowvk1g6tWL0kyJi2ix+cblju2j4+EvD4hV0RKLNdKOVyWd6hA0Wl9nvvJ3IOEo85WL3Yh/h/+5vDXP2tDwtfP+awNiooLnHqJr/PiAOeFCxa7LljsPnXPdH1onLRTEwSZadKeBQHSXgnSiTLTw98uKjtN2s9FNi0xJgTW92beoCizkNDgN+NrpOuZ+oIQHRmTCPkmLZbMm5136kW1cFsVMTcOWbwTl/64fyYOBZ8dQu+c4JjZ+eAlRtI8YAhVESC9HRoVuO7NetzdFrs4z64Z4m/eZBwSHxgA/QOl/Udkpknf0xwqrYa365lnFjn1+kzZuHQDZNMiE9f9SVp89Lr1oQGxiYGwij8/LSAwLu43psfG/Ubam7pZF78mfHWCdHx2k8xgJAqS5qa9SZJNC5C+Nmr61Y+/OT0pOg62WnaadD/IpsVPvctQZj3SZhUf+ltpsAsCgqARB6+RWf90maBOwoMj5qRLi/0mHhNuFhQ1PQ57WDqcPiAQb8an/gsLnYlL1zndJuNDp4sVPzNvYnxikHQ56L9kxl6XwIahOWKmDxYUNBz6pgTPtivotRWVGPnOe8Gk7+59502gEIJhDLq1JIVPva1z/XQ3rkS4hT5bVmjM8D4q6SsNpfHZ11rM7b803bCnXq0Ih0NCeDB7JnM48gLfvo8Pji9pH6+40JDE4OkeSW/7X828vuvdNGm9zInP1o20pxg7HhpjHEyejr/T+0eaxn5nn0IcmnDi9ENp3z7jWPr6q3ff/gbTZrujSQ+y6bSpeSKnXtIVngAHoPRdku+kS18oGR0XCDf+1wfGhU/1UYr//edMqEE4Z8qGSZk=
*/