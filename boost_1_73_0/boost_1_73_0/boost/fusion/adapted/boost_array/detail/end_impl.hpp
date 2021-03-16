/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_27122005_1120)
#define BOOST_FUSION_END_IMPL_27122005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, Sequence::static_size> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
cwg2m3zKZDXKw0NLGZ2ez+a8ni3wcgrhWsNI7UlCa1/DuFE7Op+U5WWy/I0sSSw3y5LckFuSOD7YM7IkEj6XxAu7pQCEHxRqmX6Yts5I7gw/K9RS/jCR9X+SOHoF4fv1eaM+J6UwA0phhhLs8cDygc0CNhfYbcBWAFsDbC2wzcBeBvYHYHuAfQ7sS2CngUke0djHlsE+AxbdCU9y3OKd8L93ixI2wrfAYuSRzlFvi/FMd8IfjbEY3V2o11jnI20=
*/