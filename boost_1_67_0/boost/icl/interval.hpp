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
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
*/