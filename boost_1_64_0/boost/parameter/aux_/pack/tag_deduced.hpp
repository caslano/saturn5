// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_DEDUCED_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_DEDUCED_HPP

#include <boost/parameter/aux_/set.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply_wrap.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Tags a deduced argument Arg with the keyword tag of Spec using TagFn.
    // Returns the tagged argument and the mpl::set<> UsedArgs with the
    // tag of Spec inserted.
    template <typename UsedArgs, typename Spec, typename Arg, typename TagFn>
    struct tag_deduced
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_list<
            ::boost::mp11::mp_apply_q<
                TagFn
              , ::boost::mp11::mp_list<
                    typename ::boost::parameter::aux::tag_type<Spec>::type
                  , Arg
                >
            >
#else
        typedef ::boost::mpl::pair<
            typename ::boost::mpl::apply_wrap2<
                TagFn
              , typename ::boost::parameter::aux::tag_type<Spec>::type
              , Arg
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , typename ::boost::parameter::aux::insert_<
                UsedArgs
              , typename ::boost::parameter::aux::tag_type<Spec>::type
            >::type
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        > type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_deduced.hpp
0gmnObygpNiVyfOSbyNzlu9NUt4j7fb0lvdQM+G0p4j7OZStL26ExdZf8rOQx/ZAOtexhet4XdI7MyHHnmcNCXKmMvnmhNb3UjFOrxdqJ5N/p50YvxEF44tLdDW0rgFW/z/C7aiEc8CLR4wbPybUjjaT14vSjgYlxrNX+UTMJPr6n1ktMox2ZNq+jmfRfVJrKWd8IJn20JkVGOH3gu4irzYqn3D7CoTO+KW+20u8XQl7g6Gxokjy0I6FLmp4wUin9RVkO3tAifMG5TxLyvlK4rscBrQr/iJb91VrW2Xw12vuzjWneu9Z7aiaad1slHSusZOtjtYZ3DuXWxOtP2j5DdjLEC5/PWkns6S87zljpZR3d8K+oLcvnJg9nhLm5JkOybSH3NdC8ybpml7vUP/DM00yd2pX0sXdtIcLSbOz5LWbvM6VsM8mtAu2DrjXUcAWwclZvLhIuExkuETCXZrw94gySefuNJBwVWlePFfLdZ9jN2dlRnjv/Ha5zsGECfXBR0s9vc2zznWSTwr59JN4WxJLaQ/R5cnW8jQk3DVSnusSbqU86bqvydTp8CkleXqudmvqx7Qr73Nb1gTx7/nviP1PZi1/rqR/UcIxgWbWxsAR1qZgL+vy+Em6Rzh8j34c6MaKnvRAqPw7kOdKiVeUMDE4124cMY7Q4Y4v4enB1J/pb4olzuncp13KjikmjXGcyO4ouXDrvd2rIR0C4fu4g9i/jptHW/rRno3cw/eqZBm6h8Pr+x1nfbe2+etcuZ64kJ2/LhB7TStV74dQPzU0mG9R/84Z9NV4D2bwvpL0kxJm/pgUn+TM64lfb9xfxEyP8kvHbyjumzChucBZNh7e90hzbe++pvkTZzLhN2JCcxizknRuxphmWp7CulqewMzSpKpxTHckBdomxSUkJdaznDCbSSOfMNP9w0j59hAmt264fDO/iFW+Z6R81aV8GYQfhrkilO4Pscq3jjCfyJzErBuSgrWTAslJCXFJQYQTL3thivBfg5kRus6HjS/5hdNK17R60kgXpkm4NUmBRN/5kr9LGYNyXetJtztx5nviyLsk7p1xv0HdHbdE7O0xKu814byjy7DMLcPNSYFQPr1xW6r5qLvkMwS328L54C5zU9gXhfPBLTqfVM1nT4bKre6stx235dh3Y0ROKbO2xZrDWC9tOM3I7kL2p6Srnonw3usbKc9NmEUYx/1meAvmVrWzN4ywZfeGveL5+7Y0d/9i56Dvvuw+qT77F+n/3HOz9V3ceVdON+/K7l6wdM+7bX3dEzZB3U2fpnHSdM9yuvteKOlnhN31/awZbg11riQ9xrvTkYTJDIcpxzuRU7YW4Xyi3mUa49fapOXz7oF/W9WFnu55d8BdnlGdZ9c6nmdX3OWZhD4Od/OsImXYG3aPek4hDmO27pXzjOXEYazQPZ9R4wh+jBO63y5qDEGu9KnhvCQXOfN6vIy1rHvUc/p7vBppvyLK/mCUvfprUfGj7P9+PdJe642QnWd4mbc5KXy+vSoX7xZeZ45JaYSM33L3tjFvoxM24emb4glFRZxEnpcbPX/jN9dFWjo3xf0VxH54WLdBOfbcy7yUtvs6mod3TnN5o1DgyzTSpZjfuKaNofKXFBZ3yBqT28X7yqL6NkyZTX+4SeJc7D9fp9fgM5dk+pMXJcxE33k84pdLd1ik7g29zyP2gWq+UXJY1VjPDNbEblA5DNviyoGvsh1cQcSWQ67Euc5PDqR3YDnkS5g5fnIg/l8jh/Ac7vomeuaRJvaZyiHz7Qg5dOzS1SuJ2LJoIfG2+8mCNA8si9YS5mM/WRD/r5XFi5mhRF6wQ3weOrLo/U6ELLp06Fg+WfSVeM/aPrI=
*/