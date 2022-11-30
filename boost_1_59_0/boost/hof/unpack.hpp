/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    unpack.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_H
#define BOOST_HOF_GUARD_UNPACK_H

/// unpack
/// ======
/// 
/// Description
/// -----------
/// 
/// The `unpack` function adaptor takes a sequence and uses the elements of
/// the sequence for the arguments to the function. Multiple sequences can be
/// passed to the function. All elements from each sequence will be passed
/// into the function. 
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     unpack_adaptor<F> unpack(F f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     struct sum
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         int r = unpack(sum())(std::make_tuple(3,2));
///         assert(r == 5);
///     }
/// 
/// References
/// ----------
/// 
/// * [std::apply](http://en.cppreference.com/w/cpp/utility/apply) - C++17 function to unpack a tuple
/// * [`unpack_sequence`](unpack_sequence)
/// 

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/is_unpackable.hpp>
#include <boost/hof/detail/seq.hpp>
#include <boost/hof/capture.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/and.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

namespace detail {

template<class F, class Sequence>
constexpr auto unpack_simple(F&& f, Sequence&& s) BOOST_HOF_RETURNS
(
    detail::unpack_impl(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(Sequence)(s))
)

template<class F, class... Sequences>
constexpr auto unpack_join(F&& f, Sequences&&... s) BOOST_HOF_RETURNS
(
    boost::hof::pack_join(unpack_simple(boost::hof::pack_forward, BOOST_HOF_FORWARD(Sequences)(s))...)(BOOST_HOF_FORWARD(F)(f))
);

}

template<class F>
struct unpack_adaptor : detail::callable_base<F>
{
    typedef unpack_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(unpack_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct unpack_failure
    {
        template<class Failure>
        struct apply
        {
            struct deducer
            {
                template<class... Ts>
                typename Failure::template of<Ts...> operator()(Ts&&...) const;
            };

            template<class T, class=typename std::enable_if<(
                is_unpackable<T>::value
            )>::type>
            static auto deduce(T&& x)
            BOOST_HOF_RETURNS
            (
                boost::hof::detail::unpack_simple(deducer(), BOOST_HOF_FORWARD(T)(x))
            );

            template<class T, class... Ts, class=typename std::enable_if<(
                is_unpackable<T>::value && BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
            )>::type>
            static auto deduce(T&& x, Ts&&... xs) BOOST_HOF_RETURNS
            (
                boost::hof::detail::unpack_join(deducer(), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
            );
#ifdef _MSC_VER
            template<class... Ts>
            struct nop_failure;
            template<class... Ts, class=typename std::enable_if<(
                !BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
            )>::type>
            static as_failure<nop_failure> deduce(Ts&&... xs);
#endif
            template<class... Ts>
            struct of
#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined (_MSC_VER)
            : std::enable_if<true, decltype(apply::deduce(std::declval<Ts>()...))>::type
#else
            : decltype(apply::deduce(std::declval<Ts>()...))
#endif
            {};
        };
    };

    struct failure
    : failure_map<unpack_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(unpack_adaptor);
    template<class T, class=typename std::enable_if<(
        is_unpackable<T>::value
    )>::type>
    constexpr auto operator()(T&& x) const
    BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_simple(BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(x)), BOOST_HOF_FORWARD(T)(x))
    );

    template<class T, class... Ts, class=typename std::enable_if<(
        is_unpackable<T>::value && BOOST_HOF_AND_UNPACK(is_unpackable<Ts>::value)
    )>::type>
    constexpr auto operator()(T&& x, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_join(BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(x)), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(unpack, detail::make<unpack_adaptor>);

}} // namespace boost::hof

#endif

/* unpack.hpp
Qc7oEHBK3c9YTJ+5Q1I3hkkI6Y9aYrOKuw9GzuTtRx/5UncLhcSQetYSgdQ5U69MqX10wIYWUGgtRP9j/nH2mfegcjpWEJsVvgo9Zcu64/u6I4iekyP7yeiQpIloecJP7i7nnsNkdWCa90isMxWbN5qQpe4fk0S7+gKqF5yTeoPjsfLzaeWF9RbzDDdoi1VbTeWFID8VZmeYDpxSBvDVK5GIytujDLdWIyLwM/28FSXv/lrj+O14yoFUjJcl1Pcldcy28SagxbsrgRaP0vtjrU4fi9Ibg4BMjTNXpF+ZR+B3ILuSG0eXc7dJEwNDNDtIUhCzwf1N9Wkt9katknRXpxS08tDLdI/gVNskpImupnrEwmatqeMV82S86qCP91dyOv1ieMtjDGB0DAzGSuL+eazSp7wSzg6mhk2CkRU9oCTCmSQ2AN4RV9CdiTr9BVwm4a8tasgIz2Dla+p8xtZyDjUbBK0B/ttZcI3+FMrfYf7WIXlGUh1fSHvuI4oHRML850iY/xyKw43/U4jipGfJnFt7bht53iXh2VOYUb5GfwbP+Wp92nPPcue85LZpFla9Hpr6JTZVpz2Hx2LGubLRlP7MbxBA1xmflGEEIA8BzoI7E9pzz1OjaL/bEL6V9VQhTRoybqT20bEdto+JhqOQTqm053zkORirYM+gYXltyBhTCLE6g9pzLu5GGO3VU74FrNrhDxlvYXbQWRvSGh3Gq/hQ7obBNzqNXfjwFNKi0E6jW2t0Gc8r2E5+E4yJuobfZar/Ez9FE0aBto6eRWFGf4V+zkdwgY2alglVJPJ2YOZdhdz120DjqsSEvy2knojwWPPT5fPloHH4nOmWLlIJkFXwr3mSkuMTyfPRedaL5LZxOHL1IigTucKMrSZq2XS+gvFhsskxFefa0i6q/KxGCLI7vH3lysmWQuUkHtS1FbCQGIAeiD4ixvRGNKgM+NfafUZ7I7rhESeEkRGb1iTUw+9N8I5ub9OrYl8gM8BjbZnWtYPFIrmxvwO6sCpB1m9DdMvbV+NZan9W/Kgtfszm7VOGNcHTdkdQb8nCKnEWkfWqVf86FvSvtcB+bUh3wcW7kK3bT1H9NULjqkvh62IYXqtIjGjbDXVAK5enXct9sAiZJlG7W+sUAA0QmSkvj7zbwALEEQMRunMR3ymPiZqiPSY0NSamzlfbQpwnlLl+xVzJPsPX8BVzFe2rj3jgPbYPRYlVs0amzpb9b03T5PoKcFQRYmfZW0xiGER2KOLg0VGNxlQqLSIFyBMSsYn2WSPQ9LeD7HVTfwC9nK8kv6Gfxz+x2U6yV1iTqH6Q9RJpT56NntBu3YW3bV46d+vNYZ+efv2617rnhq05+4fPRg9uzYlkllPp4VQ0FclcTMXJJ9IwkuGrLtIfRGtHl9I/KJD9Rmc228MoZh0bVvpRZ0nSx3k0vSdHzWBvyixJP0bxtUX2WfyvAnPNRFd+J23x6BEgv29ta1XeafNTnDl2yHjpwiRqBPoBOV8l2XqLaS+i3No6j9WIbHd8zGaLs9cmxxkTRw9eu3erWKYkW94iT02wMjaLaiIrnrRFj7TNZEl9SUZMFKWKouWR09gxzo8MltNnYpa8/spoX2cxykfeYFeytQJbKrJaOxsL6cDqBklvF+o1DmfN4EHsVpCbPNu4drX2sKDV4ELM1UL21PRJ6yzHl86rEF646thN3r7lZIJll556hVxkvhP/sxBE71Yh9YJFL0M+1U1z8OT3uD+9fOxPaY5I3L2Qo7fnjGxjkhIn0LBR3Ghle9QzYosjNq/7yshdJepRsRyeW0dQfhMdCl8h9c6Wem+/7rOXUjRhpw9e9xk6+IpgUAV5ifqpHB3CiD0dv05eRyIfNFUDzpo2Qp3fsIxPetN0RuaQy9ekDGOAstLTlRy5Opsa6xum8G1+VgxvAKFib8tmSxwwt9oK8TxBgaCx+bzpQhnooioyo7UjvHXUsgH2pvGByd9czC9R+Lug90j0RIiNdbjUC0l0AZxBjhAdqnHZ7wk1oybpCdMUI3MQD4ZTsLkqRIzjSHoCFGAS1sMiOTJt0RohPLMctaROtnyKuUmRAKez5Wb8VuQFwm/87KzZWSn6VDqKAUZekrU1grZSZDV2ddBOu9c55a1nz9EOdn95B1d5T0RH229X7mhBB54uvdGCq/8P0AqGhUD3oLna1dBl9kb8rM12YKqWtWiF3GxzeFatgO2ecAWO+s0+Z/QgzNNbeqUTtZzdFCwJ9dgpBgLLUg63utFP8ivxMzapd8FM9gpU/Ueq+sJ1p8iy+z4cgrIH9trDIjsZH8dyt3yp1J3oLloZgdpg7Q/AjiTro31TynEV3LlL1UE5enBjN/YC36FgHG58ih6MXEtOONtNiUit8eDkRBPJCaVgqo60P6pc3dLAKgS1L0tfJsYNG2AYIGH3IMXatghxyyNZvApELbhqFyB6+YdQ2iUGTAuA76noBXsRPciORa7SAxbtchzGIZztYZqSKbPNnceaJ6olitRyrf4Iqu4DrfqGIZ6Z/GbXUlCUO7BigMJsGKqBCqkm2yGsK8kbPREphK+/EL4+KayXYz19Y5P1zJusA+eTFsGUWvgX/zL7Qf7n7g7pjbnGQagNblzGEFZb7gQ6a9dtyLpDYpW23on80nqH8WterMj4GRarLgQC6se38cA36wu19Qu09QubtPWCdgtfYBQfIshOAtqElQ6EQvs0dczSOd07BN/rh3H0WWmPDnWWqGesm+8CvszRF9BX/0huK0jb+2WxmUCkY+xNP0sYXz9vMpMR+3J1QIye2PguEOcJrUKo5yEIiLgqFoCMwvVAgNAC9AQ/IUy3fRDb7meAfnShT1/XJauP2i3BUORB1HbxHtHbUUnDtP9A5fegwDJD/lofMGLPn0t34OuLyeG2qJ6ztb9Fxbj2ixNBkpMK/9N5EwKGUYjm0YqFtK9jM9xoAyTVT/EWOqHPhzh6vdpptwTYvLoQoOtyF2ngOPVOFwDGag8CxnUAGDEwQcBoPp0GjF5WXhTt0zuLsFTlxaWK0qXCclNDPfDXpggf7uDZ9GdvKhSjtI8E+XolEKQFzKL7PSF2J/KXuiNLeTtyB4p7ycW2LxQA2mLx2TQ1ehnJiH2YeMvZqRPghNGicdpUAO1PK7zDix1sMdqjy3XsIRnhgG23sifIvJFvssUuxAmPuQApL8OhD5aK5zN4XAa5Nmh8ezQ9fLJ7qPOxAe8QYIT96fSmiMtEGC5/Xa33oL5sgfH9M+m+2bTFQppsmTL/S2nSSdoBe2Ri1lfDfAZzQ7XG/WPpVufRpE/MOJQIqQNVQeMeXqKp/mJ9F6DqKoXBInL5q1XKWqVLq8zVKhdolUVa5cXuOV8ldqKUuwgT11qM53kYg6bEV9Rn/b+pDwiIruMIGFDNCtaUIT2F3ggDIb7e1Qsye6dzGsXY0+1fo0A7N7AfkMM/2Bdy3pt64eO2cKGs78Ro1/GUrLV3yxRvh8pextq7YZ675byzkOFQ+6yQlWTd5GOQ/YF8EAbwFML4EHZSXpKg12YNWeyul7d8OSDSg32vkh/w58U93BuUKITYwmhK3yC0BdncQF2tMV0CDrJR0GxqH0Z61cpFIuXtNeEFLMUygeH9eCbGyEUNQTFv76PW0291ncGmOqxAiZYLk6/BO5F9U4KZcPoVYAbuXjpmCLL5IaaQnxZg0gZKPTMtUg/qA6p948NGEQqn3MkcPMsw4Ves1DO7u4+f7F8DD7ndfRHUusuXduVKu4qsebvVhMD2YwFL8nKescYq7crQVwl5u9k+yJidER1qezAND+cox9qvD2cvURPu6NDGkaQPvuEyoWO6Eu9ohHWcXKXEO+vwxgdvedkwxlo7hBjdjAfd8j47S145P/8FqXEcc5MqUeSvZFGJjt4XC9DPOd19Wl44qwKVoZLTysnUq4pUAd1qXKjUqki4v4B7dbZzWq6gQQPYP7+RyFhNmbi95HwQ9lTagvBMeKa+XRQwrowdIBGg+dNdgwL3du8JEU7O50T32gzubNR4iOsaUszwEDKExipMmcckQEHRI0iQdip6ucAOtS1AfyRnLW0Sy2WV7rzXFlUKnTaU04hsjWA7qlXatTXiUvj8QGq8CT1C6hVo2s6FeoXAhtvmozyQv7/GzUR6v+Oi90VtjX3q+4AQ9GqBJXDS8JTRSoxN23L2iD3vVKX2iJ09Iobv1Fd/PYONpb+nP5/15w0oiQ7p7/P6h8dsA1pxvlYMxJ/tVN7r2iOiBgUeyVXj7prIIdspSCD/z1V0viIvRUlb5NkpNkgwv13nXlpit6bZxLH2G5mOcbTjH9h2HFr+Dfn00Ulvtcph6dn4Vt0N2cmrSFVwGxZlrzw01BH/0KbslZ7t37oNs9nvHBgJbLQTTxJ+lMMNhsbcndOqo6ObjwME+p1TpOBvdhZXjYzwvMrwnMqwqEfpu87Wo/iVk9l6FL9uEugR2MAMJ2clseQBn1GSg7Gv7bbBgF8rdxlefJwLT7VaudO4Hp5sg6hLVi5A2blUVjbDMpc7NLh/2a0OuJdH/oMgJqClYvUMGozYpcfXpjAMAN4DMbUOSTJYdtSRrt3mstvdtRs7iAyvvoZ37H5kCraRvYAJb+5CfeCyjLxMACGHoRfbss1pKGrProHGo6mN7yedLOjS6lxAQGll6E9DWw70g0OrcxC/sdtNssXIL7GX0EMr72EzNxb5Cn88pI8UokMnF5cNS71P0QeZG0VtRDssOACEL7gw6Z3TaG8hA+MA/036ZTCv2K4k2r1slWh7RznXmb0UZg0W7J+SaLOCSkmi0oPfbrPM2yD5pl/WfALjUS374+9Pix7UnyzAqFNtPvYctXXu9Ht0Xlcs5gHNowy238EetOclFwGN0iEtVY9iGx82cZrz4oY6ZpDoBojSJYCrxKaL6FKOz5R4+Os+2GnaVvRbqW19lsJq/9SG/38+Df//EqABy/AZrlz6BonJ8z5uH87lZ33TMbbSjgXmsZ0Tz6Hsym4peo7kLChok7ZXb9KfQE+smij1BtuRrXs9oFOYhzZpm7TrCg19ypO+7WdYoET70QGu//hdvUKklzroJf0p9JvbNvNLr3SUaCGBlYfhdrpPr871S73VYq1ebvfp/4Qj83v72CvGh8jJBaFQdQ7krfRJveXZfj1YWOsjlRwo0YclqtdpTz8/HWPJbKCgiD/6DT6Uh9WXc7V/J9WYf3+V/v8A5+zff4z/n9gxnesv1GuL6EARCSHtzkvPFtP6K1zmrPTs4fSvMwRfjrSAwpdplKjRE/R6n7F6jKK1OJXnfsB5LzcU3omthm/i/d6nUZZGiUY+lO8awFGj6wDub0Agzw0Jk/+fw+IP9bmCtsWisrf1G6xSHo0LkXvVIQFIG9YqREdD7DF5sIiHSpkPsNgn2NCgR6yj9SixWYtgubVPZw8KtmNKbkd2NYDl6OjGvyQBdjsaAFkqOU2t01lA1oRYavElIkPab2yNyDLQhtE7qgyyt5DvxF3bls9SGLgC7eIQz5TtxEUSheUWzmH7jWKOBR3D4xXKWMsbX81w+clMjxYjUNVvmVGG9Pzb69aSf1bXEgzLZJ9yor8vTef6gr61rpBxthJLiFNKPM+DmaHaQhlWI4eM16kQ4ohcXPNOXPN4lKicYsuAgP8tWyZqAeRYnJpXe0jQHnJoD7lYrdh2FbNqFlYiAKnOStAqUY271H57deRj09LNpbwWvobNUl4HXKYtc7ddxs6yAVicCZT2DMg1kZNUUFn0mBCeC/N3oU2GZXI95JYrp1u+SEu60pOO8odKVLn0niDkkQ3UHTQML76GXqjaZqt9svpKSnWf01aKap9rSeSLaKqtBpg0jj/he1yGdUq9YhHJLeA+/Vkc4auhKlbllG0JXESz+CJSbm7NYkvtmvCvZcPjasJVE3lJvWBhLXZtrdC51Iu05HIEo9j+tmiKVFtms8F2J60vew+7Sbm5PQdIIFXQVvQIjx6nEgjd+4WKSpQuEIj/ao4bkMXmrB0Y6jDpY36R7eEEqXomt2Mm61fHCjqydhRgbtZd6Je643o0bL8H6FP1THaHYIsnr1TPuDumqX3ZSVk9c3vHCbXv9mQmJ2FjwPt2D4XNp8QU+aGbKC4P7usCNsBpavYskdTsB+KrtH5EdNXiGC2TRRr8CoyAQyEUyzJCgOz+2cb1dtiY7QxbLgT8xvds3Jm+rHzGDvNwKkiUxSo3YfxoDG0Sq/wu3EbzLOQCJd/bp45btAa7ab3hRt8rkVy2PANj2UPPyCev3xbn8MGwoJiEe9A3XXu5lkjdmyALfiL8B3VuWMRBgYTl8KrRclmM4KpfaJqjFPj8wB+eJkmkjOr0mazNPnzGRjFUmA/9vw2P2z5jdRlAevUjaVWbF/cZvVbCGInhsbwRaNo2jiGMtA48LIsVt6NSKbqfUc8VSU8/Qzfu9uDwOdt76p/72Lnf49c9SsrW4xYpauVgAebl0e4htL2SoaImdY/YiFNRJnO1lVjlYzhrr0NPUX0eIefRV1EH4EjnrXpYcesht/rXPvXDPthse/MSefvzBqNDHbByUO/59GFlz2aBnU3OY+OwQAbd6sd9ydn4tdZmsISxlUvI2WG9VMGVodcg2ZSuhJ2ECt4FLuIA/L6tfLbZyuJAapXRuQV0MSnjItWWI/F0IO+QVodfIh9oKD9bblfPFLGI2JH1Iq3oTE6QIXZZGr55aTgf/tjw8NnReBG8H56hC7fhSu5z5/UnZ+ilt2Fn4NaaF4fmoIS6XBYv0eNRj5OzMIBIKDHiNlGPkXPMYIj2Y4mdhfcI6rigC3tg5ig2n/R4Ka4LEYE0i5P/KHea3i4SyNeDW+rGWJTM52GrPKwolz2am3cIpgPPrslKJoLeeQbY0SRRKxSiDGrbxt5h38lQjpIMu5tMhzo8rNWTd5o9lpvXgcFOhWgq/BbwLrXGbyyTgTA84R3kDosk9Mg7on1JchYtQ7Q5zaLAF0BfJlm9oByOiDgWy0T9rC6XN3HWbOFNslGGXgEPVGuUp1uCVnC29nj3dri4/RryeEvsAlsiAERFRu8EPpqusnJ5KDs00k33SeomzwcryDVgPsw7jymWLz3+Pe4bo/6iEEGsfHWANaK4x/jePCTKfd6UP6B1rtY6V2qd9xntmBisqoUkn/HwPDxxq9I6K7XOUq1zBStfAO+tovdy8a0FWmeB1rnQKKe3PPhWrrGI3vJonW6t06V14jkNvHUdvWXHt0Rj7jwcf5HWaTdP8+S00hKTMaj8EiHgPaIcCrINYttNerlHAWxyXFt5PjKdzdcK2CMCzP8jAtzN1zYIal+BGheXRt7Gc11W4WA1YoBdDUSBgO97+6JH2hap8XxOX0cPsisimdrq3RlJAf4Lo8UfyWE5elD6YWL8lS1/fn9Lokh0FbCr1XhBkZJoOXBpCE71OAkW8skmMoiR6sgY8dznv8ZIJ6yAFDa1VlnaVWddm4FxkAqC8Kkqjc+L0mRAvkkG4AG9tGt5xhRbHDFI+pv4JUmDDygLKdpP5eqs2hwsjYedI94+bwpylwmmvz5X28b0fllul3Y5ivHwpgQAz369cHP8Y8F2AUoDkwuzXS103s4G9cJaSFbPWPT2Ww9oC7UNYudl+qMplqrRKwuQkLew
*/