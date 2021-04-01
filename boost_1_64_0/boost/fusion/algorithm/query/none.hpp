/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NONE_07062005_1128)
#define BOOST_FUSION_NONE_07062005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct none
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    none(Sequence const& seq, F f)
    {
        return !fusion::any(seq, f);
    }
}}

#endif


/* none.hpp
zFnbQFWk18rejo6HHfqnnFRRHAcsQ4tHFJQW6M2cTh7275NFJf8FN5V57RnjutkLYpZ+dd3E8PruNrdMpYscPxcwF2dPyAFW4Y04q1s6o475QLj5mnnsBbXQNLoh/g7EMuqExxoXXa3C3Jax7tuTWelyhQLdCScM8mXZuM8IZiZ2ugeIZj85qgvWn3aUqn7WU5ogAJv66V5C7tilVtoyxMt+YVRgoRNSg/O51Ws2If8a55JHYbeV0FNvbe7zdDh6EdigMUd6kMFMqwJSpaWW6SnIi1D1DPawjOFn843dtcz0LOkpHe8+0xcKkD3wszuqjKClaydRxmNni05xIAPpJyJRrYuVE3/8UmCYnUBLQ+GyY74SlGOpu5hfwS7JDYnkdcjbQ/1J4rCDYPFLQxJS/sblZ7Rz93xXyOKKPssy9jFVmNPMwtdSorDFKyCpTW5qq8v+eiQDbNP6Sdbegz8nMh6fne4lRbHfJoKewujppsSa18ANnDJCxK5fajhY804eict4nGMfXmZxK857+pG43u74HREt0opazsd8Vt/kVfYiYuMKe2QEtF5KAQ==
*/