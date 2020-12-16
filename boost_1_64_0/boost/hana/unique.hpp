/*!
@file
Defines `boost::hana::unique`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNIQUE_HPP
#define BOOST_HANA_UNIQUE_HPP

#include <boost/hana/fwd/unique.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/group.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto unique_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unique = BOOST_HANA_DISPATCH_IF(unique_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unique(xs) requires 'xs' to be a Sequence");
    #endif

        return Unique::apply(static_cast<Xs&&>(xs));
    }

    template <typename Xs, typename Predicate>
    constexpr auto unique_t::operator()(Xs&& xs, Predicate&& predicate) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unique = BOOST_HANA_DISPATCH_IF(unique_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unique(xs, predicate) requires 'xs' to be a Sequence");
    #endif

        return Unique::apply(static_cast<Xs&&>(xs),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond

    template <typename S, bool condition>
    struct unique_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::transform(
                hana::group(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred)),
                hana::front
            );
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return unique_impl::apply(static_cast<Xs&&>(xs), hana::equal); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNIQUE_HPP

/* unique.hpp
qjLx3d2ipA9Ql2EJv3Oj5TcvqYCmvHIgK9Pn8HvvQmNwagZt45xVoHGwj6B9qG5oumtF3oYfNhRtq8uzScjed5vqd0r6zr5ww+5AO+whr8M609V3xsER5Z1rKxrjoxcTBa20aWh4Ny7WyVuKZm6NauZ2CvS/9JhOjYM/tpoOoL+lz3R99ES1UPbmQNH5Z1J//folUfajRzFtlbTbaKtG19diDXwH6FrAlAdoPJ69S6B7bW6+S9HI+1z0P/T5uyPaO9iZRGsOmX/iPYYe5ZiINqEx/cB7mU4eRXXqUTb2WWXfiOjdoXBGMbQH7xM0XTPQPqhog/pFfCX68SOaZr4StI2PMa2le4k+FGvIxy2aytMzsObnJwwdbxmC9tVPahr3LgHEdyc+pWmjnukBlPnRT4MmVgqxFnwGdL3ixOtR/nNMG6rAJEZErz/QmktzSeQQ+QvjVPYQ9TuqgDl25/OKTqWzk2H8+4e+oH9XS7nAz13TvyuREL9/9Iv6dxYFsaf4kvpdrQ41OhiQS/KlDu9X4LvK8RHldDHLFTTLLugvAz3irAGgvxp0pkC+kS/vJJUv7sILmfTrMtmFhdB92ayaBspczFtdY4sTeRufK3jl5ufml5eKC8UFlRO9PYgO4wMrs2fEDw8GzZu7BMlnvjC3UFg6XcyfOT0XJc3cGjU2zLc6LQWs4VvIw2nVZWnuTKGg7MClOeU4Rs5l8o0MrovqInUUUVY4YRu8Jflkl+dKmdz8meX8whx6YzaqA3JDqKvX3hCZWAvDDfmmXor2U1aO59edLrxuoVCy+ptHckyHi/xWd/j8N+CXA+TvP43yYa03B93GhdYQ++t7KeNn5skUMOceGcYMBObyoyTGlj34Vp6gtmpfPJWdQHlrVnIVFaIQ5yi58QjGFJZKy2VyrMtVMuVCic5MtMtcJZ+0pWzMb1LwoyAIyQ/2ltTJGFNdrCglR6oBumPT4O48x8Y1Ntvk9RPjjhm7zLOAU+WZ6bsFe8PDFt3s86zJDD9Sm5cJfkbdrzzHptPVkcxJBNxVHycDB9C32w6Opcg4RKurGzFWJadug43RUGlLFSMEzAkLI3b69Fa1sck97GMG/Z4ZB37fWuHg/+njZdk9xP36ZdPfQPVfrc3nRD4poD0PZHtsPDC3nu1hTFw++vBmALM1WI83OCK+b84vU1WsQ4fuqO9VTIKRZZ+vOpmg3Ft+v/AJvQdW5O9t7HYBrPaMjueFXTf0Xb9F0tOM23DFq9emqn68mRTlnrN5KttDa707bKvqwd/YxphlsX3E+NSctOjsNIv+tMecFZGZqJl0pG0w3k692wMtcuSjC10DfsCoxEnEqMOP30if7LzLr8NYlDfl0NVJT5tg4zwMJ3yMee1CCC94Ttg8oxgJxOlpns/xMNAjeCfDxWCe6igGcTdz/2EXy/OVo2D0XqFjyr76rDCW9Egf/uMJmKLA3Pbqx1aJ+iZZNSD/IcxGnfIAAYo2nJP9bGMb7R49nkJYrElu/YRegB+OPw5amKhHojh3zKveWGzsD1zycXpuqRb1hz01u6L1cw/mdaAP+pE8NBHD72NIDlt9a+EQ9wH3nxXGm4MRpRnBHDgZqPNaMx7HDY+XTsJAY42crwFMg4MTOCS2zsYqqh/yNYzBc6ZQZ6yuy/bbeD34qYHB5n3eQp1wuOEA+sTnC2GCP6M/d6xuN7xOuuUK/Yy7L7+8UzX4UqJolJ338dM0kGbSNgzu9okEXG3QICtKY8bM7Wf7OKH1a9DszTif4GyoDs16h6bI5qAe6925RFzdXK+mECMfqkd9s9fBbIl19IS9dpicWT3E9Nu8SN5Ubyq7DClgpYmjA/AQe0JnPJuU0IY=
*/