/*!
@file
Defines `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_HPP
#define BOOST_HANA_ZIP_HPP

#include <boost/hana/fwd/zip.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_with(hana::make_tuple, static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_HPP

/* zip.hpp
lx7tRuA79VSX7lgnRLvueliMbhf3RBNBjHpQrov+CfKx71lOOvvqHKtQJBFpQjYPBnHmBAfcdJgfn+IUEPPYqX+Wl8mzvMkr6HUasjMGy4yl7Dw1gDXNEfruSpBnhTZ9XDpwVxNxUcnQ3UFcfMCFLp4K4+Qd+/1QG9CFwk4vedm4OMb+WAgT39nNufSWHH9xTxjEoYHA5cM4VB7nYUfPZPgMBnZxDAD4SVyqgz6wz57mXb6OfFf8XhDDkRub+pHnIfavYWz7ooESFuMUxCIP7Abuw54axLnzvwvfrieH8Fg5erQ0qXM1dHDpWAgPndHDGhvE+TrhfBgHDYy7Kaee8ypsotpVTjUNzHO51y2X9RWX/UILdMeTLaw+tjB0oDLowT6zNxln+THYZau93oUIFsenXbUxMrHrAHPbrpdV+VpHvAlo1yt6J0Rzg356rMAUTxeKVq7lVPx+sYejrltXrzf2WWoalMVDuzTEd3LeN2zM1AdKPn31cE4KY60ElljbXKwOQsQe98kuPTI6Ew+Ow1KDgvy1yVjemvEHqm/FOM6Fv+nItwDyPgbvgeIM4rYDGTKFngvzWWv3OXz/FM4fQRxCeYHreThhciIcfIHCODpsifejEjDpYja2nYQxfBhDHEECJk807He8vrL9eu54dP3yq3xHwMOw/lDP3pqpP4SfUyJW3EWFMajTFZ++avIO4IwpdXYminMYtTeH7Y7Kz3yxJf3wtm0s02vURr5hEza2iaNBXHNGYQXuss2vtKwi8XtdUl4zqx3CwZ/Exi3lqvnlrBbD1mbTxE2gntckni0D0YvV/e6oZ51tn+jizM0A1qwW7EhhLOURulijR0O2JPZaEMvTmRlL2+YNF6utU7KeV48FMC2l8UYq15HSk+irD/lYWvNo3PUwaJvuEPeRTwrhU6voI5sfrBlCh7awLjwxiDUdfwHnNb9MGT6ags+kzQ8WEvDx6CJ8VObAscs7XV5e0YldKH5S5FKfS8CxTPJYa+9HPeKIOQ9/J0cc47MRwvoj1MVcCuBNpq/uWuqiqXs+hFtPrjvOO8HvTJKHVANz9VgYRyv1usydse9oGCcbh7gclB3Enl7oifewE7HdtXqDUkTJO40E7LQRM0JjjxLAun6350MYlrR4zl8RGNs9GvMZZd6w+jKLaHeljuGH4GL0/Tp0nE3P14w60G8dYf0TcwRu2LpKBjMXxFCeX5n7RZQnajxCHkGLjvj7EWzLLp2VyNvXZb88CGC4PTLG+5CFMZ176YgZB0l34trP2+0kaQjUQX5vx77HsT42BspLmBvVoQ1zOG+Xays7qYslXxErD98Xm04jRP+bj+V0dp+gFypVvaJa+5RtySNviQPuFucsTGS3Qd4Am8YWNtzT2TTqOhwSY51uYzAE8K106OGuTXVNfaYtvO3rULJpPGPl/eqsTWcLMPZFzxC0XMXE/JPPOrNpNcW4nLOxcBnA+dGhd2x/AeiQDRuHO1OJhR/HpI3VgAb0g+CVoZ7bpKevTCMsW1IIJ8uUenCPwJbfWKouq20r64kG/ISf6mNaKsXGFq0UqyNr77Pt86Pj8CZl3kk1Yc846mIULy4TmH0oU2LsvfC5PT6GixL7hI0pD7Pe2KLbYdUEigBH3FQirk9u9XRHIN//S8Ty1BngXJSIq1P2xjhef8Nrh70n6vl0PnYzSpR3UugKdqXZ6jZHm60BnXqt8m7st3GGjrt+SXddfASfWw5O16eB+5bHC/pSRVybt9q9oeATxMW265NPsOmjjloY+yofbRv7VJsHr1UoSdT5cgCXErI+a5elXxTLdDtDComv0qFEyPqcg0WA+CC+Kz4fwpSjepUjt+74/tmum5U=
*/