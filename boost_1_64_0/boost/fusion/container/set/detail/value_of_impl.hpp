/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename It::seq_type::storage_type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
5TZ4svOsT7N7c+JxxBaf6fDbUV8+ndb00u+P5IeebbPjKn0JbMMLPhnXalXMMzUX3XSqUsMfNu+xxR5ieLbXku8XjHxi/KKOd6zz6O5e9OfFo3IVXyrCVp5z9yY8uKnRd7suNYi7eHzhgY6u42+Zx38qf5ytbFs5F25e/e6nx/z9FxwbnZPywKbL5Y8TZh4Hy1UcMtfxsTyYD/OPWDvo0jNp3fM6F/79618faG/r68rw9WNfq3rzfb9sa73zvda+627r+9e/+3qTLT7WrwfGjzmdc9fmuF8mDTrZq8jlu8pdx0Wz9Xe0yD1k7EG6RF1WQR/ZGAMl3ks3DMTueBWDLHLfF+fIdFWxs0zXkfG8sRMOwi44A/1keisTXpDpuU/L9IzLvxPkHvMoJR4PRmI3HIODcCwOx3GYiePxMbwT1+JE3IPR+DHG4BcYi99gAt5EHonYGpOwI05CP5yMPTEVh2AajsR0jMYMTMWpuAQz8UHMxt04DffjDDyKOXgZZ+K3OAubsKyzsTnOxXY4D4fjfLwdF+AMvAdn4iJ8HO/DVbgY1+MS3IL34ylcipdwGf6OD6By//tBlPUt925ZJybruw7jeaIH+mJdlLhici+WZZDptHHFeku/2GDsiH2wD/aV9dUPIzEEJ2N/tOJAnIahKP3U5B4q27Xko+2n1kny6YyB2AV7YVfsi354G/pjFAZgAgZiMnbHeXgL3ou34gPYAx/BIClHCClfytFPylENu0s5fKSe2mIAtsMgbC/l8XXMp5Lc/5T7oZdIbTXPcxyTuFfHpbwnMAnfkHL+Xcr1Jq7BQnwO38Kd+Da+gu/gBTwt7f1ddCeP97EensVW+BEOwH/gGDyP0XgBrXgRZ+DHuAA/waewCJ/DT/EUfo7v4Rd4Ab/Ea3gZf8Ov0INl/Rq98Fv0xavohz9gH/wRQ/FnnI2/4pNoi6+F1dR4THK/EO8lXTLEY6ov66OB1GdD7IiNMAAbY29sggPQC8OxKY5Gb7wLm2ECNscp2AKnYUuci61kveaT5L4hv0nt5VHOW5ZLeV6X+EgnsRWewg74BvrjmzgQ30YrnsYZ+C4uxvfwQXwfN+EZPIEf4N/xI7yI/8BqynpEd7yItfFjqbcrleWeoNwrVMp5p4X1icrnUynnF9gUv0Ef/BY74zXsi9/jYPwBh+N1jMaf8CH8BZfjDXwWf8ODqMTFOQ1V8XOshl9jdfwOa6AnhXNDL3THFlgTO+NNOAhrYTjejCOxNiZiHcxBD1yKnrgc6+FObIxF2AS/RC+8gk2xFXXgje2wGY7F5ngXtsAEbImp2AqnYWucg21wIbbFpdgOH8X2eBh98Th2wBPYCd/Ezvg+dsWL6IeU2eKPjbAb3oLdsRcG4TjsiROxN2ZhMC7DPrgW++NmHIDP40DciaF4FAfhOzgYz+MQLMIw/A2HYhUO4LdhAxyGbTAc/fF2jMEITMRRuAgjcRmOwYfxDnwVo/AYjsNCjMZPMAavYixewzhU4kfFYy1MwNqYiG0xCbviJByFKTge03AqpuNsnILzMEP6GR+0yL1L6CPbZwP+vZPExxZfrCFasRlORR/Mxt44DQfgDAzHHByLMzEGZ+FknINTcS6ux3m4BRfgGbwHz+FCvIqL8Ge8D3/DXPSjfEuwG96PQbgU5fjhuCfJvcrix49ecp7VV8rfD7tgCN6KA3EUhmI8DsJkHILT8TbMxWGYh+G4AofLcozA7Xg77sUIPIAj8W0che/jaPwAI/EyjsFrOBZ/wnESp288euOd2AknYBe8CwfjRAzDaByFMTgeY3ECxmEqxuMCTMAlmISP4iRci8m4HlOkHqMqqfcQWSf2evRVllfq8UE5z30=
*/