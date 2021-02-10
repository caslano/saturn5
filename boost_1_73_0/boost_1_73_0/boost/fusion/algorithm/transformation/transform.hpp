/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TRANSFORM_07052005_1057)
#define FUSION_TRANSFORM_07052005_1057

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename Sequence1, typename Sequence2, typename F = void_>
        struct transform
        {
            typedef transform_view<Sequence1, Sequence2, F> type;
        };

        template <typename Sequence, typename F>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct transform<Sequence, F, void_>
#else
        struct transform<Sequence, F>
#endif
        {
            typedef transform_view<Sequence, F> type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::transform<Sequence const, F>::type
    transform(Sequence const& seq, F f)
    {
        return transform_view<Sequence const, F>(seq, f);
    }

    template <typename Sequence1, typename Sequence2, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::transform<Sequence1 const, Sequence2 const, F>::type
    transform(Sequence1 const& seq1, Sequence2 const& seq2, F f)
    {
        return transform_view<Sequence1 const, Sequence2 const, F>(seq1, seq2, f);
    }
}}

#endif


/* transform.hpp
xfPgMVC2o/bilOyi9OioGWd1XwYdiVQUKlRCl7vaAqhMd8QGxhvOSpyrleTqrXWuse6J3nBcrL60q6fYrcXf4VCLKyV9fW52r/yRV+gLJ0S7N8Mj01zjCu5BSd2Iw71MAV++jfZwkGVlVC2l2w1k9nizXtIxTePNwcKtkQQqtjL9A/F07yYisOZasJpX36290IMIRTAEF0hrfhuuD9GZE+wV0jKWYFPNaxigAzjnK459bVLW0K81yP9x6pKu1Mwls0DgVK2w2jXv2HTUUwY9SeshVoIyYJIapHT0JwboS7CQ77Qr23t1/F9qIwSn37oJdTle90KN/OEAEnhpd6cl3aXdAEl5XlUTerqjM9PREPGcao9rdhJeppESkC8UpaRHjqGu6Oq16cqugS5PRqY7ScEpGXgwV8n7zsR1BxMP4DhCKLj7rmQUKlC1BLXfmkGcc/yUlFBDcthc/jV0U5O0gHSkArhOBfQ7q69TjzTcA3ve9eOa2l9HZSvD7c+vOMixjBTRqTsyYzMVuvgG0H4/Kh0QOxfHqsqxOvw7VhL5GxbhdtnyKOMz+q5EYGEdpdXOLkw/6+BnTe6ZBPly2aVdG4Hvq2hImkuw9CqnedW3nhen5se0eIuzs8K7JyeFRr8+J10i9+kppcRsTFfy
*/