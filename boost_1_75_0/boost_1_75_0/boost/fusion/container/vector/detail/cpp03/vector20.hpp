/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR20_05052005_0205)
#define FUSION_VECTOR20_05052005_0205

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector20_fwd.hpp>
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
#include <boost/mpl/vector/vector20.hpp>
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
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector20.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector20.hpp")
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
// expand vector11 to vector20
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (11, 20)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector20.hpp
J3cA5ud6cbyPwhEJgqCFk4Zq8tVidGFGF7q+DrHH2rvk2SIkq3MCxB54+h7c6o/eQ1vaTz97LeLnf/Sz8yLc6Odat6u+aGbdht/a5LpVGdZtXR1ft1v3ha/bxTuaWLev6y9g3bZ999+u27+z/ot1K7jl/3rd1ndubt1+8uDKfOOhhfqcfs65l37uop/T7sV1y5Rbs1l77K9WpqyU3S7ZlpnWytNeHhSV5ozyJMiDbGlOm8cmD4pLc8a52zjV7S5vlc3pPW2edRBj2O5MqdoZHjOC0UZLn89aGWJEQcwIl3eyYhJRokaPtWJcALeNgrmlfCXJuUWkVfHAz0MY+bcGIyXI3sPDQLUfK9hdomZ0CIlxiGGgnuwkAkliIB8MA8X5kAhHyjr4yEGtgxnGUF9JaMyG1t7NJ0OB24rv5X9c0MX04xiTeQsnce1Y8y55dInRs2Qrfjvpnomhw1z+3Do0E9A18C3FVhNhz3McvVI5eqXiOCkYA1VUzuXeVA1BUg1og8NvReHJ8G0wqlwtaYnRNqH/R8eEBLBIaoRJmIB5eke6QY1MFjN+T0Qckjg/XzmbnitmNxkfBNbadcC41pBhJWSt7xjTeK2Hl6iOSWOAmURrq9tvzIWs7pYOjVfX0CeN7qzbr3Uqj+Iks07VQKdqoLHPR7NO1Rs6ddJFCGgv6wkEhr3MMHGxPUPNyyNb7wT81NUkdiYPbMLD0ppp
*/