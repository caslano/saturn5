/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_HPP_JOFA_101014
#define BOOST_ICL_INTERVAL_HPP_JOFA_101014


#include <boost/icl/type_traits/interval_type_default.hpp>


namespace boost{ namespace icl
{

    template <class IntervalT, bool IsDiscrete, bound_type PretendedBounds, bound_type RepresentedBounds> 
    struct static_interval;

    template <class DomainT, ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)> 
    struct interval
    {
        typedef typename interval_type_default<DomainT,Compare>::type interval_type;
        typedef interval_type type;

#ifdef BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS

        static inline interval_type open(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type                // if the domain_type is discrete ...
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_open // 'pretended' bounds will be transformed to
                , interval_bound_type<interval_type>::value // the represented bounds
                >
                ::construct(low, up); 
        }

        static inline interval_type left_open(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_left_open
                , interval_bound_type<interval_type>::value
                >
                ::construct(low, up); 
        }

        static inline interval_type right_open(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_right_open
                , interval_bound_type<interval_type>::value
                >
                ::construct(low, up); 
        }

        static inline interval_type closed(const DomainT& low, const DomainT& up)
        {
            return 
                static_interval
                < interval_type
                , is_discrete<typename interval_traits<interval_type>::domain_type>::value
                , interval_bounds::static_closed
                , interval_bound_type<interval_type>::value
                >
                ::construct(low, up); 
        }

        static inline interval_type construct(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up); }

#else // ICL_USE_DYNAMIC_INTERVAL_BORDER_DEFAULTS
        static inline interval_type right_open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::right_open()); }

        static inline interval_type left_open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::left_open()); }

        static inline interval_type open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::open()); }

        static inline interval_type closed(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::closed()); }

        static inline interval_type construct(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up); }

#endif 
    };

    template <class IntervalT, bound_type PretendedBounds, bound_type RepresentedBounds> 
    struct static_interval<IntervalT, true, PretendedBounds, RepresentedBounds>
    {// is_discrete<domain_type<IntervalT>>
        typedef typename interval_traits<IntervalT>::domain_type domain_type;

        static inline IntervalT construct(const domain_type& low, const domain_type& up)
        {
            return icl::construct<IntervalT>(
                  shift_lower(interval_bounds(PretendedBounds), interval_bounds(RepresentedBounds), low)
                , shift_upper(interval_bounds(PretendedBounds), interval_bounds(RepresentedBounds), up )
                ); 
        }
    };

    template <class IntervalT, bound_type PretendedBounds, bound_type RepresentedBounds> 
    struct static_interval<IntervalT, false, PretendedBounds, RepresentedBounds>
    {// !is_discrete<domain_type<IntervalT>>
        typedef typename interval_traits<IntervalT>::domain_type domain_type;

        static inline IntervalT construct(const domain_type& low, const domain_type& up)
        {
            BOOST_STATIC_ASSERT((is_discrete<domain_type>::value || PretendedBounds==RepresentedBounds));
            // For domain_types that are not discrete, e.g. interval<float> 
            // one of the following must hold: If you call
            // interval<T>::right_open(x,y) then interval<T>::type must be static_right_open
            // interval<T>::left_open(x,y)  then interval<T>::type must be static_left_open
            // interval<T>::open(x,y)       then interval<T>::type must be static_open
            // interval<T>::closed(x,y)     then interval<T>::type must be static_closed
            // Conversion between 'PretendedBounds' and 'RepresentedBounds' is only possible
            // for discrete domain_types.
            return icl::construct<IntervalT>(low, up);
        }
    };

}} // namespace boost icl

#endif // BOOST_ICL_INTERVAL_HPP_JOFA_101014


/* interval.hpp
/eHSpui2/eEp2R/SWzt6GliN/RlgTXs/wgF29u8Po7Pz5SE7Tqbi0P6Wo7rYxXvX7b0W7a0r0mhH/q5HkVzs988Yh+S4eD9XckOcX/ocbppf7iY/dR92Hacb6Du5GXJfdFX3AcCGigOK/aGf7T2q3h9WBNT7w6VxzfeHpKNk1nYOum1/2LY/bNsfslb3h2dpKE3MO2604erjJSi1Dh58dSf+yc3A/v376/vTGe9w6KG/mi78GMxLwP1txdzCuYU8FBSMx53vhMFVCVNqMQWVgPHrKoor1havWVu0tmhN0YqiFUOmlVYldupECbD8tVgARuN/TLBm7prCFcUPVJUmJE6ZMsSQgPmDRZOCCygF7pDXFK1ZU7imsHhIaVVVQoKV/grRwOCaSbihXshTFK+lMjDFkNLSqqu5gAODWAFuiKmMirULpARrC4dUDZ7Ug+LjcHc+aQEVEFxAe3DeiqIVxVPmFvYv4fEVxcX1wWAlbcAXUAFYBMqyorBwvE6KxwIWBoMLqQ0VFQuoEZiieE1hoZbHF+O2/aFK/jnRQtrGozYwyZqilYXj+2F8JVZQUb+Qdu1BKoVk5aIU8QLiuGyTSug4elBKtBBbQvv9tcXj27P6Sv5goGTSvEn1kyhMmDBhIIb+UmBxddhsFB7/r+UqWlO8ds3aFWv6y12N+RcGeREVC6kXUMnFa7CnBobig1x2LIOLx1tGpYTyT6qj
*/