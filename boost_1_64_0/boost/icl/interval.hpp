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
zXeqAQJ8yCegx/2TyGVQdSzwF/1//zzJFvPpf3XOE5JD/Vmc5u/RekUEkr884SpSqD9V0amXKknQroeXIog/qFytOnIF3rpxSUeYph7J09Sj32IgwidfhkrxlT6LmZ/Jk5LvXzV/F0Ntker1B6Y03zCTudnUe48qxYiaNuBm8oQ6vULok8pMEspT7KUKGfUIPS61k+1lo+WjnSZYmwfJpQbNPWuuKHZd4jDvu5PReFHEq6fN7DmZ5sWeF5JiD4hMnrvvcthw6E7UkFMFV3M7NagZXHDzav0ZjX5kj19Vy/XihoJ780pkv5x33WtY/Hrzg8I5w1qmcqYN2TN/eNt3wfPzbb+Ipm9/+F7PqP7PKaNvsPEXBhE9By7/Hb9imO/Mj1MVs2vH75wiiz83ceCbrpYjm6yIHVzQq/eRjlddFpkPeN+6xZaLx8tGD7C3yvY//dazpHDL7ewpday8Bkyskyfym9B0y+FMy+uturnuv+W8OWtA3wFxH+zins5aH7cuYV5Iz84WpfzUjqfjdpqtb+3e9+yO86X+dTePic2f+Vw2pK7Fm+2t90n4/Y6vbfPZ1UpR36/v+aYzxy5st+fa5r4XbEUjYtwGZY6ZbT8vZKr35t3d0hqVHjw2s5l90tmaN3jT1zb7MWDDkBC3nFf9+vXLfbtVOfq5fouWt8c1Erwc4Te+xfENcy5/kKSbdgz4OGpkUC0nQ3buiq5lRcL+C23yAlJONFsgev6Zt8gkuWzc5fWXlnZPTXGOvWG/2nTO8nbd14tqvRU/9h5kHlXmvWde6x/Dmgje5Wfobe7o1+t00rg6gSOtx7yZtGOJhHN0Ze7QA/0net9QSu7L2YdHLwlq2HlV6uEeCesuR1TP7NRedu93I1/9hQG214s7hNQzLr78wrRk4aF3oadkMTUGN5qfcyP7it2Xu6WfG0b9fuQdlr1z/33R3D3VDxnujFx7+NiAJZ2P5PXtz7dNtd4s+ZFSECPye7mto7nkVbS3Tfef6W1nuywM4ow4W3N//82GxY8O/Ora7m4Ne9Ok7d2crHuuOXPIVFHE6citdankx+Xd+w9lxxm7DWh4gpV/LVvWtvNvuyXJZ5fb/Pj6fOWUr83dSu7VV/pYpvF+FTWNcl4fXW3j9wJftwFjW/wKGewaM/Iey29vz755SydJTjv1GNuwRNjg3uc1AVePlg+zP+GWvEEeFzlpS6s+wqL403v7LS9/sLRuWeE83+9mhaOa/RIV/Oza5/JFx+zHMQsEnK8794VOuTRt7o9ut97fedBu2JkV/uY/EkpPPD5/6zT7rV5YZvvfecOKd9i8axN+q2T2vOnTNg2csvHF0qsz04ovTim+b3dys3Mfnym7Zimn/Hj4eWpim3rv6xWOG9e4rPa0pf03RjY+OjVl+rsLFzceXrPdqrmzc2aDOgd+Oypf5NvoTzQ9u/RJqUJScO3DBqv5D8efvx+5Zseu++a/RngfG3JzzcZLScu49atlzs6xkJ+dmWnRsJmAvfHpmO8FmZ8CYk9e8Fj8w2TzuZdLx/sNvtzI/1rosKabHOvYsfpvH8jey0ppvvl+Yc+F7RNtm+6uWdZkOj9u3ap7vcYHHs4aHtP75rI+Q9nHdz/RzzBoOWrthdkJKdZFdf27yiNOOwZv77rWYnA0q3sjS4eYBZ16ml57fGLhvowVA9qwFE9HFEj2GNk8b9Qz7dWc95Y3a7duJuDv3Plt9zOnau7liT1GH+/nuCUmf+qStfOD9xil1hgtfi4d1C3IYXuBU01lSYuW1se2rBJvHHpvdWjhgDeLkra9njpw0rpX5Q0WCEXRiT0e5G09slK/vbVDWE1lZ/NeS/28rB4vmBfbSbA4oM8=
*/