/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1229)
#define FUSION_ANY_05052005_1229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion { 
    struct random_access_traversal_tag;
namespace detail
{
    template <typename First, typename Last, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_any(First const&, Last const&, F const&, mpl::true_)
    {
        return false;
    }

    template <typename First, typename Last, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    linear_any(First const& first, Last const& last, F& f, mpl::false_)
    {
        typename result_of::deref<First>::type x = *first;
        return f(x) ||
            detail::linear_any(
                fusion::next(first)
              , last
              , f
              , result_of::equal_to<typename result_of::next<First>::type, Last>());
    }

    template <typename Sequence, typename F, typename Tag>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f, Tag)
    {
        return detail::linear_any(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

    template<int N>
    struct unrolled_any
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) ||
                f(*fusion::advance_c<1>(it))||
                f(*fusion::advance_c<2>(it)) ||
                f(*fusion::advance_c<3>(it)) ||
                detail::unrolled_any<N-4>::call(fusion::advance_c<4>(it), f);
        }
    };

    template<>
    struct unrolled_any<3>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) ||
                f(*fusion::advance_c<1>(it)) ||
                f(*fusion::advance_c<2>(it));
        }
    };

    template<>
    struct unrolled_any<2>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return
                f(*it) ||
                f(*fusion::advance_c<1>(it));
        }
    };

    template<>
    struct unrolled_any<1>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const& it, F f)
        {
            return f(*it);
        }
    };

    template<>
    struct unrolled_any<0>
    {
        template <typename It, typename F>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool call(It const&, F)
        {
            return false;
        }
    };

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        return detail::unrolled_any<result_of::distance<begin, end>::type::value>::call(
            fusion::begin(seq), f);
    }
}}}

#endif


/* any.hpp
JeGagNv9LaNbXtf9omu5tLcSpA26Vhp0Veo2kHr9RZemj7ljJZ5evrS3bKStYr+ZBp2kvfkTl1LGXJ1e6Y20t/2iQ7bokIFUYP8avQ4y5Aeav4z5NnFHMuUF6Q5pPw8h7Sh/9Cw174DbzoGz0M5PtDWPmR1i+XOtqmeLjZevXegeLwmJqWsruyRW31KxVbHYKk6jg7NsLu1OTOZHWxFbmGyWbmGzTAub5RlsJuWS+DmoYogfGSMx9n4kfXAXch5lqPeWIeDx/vkmjPdq2xd97pd63YKcr4y16ao+TRrrn7cf6/XxLSVG3nbJ/4fII/S9qtlq/tLvAs07yxTvRxcTV/KNlXxHIJ34kHmd+h5/Ymp8cnH+EpxKU2lRNGt/4u546n9bmJLnXKf2ffWXF7naWEmWMc5xB7MunWPR206XXN+xFz16VLjKnuuXHkc6WNvEcb1Wj4zkmVdNTZidEVg/D8QeaedZ2yPZSg+MEUi9BGKPYxZ6dOVDtVePhAn6JuK3Hlb2uOBi5buceXRc/d5HHY16QD40WOuBRZpnDzs9Tna0tkfcHI0eUi0t0V/0enjHLOf51vaostCjuX3FTodT55uvh92Vcdyrg+t5rSXscNj9/DDaYRg7S8PMOvREh6gb9Do01wbG/K+S/EM7mevhAmUM1ecfk5GcMmVWBpXhjgSPRZpnj8sjXfrEEJhTp89mC316K+No4/rk+uNbN9vHXh9pI/hNzfr0UT7cqNenJdrI0O5uHYxtZKuFDn2VsdSgQ3PbiCZ/vQ06m/NfiZOpWs2/+dcTT0zj67uZ4/5utcj/YmXsVPNv/nXEkL9+T4Eu1uWPy1Dz947cLWwDjw7VXaxtUGWlQwvb4UrP+6Gu5rGqvzJeenVIaen7rTr3s4Xpur7PQpeByriZ6dWlJe+37PQYG2Ftk0y9HmVzC/LntcT9hZ0eByOs7VFtoUdL3F/Y6ZHUzdhOpY1o9GjJ+087PY4a9RB7RGd59WjJ+0+vHvqxMz3SXC+D0KMyyxQvt9lt453LJFamQYdjFjoMQYdasw7Nbhd2OmR2N+swNJY/c43xea9pth1+7a6LnMXG9x8WOgxDhzizDs22g1cH/bU8u4dZh+FKe9Dr0GwbuN+/KA4gff4nLPIfqbQFff7NLr8+f+81xClx+C6X/Icg7YbyZ55njlvLP7O/1dn62fC0hS5/wyBxqi4t+8xup0dlL2ubVKp6tOwzu50ebS+wtketqkfLPrP/m71zgY+iuON4MKioQEPUJDyE8AYJGN7haXgHCBB52IBoEpILCYTkzANBqY2VWqxaY8UWFTVaKlFQU7UWW61oscUWNbXUqvURrba2YosttdZa2+/e/W6zt7d7uQsB+7j99O+3XPY////Mzs7uzM78x82POgc/Eow6UhTwo3377L883bmvnNI71I8jRv0w/WjfPrubH/W9ncuj1vSjffvsAT+4MsHfSfo4l8de04/267PbysL0oaFPaPt1hlE3PAEf2q/Pzv9x7LMPSQ314SOjXpg+tE+fXfZD+uzNsp8r+0uQJKM+BNvPaKmac8uLK4wSifz7g708smCjOR5ujQ8fOl9+9OnOffttfUP9/phyOxzWb0oxiu/iKsd29XtIv9B6X0V55xcH/D42YyRu/uxx8Gct/tSb/hybMRKbP+Y9Obl/qD/r8KfZ9Kf9xkguS3YeI3nMwQcPPqSuDvjQPmMkNvtmGWQOsNnXPZlv2m+/53fLt6FgH/bZfdD9VW/60H7PbrsPZv9voHM5NJs+tM9YSWt+HBzoXBapJQE/2me8JNSP4Pfd/EGhz4peRr0w/Wj/MZPnT3fuE7/r4MsJRrth+tK+YyZufngHO5c=
*/