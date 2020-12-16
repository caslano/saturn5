/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_LIMITS_HPP_INCLUDED)
#   define BOOST_FUSION_FUNCTIONAL_ADAPTER_LIMITS_HPP_INCLUDED

#   include <boost/fusion/container/vector/detail/config.hpp>
#   if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#       include <boost/fusion/container/vector/detail/cpp03/limits.hpp>
#   endif

#   if !defined(BOOST_FUSION_UNFUSED_MAX_ARITY)
#       define BOOST_FUSION_UNFUSED_MAX_ARITY 6
#   elif !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) && \
         (BOOST_FUSION_UNFUSED_GENERIC_MAX_ARITY > FUSION_MAX_VECTOR_SIZE)
#       error "BOOST_FUSION_UNFUSED_GENERIC_MAX_ARITY > FUSION_MAX_VECTOR_SIZE"
#   endif
#   if !defined(BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY)
#       define BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY 6
#   elif !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) && \
         (BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY > FUSION_MAX_VECTOR_SIZE)
#       error "BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY > FUSION_MAX_VECTOR_SIZE"
#   endif

#endif


/* limits.hpp
azhlvUq+k+U6+aaUxy30wDuy3t+xDf4bu6GB8o5QwBFYVLZbMVyFxXEdOuEOLIP7sSy+ieXwXSyPJ7AC3sQnkWUN7bAa+qMrdsAO2BGDsRNOwS64HrviJgzA17EbHsJAPI7d8Rz2wIvYEy9hb/kGUxA6YV/0xH7ogwNxIobgMhyN2zARP8AkPI7JWInyTMEqmIpuOA4b4nj0wgkoz03kepBtQ6hv89wkQ941WIyNcAn64VLsgMswEJdjMD6Lw3ADRuNGHImZOA034Tx8DjNwq2ynF3ATbsOduB1fxR34Ou7Eo7gLP8bd+BnuQdkP5HqQfVNnP9gsfdu3YAPcjk1xBw7DnTgGd2EansB0/BDVcioi12dy3aasv7lSTlJfe0h97SP7b19sif3QH4NlP+6PgzAEI3AQjsOnJN4huB6H4nYchq+hET/CcPwcI7AYcUdhRYxGbxyBMRiD63EkHsJRWIQ0x2I7jMO+GI8D0YRxOBqTMRGfxiRciSm4BcfgmzgZv8Wn8SdMR+U9gpkYiHPQiHNxPM7DJfgMPo/z8Q1cgCcxA6/gQixG+S5CV1yMvrgEe+BSjMZlOAqX4zxcga/iWjyC6/AkbsDPcSPmvhMo11hy7VXf5p1AV6kntbABemFTbIId0BsD0Qd7YDMMweZowhaYiE9gMvrhQmyJi7EtvoBPyvbthHuxCx7ErngIA/CM47nXn/7cy32zfc++yqQ7F/r5V9p8xtsnZBHOEAwLnA3uhABCLGHJAsezMcfkmByTY3JMjskxOSbH5Jgc0//m9Jc8/498OP3/o636/4dIG81gedYygOCvPP8va/2shXHpCzH+tfXzFD+b5yn+lucpNs9b4szPpb4o4Dn6DUmrSdI6irCBtAaVs0lr6OiUmIhRf3p6rdN2TJ7xH5W0HSZkKs+sNGmLTRoRE51cmPcQrNMWokmbZlxjGedaW5amQj+XMoYnhWrzFSt9CQZIvvoQnlTyVT5/vnweeh3JzUeAJh/a5993JH3RBFeCkZDNb4NcdNL3p9SLOE16coqbx6FRyysQn3Nlvk56cpPz59cF5VmucoA6RrjC/LoVZFxe2+fIoWqylPxo3q/ZJX0M3pM6kC3HiLSKNs9j7XwG26rSH38Gq817nN3PX236IWjy10O+BRAu+RsqdTytknX+kkYn2pW/wuQnTq/PhCZtN0voH58NlTVpSwl/6Pte4Y/PS6TvxghJa4Qcn9Ns0/qn7If6x2evvH4y0qdghaRtsWxjF3M/t/h4UveA+2Kc7Ivyd3nnbYS2zNQxr9fJ89jnXR39ABz9AArfDyBO7QcQvHHP1x/988SGDddWFc+oOsXr3v0A/A1yXYeD5fmOE7IZNGNc1caW6I5tsQ4OwEfNz73lmgtNOs+9G8p6Gsl6PGU9jTEIvTAam+AoJIvyrWq5XpLrqPo236qeIeudiQ1xDnbFudgdn5F0zscoXIBxmIGjcSFOwiW4H5fjm7gCD+NKlHKS6xuOtzrllCDpMGEzHI1+mIR9MNlcTnIdgtE65TRBnotOxCY4CZviFOyCafw3BKeiEafJes8QcmS9vaU/xyP8+SNZ73qrsaob4wZsjxsxAJ/DfrgVU3E7TsYduAF34hbcgy/ii/gK7pXy2oef4Uv4Je7HH/AAXsWX5fnrK1gSX8UK+AZ64JvYBg+hP76NnTEbA/EIXlPzIdcY+J6UXwVcIvnsLvnsiQ2wn5RfMAZif+yBAzAEB6IJQzARB2EyPoULcTAuxqG4C4fhHgzDlzEc38IIzMZIS32RawV+o1Nfhks6R2BLjMG2OAqHYqx5PUyVC9o/UdbTXNbTQtbzBA5AP3O9k3MujtCpd/6ynvayng4=
*/