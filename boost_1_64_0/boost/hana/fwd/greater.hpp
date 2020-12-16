/*!
@file
Forward declares `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_HPP
#define BOOST_HANA_FWD_GREATER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_impl : greater_impl<T, U, when<true>> { };

    struct greater_t : detail::nested_than<greater_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_t greater{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_HPP

/* greater.hpp
dXTNWkgXPP5d7HXEf0dpkACmsA6nsVEjLTj6Zze9u3e98Ixpq8Dqi/1izpgBrWYg9qyzuTei80cv7/kHqwGYYO1PvjZV8f7vE5L9yxUkdHNgX3t545tlTKa7ApUHGnHJMrbMW0DhmXK3aV0B4eyMDuuvbuLeX4exDDcxOZGLeEZaZY8ijlD8PVWXXP5JHOephfgM151edu7OW2kV60Wx9iWuLuyn+KkGL7zbVp214YpGD0guD9djnNmkc6teoPOdV4mtsWP3eGdum3Sadr8ML6jV383veFxHuTx+M2xmfy2yd3KbmEE6w/w4ddMPnLT/pzd5/xwKYec502peI/QPRNj0DYF2XHvVl7m3Y9OcGfIn5tmgskTUuHFSRY0Hp1JRo+LkEzU+r/rSfnRH/KoQNX6cpoiaQmILn5lq6wIbHJRDAFfr+aoYV/fxVQmu1vJVqfDjejVfT8GrEVEzDTfu5Rvl2oYARSvh/nLDn4uNfjZTQM3mwAP49XtSXWd/6AxViJaKWKjKIZqq1py/y/sxpeziHVfw/uLB/b2vghBBYlYHfkAZbAj8mE7r+JezpkZEaiaE5qzq2/epp34mauasOn/Pu8bPX3V6XWTsN0SoHkWXrzrzyl3HbhE1oVXnrlr+9kmrTn/wT5X/0hYGFiKvDZK8KlGzcNXpnx6OXYUfRaKmbtXpu69eUeDawGSCIV78XlZEwbrARpKMHmBPScE+Wj4meEbDdfBfGpawDB5Z5l2xPf9x74R1gSYn0u0Gz1EnF1Mj9hWcDcpSxUWkLha7O/7pDsqMg+e993f7vRM2BFYiecdxf/6Z/AviIIjYROn3oODNxPPCQKEsWsxBcXNQfI+GK+/99YFpKhEi9nX0qsHt+bjZ8Xc1/4DRlugaNa7DSBClKWtBt4bfGq6Ce8SB4EFx2PuDfc6O3quC513780/n9wijjTdwo4OKdpzwTivoeFBmp7p6tI0BalgQVAqCNgZaQfrkhYHyYC/ebyG2kSx4JP8xDSkwDy537UKZc4yKuM+siIBZEWvNigD3qAKjAraZFbBTVoAqywsuR949nPPDwe3e+x9Tid9d4J6Zvk9SOYeZbgHTAWIahR/QcB3cA6aPB48w289cBaZP5B/W7mcKtPvQIsz7Xsn7apmVD0w9RDIASWcBqADTmNwj76rgieAODXc0JAPDhyEG+5F8NcnAw3hQVbAjaGR0kcQyiDwkp+CcmUVxh/AYPK8LPErlHizYA2Z9VA4z62NmK5KYJVZ35RM/9SCvijldIpA7c1rFnJYzpwiaTzTxM+D2OEp5korrQbnHJJv3yiaOgL/lrovIkWhaRwyjZpj24CPgd6GGJ8He4Hbs4rXOiSy6kWwtM2r0FZAxreBwUObIW8EXBZGn6GF+n8CCFybHOpFwGLQ8LTne4boIfv3oWESxzC14Mtit4aaGohEjga6LbNSOf6j5FzuOqwJlgRt0XNcjXO6u4EHqxljzY4fFMsk0dWCT4bWS4VOysdfJfv2csZIUxDoKYq3+zc37OJoNd4x3wcDZ4PNIXO7aQwqk4Ghwn5G/hpso+QREi5j9h5vkuAcUHkCB/VTELpQ1YHZl/E2AkkbFkqq+GERHUIm94Hnwln8Gz6sgEXNQ0EGWoj2gbWnwuIiS7HPz7kdVLRS7EEDm/cFjzvyHXUfyd2iy6vF2BKXSFMnU2RBJya1CDXZG9iQNuTF/pcFW6IfdQagMyeVp0jKuPWIf6ZgJUVTrkSAypeoGizKzDHy6nQafHqfVY9UJBD/4Cz4S3C0uSibBLfgkVQcaolzYbvATESgKWqKPig0e0PALVO0KPmO1aP5x134kX87NuU42p+qk5jQZ9Dllp0U=
*/