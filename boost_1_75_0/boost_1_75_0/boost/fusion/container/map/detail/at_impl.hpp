/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(index());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence const>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
6jiWgtfL7erz80Cix/XPo3KOLnwJ52gyLVI5Ix4QpataYCFxmJ/4yJKpKDXk0XxphGDb+bjPYI3ho2ID8wZm1ckXbrXbPH6hQPrnAfM5lsBNh05ggsntiAmjjoyPQ0uImsQpEumTQk08nRl8Pi4QYBCi5cF0jruKprOwmel8roKms08V2f6tauYu5v75zHeVu8Y3pfv5mvLwM/Kasnk6sB+tPEK4KLuOb8kN4PUrm16uwP5xwLwGQ+5Wz/wUDm/I3fHD+3XB5N14ryLBZL5geZw1039FORs7ZH7i/pZcALXU5i5VV86I8IbLcAZ/DL9PhcDZqlk48yvX/MrCSN/c1xL47kxteouKzFcY+eMZx27ifU3v3Zp/uCcwE70MKnOBAWJsOze0CLp1VzR3fT5UHnJ/CVNVefsHHdZCD+8zhBMBxrzN44gWTzP8hqUho+Aovv9lJ2eS876Ay2VBw31q1jOHNEHik20C5+i6Q86p4iYhKvVVgpR4wPZ1eRwJ0q2cbCHjAh5xrMLDjNrrQTuYQU0FXMjtJzaGR3p6lbocOCieFen9PB0fPqenp6NHyXCgWZ4nRGRjUHyKwbm6XtRdL+sWZfzneZVch1eRZtPrtUQwHFT+VdHPIWCJYuOmczG4pF0gzm98OxUHWluUhL10AgrZlX1rQeqlgMmRA3P0rTIJtQW3q+PFWesu/RTuFePh8EIChC+6GSv7wN2V
*/