/*!
@file
Forward declares `boost::hana::symmetric_difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct symmetric_difference_impl : symmetric_difference_impl<S, when<true>> { };
    //! @endcond

    struct symmetric_difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr symmetric_difference_t symmetric_difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

/* symmetric_difference.hpp
N4QOtCSN8ZGWVBkSatXi4O1ZmR2+YKsBYTXRVhsqdLjVAgwUbzlxM67Eag04L2/w5ivws5sn5rVKxkPX7gm5ycqVSHuWP4ug5AZnAMVcXRn3FsTTLePeNvvGhNQA+/oXPVjQ5VwhVh51xazruLhL6ikm8DL5ADbyMlgXEHo1AwfGXm1sHcEXTNhqNUf4BTExIv6qWR84AGuAg0ZgdR+GEKyhsfgYTOVaziBMQo1FRM/cEVGj8TMREjXr47qyI7vjML1bT/DXdLtj7XYHGIq1ZxYyFmtNK2cwdtbr7R0cnB0ev4n5HpgUji3SdDgeL7J8MrMHZPxRjXyMCMjqKl0HZJLCrZBMQgcXlEkV/S8dVZ+N6PSlo+Pe+cFrS6AnDdkW6rlExPLnEmljC4vnZO/p+mUk8TkKe2DjenMlT8vxBQ83JCom67u2uR74RpEKEz6IVKpDwkipAphwaPPaF0pK4vZXjbqyCDIMNcGNDkQNoINC0Q6wX83rRaoxAt4fagyixyvGaRL+QFSc/UyNIB6EirUfjq4rvcUQdjNmWMpuBA1A2mUAgLTdhLODuEPFHVZ0kHeY0RH0XeIHYAIvg+h+cMpkbCSLNFjaxyMP39AhxXwCWKWR2YRqUNyNtH6jr4lECmjQHFLU81LISs5K
*/