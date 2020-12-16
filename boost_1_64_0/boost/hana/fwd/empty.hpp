/*!
@file
Forward declares `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EMPTY_HPP
#define BOOST_HANA_FWD_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the monadic combination `concat`.
    //! @ingroup group-MonadPlus
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{empty}_M : \emptyset \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the monadic structure to return. This must be
    //! a model of the MonadPlus concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto empty = []() {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct empty_impl : empty_impl<M, when<true>> { };

    template <typename M>
    struct empty_t {
        constexpr auto operator()() const;
    };

    template <typename M>
    constexpr empty_t<M> empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EMPTY_HPP

/* empty.hpp
li5dZv1QxIK13ibIejH7iMG9vyo0YHWG2hmBa0g+S+ccJTjfDOOZyiOG47fUiqHaqE2Rcrg5fx+qneZeSOCyyyscQmgg99FU6nKSsLBKyuPc93NuW7wjNr5TaHIMm2ByPDje5PgikLMQv/bxFPbvx2d8Vh/eb0CoLehJluDG5SsdPhLx8aUmetC+sMRq1uas6hX1cpJtnCWX03ieSWnomnsVjXe+l+cakiHR2qI0RPC166AdR4kvyFda1r0eA0pFz8ZjqNMYzGZTdIUdBmvAVa386iTv2aLnUeJQ54ngQXk0RFSUggqRh3QYcChZrdSJdCR+oks+w6QWjLZXqX+Z0TtpSgFUuOnEgvqVl3Xcn0yT/wjbCqiKh55FzPfj5lDnUPt37mWr7w0tk5hzuhU/jLWs1JbBTkJLslDmfbybs7ZDIZUOSSxm8dogXkePE9YWVuN51HjxfBVblEOf7hBpowvpyKIKKc7lAJt8DGvEHJ6vKP8lHTpiuymp31AVc+HGjVd5F7jt2imowpwPkIvOQGF1yIHCjh5CRiqMpwSJvKYjP3oiWy358njJoxGjT57LaZ93Ntr7hwtwFopvPzyfwO9f8T2C73y8G4QHUHOGBQ+mDPoYDPzz7+MTtOeP4N8hEw8MaNjZvAmY8+AG/MMJczStuRZPbjbNNPnFTu5eKyOT3PoR7BHmjypfDJ3MqsvZ6M+SVjGNDzK9xeFsVnDWmCNFR6573avGLBAxRduD4+k47VF2YPUQ/ZcNdxCvYC+DpubmErCLJCgJkoNpBy6o01Gk5ty6vxd2b17gcaTjMojdCz0IdkrLmfY9lK0uYtcNWcBZQP+11NeliyBYrF/FiZ/8C8ODBoPqb2olWzWf5GRTfFgbx8GEBBuOS17v1M3kmQG+lyKVffuoe2Gu53tIxpyaF1isVPPMzmK78qfS33UWc3A4uePan+GWNnNTIoO0dudQG7W17yv7tLarTvv6w+sM8UxZUBN3Q9XV6lOuAqiq17uaU3HMo9HTeXz/JyvR/oebSOtCvgokwStjtBPWGt9B8Q0tj9IK5zf6cPG4iU5S3bhNgunKB6le6Wa0waPEmGnP1ygZu66Zv3gB2f/gbfO8U4JLh8/B978HCnqfzz49vB3mtT75UgPR1cAZcrnYuThkt5Mvc1m1e+GsJ+zcXALetQO8a5DPdptqQfL3xA8C8/kgsJAOAvP5+LUWuItjuSKhvZkHrFzQgWIsgSmxoG2z6QFp3UBH83z8o9sg8SW/hAfQxI13YqTO0RZuR8SrpZoozeNULw/UDopflIWt06Ee5aEzNbHhkoaOOs0u0LLntUlyN/T5Lx2iCRKdaDaVyNeeSGuUbosAG4TeKOwJaYqj9vprSKGrQlkgyoeU8VZg82i67UVwYWaa3NIVDFfZQE2ftX8cekpIXHiHAYwa5/Co/M0gkZwIsT0WJ8Sci+ScgIuFWXxaVeKjf8pbQreTFtnP7E7bx/m0lw1JkX8OTnrH/mzHj9T9YAAscvf7wXwR9gn2h/6hXL6/QLklW/VFgyt2Q/3DRfA06RXV/2GatgOkEsLT8rqj6kn7OQFT8+wbk+zxtb9/IEn+23zipqR4v1m5V6FmqiC2b0tJf+zHyemHK99KTN+8L6W++pT8+1Pq66uUJuV3JMVjfFLy355Sv1MxJcGblZJ+WUr6ocreNxPT/3V/cnp3Svps5edJ6f+Qkn5bSntMytWJ6aWsG1V7iXfYurWXSPEiLJ5e+cLInuwlNhcmp28uSOmvrBT4NqfAZ1H2vpHU/leT0ztT2j9Q+XlieqlebQ+Ecd22pz4ZPk6vfO/sHtuzMBm+ZimlfRtS2jcxBd6JKfBmKX97PRE=
*/