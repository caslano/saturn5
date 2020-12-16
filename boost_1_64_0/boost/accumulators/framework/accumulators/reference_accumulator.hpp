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
KPYIJDxiZ6bXf+rEtk1Omv6QqTS1T1P3RtgQ7Q2d2MHnU6Xlmj/oqyx+1MYUMckC5OYyIS9T6gTyMicxcUE2OeRdj2fNkzBcac8ptAuJxqbfknphX/YNkmn39aXyBCMndTU7IuO6KfvzvJc8gsu+NINeizpCe4ou2tlgQerC3e0vuuX9+DvMD04VsTN+MYmdjJB1kWxCR4ZkE1qCX9Ybm8PwpSxrG+2L1fzYvOgpv4JLL1/ir7aI9z8jZP9TR8u/nNo5e7C5blEn3sPw9NIje6Qtd12M8cEbS/NRSQHqisWbUEHbyouvQD+/0IkjLBGM0WvhABldvQhfOL9E5b1UTBedzB5kx/XAPfjPvfRjSCmwayIdMs6a4OAG/n2x9VrJGdRkH0iTvfU8Ztfxs2MX9g6i0a8yh/PBLRI2WqArJsZQ+/RkyUPKWHeVXFOQlwDxDJDZfgEPHvP1C3jAmi9fIAP4kd5Kk/UO3vADEwzj9QlGDg/pD6wB2K6OH4hbfoCIjjxa2XobAxY+4tgoR2dLByIlm7hhlBCPYOLFHttjZhF7RN9RZxMV5s0q/ssJioq8zqEiM/VsFfNRPmQZ6YHmho3aqMd+P0MN3XPk5KNWnQWqk3yt/hOnVtKkuS9swg2Y9T1U4F6UEqRvPiN6ns9eaDg82EsdhKYleUvJkRcHM29SYVqsF15yEy+8XDwJrJmnxPfYLw79TCaMCh1hwrjkR2bdQxHBi8NBGsn0VC+li8gbFDrVyNwwjXfbqPtkcJLLRbrYi7GKWAgtr70ELEvse8fJVlSYbrHKhOPV/qPYZ5BVDirmW7RlB9XvXtGyND4vd80sNWX45exk8nO0ut+O1f2HZt1Jor6ar84wvnO6zBTX8O8mczJ+wwb6XFjeEkJX5Fyka7YFyfwy3v6UncVO6eJOO4sP2wYhjO1viv/rWyz/D8wRYCGp5/8HPYv4lf11/x5NTnHiPZqxZx7kPZrMo9T+z57v1JuO6nZHa5GClTme7Ob3McTkO3rxVMx3/TGU8YV1PVO+MNnRMRvD/FFHm4u35cS8Z/ZIW1V+JOaU6m+bI3pa63j1hDXTVStvlVb+ZDO18j1o5ZXm+DzqSJIMHySGSnZG+K1nR1i64N2l9IvcYK0tVz3UC4UhY2e4ahWftfFZub0ab2RbJCzC+Vg4ky4uNJ3EplR3V8hQvjIe5ww+5VPk6sZYRQY534aaiZ8VOzbxrNj4SWFwdMHHe2Qe8SGmrPEvUIwFpZJgtkpwS6E8/w11SQs+S7YuPDopdIUK/RZbuV5QEcabNfgtojliMMKB8Y08J7BJCB2xbuIy2DPDsXLS0EwnDcqkQskrl/aWpA0kTfIGTF2RCPx4Tohr4nv1p8I9igSW4DEivseW0yqIK3UBjraMuRqJasfJO5NtF8HXbs2bpTWHbrJac58ZJc1WnbTSf9A7kof6Z923ffSs5LcAeO9Rg1Ka2/ft6QqHThYeugv/vEBEJ/MShYbuwa8/pjkOEQu9s75lqMXDPuIBrICJ/RvdaThtuhRsKCjQCcJDKKZ7VO6wpo/6XfjnDRMf0dF+xQB6ZL7h0KJphpahRf0ZtBmloKy3RvDOCprPqatJuv92pjU/5YN1QgELbFT3ziohJB/4fpTal5xlxdc8ULhh+cyHNSffr50CG7EyL2kNjjL35TKaKBuZ6yX1kf7Qtp0nrsUd2ZEMOIeSVsivBg/0QxhYhesCqDhYaVzSh8X1LERACCcXPvGmNB+7fY6NYPf6Q1WeKwuTyrNNytPRpTyndlOe/NTyHMNFQSlQBjpqg3Iao7c3luJO50efn/Ou+++Hz1Bcz8sH14IL776lL+pJwMDi6xnc/dk0C9w=
*/