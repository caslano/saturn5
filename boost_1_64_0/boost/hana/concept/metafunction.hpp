/*!
@file
Defines `boost::hana::Metafunction`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_METAFUNCTION_HPP
#define BOOST_HANA_CONCEPT_METAFUNCTION_HPP

#include <boost/hana/fwd/concept/metafunction.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F, typename Tag = typename tag_of<F>::type>
        struct metafunction_dispatch
            : hana::integral_constant<bool,
                Metafunction<Tag>::value
            >
        { };

        template <typename F>
        struct metafunction_dispatch<F, F>
            : hana::integral_constant<bool, false>
        { };
    }

    template <typename F>
    struct Metafunction
        : detail::metafunction_dispatch<F>
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_METAFUNCTION_HPP

/* metafunction.hpp
7ZePM3MX6f4i1mFszEflmtbW9Z437DVgrc6D2HhjZ/YfNV/P6UM652XA2pDOSlCsrzGf59RvtbZi9j27NPvo+Rc/RHyjRTfaNX2n+rR+YvZ8H5pbeKWuT+xQEzcmOeBZ7U8B+y6PbP3OZ7oGsUNM3KPnzLhZ9ywxW4fZZ9680rGkmJ2Hrw8560Ld58V6G3vsxs8m6RrE+hi7+eZuq3XPEtvG2B1rTh6jdymxfsZ2m9g3pPUTs3WI3D71IO1dse2NXdn/1qc1L5JorzHvHRMP1DutWKe74q4/jtd7qysufG2/HtrzYu3Gnrpt0CPa82K9jE2dcLn2blRsiF1DaOZLmmsxu74jx719g2NzxOyd6N49Ltb3TIvZPvtXcfJf9Vxx2Zm5o9brfVDM1s+7+2U6f0UxW/e/9fr9Vbp/up75+YL+DZ0jsQ679g9P1fq1H9b5+557+7bbtQ5iPmOPBh55X2dMzM7Dii+nTdNcu6x89BPXa67Fgsa2OudXfTRnYnYNE6euv1Vz5rKxwzo250zMrm9KduIHOpuuuGvXbVXVO7TYzrbuV3bXu3dLzGvsq15X/1pzdnjnvy3+MOYm7eugWB9jrxy6dLXmRewIM+8X3P3odro+MXsXHj/6J1O17mLjjS08+/OHtbau71v0zZT9dQ1iOxp7eZuHJmptj+h8Nl683YKHdI8UG2Ns8t5P9dd7gZhd+w0/tg/ROoj1NfbawQWtQ0lsO2NnfLz1NK2DmNfY2Xt8Plz3F7Fhxg5YPUPX3u3IznfvV86461utkcsWXTpwZ70XiNn72YU/20X33ZBYwNic62dcoeeD2NbG2r6c+B/HkmL9jP3lAO9ivReI9Tb2wMBn79D9WmyAsQ87dhmndReztT1twRl7aV+L2fPhpXdrZd2vxby2P+vv+nWfcK39sjunPeGY56ed63fuuSv30LNKzJ5VM17bbaCeVWL2+1bOimte0mKTTdw2A7Z9TN9TzJ452fdnZvU9xUYb+2Kbjte0tlM6z+1Xz/TaVudPbJCxX+20Tu+mUZc989SXfbR+YnZWHpq1rKvOpthOxl5t3byf9rWYndtuR513o65BbH9j8cn/Oknn76jOa3gjseRN3SfEfMayvnM/0zu7mO3PeZUdcpprMbu+Ptefco7Oppjf2Pt39n1de0msq+mlc0IdfR1bIraVsYsXX/eozq2Y7euzXszo2utidh5u+mTKxboviW1rbPARi+dpbaOd19dIvTRJayvWy9hbb04Ma87E7PpmH3r0Fzq3YtsZm3vgqzpjKbG+tnf9j83VuovtbWflg/vXaO+K2bWPjl59s9ZdbKixCaM/+kbXLmZ7fugl/mt07Ud3nqN9r8purf0iZvulS/8Ph+naxXY11q33T77XvhYbYyzbrfG59oSYXV/ro+320TWIdahtqPUxq3UNYrsYG9t7xUjdJ6Z2/tviotWrx2jvivUx9t7EO5boHiJm1/D6QXfoXp4TCxobv++hUa2D2FhrJ35/gWOeY+RPJLP3PHLQK/qeETEb9/C5uxyocyTW09jJ2WxMe8JlD4SeulfzKTbO2Ks7P6y/Ab4pZv/+m/FhtZ/Oithw+zeed57OmPdYua+ZNWz11ts3OTZDzM7m9udMn6B1FzvSxL2w97juOu9iu5nvO2jbQZP1zi52kIlb9NPJun+OO67zffe0FbvrPh8S2908c9jopcu1tmJ7GrvnD2t/qzkTsz04f0H5Ve1BsTHGem915hCdleM73/UPvWbS7zVnLlsxZcIjOkditg75Bz46THtXzO4hnx436xidMbF+xva/+ZefOHas65n1Zt8nde9xxe31WeI73Xtc9t+OPTSfWZe99d3ypP4=
*/