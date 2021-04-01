/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_ITER_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct iter_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State const
      , F
    >::type
    iter_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State const
      , F
    >::type
    iter_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq
      , State
      , F
    >::type
    iter_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::iter_fold<
        Seq const
      , State
      , F
    >::type
    iter_fold(Seq const& seq, State& state, F f);
}}

#endif

/* iter_fold_fwd.hpp
wn04C/5KZF6co4hW4BLaLojHi2YjIICMNeZ8ogjMrhv/Aub4xZD/ff8nHDgWt/fTU7yZMPwBuuqROhY1S9MAtXJu9WDFCqD4tBzoVlUq2NI4z3xH7JABcSFY7C9XvIH/s7wef+61d9JyV3078C3Si+BqhV4isa6sPO43IfH37H6vmLKoj20VItB6fEtIaZLLIyrcGBAIjVPjc5jnaVnjWeVT34JP2hMO/SzTMxo7Y7VJ4fzVMvIwozYnIi/ErFGpJts4wg9gB6poxU52XFKqYYnLjBUSiF2QbTQglhqi08p1vZz7yKjjcnRyMPjDKsCuq4OWyiS1jpnt6/Bp4ZFemnpyRcH9wOzLnhFF8y7hOcZVs60N2q6rAMbOx44KgfUna6d+qOazAyZNYU4mmu06T55saiKZLS6pRfaS1UP+1IMVu9WipIwWOz7tFjiOiBGh5v4slwgFYlHb3A17i3am4bVcEqoynjADkYxQgOFbGC36tLdfjgZeZd9JkUbzU8WD0vKVpuhXIPELGD48icyiQLiTJDoIeucQCOSKR58bQee/95FDKUZCnopFFg==
*/