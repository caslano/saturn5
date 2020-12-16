
#ifndef BOOST_MPL_TAG_HPP_INCLUDED
#define BOOST_MPL_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

namespace aux {
template< typename T > struct tag_impl
{
    typedef typename T::tag type;
};
}

template< typename T, typename Default = void_ > struct tag
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : if_< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type
{
#else
{
    typedef typename eval_if< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type type;

#endif
};

}}

#endif // BOOST_MPL_TAG_HPP_INCLUDED

/* tag.hpp
LScjkgWAPJBTvUJAklS+nCymENofRVHBj6gmMn0N44PPorAtVCjr21ZPTlndfnKH1TWAobY9vfrGyhopWyayyUgCCK8qL8GPd1Wmig+PfgYZPtINRIZ9sgW6A2yINwtIMgv4iRDILqLGV5UsEBv75djYL6ceK1iMjirijglWhFYL5v796vIFSLKgejE6sIg6MDX4XU5FR2uPBhsqK0mmuCC4OUkU/GB1+ZKqFR5IYhdUhwRikatxRxJ9LV+yMLBEolBFFAqdvZBR6HkCFXNycHXREuGbA1Nx+nnmHA9SCp6vSYtFNWS3lKwSlCwpKHFVtq3LpdiwuHOUtAKR5Suri1Zusx1PRk0h9FxZvWImrhJgHrjpMylN9OWbgOUrkxCpMo3SmaKQWmNbbCemhwR5j+zId63dxXM3p6IN/V9ZeQ5Vsc0+lapGOVzvHEu9Szd/nxzcl07fb7rJoB5bkmqmpZJq0yntTcsQ05ESAfdXhjuKr+VLLZ/qSgkCVGarm0WOPdHHfbgfKRp7MZP0ne1jizhthNCM6nveB6LSBuDZ6P/w0Z4nkAPCKYzg8vkYQeRfNQUkSV3JyLz537KU/P/Xgp/iRzvfmpgffeCWpvm/DPB/S6APH+sPyrj0bFMSm036PGMqgSTXE5JcGVAmT7L5xEpJQ7PovIa+sOOAocbsM1lAAa9sVanSE9N7VLo4GG0QXkE/PEPTBFxCZav+t+ibiOUH2Az39Wchnb62oU8yH1pgRuBSmQ1HUTnkqHuVaTjo8svLnQtK7bYyROaWGlstkZPAbb3ij7gglyFEpRBptD/HTNrH+PBeKGa7GKynq0zhCqthIEtwyWFLOg/vp/Ah6ZZm8QHys6xS7EOZe+TraewxswX6oJS372UY/Ki8LdQnpfy3XfLT8re/s2X54aZLT4IX5kjpSNR+/gfamUR6QDP6LKMRDkljFsbR6mwVdlbmS5tIDRh+r0vbWnBfCKgIezxi/+DxVUrttzdnIX8rdSI0fBcAPuvExDivAtYnW6+pvX6x2mNBXO3guZuUfuPzfHLSmBuqf6WrS8oe6h4Uc+VCghMXOZexItftc3n9hlmfX3HkNSpyLkeGZ+M4YO9My5WZ7t5LObFLJZ4kE4/H9eBHOXGwIZuSzuKkV6ukfWTSLPqEGL+KacsxkLpPvtmqW3IFteQsek6m51h6dh7hn54vTNROnS5JaMz++flg0/cLD1Vnzlnaz1WdfBNjDh+YdIY2YUFJg1/hbvi1FqFF9H0/aHO3ubG5+364VdOeWoFG5Fa5cEWmPeRV2bhuxBnjy7vN9jfMSKBvneU2ylqjb03pwwn1rYUaL23gpjctj7uX+jfWf+ngGyLvd7ULjhLpzLuvyGZq8iXzHUdh8OlUb6NYHVJ5Ql/OzVG6go7wLqlpQ9RTCTvqvTZoQrx9s5p6NKAPQb0I7kGHu6Dqdwzrf8D25AFjSzWRF/nF4Ra2EeiqS2Ww9TZuEuLH3y6QPdfs/Y4PzolMFf88BNchjRtPjZv+fj0k+jxkDREqY/b1mpWg+d/b42NWopKmeK6fKQ4EAWAkoGPgZGmK92hOazfWoIOcHFk1LhXrOFkTwUlgNSQwDXROpsUGY1K3JTuYmwjyabcb7AJum8jF/ByQ0uOXWNd9Pj85CN4C/EuED8f+mFTdIwyZLjw9mgUA3X984s/JAnB/bx+TKtqrdWeroq4d4dfseVdu/PM3EArQg6boSb5JT1z4MLRK4koz54GQr88qlxcrb0XHN6vPTKOXVRSVqqXwm/YDNfdAfF+HSdFd1Ex6YiLfP70V6Wk2/WV5K9LnEas7RaaPp/9CrLbOOZDvcPMCU1Di9HXSbmoGMKq2VMk=
*/