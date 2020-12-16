/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DISCRETE_INTERVAL_HPP_JOFA_100403
#define BOOST_ICL_DISCRETE_INTERVAL_HPP_JOFA_100403

#include <functional> 
#include <boost/static_assert.hpp> 
#include <boost/concept/assert.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_discrete_interval.hpp>
#include <boost/icl/interval_bounds.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class discrete_interval
{
public:
    typedef discrete_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef typename bounded_value<DomainT>::type bounded_domain_type;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    discrete_interval()
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
        , _bounds(interval_bounds::right_open())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a closed singleton interval <tt>[val,val]</tt> */
    explicit discrete_interval(const DomainT& val)
        : _lwb(val), _upb(val), _bounds(interval_bounds::closed())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    discrete_interval(const DomainT& low, const DomainT& up, 
                      interval_bounds bounds = interval_bounds::right_open(),
                      discrete_interval* = 0)
        : _lwb(low), _upb(up), _bounds(bounds)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    domain_type     lower()const { return _lwb; }
    domain_type     upper()const { return _upb; }
    interval_bounds bounds()const{ return _bounds; }

    static discrete_interval open      (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::open());      }
    static discrete_interval right_open(const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::right_open());}
    static discrete_interval left_open (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::left_open()); }
    static discrete_interval closed    (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::closed());    }

private:
    domain_type     _lwb;
    domain_type     _upb;
    interval_bounds _bounds;
};

//==============================================================================
//=T discrete_interval -> concept intervals
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::discrete_interval<DomainT, Compare> >
{
    typedef interval_traits type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::discrete_interval<DomainT, Compare> interval_type;

    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }

    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); }
    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); }
};

//==============================================================================
//=T discrete_interval -> concept dynamic_interval_traits
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct dynamic_interval_traits<boost::icl::discrete_interval<DomainT,Compare> >
{
    typedef dynamic_interval_traits type;
    typedef boost::icl::discrete_interval<DomainT,Compare> interval_type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

    static interval_type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds)
    {
        return interval_type(lo, up, bounds, static_cast<interval_type*>(0) );
    }

    static interval_type construct_bounded(const bounded_value<DomainT>& lo, 
                                           const bounded_value<DomainT>& up)
    {
        return  interval_type
                (
                    lo.value(), up.value(),
                    lo.bound().left() | up.bound().right(),
                    static_cast<interval_type* >(0) 
                );
    }
};

//==============================================================================
//= Type traits
//==============================================================================
template <class DomainT, ICL_COMPARE Compare> 
struct interval_bound_type< discrete_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::dynamic);
};

template <class DomainT, ICL_COMPARE Compare> 
struct is_discrete_interval<discrete_interval<DomainT,Compare> >
{
    typedef is_discrete_interval<discrete_interval<DomainT,Compare> > type;
    BOOST_STATIC_CONSTANT(bool, value = is_discrete<DomainT>::value);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::discrete_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "dI<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT> 
struct value_size<icl::discrete_interval<DomainT> >
{
    static std::size_t apply(const icl::discrete_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* discrete_interval.hpp
gv8k8O8E/m3Bfxr4R4D/RfBfBv61wH8E+N8F/yngfxD8F4P/DPA/C/5dwN8c/AvB/wv4bwb/HPCfCf6O4F8P/OeD/1Dw54P/XvDPAn8r8N8F/gvAXwz+T8H/AviXgv9C8G8P/jXBfwj4bwP/FuA/C/yTwH8f+J8G/2LwvwH+88D/FvhHgf9n8L8G/lvAPxz8DcG/APzHgb8N+HcH/xfg7wH+CvD3B/8m4H8J/HuAfzD488DfBPwtwN8H/FuB/ynwfwL+W8H/HvjLwf88+HcA/3Pgvw78JeBfAv4fwP8Y+LuDf2fwPwr+duAfCv6zwV8P/LeD/2PwPwz+ueC/E/z7gn9P8P8I/v7g3wD8W3kjALBBAAD+38H/Efi7gH/GOAQA4K8P/k+OIwAAf48CBAB3EQCA/x4OAgDw/30UAQD4h01GAAD+lw0QAFgiADiIAAD8o68gAAB/BfjfB/9TSgQAHxEAgH88+O8G/wfgPw782eB/HvzvgX9D8O8O/jHgnwj+aeA/AvyNwD8E/DmzEACA/2Dwl8sQAIC/DfjHgf9L8C8A/+OXEQCAvz34HwR/g9cIACYgAAD/bPCvAf5C8L8F/tXA3/0YAgB3BADg/6EaAgDw/wz+ozojAOiPAAD8xeDfDPzvgL9fOAIA8I8F/2OGCADAP8oaAQD47x+PAAD8b4J/KfiPB39r8C8C/yHgH/AVAQALCfxzwL8N+NcVIQAA/zqmCAB8EQCAvyP4m6YgAAD/PrYIAEwQAIB/T/B/0wgBAPgfAv/b4J/ZGAHAQwQAhxAA+CAAAP9G4F8T/CeC/04LBAA9EQCAvxL854P/cPDXA38Z+CeB/4+JCADAvwX4vy5EAHAdAUAAAgBzBADgfwL8u4L/XvD/dhIBQBMEALcRANRGAAD+h9sgAAB/KfjPAv/n4P8T/Mt6IAAA/3bgHwr+nuB/GvyvgP8n8B90CwFAJwQAbREARCEASEUAEIsAAPwng/8N8O8I/kfBvx/4F4P/VfC3K0IAAP5WpQgAwN8b/FuCf69XCABGIQAA/9ngXw7++8DfEvyfdUUA8AIBAPhvAf8V4N/pBAIADwQACgQAPxEA3EcA0A4BAPgbgv+r4QgAGiAAAP/wQAQAZxEAPEYAAP4XwT8V/NuCvwD8++shAPiOAAD8a21HAAD+JeBvBv7XwP86+OeD/9eXCADOIwDYhQAA/BuDf/AiBABxCACsEACA/8kYBABcBADg7wv+QeC/GfxTwN8W/JeDf5N9CADA36ccAUBHBADgb3IDAQD49wD/M+DvFoIAAPwLo2umXnVpv9LzYOfleSM+XP8x5FHHkQudy8e6TwkMOnb3+ZnYwbPcVh1p4fsmbHatgO9HI4yc8pPsb9puy+izLDR94kU72dfPiWNS5tW/sqLv2X6CnTNE0pCoX6933+pv2aXn6smLc6fdWM+atO+y8ZfH8dUKt3OqF7dtOvV0J1P9w5v3G+iZT0jzml7XPzL59ou57y+cL9vxVD5ng6L5s40eox9+61DaWHlPHPyu4cAmDsfHS3Yl1FlndaDRzx5+3U5cymYvKDn0O+tc7482d9a0G1fjpOvWema9WuW84g7oPnytdUHX2o5PBi2ZeWrR26X3vcM3tf60pejlXp9RMfN5DdoYDtuTea3lA6EFP66ZyVCQ08Ogj8EQgxEGMwxsDJ2p2zGGRhjas/6f/p/+n/6f/p/+n/5DE75fwP8kUoFYLhc5ujq5Orkk9eXLsqUKSV+eQE4NXGGywImvNQ9PLhfIFEKJmJ3EE4oEiV5soZjdsiVbolRQP2mCbOpHmCHg/6157P05MVxORGB0r6hYtq8vWyDmO7CHDKHzgzg6+dQS/uY=
*/