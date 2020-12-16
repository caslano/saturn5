/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
JG5UbXynOesyVcqRkMxeJosItbZjeqmxJxzL3px5sI9O0ca1e8BeNuWlN/aYWjXs8QOXKvcU7fmp+/6edWXfa1sSWT5tnVqK16mHxFVbXI3xcR6yLMQE1i9L4hTnshwv5Rg3OVN/jCvUL5v0DTUvb5DzGEKWzj78O+tp3rGtW64ZmbHWaBZO945tmV5iL2jehy3jq+3Qqs4nW+ah3TaUxXeOm2+yvRaoyzEtNV3yClOnT01Ikp7pjhgFOz0dw9MT1OOrfj1L/3P1mD0dmF4bT4DsNf1p5+jyo7jqOQLa130GA9V4iz2d9cah396ujijPEt9k759RaF/3su+R/pnUBbnajn1bnOtI2pN6zGAmJD59KjFfDMKjPkoB9e0pizh9lNZ+5LCUHp9FthFdPUmdqutKll62B02dpCfIcO26jc9Iio3PzsiU9mSybvTtSeZuOH6vlFiAmyRuy3oc0ZrznWnFl9eamJiZWsb+2k1mGM4TTdpIrnbblvLmudiuOju3C1qOsz6re9imnx6bJvsRTRtXystXQ4zeWFuDrq1/z73xPHO62rZN2mBLTZuSPGxtsCptZzn1GauUa7rumKKWSY27oDmvYhsu1g7dJJbcPfKes1kYwXrJn1F8vdh/jUWnTEnKsK2b3FLWzfcz9esmz2TdrDTbn+vXgeE8OoGKkPfxG+rVarKPiVD3iamJqeTqyCPUZL8RgxvrOsZNsSaTk2NdhzmG25qQyXmAur/V73uMx0SLRNkKle2gHx5j/RTOkvpmMvvGHqi0n1K3d0e5s+37GattIilfMqbXtQ+n4UqMSGebiiav4nUu+0WTWJ9K26tFe7lBylPaymxpe/rjKvtK2zLrtv+dstzz5bfsbFLvenyPMS63cjqQkZBoKb0/vWw32mONoU+9lcaiqSOLtB/NbzZ//X5bV+ZgicPnJ785OpL6Mm7LWGOZOexT5rLEbTM5p9fFTpAy68pxRcoRqkwnvzM6MX1MsXLYf2GX57eF8ze1lENXNmObTpmSQJRQbfvvoJ5v6MvcWGLQNZR4D3UxgGH547Rl5iexrG5HmZNLKjP7lI3jZZ8Sz15FmT/DFqjD0lLiGKzGIDNpG0o5/ezLF6Qus74NGLYH+yYlbU2OA8rmZB67TD1ukifNTK2nofZysKPQ15O/PLj1IwvQBL/CW5S6u9NYT2oTK/XcUsnzAnYzLOclk3YXaVxO3fpOtLIM6n5jm0/x/UaM/L5S60R/zYNptfGEMohAlJQWOylL6kXGIx/jfvKC1Et/afPB0uZbxhnqxd7k/2vt3VHeLRID8DnZV2yR6ykHo7TlJZwZl1XK8u4DiRWiu5YS5byWoolXrn8/gMTyjlOXz+SalL9zvFhjve+W+HqNZbuth83JM+YO/XLIZlumbXZSlGabNd821d8e3vWc52T/ye0zTN0+9fVxvJF9YSZKfYzDNsp+bIyhPhKnlKk+lPOiw2P150VWWW7teVuOrl26/s3XXV8PJf62C3Nx7A8xbsP6GEO6+shpbH4sOhirrw/7ZvnfOw6p1yCa2DObKb+zsvF12r51jqa8Ss0F2g6gpa4/pT2fudu8PRvbY46uPZq2ZXtMt8bUK+XM4m+P2ctlbOPp2rbaS3Oe5amP3Zgu27M6331N7OdqTe7WxvxG+zz4rSFtwOT6pvZaY2eJY9hWrim1JA1hOSLs52+sa6J+l/FdFrJs2u1fl9dKY15y/Wr+Xdq8eJFKOfJydR08vKmL81L7cYYDFnnZDjT/vfNSi+Hc6nRTF+el8cYy/zXnpdcY5l/Fddwp8/hPruInlT8+00DbfIJ/9G0f+cOcxVuHjG98ucbSefSBG6IMHxr60qDoHr8=
*/