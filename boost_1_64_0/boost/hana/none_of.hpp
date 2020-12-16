/*!
@file
Defines `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NONE_OF_HPP
#define BOOST_HANA_NONE_OF_HPP

#include <boost/hana/fwd/none_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto none_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using NoneOf = BOOST_HANA_DISPATCH_IF(none_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::none_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return NoneOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct none_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                                           static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NONE_OF_HPP

/* none_of.hpp
lqAb2EPsI9wR6N79HS6vqhMva6SKH3TB3UeeyPsZQVcVZrmncpCtt4bUJsDIHjzDjS7OqjCwkexsOP183vV5P4MMGr6slkJnn5y5Fyz2bKbKtMCeWYp6bK4kai3pqtuHB/sHYDudq83gobvQBzjNAuJjVkee4rHJrnqt39o51+Nt0HXimMVVjosEzmUNrNPqGas4cxMxWgaFDONr7yO/vr4r5ytbdD/NYjEZ7+L9WN3XYZiwfq6vM/8rr4ctLERzgwg3iVUddR8SoFF1KDzGKNYcHypEgh7vE5ZHb+C8UcZFkFV+I/bWLw7HO+MRHg1JJ7ZrbVtvtNfaorSTSNYoe3Z8ljnOEHoYPw4DWTaC0oC2KWbay5IN23e8dWlmd9Qxx7OcF02VR7gFtc5XR3QeHJKvrUMXKjofSum4wi5tzy1VleLV6yQFZgmoYXP48KMc1+m8KmUVB6k6zsAVJ9372qc4rB9CH4DbGrS1xp5700qr4IkLpuqI4hg5dMIANYuwVnSggTju0vlpj07QBAX21Rk62D4umKojO5Z/5XXP1GVZQ9ebWjpDAz5YorfgG7p606by4tgPmvm0Fm39A4ofx+ufKbH7e01cEL0TfXoLPXoY7QI31/IS9Gz9A7rH8Pqnq6SqmqQEOe2n0gKfJVkPsI5PZOKlYd349l7Bd2FV/dDcaqwMxG0r3urY4ddFmJchJHSiCpBVus/07PChfvCg6MpgEMBpntkdXRjtuqQ1KjqLnbGtytyP6yjTY6s1sta2lPYrp78QO7IqKRLQpf5iy2gXo6u+0eiILha+s0/meZBIGRRGNYm29uTLG3F4iJXQYzZZlnmqv3QELE+6dMdAgYWJDYH2HOL9hRu5/JF4JTYVPxAqVMiGukftj84dTHf05af3zp3wumDhOEt9qQKYyf1e91tkD1ti2MTAI70M8LixOcOowNCbNtj90PE9oliQN3LPZCiTVbozX3i7u+qxRVkMQXPlXuqmRtmPNth18lWnDdhb6zhtUi8j/b7ejIf4v+7DjK7k185YVOhDHWSxn2peUE1h02/w0f3ykLXjVjd283sEpYpCJ/WS+w/DsURnBK8fVgIqjyqQdcuT/21IWM7SixzPqbqI6jiRldByjqG5QzbKDs0Yd6yoiQoPbICzcQMsYGr1L3mj1uTNo7OB4zkdNE0U+3WiIoQggFQ/HqdDM8EBi2OkjmKxasOMsrBTxpvFRJBS9w6P8n9xPI3wcRX3g0AY432H9Dbl3uQ+ahHGWDY5rtHR5dKmvdXxdZOx8vvJBUTgC13ONdpbOawSdYvMq2UJBRVSWYOXkKm0rWgeYzYvqLG27+EbBzzv8ldfweTPUqldPRlg3alHkM2hRmPIM7tmh76v9C1p6Mm4R5/EJMx8m8fPBGmcsBxhf+C4IBRBuoyquII9lLaDf2q3ccECzwrTBnM/7ufCx534jj40fGGK9/1tRNxf3+vtmzd13+HyuEqTKAuFyjao4UdQe804+9HVke+bCceFsfPLpmlkZF6dh2cPD86P9smMtmfP5bSjFlGG22ZY4AAZHSpNmHnhmIBftOKbPxlf2BHdGcnxLOZlkfkpGOgiGVRAtqQz0mkvZNssKxs/SQSA7Wypx5TNfphEg4nekziepTjxvAqcKC4y+xdJMZ8A68yzTHIslVZ3fRlEKY4tx3MKvAK9D1bbRaaiWiIZHrD8bEyaHJIf9E0a+DKIsnVyq5s5+qYMsmfWJIbuUGva6A2N7OZu5u6FdZ14VSrOztewmRaZawy/Oz2R4znjV9hPwzoAbW7vw9bn2KGbiSLP8jwtpTCqVbDR/H6bHYL7uHyA41qu0qIuI+ysF3s2M1Pai2/m8nM=
*/