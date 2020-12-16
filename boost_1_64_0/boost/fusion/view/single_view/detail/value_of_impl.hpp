/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324)
#define BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
YeLfUHGTmflIrXlUs4/w3Mps6NbJRdGywXR879p7V6J1uhjEDFfNbn4+rhOatZBBtGNxIrjOVJrP3SBChGb8vJvBwpnx824Hq8yMn/dMsEBm/PqSq5hPX8T5fBaFpYE5W0s2mLP5dB7OxzQrzA7mNHcwZ/MJT+djmsCcjWkD+yrfmoL1HeoTQ3FeBrrWNZOudWYwm4tmJ7+ak4IW5W0QB1hcl6a3t6HpfWAtZNLzGVh5Mun5DCyOGT9/2WDRZNJzSDHYL8z4fjGBhTDj9bSChTPj9cxQWC4Yz4/XOsrX+XwWMGdxaWDYh3j5eV5hDoVl0nxg8r1DB30gk+4dOudxNp3z+eyKMR1gHVw0c5t5tSX1oYRBfMbizlTfOoByB3O2llywJGbJvlU+0Jh+BnGMWcWoSh3J/J2vMw0smVnpKfFVqbclDeIis9CR255TzQLgrDC7s830B1o2mLMc9IHO12IGiyOT7lUKy1WYKci52cGimfEzlqkwXbBzMyvMDnYo3xLAFl9Yuh7NVsogHMz0C048pP6VNoi2zPh7rmww3J/Npf2ZqzBRxiAiXTW76BP/As1RziC2MJtS4uMtNH0o9RZMutaBlSeTrnWKuExFnDBA7sx47lawODLpfaPCdEboEbP3HU8Mof5xk/unsEywQDLpHg4WQibdwyvAdZdMuocrLA2M6infw8GcrUVUdL6WKDBn81nBnM2XARaVby3AGt48u45yB2uWby3Bnl0YcpVqXckg0pkV2vx1Z1pLmEHcZXZs4CR/iqtsEM2ZNfgw3U5rAYvSjP2cYFgL2ApmA1c12YDmqGIQDZiNmryU1qkPL7jOlXGnm6CJCIN47aJZ78AlC9FsVQ3CncWtCV/8XzQ72DQWN718Z0+Ki9J6BMb+zjbID6w+M/p5sWCiGux5ZucCu42mmoGFk0nPZ2B8Pr4nHIo4Ud25mcAqk0nPZwpzgAUy43s3G8zZOnXRztdiBovWjH1/D+Qe7XwtmWD47yy3Arv+ZOkftM6a8P5BaPYoIOIVmrUWXHfJpPfvCrODVSaTrpFg5cmka2SsQfR10Swm0WcqrbO2QRiY3d3ZzY4W9bnz+axgzuZLA2vLjF+TdXUNwovNd3Z+lWZoljiD2Mjivht9bRWaqZ5BHGE2rMvKoWT1DWI6GzNh475DlEMDOGPMhts9r1OtGxrEdmYHUx/0pRwaG8Q5oVly3O86tIwmBpHG4iq8ODmM6tnMINxcNRtzr/5tNHNz3J9g0v60gVGt5T2viMtVxEW1gLPCjJ8VM5jTtYCFM+NnxQHmbD7R0iCM+XVpDTbKr0MlNGsrg4gvpNmAsXH/Qctsh/sFTNovpvYGsdJbs9t/jaC16HpjDmBSDiawcGY8BxtYZTKp1mB4/trI7x8oDkx+/9DHeZwerDyZ9EwL5mxMuyLOARZHJj2/9HVuFrBoMulzaKe2xy0bDPMzu+7R8gPLBevNrMYfl1ugWfsZxE0Xzb4eX3QpWmayljuYljuYbgDkzoxyBzOBhWjG+g7zgfExqbdgGWCX8q0t2GDzlVA0x0DIjxnPLxOsMpm0zkGwTjJpnWBxzKgPYHawaGa81plguJZ20lqyFZYLtspVs8gDt2NoLSkGkc3i/ju3+Do0ixXyY8bzSwMrz4znlwkWwoz3QQxjY0p9MIEFasauS7AWMGdj2sHCNWNnGtaiMN1w52sxgx3Ir1l7MH//+15ojlEGMVRodmD8li8pbrRBTHLRLKtd7ga0qFSDeMCsZYt/b1I9v8T8wKT8MsHCyaQcxkEOZFIOYM7GtCniHGB/Myv3cVUuWu54A/2cxA5gpnNfLUHLnmAQO5j12zvnAY050SDGMou/Nug=
*/