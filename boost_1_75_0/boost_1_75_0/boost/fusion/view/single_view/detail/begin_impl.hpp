/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305)
#define BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<0> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
ZAxXvvag9vS8+9HJ66/lZd0UV9jfWLW/U9Lh5Nc2adxWfsiYvb8prTUmK1Po7C7hekUlnxrsTBk3vUdi6E5RXH5eJu3VnD6tlcY03mKTjSJC5G1wPjljoOv2zB+apLkXnU3wf01c8UNvHp9PQRWjTZH6IF1y+kPV8Q5q+eNbOil18gLX5Cm32XlBPu4hWJJO/gL6gEzbmPyhJbMpS7pZYFWr7Ly0aVer9Azgr8gK2D/1fvB8nGcwK4XiXyr+p3zsLvcbRGgtTdMEtWPqFfggYHJAmW7pPaGXTv+gSu94TnqI2Lk77scWhexlL0+1SLdpSZLbcnaX89fpeUftAnUz/I1Sko5xVoPKdH/A743pLBbZ++vSe9tjkqYhnz0dnv50vDVuT6vId03SUfvdMvsxpX3f5XdQ/9ii0XkmK4N/Dx5ulIUgAw82OMcrY91GReiV/KvqiH8H6YMiGnmWYCPQQW2KWnL8xpS0ZxHgs5twfnx8Qj+/SX6cOKcI0FK11mt0nlvZFOzHpv0t9Abr9LtjOumnfEN62226eeSfJ526e3yT5ftu+CbX9bek54ldwKNy33adyUZ7tChmW9NeDWnf64s+GNKJ69I64BM76atPg0/kXE5hFO8tQGLV4XwEu1rrHcxpn9f0U2uSH4lP+fAA22RdXF9wvFDpT0M6a5W8uU05G+40iJdzf8EPTNHI4wGdsx36yvn7NcsO7oqa
*/