/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0721)
#define FUSION_DISTANCE_09172005_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/distance.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct distance_impl
        {
            // default implementation
            template <typename First, typename Last>
            struct apply : distance_detail::linear_distance<First, Last> 
            {};
        };

        template <>
        struct distance_impl<iterator_facade_tag>
        {
            template <typename First, typename Last>
            struct apply : First::template distance<First, Last> {};
        };

        template <>
        struct distance_impl<boost_array_iterator_tag>;

        template <>
        struct distance_impl<mpl_iterator_tag>;

        template <>
        struct distance_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename First, typename Last>
        struct distance
          : extension::distance_impl<typename detail::tag_of<First>::type>::
                template apply<First, Last>
        {
            typedef typename extension::distance_impl<typename detail::tag_of<First>::type>:: 
            template apply<First, Last>::type distance_application;
            BOOST_STATIC_CONSTANT(int, value = distance_application::value);
        };
    }
        
    template <typename First, typename Last>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::distance<First, Last>::type
    distance(First const& a, Last const& b)
    {
        return result_of::distance<First, Last>::call(a,b);
    }
}}

#endif

/* distance.hpp
1GHE6Xfcq4/5b2qvI38391la0l+/oO+hzAuRr9lLh21WHuZ3AVfy/bjj0zuE/G7Hz4AeNzweUviy/BFryfFNw0GneUGf2RL358XSMKZPm9vP6POTFwyaH7ugzz6Ki+W6PZ5q2qzq8yk+P09o/wLBHGvscUyNHo33q/tWe/6wWDSXVBiSepu9nMhSZ0Ti7fLBARV6xN9hvORoMmWhJFeUGJF6p1xzSJMZN3+X8VBhSOLd6pCnxYy5shjIUWNE/D36I0udCUvvte4oMmLufXLDMafMz8K+xxFXRf4p0iNu/NU3mw82C+b9Deb29fp8uTqkXyFeai9zr/2vjl4i3hd5HrzYPFN8jv5J+Vp3wilTjp+pjWfo60Bd+7A12qGgx5TY131uiDV2yFKkyd6TtEmftbRcPFZ8tBkRfpy+WGaL8mOM9Rrn8zVNHK+0Gee1fP76yV5nn3J+fwOnjdvrnypj5u4gL+RpE1oV9/N9z6rcoUif1v3O6++KzTU5GkxZvJM8U6RL7M7qkKPOhMU1bZGnQ+wu1jBpSvRo316MXvsX7+o8ZXok7yZvHNFk/hLn8d6INtfVo8qY1N3VI0+DKUd/PW8wfw/j45g2oXvqmzRVRqQ2zDVZaozI3vb8Qepe4qZAn/C93csBdUbE72OMVzqf9y2M//G+tiubTLj5plzbP+JAWWfC0n21yRFtovez1jigxIDk/cXMIXVmzG0ZH1kq9Ig9QB+38Ty5tT5v6v5Lup+5S2njTaFgV1lhyuKltUmRPsm4OKgyo3nr8wY3v4xr9/Q3psoqM5YuKzaa9H9gDV1ODjiiQzQhd5zQIXZ580+GOlPmriDfDN4cCg5ue94g+yOfl/Y4fEXrlgPqzFhMiovmifcvlbmV8/p/TDxXHCeupO7tzhtsKNduf97gUHlK5MpySJZTIlc5e632eVrlEU2iq+f1mROxkadH6qpi54gWwdX0zw4lRsxf3fqmSJ/YnHkgT5voNYyBNCV6xK+pXY7pkriW5ybHtAnNyyE5Tolc23g4ok34OvLOAVUmLFxXH5QZMr8gTkoMWbie107qBNeXDw7pkLiB1x3KTLj5ovmhSfiG+uaYLtEbuZd9aoxJ3lj8FOgRX/KYAl3CN9EmjYu7HjUPBT/7XFif53X/ueXc/mLj3/p68/7zBAveU9qyF1n61/ZSo0d0ZE8YMtQJ/eoCweHPXCP0c+f7vj6R9f7Wsc+WBT+xtwxptrv2kaHP3Hc9psiQpO8b1jkh9H37U3FAjaBnzzrSFOkS/YFzpCnRJ/pDsbFPlRGpH9nXhhx1Rhx2xEvkW/psiZUOoa/ol3Oq5wt2lCe0CX3V3jakvO82d+o6J/SIflGuyFFnzPyXLhDssNs7f1BU9tmzl1eZyOdco8b85537tPs+Ii7manJCkT6Jj4qdQ1pEPiYOdinSJvRxe2SxR5E2kbo8kKHGhMVPqEP00qGgpByS+qT+KDMi9SmPydMl1tA/OU6JiPXg7X5m/aA6N/ReZdXYyRP5gLy/z+N36Zc6Q5Lv1gZZluS1ohyyWFafCgMW3uMxdWYsv9dxUT7fok7BHP/c7+HeaJ5OtPkGOaDAiCXna681vteJhSaNJ9n/42Xyc/PzBTlliyGhI/FwSJPo9exzp5x/uXnlkAZTFl/hHEfE0/aDOJRXli/tOaMs0CLucfA46/Ql8sfp842BxReIiSJ9EjnrjSx1xsy90B5GHNFkyvyL9Msxp8Qf4z5mjlt/sx/L3+1XE3it9X1RgbprW/+wx8k/7X2i3+zzrM3nui9r7jNy8wxzeeyz3yw+3XUajJk/kEuaTxOvXO0/UAxPcO8Txb4gdnYcF2gxZS5tb0Jy1Jhd2ns=
*/