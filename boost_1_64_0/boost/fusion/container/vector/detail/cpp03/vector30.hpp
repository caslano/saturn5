/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR30_05052005_0206)
#define FUSION_VECTOR30_05052005_0206

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector30_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/container/vector/detail/at_impl.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/container/vector/detail/end_impl.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/vector30.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector30.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector30.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

#define FUSION_HASH #
// expand vector21 to vector30
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (21, 30)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector30.hpp
sQu2wW7YEaMln544EPtgIsaqcTzy2cYbJR+Jp1H70lfsjzdgPK5kASUGZs9bIVeKgyFWRmtPvdOPfjID6WPfipEYL/3rzxh4dX3sx9RAP/u0lw6or31dP/t+97H/XfrXDxti6GPfrH99z771q+1T31d/+mGkTUO/v/70/elLf8/y62ukP/1r3Ze+P/3oH+czd4EUejx4nzk4BafgFJyCU81M39P1P42bv/v1vxIDsIQf0RWu639Hsd1eWOTMylRWXpyX5Y4BWMr/H3P9f25BrjM3PS93kbaE3B/4ItyijnO/Sa65G2JDrI9fRJDHbHc/AuPGjlCG1u6hDnAvl8DZlMifca+1dsTGtvAyTr+0u5Q227PNx7kPre093niZlfm5Whlz3ZuolNWWnZc+2+HH9XlVu+DRt7ja73P/xJhvmUm+95BvtI98XX8GMN65j3zZed7jna8m32Qf+Sq3NPy5H2Ger9bud4lJvmvI1+4j32JHkS2TRu/fJe+qbb7oY5vLzfN2j49bA/lWje/flBRCuoV0L/nuM8nXcRXH1ijJV99fAteqzHOtyVD/YddJX2JyDyqcdD9lOWFWlqusf315mrrLI+Nbq2sztEd9Wso0khRBGkJ6gDJV6sokRUrPzKz+fpz0M+I1tn0c85a7+xlRIprU/jJaN3XVlTLPsN/a1fM+Xtbx/uQ5WrlMDlW/66m7q57srMJ4vByo572P1iufEe98Hd81X9/7R7tnGilt9SfL+Wm83Lss9yqPw5bNV4Ijp/p7vHJ+lmMll7cb84yWdvGDpO/ZfviQ8oa53nkqAWT+fk8ka2PtF2Sr7aU9791KvxEenyNlXjuP8dcbGb5nctXj7AZXHvPz5DOgfj8xTwb01+4bF7iXVc42Ds9zRzu5HP1aPhuXSJuUc1aeeT24vjT9qAulf9Tp+YY+aKkbfX8ySkUEXj/K9px11y9f4p7fw9SZ6fe1cd+/LNv8AkmZ8RypSQvOUfne21xcoGy1f8eb1jdOel6e2b6TcnVXz1/G81Q7uXn/AIWw4lp8lD8qCrRy2dOLHAztT9v06vsBNvZJq7zHJn3SSpl4xmGX5VDmFRQ67BlqH78PW9X3ZsySZUvVz3N60WyZF21y3CaqedtlbHu1LHQYXMRins9inPn8KM20yG+pfoXGfoVmyOub5fUaeU0ZXa9/77F8U7v6/4Y+OXbeaN4nR4X92vbJUfWZqy/j57eW812EnO+i57nylx/bcr4ryspSntX40/+VfhuPSB6Da5EPxuNjFDTNnYf2defH87KqY7vUdSxkOgplXqLJd2CyyXdgqsd3oNSZfA6clMVY9k0N3Zm/IvvnMGmL8gaHvux8E2RWfx6SMnmVM9qQv/dntZHhHGL3ODcXZHDB5DrGIhzGY3KnvG4ZZux/OryRu1B7ZJt2kKzUSaXnNvHt5s++lm0wfL8p+Xdxsj6pb32drpT8J0v+40k9eO8JpyH/oiw/+gyTvD3OY1peB25yLxxZm3JgW9xK5SYU6/NSru382X/XNQ5Z4P4eoSc4vkrc3y0fzzf2vZ1s/N0hx53Xfpfzofp9KOdD/Xe2+fmsOfNi1HmUnfMhZ/msTFk+zmRf9HaXkc+D+3W9Beq+MRwbp+RX1Qz5LTIFt1n5o0RXX+5vXz587jrLqea7t9ZCY/3YTbaxxKR+Sr3qx/zzm6Cd29OdOZ79l5Orqxd1i7ZvPK4hEk3OE3H6c4zHMXWusdZ3XDRuxR0sW7FQX0dFxQXy2SlBk2loY+m7LM1Vzlqyzd51U2ZSN+UmdbPJ5DdKgsnvkUR9HUh/YqdZ1xkKtILXv1vEdujqa6yrHly1qPa31U/qIrWJ9v3RRL4/nmA=
*/