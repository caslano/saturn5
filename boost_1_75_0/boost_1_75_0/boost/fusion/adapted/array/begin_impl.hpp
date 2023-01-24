/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
hKEssIJkNkl9Gm38tLZBj0wwJ1P1Qq22Za7iavs7ZW5vl1QT5xXrXhMB4wXbMzAXEtA2tT3qTkaw7gT0JgJgNvpiLFreZN1+V1AakPyI/yLZfygPhPIIBbOfc1gW4dHeogOA7q7FIRAnytcjN+BMegF05w0CIEHweKcRfk0gnr9scT3EsW4Cx3Y9D5eSCaX4Yp145/Y/0IDQb8nzDj1Ir7t0Et4eyIBGe/ILIiNore2bymTk6XwmI7cEkRH4I0tsVwAXy70IHMBTIdUE5mQjUQTKnVJxtgIJyQBmpZmgbMGL3MLN+G4M8Xzo4HrHacD0CXVSkeo8NUPxbnGIAyZDuRTg9U7j6wnQ9OIGWKWeqjIPqvh75GpFjQBmlC4u8Vm4QkaCFpnuXXIZ3f6Hram+lf5e9akBgC+YC4UeQEk7uiCt1bwTxH5HxtcEiG5s8pryfCTINHLjNEUPstz2hTUcCjKF4GDGMw5L0aYAKFI8aN44WUZ3StY8G08HOAQnWOmtI9wFs/dU32rBo2alQCC3whdBilR2KhAAZYsHeCbB03QTcLTrOYchhCdqIJIlsEPw1n6UJWuU+JQTVMBXn4qvCNYxAdWs22OVE1YT3U1grTZ6oprv4FQxuSYI6DDrZJ4mzXDFUAfKua4T3Uysqg/duuwLX0/Msi/kcSZzj2DEVbQqeaDkbY35UkjLdfdhtZa5GSRySaBe+g0FR+u3
*/