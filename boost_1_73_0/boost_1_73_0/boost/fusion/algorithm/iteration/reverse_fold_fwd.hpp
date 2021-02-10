/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State
      , F
    >::type
    reverse_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State
      , F
    >::type
    reverse_fold(Seq const& seq, State& state, F f);
}}

#endif

/* reverse_fold_fwd.hpp
9A8TeEb/nB1ltGgDzuhRTJR5SrLlQjJ+5B9NrRana4Mwjf1jNcpnNJEPZMDsO7xbcp6hYvLDiCpGYwpHsaLmz8aNYexzh2OYuBKrYO5aGonR4Jg/JGTHocP7N5ziT9loFO1SFIPCMO6u2ugYK9lyRJq9RwCLqZ08sGAdDFnqCbpk5VvrTUJ3BlTZ8FJNqwTghZc+MLa+Cns6RjXoF6WKWbe683KDjsr2LOQPJ5hzsceXMfdRx3HMfcJDnPuMYeyVUx2LueWnY9qnHhWs4EsN8h8jTJw4oNhTjA0R9SOZdk9iaw0y/PZ3ns9CClCa6nsEqI34PQLU5v0eAWpTXRbgvllgZ5qMAnVBGJsBsyuYoh+hx7Qd1n2zXHl3JwjrnpPpXvJSPvN8h6lu5434sSSj7BFnwoUhqsjTVNNnZ145JNhIPDzFpnRVhGmyFKwE5UneDiYYer3CuQqSzEfaI99xwNqt8ioxvlVFB4T3iw/p7X0SHtpwTfqmsods8jDOUUNtLOY0btFAyJ7tMN2zh6X5K99ttNUvSzLMxYZy7G6QZi+HH0wtdTQURe7vkNu9nT/uMorx3XgE45viYqVgvHBEWl3ZS5ttlMFgztgrxCE2LGCxqXZlsr2EHdy1ghKUneAN1zD1GFNiitdRw2Rf
*/