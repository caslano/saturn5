///////////////////////////////////////////////////////////////////////////////
// reference_accumulator.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_REFERENCE_ACCUMULATOR_HPP_EAN_03_23_2006
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_REFERENCE_ACCUMULATOR_HPP_EAN_03_23_2006

#include <boost/ref.hpp>
#include <boost/mpl/always.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/framework/depends_on.hpp> // for feature_tag
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    //////////////////////////////////////////////////////////////////////////
    // reference_accumulator_impl
    //
    template<typename Referent, typename Tag>
    struct reference_accumulator_impl
      : accumulator_base
    {
        typedef Referent &result_type;

        template<typename Args>
        reference_accumulator_impl(Args const &args)
          : ref(args[parameter::keyword<Tag>::instance])
        {
        }

        result_type result(dont_care) const
        {
            return this->ref;
        }

    private:
        reference_wrapper<Referent> ref;
    };
} // namespace impl

namespace tag
{
    //////////////////////////////////////////////////////////////////////////
    // reference_tag
    template<typename Tag>
    struct reference_tag
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // reference
    template<typename Referent, typename Tag>
    struct reference
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::reference_accumulator_impl<Referent, Tag> > impl;
    };
}

namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, reference, (typename)(typename))
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, reference_tag, (typename))
}

using extract::reference;
using extract::reference_tag;

// Map all reference<V,T> features to reference_tag<T> so
// that references can be extracted using reference_tag<T>
// without specifying the referent type.
template<typename ValueType, typename Tag>
struct feature_of<tag::reference<ValueType, Tag> >
  : feature_of<tag::reference_tag<Tag> >
{
};

}} // namespace boost::accumulators

#endif

/* reference_accumulator.hpp
kBOdtow3WQ6fcSR7SbZP2TUSqZW6bkv0/Fy+6gDsfQe4vO6kZ5lAvQHa7HIY0YKyhq2qCzhevUu3wR2U/gf63atW1sJHtmwp0zuYBrxpvsbijAXVOXG0USspb9KFKW93009VOxBIqSzH0vGt7z2/RfiqNu15G6THPIN3IONvEQKNZTpqsolnYj3MjMik+EZYxhvNjXqjWzYB8SkfmrhzqPH1QBYgYvZNz1C2RnpanegWEKbZiVtJNuGMLuidFDnlYOcWrkFmzKPyQRsbt5p4Kl41x6FC0oKpDTSYo98f6byBn7KLfvD+phvgSCv7rxXpjK7UyxV/bNBOXHoztcen/mCQOPd+t4m2095T5OYmFu+zZN9dAUoJ5zPaEAInFMSiy0VglbhE5zLV11E0Ye6H0eLOzxSrP0fcRryPObgwud/qP+459h54FSxfKyOrv4CgQrC79tENYLb+tcBLhKAaKDpHRIiWqhKyhAFcP7j6KgcU+OLG8S20J9DHqOegScTGrjt2cirMhU9zQ8O2b/nb/Z320p2R0iDlU5f0N2Cwtf4WjRGVrgheyQLTumyUnEGYTRf5hYT/VP6TpV8HnXtbifk76c32r65J9U6kz64OPn9/XAsbRzutFJZ9FyUvbt7f4gDk+Cbn/UiSHvjtNKmFP4Xh7yMArub75Lgm+WP3IRKpSlXFyrF8UyA9CAfiWaara3OqqU/eUmvpvBrIfd3m7ScvLje7HtTWDvmY6rXsLhgk6vzKeXGBhl9dqZBa6MvTNuhf+YmW36uZaYGj5vNW3/WQZgmtccI8raT1rixkyqKlajKlKGLiGc/ojHtDpamGyjiBN06vSbzgwWuRvEH4c5INR5eT/nRHfrRt5QTTgTXfrIOLteBnUQqi+4CRR06bd59xWATulYu6ua0FM7cpie/ZgKguNUw5hizGtCHviZMKIlYktJg5ShQ3kGcffGwoJ6pKh1Du3l4QIpz9oiJzoqoYP+VbXXYeSGrp8QAc2E5afVek3JAz5aaZwSP6WTCNPqBwynu2/+oi8D1mka3KeO6nc/e/XUCe0ly5l3FcMkezzoQo4o6zRA6HWVD3eUt4KukSoWlAY4KOeADdNFw3gWrRfM2f67HyunKHwdfeq0LULSiPeMR8ggpOLdvAQS7J6eIjDvt670aLyQ316sTQO9OyCFpAgYJLFgrIWcFtdqSOOAwpqaG9Dsx97htPQyV/H5AIOHg4UCqvX9wMRegqF7HoWOxSAMdNuTYW21e/mOnqaOwm073+qTAp/G23wpe4o6PDQkx0/43m9Ns3mreRFFQ0/tnG0DEjy6mdYC9XPtux6Ps2bNKqc8Vostol41azc8pty5Txeb9tRCTr2nGNPU79nn1XtHXI4RiV/iutZ7TyRANxO6KX97XgME2d+MAEzbME3UbTJ/GEesGzdotCqq885CpvugOl3xw+sFges+kT+z2dafCn0IRHbA7b0H4cmvWor/xJ7c/wjxoRoxc/1eHXhX9nXnQabRnV9wvio3b5Jbrp0fyO6sq/KNNp1AmQK3I9Hr0uvOj7dh1EKn1O7QYM5AhoQC+9nEafuyQIYnuc3XQEwD2nEgYrBkPQEuX9BwnA7ZtC3aGfl9uI3i5rIixHuoftnPR+AYjj/kHxw8ftoNMsWAfR9zz19oa2ukNpVmvdCGfaKCN0s856DRz+xsdznjfFCL1MXfgDhX4Z2fihPHo4c8c+J9WdhZvm6a/MIputfktfipOOqC0bRbuRGsqcaoyXdk+oXo3Z8KhtQSHrymC0XNtQwtTwoL04XhzGmFO9EmS5eei9H+LFCcxFyTNQy+KNeXxx28FeuHH9moWC8Oj1cZPXogN/c6hzbZnSplGBTe9zjYcD+KM6gbyWqN/Xld7pvIckzdtmhMOgbNB+kY3xi3u5Z05P2O7wr+SQ3ejktFayrZBxSmyy2oFxYAOkhj6SnZ61mMC7amD7IiZBh7tW/kwbSV1nh3M5rnA35sC5//2hayH+7oFzb9iy33dW/resv8LcnK5WD5W0vu50xMlBH3Kcy22vcwz4JSTzaVe6qc00wPjen8NmHnQc52jQdl3XfBQd5yEVvxNccLSjeXKx66Bkmm36v6otIkeBtBH9zXIH7xo5Wn+SHiCprquSHik8oUQyUzpvf8bOqb1ecV61x/KXkKxP761uJ37X6lVbPxCh+LhjUEe1VCaXPmDHUk3i1179666L31MwSZEjRuhcF43X7Df+7kLmIdpIt/T8rqZy+RzT2WuL/UVS0UBLe58JBPc4FhM8FUjya/dixYw1+n3A3SOQyseTBZ2X3yNoT6mfSGVaHTCyopTErRujExzS7bLNCnz2l82gPJoBXB3+kV2WxtZ1fPc9s3xpCq8SS3wgESUxrNVemNs/zCfdpA9HAuww1+gyS9xG//9J9wGG7NlwJUS57qBEkOxcurL8vsgZaL25ebPaMOcif+rMZOjmTnK55xXUzvylMtAIVLX5Pt03nawfhyrdTPA3AdrFzxCF6MxVt7fgRs96KzWNSDY35/OMTuSfOnsiyCuXxkc1G5G3y/NyVBl2TfdUJcxOc6lkvM4ctG87uzvliZYJkiwcuFfa4jt1EsaaPqGeqendnXYMpplNtqUTJkbnQIHWnQ9l+Ls5Jr13Dj3JoIR3GMrXnoQbm8O09D+KGhwTY5hpBujnXrPwtWlIJpCemr3TdQrykgi6B8RL9lSCC7Qg1QQD6TZ/RNxVoU99WzZv1QTV1zrWwG4in4DTf02ZItfQlak3gZnds480OLM2p9ifvfTFI+Nxd+a29l/n9c9Eq4U++8NzxXklCbIvq79e8XJjEn4na0X/mYjx0gbIGo2PAM+5vAmlcKIRqemT0ePlmscLjj06vtfkm3C+RTO6l2UUQDqwnLvg+hRS7/UWCVqqZWaFgk968BD0LbyfGBuCGLOiniZBg5xN80ZQpVfL/TIG44vpVpnXktVB733aofN04V8K/EqfpVbKWcQaQ9cHNGAAY5h8t06U+tBoZ+pRf9S1zFnO5v0lsFmtSul5PAchr5eFrpiPBxv57ydrTK0MqjM0PCMzTK2+bzRRsJMv2vHew5R1R4UvqjIrFI8duGYb77XjHwZTTd/UNetFkitl7pzr3w1Z/MMGfouYPfCPY89Pm0vGBnQGZrMpSdyysh90OmBqTX8L2cr3KKG7n4AE7SCbEArE+9lQsaux8aOU23IPix9+7f4HCyBFBXr8r5ojJH7pdPmn8pTmhaNpx/uVqFBIv78sYTHbSxTXQ2wdTgvqLxzmVMdBPdq1qvpkezwXxMQG23jfuMCS1hVxFMXxqsJC5uX5UonASZtuNj+pl7/CRarKe7JXitd+PjY/QOblhkkC8a/BUKBeQ1yApVkEaz56K/46uP3HrOn+uDdwCT7O1eqTRevKJpsLX1MaUAuwCdbkaRqUncsQVonW5FGVcbSTIoz2M6cmgWjUYyh0XjFakLT8+3lpsDq9w/4ZdSQLJyL/emMJaFS/Bv6PElngbGb+C8zhrS7Xf5VVpTVR9EO4m1KLHkTVs2UCVZgVwYTjQUzseQHQkejC2M5fAtxYKhPAk2WhESf/iejCGgnwfuyqxZDmJq5cZ9dlutv876j49t00csVOjrFXaBa54voL1Uln0kpfaCGMmNY+Y2U9uhDXJGJtWE4VGJBFrQiKZRCIhewKzY/n/qsCuuubvyDNJVd81fzhZ5yS4TZPK/4z86aVvFT9q77zdLUN1X34E5FOrfE/YzimrOVE+5+4sPGJYPLN/xGqPbVmx/S0OUWjJ8yqy08sRo4j1AN7nt1hf7woTryE7OKMq3/Hhx1fJ5Lb83on9GHmMroB9RjqsLnOf/WVvwGYdDKTEGz2VuH8ESBQra52JZib96o2HKzBsRSjJtD73JiHUnJ+azjeq4A/Ch6uG2hfHUTEzXxyL20W+dBi95ba30tQ3jLFI+925uFPZ7t0CfHDN/S8HhPSBrT1h/rteCkqZSy/81/e4UjQ19We+Fs9e2WGa566l8H+alnTMuyPkVmbuW5I72ZeKWJaywh23V7yZUQntxsa+Ikp2GIZn6AUDRrQ5Qvm5B9EJHtcsgOEDcQky4i9YEYn3y6hUjqJt0spic6//vIrWln/vVHcs4nk0bKy1Vcssi09JLJHBDnSB+W39ZTdqODpi1JQfzMkdxAyNe6x9tmJnT726Ole2f0eKP1J0DCPNrkcu3Vw3Paatxx565sw/iPjtmfxsoN9XoO26d8G8GvL3Dk4YeGc7j7f77ybcgDkgCNcQD9nQRnUAuY6wgx7/VKDmtp1iA/S8fXaNmTCoux8EGuR66BN0xEb0tXRTV7UCHdak2KOjBDmdm+T6wKvaSNl2uGh7UmOZEYwVnaUK6BXcrs4/dINr11tCnVeTQKXDZYLAz56t/xE3M7zft9LWL1tSsuO4DZo+mf/vpfbULrJMkbF34iC6NErllh3d/FY+kefxZ9YV/8/pqIXius1y1/2rQddb7J1ymA/0fONCP9gvvtVSY0NKg6Hbha0Xrc8hsJ8cAfgOYat3ojS9dN6p27EqAOPGwwiovNF0rul71eK32wVGyb+pb7bd5vhrsPNc/Otxy/zCacQsiCWjRmO0A8bSMs4EQP56epjBcpTIznxPRUQqDaWiH7boPDhWrvWFohxpEx2TfswEMwX8WlB/leUciu015cgMzlvzwLH/LyQQOjh+wBB/T8PXzP1PXOdA6HKQHCCPGEfd5zyRFnNR058LGUCW/R2BnZ6lq7QfyDTNZsmtQWBTGmEvCDrhzVZneEy+R7nWcZ/GU1ZndIy+bLFHH0GkiSxX5GwQL/DtFCDuH8FozJ/nBAkpxlbupv+80ITyzgsCbzcjB01gxVIjS0JYK3ZFSryIXwYZY75mut3X/t2a3JoHlBfuUNDlXu9/5Dhk97OkflFl0i8/yxUJk7kaVc+2LQjh6tOZ36tpXESOVVOsSDBvu053Emv9K/1pSNEJUSigKDmyVjm/9F2iNbxJP5N6qxuEaGvcYHpPsPBvl1TKeSES5LaEZr5xcyFZU+FgShGJRb1Z2GlFf1cibnbhzKuX2q0BqxU/F/oSFIrFR4NN8v+TIBFcsZ03RiVZUZV1G/cvXQYjn6sCn5OznsXg+/9UYdBUDwfS5QsUX815WLFgZHgnoX4ZwhfRILwPMlrnuvfHWnaMo+/Wdzhk84+dkYmmpoKMqgsUot9+M/NE8H4JJ+7hGrx5pqga9Hby8/Hug6SSXcONcdkQo5qquIUMLnkHQfz5OJsmWKYVhbVxzB1m9LhmVamt5la+dOtjjVapM51C88CPL3jk9VmkEu53QqjhEyc8rr9IVmD4f3OeZqVNapASRMCxd2ErHcLxM6dLlUy+wl+R+W6dY4jd0CK1L0iUw6gq1lKlfvx662ix5GfuRpVjIrbjktiMNuOcVlD2xXpxIYKlvK4QFQHbq426FlrthqA27NOQWcSO78AnOUi4dLpIkiduLh0yBeaibcUs25hEHs1iBzi9lQtNZZ7rgXUWl9o1Xi12Z2l0iLYfVmuNooalXwPQkibt4ijwPErHKPcRmKOFMV7P40EhVZSeIXfHd0CmA9h+fK2T177h4BFyWa9iKk7TbnkXBSgcZ16BGqfn8MED3jtDsSu2SnZr2W2HKVXpOSkSepkGR3g3hxCUYj1ygFAxb4oQoGre26gF9864+TvLqH7liIgtDBuYUHsZb/sryj0B1EWYerl0cD5hg7zdisMS+OGtdC8hDtrxji82VBWBKlwlZYC0xEDSDyf39QQe5Krbc5RG2sznBMUviXaM5zFHNIrec1saImtqByda35DQhUs9yevd52rtf3/h4Z+QbJG3+rg6vPvvarl3M3NrQvc1jzrn0LCXza6tT+1Q88ax5WnVyb+jvTib0WhYJaJwM+Jiczu4Usj7DaL0diCkX64JJioJQrf1eBPB1fwZumWQTSEOuRASK1W04xIoyCizcTKSM+1KWkbAR042OgMvvxYe7rOZs4EgIji/injZmVGBCixof+GSfY9XIaZF7ARbIHTD3iMITyvtS3ar1/3DnIrFQ2UwD4sl1JYQ2O9yz2R57TJfSdIPS+qT93sKBqNr7Yx+EGo0V+UXuMYJBilF1EwwamVUBc3J3isOC5WHazo1iV1BS7gTE+V9/oHCiIiTwPzCwLoh/Y3d1bgjNzaMEWwcOamKXnKM0c/u/DDd/gEO4nrL9p2itul4u7DIS21lFgbsWa1B9SS7twytJq9NAMA+C269HEv7dylPbPT3g66kRK862UHF17mx/EVIH2sOyuFNKqECXsZIqNbIgSgY3yA6YXvXmaTUL+CIJ7R2Zzwsw7sKwQA0RYbXBC+cQhx6N6qLRXrQgToycKN5/le/cWxr146UCK3pEgcRRDBVXl1RekwU7bX6dosuBLo0gFBWB6m9SHIHkpLrI+BArODP710Ml+9CEPvuSM2k4c3NMn0qREclUCeDaCi00vSZVhg3Hk3KSohhzQG+dUSCvwL7PZH4S8M8S1S1xvKD3emsd2XkVOXttcwq9s0Yn2DURhaVP1yru2EUzgCQC1b6vsmjuLiaK9OL+oRP4RDsfvNT85iwLMKLJvxKyMhn4MlJYWAgwCYhwvw5yH1wfZFzeQYfnhBfeXnfC+15AH9DYMvHVCX8KDncZ2prwS6JLAdGSwbUrAp3Ub8gX8KQEijNAMb2NXBe3uuhjWmRhCAEtArWlRrPhl6cj+KLTMcVgdFpKKdGwScjODQa0BP7lIw2ZEoEDZcwpZHjkzXUQDVK8rtOSmiY6V3sbo6TBrthrxFA0gDNe95XlH0J7o3PYaHHxX5ERHm5Spfmel9YVz1vK/4QS3f5xVeN2sI3V8ZF4IQCYZhSiDTt3uQuNOuhjQESWT719suOMkg1Rds1WqATg8J19raY2oSxJSgjhlJjRMAeNmQmr2sDDycmtBUpNUXgM8oBIDvZTK74FLUi8Kge2TP7iiEOojUMUi4AOQS3whADJJJIINnjp5Px9IhMeYRk6FkHoP4oQLYjJQ9JIwYvNPQ4ftrWhS6A3Qqh8DLPBbcYIB8UZMMrKYVNNBNa8GHFJiUHoTTk0KaZuS53m1UC2c1yVPRGNujbalGwacrhl62pe9eLl0t68NPj3aRHTGUmuFvVqV8BtV7AfP0oCwwqOjZ5bAbV7vCvpv2nSe0dg+JozqtgI4yJq+ISXoBFdBK/Uo7sNkp0UPiW07UMgf6NgBiKnwUz+O6jkM7zn3/aOvzVLvTGHONoOEQHAJziO/GgWMjvkEcAeI8qcftmDKU9+TWXGBpRENtKayX7eStUOC5DBLgA9pO1mdQhcWsBVz9J37eCupN6m4LxNTHWPes9l25bDBicNB3OFHQx4NaCiQkFP1ThBeR5Qn8v6cUmQawwrYyfllEqqDdK5D8kzaGTkAegDGPFf4R2s4Mb0DCe7GEM4dAG5tgBilNdGDf/BG4BrFqDCdXmBFcc3QLA2FLbRPeQAcTGd/MZUAFACFwqOkO9PWLYJkGOHtbqgauXBHMWPfyotjeg4ZC5yIIs35qDwSgCRxKecmFIG7BN6CmuQj/NrBiNhK08HGVxbUnGXLRXaw188nwmvb45TVjbhNEBNqUNEDF2KomhJmisAAYr7q7FzbHTLN7L1OdXhfQeBsRuiQRAAtwPO3AKO8U1J7AJcwjNysrmIBIAQKKEQLaLaiRbFmAH+sD/Jj9WBoB2mQGr1nVpyA/gTP2LDGwgrtxB7opzxzhuv49COvx6PAaMbJXuV/PGABwLB28eAimSx3j6IQT8wUGBSBoaKAD/n4tgPLcSOFWIKoiKtJgW8zDDyAeZ/R5jKStrV+gm3vdIUfeIYiYQjMw99ecQrZWhABdwe52Xk3FYanOWDtOVgAB7S3oHh0eeN5RWJj+a9TUe70WAFZdKIUv1FggZwktiyKkooHObLfAY+NwG7Q2GAdK8zEdYAAHCl8oNLP6wml/Gwdu7qnY3n1+5hFgrathoyBPY9dPF82YRadYpjCgRFS0F+Fz8GAMAdWAdKoA4NsxKT0ozQu43okLlEu1tWWBDURWKw11w4AbzATSZtw8bgfegQldAeCHW5Celzw8R7uBF+HiKAiJ9BiUTjVZBePb7IAHXNWdgFjh/LSDwYCaiu7XSueX6RAUEBz3ymMeNAc73Yl6QwfueQLxQV3mbJq7czC9VBkhpKempjyNgKgGEuDrFLQQGT6V12+6KQJb2PtSBs54x6dBSARGUlsgIkYewAZbY55xwFw8hFYpAHlTmU+1W6B1dpQg0OeCVy8fQH4egAA1oVsVoVs7jw6QJc8HK37mRgIwTVqBisH36phJjjgonNSg0kt4yncEDQCd1Pa4Kb0Z/PMPKf8UeItSFzUA/OkmV8kRTvHh39nModp0BWzphEGlglmh6VrQTdm1G8CS++oeiPjv5XNlQULe39z38M1NPH8GRAAkNAnesa7W/N2vG7RgZ3N1KFJSBRBDwOuheKVVBP7Jvxu+rk3EF1PCAwQTLoAMdc7uHZ1iYPenNm3GAPBwIgT+BeqPfSOEBKi6t4ONwS4XQhIK04vTC5dp7+EpAQAq1i3HHwe1cacIam3Jk9gxjjDVdvhFASIZANwo2gY62BzUmZ7phdCOD1iYZTaFlMBddrq5CXfpEHKB8PECTCox7IVJWNJ4OJpVTymfcJ4dnT4+KqBsGSgqdkz5eji7tYsGkMkdkGoX9FnqJkQzkkNEP9iDydWjcN+AT1vgK01f0YQNglOlhBXMVt3mBfCtbG33Cc1sSwjNbPIKC3ct820JbYgJrMwPbW3wCXYsUaX56WxSZJLkMJSi2XuV2cvMbjTGNW6wyYHSv4eNiPGF19RZ2FjUPuT9fC4sIDdg2civzJxZFHnCEiieEQ2jLDC7Cy46ckpW9u/7eX0nTvPtiYiO+mN4v3YP3gN1pcyVhqHc7Lhd3YprffkNJGDz7evz/fohl4FWFuVHBpgyvFz20EyOh0j5UjmSA93TEzUgmPmPSHDkaH+MZENRc5VkkpGOnwtB50eGO8QSokZmpR8X38V8uH7OPrsOcwW+/50s232zOq+BYBxIuC2NzT//aCzJcDcAyeUM/jxVPjv8U4UsGNtrzPTos0p5CoRkTJSCOdI4wU62KSCeQ5zE4TagHMWpciuprv9Taldy6JLWh4/u6Lnqr1U=
*/