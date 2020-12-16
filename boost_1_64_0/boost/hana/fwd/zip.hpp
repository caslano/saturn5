/*!
@file
Forward declares `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZIP_HPP
#define BOOST_HANA_FWD_ZIP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Zip one sequence or more.
    //! @ingroup group-Sequence
    //!
    //! Given `n` sequences `s1, ..., sn`, `zip` produces a sequence whose
    //! `i`-th element is a tuple of `(s1[i], ..., sn[i])`, where `sk[i]`
    //! denotes the `i`-th element of the `k`-th sequence. In other words,
    //! `zip` produces a sequence of the form
    //! @code
    //!     [
    //!         make_tuple(s1[0], ..., sn[0]),
    //!         make_tuple(s1[1], ..., sn[1]),
    //!         ...
    //!         make_tuple(s1[M], ..., sn[M])
    //!     ]
    //! @endcode
    //! where `M` is the length of the sequences, which are all assumed to
    //! have the same length. Assuming the sequences to all have the same size
    //! allows the library to perform some optimizations. To zip sequences
    //! that may have different lengths, `zip_shortest` should be used
    //! instead. Also note that it is an error to provide no sequence at all,
    //! i.e. `zip` expects at least one sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zip.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto zip = [](auto&& x1, ..., auto&& xn) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct zip_impl : zip_impl<S, when<true>> { };

    struct zip_t {
        template <typename Xs, typename ...Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ...ys) const;
    };

    constexpr zip_t zip{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZIP_HPP

/* zip.hpp
885XeW9UecE/WMOiq7TTQZwX7PPFx1FJi15XEjIqI5KeAKqMcLoMWhEafRll2GL9tNo0gqssh3/VctCsSYc/za/2c2906mg/t4riG7LSi1/697s/9M0yykuq8trHi+r954d8Q+Y/SeVvHy967D//TimcM//EWZ0zlZHBH2fFV7SJl8/PqVQ+PIdAK5jSqOqLtDSEHgzhMO0cczzi2i8lq/grCJclC27cPPBjaGbQoeYvn5Uncg4wHQVazMy6SGWdks46WWWdhryGgC/mgjz1SaaijuRAI+FgKYAMEP8/wQLihAz/JCIYP9o1s4T210QSR2Edo7U6rKQkOfrxaHqB2PepwdIdppVlSF2ukk1Z/kWLtDtDUhLqxuUVrho8B+QxpPDYTVWZuTwqV0TmQi2OkcfH1obFPf2VlAyXiBFsSx6PvQzc2igz93iVu4/M/bUK7vz7uvOgYzrJ86AaNT18WO3hJ0k84UHPXMk3ezCYAe2mjKl8tYRG38PQ8F6WUMoTjuBMIle/mFQ//GL1J/IMArzVbfY0R+wl5uFn4GkOpXsGG9HHZFY1sl5upytdiUUuC3Gs6fqa3mWuNAlO5XwW+T7NIt98lC/VT/bKPoTw9pfvmQewjyMRsQx9t6AG1PSrt40aPMwQrs0on22mjXeRoaGg+AMKgylYnMs07iThOxRhxfqthtAcE+KFdMbmk8HP6LgdRWYCkPtkNrLhgKsscYrPhs6wJy/GEcD4TcxkBBDHLwxa2VIMek173CzsYtWrx7VyryJzp5EXW+gq0qXypIiHqUYcalW73v+Y8ACQZNGXvzokfVH0lPU/bGT/kRWQAvCzOZcCpXi0bHqemwT610mTyoV8FQzukQPcS35O31rsGi+EIyTq/0I8H2kVdYNfPEDeLTR76cg/Ip7ZQ2vXIsZFJ7HakBrwHiDeXzwhjcpg3I7WEhlSqo1wi8Oe5o5mbNAzIh9k1vFeokL1uabBKHkof60MRU0Usdxlo6PlNXvs2LqwyinmTq9GBLH2D+4rqGKDwtFJKWBQjV20GxDVVGbl116KLOpgr5Chucma3p8OhltHJh01IAF4erOWANcySbtLJa8Wv3WoWnxcy91Uy1apF/BCqkUdH3It92XUsto40KRzflLPwDcA8XDvv5jTKYEUHBpDLMQ9X75lRMVmJxb5LbGJZLAA15Va/kZiOifLzsgIRPNM3Ghk3RF8qly4ZxZIzffTXcg6pDSU2bWnTVi6NY+gyDs6SRWFCqdxQpXPjT1CezgjpUu7KEOueYOcP5/Lk1pto4pi7aqfNmHh2ZQRVCB+iKCQOBF9XyNG439+zmhdYAbrp/sbmLDD8R+ZYd/tz7B/i/GX98/8PClZEZDm4Jk2No8UoCk2le2exy1iH2SVuGApKltJZPqj3TTJ+uJ/nEWKnCbuYqzGjEg2cxCcTZ/Dfck+nn6ayHlTTlWkcaYHqgnDoI4/IUhGPWoWdsuYhSs5EYwMNUisncCbtiCl6JVGgaalXJ8U2UQpnFmv13oaEsxk3MGb+8EZ1Z/KZKPza2hXMkd8/KW5o0S6ozMgOFKeswrJjVRIOUJRRls7U91fsUQnxK/vRcSvXjcFHF9Qn1++jmcDZx2XAcOLxmzCuTG3j1LM18ZnNGylhQq/lwr/GXNm6r98VLPFpmxbsYF2yS++S+fV6wnWyU6iEtrkdIWYhQAQC89kNq6GJ8yly4c3zPkiMEtZR4DRpmi6uFMnd4A8P2QLXtemZRTo1k6XPmUb50Y5/ebJuxU1ounLdoXVQe79r7A3/K/+KX7bRX9iNPpZNSKT31bx/nbx4aiFYzY3Z26wlplr/wXaatl5I3eaO52IKhQnqc96TE0=
*/