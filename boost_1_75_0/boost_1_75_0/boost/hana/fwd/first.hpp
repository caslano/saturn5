/*!
@file
Forward declares `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIRST_HPP
#define BOOST_HANA_FWD_FIRST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::first` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the first element, where
    //! the type of reference must match that of the pair passed to `first`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //!
    //! Example
    //! -------
    //! @include example/first.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto first = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct first_impl : first_impl<P, when<true>> { };

    struct first_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr first_t first{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIRST_HPP

/* first.hpp
obD0bnqr5TiknU9Sy7DBtP/Z3kx1CU3GRr/CDtkunm/sc9fV3PkOvQzbqic1UI8aGvjqtmviURjeyo0tXf5yvrtpu9GvFtfepLsRREgJ67mK7RI30rpBp6h4PTdHUvqmH0kRIXERkkUMCR254R2z0X8oh3c4y9JxAl5LK/gm89tPuY340gnfFsIXxfDR6RNeSSs96Uf/aG9s7Hkv9TxOPc99ck08CsC7982WPXM4D9ff8Pe88AatwlHoWfRJs9/Y3uA6D1C76dRuzSctnM6/qLKeKvMakbDDsrwva3y+fJtMSW/SdPXpBCW9c9w7RabYE8wKy3YciCfnp/T5doSNQO6bVOQWUO4rbC92TDfSrQ4wsiOBcr43fH4a06ushKuejhLdUfQQKicdQrNNDyP3DuXWU64Q4+/oMRm5E1QWTjnVIUJCP4089ZdUcVfw8z3onY7KNiCnlT+qa0ev69lkiq10o9ooUUQH1MfhmnC0Rz69rYxOfRai2zbHRTjopIG2gBDxOlRsEyLip7IG0EB0+fvde15KbywKeqSE146Ufug4HCmdFjcKabDYlvBPCLj24/HTTgyr7c1pX2PntFPfyBBOe0MrtBPQuDIxXyG2oetgsayobXPa/X1/EGn/Fam/3N+O0uv1vLzNZc5rp8u8fffLfG5ojKSQ28/NLuD6M13C2gWJ9FL9upDmdJXW83H2I/WX+8fZhbZUtymk
*/