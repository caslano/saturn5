/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONTINUOUS_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_CONTINUOUS_INTERVAL_HPP_JOFA_100327

#include <functional> 
#include <boost/static_assert.hpp> 
#include <boost/concept/assert.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/concept/container.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_continuous_interval.hpp>
#include <boost/icl/interval_bounds.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class continuous_interval
{
public:
    typedef continuous_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef typename bounded_value<DomainT>::type bounded_domain_type;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    continuous_interval()
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
        , _bounds(interval_bounds::right_open())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value)); 
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a closed singleton interval <tt>[val,val]</tt> */
    explicit continuous_interval(const DomainT& val)
        : _lwb(val), _upb(val), _bounds(interval_bounds::closed())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    continuous_interval(const DomainT& low, const DomainT& up, 
                      interval_bounds bounds = interval_bounds::right_open(),
                      continuous_interval* = 0)
        : _lwb(low), _upb(up), _bounds(bounds)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value));
    }

    domain_type     lower()const { return _lwb; }
    domain_type     upper()const { return _upb; }
    interval_bounds bounds()const{ return _bounds; }

    static continuous_interval open     (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::open());      }
    static continuous_interval right_open(const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::right_open());}
    static continuous_interval left_open (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::left_open()); }
    static continuous_interval closed   (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::closed());    }

private:
    domain_type     _lwb;
    domain_type     _upb;
    interval_bounds _bounds;
};


//==============================================================================
//=T continuous_interval -> concept interval
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::continuous_interval<DomainT, Compare> >
{
    typedef interval_traits type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::continuous_interval<DomainT, Compare> interval_type;

    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }

    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); }
    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); }
};


//==============================================================================
//=T continuous_interval -> concept dynamic_interval
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct dynamic_interval_traits<boost::icl::continuous_interval<DomainT,Compare> >
{
    typedef dynamic_interval_traits type;
    typedef boost::icl::continuous_interval<DomainT,Compare> interval_type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

    static interval_type construct(const domain_type lo, const domain_type up, interval_bounds bounds)
    {
        return icl::continuous_interval<DomainT,Compare>(lo, up, bounds,
            static_cast<icl::continuous_interval<DomainT,Compare>* >(0) );
    }

    static interval_type construct_bounded(const bounded_value<DomainT>& lo, 
                                           const bounded_value<DomainT>& up)
    {
        return  icl::continuous_interval<DomainT,Compare>
                (
                    lo.value(), up.value(),
                    lo.bound().left() | up.bound().right(),
                    static_cast<icl::continuous_interval<DomainT,Compare>* >(0) 
                );
    }
};

//==============================================================================
//= Type traits
//==============================================================================
template <class DomainT, ICL_COMPARE Compare> 
struct interval_bound_type< continuous_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::dynamic);
};

template <class DomainT, ICL_COMPARE Compare> 
struct is_continuous_interval<continuous_interval<DomainT,Compare> >
{
    typedef is_continuous_interval<continuous_interval<DomainT,Compare> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::continuous_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "cI<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT> 
struct value_size<icl::continuous_interval<DomainT> >
{
    static std::size_t apply(const icl::continuous_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* continuous_interval.hpp
Ha9Kttezu+A9f0PR6qFWZmL+otLBe71Lama1PPfRqpdYb9eCV2sWRI4SiGc/Hfa0fJ3RhX3NnpZavr258Nme8+0lXa/UXPLi2pAtDpu3rXB1bdGptcuslScOJS3z6LAvQrHq9MifW4qn3be8sbpd13mG777ceuVfJ+rccOfP0xtMvhaeEb7lbWBs+Lqz9wznPH5UcDGv0bjUsEKbtoeHdxd0MXzRf3E/j0l6csXY707+tX70bpK8PfpSyYx2PcyemwdfS5/Eu75gkEl+hykWX3uN9zF/+abV2vMep3i7Xj9p/MBna/CgXvcuLeokfx+Xfd7C6mCHk/IX577E9Fn3i2sh8b03piQoa8SHzaf9jqXsbutu68ntvPyI7GiT+iZ2D/dNDPWx959du3yg3pqOd7ebGC16vOPGtMM9Enm5ZwZLd7pdVfQVhQT0LCwG/yjwjwH/o+A/B/zPgP878F8P/jPBPw78P4P/dPC3A/+f4H8d/HPAfyr4h4J/MvjPA/8H4K8P/vXAfzn4nwD/Z+A/G/xfgv8t8HcE/8vg7wD+QeCfCv5Z4J8G/nfAfyf4NwD/JPDfAf5W4D8S/AeAPwf874N/Lvg3Bv9Z4B8P/tbgPxb8d4F/C/B/CP49wb81+NcAfwPwXwD+K8H/PfhvA/894N8X/NuA/wzwLwP/fPA/B/5Xwd8G/CeA/2LwXwr+buCvBP+O4L8O/KuDf3fw/wb+vuC/Cfy7gH8B+FcDfwn4l4O/LfjPBf+z4J8J/vvBfxz4e4J/CfgHg/9z8D/FQgL/UeAfAv4bwD8C/H+Afw/wbwr+rcA/Efybgf9F8PcC/63gbwr+l8A/D/wjwX8Z+AvBvz74G4P/E/APBP8m4F8L/DeC/27wLwL/0eAfBv57wf8X+C8B/33gfxz83cE/A/xvg38K+PPB/zT4m4F/Z/Bng/9Q8P8K/nXBPx38u4H/B/B/Bf7F4C8C//ng/x38m4P/MfBvCP43wP8t+J8E/8Pg/xv824P/BfC3B/+W4L8C/B+Df23wXwj+CeB/BPxLwb8/+H8C/wPgPwT814L/dvD3Bv/V4C8G/8HgXxP8P4K/HvivAX8B+A8DfyPwfwr+N8H/PPhfAf9r4L8Z/F3B3wX8D4F/B/BfBf5bwN8S/LuC/xfwrwP+zuA/GfzDwT8W/O+B/yPwbwT+heA/HPwNwb8f+MvB3wn8e4N/NPi3A39z8J8E/oPAfwr4jwf/N+DvAf6vwd8H/HuBfyfwzwb/g+D/Avz7gL8F+I8B/xHg7wf+bcGfC/4y8DcB/4ng7w/+A8H/LvgvAv9p4M8Dfyn4K8A/APxXg78A/FeAf3/wTwN/DvjHg78B+H8H/3TwzwD/MPC/Dv5nwD8I/JeDf2/wbwT+dcD/EPgrwb8M/OeC/zfw54L/IvAfBP69wH8U+DcDfyH4F4H/ePDPBn8/8B8I/pHgvxH8N4C/F/h3BX9X8G8H/sPBPxP8N4H/UvBvA/4p4P8L/EXg/xX8L4O/PvhPBf/14G8P/kfAfzD4G4H/WPBfCf6p4D8S/BuD/w7wfw/+D8H/I/gfAP8E8P8N/jHgHwf+D8D/Jfi/Av+34L8E/M3AfwL4Vwf/auC/H/wng38/8L8C/pbg/wP8n4N/IPjngX8A+E8E/z7g/wb8jcHfFPybspDAfwz4vwZ/KfjLwL8c/D3B/yr4dwT/m+C/Cvxjwd8J/JPB/xn4zwH/6eB/HPzZ4N8N/BuC/x7wbw3+98G/AfjXBv+T4L8G/NeCvzX41wD/O+A/APxbgv8n8PcG/2Hg7wD+J8D/J/i/A//b4D8a/JuDf13wtwV/X/B3A/988HcGfxfwjwb/R+BfH/x3g38I+Cc=
*/