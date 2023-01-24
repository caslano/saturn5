/*!
@file
Forward declares `boost::hana::union_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNION_HPP
#define BOOST_HANA_FWD_UNION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct union_impl : union_impl<T, when<true>> { };
    //! @endcond

    struct union_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr union_t union_{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNION_HPP

/* union.hpp
61OFGtB8z9XxatF4s2lnenaVcwsAz/Fkbd/EUZK3NDI+XGCJo2j9vR4yzMLsVKdOSlxQ6DzxhLgNwh9wKMVkadFs3bY6P1LWkJZRh70N7PAnlvPDAoi4XP0k/uDAbq/gVJ1U+qdzBkx8tedg+3WQsRpgqR7wuzzBZFXbXPHzXfL9tM9F9PcHbhxsLY8Cw99QGlbz9qgGY9/ay1qFwaNNb9dnU7Y1pjyqkzYU0jx9mUAZ3m4dsdH6Hhr0HlQxClZTWNVRTxsa9OdKT69rio0di0wc3eaH/EDb2qegnvYeRSiDjsosbIFVC+39MulQLj0+j1bfzzwYiDf1imGx/8kP6Fjv4zLt/lN1zxZK6Iu1i9w9lBOpYBgyxSfKJVgJLMQu0+SSLUK4GjKhVH+pkNjig7TcNRTKC6oMvr5h9M0iHh/XHUXwWq7kwbViGy1dV4cwJ4t/rCg11NqPC2+XEorE+zkPsiU/7gaQXGnhSCPs22leCu1YFmZ/UuXbC44G+75Pn5yvgn803EgoO3bJt2mBbfhR0RDdJm25VuTLfgNWUZlPcKSEswbjkRvYYglQTyY0wVLFCr+VomypuyxAA9XcPR/SKo3RqdhkF8sMSOyHxLd+KWY5ohVrnarckTClYk+frEcg2rnh3yRAlEXZERGuLVf5Mis62qhzrnyBQ8I74uka0ZQv8zTySy7cXFA+Iqc1EQD+uyJ7FopvG/xH
*/