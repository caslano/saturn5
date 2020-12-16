/*!
@file
Defines `boost::hana::find`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIND_HPP
#define BOOST_HANA_FIND_HPP

#include <boost/hana/fwd/find.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Key>
    constexpr auto find_t::operator()(Xs&& xs, Key const& key) const {
        using S = typename hana::tag_of<Xs>::type;
        using Find = BOOST_HANA_DISPATCH_IF(find_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::find(xs, key) requires 'xs' to be Searchable");
    #endif

        return Find::apply(static_cast<Xs&&>(xs), key);
    }
    //! @endcond

    namespace detail {
        template <typename T>
        struct equal_to {
            T const& t;
            template <typename U>
            constexpr auto operator()(U const& u) const {
                return hana::equal(t, u);
            }
        };
    }

    template <typename S, bool condition>
    struct find_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Key>
        static constexpr auto apply(Xs&& xs, Key const& key) {
            return hana::find_if(static_cast<Xs&&>(xs),
                                 detail::equal_to<Key>{key});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIND_HPP

/* find.hpp
POcC9bQ60ToRfKDjCu+2DwCvFft/MXNPlV818ul2OvXe4Fjzb+NI1OforT/wb3Fcizd+Do4j8H6XOz1XV3E6xTiHG/9z4q1/0e9m+RHu67auVPOncT1C37fmI/BElfmpfAQu4JnMs/mbo6w/LVMPD/HNZ9M99gu0d7+Go/iOT63Ln4Z/fsc72eLQn7+lA4tW0v11+mT34ie6J6mrPuKYCJ1LFyaK/+P6MB/hzxV0T89YcHyd3kjTz2glX/7GX0/Qlx8n8pPmOVd/N1lfyLpN5qf4JVffaQcfuBgfDYbDqZ5nF1/Qk/5qJX8a4RRcyOuNt4vERR7U7JKX4T6F7XhtPnyN0dWHwOOp6on/jKYazzJ5M4+uuo9f/gN+jIdr56mjw+BQS7p3Cd/It6QdrU5GWS+gswoe0Md8i15UVxmuM5UfWJjqvAJ95qV4SH5X1Kqnp+nVdnD/abp1f6hD9H+vC//fCL7jSwpj5uES/fs7xe0muL/E/pZn+PPn+YMF/DRc6nauvkgaXEnFx3vUK34tXtNM3x1u7sbju9TF3/JIPRQeafwNdG5r499kvBn6AAPpqFPo9Df5nK/U53N0ccTfTfzGC/SKvlrxrGb2e8jLB+n3I/QXn6RHp6tbenqZvndMXzQPz2Tsk9enGcez/Bx/FTsKrg2gN/vIC/jdc634wKEU+3onq5t+I+h441n4nb/pxMwh6ny6/sPD8JQuXPYJX1Hr/nxy2/54MiM4Ru/Sv+QPMsqcP8vfv4nffs95tvkX9+g4cbiNf+3C3z4Pf/rBL/qs5g59otPhDH1TLo/rMs2vOpxcGLw/9d94I8Iv7lGf/5Wnf+CLTfLrCX20znBWnc9Yy580wenT6e1t8s267T/bJILzOtNLeKbyPfV0rLy+Vnx/oTO6eb7ZfMo6/P4v+NNDXv4hb+Fi1jZ6/B0+CE93asNP/9fnv+Qblnou152d47nGe4736J9DrHvF9HWPt5/F6xniV3A/HRa3zo4na6+mQ/LlIR+VOVQeH8XfFcToZP2hfPU8VJ+Yjyk6m//7RTzdb0QLeVyOf/F88hR63f7I+q6x4GjdYNYF9Fh3feW78Uum+14hfjP14QY4/0K+MYN+O8U8vkA3pZqHcH9LuI4XoRd+TYQDdPJZ4rDNuIdZN+oDb6wfl26Cd+Zr+ot8wQB6Ovx/Gy3g/Et4g85daF1tVTf4/7m8WIB/LvL3h/DwffcbbH628GsjXHe0etusXreH/lN+tdDHP0M+zeCjxDXnYP6Uzs61byX9DvEqTcQP+hW7jds8tx2mXvX/o+F6wfV4km5KjvIVZ/KnS63XzYRf8De1c4wvpU/wzeT91uFcrwAvpPG1Sc9FgvhdJx/UReY1+FB8U/n+6n505Tz7LI8Tr0f5+en4dCscKpW/8yPqxvVLrAvFxLeLfE7jA4utQ/Hr7XurL/lcstx5r/Ev+tWpzsv9hR7fbD1ktPHzN3P40Dn6GItaWj94DR6o27Id5mW9OI/RF/pU/+sF/dBP4cwQfYAiPJVonCv4S/GPttVv8X5mSZRel4f36+PBgYb9eKfW+EvgNH2QudK8/0m3X6wfbT2v+FLxuhKvvY6f9tHVbaxDnsWf6/dsb6dP0dCMboQ//fFWEb38h3zAszldjIOfjWXgLXHPytK3PJG+ul1f4TDz1hPOnMrf7NQ/aosfKuiRF+HcWfT9V+a5kZ4cab36K89lvarwSbzZMzgmHw6fS43rdjqvA5x+MNynKy9788V9xGkrHrOOWngX3V8szwbqo59jPGfTv6fSR3RbyuX8yuPm/bfgmIrHF15KJ57sfl8n4nf94pfo0Qnifq16+ls94uWKr/FdpXVeOnEK3so=
*/