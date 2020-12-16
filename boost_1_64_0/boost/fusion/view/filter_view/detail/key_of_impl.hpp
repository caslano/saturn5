/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
2hDhB/cjXG0nwNfCOJzefFP6i7odqLrd2iWL8aqCJWbU51pdX5Jh6tC9pyTWLuMHVbhk8zKenUY4K+NvEE4bPSiLvIuOcFb2XyGcl311FuGs7H9EOMqO87bOeXYW6EZelHi+LTb7m9vy4En6zNXvKuL9+/PcLiOw09CO00hUe8F0fNUWNu1Z58/zfb04lCfLxdXfUVinX2LcfuITMj5KFM03xl6nMMqYAcv1wrNu31GtWvuplf0HY+Rp9B8pRIUw1nVfnNL4UKKm7TzCq9QMXZWYoSfYz1bhdRqVSgD76IyJDa/bWhnHtzyrMaVeCF/cr8OruNC3EK7UC+FvOqDDsdaBfzcVXu/fYYxFuFI7hM9fT4crtUP4nxFeqR364vUpXLYJkjDOjD/OzpljK0gs3xV+lHp0CLtN9nRQqBk9/q4ZvufI21WfNv8sjQ1MbNSXHdi6k54jGJj8rJAtguwbfq7XDR/nd2n8IPeL8prVtIN3KM34joRxmRSxvJe8OPYBd0Rz/2xyHxxlWZpEvqTO0099zK5tWzqfMO1O4sz1A98PxSmZN4o60hKwyzH5Rxw7TYMwTcQOcVNt16p96d3d5B4u/dD37dIRo6Y90b1N3qJvJVleWOLUqQ06EFF5QBE7x3TfLD9uftNOkUO0gTrvfODtaI/y9fLsuii9nB6WoDnHxvrWM5blCXhjbO6jr0r5MfarKYYxu/OXTmusSpXNCyTGx3Ts2fc7kt0Y0/cjnI3pcwcQzsb0ywjnY3o4h3A2pv8O4XxMv3w9hGNMx5v9H+f2PmkY+5ablULSyXKlP1zZWR/gCWHMQ2gvEf2BTVRoCMM85GOszVZlxeKcSH6DZL1SeHv2INOBbxDw+OzB8CE4LTloP7YX915glANzvFHh7bY7MyPDKS3VcmP+oX1VuGo5I/wNOly2nBH+tP1VuGo5I/yiDh/saj7GJRWuWo6Nryq8bjm029M+1rTTDr2gKHwhbY1OSzv3BTVl053vdrrvGePYoKptT7fpeaNNaWK5dN2QrEqW1fn3SI8HFwzOmLC87ZO6VNTOUI+ZJ/aBq6qH8kOeITvbGr/SmCdLVyRya1vn9c+NufJou7OpZb9kYoibZPX+6ANmO1Oq3S3XPd6Vj/tgT7FzmGFSljZkd0g3K/zgZJzUVBmfgndoDx5d6+N3csy2cjLhpfLh5uLqDWPqj8Od6n7VYf1qVbZ2dZe29qUoc+MtLXV9K4vSJ1R7nnekOczSE5bIOkBeIam4hyiM4q5i6ErFqbhyESALQz2jO6rjvSdx09KMoeL++LYd1EB9vom91BWFqNibXRx3osopxmt28fHbTuBRh6q447uK0xobqlIosGPMgRWOvo60V2dkeJVub/Xpu9Id78qz1H2W7d2R8a7XLHjarQGwG+4DhneYYCdwfWB62EDaPzYweWK7OdrtbtOB6xp1f/Zu2A3Aq+wmdJnG4XooAfbKGwLTwwnSvXAjExv2G0VGHG+4MXh66MEa/ks3kdhp8zxW9XzYgn6U2cgFsWsHgR+KekBaoF5E16dhRws/dpfMPr22O1rdfvYWBQvdb+cfsq/ub06R556zLGvEwF/34Caual3g/OejfI7mZFnuBc7V+8Kp+iHmnyc+wGzq88wrgiITNPL2d55Fr9/pnSAS2YANJpOxpfG+7ZVibXs42uptGiIkc6fOgZt+k/qX6mFyh2bJoztf9NewWFqWbUX4t4GnRZE8tuw6aeTlyxgryo+aY0Vd84Oq796A+rRRW6qf/9zozxFNYSlydj5ysl2/wMVUE+f+rc4Dp3CdF6OPP2Ra40OgWE8oDH0Y+z0HZ2S4ZCt/sCd7erPA0NdLBmdje9ivNzM=
*/