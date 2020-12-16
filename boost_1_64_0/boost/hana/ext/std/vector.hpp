/*!
@file
Adapts `std::vector` for use with Hana.

@copyright Louis Dionne 2013-2017
@copyright Gonzalo Brito Gadeschi 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_VECTOR_HPP
#define BOOST_HANA_EXT_STD_VECTOR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/less.hpp>

#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct vector_tag; }}

    template <typename T, typename Allocator>
    struct tag_of<std::vector<T, Allocator>> {
        using type = ext::std::vector_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::std::vector_tag, ext::std::vector_tag> {
        template <typename T1, typename A1, typename T2, typename A2>
        static bool apply(std::vector<T1, A1> const& v1,
                          std::vector<T2, A2> const& v2)
        {
            return std::equal(begin(v1), end(v1),
                              begin(v2), end(v2),
                              hana::equal);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Orderable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct less_impl<ext::std::vector_tag, ext::std::vector_tag> {
        template <typename T1, typename A1, typename T2, typename A2>
        static bool apply(std::vector<T1, A1> const& v1,
                          std::vector<T2, A2> const& v2)
        {
            return std::lexicographical_compare(begin(v1), end(v1),
                                                begin(v2), end(v2),
                                                hana::less);
        }
    };

#if 0
    //////////////////////////////////////////////////////////////////////////
    // Functor
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct transform_impl<ext::std::vector_tag> {
        template <typename V, typename F>
        static auto apply(V&& v, F&& f) {
            using U = std::remove_cv_t<std::remove_reference_t<
                decltype(f(*v.begin()))
            >>;
            using Alloc = typename std::remove_reference_t<V>::allocator_type;
            using NewAlloc = typename std::allocator_traits<Alloc>::
                             template rebind_alloc<U>;
            std::vector<U, NewAlloc> result; result.reserve(v.size());

            std::transform(begin(v), end(v),
                           std::back_inserter(result), std::forward<F>(f));
            return result;
        }

        template <typename T, typename Alloc, typename F>
        static auto apply(std::vector<T, Alloc>&& v, F&& f)
            -> std::enable_if_t<
                std::is_same<
                    T,
                    std::remove_cv_t<std::remove_reference_t<
                        decltype(f(*v.begin()))
                    >>
                >{}
                , std::vector<T, Alloc>
            >
        {
            // If we receive a rvalue and the function returns elements of
            // the same type, we modify the vector in-place instead of
            // returning a new one.
            std::transform(std::make_move_iterator(begin(v)),
                           std::make_move_iterator(end(v)),
                           begin(v), std::forward<F>(f));
            return std::move(v);
        }
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_VECTOR_HPP

/* vector.hpp
Ictai/C4Gn5TxN8q9uD5wktG2xwYw09G2XovFJ5Wa/er9bF1PlqV3fmfJnnrDe8wsr2caopswsALlPz2naND7mJkHEKrUh/9fHJMtgm+a0ad61Czk/M++F5WrBESkkG/6b5YyKRFMBzzKQhPEXw5wdW4hd4BBA58txjtE96vCeOxEHMC+A01+oT7M9mAT/h79gk9fYkSnr4caqL3QIYHd/R68fORJrmzUR5Cg5Rb/f3LZX5ZYOW9C5aV3X4bYq9H9exJ4Mfa29JydIzf6fPpJKtT8W8UuPxC2JdqXtV0DhqRbz+WBvYH7/BF3RAvaOpc/hDBH9wka6K+78DpqTGBS4kkXPYsrZwCjt7I5WkGGX3zBHDYvxCcMfMKwPO4omzijPY+KcfXHk8MuDYfAvysNpelk6QzJoGjvBXdHx1XAfwytLcTNM018XimkozfnkQ8dv19IeqWb6TjOq5PL7Z4eWuOxuGly6L7Ws2R5uURvIl9IKWi0Jfqd8Daci+zbclbBMSbyx1OX5PP+yVXAIebLFpxw4Ydn1cBNjKsMh3i6/drLJxvenD41xp8//C2dG//IKbeSPye8tc18R1bcdzrozk7cgkmClAch0jUK9uSEy7P7s1hGqTzOd/2rfH+A4csIy3cjubtMRq5g9q7u+EdMZrk2w/viuGNbOCeC8vf91h83J59X/Ibxnlt+IAbR3mdwtmAHzRlVTq1nj8zFZg/Xm7ENVG7w4PWtLD3F7nydD2G03fXxvFy7T+m6YFClu2Dj8XpJECreYC2wjQKWaE6PhGuQ2lod2+49y1EZ+faulB7Pt0cfYcOEgFw8nG9R6PxBTqL6tPQQ5PV6shkYU9k0Arq2FCFJqvcMm1WFNSkU3UWUGW4X/IUspzfqEoDGbE2zNlVaOBTRc85ySkXym2hMfDk0src54jGfyfo894Y+vgvWnkXte7dYfMV8SdkLsXe/rvJzbGZEiiiO8V5b/rroCGMZL/r5GZL802fBlyJNL3dRyae6f0rMIzH5jteHcMk9fb+b6Zx3HA+to/3dOQPg/3EWplxc/jHQRpRgbSu9S+RfTi51EAlC7At+JMmySVSSoLWoJ8BrhcYFMRZ8yL7bTe78dDNqdHiNQp4td/CY2nb+wVwtLNlv/kWwDVIhngEpr/aw+W+/ppkjPXdbzQcFmJqZNewLhV/S+u2JB7MkoxD4vtvXf1EYLLWI5rfezR4VE0TsKz/ETT0CYm5cEeiP/G14U7No+lJ5n2E+xvPE/SB89Pr1ri+TVDfWG/MBw31jQbQ9e8oqieEP9pvp7Q/T3EulJfxpz5GuGPWmDOT6JyInJONp+DbDCyew3Tcmrhu8ccm0ncnEJ3VAMj+xIF7ywd+PwRdiN2RfBLKi3KKGE/7uA7H+XanUJsGL+zgOEWCxulWnZsA/LsXmnOvLTX5XqaWpG2bjdm2J1PfObdpyZrQeWWEJJGKKFfZWj4tA62O3NA3N8TK0ykSWvNW+G3IUfOZ8iwSPnJq/FCnG+NVVehxtp7qrXrWGudBEWKSypn3q9fQ3XD2ci+88uz5poajRh7svrn3Rgk9U2Prb1qTpGnWK/GRaCqaaB235b+XQQ1Gda1ZU4Wu2em7tWEa6ZiRudNB892FqA/0rbXKnLJWEj7r7LJq95pKCd83xD1aibiIGsC6I+dP6Zi8jlgmZf8w90Pk18RTJZJq5/m91rg37iYmS2P+WRY5P5tPqyeCqK5WlAMYL1eZmMl98N8nnIo21PjVxMNDGJVQ7tejvb7TvFVpgMTX+6JNebkm7a/1F8m4y8EMIXNzeSvw/t2CfD8JJoaIm9N7nVGdKMj2Yo+qa795PnTn1ou7O0eS7yFeHKA=
*/