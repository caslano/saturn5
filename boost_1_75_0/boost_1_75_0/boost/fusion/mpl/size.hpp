/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_10022005_1617)
#define FUSION_SIZE_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct size_impl;

    template <>
    struct size_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::size<Sequence> {};
    };
}}

#endif

/* size.hpp
1D4D1sq15taJv4SPfwG9s4Dy+qF3hWoX3zCbAnMyC+P8KaQ0wLUzXhjRqO1mplz7HSqOT0CpAuHjXcADru0gRJNWU/jDZPhDbm+bpaB1LK4OZHszf9WCf/iLm/mLI6/SC+VV40Vf/mIv/2Jf9ItMfKHzSPVb5+SR5dzaCP028mFuc2kkAQukY9PT3OwwdB6fm5oWYLjP0/ycm69/YANKYks1PUX/cH/X6gX4iIJ7MvcU1f75Ggr9JGmz1JC3aJaS8FmB9qwPf1ZgMrZBEvk2yNQ3DFZqZfc3aLe+Tyva0SxmHM8tofw3b3KP4ZJojpSSwCYE1+xL5D68mLmA/UJSnDaLpioDHufxS6dAsepFmaguIV1Lgy/xDR82oRC3XC+W8u4pxvTKo0ook1KlL43sgvontCIcW0zvgyvp7KkU1I7oBrXDrPKoKdyxXI+QWoDw5xKvYdxqdKBH46Ae/n0CTI5jgecm9qHg72nVS4gCBNXYqaq96DVg11ORNBiHr5vbBIAHkd2FTkRix/ztDZ0lCo098JgsbFGWcDzYiiWAHaanc5Ywcs3peXWy0mPnVD2pThZNI1nY6Kg3YkVqFohUOheS9woSxKeFAvIH/k44+UdgdhKL2aRvpNwM7PTRn8ymBXP4Y186f3YvPKterLMd2W4X4yQYiXMcFLmkpNZDr+so5+iHCzqQlCMeiF2PUoIeI94DIjmid6wEaztR
*/