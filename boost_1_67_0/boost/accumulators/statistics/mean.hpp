///////////////////////////////////////////////////////////////////////////////
// mean.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MEAN_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_MEAN_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/sum.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // mean_impl
    //      lazy, by default
    template<typename Sample, typename SumFeature>
    struct mean_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<SumFeature> sum;
            return numeric::fdiv(sum(args), count(args));
        }

        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

    template<typename Sample, typename Tag>
    struct immediate_mean_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        template<typename Args>
        immediate_mean_impl(Args const &args)
          : mean(numeric::fdiv(args[sample | Sample()], numeric::one<std::size_t>::value))
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);
            this->mean = numeric::fdiv(
                (this->mean * (cnt - 1)) + args[parameter::keyword<Tag>::get()]
              , cnt
            );
        }

        result_type result(dont_care) const
        {
            return this->mean;
        }

        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & mean;
        }

    private:
        result_type mean;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::mean
// tag::immediate_mean
// tag::mean_of_weights
// tag::immediate_mean_of_weights
// tag::mean_of_variates
// tag::immediate_mean_of_variates
//
namespace tag
{
    struct mean
      : depends_on<count, sum>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::mean_impl<mpl::_1, sum> impl;
    };
    struct immediate_mean
      : depends_on<count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_mean_impl<mpl::_1, tag::sample> impl;
    };
    struct mean_of_weights
      : depends_on<count, sum_of_weights>
    {
        typedef mpl::true_ is_weight_accumulator;
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::mean_impl<mpl::_2, sum_of_weights> impl;
    };
    struct immediate_mean_of_weights
      : depends_on<count>
    {
        typedef mpl::true_ is_weight_accumulator;
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_mean_impl<mpl::_2, tag::weight> impl;
    };
    template<typename VariateType, typename VariateTag>
    struct mean_of_variates
      : depends_on<count, sum_of_variates<VariateType, VariateTag> >
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::mean_impl<VariateType, sum_of_variates<VariateType, VariateTag> > > impl;
    };
    template<typename VariateType, typename VariateTag>
    struct immediate_mean_of_variates
      : depends_on<count>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::immediate_mean_impl<VariateType, VariateTag> > impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::mean
// extract::mean_of_weights
// extract::mean_of_variates
//
namespace extract
{
    extractor<tag::mean> const mean = {};
    extractor<tag::mean_of_weights> const mean_of_weights = {};
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, mean_of_variates, (typename)(typename))

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(mean)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(mean_of_weights)
}

using extract::mean;
using extract::mean_of_weights;
using extract::mean_of_variates;

// mean(lazy) -> mean
template<>
struct as_feature<tag::mean(lazy)>
{
    typedef tag::mean type;
};

// mean(immediate) -> immediate_mean
template<>
struct as_feature<tag::mean(immediate)>
{
    typedef tag::immediate_mean type;
};

// mean_of_weights(lazy) -> mean_of_weights
template<>
struct as_feature<tag::mean_of_weights(lazy)>
{
    typedef tag::mean_of_weights type;
};

// mean_of_weights(immediate) -> immediate_mean_of_weights
template<>
struct as_feature<tag::mean_of_weights(immediate)>
{
    typedef tag::immediate_mean_of_weights type;
};

// mean_of_variates<VariateType, VariateTag>(lazy) -> mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::mean_of_variates<VariateType, VariateTag>(lazy)>
{
    typedef tag::mean_of_variates<VariateType, VariateTag> type;
};

// mean_of_variates<VariateType, VariateTag>(immediate) -> immediate_mean_of_variates<VariateType, VariateTag>
template<typename VariateType, typename VariateTag>
struct as_feature<tag::mean_of_variates<VariateType, VariateTag>(immediate)>
{
    typedef tag::immediate_mean_of_variates<VariateType, VariateTag> type;
};

// for the purposes of feature-based dependency resolution,
// immediate_mean provides the same feature as mean
template<>
struct feature_of<tag::immediate_mean>
  : feature_of<tag::mean>
{
};

// for the purposes of feature-based dependency resolution,
// immediate_mean provides the same feature as mean
template<>
struct feature_of<tag::immediate_mean_of_weights>
  : feature_of<tag::mean_of_weights>
{
};

// for the purposes of feature-based dependency resolution,
// immediate_mean provides the same feature as mean
template<typename VariateType, typename VariateTag>
struct feature_of<tag::immediate_mean_of_variates<VariateType, VariateTag> >
  : feature_of<tag::mean_of_variates<VariateType, VariateTag> >
{
};

// So that mean can be automatically substituted with
// weighted_mean when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::mean>
{
    typedef tag::weighted_mean type;
};

template<>
struct feature_of<tag::weighted_mean>
  : feature_of<tag::mean>
{};

// So that immediate_mean can be automatically substituted with
// immediate_weighted_mean when the weight parameter is non-void.
template<>
struct as_weighted_feature<tag::immediate_mean>
{
    typedef tag::immediate_weighted_mean type;
};

template<>
struct feature_of<tag::immediate_weighted_mean>
  : feature_of<tag::immediate_mean>
{};

// So that mean_of_weights<> can be automatically substituted with
// weighted_mean_of_variates<> when the weight parameter is non-void.
template<typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::mean_of_variates<VariateType, VariateTag> >
{
    typedef tag::weighted_mean_of_variates<VariateType, VariateTag> type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_mean_of_variates<VariateType, VariateTag> >
  : feature_of<tag::mean_of_variates<VariateType, VariateTag> >
{
};

// So that immediate_mean_of_weights<> can be automatically substituted with
// immediate_weighted_mean_of_variates<> when the weight parameter is non-void.
template<typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::immediate_mean_of_variates<VariateType, VariateTag> >
{
    typedef tag::immediate_weighted_mean_of_variates<VariateType, VariateTag> type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::immediate_weighted_mean_of_variates<VariateType, VariateTag> >
  : feature_of<tag::immediate_mean_of_variates<VariateType, VariateTag> >
{
};

////////////////////////////////////////////////////////////////////////////
//// droppable_accumulator<mean_impl>
////  need to specialize droppable lazy mean to cache the result at the
////  point the accumulator is dropped.
///// INTERNAL ONLY
/////
//template<typename Sample, typename SumFeature>
//struct droppable_accumulator<impl::mean_impl<Sample, SumFeature> >
//  : droppable_accumulator_base<
//        with_cached_result<impl::mean_impl<Sample, SumFeature> >
//    >
//{
//    template<typename Args>
//    droppable_accumulator(Args const &args)
//      : droppable_accumulator::base(args)
//    {
//    }
//};

}} // namespace boost::accumulators

#endif

/* mean.hpp
CJfiIH/hHYidv9reHYQd2h08U3st2prJGv0uY0UeQmlMbTWBb9N9FRij9CGwGGSM7y+KETkU7uY+dSxKK/8556Tpd6WR0pkR5OhM0pig8cK/AZLIwiG22N2yQ+On+54KlmjboMi6n6aERnlyWVlFmRvG5cQEveqMBNKTDXkCdagNVDEhIn6EgYbYjnRqQl2FPHa85LtBzwt1S0ZbUs8FyEgKD5EdaaJ6GEvq9SHM0x1ErYsdU+j6Sm8Ba5pzi8mrowzQEoe4DXk2NbkNFD/tDos0Zs9Hk5LIpu0nUObzfwI93RSr86AtmtnlZySFO+vGV5FMlXFBVmTVU7Rt8kGeGAXCYbwxOgQTvhSRmBkTYCFpCrOVcB6tdHtycPR7XArFrdYjOUqMoeV85Q6LgiYEMRv0LwByhOIwAllk7uzAemfdtl9NzgM2v0rg7Smza3j/EUk1vILWFCBRAhm0VWnfWUlyUCYFKHOOgiuJuD7xKiK2SMqecg9AuUOHi+ZMHkBBqqFLtsnrKaTt/DGjJGSZk15e2PJhIwNy8l0bx+dv+O5WO30fN6Dn3NHk5wRZp1gtv254bFtzUpzykf8FZ8IsFS8itsmY9qOIv0DbP0nudfEXXAjXS/ycxfs1upYNBOIyXLwu2jq91w0IT4pBLekla4aZVKc71t8mvxw9P8PCmXqVoHEEnMrPQ/XqIT+VwQb2ViIm8ABgpAltQkmuB0iccdHaouHXh1TcnkS9LvI7vWcNCD3GzxbpevVKnxxzwIWK9wOnOyZeF3WdPLZZW9UOga0t9xurv6UcLjutUHr9Fs/fjPBhwVZ1eGAr8cOGL14fMdKd/hCZSxEPpf5Q/RlUSWcbiNmxI9qsFm69+4PzrW3fRiXk8UJwpxb0qSFKmx9n8H9GvWrh6v4jun26AHFj2+dAF+VchJXaxg69XAB5a07S54jcFvsJgp9m+zQ7uNMNqnx6rL+12cFCwsFjTwV/sbHmXZAlYpBlpPFfcLaMnNerbBG8xf4mFM5ONH6mDBmOxKc+WtCPiu1SZp0JxuVJGRg4Oz/nF3hCRev9R5di+xyBRwAKNT74X91Q1Pj8AYqDcwS+f3WB5wi8AmKo8Qn/6vajxtcNUByfI/D/q7tzHsEjQI4aH/Gv7nfU+LIBisPzCL7/5lpnhtfm9xX4o1rwpWwVQKFiu5cliIcR0e8oo6LlDQzsn5/zCvj/q8tKRDzNc8u7u74f45bHMR3wT8JSnZCztKNEtqqlFvPYrttDId15uHkGf6lHfRTd//gjKkWc7291rRmGHJXuOn/L6yf88nV1Edw6kno0Nt9jUjQ/t2Ff8qkf+BM96jxskEcwBVUdti2qBhqG3KXfS+Sr9dQdMJtH13xorGAeVQv6Yb4iBSdH8gTjrZ0N3DwmaNG7v8NbwhPSNysSGwquF8LcmhzkbngYXPWv3xrcLHORIXNM0Viaoq2tMnSnnPuU+G109tNXavaP9QXUPRGRKFz1Pyx1edoO2OpDqLlm41Fg5ojk3LTk5lJw3HzlGDxGq5YTiZgeiRpkOTj0qY5vPdLrODI7ZXmwuVkEJUs6mfWQ1z1W8Kf0qQBMTpoPtwKCHoxUzYWah9/V7j07WbdKCErBOWkfmQX5YmdWHPr27TtU6IWnWlRAKjLNgwXZAtXAiOz4eZbUIk9qtWbLVHOkdgGOQkq1w70MVRbetPmJeKrrJPnydCvZbiCeKsurXy4XcLRTg6eIbzBRLEw81rXMdh+kIpVbIwToUMmoNczJYKNXw1nIaMDzYNRRJ5HDKWS3UMmhi1YZSZC4ZjM3yQLMTztdowOmmwlSx5vHJD1r5iIkF6So1GaWJ9+2opFpBbdL9U61Q5jwCq9Vjl/SYddSo4hSmZpBX7Kdi1KvpXR5fx1oLpJsjCNK6eoEFaVixtlaPKtUZx8rR+doKgqp/tqhKDRztXVnVDxZ0wusreWJa4NxoTc9Gsh5T3L65c6ZZjCcn0xoHfHil2IEmpeYfxvmzj+lerzria5vPxsBWRCucnU6IGjwOA69NuhaTtsAsJofbtOcWRii/HRU1jujdjY1sG4rvrdpYQ91V9CeJg6d3+MJkQwIVuGdmvwi1oC4LYNqk8LuE6yAOBWFdUajV/7y5MwyjiuzYFZyO+3sRK2cFKex20APjOP9giFFE8c4JYaI79vKLb+wmL1EYGmrHBo158FvQsRRZrTtYn30LjNuCCdtaZ4OR7Cyowdu4F7URcXGwaK8o8z91w5v8aUSS6rtfrqmJrO9vznEDXM1XU7IT9+Y4V1HEwQvZHGTdy5hLoJEnlIC/W22qJ0UxCb6BOEbLrWszDYDp++18HBrfiXwY6aXmtyCP8Yw/Kzzo/ownGq9TCSC0AmNYOIFQRZjN1/nF/vBs1Zl4BRCDA9ax8SLlOEY1TxsI6SKFa6h/1REc5loFKnzLfHur2AdfwK2J3xDP14GUqf4b5NW4rANX6wf3zSK+ojmWZzhr5HXh+qdKE61ZQaJGCLbzKjQj68j+DUxXEZkyd+CMNdkO3Gpn9brk/4Ef/xXKa8qytAo7L+X+hPM95RYJ6uO4C/CdglvIi/zQm/dlFA+Iz9FkIZpZsBws/qOKhG1nlFGl2jqRX0oTnk6/ekI3QXegrwMCd0rgT2KiNgDnq5wuVrlNiHWdF9iQ5wrygDLA22F1vPTPFFF3Pe2wlMXwiEXQo/4XVpZvkPiERUsg3mmDtoo5kPibyq3fTEd8JZYYR880CbL/IwlN6A5onbi3kLzgqyFpyH4Q3ER/yCYozooJlVam+P/mOOuss5L02Uftlvr2HYpu0lBXbO2+A8DuTHt4SaTgu/MTk3wBoTi/kFsxv+XEO+O+AcRG9kunsbmNcr+G1VnWDnd1NEg6tdyDFEzdmQHltuR6mS1HFsr89DfEu0edL8Xi/EO/yO63oEl/h/Rb3rppmX/EX2riF6hkKjnELVuqwbUzCJvgpNwpDACcoH/mC+rGsDFGvJWT+z25kqE5srRagMJxxN6VzstdFutRL3OqPW/FZj/jzJ/CpT9R5k/BZTfyriJJfop0rrOIEqUeUmcOsSR33JJJfplFSIoGCauydG5+tFJOLIUI2C3jQrGYxVk4rTvJ5KrD5O3suO0p9aPVsdIlMVInOKXIJyoJK7V0ro+YktIOQwVjmN3atQsVysPOXrQeSrRDC3vDZ2CivD4W5YFc7DMbrE7S5NNj4tMWxFph2toPbOCTbG86/3i6CTrcTqHdGNMmTyjm/H21I/T1NhQp0xvZxk90f4yf/JT/oRhuMLsUjRRquGdELuIqTxxgDa/6bhd7ZjO/eO3pqZNb7TNFPmXLBOWklY0vLRzMU5/qi6Cli2ZQCNOP4fd/2Zke3FqosVAHui5Osipf+7/s/ocZdumvPodejAdL3P6UOX/QaAnO8d/++I3SLlOQZ3oqE7Po52S2xS1IdnIY/HRxYTA9UZLbPpFdjRy7Gv2c6oyqUfZdC5EhV2F1XSV4+9celaWIW6PbRznyJb8php3xTMJ7PJUQXOquGP7MA7u+f4MAttfkyjNzr+/6vK4iTMdbyozIFnal5l8rfxE2/gHPH+BsvHTIF1IN9aBgZGaZnxkXY4z50r6PWpNPXCAgqAHYViAHO8ywniSIpQt/n8SRRRQQxFsvzF+fEPOTbuWSGSR/OivAsSVCMT7dW7yZSBcqvdNhqOjkUgK+ONdnJsMDuAqXA7goUmK+ONBXgwlGL27/5/I5NNQODoWiaSyP57oxS86I5Jc8PXfjcmXtxQOiaS2PwgBOffm+peNkZFKJkkPyd/8vxsjNjCL5MvQaC/ePS7FqynQKOYpOjGIDSw1cSA+cRBNw2qKrTjSonpvTRfwv4JqmbjpWw+GvRLiOLQS5OM5Vh3a3028yMM5QhFLyBPmqPAb0b1YHn4W7xMapDb9xwcj9wC2QYmIaPQR9HTS4dEPgQvGO1oo1P9scoW4A0zMsh+PSnW1oOSM5c6fKiO3uL/dBXz+Y7yZFwfPCOSfan4Mnn34P5qP0cqfn6RsEiK3eL/d5Xz+n82+s4JAuN0Orz7Ht574kyGEvMgt6G93gsF/GaI3A/nH4A96/rqFoA5EM97hNcKcuc/0nl4adOuhzr3kvMiujdz3VxDYt/unlCXCfXhC0B8SlqSfYgWjUbz+oSABIvuvicLEqFwDo8IxT/+NXCzZ/n3MsVlnm8i/ISYni2fu278DNmD8BSKmFfH/DrNb6mmB/xWWfy40lv85+ZF6mvXvOAV8a5Mz22GOjez8+A9CqPePfnj5g2lt6gcw9bTyvwlLGRmzKjSylERUqyIKfFAZA1GDsyTff8j5W6wgJzmewtNzttNwDkBiTFOno9eKtORGYkwHxQgtyZh055HnVrTlPNFUGX+mitcV3kznkeIEf8rp5xh3WgqiaWkpdgCoQxzfg4jhb+K0JYwjF82qiSlbxYinsMdZcm3dggLfQ4r9MI6w0J+S4qRmLYDl7ZM+Fp5aS278NBM4q+FnSnaWDArjeGDI/mn0K+YFyepKi6ewZpYNUBDjzkNB9NdBCGeNHWnfUuDb3PpJsefGmwuQjFnrURb2SL/t4Pb72w44DuPeDlNw+PK0Y+4kzvxKi7Kwlxz/GXvsoFZaMkiC/RCJiIJoXPo/zvK28VdMx8BIG8nfjrpjw4JjiyL5tn680+LDlLdQ5oX/x917a8m17/gOcktEUwe11m8f8naImT+Nfsa8RFnOY/P955/Rxmvj1GoA3yM83kU4OzHOvGjDo3NC8u2MzeeJeCXvpSVXDVofDUti2LcYGplURoQvdmUX4hnUhWuUn9vErneRFowSmEnE9b+04bkQuiDupJDsjaSWk2iVBOpnPLhYHP6XuPDzEw50Ohs5O3luI77e9Z2PP1IRrpH6BxFYCxrxKCdZKgzUj39wETwcuS77B3F2/Nz2crX7MBd/pCRcI/zP4i6nm6S38XbX6ybwaXozfmvl8YL/bXdWZ3+q/fdk8cP/JfkPNfXfkpUkvW7Xu141b8mF+CN94Rq357bp612+pX9baAvXmD23Kb6JH/FHMMI1mE9tiuf/LIhDSG4Rni7cu5eZ1ynOzSgn44+QhGsYntpqznc7+v8nAXKJ/u9RyZ4nvHuwGXAiPpHln0QQ+XMngTfcuxEfiF0ayBg3mLpe6OUtyOMziBsviEf+4GeivhdU4yD4fw6/l70c4LB9C8TYwbDWoPe1SULsfoCcD4c4FP/j/Ff0mirYJRZimBPql/duRrQdPT0Dg6ViZU3ji5L05MiNcTZFsEscxDAvFN4+wj8Lf4rgi7eK3FB4W/8gEq/OFIy78XoRjLvIgy+iIIYpoPDiEYwF3kQExDAJFF4QgvETWfBF+P8o/N9EGMQwLhSe0VuGVDmFOf5k4E4UYhceMoYEhjXwfd9/CVeivlGPt5shyBh9eNaa931tYhC7SJAxDDBRcqpZSparoXA7NjFMItHo/x3I/zai3/+v6Fv2gjDbujPzC77A5ZwtRDA95o/IlXgvGE3qiyN6xRh6oAODDLj+xeKRHx4ivAmPF0QHIxhD6osnGgOEZUvCHZQ2fC8l9gcUPn9CLuYwb/h74u8hIMxf2K7th5Ts4QkN/WecLwGR3jYICiNCUdF1fqRhQO86Rl+EN2kA0nLqTTvgxayIoqbp+tpgOZV5WhoesMfU05OkLgx9Q8aF/ogO/x4ePfx9+F8/H4+8/88fkBP7hYBn4i//Bv2vP5X/FQoEnkn9OwQJJBH5d0gUSPLp36H/pSvtP8kESCL57xB6FUvotURdD8Ii7o8Hcm0jmKNo44C/BS8Cvt8Jqfjn0fYoYW3RRJ1hSryoAEn+TnSPJ3L53bL/d2AVHbH87c9/HYjYpPUvUPoXSP1b4JhC20I7UYH6/wBK/wKF/wPkoU7kyL/V4K7F31CG/P8G6KKB6EDc/6TwG+qQfwG6zOXArYRfssj/Bum1LFpwPPnrX4QHjif7d4gcaPTlKTohCB3MIvYiMdqKcI9DtkUO1PviH53ghA5mEuv5W5BiyxSoF+Mfnej0X90y/xrkjvPf/Q962hll+Qfy3xmlifOXTVBCBNOJClGNlsJs1cI8NsPcp5FuYQD1Qv3lEpwQwUw/bhn/3mFDk2AEdU/1hygTlP47BbEzFLe+tVeMar7IeEGhDMWlwRQRhREXpW2mIF9V4W7s/rxtpJIHlpBAD6jnQ5iHheDn4RhAZtSmxYJH6l5zs7c/zbXcb1iJ5bKrejiOgEn41j22KtuHuREaZz/htM1NqZhoI0zcXmrmQAX9p8y2O06XCztTnsnBz8bUzF+nrkTrYBwvaZyzhEPWnrxlF+WN+THw4gZYM0niye4v8JL+1bA9/R4xk3wx5psMv62f2z14N/QTP6qQA0vKijZuWpkwp4CHT9zF/esOLMj3e4RZxJ+ui786hlQBf0/8U43oVh7mzZ0DwqGfvFGFblhS+28fokKYU/gn2uYdXdj4VooublqVMKeYh0/OxT1t54Bx6KdO1P8XiXPuFQiKoP+hAK6Ti37X0E+fqMLLtyN6C6kR5pTy8Cn9ibpc4EhZ0cdNqxPmlPPwqbm4l+wcyA/9zHg7IeyRIT3CnIq/Tkj/r4I0DH9OkE/Pxb1l58B+6OfK206wpawY4qY1CXOq/ysxJ1wb+aP2PVyvGN4Tksk5w5cfFe/hasVAedhDDvXvHaPDnPUYv6yZkhk9QJs9fYIY8aN97hSxfNjWLYMR7qB1CXrRDs3TTGkTrpY2tux/xpf7s+2MWjFuE9/9Z7/kxe67p4UE8j8bZlBi8+iDxCIPoCT6pjQoZ3kwT5HtolRJfn8/9wkWRFIPSX+sjB4eFVW8iIYSxYkdLcdwka7nYkvbd4/0ipkQqp4OMWx0N/S6ARlkOTyYlwEZc6kNOW0Ge6eWSKdm9QDgT7YGP7+BJ354jobNBX5mkEgA0+tcPuhBSBGl7bPVDmpuJL839XDe1BUqcS7P9a7WVaCAz+FIcukfo1TEpojCs3eHCfJmGY5+Y/MH3FI21MjEK1JJwGc8GTTsoiBIXI0Pa+j9nl/qiMjspRBKS5TrKDf02nAxFV+107buL2h7L3dVRMLqU2bGIkvKIy4pTyu/zAk37HkF8oyfPTljKYsyegBzCyXQpaKda6kI3XOj+boKFZ9/uh/lcEnFKyseFYIWScZkWjfvf9DmA6rR+HkDw5F41Duu0Wn2pe8pfECL/P7+oFUzRcWOE4k3OjWlGSlfwzcSMuo49eajecZUCdyn+R4su2S4A4Qhogcq24xRZhOWDgVKsbcZEaMSjblQ7mrDknR4/UqY+9A75/sGQp83HxCsJuRMiaZH4noHk70In7242+PNA2wi227a/GllxLrhWwondZlNEgfeRZMSpSu9ofB1Lqr9/HY0t3FdJ4ncSMV6ZwJeX24TH8TfYg5CYmE5i+Fz1V5X1MdNQm/IduwulAOhE7i602U7dhZyo5eevCHxChidzC1Jv4NXHmFWRB6XGMXz/0Lcx5gBOeISo3kkmXfw2iNK1+L/0zcDksf9/53wRgePIEgSUuC5xBgPsoWi/19FF54g0pNTB9L3A5+i19pwWl9iFUZciZlChMto1l7anDywtCyhnD2fWyZo0sbyYeR9CBLvfCINOWoq8a+/JJg3BaT8p99rIGNF3sqSo/Bv/trT9PpvpVc8cuUS8Xsi+m1l0XAkXvXlAnLUvX/q94JtmI0jeo415xtwiVQQwLbYITTeKafFVJLI8KYf/3Tk9F9iUE2FOjeK/UI9JbL0++RVOa2Aws7IHOWL88O86Cr3QLffOxKY2XTkfBZcESPm4B7Cl3DPYBe0D+noP64aPpjZXZgS4uOZRZvFMMWxtfAML++8CRpnmKK7bz3zjxCKNnyBrzY4u0HSWjGvZAZsL+HuQ3ckAOxwwF5ohHjEQMSff1h/mvrSwLRunpjrL/W5rIvJDef1dSyxf6XosnVfoD2vqFXPafFnOh0m7XKeh3e7+FeQ+7xvUe6JGkj2DHzCUZ4bkLkv12MV9L7FmnW3pSsDRnp8f+minJP2aUKEyO8SkQkj1+xDMEJ6vzdm6COAwCBzbj71hayAdIRdttv4ReT9iLJ5XKWttQmX6yCOZzOpl/gMIQOh2PBrFd4Yq+9j8MRbwYRjV01Fzj5eCD3IwLozLLAmQQ1YfE3PoW1QkmBfM9Oz4WNqtm9Dzrr3DhCLmI06bFdcdeihJCok3Hx3U4JuvdkKifvElLm+7jdb65AuOO08iangF/K27EpjEVsxZVbVbyZpaIhdjN9Y4BIC/v2MVsc9qIJsF9lxaU9XglICAYXJb8NJ9sI2sg0rt8ed80Q3G8OSCpN6ZuIrNEDR4GqI7ACoIGFLkmS3ZUO5385ECM4MfZrBS5A30NL2LE8b0EFejRtFbI8RV5B4CKwo25pvNR4hzW/Q9RuXmctil7WiiRH6lpnbLOtzznX5f61+C0CYDz8Wt15dI+hXuVTJGj37/MkTl1K3Wfy7jZwbh5/dQN6GaCE4v1S0kHg3ZxRiZz+Hy/3Cwul3NfdV7ejmpNDGwdSMIRGD8VkCHAQckw88T694F0QhZAk0I0RCsC9umdcYRjADhCb0R4jgtB+cyH0ThnDe2NsGqhDKCKwfREyc7CG4slaOCMBRDWZMK543UDawGEGx3da7WiuXXIFhgla76RBeME/sfoHiI/YYc7+EQqwaIKwgT6FvJW7mh6cVGpPrqe0ZRpkJagIg4KBioL7BOfMGD7Y0KBKMN2SJUcUnpmNDUXEn1Dr4c7cbkIW5NSJfRolCdi9S1Z4hivzY0zyr9qliddpDSWhi9kk3gE3xGOs0hlVepDq7cgtpYPZJRf7DFn/5aiWQFgZgyVh4JOaslQopPq8p1PhMqe76YXt0aZu/A32Z/IjlXq1u1XPuK7GgiCk3zm+vs8Ruc2QDMI8Bexpzew4zXancdIncdLHcwxxV6SzVvbuMX0cRhYGqdLqAJAVpFFWT85zKmLWJXQfQogMY2FGUxjxWKNcxS5UDwmBBwXW05CX4euegbloYy2Y3CylkAqGdN8wIT5kJzZcHzWXCoG8EL71aLkYLPEmhXy8pDON3OGZjTT3dWKqKQ7Gc6fs8I8ItIH4DgTArOhP8QRA6VQAa++PXI5FgG4g1iBtoSkhK2g3ED4HtAQ7vloQgoCFLILOh60hEGrIaSYITbe0=
*/