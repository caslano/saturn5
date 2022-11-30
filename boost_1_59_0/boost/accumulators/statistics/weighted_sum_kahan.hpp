///////////////////////////////////////////////////////////////////////////////
// weighted_sum_kahan.hpp
//
//  Copyright 2011 Simon West. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP_EAN_11_05_2011
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP_EAN_11_05_2011

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/weight.hpp>
#include <boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>
#include <boost/numeric/conversion/cast.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
#if _MSC_VER > 1400
# pragma float_control(push)
# pragma float_control(precise, on)
#endif

    ///////////////////////////////////////////////////////////////////////////////
    // weighted_sum_kahan_impl
    template<typename Sample, typename Weight, typename Tag>
    struct weighted_sum_kahan_impl
      : accumulator_base
    {
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;

        // for boost::result_of
        typedef weighted_sample result_type;

        template<typename Args>
        weighted_sum_kahan_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()] * numeric::one<Weight>::value),
                compensation(boost::numeric_cast<weighted_sample>(0.0))
        {
        }

        template<typename Args>
        void 
#if BOOST_ACCUMULATORS_GCC_VERSION > 40305
        __attribute__((__optimize__("no-associative-math")))
#endif
        operator ()(Args const &args)
        {
            const weighted_sample myTmp1 = args[parameter::keyword<Tag>::get()] * args[weight] - this->compensation;
            const weighted_sample myTmp2 = this->weighted_sum_ + myTmp1;
            this->compensation = (myTmp2 - this->weighted_sum_) - myTmp1;
            this->weighted_sum_ = myTmp2;

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
            ar & compensation;
        }

    private:
        weighted_sample weighted_sum_;
        weighted_sample compensation;
    };

#if _MSC_VER > 1400
# pragma float_control(pop)
#endif

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_sum_kahan
// tag::weighted_sum_of_variates_kahan
//
namespace tag
{
    struct weighted_sum_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_kahan_impl<mpl::_1, mpl::_2, tag::sample> impl;
    };

    template<typename VariateType, typename VariateTag>
    struct weighted_sum_of_variates_kahan
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_sum_kahan_impl<VariateType, mpl::_2, VariateTag> impl;
    };

}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_sum_kahan
// extract::weighted_sum_of_variates_kahan
//
namespace extract
{
    extractor<tag::weighted_sum_kahan> const weighted_sum_kahan = {};
    extractor<tag::abstract_weighted_sum_of_variates> const weighted_sum_of_variates_kahan = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_kahan)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_sum_of_variates_kahan)
}

using extract::weighted_sum_kahan;
using extract::weighted_sum_of_variates_kahan;

// weighted_sum(kahan) -> weighted_sum_kahan
template<>
struct as_feature<tag::weighted_sum(kahan)>
{
    typedef tag::weighted_sum_kahan type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_sum_of_variates_kahan<VariateType, VariateTag> >
  : feature_of<tag::abstract_weighted_sum_of_variates>
{
};

}} // namespace boost::accumulators

#endif

/* weighted_sum_kahan.hpp
Hrgct3VYeMN2QZZtzC5aG6U/Vb9YmX+QNjSLTNjIPw189HuZ7VXW2/GtNsNVbPkOvriy86LEwLskvMDsE/6KlKqGTgnHWsu/zr425QbLDh7ahfoVNrRzs9vY7C30/ltzZ+76fqsNMssROGPr87CpI+HK7a5tAwH7YwLnsqBt7RnIk0A7iq7X4lrDk0E7hK4nZXfs2t2TY7PbhmCv7HrhGbMdQSeCbefs+uHducY7W7Ntwktz1st6j/Xp5tLexSUhfWvv8hC2qbnnw3zpuzmtdryukK0h8GvwZ/xPeJ9AvsHsbbkbk2ebZ4d30E+uT/BPsk9En6CuwZDrrmu2Z813nE/cL1+ffr6d7Bu6Z1VPdLweMbsMfH9IgkR6QoRUtdCkZXEoCRLneNFZCbARYh5xudkIw7jNArgTqdc4JHEfRt8McbB4AeJ0dnHYERK3fWLG3z8IyBJyDdE5gvYTdvZ/MvpHEoMWxLJLIFCQkvSLSEpgUJDlt26Ok+5JoJSSIg0LM4bNx85J0KRKF8WWFkRLE82N/GBMmE8AY4wYJ3UY/sUYkyEw+W6zoUuGluC0j2hP0RJZTpaSALMPZU/SEv5LppIAa6TBEKkl+pecNT5bfPrwxD5qbeq6ZGPs2vDFPqw9WUvEe+q6zCXBU/zbsM7wxz7grCwuMY4h1YooLuHaSJ8h+Akx1whtbTq3IC5JTBzPvt0tiFs8t0gW6VSsCWS55i23m1+7uDYhXYLqMO8tpVtUu+wmvk180/DaPs6t6i3titwm0VUC8D6wfaynOC8hXoLccPE+0y3bLceL/3vme8B7gqdEJ6FOgtC+zj7WLc1LtKecNz5ffPbw1D7aLRWHdHRsPrEswkCivCRGUok0zbykFXNQkSKXTP4Jc4DxLG492YVInanNashj4ccxZD0fDr9cAfAJfpoMzvf0aZbbHRFHOmQ64USeMzJL8O7E1p0SR0BsFkhDPLM+FHUO8TSvsD4yeU7hXs6RGUdILt/ADLSiYO/YVUOk7ASEM042j+XeUePN5+UKwvS3aPwXDqCW7FQR1TGHIwlPSmXe0czdCei9YGuatvDSdMO9fmu0tiBdYcrMw719q98/P+eUxZGoI9k6b0lA3h64I25T2KaoaXriXqU1aFPUpthlmutE637q3vqfnnP6JXhVDDftDKHLeazSGsUr3DQXcgKLMHye10ZQ4IYMlM5zb/cK4hXPK5JdNDVtcqL9iu2V1cmvU0A3k3JC5YjnldQpqlNsM812onlv9Qr7QeWVcll8NfN0AvgKyCPOV4A3E3NCdq/0ivGB9ZHhLfAl+yXwJdFVoDNTdULwSvcK85HsLdZVzDeNdyJ3b/IK/ZGEWyR2rIBpEqonim4UKSFtjGpsxJrcq5iaWVjjmNzDqA63mPCgr17Odtb3Wut9DrKYDaNLVutne23MBD6m10Idk9kPVkdwbsiaCGNQXO3JmpE5KlodVw4Aa0JGpT9QHtiiRkFlcGCJ/IaEBTP0YGZJXaabZImNNfVHjSUdIOSZWKVPNiTAkzG9t6iWkzVKxoRpWVplCnOZmjV9Qs9hhdsZjCuBpfblnLrRl6I8jIWJTUkd2sII99AIeoXw0MAbVVcAVT9C/a/HqA4sIzYm0hhYWXJwpVfwx4gTATFk0zHB/7heXsAyhSmbUWPHFxGEdxo7rTXO3m2ijQbN/9M2koIY+pLuir2OGbshgCc8kRyLaa0CrJC+C47sR86jzBzdLc67gKrYa95d3CisBAJ1N7z+RzjPfBlLvV+wU03YHPb1I/zcDNpt3veHgWuANcWuEiFu4y8YcDP6nNnj2Rzkh0BleVp06DrUK8Qk0faxgtBWYRhxSrxE0HZAlMFbUODG0NMnqH5Pc2LC0giD8Ckgd4pu1J8KRNzoZJL3fByOSum9kneELKNOtSyAyHmrD4q5On8QzR7d0zt2Dn/zkaDaBqinBegpm8NQSc1/7ec03swoT8axUuwgxyFlKIIUlywdqVglWVdhgtWJFYzSL29ydqo7eegF75sXcqAqH5Rq1HHmp1b08NfmNcgH+paGk7pFyGkZKyFaCbtIIBiwYRmUacgpn5WSPvycyNKuiFK12JMx32NZA+k/tpe3wJxPA0tIA5soEqgwk7bAnEsbjE8bHC+yLmxQhhmzhof7FeJRmuSRBfezWnje+BLUHom9C/PAe3QBzk0xJwSvvXkETQKyrEJ7U8BpLS0gl1XPPv0ljQwSshyMzQKgPcsDs7Q8+SxQVa3DD9WmG8uqzk7syQO4JjTKo8DUeAlH0dA0HTPnU02PchjhgZK3qalwADWsp3dbUENwJ4drEbuQwIYgEuPg8LEQrO8S1dbx8sm52/s6CL2kaJYzJptcV2SCCcbHBTwFTLH+gDqHbvnUSsUTvwGUeVfe+gZUz10pCf5ak3S/1g14Qm8BLlnKIqonsuwz5/rdkam4wnTh6C64eYRqwHM4aZV4AVLw9I8EfAbxNpib4cLVYv+sMzKvRlrcDDW1vf4UvDjyqPUVYpVmw7P/2AJ/mbkF04ZrJQcgTTVtc1E5JyoslNsAqeEolb0+8+wuCQ1v+iFeN5vWmnNzyPWKrNy5roykMIvRQepPU8wHEAP94jLpZi1zJ6CxpF4Wy4UiMhUL41KEg1IWiU0Ng8bSmdV5M6vT+OCyOXPM+rTggjQwBQOnO/Uw4XaKMEqJdMCuWWxYsIIi+vNEVtMiZgcSDJ0BVC+ENZ4a/jLE6BcvSWooCzjWdRHFOqCN/ZHeIMNsUWPzIISo8blhewHdEChaReBqrpnTkpA/CjHcqpo5Vv7iD1n4GRQKN8jQPacxL3mbsVU0KM8i+vpAvaXVM1jsMpbPopNAFdzhVSSg5OzG6IcSFjkmhIjj3jnqWeTMSZqgeiw5NU5FlcUs+ucaeywzaSyM2koF6vARmnW/aZqFtxqNupZg+r77eDgcP1lyQhZVJN8+iTVUk0i5VzfZvCPuD9ufRXPljWZMj2xRUosgXoFlw+1hz4yLnxWcOTa7GmW+xvec1xITc/5g8SamxOVH9Y96UePzUESrg8o2yyTmy4XaFqgowubbsoQDz0iTUAFK4/vMckRjoHp3zf1jOwQyP3XX/CFV86EyD28kw+n2FYibTiMoUVFYIdlTSCDw36GiKBkwb13nEE2If1jPPZHzAxo8ElCHdtsWHDruav3GlH/+MoCHFezGd9DZpSydqO5bSUStWlI+pqZlkldv4R45oSaniSdDSU5CtigokI/Ny0vUhfBUwQZIlrTapAkXVRoio7k4BDHea8mauK7+ecbzM2p0IS2gJO1M+c6ZkluRjDRqPo15VngzL8njWNiAVMMplpOiNIasdIpYTW8cGK5FVHNrdcemdMbo5rR23rTWlcWkYuZjumxmfi5BVOd396KGULTI4GJ1aHYGIN6506bxmWH+qolvKRjEsa8KuAaF5XQyp1ZODq18Jqm8PPzZj3ydZXlX43jxOOKgs5ZehUrbAO9LCyi2472h+xus+huDtF6Y1l4GrZ0ViXw6mV6HBFvN2U1I2lVMCQS7xOtL5IHAZEmarFryP50KEQ2VO7pAa4m+7APt4dyaa50p5oaNjZbJ5hXG6UfLinf4v8tYLJGEubBaVHYg+gleFSaEmK6v/WtvdwWx+LYI5H015FVA+nDblrFYsCUObmqjLwgNWSmFjytwIFP1EUhRxGd08dElmAoQWxIlO5NB61UtpNQNyxcUKuZVkObjOianfICWTi9gJKKUTt/NyxZLQtDS8PoEELGX2dUuFJOWGR15LXG35Hzh9qgLNCAUkZcFP2Ssg6TD4koZGIcsZtzizbQ5+5ASjcO1irTD1B0/HduHpIpF2uPhe7QT+nmEbPT3lRID/5jX/vmT+2dJnoXK2VJVYTitGarCky7wCR0+0yTfU8mwPb9enHx7Dvl6SBxfNNlNrwUC1HQZKXEAV910Brx4Ap+Tn4JcWI71lyja56Nu7YnBSBFcWhHap5Ka/DY1o7xEblgGqeQ8anpJvzAtUlJaybjwAZg9yu/h/R1GV2TU9D2UtHzkvyX2CYWMQ3JZJcViiuw57Cmz0SNmMec0Iq6JuIjxf07SWMip3OHSuCKkMYQJYnEj+cP7Cpa35KxuyOnc4TK4A6QxgVr/ZPUTxOx6J43hUlb6jB5tU3l+GccoKv1RVEr+e3LY/9eJ8TspbTEmiKWO5I/vKxjfkjO5JaZyj0rjGpHG2CeItYzkr+8rWN+Ss7klpnOPyuAeQPIg5qNzA6SXTAsXXaEip5YsC5OQ2qeWzAsbkTK6IadxIzKmEDvOuV+D6vaziJDIIt6u6rXB9b+bo6s4LsPm1qVKoK11pcrsdaURH2yzizOjgAsSUkWDMaWrg3INPefwgWBJGSp+JHIsquhoDispalQG1AIBI0s6EbbChZsEuA4+M00g/aBVTMPPCZ4rHIEFlEs4haY9wEhn3wVBHCIQe3U9GOw+CAKzxcwZBhgAI2fwHQMoBCNn8qWtLcvpBvjnFY2SQvLp+jmJkkpJ37JPlbDxE4yQLrQQUITOtbOHVohNmu/FZpc6KaJ3o0aAIokhgXInaaAnvip8b6RW9sifIUQjgbQ4eI0RgMzITUqPNyQfOnzwFgTryO4+0WjpYdXiILUoY41TT1bMrHbQ92zRiABoUGAqa8NUv9CQ31g4NVctU3UxcWrg+jYNrasLpwsbalofVuqSMoJsVZBWLEUo7WCzWjXL12uIfTZSP7po7CQRYlqFJfz4RczCSioEssGErq8LoJrRtU3zEEb2YDzQpGYghCHiTcnDWGsVcALFhbWxLcJFBqaMzfuJXhZKVilfkgYkoaGpaCjvQ0siaBBi2Lp1pIn81YgEtlHDaIzhExvlIdwLVKp0HiSsh8XCxAqlEklm7QsnsHLg36fJCxpz1lZ3Ycg7RSShg4gBbZTpbsu8oSTGQPQBoSC11T5OCeH2AtSERcRJCFhEuk1BdvEluE928cWh8phoidq1aGtaAmpI8dRMw35APp+C+u6r4FK7WfLj69vcvc4BnSpWH+ovDPlsyPo9thaZBZf3Lp6Iytb9Co/V+k3HBMgCrcHPSetAiSeORy2iC+gRSjijWDUuTYkAymr9k0GBAtuMWiRXB9INba17XePup54jDvScxfKpAosusNe9OQOGu9m8qSlwgunwT/kqeoU/03J0D2Wt8ay/8WFWGsxmGc1euU/00fGVpRM3kYqkhCg8SR1/0/ux/ImwBF0JUqfJoXsShh7up/haA8LvxRdsznq3+ZHsvqEgh4+uhn4PNm8brF5w9DLlZ1t7YxD9FZ5OIM88HOGmnVFNUiji3q6gqFGefYP9feyv87v/AhePyeawTxs+Lxuawk76PWxE6LCPGGCj0DInLEJKyaoQFvaLlJJFQR9ZaRZIadZfUElKyZiH0QUFpRWxFt1LKhwGUjJcmsdR/dckY0dyvnAqaXbZcqlmKFGAWItZFCEP6X6DbH4VhbKE38qk0bDiTw1dQqUYxTmVwqIKyYnOQkjN1NdkUualIQdOmbWU47j0MfXKFLuCNQz50pXK/sSWdeFCUslIk8QkLOdghdGJWqC6zJEJI9Ofu5L3Cyz2qCeeHPapXkh7JO6Jv4ctVfUfF4Yc/PzCpRPJqdhix8pp2B5o2A5rqQnqPjeBjdyFoY0Ovz3DK9r2RfSq8VR+sK1awjrqHRkjyC16rwpqhfTfoCkVk9wSAYepminsDgFhTB2VFt3w5xrySyz+EM5R+KetEfj+GyLwTlpEobpLEHmV6RCEyzIgBLuWFy6lukDhigSJKpS6reQsQeJwuAkLrxCHGniAc8KlPTQ0vzPqWH6TG4/OxaLTJ/vCQM7oQy7HxjImx9buqFEYDEmu/L2CTmEwwkHDDVTMwB9nVUnhkk7xtA4S0SicyKEawbgGonepm7NAiu/DdiL8cMODEsAZzKGVihMdHR5thpMbrYyTzrXK9eiEfS6+MmdXEnD9pUZ8L7/lXXlOmcFA5YFaasFe5gdydkPzADefcML0VovB9FadyuReN2dhXA3JUmipH5Ug4/9TSXFSNMaplsFgqHpu8LD6xgC81s7ApFpSHCV2MJk9tW54IlwyXF3CjoeKFqP/EQWPmventEt/12qr1TXxUvRzT8Ua492vdz4HiTXjMVurM74wmhX3GRX4s+nFirwBOpSbisaEX5p1pDURS4/6BDqmGCPNNwHpEgMyXrK2yuvLJr5lu6udvqyPONutpk5V55HQTCom5VPN3AZCj0ErZ3V0eC3eC6fKFnRd+n2nMBas5RMl7FvJJ6MQJiESA/rpG0k7Q9EdyzfUuG/jS1PwQ3MockjzgQpKxkil8qxUxHs/PM1V4Fi5LejHpihNig0f9Ptq3evOywWohxiyOGpF645eVes+gUlrAT/E6j7VZRexVh+A7DyMH0x48INqbUVUDlxVRV8pVsQHzeQWjdeySyZkV5TSrQKILyonjGPmjecmVy1r61ixbKomROGWjPle+ilWPHC5SN7iwtXbHGpdnA8N+dp5yN7CyLIlPSyn9sza8NzmN1scUrze+rjOU9tUL0hRMss4JQYfa9bOGrPbMo0s8SDpIa5rLqosY2yaipYlU3mixCPlBekJ54jbgYdUdZxXuh+jGpgO66sw2V1CUBYWp8yGLlw/1p0tLqRxCD+zj/fF8uLEvdmynTU2aFU9Ep05qih7mU64E7JUQXN4AvYi2/94rmcpX5hNAd2nCxAOkvHlqZpH9gMPtO6NGIX1MvF9fQFu8paB//t/EmX9LyMgMDLSMzMzMf3fYnbfjTGyMdAzMTMw/V9EQGBg+7eYHfu/w+wYWP8XZycswvJXtANmQSZGEebvH8LBzMYgyiTIwsEmyCrEwCrEi8/NzErPwizIJsLO/r2DgszCTCIMDEJCDCwcHBzMHPSizP8pZ8fG+H/C2W0BAAJlAQACs37nLgBAUHQAQAg6AEDIPABAKGsAQOhiAMAfAQCALOMAgKye/xmDx8DEwfw/CcJjZsBn4vh3EJ6YvY2T7V9w1N9YKzqpfzJKdD/t9awdbP+i8Qzc/ulL/rYlL+8/Ynt/b/T/HttjZvuvsL2LpClzIoYfg9ndV9sGTdM/40k0O2kvenGhgT1OrCQpjGql3j5DRrP4Gs0qC1Nk8JneSW+fTup221vYho57NgmWxjydm7qmtq8+V4jYCRD0onFlOY76fT8tfyYIwp8f6zPX0Rd9trn630LJoyvxz/iZCfYQezvziCgK6mnWFeOPqFSlpU/ClMcgvRiXBjgcdfUNUEJYVL/pQbbFr2DUY65pJSljbXCpgbU+rQZqkKYwZm5EvDlcfCYf1wh/yfcVm/L4zYMmYZQGZwORxmah3iQyCXdHp3FAMhSZMxEF+hIR5QyrYZknEouyOIzxK4igSHnN1fCzL1SYRTuzwl26aCwS+/4m/PEwjKBnFCJr0Jbfmgm+sUFHxPNqyUkTM+X22DNXuG01FOcKkxUrUVLsbBJlwwoIjyG2qMl3rNsxY5gnXwabKZ3IfDTzOnhoh8yqISYgAtEnX5VIQYrjyLkY0ysQomB6f1x3Us/dqrC87MkwdRDK885n3nlWsuO0Ozb+lfHrdq6t7UM5/37O4YQcWvHlOt1FDby4iyxWv8maFpQEbHA3
*/