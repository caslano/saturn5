/*!
@file
Forward declares `boost::hana::less`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_HPP
#define BOOST_HANA_FWD_LESS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_impl : less_impl<T, U, when<true>> { };

    struct less_t : detail::nested_than<less_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_t less{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_HPP

/* less.hpp
4XvsiTaen5+RXPOIJgiuty+UuURIPtvWcpdGzp2HuT0La1x0ZEQ69rZp+cXgfxmS3+a+HGKusv/baEurEpmkacNGrSNMaMPSRgr3528LX5fWI3feyoH26sRxDWelqA6n7uvapfuntPWy8WRkjk8MT7Cc4Znxyhvu9J50N8089Qs74xV9OCIXBpt9xgMBuvDOnZBNUYCvn0yVBTQh4CLobw6vuTyqXHodF2bR/cIp4cPrvCkz+55FjS7JrpTSv+9rnZNz8INJznXmvdIDWO1ckzr+BM0EzW/sip+JYy6u7p17mMOqI5fER0DbTVGwukDsez+m/EH38CEzpEi/MInws7VhKLp04ETPvvTg4F8tbkM/q/JWXeK+OvFPtFH4a/THgxx1ZJDbZkHce8qPUaOEntSd6ypC8puMP3a1Wtua6o3EOXNsRB6K9MEzF2FEQeNkcFwE6Xs35PXNcMkN0Kds/ss/H+ESM13d70UCSWPe0ZR+h/Q4Kxf8pPtgrECU+Y9xAyfqCDoqtI/8n3ueig21K8sWz0pP/iUC5ISjNtX1v/a1zIHac84Lnh3rg9qC8ruWNx0u/hCft0Drn7eA9Gq/AItZ2xNe5z7nwPSvO84FhtnerlBgvLD2OjT8wjpTeQ+Ke8FUM7KGUi1xUsSFXdwTTlJvW5m8EH4msoJ5SuSLMiIcloAac/YHXhQjj5YWH6J8OWxh/y9rDxH+9jZD
*/