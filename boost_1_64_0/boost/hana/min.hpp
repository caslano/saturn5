/*!
@file
Defines `boost::hana::min`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MIN_HPP
#define BOOST_HANA_MIN_HPP

#include <boost/hana/fwd/min.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) min_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Min = BOOST_HANA_DISPATCH_IF(decltype(min_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::min(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::min(x, y) requires 'y' to be Orderable");
    #endif

        return Min::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct min_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            decltype(auto) cond = hana::less(x, y);
            return hana::if_(static_cast<decltype(cond)&&>(cond),
                static_cast<X&&>(x),
                static_cast<Y&&>(y)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MIN_HPP

/* min.hpp
TrBkO8nGa9jrqG8ilIbeufrQzcfqizoX9E07phSTTfOE1neQ0G/NvBxr+r0MuW7Ww88V/Jw4C4LEi3EiurEyYa4tZ4w4Sz/DC2zwugJumQAZTguwDU5cbfawYQsBO2nmkPIMuCp1YunhgJIzz1e+UBi5QvBOd1rBY7C6AVnGIw2AH32f4RzHfSgKkWdB7BK2NlYOHNpfg95BteO9HzDaW3phXsIDvrU8afrsLvB2HI6iJMgRdgB34AASvrQ88m7DRQ4/HWRVisz9NXh3pXtwBP6S0U9sgCLMqsTCwtRHo7cooLWB31Vy/H4awseJ6Fxkf1ykBpnwew34KParKK3wZgo2t308zjTSnrsY8CWel8wRsoH2YCqPwz9twHt2hSxm4KPEPzExOYI/Kjk/ERUbOLjODb5PmPzUsb6t9ucl7jwT+qlD5tvbj+CwJcyTIocWdoEcnuiDEzMHDjAizFbrGzTioIDjLU9qIgenVR+a94DPcfgCQYklnvvHscYSXtY9uTZYZURsReO8QaOwgwAvIYQ1jakJNcwN/KsN+BxqBd71yFqGe75Bz+CvMPlUeAh4dXKJ/1EHDh3U+FUfPszh4TKA4xOpY6xFCOoRPOg1lsYXDBph4odwpCQ1jYmDozQumDTSOHQ8RKgSEQjfGD79zqQR4LUHZJ8gGtMjNCAgBo0oLfCgaujXNCAh42jsrjiNDG5sPHMV1jQm9x8hGo3tuq9q+RAykXwlR24TWIHr62uLbZbhCFzPD4NW7kAdBFVZ05o6rMa9sbGjFi0vLpGlIEgYLXBuPK1HGLQiPFSE1Db1ZFmCDIzQ6rdo4dQC+r2IGS1wcDytZxi0kKwIIU5hXNNisjCl9O2LOPzBtLBxEog4k+7p1hnJS028se35aZwQXj3+jW3/CEPnl1EMSYb6XF1Ey9tn/G8yxx2ZEtGEqMaNcR/B3TdwV3YOnz7sJCDHG+sSusH9XnOcETMWRHFV4+bjrOA/XRn7Qz9MPRvPiCAObmu93+utUwXdlq9w+ENZiafac+A/MTE1dYBa3sw7c054OKWBi9Jmk3tNbUBnVJ3fmXWSyEda2jJnc3W0TueBRh0/qLwkgsCpucfrqH5ch9eZipE6qkornOQ2r6l1Th1T+OfMWIMMaT7SLP9v8uKt9VdxvqGy4hFiHe/N8UKBwVcK/yVaAZ+gfhFBrHfYfilchGJNy90jeOyS4zlQ51GKhV5eb2v5Szk9z0GSA4RAOhFiINc2QJDqoPVg2OZgiFOBemvZ3USB1dyPGXI8EwEGKMQRg7VBjVvROepafAsKJBkuMYtwjrSyvQySsKIQYol/bIFYHWHRq/fh7Zi0lxo0HUQl4tn9zNqgOyDdQq1XHM73kMCsSipEJ1g+3WvAUMXD9YHcncByQxtEnmokCxBX1+pEAfzu0MU5Yz7B7Eow+tbGGg75YaHrcyvF40scHgsfrFUbZ3nIBbiBV9ApFRpq41hc1Fc3ZgbtebZ3ntsnvosnAnNIRnd9sY8zzVbMP4f1PAtJ0HL8l1k5TtGxcaCcUxhUyeh1+p0GudF5JziezMIDZ7C0sRFcHJzdXF54ZG9pYNJd5fAi5zV0doAshJrXsmLNUxXGiVNIMKGP8J7GXl55IrfvA6yBSIDl1TY28fesgj3PaR6KXTfDSgbbeg3PyRBbzmodPm/sL70YZn5BoDBqR3ThpQ/wuRRXdoCwqBhzCaOFtWcE/iLguR53nazAPJDwZGQbuVXexPU4QijgeoJqi7U+ZFS6qs6nzTpgr1Ph0pXWh+PqXDTrxK5fFVi7tT4cV+dN4BWrkyPoBEe1DmsbdGirznvNOiHS2kTIo8TaNlrn02YdBJZ6AcRVt40=
*/