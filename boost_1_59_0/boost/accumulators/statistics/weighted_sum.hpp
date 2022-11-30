///////////////////////////////////////////////////////////////////////////////
// weighted_sum.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_sum_impl
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;

        // for boost::result_of
        typedef weighted_sample result_type;

        template<typename Args>
        weighted_sum_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()]
                  * numeric::one<Weight>::value
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            // what about overflow?
            this->weighted_sum_ += args[parameter::keyword<Tag>::get()] * args[weight];
        }

        result_type result(dont_care) const
        {
            return this->weighted_sum_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & weighted_sum_;
        }

    private:

        weighted_sample weighted_sum_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_sum
//
namespace tag
{
    struct weighted_sum
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct weighted_sum_of_variates
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_impl<VariateType, mpl::_2, VariateTag> impl;
    };

    struct abstract_weighted_sum_of_variates
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_sum
//
namespace extract
{
    extractor<tag::weighted_sum> const weighted_sum = {};
    extractor<tag::abstract_weighted_sum_of_variates> const weighted_sum_of_variates = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_of_variates)
}

using extract::weighted_sum;
using extract::weighted_sum_of_variates;

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_sum_of_variates<VariateType, VariateTag> >
  : feature_of<tag::abstract_weighted_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* weighted_sum.hpp
27bf+u3efbp3d5/uc5/zvLf7jzsrYo6IzJwxc0Z8M3NEPvUZOSNK/hteek9ctGq2awTDj2ylZW6ezY4rASw6rGqC6GfYGLYAR1REClRAPVJtUQ7i9K9SEKGyr4ezckzRByJgGFWW/JO8EinSx7O0mxqZZ9vsm9Lh5c3rVMjaSdKTOHV3du+cRXhyTw0lyY4jFtQYGfcjv59veht4VXOOQf9eBMz/ynH+y7H4drbp6enpBJxN/ukoYf0+TIT0bP9+pLAxsv3dAXHEp2GkZ/ura00c8Jn/NhyCf/nUNCz0f1vzPYLMbH9rS+tvK7+Hwujb4/mbC/+3BX/zTf6N3CS+JwJmBgLWJpZG+PR0Mnquf5/ZM3Ow0Sl9q1AFn+NfDf+/yIVO7e/7x8LM8q9EwfLvRMHwPRVk+XvlezLExMjK9F+I5MLTxfOn8uqX2dOkNCMFP7l/rAQhBBhBKnFCIKgEPqC+rzxiGljLyLohWBEDKAShvgA8Sg2Bc39j8gI6PGSO/lD0BopIeVlbWe0j0PgVx1Eyhr7algvflTdvF1/GzvqRx6nSpMOk26UtgF6gPKZGEHmaCptDgYO+ZV+C/C1ugfqEN8l99w54pQAEF0It32o78env9sJ4/hAh+cZSkvlTH/sgEzxBDAsCvqaFpUXGUrmjCQgj71D4zB0FlCeqPlw36NxyQvSpAz9/bZ9agTdqun252+f8sayE3mKBT0b0Oy6davUWnwlgK4iDrJBYz+Uqamj1pdkYeExn2HoXEOSutBZjM4hbNgLDCywo0bwq3j0bsRJbLEEh0qBe8xIZL7Lo6fM+iLgYBGOeazBiAmItOj8Q12rRE+P6yHUjEWJl45/6kfSmHWAkXkXjjuzyoPbvkvsCYkd5RxWlz97gvU3HCz/lyAiteYgrQrBR3UiD/LQhHhMRhKhuWp4lPamsh+xuqd2i2+UYCudF744lW6O1JW0K6Zi4ygz+ikuOEqAC97oys8YwHHeGvktui8whyiHKJevwk2PSaf2yecxOJzpxjqpYTtZ6MjYDgePOQaIyIz1ujanJxfprXaDlpSXBHm3/T4ANjufV9hF4F+NzndC+/GoVMe6Rs1C6QPjEM+A7tBtYgWsIoVI4tED4wz1rsDpn+uRhHUyACszq+fHB8ZktBEVGtL1S+Bp/uEdM3O4PrXBc/AHIImTr2F1cLSjP0I/wvZvnIYiBuunM49ZnzsBoY35rRg3Uqkg4nnaMW68WlJj3h2EusU3e28U4Lj5ZlsOd7dOAJU9TLtednmy+DCfbk56QXEPggtqAF7xDr+rrgMaArIB8OEvu6oNuEgicZiTF++5dYBMcdLcc3a+JN7bOt4XP4c/BcTG9YFyUO4dOBlqKuVmGF7v+hHPggoDW0hBaAS1ex9xk77dch/p5K62kS44mP5fyIqpp0XuMVogKsZSc9OmNY+fEsEW/ULScsmmCezpHjFbUigH0xZ2lY2NHuFdUr4BOIc1pL1M6d7APUJZc43rAlpk7cZGpvKPpsWPQe0J3yA+YhhzVGSpTvFa8hryqaZRjmHtMdxy3abRjvGP9eni3GcJ9MV5k/nQFeBpRAmRRBGQhhXoQGpHsfCNTDnMhk3yHaah7+laUzAgVf7bskM/ozzBOO5TKQRCl8epAb5GQGxBuBLlelmMIznAjyx4V5KHiPQ1uDLkeJTucxh3kjPALV8ysaG9+vl0MV9LKIRhX1Kyoo+0WV1xe4OwwrBtPT1RtX5R7JHeklB379cD0GqyyZtDiHcf1cB52YJNd3GYyzlDe/g5b1MfdoGa2ywCxHZHlkA923wD2wLdd72PA+Wi57o8bfexB4OswV3zcQCL2cG/RrpyY6SF2LC5b2MkBhnYQuoExWyzt6KlBKltcXki4QaFrjt9Va8rP3J68q2Fyg0I39J5QryBe4XT8Nrlw0zozbaZ8nL6bold76dcTz6jtsCpLFa7QnThbflf9Ljt8e56ebJ3gWxFXfX03Otcf1Y+rNwHNwDYDa9dCrlze6Ffdxbuy7UhXvW03RM8K7+ibAXhDctsIzxLvyLhh0Ndzzxjv1JsR2X1Te2jXEc8k74wYQTo9b7YEzruqdgjeMF3RW902u03Xa88476qz4ocJdcNAebGks9LrwiQ0BUmuoSnUxBGhMc8SviASodSkeogECohEUsOKtZH1cQf7lrX+GUIq8Q4jlP/0SA5a4rIREUMYdam/PUKiIn/ur8dHTBY81PtN5tWdYHOmTOabTDOZEWXKTeVBlwimmzKVYyU1Tquo8Wi3xtLm8Z4WA2IWELSi6/hVFShg5ksdK7ZGNuaCK4BT9A0cE9Tj8IRVCWrOsN4jl88PzWDe83QG04q1zTgdS92DtAJv+doQ+xDmj6DbY2JIUYqTYIC3tUbWW6Hz/r4OWjM6ESAxiresWVVUvDA7wUjlcX8cPd0otulCeoVjt9vOsRSTtd6UCAjJ4HZcpnjpk8NhqM2ZVv/5a5eShgrvoXjGQBZLU4HD2lP5ITAswVy2KpPbyHyj/oTJeJFtPI3H5LKdadIyw2cRCJSFpW0hWSXGZYcwmw/+Bw2sWF4NiVRKAw2fxwAH1ZSW0+YL2q/m1zwWCzptl5HClIouzz4UVW2nBxasqg3HjQe2dde5iSbLTqcxq6YtuyMtn863LI8TL5+WL79HcK5Gaw/Ttz4uTpfL1Y/h/JgLt/cwsmz311STJ96nd2i6zvtbqrfpsqqOz8F0m46PSZ2tja/NN3DeY+shjHA2jWYt1jNHpfc1S9ktDMde+kjvrzr+q+L06+bsSs/X3CuQ7CmHrzZP1hPPooOPlIcezGwhsg+XF2xiTLwhn27wD5tzURber7kpn1HwEcxs8AMY6Wch7VMGdytJqf02LD6HUOMQmMwmiY0FvNmPZ4eCmzHsZpF66JODOe/ir4zzy7eUj/KKBJiuOZ8pu9cr+le4j6ePEM7ovi+0iq/OrZ2uHfYPOJyZt+z3q7cvx4zP3HyNr3G9r84v/4zLt6+V4y+u9yfc4i95r+y0R64PaPu2qy7+q64dl1cbTlkfg+x1+uetJzG3jSe2x67xrdS/viP9bfXqfsuF+/PVm6Vi7SUBfER9luBEudGfZfaJ4FT4pmuAj7v1vOTt+Jc7y2gwKRbB5nkg+Z1R3Zw1u9eLCeQpvwf+rPRnRkhlcPOnSGhYp+xvVP1FD4W3mktKSZsQtSdv9j0Xws/kFtTdOZlj2FBzpGz8jLeUfCx8Ti8cuPmxLGJ1tYRtaEOyKkHmJtwHsT4FFE4k/aUkeDGXnA5XxsQov1ozecxg9kdJ8otA15embAZTVPNANXaAGTEyYcx3B6jERSHhDvlEs+wBeGidHwzXWqZoww3YxG1AWlsTrkdx2PHACPfF03dunjBuYMyt0BXJdfJQ7R7toxWjmEFWCtibkTGte1tC0rPCnUSawyjHgLXwMpXiNiV0TjAYGRtlJmla+obN+ZmwlZNlk0rcZ9gLuEOt7X9AlYthqzIZilvN+WUn15VCuHKaR2ei0dj/rJFR39xrqk5g1T+N25AFlLlpLGvbjQABuClzcHDIz1Ep1BF1Hs0W/AFHuL6dn9qhdtPYtqtnKkGOAZTPk+o+44beTlUFBXLU9I4MRbolpVZrshbMMuhtBT1LxLlRlnGLHm93gltcrIRWprOtzzdzWGVIvGo35H8LlDpqNKG93lbIwUDT743kMADfv/dVMDc5XJDNZhtS6LD2463UViw6wCU2xRYXGlyakqj07S9D2Jm08Xuyc32pzSkPMXLdODLbl7rqIsYNAuXgsXf/EQwerNJVvmvDyo8AgCv9GEKRAZdg6jey3tnQG1yIc5PduHJhH2AJMBb97IICzcGpVdkIn04zILmoG1mXk0ATVOm3dEYtEa86jACdOwBKgUKRi5ymLxVHoU2rN5KmN1Q7IErCxQmZlG9niuuqh/ya54vzR7HAc4REJg6TWJlTs1b8cn58ChOLyQd9ZbnOxo0Ic43d3dLtZXiQDhradi9tnCjK4/F8JtQJznp8akosisONOeRwJ0MbXepOp+t2OJwqmyig2mlgRifm09+G4494Fa626CMexo+ja1r2yBT/PUXmIsIQXUseNJB2RHUr1hbAlZbwkq+WHMw9UPQf1Vq+DdR3Ie/vg0QvL9l+wgY9BW484dezG2165NV6Rwpsa90qOdrDfpel6OfEBx2Z0TcFRU/sQ+VZFTyqGqoZv+OtE96iz3rOZ3OgVpLNp1YRvvS4jlJYAC5CfRpkIACMerexf/6QlgKuJ2DjcrGklcDTrbsjZSXIr+jCef1ZYGw4DOOcmiL0GXsMtX120V7sZQWbwsGHF+jMicXUBfxsxAvxRfJ+oq6trTYdWmcYQX10AMvRAl4yt3ZAaf9YMCB0a28kFcPrFZ5B26h32m+nuVFHV7bS0ea81HvE56m/cTBnU5WJWtpSmhmp/bYzP1cMh+Hu2HzvYGnZN6Ma/Xn30oE0GlPOUfqFpXvCoJvgoKdZnSNFRZn6i1p1ZG4f1F482WqeMJP/TRLJFiYzwHiP1Zwo+XNa5HSKvEwACV0gkT5sOQy8yF9+tBvfg9LeKrXQ2ZGQE2fdhCN+2qjxB1ZROVqZMWUEQ1imzcR7oIesgTfcdUbctx+l1AzzDugiEIV+9OCvKjU+yYPoZb01c0PXm/7KvfgcAdo1KMv7joxTIWJBrMh8ZD8GbWIU+YkLUx2udZ2VpNzHvsFhpAAILPfTav3+mu+gVFV7m8z6EfSjmuXh+Efged/e0ter6KmyVj6ve7QyHeFbvXDINrc73mudJ4W74mmAdfVmaGXcYy4Ehr91sea0UGyl/21bzifLLWgr1O0SII9gUz+f/21EIW8z3LSmG5a4Ev7F7OjMQ2yykIZ007bb9BUT+h55wdWBVA2OsRHT8TwtjdBHIYppVT2CyL6Sr3FOxzlnvSptMLeIx4mnI0MHDEwKrQBdDXkiH5QVLHBmJOG5U5QkVo4lRmuoF+jbsPd8z1C9p99k4qSo8nm2OFgr4rMPjBlQgYdAcKZi9rNebEdWRyT3Of2p4csw9PxQliB0D60ytlRqSQL7zrUr9yfIWhQuePtYLZrTrX0jHg3yRw6OFvkr+PHIMXOJB/xqNCBunW/04W+UfFEK6A/Q82rsY9qSNZL7Q8j7Q84zzqDmd8GiS8QUhH0pWfw5493IL+DZJ18SpUbasDEnaX83/bp+7I28qSUverJM7Do8ebLxCRpu9cdcjwJeQ/xlc9xsrjGBxEkrWKcmwU8rK9kanNeXgl/35NMWumRHnNaxl6IRBF2wgx2oiliJNLXrsO7nYlGxOuNeMW8oBRG6vJvArzT3TpJCM5mxlyGeIXpkPXf29eO3tMez4Frg71X5TwNdIFsb4sH9XSA+G+UxTtnVHONcL8STD0L0R1wEPIAhMknC+H6X6yG5W3D0g3CPO/hMRwkE7+L5GK1XE9/fpGI/bkQff83EY9cF8Nasu07n9xgwD22ZDHz/UxyqQD22e3J5RCXP2xDolOwdxTP4jfQJ7hJr++7kXOk3XazW8TVsOeg1wzSkZcDdMnXWNBW33+fT6YniNldaFdpOBH4xB+sz6hNGAFQ2WNdRqwNPixzGz/IOhOEhI3gLeM+xHM8Nv+gnKE68dzDyDjRHsOyDT2P5GtKWqh73fQvBYlXM2+uHkaVQgaCPZjrMn01BAisaVl5jKScWd16xhXy3UqWmBB+QhcNM/N7TIQM9tFHH7po49V8I70/Q9773sOc22Tls6j86Rp6YaxGMqtlmkvZpHAHlfPFAMBkvpgdUtKx05fsmu3J/NgGKwOZ06OIG96W9gx2r88MBa4Gy9nt6+1YeeWBuqfZ3gnlEiKdlFu6tNER4gTs2nNmcj5iZ+9/yKJxLtfrEqWznnk0tseikc8JdxtxFPmqVruAt4iz7ZC/z4YrAYX5CmOHoZDfjUKR9JWTxI1zXDtsqjvDxV/PiEIpy6UL0UO/pVWbcoI3X6dZ1gvXARTL5rkGevmK9df0M7e1ly8nKBo73T7blOn7zQnnuUYlNqgpJEtS+5Ft3qefxqksEe2M+d/gF597UuFSXr2/tfHLHIIpZsMCkfq4Orfd1bJi6jdV+BfsTXydo9eBuRp/BpD2yCXB0rPn99tw1463aEfgcjV711bs2fqrjAWt+bnSqSmrXbgcYP/+aoA8sVngLTwEKb+wW276absYRQwhPvBcXXEHOGm7zCl3TFm/RqmcpulpMh/yK/6yiOLdjkSnXC2W5A2G0N9ZaONwJaJprxtZu8h1HZAWpJIEX5vUz0rL3Kl2ewSFPkgLLk1Rz+cDukQgTws+i2NHf+RBidKofcvUV+WhbFnn/CP/8KLM6u6KJvwDKT6V43/fBAyxRC9AMMI3CBvyVEJNuEVOHTy7iNmi9awDjB+vh2QAjDExg/9S29iG3Xacu1Sb4+yXoGtB0UMpEL1m39gtLwRS+1cJJU2zW5as3hdgDSzKYhRFhew6hfkAisIAyz7Tf66csSzi4EGZKIr6cpftGM+3IglMVT/Ig3+fTwxewe0YHZRisgZxAu0OGu5fcaskc+DReNh+vj2e9V+7Yigd1lI/7+uvxV6QzT13Ux9FTCQYRbkyvG/iuz8ieTc7Kl9hW1FfS1d4q2tLnoccT3hZfp4/n1/PnzcfeW7bnwEKigzxSbY6IuCCIUV6cKWo7lpYQ72IVcjRx/v1YMISWoTZvP7nWfskzVrijY4MbxUxU4/HvXEdvFlFdyIc+dc7kXM/maBpTXlyjT1guXJtZBlHU9q1nBtRrMc6i4bCuaQYhVEb+IcTahF84Y/K8gkOosV2BFr3kkQZk1n5BRcTE1dSjqpCWCAcpUJYoz6J+Vr9c7LOjBVxO5xmOZakcf7TOlXKCbZiFfC9qFRvK4fL66+1DehuZFrgMkT3pzmgOpDHiFhSoGPociT3hzmgM5BK0maxNfJt6xjihu2OAvQl6XSzRBukZZEY1wcS3mw6aW77eTW7b0o8P7fnnzCFXdIWgbBgE9WDiLEejxcEHKCqjlJA8j7kQQUEeakGOcQ5sDuA1LDgxqAgBx/RGLJQCh6eWbxE+Xf2PfPxwfnM/VlhmXHn0wR25zTFocl9RfhkSYVveHKacchS3HFpCe0p5FA06v2Isz1SDpu2K0FUV5ABvqMTP5K0S2gscLXf0BwQtWHB7f+qBEpDpaetBrEWj9r2Hy0plQbCq6cj8kmp/rNMPwSwR+UGODzpL1S1URc1E44VckHXYJkRlbBcuqLExrWiKzUNbekTLMM5B8L5cXbUw9wA/hGjJ7CmGvrXTMFFspvlQTO28VpNSvSZEeeOSCoZsRNa3qNkxHHfQKTHdHyEOwnZhBiUr1r83aVs4FYhFr0Wxw4kwVdb/6EDS2YNotqbAyqC02mk+A7DksmaANe74VHyCFghvSO/YAOopVVN3ZPGK4+XGCJwWcH1P+p5Pv7I73cffSemn3Noq3q5/O/NuZ3Lf6V/GMJF2Ra8nZ5gEqBGUGSGtoLsmC0UB1fU/7Hg7tTNQAgbpgQH5n91o4IB/baKw2RWezmje9aOUKsFaqJ5MYtBWLp+XvYvur9GA5m3Urx2GU9mM8a6Sr15Nn9xUtnpZl06/ZtYp12t6VIqyaVVF2RR07HMoVG7Z
*/