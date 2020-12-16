/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SPLIT_INTERVAL_SET_HPP_JOFA_990223
#define BOOST_ICL_SPLIT_INTERVAL_SET_HPP_JOFA_990223

#include <boost/icl/type_traits/is_interval_splitter.hpp>
#include <boost/icl/interval_base_set.hpp>
#include <boost/icl/interval_set.hpp>

namespace boost{namespace icl
{

/** \brief implements a set as a set of intervals - on insertion 
    overlapping intervals are split */
template 
<
    typename                  DomainT, 
    ICL_COMPARE               Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC                 Alloc    = std::allocator
> 
class split_interval_set: 
    public interval_base_set<split_interval_set<DomainT,Compare,Interval,Alloc>, 
                             DomainT,Compare,Interval,Alloc>
{
public:
    typedef split_interval_set<DomainT,Compare,Interval,Alloc> type;
    typedef interval_base_set<type,DomainT,Compare,Interval,Alloc> base_type;

    typedef interval_set<DomainT,Compare,Interval,Alloc> joint_type;
    typedef type overloadable_type;
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

    enum { fineness = 3 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    split_interval_set(): base_type() {}

    /// Copy constructor
    split_interval_set(const split_interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    split_interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { this->assign(src); }

    /// Constructor for a single element
    explicit split_interval_set(const interval_type& elem): base_type() { this->add(elem); }
    /// Constructor for a single interval
    explicit split_interval_set(const domain_type& itv): base_type() { this->add(itv); }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        this->clear();
        this->_set.insert(src.begin(), src.end());
    }

    /// Assignment operator for base type
    template<class SubType>
    split_interval_set& operator =
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
    split_interval_set(split_interval_set&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    split_interval_set& operator = (split_interval_set src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }
    //==========================================================================
#   else

    /// Assignment operator
    split_interval_set& operator = (const split_interval_set& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    
private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_set<split_interval_set<DomainT,Compare,Interval,Alloc>, 
                                             DomainT,Compare,Interval,Alloc>;

    iterator handle_inserted(iterator inserted_)
    { 
        return inserted_; 
    }

    iterator add_over(const interval_type& addend, iterator last_)
    {
        iterator first_ = this->_set.lower_bound(addend);
        //BOOST_ASSERT(next(last_) == this->_set.upper_bound(inter_val));

        iterator it_ = first_;
        interval_type rest_interval = addend;

        this->add_front(rest_interval, it_);
        this->add_main (rest_interval, it_, last_);
        this->add_rear (rest_interval, it_);
        return it_;
    }

    iterator add_over(const interval_type& addend)
    {
        std::pair<iterator,iterator> overlap = this->equal_range(addend);
        iterator first_ = overlap.first,
                 end_   = overlap.second,
                 last_  = end_; --last_;

        iterator it_ = first_;
        interval_type rest_interval = addend;

        this->add_front(rest_interval, it_);
        this->add_main (rest_interval, it_, last_);
        this->add_rear (rest_interval, it_);

        return it_;
    }

} ;


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_set<icl::split_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::split_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_splitter<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_splitter<icl::split_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "sp_itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};


}} // namespace icl boost

#endif // BOOST_ICL_SPLIT_INTERVAL_SET_HPP_JOFA_990223




/* split_interval_set.hpp
PulZWcUKGpy2SwbP1lymffhe2PRz3RMuJLocdOF4hsIyqYaV0aZwJ5Ht/XAz/cm9n+W0nJvwMr+m3p36TqdUt055GutS7Tu+12THzIsBBDqhSnfOOWt53xkrOHExUpDXKMefuGY3uLC08TT6YHfa9sXPlorPbnr6CH5ZwB9PrJS9h9VgsLb6QkNLwIQgs3ntS/bkU53NgLrgNbPavGpq0SajCYG96C2R8rAwU6Wvgo3CVC1jHXg7cOrsbMoy/jPxGRaVnpFuN0vZbEWqJ6TPhm50HV+nIM22oMxa5hkPzHJQLCC4bhpakFyKuGJvW2CZcaZMmxBudYpvPLooQDXUR7pK1Nt/+t2eI2NBnzeV9FFZHm782IzN4vuBJifxXB5hRTmfm1KDVWNt5+rt8qlE8T+t12eW9Y4raRBaqmClSxhI1zWaW5ud+/n9J6/60IcOy3fenl0YT/0mFPWrmwaRUYObXzT8ai2Ss/E7l79Qh5Xe5GTxjyvSaLoU38x0RWzmhiw5nuhyqn3b4san9zH7L+2YfZ89l2ojSPeePF2QkNdj5KmfV0HHzJtllaoZ7nfPgevVhyuBLRpal8OOw+eb2RrC71Q2X2TuVXR4wRYSX1h4d7xRY+HQYeHRkeWSmVDh2Tfclx4v0WQv/sLJV+mHF35nSvNsVBbW+WxntwGfFna9MdUUhsWw95yJa5mCR82XHtXayeMYJwezMYt1/rKrSfsNT1HUHdV2ox2dpjPMX5rtY/sT9d+qtLR9Y00x/CiT5fOL9ycc9h6b4Z8L8N7IP+Rlod8OZiEXYg9bnk8oExT81uFNVurELTz7kM1KcbRwKQybfItu484VkS8h+S67uVsaipedzIgTGaOsXORPDx5Uq32/cJtFaO9yiP3hzZYPz72KeMhsC56c6jY8/kV78emRH7y/ZCJ4vTkZ9qjpi7GgarRcF4mCc1QfLnfQUJ2idALO57Rogs7ghTWvh4KpbbhIWkadgsA6r3Pr3LAjCvN3YeRs2issfGop0Oysrz+IjjQqdGfKus8wEwWQvopmwO91HCC5Lt5jwb8b2RRCixca3RWaNHPHxP1x77WAW53Vhy9axV2sWiRvYUerKPOPms/cFxm7rWlBv4lP8CaXiU+95p6+bVY4r//V96f5NjIeOPmxh3welBI8/YlX1lu61YjQlpMgNHY0bmeXrxAfd8s7sfHksMZhyaI1+cWsQ8vqw/ILlSYNY8mXEn96mX14eeQGT/EBG9HKj63nLLFPvkgQ+rAplSrGNyDSy9cd/BbRN1IRWanvz1o13dN1VO83fF+QHrsyoNcamLWtiavlU97kKXS7k6xxrbg9yafqrV596cRu9ZX0a1fYxrA1rL0l7ipFsWsuuz5X1x+iUAs17B9xsSWR6yzAwWHKnqsNj6OutdJdM3mi355Ek7K6THI7nutrzRHWQdRj/J3d6tTM5ptixTOG14XocOe1Rqezvt60GVhZk9thFVoqa4x+3dR7ZyRHk7dLiX+rSkTzOecDXC5RxVo6/bzGJNog3l7nYSqpqSDLHW7Bk2Yei3jtjl4Hn6gLP3WlFWfjm0wwjHEyLjRwYJNzmcNJLQeU/hFf1c53v/rZYEHg1bfEyzcmToe82m0wzlryk35PyKQ23fhV5Ytf273ysIXZo9EyNwPZowh6LDUlZWnZJhG6dfFYyfT8uCaLJPztkvX63qbgn6i6l6tRqwn7bONdZ3cGVvPCz4r+FiUVbcEmJJwFk6Nnv9HaCTWFuRJ/WHpVEV2EjUsv1HL2wo4Nuf/JTyvnrRRnyJ2VB06ueKjQWMoaC0/tpge88FP6YCEjWCMdH9miOdoXanulm4uz4ZpwPds17n7rPHo=
*/