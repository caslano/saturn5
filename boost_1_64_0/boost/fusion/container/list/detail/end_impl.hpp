/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07172005_0828)
#define FUSION_END_IMPL_07172005_0828

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<
                    typename mpl::if_<is_const<Sequence>, nil_ const, nil_>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence&)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
JkuqtIXMt4SzFZy1cw9Q1XkP0UOy871tSopDhn9TAqWBQD3dZvo2i3Qwt7Bqb11zWBerSfEeAVErke8TsTQ254dx/9APWEBUlpJKmoPfiYtMJJTDLq7dLmC2lnsqYtlOqc/8KWsaLx0gSsAIgCsXjD/0opU8nQJw4Gs/dfRP3LTWvTMIa2tDOB97XsbBQJU8fZ8o0x/2E0v69JO3d6yNj1xqbfcs23kq7blfvBVkMLJ5lIQ6/Uc/Irji3rE5AR8bueDwQ0DkN65ay6YWLZy5Lw8fQbrFmzhPE1bURaGPA4/OZJVwmjOCEy75W99R66NU9NfVqrabXL/gKMLfC7i0QTC1ylJLHnDNDrAHKqlIMkIiww7EcGCIU3xV8DBhsEuvMCAN11760BH9IR60EmQgRrUOhxLDDDbILasnRuT29VjtKZhG/OFLATKRpYSYUfDMklsCWj1cE9uEhjx74MRocL+aPuvGw3Bj79fbicf6I7lDPDc+BB1M+slsqNKAeiC3XR4aJZLFsID1oAjYto9tg/LS5G0ZW0gSbc3PCtYSOaSEEZlOooMgp+Rtng==
*/