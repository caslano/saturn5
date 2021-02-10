/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09242011_1744)
#define BOOST_FUSION_SIZE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply :
                mpl::int_<std::tuple_size<
                    typename remove_const<Sequence>::type>::value
                >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
IArOAj90rqApu9R3CcctM6ebjVaO3+9NTpb7GLNQZWNePKE/HfrnYOWFvYG69Cc0Gu6Hez3nNNPa3ahyBIOfYGaYy6OkEPXd6zvIrD9Z49K8j7LvCx3EI9sJhF221fDuL8fNlI3ee+/NfO/tzJ9FN45XQAvGri+n0Wo5p/eev5o6S9ngemgsqGkcvOO7XD/akFSnX15FcXARX02vguUNF7aVGNSFGixNm2UqUbYfSVGheEQiuxyNwumUPD8McEt6u6RjFdEIOkL4jy8WXhheB8vz4cXBKeT3l5vhbjVs+BtQSwMECgAAAAgALWdKUoWmnoi7BAAAYgoAAC8ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1VTRV9TU0wuM1VUBQABtkgkYK1VYW+cRhD9zq8YXT/UtgjYcdTUTRqVnHFMfQYE2MlJJyEOFrMNt0t3F5+tpv+9swtn586R4krBvoNbZt7MvH0z6ywmcPDDLsvRcPDdKzefHC+8b5xiwf8ipfq2Q55/geEPHRd4f0YoFx69vuT78CyvL7BnvPIx1lv9nOfPCLfQSeovVzsvcv2IK4Pn6D/l3b2gN42Cvek+HJ2c/Aov4OXhy0MbTgtGSQupImxJxI0Nbyuz8kdT
*/