/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_05052005_1215)
#define FUSION_EQUAL_TO_IMPL_05052005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<vector_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
92cNDgjlWml8vifXSmNCLz7H+AYFth7HhXOtNP6d92cDWiiw2/BmvB3vw434At6Bct6Q39aUu8554y45Pm/CvrgZr8Itct64B+dgKa7Ee/FuvA8fwfvxBdyKf8NteAofwB95fx6Ua8e3Yw/cIfkKrSe/ZeW3bTEOIQJJV6b2kq+OGIZdMAG74jgMwfewG05lJd3xZuyBPvIsgfXYEzfj5fgo9sJnMQzfwN74KYbjeewjzx4040qMkGcPRqIPRmFLjMZFfN5i8Fbsi/dgP3wMY7Ec+2MFDsDPcCBmNGSfcR4OwrMYj/6N+L7iehyCjX34nuJlOBw34ghs58v3FOMwAZ/HUfgWjsbxHIeuwkxMxJvwatyI1+DDOAZD+T4k4Ta8Fh/B6/AJHIt7MRkP4PU4mu/NOJyE47ESU/BfOAEbcrybiB1xEkbjZFzM9+wGXIWpuAHT8GG0YCgfyHTchpn4Dmbht3gjrrbd3+7Sr/O/lGv8UxjPYiVKiN3EYeKUMcbFmIzJmIzJmIzJmIzpdz/96v3/aRl1ev3/aw7j/1dLv7a1GfUO8QIVoaQw7Z5+GS7X/5dU89y/1XIPvar2/60DnPsDlrv8bdH+ljLU+gvWxla1gfdV28qna2lqW3l/LU1t3/fX0tT2/c/7qWlRVWnPa2lqm3+Jlqa2+c/W0tQ2/xtiqtJi1PVFaGnq+ry1NHV9H0Sraer6nlDTorU+BC1N7UOYpKWp5dJXS1PL5bMItW9FXV+5lqau749amrq+HC1NXV+ClqaWc2ctTS3nc2Y1TS2X17U0tVwamt37g471ce8P2tnHvT9olZam7scULU3dD7OWpu5HfS1N3Y/3w137g+jn1+lv2a7T31KGVpM8T3J6ljVf0vd46IcpV/th1G4Y27oP6vTDHNbph0nR8qDOl+CYB4e+oc0dbdvJVJ9Z6fJcy1Cd51oOw2DdZ2VkSV+n6/Mr9ccJJKrL5aXPcrvOxmJ2v87GEgEu4wnmmoF89G/+ZqT92HBPe/vfo/uqf6v9PUtIuJHw9zo9ZExgQeit654NiLvVt/Knz2nrDlPS2z9ftO5C15RnVhWO/vPKvzx2yHM/TUezkr7jnm3Dbvau/9OQtH4P5fyj3zTP/TR32tZzw18WbvU/2ubB0ctOTsk+n0ID1wzbekZck9b+o5SzYb65gZWLY84/57mfJsG2nrcWHnnl5282nJ2/tnPbx9dNalh3/VKRtu1eOP6Cz12LlhaPPHZuWtakbkqHhi391Lqgu3vvz7mw9MzWp5dt7fwIfQa28sw9PGvlN6d7vHLktqGBYR/Fkv9/WpX0L/tOW5ST9smaET+PGZzXtjUfHHv7m5xH5LyS6eXQ/ib3tIjCjjgYO+Fi7I5rMBw3Yx+8D834LEbgUNYViQcxCo9iNJ7AGDyLfbEB2+qHbTAWw7E/VtLuNgB/wIHYypv2MuyNg/A5eUbnuzgUT+AwPIXD8TscgfV5T0ZiE0zAljgKA/BanIxjMQ2TcQ2Ow604Hus1oj0LQ3Aa9sTpGI5pGIcWTMR0nIIZmIMzcCVmYqwv7Vk4FnNwCs7GdMzFPJyDRZiHyzEf16EV/4BF+A4uwuO4GOs1pt0ZO+IyXIgrcDOuwydxPb6Bt+K0prQbYxEW41K8DTfj7djej/Zj/CPegcfwTkzk/Vp9OW1oxCHiAmHuVc80ldhIlBPnCafrxQh/2uSCiGgim1hCbCTKiHJpswvlTS8kVhPbiT3EQaKSaNWHfyeSCQthJQ5Km14gbXlhRBwxmciW9r23iVPEBaJpBMsTyUQRsY7YT7xNnCDOEt6RbIewEsuJUqKM2E+8TZii+HcihCiStsLDRCVxlvCJJg9ENlE=
*/