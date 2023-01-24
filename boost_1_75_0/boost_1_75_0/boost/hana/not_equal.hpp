/*!
@file
Defines `boost::hana::not_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_EQUAL_HPP
#define BOOST_HANA_NOT_EQUAL_HPP

#include <boost/hana/fwd/not_equal.hpp>

#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_to.hpp> // required by fwd decl
#include <boost/hana/equal.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto not_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using NotEqual = not_equal_impl<T, U>;
        return NotEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct not_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::equal(static_cast<X&&>(x),
                                          static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct not_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Comparable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_equal(hana::to<C>(static_cast<X&&>(x)),
                                   hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NOT_EQUAL_HPP

/* not_equal.hpp
XZYgE63dRNnkMFSx+eEaWVCNkc1wn/4RwyFO5gHHbI9NO4Djn15H6T0ajOgUac8BlUvkl8WaZLBA0UnKNAum9dcDXtjrweIi7ed6Lok/pLS1/8PBBBizukviUxRzalCHBeSUZyXY6r+sBWxqQU4b/kM9+20T+m2Ti1Fxq63sp2P/4WGmQ8OweA5Kuu9C14BsJDD9kcWdtM4zw0Dk3k9xqz+x3412iiQ7riTlZb5A5TKa3lMtPnv3X3a4jj1oej98NvogJOlMPyhD1+JguzbgCngGjyf4BjU/abcmG6mZTaCo/qE+ppPQNGSVZlD91aCaKaXpk441y4q1OhhmIBagIUZjD2C7vULBskKhDu5J0I76MdXtSvu9J7LI1wRBkSp3BCMHSHSJ8U5OCp5JjZ5JxRMS7fEsWhHaVhzaqbEjPd8WEjide2gTLAoepZZpZZVpbbmdjsJ5zpqCRyq0hisGREwSFE1okx6p83YZPP3ExPD9kXcPXe4T6osvT6iHjagLyT4qT77VBIRm9giNrmX8lxjhKLOMHqGiESFX4VN98PNiGx5qG57eQKRUg72E2UHfZa9njSrwE9QooAODobk1KXez6xS/K3dItn3Vc/84mV0xEGU1bgmEGIx02mut9eqZlzbpmEA4DSE3+hAo9ZyJn9crSCw1Vnwjl7fAr5v8ewhpyVVHxGlRkzc14fUPgIOlamqByldCMbBtH/cn
*/