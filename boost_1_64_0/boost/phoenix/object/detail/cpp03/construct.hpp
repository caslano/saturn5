
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/construct.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                                \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                            \
    <boost/phoenix/object/detail/cpp03/construct.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

    template <typename T, BOOST_PHOENIX_typename_A>
    inline
    typename expression::construct<detail::target<T>, BOOST_PHOENIX_A>::type const
    construct(BOOST_PHOENIX_A_const_ref_a)
    {
        return
            expression::
                construct<detail::target<T>, BOOST_PHOENIX_A>::
                    make(detail::target<T>(), BOOST_PHOENIX_a);
    }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* construct.hpp
Dmj5CbVGaFte4zL26nVF5DYb2maqp913r2iYcQ0eolq5qFoR9KtSsGwfloJlO1QXWcFyGytY4jjuxtb6jXYFy3ZWsNyG6vltI/7G8WdRssyOJZwWzQDkEEuSZwNMmlG3lG7z3aYa3urMVsOtt0nbCrO65V7McjmHsxKPudhuMqlbno+wTDlClzK2WYTtaoPtIhu2dylsLsRIk5Y7MgAFza12DQd7VlhB81qNCmrdTZ0WotZqfIWCrxWnm7WGZugoaj17B8hMo9bQvJC9fHm6otn6b+qenBsiXU2cxrhQ62pepXQ1D7Gu5hqTub/YWuwnPi+ZmwnY9I3Q1xN1UPQgsZn23Jl5k0kcCRTYtDZNkWwqGGzCMlals8uZ22//TTfUL5xntDl/p7WV19YbrUqbZnZ8pmo0kznYyzoDWquSaQZ9x+/IFjtNR7Z10I7sA58zHVmpc7gdWX9YdWS3UEd2S9i68VbTkd1Sa62SL8K5jzqsGbDDKVM2sX4AlUq8i1fNwfvk2Ds0Px81BL5gI7CTkQUzyzTY/oIBM5LbFcxi5tbs841epMyp96wZoBcpqA4NmuI7BRsd7lGm9a0LtV7kZSLr2fjOE7KeE78Tv/+dnzm/+6Z3mPtxsJLi5aMvfaPbLjLiKySNyOinNTkiow8xaB9m9UlWaENP3VEg1nYH2z2Fb2MQE7Cv45NtCYwCchyRxU5pZiVfJLMC3gUrlxFOL/C5L4BGUnd2KtTtf8BTlOg9OX5hduoNP18AMw8lz3exTzAw6gdNfyV5+Mrpcri+u5bpc8M4dv/4DWwi3WdSt6VHoqSWg0V5lgN4pKUPNuzWh71fxKvvpqGYgWG2LbYAK3AnlvP1R93QDTVBtSC7ziQJb9AiKTBkD9JOhn25m8Le2GnMn9HErxgpQbzsFJatGgPBPKzJrSpkg48+NhnnWznPEOgmP2+SKWfL7z5OQJRCfW716aOCvlsMcBNfFnrLqnzzQ75V0yMTnNkhpU0GgQtuMuNiXI/kc/l8wQTbJs7cxGFv3Mv3jgbIGE4AhDUWsvmRABKllMLeslrf/PrAKr/dg8N7K2BdL/VTVhvtH18ObiEZPh/6BvtppkCZlKa75qi7pleGeswZ7rtRGa+wMjMjc3UOIiSH1JloZpDgnpDVjx+Z1lu9kHPfm6wN5AgFZuZnCgKGo+5Qb1z0iAsWyTIKaUVJbFtvQWSbtS9TNTdxyEt6aL6KGhQT4a/3pSciTbH96RazrVTTestCVAchJhm8+Iy06h830fo//cvqP76d9RWpO2FbwOhklD70SjoF767pWz92DStqu0N9LQHx8j8wtvkJiCpdmR8dx97qDrb/+na7/Jy2w5ovQcENpqByKfypdTaeGllq6luMXHdIfRu/0TSaxzz5p7paDhURElYPYYM5FWvJZ/n0VkbMNr3eQiHsTflo6oVjfijYcGokbtLz29K76zMmvXer9Diyw5wCrNRTwQjX4+kLdF9+Sf6pxGY+GrWL3o7GUa38mXYDq/jRDHqN0zaDNkSUZok4QGNDG+fmeuTmA5ztXu4Q2y5hbQTKfVY1/KPn8iZiTtqrTyEeNBNgkjOjSLmOcDP33CnyUJxkjBX1kKnmtOfJ+e1ZhH0Xz+f8C/r0TEJZEywDJsIX0QYXFjlJTehyfPJyIEyfbUuZRHqX4tryU7M6V5oPJZ82fNiHUIF1xM7N6gLFzrLp8DQAnFV+lopjpsOxBpLQ3E7FGYcGCuEBCdIHLyZXjHnEFFasJZ9rRyZ20ZcDhrneNJC0xpQh7UwmLcKw0OL5CONmW13N5MlD+Iv3AxdrA3B4a4reFSmiY4WvlTmRbOMQjkMR6Av0VTQRNcvfvqc=
*/