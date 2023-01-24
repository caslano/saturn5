/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_1026)
#define FUSION_DEREF_IMPL_07162005_1026

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        // Unary Version
        template <>
        struct deref_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first);
                }
            };
        };

        // Binary Version
        template <>
        struct deref_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::deref<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first1, *i.first2);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
26SvtnC/JNOquDOjotlOGcNK9pI821U+sj+LPIpdURs6bg/3NMCvgk0mM27M1HVeB12ynve+hbnkqdRV4S4hsgvEv5M0JxHrdJGPWSGtInqwDfavpnA/e63b3cvnXmVN5zt7Thw46m3Bt1SGex+WMD/DIGsFQwQ1kzbg7qsu6xErEIOTfymPyNpTa6doZA1Keb/00ZBVzPFcs7wQZkjcwvXYW5yY2SnAPVB9qBUlMXtgieHy/ujMn+XpYHGa436U4XpKe6yMRSITVAT1sHO9WT4nehD7Nob77ddwFRlNXejEdtKwg7I/53qwqJGrrXXjje0ZdHJmxWQ3ZXRhJYR1ij6V/Hlr+RDgm+iWP+f/Uv+lokZ+jYwwSCJWmy7y0TlPjyrzdc3P6kkHcwyHp8/0G/ipmf2V48OI86jAe14qE6TRf2RJqCU02l8m1ntiV3/nH2wBBq+SfRsVJ7jeyK66nrfLuq6yJL0iq1w+plwSpztr4PlCth9UwW7y6xf5M0PSvHk/diPvFs4m/A06aDnPi85LLf8eNmIQ3GQ6iVpP+WAyYGoY8aW7OM/JWUw3KaXvF+WauPFkP0/50Iu1noOKhPF1jXIeo+yq63lk/ppDA42X513knzaH1fA8IE9dpT44h6eBmj8A5GgVOf8LqIA+yASjrxyfe6aFJzTARgdryZo+YZS/kK9HjbgOd1224X6wLlw/Wg6ZmR/S6URX
*/