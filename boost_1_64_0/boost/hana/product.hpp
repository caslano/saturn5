/*!
@file
Defines `boost::hana::product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PRODUCT_HPP
#define BOOST_HANA_PRODUCT_HPP

#include <boost/hana/fwd/product.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/integral_constant.hpp> // required by fwd decl
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename R>
    template <typename Xs>
    constexpr decltype(auto) product_t<R>::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Product = BOOST_HANA_DISPATCH_IF(product_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<R>::value,
        "hana::product<R> requires 'R' to be a Ring");

        static_assert(hana::Foldable<S>::value,
        "hana::product<R>(xs) requires 'xs' to be Foldable");
    #endif

        return Product::template apply<R>(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename T, bool condition>
    struct product_impl<T, when<condition>> : default_ {
        template <typename R, typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::one<R>(), hana::mult);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PRODUCT_HPP

/* product.hpp
2KGySlTkJDmzCfrsbN6You9q141s0l2zp7qD+8f9IaHrRNXIBkJmkMDCJKOfizYCt41H4fYZvydRGZrQtBb/ksyTXunMRZkL/sHh+A59RmE+TpWtSyxGlD2XSqfy9IV5+eMQWmWXt563l+vOBAIZ2/LZk/y7YdvJyrwrRWI39MB4dnLeshIaEqDCuLgHizgqPDITUmQcBxnw9TbcvszvD8e3k3tVldShRVEUXYX1vnCv2sdXd2fOg3Z3H7a1Ob4asDg3e+CTxChBS4vKihEQEZPy9PZ2/DJ9POM4TY4zzhjMrxry3QE0MXOsCvbV8/FSHy5Dit7zE36VqCCgFgMOo9jmGAI5hQ+9/g3jGuH055RmwE0Ma8o2s3PgnbzcuabXKusgHfQWXsyxMNn28bInjMP4yzus09v5D7Ugt2/Smymna0WnVWfzIgPhyml/OOeeNsU/5TS3q7KskEMXm8V89snOFuX5uQwNWdaoUni1AA517kFLsVH+mt6fC2OtqUYrd7o2k210UNtAZjz9wId6dCzB7Wf/ms6ZTJtKt9IFtIOgGt71wrsUyYR/neltKlXKThWig7rHN8DpcAnCLbF3HBJaJeqm1y3BmxxpZ0Lz+xSnbUWB/antjSRaCLCLtqtp/0xeOawvNdV3aopFS3qFpI1G5HXWNl1fLADNhefK42fcIFFfb1PHtZDwaUUP+bfCgiQ+vsWQLZz08igexYzmSUY6pYRXL7C0VY5NmniFnpyd28Tr2/N2tWXRY888es1D+0eSJRb8Oen9cOlvM5tMo9tG1TnpYB7kT/QQugbsZuv4ypz+tto5tmUQCygYJIrsxb3h2rzsOZ3Cn8wo3MfCmUkxjVGOy9RVVvVDKw2NFaEJ3B6CM+1ETtjeRUPxrrbpAzCSLDbrY1dLXaq8FCNY3alNWKY4RS4xms35vYReCll2QykhSHvDovigfBu+Q2R5nIsJbeW+VSd1ZwKtEyPjm8LCRkZ+MQkPI4a2zg3UQEn9pO1dkEnXCTNm1pbWtKUzbA02AFF/yVdwGuN53pcOClatjPDqT8dgNftn9D+Y0SvTDA5tc6LXOqVP59rS3xOZGEqjunGz4rb+H19WR3nowrwsCvUQvZrcDiwwNF0e+f9SSSn8b/0QE2TEQ4zf9Rjnj6mUN4XsW5sTbjXF9Vv4ItcnW8GEh9PHWlUUuhLcIY1Tz20FE3oltJSFLhx29hw7ZVEvcIbTgkJCO9JXTjA9OBXif81rpvX0tKTeQhRN3UO10Yv+KNwWIs/uEedzQt+LphnarqoIo9g93FOUzdAMOZNjJbtz9XGPTfg2wiFm5UNt/w2+nOFdye414VcLrBat68pEfuND1nhi7+4cQookHvSNl5ZSrI1StXVbuXspRWklBH36SNzuldO3AkqULjdthaXvJ1eUTA/mOu3rc7rbVEVmIPqEHZRj2ce1dWNe/hw1NHXW6UJw0DWad8d42U7Ith7avCalTNDGoJKj8NU57e3zDtfAocqgjdzdedTDd0/HfiiSN3h5rN5WZ0PdO/tdZrs1G4Vz4/pIx65ph9zhykVaJten+MR7oEt8DXJVORA3ELLoukf1cpKDT96O71VG4jLaZa14VDSEi+Xuy8ud0+Du01bNAPExMCSsHt6m47in10rnnZgvUo+B8derY5zv6fzEydbER49dCtgTt7ws3gA89sQo1K+N1ktL1434GTwPcxyGZdvOwBxZnv/fwP8JJ30ZemZ24kHkfx6HX3Evl39wQF4EB2PeeZH3BJ83vVEfBLrzIe8B93F55DpDbT6/y7sv8pxv8uYZInR5F0DeL+7n8rzITAF8nE/8RZDn9F36pMOXGNO+cRWkrSImAIA=
*/