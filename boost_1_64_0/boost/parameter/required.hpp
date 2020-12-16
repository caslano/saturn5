// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_REQUIRED_HPP
#define BOOST_PARAMETER_REQUIRED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - all keyword tags wrapped in required<...> must have a matching
    //     actual argument
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct required
    {
        typedef Tag key_type;
        typedef Predicate predicate;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_required
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_required< ::boost::parameter::required<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* required.hpp
+bgVGAHc5jb54PzwreHys5bLzzqgKX8q8zVSyP8Oy7+X5X+X5S4HxgH3AeP52ZQjg8OLUcjRkNupeKAb2Ehqp0qZL1zBd6yewfctsA7wONCUv4z56qvkr8PyA8OB7wIjgfuAUcD3gNH8bMqx2o8cbuS7jjHAOsBYoMm33Q9fQ+aLZ75GQNNOlDNfhMJOfMrp/gxoxlPhJ5+bs36TgRHA8yT9Vvrhi+V4GgB1vriq+GA0fOdnJMcXxflZT+53+OH7Ldrg+x3oBp4DmnypzFdHwXdNpMHXAxgG7Ak0+dLm+U7fzyEG3ylgBPA0UJRX5mug4PuR+SqBscCfgKK8+onvOPN9x/GdkPjKmC9Bwfcg58McIM2Fcz5UgmE1810VbPBdAfcVXlD/DXYqCNgBGAXsCGwHvBR4MXAj8BJgF2AvYDfgcODlwFvZf4oeNvAu4NXAxcB1wE3A9cCdwA3At5j+bWAP4JfAnsBvgNcCvwX2Af4M7Av8A9gPGKK398BI4ABgA+BAYCJwELAVcDCwLTANeA3wH8BhQD3eG4B6vDcChwGzgcOBE4D/BE4H3gB8DHgj8CngSOBzwJuB/wJmADcAM4E7gGOAZ4F5wGAoMB8YCfQAWwAnAjsAC4FdgMXAgcAS4EjgJGAmcAqwGDgNOAdYCpwPnA58FvgA8DTwQeBfwDKgOxh5CkwErgG2BW4EtgPmAoVdWeDHLoaxXQSSXQSa/Yly5muu6E+85jba5fVAN3ADsBlwI1DU+4UGf0OVHeR6HwOMA8bK9X6h73HKi9wOreD+y0qgOZ5KZb4JivHUq+GGvGuAScC1wO7AdcBUPT3Am4DrgaOAW4BZwI3AscDNwHx+L/Sz0Hd/8NNwtrvAaGAFMAH4OVDYU+ZPUqSzB9v7nsBEYC+gGW/y477j/b6ekc4fgPWAPwLJTgBN/lTmb6DgT+F4OwAjgR2BscBLOf4M3TH/COavCzeM+T/g9vIQMBn4GbClnm5gB+AXwMHAL4H/AB4FDgF+Dbyen09y2OVyPFx+B5jtIZe/RGBTYFPgFcDmwKuBrYCpwPOBacCWwOv5vWgnnvBdzl4BHZUbYDxwjcSX8YRve7+K+f4FjAW+JPGVMl+Ugi+M9V6H9R4OFPbeD18k80UxXz2gqb/FzNdFob98bic8wIbAicDGwCnARGAR8ELgJGAKcDKwM/ub4Vf6CX8ah38nh1/K4d/P4d/N4d/L4c/k8OFflT9P+p53yOXwxwLrA8cBzf5QxpO++0MfMd/HUv/Pw/SXKPp/HwQZ5ewA0A08CIwDHgK2AX4IvBh4GCj6fxxefYXcBdGsd2A0cCJQ2JMnfdfr59iePM/2ZDnbkxcke1Tph/8h5n+Y+R9h/nmSPXIv4nGIQu47WW4wU37eBRTjhkW+7XxbtvPt2M5fCBT9rUW+9TSU4xvGehouxefxwzea+cYwXy5Q1KNFvuv7uSCD7w9gPPBPOT/9xFePy1M0MFqnkcpvuR+9BLFeglkvIXI/2w/faU7fGWAc8BegaZfdTxl8AxV2eT2nbwNQf78R2Bq4GdgW+DqwHXArl+dtwD7AHcAB7G/G4+F4blHE86vLiOccMFzXI/ACoAv8lwFDgd2BYcArgUHAm4DBwJv5vdDDU77Lo4v1EMTlMRgoyvHTvvM5LJjtLPcfwuX5k6d915/L2M52BUYDuwETgJcDRXn2E++VzH8VMB54NVDYn6d9258tdQ2+7cDzgDuA5wPfBOph7wJezM8ned/Nag5vLYcXDTeNw4uGnqgsA/Xw3MCrgTHAHsAkYC9gA+BoYBxwHLAh8H5gPHABsBHwSaZfBGwMXAVMBK7h92Z5WbzYkKeDorzs4PrzOjA=
*/