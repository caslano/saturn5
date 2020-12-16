/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1230)
#define FUSION_ANY_05052005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct any
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f)
    {
        return detail::any(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* any.hpp
SijllErKQUqzQj9TBCWZUkwpp1RSqimmIsabUmIpKZQiyo2UzZQDRb74u2/xLb7Ft/gW3+JbGm5pqPh/fcz9p8TCN7bid5ifLf5fG+xpx98XKQ8tsf9d0gH4f/KaVPv/G8qY0doXduD/FfGjr5m/6v+pcgnGO8w1uFwnl2BnNK9/UmItsgFv8wjmDZA8Aoe4zhGDPAKTU13e5BAkN9HkENj2LVUnh6CKfUt2qs+b/IFw2fbmxtp+28W2Sxy2nbXQ7HabruJgIX5OdUjMrdJeh8dzBqjryVTFgjZLPcMop1ASKbtrB304xXkLc2fnZxYtLMh2H3e1PksurK1Sn5lXWv7WTPlbm9q/ZebNtrSrjdIGnZhjrMTmI2X8aW/Km7QrQ92u9Ozi2kHrXvZBgfE4aam/QuoPlf7vInHIcnX99m5Jz8/N8uJYyD6rzqugJvrvkWp7nZzn7vvf+v6o9lO9P1R1mZto3x9v0b81DnXx1nC7P47HjMuO7XmR7eWZT2+zzeBN9m0W1vMxs8Y62VXl3C6Y7fReLQvQxmDfoU3mTaoYrMdtebmD93HXSGufSxy9USPagkekLZXqtighV4/ydG56SpOno2pfqq19ZrM1Rpnh2L7ZRTnSbsd+zi6S/Q215Sos4LWOc3UoVx7Wcz7+gdq+fk/5PHnaYf/kuuvNdWtfHWLd1uN/YaA21v2Bch152hrr9u7400dG8W319Vti7Pul3n1Sb7lDvXKsvcwxyLTlkcxRH1s5PtpjG4rBATJHjdMxW62TC1CtnJObre2s2zGbN8Con9T1h0iMPkbq7yf9ZHrGVj/XVkvax4xCz+t3zLmJUvWVOkegRuo/IvX/LPUn2+svli9mytws2QX5mXkmj/LoHPPm5P3o4TFrpZoviWNmOa1lX6zHsrAos6BINWfDEp38go/Yl7It1vyCkcnxWVkF2YWFwzLn5eYtqkPOQ4s22pyHp1qqch5UeTZxJ1q28lojtoTb8fFWnF8battU27czZ7jPs5H5fqRP+L5ekFmUOz/f9l54jG3Sr8xBYc+pKrFcJ5SXSP9bPyeyi/mkkPeG6rpnn3PClycheRLez1Hhy6tomLwK8n35+4cnj1t6UuO0xRtzi7/3Lz18Y93zKpo9aY93lzvFDTs6xA1Nsl6gznqnO6yXLOt1dLO9Ehf1pjo+q9PFepNlvREm+e0Cw2S9APlOapIx76fg29ga92IPfAcjcR8m4rsOceAM2V4kpdwpDpwhz8DNxN44w+F15fK6UJ3XfSBx4P3YBasdx7xvNO7fFPt6fFc37t/JtnbI92+M1WnHdJlTIg0H4NmOY/nldQNdbL+CIt9f+V5rWe9U5XuFrJcn+QPzMQQL8EwswgRciEl4LmZjMc7DRViEF+DNeCE+ixfhc3gxvo6X4Fu4GN/DS/FTvAy/wSX4Ky7FI3gF2s73p2X/3JyfGbJeHxf9UEopl/X2y3on44Wy3gY53zbJ+fYUDsJncBJuwen4HF6Bz+O1uFX2/0Vchy9hBW7HV/Bl3IOv4j7c4fh+2SztdrF/USb5rgUxsp4/9pL1dkq7q+Q83YX98A2H/U6W1x/R2e8yef31GI834iV4O16PK/EuvAPX4Co5vuW4He/CKrwb38d78GO8F3/ANfgzrrXvN993jOcBb+PHelhjku8g+Jqct8r74IDDM46DsTv2xjBMwl5ynHrjHAzHRXgGLsMIvBUj5Xj1wU3YD1/G/vgODpDzMgqV9000BmAsdsGB2BcHYSIOxskYh7MxHotxCC7DoXgbJuJ6HIZbMQm341gsbsK15TzmhTjPz6M8jJbFxH8p1jkntp1gycvYiy7mnnA570TI+qMz90R9zTs=
*/