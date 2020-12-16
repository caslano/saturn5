/*!
@file
Forward declares `boost::hana::cycle`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CYCLE_HPP
#define BOOST_HANA_FWD_CYCLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Combine a monadic structure with itself `n` times.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a non-negative number `n`,
    //! `cycle` returns a new monadic structure which is the result of
    //! combining `xs` with itself `n` times using the `concat` operation.
    //! In other words,
    //! @code
    //!     cycle(xs, n) == concat(xs, concat(xs, ... concat(xs, xs)))
    //!                                       // ^^^^^ n times total
    //! @endcode
    //!
    //! Also note that since `concat` is required to be associative, we
    //! could also have written
    //! @code
    //!     cycle(xs, n) == concat(concat(... concat(xs, xs), xs), xs)
    //!                               // ^^^^^ n times total
    //! @endcode
    //!
    //! If `n` is zero, then the identity of `concat`, `empty`, is returned.
    //! In the case of sequences, this boils down to returning a sequence
    //! containing `n` copies of itself; for other models it might differ.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an `IntegralConstant` `C` and a `MonadPlus` `M`, the signature is
    //! @f$ \mathrm{cycle} : M(T) \times C \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure to combine with itself a certain number of times.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of times to
    //! combine the monadic structure with itself. If `n` is zero, `cycle`
    //! returns `empty`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/cycle.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto cycle = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct cycle_impl : cycle_impl<M, when<true>> { };

    struct cycle_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr cycle_t cycle{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CYCLE_HPP

/* cycle.hpp
J/TCrrhg7wmqS6c/bvXyAKmo4LuMy/Mojy3i4rrnHU+VT2r+vbwepc2ny/95XkgrNNIZvQoTl+y96rQQr1KCdzousecS8WtlmLKP6fWr03wtubjTfD1llpivmr6Z5i8ZTkAd8Ru8s2TtDsJexui+IBoO2eYMpeIhnVbEUOrRFMyivIpYeb/Tyrv4W5RnDwl9uLi/I53aoBb/a634AzXMPjR3mX973dHy/1bL//hR8mdjIOIChWxbnjAsfBUY1GVWcWyS6JtbnpAXnp9nnpAvVMAvTVIvL7x8im5NUeUdOkhORhfkGCvy3fJ4g576Di31qFjqZbuYOpDLJZh92MMTCt2eciYhO9GRRK9CKS0T8gl3yZCyewjRZf88toLHK/7WjDuD8cOVrg1XxtcPF+O7TZ18HuXmerZjSaf5V0z4Z4JI/+eCvLYUYwrSj5iCCKJ+PMr4r9Dte8hoisavE7gfX9vl8BH/ZmOY0IM54VI4ai0dhm8eG/9wPwKqPj47sXjKD5cxwaapGqwaZqCq7BdTtcnd9qYr+LmK61R+Lkue6SDjMCPyB68mU9yDRGm8vjHSNiJPGYoiE9VSmi8l7WAN9vA0tO3E1ZEikri6P+BXOLuYdT7Dp0kKVxKhMGw14ijqFqPqJESa/SLeZ2+l9/Jfcq8V6Re4kM3uuBZsraiv3ZqwQB7r8KWS4SkKrSpABmco2RO60sI9Xcp6C58BrB4e8iQSA3hDpTalernmFdehMUJe5UUyN5yDptHgk3wKsbF7132FiNFMfHcIPnnXUnWP8F0a8cZ9aNYz3fPIebBtAcacq9w9D1D6GRa3cpBZPkKpdIGfPMFDpenc/BTBvFrcyHYFssHemRhb8ieexKs6YWWOvWJWyNqt6614fqTr/h7Pla5HJoYkujhdKfuZ7kmvpTSdZ4eBPtSIeM+lzcfCv3cxeammLN0fqw2VgcGWJ4LNJgQiv5s0jdAgMsVh+yK0Uy52eHw9NSvkjVqP/RwMPbvZVzttw3Vap9GtFLdTl2WKLnNylznVLhuBfPJk7rIdcg90mrVCQEOKPWDUZLhvyLFSk81b1R78llhAoKRDtz7VI5+X2Llt2KgSLlPPUvitWqTex9niKXqesvVybl9Lit7lsyrgoeuY2lHV3yPN/HSPbPZq259y2jD2+ikA6Ckf8JAnPsVWz7OD/ABZw0uubL0ZlYA9CKnHUC2B1PV0cLH1Wg5/Rws3B+bTLM6kAif61ZsyPHK70sjloekQJP5MMqzEPLuPWrhdzDPfYo5Wb6+D/cANwgb4gukUThaO7zPCm9Ur0kyhPKhKyRyUTZFENcp0VFJeJhzbOKZwH1V8a5PRuI9u/yiIi0N1kGcghMWgFsrnAdBz6SI882XcIS2lDpYgsLmRR3lkruaMdKRvqOgEspBngZlSNUu9TmOnbyDF0e2gN4veuSigSyoubcbMYFVY0Wz0g6MsjPVrioemBBmsjUFscInT4J9cRifVaRiaFsasJd1lbC1XJivKgUsFLPv9BR7l/HoGV/6c9iPMiRhro+jk82jTsgmVgjYySGkaSGuFQAupLCPO8/fwKMmiCN5NdOOiqm/4afWv6OT/t05/j/E/gCqZxgLyn+yZaq8ORK8OE716iyr/WaT3quqBOm2ONj69fE41tYrhI8WAYj74pwbb/f6zRxH6+3v5xlI6MY6RH9Iwh0vT6cetnEtdxKNymW9U5LyEuPTLtbgLfcMjJ2l8AobrwHx1P0D0/kxfrgAjTQO6eFGnfr++jgFjai/GrOKYUp3uf4S9hKstuD0azHcEZo9YYPFPd0urAZPS5zL9vLx/giwU/xa5V8hKRppPaxsJmrYFLfaLW4Tl0AA=
*/