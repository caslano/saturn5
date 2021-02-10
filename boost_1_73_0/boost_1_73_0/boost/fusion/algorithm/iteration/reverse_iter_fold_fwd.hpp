/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_iter_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State const
      , F
    >::type
    reverse_iter_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State
      , F
    >::type
    reverse_iter_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State& state, F f);
}}

#endif

/* reverse_iter_fold_fwd.hpp
gEHBilI2CMIUd2vAQnDVcIlT6sHYZPkBRjXoj+UpySIRdOtG2/8DUEsDBAoAAAAIAC1nSlJRuwfj+gQAABgLAAAjAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL3N5bWJvbHMucGxVVAUAAbZIJGCtVu9T20YQ/a6/YmPTjExkC+hMpg2GxiXQeEogg00zTEw0snRC10h3mjvJPyakf3vfnWRsh7R8iRjQaXW7+/a93RPtZ36llT/lwmdiRgVTmdPe/XGX06Ynr8D+BrhwNw7vlfybReX3NwfBPdU/cJrg/kQKn9Ye90GHnvS4J9d6BE2OvlkHwRNpJgaY+eMbx0lglrA4bfidyGKp+F1aknvSoYO9/X3q4naw59GbUHCW0ahkYsrUnUf92Fpep+Fi0dPs2CNWUpj1bKBxyjVpmZTzUDHCOuMRE5rFFGqKmY4Un+KBCypTRgnPGJ1cvr8ZXvzh0TzlUYoYS1mRTmWVxZSGM0aKRYzP6hBFqEqSCbwRO+a6RLyq5FL0kJpRyVSuEcIkDzMtKZyFPAunSBOWlJZloV/5flSpDMj9WEbaj1al99Iyb6q4AYI8XJIsSiolVZp5ZPZ5lMuYJ+YOKmAsqmnGdeqtoSCRiH2pSLMMjWrcONM1ZEajhhnP7DK9
*/