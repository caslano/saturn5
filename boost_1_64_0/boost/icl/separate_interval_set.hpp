/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SEPARATE_INTERVAL_SET_HPP_JOFA_080608
#define BOOST_ICL_SEPARATE_INTERVAL_SET_HPP_JOFA_080608

#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_interval_separator.hpp>
#include <boost/icl/interval_base_set.hpp>
#include <boost/icl/interval_set.hpp>

namespace boost{namespace icl
{

/** \brief Implements a set as a set of intervals - leaving adjoining intervals separate */
template 
<
    typename                         DomainT, 
    ICL_COMPARE                      Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC                        Alloc    = std::allocator
> 
class separate_interval_set: 
    public interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>,
                             DomainT,Compare,Interval,Alloc>
{
public:
    typedef separate_interval_set<DomainT,Compare,Interval,Alloc> type;

    typedef interval_base_set<type,DomainT,Compare,Interval,Alloc> base_type;

    typedef type overloadable_type;
    typedef type key_object_type;

    typedef interval_set<DomainT,Compare,Interval,Alloc> joint_type;

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

    enum { fineness = 2 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    separate_interval_set(): base_type() {}
    /// Copy constructor
    separate_interval_set(const separate_interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    separate_interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
    }

    /// Constructor for a single element
    explicit separate_interval_set(const domain_type& elem): base_type() { this->add(elem); }
    /// Constructor for a single interval
    explicit separate_interval_set(const interval_type& itv): base_type() { this->add(itv); }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        this->clear();
        this->_set.insert(src.begin(), src.end());
    }

    /// Assignment operator for base type
    template<class SubType>
    separate_interval_set& operator =
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
    separate_interval_set(separate_interval_set&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    separate_interval_set& operator = (separate_interval_set src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }
    //==========================================================================
#   else

    /// Assignment operator
    separate_interval_set& operator = (const separate_interval_set& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>, 
                                                DomainT,Compare,Interval,Alloc>;

    iterator handle_inserted(iterator inserted_)
    { 
        return inserted_; 
    }

    iterator add_over(const interval_type& addend, iterator last_)
    {
        return segmental::join_under(*this, addend, last_);
    }

    iterator add_over(const interval_type& addend)
    {
        return segmental::join_under(*this, addend);
    }

} ;



//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_set<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_separator<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_separator<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "se_itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};

}} // namespace icl boost

#endif



/* separate_interval_set.hpp
+4tr7Df9/PZHrJWvGRgRet6mYvmY7EgjMr7dv6MRHFDMQs9rn5H+IEBhKrbRXl47lZBR9POD9k5G2jHuJydP5qfxi6XL68LeeQYsWFHLKvZgu7Xv5XhtZ8ikk3vIKG126SGi6F813/UzSCBmZNDPP7vh3Ttj5SsrKerea3rszti+npAeqqWO98PRbSO/RMiRTuWDmd5Q/WWciQ2+X6YknCY09hr/TLm1MZztwVuVhXt58XZCGdk6waeTpWAk9/m2XMJGRU9A/eH7tik/6bGP5RcIxN58Tfru0TufO/4LGSz9jYVZ6ZNsNrx932lf4l8yuK+nURR2uA8859M99omYSFaRXHS1iotz88g8YNXvJJkOQL98wSakNmJsurynyU96x+yG1i+Yzt8zvN1m0fmw10yi5dKXDyHeo4NM3JYGfqYMp33u7IkG8tFfFtNZmX1uzmuS/v7KsJBCAw3PKb8Mwh0sjkr3wBS3yZmsyC3b+gS+QGKjQmG2YweHbQaxk2zrw0hGp0j5aI6cqU+XrrxVsVIN/TG5qHw1FJ3biDK/LRQpIh9uIetLd5RG5/g6MDhX0Ixt8Sd/lcBk36ifKiUHjqfPcH7ITZvmuNWaN9SomTT7K63hdvP7FivKZwNdsQqqswvZxwNJLaumamQ3mUx0++YC+TY1Hbcd8DSyqZ9pXfs81mx4p2qeRvtegs27ALF+e55xrN7V+r6BPAMJ32qCfNfSm88qBYc7PUQTub8Y4WicMzZ1WPMzl11gfERiVJlmRjnBnE0b+pHdsm4xX8nXY6yGmY1Hy0i43/EWbWK/282wX3RgV0Yq6h8/p7HJLHveS1ZAi8tHmGM2+SC0m3eibqmrg1DjZP0shTzTjBCnZqU4l1km14L0uicPnX3wLRy1rSAL+g6sS1uJP+fwqeHn85MQxZtQBH5/eDuZPVvOwHy10LXzVp7gyXtpCu6snE/1ng6nfJnw0z+pmSpKdt8dsWkt3n1m7sJ+ydfDKJ/tx8f52Xnit4y+1ZvvxZQDKZT31/lnWfG9V5S6f34pZh0Y+mgvetfEcP2h9p77uMGveN/wk2fLOuzyaa4eVByM+JD1uAVt6E7c+mh0xDtO9UEg2v27Nd/+1U3soVT+FKIDmdaylZl8PKXHHYQsY7WcfP6+nVsTnx+UGw900oTjm7S3NC12PTNV3iloONjgfZty0Z+58n67f5jKp9GGS7QR8+T0fG5LYhx5yydlHbWfTK0UXyHJDyc1Ypyf8fV2x2STk6b3eGuoXJ6n0UZnCQd/Lh/IJ6+Jb8tcsSfJv9rR0CEjrE7dwHlvY/juqVvFrtY8N9Y4hMj7Gfwv2hsQHH6LG+/mWjbaidMl9VHVjfWwCtDsKbBkVzShClp+cSNy0EQk4PsUyy/CvUVslfrnzxCaBL6ieyg0eq2j/POy9s0XFX6NV8uKz7GENIiYH5RXbVbkGEXLKFD+cLc5daYxrEw1LPepuZG0/DOWgFMGdWKGVx0TR2Q9++y86Scn8TZ+aWsrmmvy4H5T80Ncl5CAr6ss8lKtG1GZhgdszRIxK6e7iBdPfEyu3ZjNvCzXwRAZ8+7Dy+bv5U3L7w7X1ah6F1+enlTHCz0Xp4hbshkQJT49RHw/LtOL+Hydl/npwdmZV0acqhKMBaV1U/4TBxHsllkX3Rz9W15JanF/SVVMSNoYbJA0+mn9xwnTEY2+/1q7VpxUjs5P2AHUKic+U/ULCv63zpHqPG7eeygY6pcZuajyIy+3yr+rhq6lwLw1U4dflcDSWLLx25u9E6kfUTUMb/ptHqfNecg2S5Sl3OgYr5pviTJLeeqnRduZlG3Pg3Wd83po+wOHth6SVtnar7KnbcXDCAI=
*/