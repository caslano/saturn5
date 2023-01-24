/*!
@file
Forward declares `boost::hana::cycle`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CYCLE_HPP
#define BOOST_HANA_FWD_CYCLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Combine a monadic structure with itself `n` times.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a non-negative number `n`,
    //! `cycle` returns a new monadic structure which is the result of
    //! combining `xs` with itself `n` times using the `concat` operation.
    //! In other words,
    //! @code
    //!     cycle(xs, n) == concat(xs, concat(xs, ... concat(xs, xs)))
    //!                                       // ^^^^^ n times total
    //! @endcode
    //!
    //! Also note that since `concat` is required to be associative, we
    //! could also have written
    //! @code
    //!     cycle(xs, n) == concat(concat(... concat(xs, xs), xs), xs)
    //!                               // ^^^^^ n times total
    //! @endcode
    //!
    //! If `n` is zero, then the identity of `concat`, `empty`, is returned.
    //! In the case of sequences, this boils down to returning a sequence
    //! containing `n` copies of itself; for other models it might differ.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an `IntegralConstant` `C` and a `MonadPlus` `M`, the signature is
    //! @f$ \mathrm{cycle} : M(T) \times C \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure to combine with itself a certain number of times.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of times to
    //! combine the monadic structure with itself. If `n` is zero, `cycle`
    //! returns `empty`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/cycle.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto cycle = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct cycle_impl : cycle_impl<M, when<true>> { };

    struct cycle_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr cycle_t cycle{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CYCLE_HPP

/* cycle.hpp
gmdsEZplQteo6Kmcv44ngKiDHMxQXeXFJqHJoOfUrGPktVnyWlsixxq84FmHeeoDBwDgfH2VNC/T3oHF3wbFk/kGoQKdkAi8wilYbqZdBrJ4vS4gGerb+yE9Q79QsGy6hi3MdCyElbFSj3gsDdXQsa/yzzE3DAKKwSwId+Rkrek9LifLxXOFlzQdyODqHA+9lx2L5LV5pcIuPh/zujPZXTZWAtN40bjDgcliJ+jmyFzZxZxd3kX5aILhs85kZZLEyL7L8dGaNP+j7KMiEL7FiASzHO6mpEXmaCUtlMPndAq8lymIowvd9ypmwuL7yNN4cwqGj99WoWa4QWy53q7teTEjMxI5gEZT0PUkqUzuIJbNQhe/UjhKH0Ok8F56yfZrpHAdGisj11O+dFoHZnfAYlGAqQ3jkzZRniPDTwEY+kiMCh2UY2PlbXXkamovPaP0xPLc6DSHHEzdjuZt2i4DltVBNljUTvM1cLrifhUqbhEDZgd5dGAmSc/mGWBhLc01SHeZ2TwLu9smzbVI0ArzMtndWdLcTOmuLDZviDR3CJuXLc3NZvNGSnNHsnljpbljI3PHu/xyZN54l8cjhC70iuHvEwlNxKucEPXEBOFrS8R2Ng7u6Pyn2D0U6+lAz/U0UlWQC0kqMPNrFNJ92S7LHyCGItwjbcEfvqSLaJeu0C42MRJ+knaOFSrNJiqFuuXAdSIG1udYgnAt71F2
*/