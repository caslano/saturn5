/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
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

/* end_impl.hpp
wnJkDmKKsjjpG6FP4Rp2O82pt+RzcmYiWjbP37FwUiDKbRWI35Jj1Gw04aufzewB9IQPK5Y99JFLcNLtirGOMfsHcm+Kwg924XCum2BeYXMDZmuaLcD3wPaR+LkB2Ux83UbI+NmqbX9rVjMEhwx/W8+ts1nn1/95tM1w/90OJ5B6WDdMkukaqkVrFm/GpRoP51gWr/eK6RK4+YPp2RKiIib378+gw8tnyQZ1Jh3NepcFiD8r+SMznouQr/8r01KKHGCHndBopqrZ1eqh+2+aFciFdYK4zSJzfg25mMVCsrHHBi1rUeZXLfK5uJ2CAqERwAwQ/NWc1WUVsBuvIYJETIzf9YjmjvjzEB2cUse2GvXfXRbh7TK933RTSSIzaV2YpadtodKGZLOdPSf2UQ50y0wMeJwm95LhlEHoG67hZgQCTy4o+cHPRZTnIvPuxxspsxi+JQsAFdV39Hx9pFVh9xj21mH2ewt3dk47UXv5WQ2FPAL5ZbmoddmIChf4GjIGxIDBJ+gWfChmSfX1zr4+uW8mtrHM/KicyxvXw+OkOXN+VNDcPR8dbpTA9w==
*/