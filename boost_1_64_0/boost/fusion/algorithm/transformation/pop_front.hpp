/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_09172005_1115)
#define FUSION_POP_FRONT_09172005_1115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct pop_front
        {
            typedef
                iterator_range<
                    typename next<
                        typename begin<Sequence>::type
                    >::type
                  , typename end<Sequence>::type
                >
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::pop_front<Sequence const>::type
    pop_front(Sequence const& seq)
    {
        typedef typename result_of::pop_front<Sequence const>::type result;
        return result(fusion::next(fusion::begin(seq)), fusion::end(seq));
    }
}}

#endif


/* pop_front.hpp
H07Ev2E4voexeACX4mF8BY+gUt5jeBmPI+XhJErGzpQxNTMJJb8k2Q4+kv1IATbFT9ELP0N/PI2z8Etcg2cxEy+gkt9FPIWX8Be8jLfwCjor54/oilexOhZhTfwVH8Ab2AlvYjf8DfvhLYxEZxeWFyvgU+iC67EibsFKuAuryXUDNyzA6ngaa+AZrC3XDe6X6wZ1sLpyTIc1sTHWw6bojR7YF5vhIPTEEGyJEdgK47A1zse2+CS2w+XYHldiB2kXfC8g43OyPmQ9NHOiHLIeNldUt6dMbIcvYG/cgsPwRQzD7TgTs/BJfBk34045/tqFf8NX8Di+igX4Bv6Ou7E+ee7BrvgmeuNbOBrfxqmYg7H4Ds7GvTgX38NnMA/T8TDm4BH8GI/iJfwAL+MxrMyyHsf7MR898UNshR9jeyxAOe6WsTtpuybH3RGV1HqKwm44DfvgdAzAaDnPjsEonIHTcSamYCymYRyuwnjcjxb8EmfjNUzA5uSfiH0wCQfiPDnvTsEEnI8puEDOu1NRvm+UMTnZ3ky+b/xDzv8qKPWPLtgXK+F4rIxTsArOQVc57r4P07AarsXqsv5r4tvojnuxlhx318ZTeD9+jXXxJ6wn560NUNk+H0A3bIRNsTG2wCbYBpuinJ/J+JysS8J4fjZGzufHYnscjz0xCKfgBFyIE3EdTsKtGIwv4mTMxSn4Pj6EhzAEj+DDqB3nypib5wjjce4vcv/Fr+iJt7Af3sZA/APHoXNVtX+rgPFYEVdjJVyDrrgd78NjWBU/wur4BdbAs1gT5XqhjIOpjI9pf72wDtN1wro4COvhCKyP47ABTsEH5PyxIc7ERpiID2IqNpHzyma4HJvLeW5LfAfbYQG2xy+xK36H3fAnHIvtKNM4nILjcTYG4TqcgBtwIr6Ek/BNnIL78CE8jQ/jRXwEf8UwVPrVcGyLEdgFI7EvTkc/jMZwjMF4TMQVmISrcQFux1T8CB/FU/gYFmIa/oBP4E1ciMrx3yL0xsXYG1dgHKbjSlyJ63AV7sTV+C5m4FF8Fs/hc3gd16ByH8Q6dMEN6IqbsCluxhaYiXK9S8a8pM4I4/Wur+W6wbfogd9hR/we++AFHIIXpT1ckvkWERaZ72vSnyjt+zxhzVLme0PmexO74C3si1WV7yexGlr7DdyMNfANdMd3sDbm4/34GdbFIqyPN/ABrEz+DbE+NsL22AS7YlMciB44DpthGDbHaGyJ8dgaF2IbfArbYiZ64cvYBeW8UcbBZJ9HGM8bu8v5bE9sib1xOPbBEOyL89AHn8B+uB7740b0xU04ELfiIJT+W8ao5FjVpP9+UvZDS7AdLsWu+DQOxuVyHXMFRuNf8RVciXtwFb6Fz+FJXIff4Xq8gBtl/7MJu+EW7ItbcQxuwzB8ERNxOy7CHbgas3A9vowbcaf0m/TljAEp/aYsl/J9RWPpn8LkOCRCrptGyv4pBofgDByFsRiOszAJ43ABxuNfcTZmYYJcR02U60JzMA/n4hFMxuuYgkq7mo/VcQHWxFRsiI9he3wce+JCHIWLMBifkuOUpzEVn8E0/Cs+jyvxNVyFu3E1vo8ZctyyBk/jOjyLG1DOI2V8SM69Tc4jj7io9XUUO+MH2BOP4Ug8jkGYj9PwIznP+Fiu2xbI9dpP8Cv8FIvwM/wF/47KeeUp7I9foB+eleuuX+FE/BpD8Ru5DnsOE/A8zsdv8XH8Hp/BC7gBL+JOvIR78Qc5jr6Mn+MV/Bp/xJ/wKjop1/+xM17D3ngdffFXOV6+gXKdXsZOZJ9qcp3eT9rbEOyBQ+U4aBiG4nCMwhG4DEfiRgyQdjUKD+FoOd4Zg4UYiFdwLF7F8dLOguQ=
*/