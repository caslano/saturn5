/*!
@file
Forward declares `boost::hana::concat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCAT_HPP
#define BOOST_HANA_FWD_CONCAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Combine two monadic structures together.
    //! @ingroup group-MonadPlus
    //!
    //! Given two monadic structures, `concat` combines them together and
    //! returns a new monadic structure. The exact definition of `concat`
    //! will depend on the exact model of MonadPlus at hand, but for
    //! sequences it corresponds intuitively to simple concatenation.
    //!
    //! Also note that combination is not required to be commutative.
    //! In other words, there is no requirement that
    //! @code
    //!     concat(xs, ys) == concat(ys, xs)
    //! @endcode
    //! and indeed it does not hold in general.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `MonadPlus` `M`, the signature of `concat` is
    //! @f$ \mathtt{concat} : M(T) \times M(T) \to M(T) @f$.
    //!
    //! @param xs, ys
    //! Two monadic structures to combine together.
    //!
    //!
    //! Example
    //! -------
    //! @include example/concat.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto concat = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct concat_impl : concat_impl<M, when<true>> { };

    struct concat_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr concat_t concat{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCAT_HPP

/* concat.hpp
gR9woIMyfphMoo0RcLxqH0+32JZRo4Td5YweKFN4196EVKDd9hrS6JHWRaZRNJqb0LZc6cu5BBFarLx4ow7Rr5CFUtEx2IIm+6pHkhnCwDwwHD9Gq9zknLCULhKwD64x0IegptTyRnrycHunueXmnI1u4UxS+SGGE+NOEP0MxVEJmPx+S0Fk4QZ5Yw4S8VUAXyaJOBSeTytPAc45KRSGBpIaK5/odaw++nUju6jPo9b1j6/0uoxU10YqMWej+QCJJVBhU+uvUSQ53DP4h1JDjUAOn1F0hrLhV3pH1KvQtM4VIGRoYqxge197zVILPaTbaxbwQ397zWX8cKK9ZhY/9LHXlPODDX7X+eEEe81Yfsiw14zkh+TAlQSBeRP5ENYxK9+tXPCGdnDrBwDtAIN2egy0j5CbTdaV0Y8wFreeghCpkZHkmjAHUboWC+O+00iy7l54IWn+5BGo0n+KtINTXxxLfZNFbyfloD5yGOzXv2jmYHg1NUCyzZkqxHHo1ocRhWkKDoQfLPbac5GxU5NIgLPkpjij0uBoQ9UP5VlW1xY6RSj3B8nLrLcMKMxaZCtMxdm6NL+lsEegtLDqqpLigq2V7+s9MOSGWA+YSe5FDIxX6RUL3o1gKKqYBba0puENuDQNLPdkX0/pfYZ97y/11A8ifsSgqpdldu5pMbulzzhJ9RY9yQokGVswqPItjxJQS30Gy7mOLzfESpthpolC/gWaCwZVmeRkOEoWE7LfTfq0PY8AJLkodbByilokqbj4Xou3DV1239R1ui8De00YafQu6ROr/00Usvxqi4koaAYByG35eLWeYK2JrCdHuKpOlcda0d48rb2rN+tpfo00pQWuyrfJ7cU4n0ky1FKKh2KlLDKR+ueMJgH5g7R+WDhNkqxj0sUmDe8orVFNW2WkVqYetZWuF4/WytxY9Z8ZuZWpia3sGUvwivEorXywRU/zmLHLVm5cpacIGwnyrFsF5KxtSec0g+v1Vv7UGN/Kz24RaX8Xmzm/NGj4R+4p47BmRqwiyk19wZhTsHuZSW4WeJMJReJvdLz5ShWjU12RfL1j+sYK2qN2KliFDFYUeJXPr+fYAoTaa9ep3Dhgcxpg2Q1ZspRNTQpnnqmcHxKLYRuvAEg5AuS3yinoLTpxkNaJczepFVZdWVqANJX7pFzulxRRAiLK1VqyMUB6i33Xa/nOpWiiq2YssyH8ksSE/J0CpnFYLWnviF9SJcrtrCOAYQ0NKZudtb1OWvG/CwnvRcLvHZmDhNiuczqt5VOkWxnUZzdylRoPEHmenkz09KSvjzSO0rjalJ1hDbA7SCAe+e22/3/+//naT0MN+z/cEK8fI66zTbhZzlr7VrCvgxRjq0nG+z5eSDdGL/BpgMmN+S8z0vGJwruJekiUP/qU8MestN0D9F7JL+EZLFSRm3hn6MHJ5hTpQ5QYOblmy9IU6Ut67N/WVORPkWzAaOjoOwZVDZAy8UzaGy7XrbzN7B1ilbEsqrPIu8ukD6+lWXLjBgZlOiZAZoVQGKJqygaFyRsvkMKEmtuMQDrHQMaGiGgUEd0w5v4GnzLlrN10QuoXr4v1wIL1O9P3U6mwluVAu4Qc6NanVTnQdHFlFmyFSmo6onxUrZ3+al+v8go0eWwl15Ou0tgKWZVXaYaBRZkyiHWpw+RNx3PpNVeXSa4RpAVM+9xNXG9uYq3Do/iQY+ADUh0nG8rrYC5V9rV1NTgsZP/TGI9fNgSR0jUDv4RaWfgF92RTUt6grrr4zzys6mGyE2bBOTdloTHs10xDRUU2e3E2Z1BQNRmDNjcbgdgAT5AMeBAuzZXNy/UVhfYMJJ90cxQE0XUdUS1pNpLexkkzsCE=
*/