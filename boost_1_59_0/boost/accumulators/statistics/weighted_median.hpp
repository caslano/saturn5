///////////////////////////////////////////////////////////////////////////////
// weighted_median.hpp
//
//  Copyright 2006 Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEDIAN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MEDIAN_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/weighted_p_square_quantile.hpp>
#include <boost/accumulators/statistics/weighted_density.hpp>
#include <boost/accumulators/statistics/weighted_p_square_cumul_dist.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the \f$P^2\f$ quantile estimator

        The \f$P^2\f$ algorithm for weighted samples is invoked with a quantile probability of 0.5.
    */
    template<typename Sample>
    struct weighted_median_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        weighted_median_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return weighted_p_square_quantile_for_median(args);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // with_density_weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the density estimator

        The algorithm determines the bin in which the \f$0.5*cnt\f$-th sample lies, \f$cnt\f$ being
        the total number of samples. It returns the approximate horizontal position of this sample,
        based on a linear interpolation inside the bin.
    */
    template<typename Sample>
    struct with_density_weighted_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        with_density_weighted_median_impl(Args const &args)
          : sum(numeric::fdiv(args[sample | Sample()], (std::size_t)1))
          , is_dirty(true)
        {
        }

        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                std::size_t cnt = count(args);
                range_type histogram = weighted_density(args);
                typename range_type::iterator it = histogram.begin();
                while (this->sum < 0.5 * cnt)
                {
                    this->sum += it->second * cnt;
                    ++it;
                }
                --it;
                float_type over = numeric::fdiv(this->sum - 0.5 * cnt, it->second * cnt);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
            ar & is_dirty;
            ar & median;
        }

    private:
        mutable float_type sum;
        mutable bool is_dirty;
        mutable float_type median;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // with_p_square_cumulative_distribution_weighted_median_impl
    //
    /**
        @brief Median estimation for weighted samples based on the \f$P^2\f$ cumulative distribution estimator

        The algorithm determines the first (leftmost) bin with a height exceeding 0.5. It
        returns the approximate horizontal position of where the cumulative distribution
        equals 0.5, based on a linear interpolation inside the bin.
    */
    template<typename Sample, typename Weight>
    struct with_p_square_cumulative_distribution_weighted_median_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        typedef typename numeric::functional::fdiv<weighted_sample, std::size_t>::result_type float_type;
        typedef std::vector<std::pair<float_type, float_type> > histogram_type;
        typedef iterator_range<typename histogram_type::iterator> range_type;
        // for boost::result_of
        typedef float_type result_type;

        with_p_square_cumulative_distribution_weighted_median_impl(dont_care)
          : is_dirty(true)
        {
        }

        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                range_type histogram = weighted_p_square_cumulative_distribution(args);
                typename range_type::iterator it = histogram.begin();
                while (it->second < 0.5)
                {
                    ++it;
                }
                float_type over = numeric::fdiv(it->second - 0.5, it->second - (it - 1)->second);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }
        
        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & is_dirty;
            ar & median;
        }

    private:
        mutable bool is_dirty;
        mutable float_type median;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_median
// tag::with_density_weighted_median
// tag::with_p_square_cumulative_distribution_weighted_median
//
namespace tag
{
    struct weighted_median
      : depends_on<weighted_p_square_quantile_for_median>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_median_impl<mpl::_1> impl;
    };
    struct with_density_weighted_median
      : depends_on<count, weighted_density>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_density_weighted_median_impl<mpl::_1> impl;
    };
    struct with_p_square_cumulative_distribution_weighted_median
      : depends_on<weighted_p_square_cumulative_distribution>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::with_p_square_cumulative_distribution_weighted_median_impl<mpl::_1, mpl::_2> impl;
    };

}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_median
//
namespace extract
{
    extractor<tag::median> const weighted_median = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_median)
}

using extract::weighted_median;
// weighted_median(with_p_square_quantile) -> weighted_median
template<>
struct as_feature<tag::weighted_median(with_p_square_quantile)>
{
    typedef tag::weighted_median type;
};

// weighted_median(with_density) -> with_density_weighted_median
template<>
struct as_feature<tag::weighted_median(with_density)>
{
    typedef tag::with_density_weighted_median type;
};

// weighted_median(with_p_square_cumulative_distribution) -> with_p_square_cumulative_distribution_weighted_median
template<>
struct as_feature<tag::weighted_median(with_p_square_cumulative_distribution)>
{
    typedef tag::with_p_square_cumulative_distribution_weighted_median type;
};

}} // namespace boost::accumulators

#endif

/* weighted_median.hpp
YPFO35Gj224YlbCBkpto9PNwiq1WI8Lsk+0Kh/Cll+YCxzHyflND6UnCXIdGN5o5mTSnrzsrTVupm6DZUnTHT94RjjtQa9Gc13FVOi8TSp2kBhYLm2kM6WMWpmHtDI++xUY6tSoNn74nF7oFnXZbF+UlyHljM2VmVqnhFI3tLGld643I04ktmAnfn/S1gip38MLR2OyUnAksHonvE+S/F8woL35pyKPnrEyKfn/cJ1FYVD/aIEw/IhC+NNNfu89KqynxRlPh18+VEr+nfyi0ADcrJzeiT6MIZvGVvtI7gZXGwZiSZSu4pIx1O6divOG0dLxBJJ6wdNw4Vs1sOmsuzVjdhXJdNyucsGrc+2goPs2LkCjt0XypXbKOxe10dNjb3UttL1GBP+viIZsKldDjpvYhq811wM7PXdL7ioyOkMSEV/2EXHqFyrp6yXfdNaXBhz7XV4ho4/XoruoUM6Pxcx8VcjiKzDsJ45Rgt82q5FQ9gRoj0dvMRwI6KMZFA+G5xmtee2jdttzvyvzqoihveqGOoluK1PfYOYgflwzKnIcIik8ikKvJr2QMXSGJCaTxFYarBvsILJKrYti6X3vJC/0cRT+W0ErxKe5osLQwGrjv7b0yQc7iePzjPwdz/MvALSwszGxsrKz/u06aQGIsnABmVtZfTpr/y4FbAJz/0UmT6x+cNAEcf/PSZOZmExXmYOHgYubmZhMXk+DmEhdhFZYQFQWwAoTZhVl+BW4R5uIWk2DhEGMX5QS+L5c4myizMKsEsziwiQiHuOh/6qXJyfJf8dLcAAEFSwEBBWcEHs0goJCoIKDvnEFAYfZBQGHrQUDhTkFA4YdAQLlggUfrf+bBCWBjZ2H5N3LhZAMQs3L/gwunpKOdi/0vF7vfPPaYZP+SqDB9cDSwdbL/5ctp5PGXTn6rKSDwZ6fP34n+7zt9snFw/6v//E4ei1EBwCzdQ4wwPKMF4LFt27Zt27Ztzze2bdu2bb1j27bv/Mlt8my6atKe9HTVsC+nj2KC3ErSPVdbL/QywUpkPrdBCiM+bIvOG3AHDmWBHCMGlBLrbKehqXWxokfBbAiA8LdkGfdZ6w5+DjBenc53AYOEpEbRjSUUxaBXa1RU4RDvI7rx/gFMxA9RI12DkSY0cOzChkhocn/YGPKRiaa6IzUxtneEkqY5e9xLodXyiK6JRwGVIlBLgqzWOC3RHzrFGZroWq93h8oxUv1GrdOoDOIlmE/mr1GvcDzCvtOY3BXhxBQgR1O6/6rvA3npGaxa6xB95/G7neJ82g7KeRjgXHkm80bGL6KkhMyOY7V6oLAFXIyHRhLbjSyOWcAaJH9gzsNxQ9eo/gnNKxo5NriYWV5CD/SyLH4LabXGWau9CMSKy8zJjJ04cqyTkuFLHhT/c8QUP4UKjnc8SXyXNjyo8TEOHo+cQuSyLGo8Z6xb6V0sBMUjwZr4xNwFQpTNsswWpdOopInozviIqMywtoEEbjpk7bVqShpiX768oNpynXRtWr0tt4mW0daWS6CJDrwGLVaqo7A7ZYU41KdMyFJHUEZW6IeOxY0EJlTpkQJn2WFRmm0bjV6pZeXYLBI3Y0PSMt/sTAHktByUhN3vxd/ETXW45ursN/Jwifmp6ZEKSKse9r+HBdVr/F5eVt4I/XZ3T/c/dvtQlBPVfCfOqS8KCWjZCvN34T5+23XgPv66deP+JoYBwd6ri9Wu3pKhcgKTU+vrSvnSfzgoBCp4T0JHn61TgNvzf1gLBAj7moFOgcAEQQH6kqer7OsmIVSUyJ+fV/25WnL172Hcf/UuuSO1pyfDp6qx+FCvE27uDOPeJn8305k5/bSkSppKis2i0W79GHskMpmZR4yGziDdCpdSnfJPoFUrkARSGrXXSGPG3akoMsRicM01JeQdwXQW/LIQ17Q/KI/I7dSdM44IOsBqWcUa7c8o11wVwif07kgegfutkB2UFC/OpGnnzJfPLy8heE+n4x6dpxJyHeM7Dqwyac2YaRgatrRSmRUs5QVzxcX6pjSlF+spnEzi7o4sjXK+fedvbwr4dfdab2xw/kVW/LBPxNvqk/gLCzyIghjBgL8oMKE4GCCwnvDP9vZuto3igibMvATAoBRcsX9qwdipvn/ef9r1TsaLaq1yVnheJZBpmpUTATg5TxyFh5JhRSPNlmglI82aX7HePFBQQspDpPJHqBmypHk+P49leVqBGM3LQQuU3zhaa2ErH0IZ6B+8FBr37rKWL5oH2EvwQI/M0Rb6G7lPCEVRjS2Wqq566YH5CAAwqD2yz+VT24Bb2uVsWZRPxU7X5b6saDhLjemHhDGmpAOfl35AIA5qlVAMyNd1OzxWsojnVOffvRW8RIT3FPtspSgxeconhAZka9hXQaMUhYW2dxF1Jd8kmTZNHEumeQ69wQkNxLdrJ4dlX0O5fJ+sYrw098ZUk3cjKSkPeHC1o/AkamfN/QsRv3Liympurf74hJ8tIgE/66soOCgwB6tIojDJjHtgP+SYwoKkgOAC8VgQ1N+avXildJfu/3Uo1QhJtwhvHak5Hhfqe/tdg0cdcBjFLRjKPXutnHUk+dZunz2ob7ngX65nGC8dFL7v+9VeEBH7PJ9HYXQOVVRIxgPcOXZIXxN1pgQN49MyXcwoq+zmJFYywVUae+O3ymfhN4P5eXBv1fAs2W66O3lWtB+/jkAF/AcBevUItrmO6pPS7v3hmoAPdAkPBAQW7olvmiwR2sN8UJ3S97LJ/QUdt/pbZDz3w05+6B8FCgbB7x9IvocE1Myc/9vaLxAQ8GsZIBggQApYTwXJnd9EUfStCVBLWRfJHjg6XveRyV73GbAK6IDRDX7P4/sgfwSlTspXzqqGAeSoZtG9IohlST3q4AsV4s955J8oY9qV1vmQL2vAABfuYYNGuwwSqHro/l+l+NlHGjxDRIEJV0a0mrxs+bBGGwm/Iz5qof61ZSuSQal8DZe/DEBuNHRVo9eBRv7wevvBcvggIwweShlU8H+yISr+xSeLerEyMX71h6kdTcyu2UPY6jfjGpPVsc8y01wlleQQ1AXf9VY8TfO+g3M1Ot2yGduQtgaEyLIhQ26bmASiwLKZsfSqsf+wFR9lbPlSuKv0hHagUnYHZBknYh05ht8kIaM1qKWg9aAFobPXMIgOpB0pdR+Ksxu5dO28DFGbftw9To6Ryjch/pOKN8effTzZqCw0LSVg7eI5Ub7BSVtRZIn7dg7gqQeRxrukVA9iwtrcy4sgv/xFnvslz/3tPZh48acVAb7si/P4SUKA/W15Y0o6310WEKif1CneSfBfAgBcoM0hJpMLXgAHfKZ538N/yx3EB3mgkH5vSw38jd6++iV1m8Lk4M5CsAacmdDHz/2hnk5zYbl7I9fn+xn17981mv9yfumixz43FkZ7w3ZT19LSWPDHNzfCgvs3xdyc3CIp/3mxJBV6hL3oxe1s4+JNrIzzAPceBJa7PztNkxufHODiI1a2vCV3Hs8E0nmOXP398NWeKlehwX5ZhYX/HTefKz7vEy4wEZdHGFIEnJK+G/RfOI8h2G+ZPumveOutv/4eVO1vRz9q9i9Ge+CzfgjJG2p7YRomnwhh2mp2Fx53k4JKKog3B+V/P5IuofVdbJ5uToqDgE0jYbpeFPjT4Xdbp+ARUaJuo2TWGdoyyooq4ErRoiBVK20YFIVbkZJx0W0k/4RyDl7FLORvdRBiRYosaoGHyus9PIF4Y0jkez/DVKcWW8wqeI5Hop6CWAUk3ea9geBOCwNpP4+KFthe3Cf25wbJKRT+TWJmGXJ6LCJbeVPuE+pIQFlxh804s+vjn5LocOlxnLXVCky4zm9Pk9WpGDO/sQUybBNT15AgXc/NzMhIZ0HCyutWu/XLZ5kCeEbOzOt+XLYu/HLc6fzSqIGO4TdQrXEC+ONXAfXfi1dDqaG9+CNVBQYFfbdp9x1IMv2KXckPULX/4lQf8I+v/RJogELHn93+zbT/PBqgAtz0JYHc+EdLj82OzD63GaBuTdtUZ/9eJJmCP5m73FvXqgLPVeV6rJhN3C/fM2PH76W0wkX6GhlpWLTd4IUx0BRQ2OzvRM5RVIfyjGNMfxyG9iAYeP8gblG4H1umgBRMvLbx2eti28etn+oRpJrWkJIek9b0sTEnkhxZ+ntFTiva8OkP0U78c7ThuIH9d95zXHGdh592MrQehP2WUCsjzk+1omtCxbIbupUOeqtiyu6X4Z6k29EnbNrRj74eUDGGtdr9tl9/d31cQPu29P4D/sGS16ZhjZV4u44ygFEE48LCd+qLHIwyGoLQRuhNhLQp9FzoaD4f9iCn0bSuTr0oTO8ItO+Y1Y1R+cykZEsFhcL95rB0KvNviwxskyI0m6QBPPLyItO1g3z9U9SDxFrQEclJw8q5idFvFnMwKGGPgfYGfDf2QqiRDUIrkXxIfAewMeJ2IzZ63ZVkpFg3dOd33ILGBtbnV1M0jJg8qWZ9I5lXVldSU1qLT2D9fWy1rgFW5cjyqN6HlELQpthJiVIzwAcjlXl/sR3yO4RFKRLFvVvaLs8kpdeyrGgPY2h31MfsJiSXgifJVT28Kbc1t+6/YGylnVcYh0XOf2qneunY7g0NCP7DdcwOzwwBmhsLswW1pXWl6XuaErgNVEW4w9h9ywUrCI7HmgoIUv1rBZv+XpDVWW7dkS5elGMtqu8FtkZ6PMJrNxhmFrvloqIot0+cv0a3cs9a2IZCz2pdufI9dSVvFpH6uDVcWpFWXEhGECApkTYIgaRclIBqmmq5Vvx8nmErCdWk1g6pDTH2sy4Z1CZprNJta4vSUiXc0JrwDzgiQeMi8P9mPTVfVk6StBt6LuVdNrnmbe5UF9/sYT5HxNHijtAD5LVyAMOQ0WHa92ZfbrIRhKdP2pSIJHuZAlWcsUwnUgcB3k08I+FriGogp2MiQRKP6Fx5LG2ooCqhVIydn5ueF13aNto2lqy4RjqVpkoqSrLLOWug6PfZcWo8vvaxg6rVlZLgH+EpuTGRz5HvHeMC4gz2R6+GUh/eM2Ge8ZGDg4h5MklKEc7BF0pjypTtxoWiGxxJopAXoyGlKaWRsoNxlA9rQh0ulcyQh0Ln3XguCjdNdQ/Jn+x3RBBQh5bC+sCXtpd2loadeN8yScAQKZ3u/JZ1gbwRxkldOu4w2YSu/j1qXAsWqu0BoU0Z2CsltEOQvcO9bi1R3PG93RwIQJ884Np73Tgpf7ro3qMifcgzO/JCXEUK26u03doIkZcgWai3BaEiUl6E+uzJP+ACs+kMvN50WoG6tdjZ7zqKZqiwIrKX64Zt/fJ8k4lajdmeavuOEDaJx7NcZLJsiOW43fIvMH4lcYFLJiRQ6G+yqm+y6ssIkHyBtEsH50GEeedJXOeTwqYqjMlTJJ6ghLtChXjjS13Pk8LSKYxtUiZ6USbYHUW5/gTD1RHQ4k9ueD4XRfCrE31XSFClU59Qo/3gRH+0o/CPi+DWlZkcUXM94STdQcg56ioB3E099lLfiU0vi02vik0jS+dDvs45E8zlySF9xifeWa6RfUU1wlhmJDdrNEJVKjHVJ+cAiT6TI7+j9og7dZVb52uQRxj4oLsKWmtCevLRyb6hK2MqSbPuISaTsGFvkLB5A8mQ/ne80P+CGXL0juO0aMRW2mjEtg6ZlypJqYAlaxJttmwR2qtSSUJRQ3OAxjIBK7kRrKs5rAcL2cbBbuvTPrPkpmJEomBComA0reTmU13aXlkcZV4cW1cY21YSy18US14cOxeL+DiN/EiD4D2J6j2J3qVE8pxCMpJM+CoeAniSLCGZWIx2WEJAoTAyZC8yZE9S5PiF3D5WxgeuUAapXBZA2lNW1l/BmdFiawa6CmgKG1/K+p8qyx5Dmm3MYZTyXDSRLI71TcYoFStVIbZrlHWOHq/yFhnfKmW10SYAvXZxB7qCmjz5gdQiJzJtdSBCOQsELyJpDgkRNok5YN2dyZ5c8anLZ+b5Ribl3rgv1JZuhzxuu68cTt74WKjavtkz9q6uayT+hM5j6EJoa94Yfwcjz8yGTMa6GFS75XZw9RFzjeHHFRuuBmuUvY+pxo491392aOg2ph5YjYIRD5pwXcAhdGZtiUV8eEf7jkDtm1ZQ8P2+AV9AC8s9hS3vTgvIOl2CBu+SaAMl//5L8GWFL9yessBa7pL341GM194/Dr5lUjqW7DEZq62oIDNHFpOuimx+SEmYTfgN+OZTtAsD1J6v80Yw2HdR6bfHC9Og8ALIUvSbYLtMJJ3sq+FRlHEOq2rvZ55KuOhQa7bTn5Rk8CEndk8jUq+rX+bactotdhWJ7/QpDddv35szc5otqh+ff/CseLhkmnF1m/AmXzKDhqnD8L5IDY99fM8C0MwDNtWznULSzMM9ZrOdMltXBrcaP+1J1juLDanfE0Qol5tnSw+Lxf2MvYOLJ9Ieks3M7ODYLSHMYdzeW+5ALjqhAhWVWWs1wC0v65xnxYgM4aq7u2du+hyej7ySqixB3i/1YFMu9gqdkS4DVNNeiytcBNx8JaO+BPLRc6jSH1rp17UJqmN6H4MseFZYM3IlwJWUz9cJghpMj/ueQztXsL6Q59F9pwWzieFEvkEB/4cUPS1Mmu/AVFjx4FPg8eEuW0sg7op5NWf14jloR8ihDWdeQImHhuNpWwOSmOPWvCmU7ag9OMiDMPfZUwui5h//RgQ1eiJTrGfMU/Sx6CJ6FqNqn8avxjf16eQWYguDYIvHH+nV9GEK9XJsw6y7yTPlavbuCv1D0JnrceSz4kXqAe1BbA+7+j0AGn+BGvWLghkti41Va5L+ntHNQdTwyivghCLNqh+I10SS3SK/ThgqLZjFQYo0VH9Wlc5mitro1X4RFweHq59CxVDjJQ9L3Vc5Jyb2K1CBelpkG8lwGfIZ4Lh+Ubso1xo7smntrflBbZFE77RKPqC3+1acGjkwryqq7TTrUTMwud0V5Qpo98xs1BbcOtCCKyRemromQ3WGa2+3+KlyRigQpcJ2LLI1DlerqHCd/Fno2PCcQOnhe71Y2TKzYx7IKKY8+1FfkpAVLb6k6eM7PefrHSkXsvWd8fGAQ2pZXTT5bBCyo3FBWxbLjf4Gbqh67QI23LWeJIGL58Yq0WuuEvC5ulO8+hwnbaT9qS63X78UyHmyw+GFNNtLouu4NhfaCyCAR04cctI0LQj/jyTHy+iM5FKou4VeS51jM+4EmpaSWP+slqD1v6sVmNb45xWGVoLBVo1WBl36X7BfG9qQOKLTLyP8kAQbSurH+vByG6cKJwnbBw7ncTl8kzzK0qauj+fxdvLLa4UIu1kd5L23PEF4Qa5cRbjd+z4AlgtyvFdozd3F7yMteq7uDDjD910IuM9bel8oz92D3WKeb8acibeQBZ5DV9jvhhAeYmCYCPgJgxEB+HODEcnQfnn+AshMaVArDL9BNMCpkne6kC2DQD4Q3BhiysSpXIqQGTMx7Bv/NMrUPOppKlqIeawSn/PDpfRAcblZ+f4yKmTzsYJRGHT22EOlmeQAVCtscnCZFRRUIvbsPWrh4i6kUHDWcwhRCPsyEqH0uoFGg6Z1xb3/aLsG9voPOg/3BHxdwoYFZdzH+gF1f7AQQRG3c5FA1dZzcUFZV/DwQb0qaVfxMbRE
*/