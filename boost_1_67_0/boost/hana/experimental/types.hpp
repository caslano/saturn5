/*!
@file
Defines `boost::hana::experimental::types`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_TYPES_HPP
#define BOOST_HANA_EXPERIMENTAL_TYPES_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/metafunction.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/any_of.hpp>
#include <boost/hana/detail/type_at.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/contains.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/type.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    namespace experimental {
        //! @ingroup group-experimental
        //! Container optimized for holding types.
        //!
        //! It is often useful to manipulate a sequence that contains types
        //! only, without any associated runtime value. This container allows
        //! storing and manipulating pure types in a much more compile-time
        //! efficient manner than using `hana::tuple`, which must assume that
        //! its contents might have runtime values.
        template <typename ...T>
        struct types;

        struct types_tag;

        template <typename ...T>
        struct types { };
    } // end namespace experimental

    template <typename ...T>
    struct tag_of<experimental::types<T...>> {
        using type = experimental::types_tag;
    };

    // Foldable
    template <>
    struct unpack_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr decltype(auto) apply(hana::experimental::types<T...> const&, F&& f) {
            return static_cast<F&&>(f)(hana::type<T>{}...);
        }

        template <typename ...T, typename F, typename = typename std::enable_if<
            hana::Metafunction<F>::value
        >::type>
        static constexpr hana::type<typename F::template apply<T...>::type>
        apply(hana::experimental::types<T...> const&, F const&) { return {}; }
    };

    // Functor
    template <>
    struct transform_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr auto apply(hana::experimental::types<T...> const&, F&& f)
            -> hana::experimental::types<typename decltype(+f(hana::type<T>{}))::type...>
        { return {}; }

        template <typename ...T, typename F, typename = typename std::enable_if<
            hana::Metafunction<F>::value
        >::type>
        static constexpr hana::experimental::types<typename F::template apply<T>::type...>
        apply(hana::experimental::types<T...> const&, F const&) { return {}; }
    };

    // Iterable
    template <>
    struct at_impl<hana::experimental::types_tag> {
        template <typename ...T, typename N>
        static constexpr auto
        apply(hana::experimental::types<T...> const&, N const&) {
            using Nth = typename detail::type_at<N::value, T...>::type;
            return hana::type<Nth>{};
        }
    };

    template <>
    struct is_empty_impl<hana::experimental::types_tag> {
        template <typename ...T>
        static constexpr hana::bool_<sizeof...(T) == 0>
        apply(hana::experimental::types<T...> const&)
        { return {}; }
    };

    template <>
    struct drop_front_impl<hana::experimental::types_tag> {
        template <std::size_t n, typename ...T, std::size_t ...i>
        static hana::experimental::types<typename detail::type_at<i + n, T...>::type...>
        helper(std::index_sequence<i...>);

        template <typename ...T, typename N>
        static constexpr auto
        apply(hana::experimental::types<T...> const&, N const&) {
            constexpr std::size_t n = N::value > sizeof...(T) ? sizeof...(T) : N::value;
            using Indices = std::make_index_sequence<sizeof...(T) - n>;
            return decltype(helper<n, T...>(Indices{})){};
        }
    };

    // Searchable
    template <>
    struct contains_impl<hana::experimental::types_tag> {
        template <typename U>
        struct is_same_as {
            template <typename T>
            struct apply {
                static constexpr bool value = std::is_same<U, T>::value;
            };
        };

        template <typename ...T, typename U>
        static constexpr auto apply(hana::experimental::types<T...> const&, U const&)
            -> hana::bool_<
                detail::any_of<is_same_as<typename U::type>::template apply, T...>::value
            >
        { return {}; }

        static constexpr hana::false_ apply(...) { return {}; }
    };

    // Comparable
    template <>
    struct equal_impl<hana::experimental::types_tag, hana::experimental::types_tag> {
        template <typename Types>
        static constexpr hana::true_ apply(Types const&, Types const&)
        { return {}; }

        template <typename Ts, typename Us>
        static constexpr hana::false_ apply(Ts const&, Us const&)
        { return {}; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_TYPES_HPP

/* types.hpp
pec2OmS4KqKdyTd8nDqQOow6ky9b6GRom9kTnK/m0GydA7jJODr1O7gPGNoDgFyDs2WshWhhZgKZM4YogCoes2wNuaG7kmYq3gXPwxDGut4TnimnUukacLb7IfK5PWDwWDSauJe5J7VsLYyOarOvXumPpJh5Ok+5THTJQf3Ge4v7F6FblCHLabJGBvFbOdZvf3eqfXlqKVoS5f/2TtaP71RJ/015ZupipZH9r4grKru7MTmqukJrNH0ZwBAxJCeOhLqzcvyn74lyTAojgKf0yBdlRRCTcTP5UTCmqo2KDQlKlQjyv7TvvwzP3SB8dCNCbSx5TVCAPNx/vhfX8vY1Zc4ODHew/Ay77Z0nPWHrQ/SrhBFxXA95+Nvd1BXHovZrckNvOpEgw8RsdXE2pc7oH7AMWtxJAIK8XNlJM1E06t42m6gsHIe/5U4wP/khpb8WGxz0GFjkfZSUwgkfCoUKM90vSXr6ra/tsdWGXVvqPgOBrscLeLKSqxrT3LbPxv8rstorLXq4CE2SGeBO8UR9iXI0Q/kvHKHPO/4yh/Y26Kl5OXYWxabr+IMEk+DR4kWhQ/BZmM5UG5pwMTPZWQHEjDr8L+X6ap8sfo4Q+03eEU0rOGQC19rhfm+KAqqF1ZK8D7ali9Oqjc8N3OQ6ujDK9gzkZpHEWK1tMTG9vBuO5IXMeKcVHbpxF0YhvQmI1JHQcizQCZabXHJh/rWi6fzgZuD2VnbsbaefLbADc5ajsz6TYH3Q/mWGrnEJyHHIahDIW9jkA60aTgUGrNwPcBGWs14v6OC+OvoZCHuM6RgetiQ5erLV1geIlPdqKSRp0DUd7LBsrSN/EPkrSp0DK8a98pCuDckCJfQQMj6RwR7XWZwufSP0p8DX+L3QBBdOoR1L0aBgAjlwo3y4GWJLVLwciDiyWwbWJCJBEyyFHQw1+V2LOofajrVpcs3AhcFgVJ6iMStNk2VdQ3TNc0gYQpHpvCuiatwr0Nb4G9VBrJ+Vb4nqiu4xmSctsFuhaZb4F4SWL4vKaywAdCKb5phg730Bc3GvofAMQzDYveAXS8yQg6zW9aQi7PxePpzWWoeyUvV/Rz7x2/4O8MvrEiBQURKUkTGs7dZCuTpoVzswWUpI7yZBtnn8RVpelBaf3BriZD1qF8yS/oJ7ZHgvq58ajcNqQczvjKqUNvyr68rSQ2exRnfWxqDOW2W3T0zNDlj7fEShZkxB0dYZV09N/YO5JJOqU8q6ewW074pmFMtNYitJT6VrTensqiTuJlHau21mgX7bzz13GyRWdKGwkdvPEuUJ16IBOhqkQsK1JKX/QVEfCGRvb6oLZdIFQB0wn4MBxgwCV9cmzbhdlf6mm+CP3PIh/z2it7RPmPdQCnaeZbepO6d5Mcy3StanggJpj8dPHWwjOtPogXUv1RN1VOfvaC3SezrFbZputwpy1ngu72yQOMrEi0AbxyziZiVHfjUciZnq3Y1Ifiu5FqrTh3NM96ipwwNZhyGktioWaj1tpMSs+GAwQGSj4j0OLCR9sSAYqffHEmGLqOFrDcy1F6AaPXPoUqpdm3sWCUZ+6FhRuSgkLP5b5IlOL+zF5PAbel+l7l2UDnYgSR1mmDTqDA4bmeDbqU/mRkvYIsgMFn7JIkDZLD58J8g51gP7vXJn0T2Jovrnq3szOf7Eb7Q9/TUuKZQRyXGmuNTHrhYNjIaxHhrWcfm9e+7SIPMK766vwiy7n3C+0gFx5El3hRhlVB4anLTUrQ5Vn1dou3QAdZIQbzrddZepYdG9JZqNVbGsQcFSIRLH7/IapGRcTLxCMMZ/aEn0cLWvITXjecJw4DpHcZE2fmJ0LTU1X5K//0p+4Buu6JVjya+ynnrMaBC7yknvUjNYC3B2lXVtSusYadP1kfYifUXkEwulyggWNTK5uAXR4LOPX3qqUlW5dFc3AoFrOhlBzQjyT+1QahuNxQkxz0l0/j5tUly6GAaETn7n4dOdQllOD9ckhcPdur1PtuGa8T+OeH/I7z5ZwUb3VN1YBWrWib8xjo4eiDmlXJVG3n/gFtjdBb5foOiVWuUo4A6Fwe0j6RBn9Od33APuK958oxvmL/CXmcqo6GxnpmnCTrQplXauSQVFELEV37lNdQWHubMVa5sKS5kS5W+bwH8KIopA5J5A4F/lO/kc+TfCo8MrbSYHowr1uP18p490mLdXpomYnXT6xAg4TbNQyzupx3avu/hefBmRoSe99vx1N8kCgHKtMqsnS91RsY9jqMa0u1mFQCn+xL9T8cdiFrZ737IhpfbO6k5Sn3bxYULcMxwDOqInswD8YI68ibYGEgD9GAxwSthUPiC7yB7VnScRpxID7dQWCuoRPUcrJSdp/Orf0hV+X49oYMyxflnVRS5SM6kZ/Henb38nEQ8OWYdYA85Q6BTeqU+9Ev2w6KD7MsxLW3eHI7Qm+Zqs13E1iLkxcpTg6Ixsg5bCfBnSM9/N3u0olX0pBc6M+htXADn0BNKxlyXvgXiK36lg8dCPr2dKfA7xWavh/DT3nrg+j443ycwLmocJxkdPlvUsTF7gF/CILxgtWN5oLs8LdrBWl4EzDLghS+oMm3gFz6fQUUQSUr2+TvM+64rjhTAvR9NRzt1b0Gkc4k7idqg/kKpXFQHwUzRchspXC2b7xO06iRKNLv5oQwP8y1BMpERLrz0pix4HBB+b/CSKPvqHUE3bQz08BH9tIRyMCtaL/aDhgUQPpMm8IyjDs0puWD/bW72NbTFDxrsN1bZ1Ov9XxUCDe/2x/fUkQjS22ncrUkAwracAQGEqxJmziO651vZANu8SqQ8kIgaK/e6uoEp+VffoB7y4fvN5SQEoN7mmbA893LGshTI2iiqWt8XYGWDossLXbUkXWnvX3zzw/z3BOhkQOkFSxoioewPzoNBUZnoa+n+pfMiTnbP+c9yRbdU9DREpm2uYZGkjKVH3X83/aZ0fqtqaPOmq4bFN+eaiqZTapyni8FzC3ZUBWN9mwOpZwhBKpAoM8RjGnn8SwC8zKDCmFmB6od2iEb5qESZ/+85kihO5TtvPtVfh4myQX/DCyTVoTS89d43QfCRlrbDt+ci/J4u8ivTOXvrWIbRloxTKMvRrb/96xC5VCQ28owtlRUu003rsWk/HKtvud9baLoq67MaJ2OBBf2L3DXlmfJ/epqEMypJ0C7MJ5c0cb6jNXvraLSmCjsAC0f1NmXhIq4+hPtVGcQk95n2qhov+H+GphhrgQNgi/dN3GMk6T/KuCzinOssZOw+GRMOQyVs18YZtiEuqVHwFUDbh8G+Fj8mO1tm7/KawViJkDYMehKfaimpG65LuFQIe+Gb+tl2B/RFx2YP529iKUrsxjwANLPLTb45qBVOemTlPaUqr055s3zdQpVcMZHm4scQ0hA/NDfVcNzplrXLbW2Eyad7uht+xNRLJyyMYiTMiYt99zHTmBMP0QxNnB1xEev+BPAhGaadyXpIWKAp+aG7XbwIqdiFnnx/HBM1mH/znuEdZDHXkkLR5SAJ1CShsmZLzEDiJMbeGy5dkMDxs/mVZfYdX/PMjRJ74UhRA/koUrc5O5PZLC0ieREVJTkNZ64KPsKdDMHF/60T8wAjwkE8Edd38cNQKtJ0Oq2ZX3NPUjFC7i0XVs+Z+A5DjaL5hzMo0n5bly5loT1lxDtRWuLFv2Fm4En69goL/MRhawDtuuXmXqdL45Y4ouSrTY6EZxTr3fVqMLJxXgqmQhU4ijyPR3pml0r25pG4M7AdtmBIYFvxSDNaNTMc67jYHSAgmtTgxiZBJyOuEunS5WoUaAn3H0r44sFqNP0lNhT+hhg6G4AaifhWGvI6A2ZSMmzCZNavvgPOZZsv0wIQvsCsFNbCk60nYLLWoNuRTDTe4qz8v8tjQddawo63z9JVfDnk33H0W6QIgJ5IigozFKS7FQNqSvbZg5EaGStrUu0Kt4f/QYh/RJtRIdaWOYjYug9ZwobrZ+PxqmBi1I9wSTKDwyYtQNH8J5irL83j9lcPBBAAsG6UUTYKu2KHdE/Md3BuYWWSnbgUVLW8RYmRs7d2pVBHKZtKJ2W6m2RhVHaVQlgDP0oU9+1MYADZUjJFSpLPC3StMhzuEERIj00dJ54YTEtwo20y8jYFPdlBIyH8RS1bdfPU5P1+Mx0WJrkA35rA6bCSz3ytWGfEucZ1kfvebKaCushCoNabXxssaYg7l5Mnvpu2VNSlSlo9Un6wQEQ/ryvHw10KduxO/bcJz1HBcrqRc0bIsneJqd+Nlk8lvH4L1alWWsZqBJ5R57vhZoRkHafOaigpFisFkygp57IvuBIN0zIh+tSWgI1xzMDJ2pVfRRjtMLY/hwTwwZiJm9EeouU49IO+CZdKYB9bofGrYJ7GL5Py832TwJrnreE7rDxqfRIdfZbs+kFNWJEjg4L1mnzT0bhed1/cIOX7MWN1VYfYZ/JthhZ8yccMcBxqY+uVDH013fwax+6qk22Xo1ui5IZLdcFTqSbC976MufMHBbZ8QZC1VGRfLl/onrk82KV9QDLXAOO8p92kk3CVV0FrApilE0Kgsr+RC+8UD7H+8fWfsV8jV2MvnATfwahkRK3Dj0Rz4PBBTh1OTetZFHx/9PwH7ebMwH5+Tsw/LxQPgq26cMw5PW2mUDO125xEkadBWnQRLRs/cbD5aLy/WNtl9K+9roRE/68qsWo6IeFfoFzMIfKR0cIxPN4jecItCtjgeSkJH+eJa8LZsS4HF27sjq+klsMr2FSyUEuBR7IWQKMMOhtOtLaPUomPqTTG6wbQSq4ZVuMPIBkWlGa/KvF5A9qqMzfJzoPJC3YPdkCQtWU1fVjnaqkxfoS6oUHESvQjGKikQVjPFwQT4FMixEtOtLnYW5aMm5/VPO+mbi56WLD4sVfK500tpFe28GpIzUMWPXmiHai6TSpndZzzjte7rudo1IE3YX2MACaPKSYmxjpq7HxEhYNNKiuHzCafsPKIq8J+AAdUwFEzzOK8OUE4a/qsRdMY04qeH5HXXnYG+bumV+uxo9mquDFsW/LEcKgbA6fSI2B0K6GlJhOZJ4JUwiAF5akBLD1pVROO08vGFUegHH+fTYZmAxuFZhBjHoehIUVQ+3dqE4mUj1KAw/9Rh1Sw/+MTTd5eXa9mE0LM+qD1Luujqvwm7n9bRPxsCM/tmViFgkeVaJCmqHH/j/u7HFA7tTFS8dTMZajjFwnS2rV8u0AoyVbyb+9lWR2r8FZfRzWBhWuuMN7GwziceJ6JgANA4a0jjgYoazUVqa/mr23mjGfOlsV7yDdfR3K0uirA4VAL3TO9GDh/Fv4qFNl4udAdnkehrdr9dj7pm4jz7SwnjDOMUxyqT7J/mD+wBiVul9bb8v63akqj0GWtnm0HYJYY7YetX+eNyVkK+zoFD2Ypp1dj0kAOlJiJ/aq3tUhA2Zl2rKtCa9CBq56oEYmRzPzh+sQl/fdof2HWQ73voVzw+tB3aZ8wnjNx20ezDDRBvbMcw1Kq5pGliZTmNpBjHAEY2sQmxRiVikgh8nmSAVQo5iAMYoxpewgySaa4cg8LHYVD9asnLtJGAfJE2K9TbVYp6KLD26SUMe6C9Ff7RnAHLUGun45jLJu1FpcyWqM4zDApa6FehJJeD5bs5oro8WCFOLI9gNrBvITODSn8/TFimpa2zWnCe9z6PIMLr/8iJyXWQ7xydTuD/f+14m+jl6fAuvmOfHt2G7pAzJKte17jhPcADRtxLajkluQGWeE+9sEPUgHX4Ug3Ocp4ewuJbRncap9d+aYqpbMTAs041aSYlk/CG1Uzn0k/B152cMQTL436oKZ+1GEmM7LbWhDDdmoJzzP4jb7NCG7vxKvVLgSgyiDnxk2UBsP7InvfH6wlrjF3+oKi0+wO3mORykY6909iZuzrpmblc6q/65RkQcT+ezqJ/ipBwhR8nY0/PxDbbABUUx6lYG1nXHmogBRPpAnxZcZ5lz9oGzLmOVhR+xuEDZYcBafqi5XNBRY30rG15RUYeGn8GxnTL+ejgBIEzw411kiH9hXqqyhY5Fx/Lr9uZLfzvpucaLRbJ62yDdx4sTmpvnik0H5mahOmv94I7DL+nldSBGBfRDokNfIVhXmYuWaDlmbrbBeUIrFQE/n23cQUcYWDGvfdP2+i1B2AAvNNBmj+TkaQoo+4NejvjHBpzTbD+v6JSPpHYRggGAV40l5B+X5lxJNBvwdEMucjIbjO5Yl1AWQgPtg5Xss8MfMyNsYIP4x5RlOx3oJwqTdVS9lBkVSY5fIKPBR0n5v3cRoNNTa7qod9zWB6U0X8ZvNC6D/KafSlh9KLbGh+cITjBMlPU+mxa25bTCqXlMce/zqaqlcE7xdagClXiUZ+9jGeO28QUheSeEMOivz2PteMR+wmDuRMfndazD/CeJ5N8cxKicZuIUbdewqVHFZuOyY3/yRWeDcXyR6uFcynZQ418t7tjje4mHp4Svipf6CxjUs6tKiUPVZldiJnAonoRhLuXMiPXXCHADBmFPGlOZknkWUVCA+zNsqsJmU6Q+GIG5iKIhsOxQTngeqky//cAbj71Y+EM0VdIH8AuhQi9pT9ZYG/MYv5+rFXPImqStEayZglo61ZzmOTq5+jQNn3VFflfNaTxitg4V3nBezQPTqPPSj+CSd9i3VChBVWizZu5o4sn+yocsesXtsSpEMFxFLXfvTkDhK6Tc4uQ3ngYeMI9uptYH+qjgo/7VN4pHYNUjQAB8RK7iajug9zoy68JjvZjh4KDx3e7NG7hoF4NAdp79oGAGXQtOPHxXEFBYyNYJeTqfb1FAZBeSK+YEvNEI7mGc6M5Pog1uwYL3Q/LK8KKSCciqlJSGxcigVwHKm/jqYNTEaYhPibc3a1VruczJvbnE9qQUXY57QioS/n1Ojl9BxNePftnhR9DQWjyVFFricP4Goecmibo3qKyLCjNnQZyGY3b5poYP9TPnGD7JdirOIJ+RmnUiWvrn+72rOgSeFMe6hH2KiYjLSnBGKyIrh84M443P52cuN0O2vJ+f72ArwXs95gHgpdXR5HVL5Y9KV3FkOoWQRN3gfh5eZKX+FQ/ChEAG5GkkWEUhCkw8CvujDwrZGsnypL9yCni/kYPkaLC4+oR6d4ikI+YFe6/RHDYqNnh3/d5+q4wlr0WihIMuwABsX0VdZU3iFn1ZIb+UFcJ7bEFqwWc1PeCAw50PoWnIBEkN8Qz5bzJv9kUntkWqPFK1+81CNXnUnKldjPrprJGm4Pg0bKp8m9mbZRBDnd9L6E/qZN9ejUgJRP9OiqNgkC2jRX/hkCRBYwp18k8lIwooNWh5XuVfro1FIcAi2KuZNq+6eDBDRD5Ym3H30wbu8S0Djq5Ocf8j5bpNnVZzlCPgkglo8rkteJ/7WMJ3P1vQ+4XHMIg7dGmnVPVgUAbZTI8YtO0p1K2xKkI2ZR49iZFHMzvQ/5HMPJQDTGsFKUw0F9wFKqmpGEUAUpAPhdN2IBs9ZtPKbu33DHsVd5TpzBYRoeQJQGeFXacObiOfwVNrTz0xR+mF4S5qyAgZ3KNDNsiVKLhIgEsMvNwLUbhuu9UNlfSd2ONDN2xlqwvgMC00HINxoNoeVtyJu5OlDMeO1vZ2iR6dR+TcfBXzVPs4f4oMxsViy+1xkOlgz92o9TIREiwbSlqTxzhMbcQMw6ebFxaVk1trIzJ5o+ZVQz60mn53f5DMu+rrWtNmiM/0a4246dzxzp2qWP0bMXveJJQ3WqzluNeuY92sdR8LvgTh1VT/sKO7ZAWXnC0FlwgWdj+EfSbkN2bbyINgtIbQavS0wkg5J958XPB0/X/9DhfSkfMruN/PSdNpObeQesztpyZT1wNaNVIi5eL0X4hLt5FA8LyPL6uPHAcYquTtI1YXosj4sS6s5zRTvEgCYreOvXFBBIS+gjyiGfnCj3U4xq0l2ptkhLU4q0CI+Ba/rZbBI0hfWZX+ecIB97p884oJwCtt1r2WB56Y6s4m0kOLsVkHVF1RlefPapjmFH3Tugh7M5+OFWLM1xeZY5MD+SHmAHNZViR5wCg6WSaGNF99gOke3Spnet2N4p2Nxru0+dacSiBCsCMN0d5li+0seY9cQrrRVHgYWZalk5iQ3ISpu46DIsr8M05T6GqBNdDHNBVqWG+XmSZ5ghTE8Az74HGpW6HSJrHrwD7KKzNYbCtZYuEMSah4cRs5m4nrFmMnkAMUfc1/fuEt1b7TIaRDyvpO7VhgmRiLT7erqVx55i7363KSYXSyfPhHNyLTTNaNjNu3XQst2aSU/hZhQ5pJZCmAy814C7HOeRsKEHY+R3jCh/bJet82fuiBLmXMhOrwgsVAn95hlDtqg73UDuFajbkzPlatmPpyjfN9PxsjcbDxNCvknmuDbB7sPMyCRcepU3YhsTtJFgzA06A52c6kX73KATDk9MKri26FtdJ5e8b7ljWnMnPWuUBGW/t6Tib58sXKTDxxIt7aoU4MmNnNCNyFZL0g/Qrukz+SAC5wGGX3fYiuEhnE0JD8zGup4gKTrqHm2so7U1Cg/NSZqZKiTpwiZSsloVTQblXfxAv8i9d4GpIPLaqpmZ8y6dZwaaFL63nNfPc0DCxlQFXhEfpDFtiNDPSuae/+H6qAQcLBe4UZNpAlGgWLA9xmhyjFUfG5w9H3PnXo4NEVMiNK+f1qZwfuGz6RDU70PJ7KyLPiC+Znc9VFTIiezYJ1+/rP2VqLxNOfcCCdZr3rqI/xBF5RVaUqhM8SZmT1CNNWMMz0fr91QvLVzQ/sfGPxeY0nbc+Xqq1WvHq3Jt1igLecvuVIzAy2z2wk8gCK8HgkZt/MHK2R/aHjhUmXy2fX4ySZK0MN/nMDcwUI6tdloa+XQSQV8k3eFDQaxkrdjLwEoOh9nyyWjtRRVYjNxo4OGkGZ/SwS3FTPMub/hINnazD1AwfFXda1LozxBUOoYLclEOsFrEbJpMe4eEdtgxhv+21dVhnWR6ffNUin7GQ8C2vjpR8ReIFlJ9Nbxw7ifmCZmx/3/+US11Ll+p89rOj/ux8DEii437vdjOOL+qUHl0AAEjk+mNLM98qfL9BqbUwHrg3chKPjFZOQjwKggWixBkpBaZ2i14jegRMHE0SO8dU8AfYHyrgESy0hMhu6sep7JrFZHIvWzW83Wgx8ntAy6TmMM7gS+LtYXM=
*/