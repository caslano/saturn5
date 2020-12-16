/*!
@file
Forward declares `boost::hana::comparing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COMPARING_HPP
#define BOOST_HANA_FWD_COMPARING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a function performing `equal` after applying a transformation
    //! to both arguments.
    //! @ingroup group-Comparable
    //!
    //! `comparing` creates an equivalence relation based on the result of
    //! applying a function to some objects, which is especially useful in
    //! conjunction with algorithms that accept a custom predicate that must
    //! represent an equivalence relation.
    //!
    //! Specifically, `comparing` is such that
    //! @code
    //!     comparing(f) == equal ^on^ f
    //! @endcode
    //! or, equivalently,
    //! @code
    //!     comparing(f)(x, y) == equal(f(x), f(y))
    //! @endcode
    //!
    //! @note
    //! This is not a tag-dispatched method (hence it can't be customized),
    //! but just a convenience function provided with the `Comparable` concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and a Comparable `B`, the signature is
    //! @f$ \mathtt{comparing} : (A \to B) \to (A \times A \to Bool) @f$.
    //!
    //!
    //! Example
    //! -------
    //! @include example/comparing.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto comparing = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y) {
            return equal(f(forwarded(x)), f(forwarded(y)));
        };
    };
#else
    struct comparing_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr comparing_t comparing{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COMPARING_HPP

/* comparing.hpp
8f0DvkvxXYevwWK0xH1M9Me87fv/tK4C9Yp/l/Ymvj+2MfF93LuJ739/O/5dx9dyuZQQr3dbqc0R6Bk9161kPiQ0MaU2r9y+/APqk/th8y+NpV7Ov1Y49ytWDT+iFYG+0ngtxqMMbezo3s0cLHUiGZNNtstNOebAXNlr9ciLrMFWy8K+81bLpoLkgAP+cIObLAha9FHw0Jf+YfWmkcmB04OHvvIPrS8xjiw1Bk4MHurwZ9aXmEaWmgJp5I3OXl9iHllq9qfw0VhyHkEnrehcZc5YS0V3NUTUP3RKQGgTSi0MamiCheguVNr3Pqat92YI+pZfZqNuQpcNWYYltMcE2zEPWAj5e2zLTP7RDazO8UjDtf70OZQf7dE1J2AtztNjiqVrxRQculVnLeg4HY6HWhDhUbz38TAKzcjr9x6vZkTXf309Hoz4U9d4cDKFEx50t/38ri0B8foKNUlCp1z0ptb7g7rqkv5bOvQrXLg3uoAidtcgVJMnQfApXDKTVCHBn8XH5TTy6SPOq0oOLrMaAqVwZw1XWlI/rVpIfGZvZrF9aAL19hDphDiInlX5P06RHppvJb4fDpBD50Hzmu4po8MjLSf3NuBAHBq0yZJsQDQjT3cRNX68pNPjx+a25/RTUaFS9frNWc1fOx4Wij6yv9/aTYsR9fiWrnv8nhatx6mcULFFbjoG+MJ4seokMljMZOWWsTrfEOhdvQTrX08cGQwZteWu+fvIr8q/wZcTlvEh5iy5h8dLgrwP2Xh2RDgQld+VW4bQYhP8YDBxgujD4mB0cOB84tE20sJmdO3CLQfZq+FjrDi4d1nTvpSeO3AhpfB9Qs7Qogb7qls4ZU3jkjdQbHHwA052GMkipto2csbqr6SVk2Rx7MmYj23lhqzM9DIvq5DURZyKmSLWc38SfKb4x9EA0z3myJuJs9ot5o0jjFWDfNN5gCSq2LeQ7N/Elnf5izSNKU/PT1EJCe5I/DtXDOfVnHT3Rk7aQCkrvsUNyl//IUU1WV7D8dJSC1mwsjK4fXBlr3ns76upPaUYBkPtRBdNcMHZZI6kF+PW1ape8obaXVXWpnYrx5O36GU5Gwo2X/Ns2NL76KAKFJlHbIZADlMiXSBen/qf5YxkNoHX12XXwTdP2iUQYF8WBvbQYDiuf29w6ta6XqWR4uqtg3FFbP9SeScYf3hnTymCRXx7uawAMU8OL4lOrN9ZvW9ZXXpeQYs/GRameGo6lAKo/4biM8yfzwxGTYHUTcnVpRUhF4gCnSRGE5f1QJkixLWFW5s6b7XW3vom2K4ml8pNqLLn+XXpZzcdtuLM0+fmA8jxLTyrf9v5RP2WTrPIBmG5XI7NnvGa5Ao2yageWU296wlkuqItBiqkhGTPs0LlhlA+FQqaB4qYX28qsa85EPzbMkyoYSDDkJIWNFUOIzOaeavJh35yCaZM4PNgh+WqQQh91r7GVNL0gbVnOwV/EjHJHcujhA6L75xVcbzGIISPHsGPnEdjYMUY0DE8tFfeygh3yFqEjm6v31y9pRrDL29Gd/WcSGN6GD2HEfiY0x9jPR0ORuuIVfTTNUKYhdoNievoGyLmyGLFaSZxAJaetctSyMCoK3WtmtpGv4k5pnaZg+j4KDqz5k8ZlcrbcL7pP9g+6CqyVVkA6Job8mrpjH6Xn4Zc1v9uw+YOzqyr4+7JZT/Acc7hqk6QsmvQD6Qr86xmpoUU9rlEEYbRQTuyhBiHzb3DG7aR6+phkGhevzQFdAwl68cHs+hPpmrKtGNX3Fb/bkoKv3DyRlrucz4fClFFjtEMuYdbmoGavSFyDZ/1Evc0lT0khYQVJ5OFpCDI06Q5lE75Es1BoZG+FHiJVM0=
*/