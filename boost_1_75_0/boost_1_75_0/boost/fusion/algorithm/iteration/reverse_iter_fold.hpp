/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/reverse_iter_fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#define BOOST_FUSION_REVERSE_FOLD
#define BOOST_FUSION_ITER_FOLD

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/reverse_iter_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/reverse_iter_fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef BOOST_FUSION_REVERSE_FOLD
#undef BOOST_FUSION_ITER_FOLD

#endif

/* reverse_iter_fold.hpp
0kYMOQ2GHLkbrultxJY5vY3YcnBvDVue21vDln16a9iyS28NWyb21rClqbcRWx7uFXKgI6r8GLQ8bJX7/wA0eUgUaPrqD0BOGoGeHEKg5ypH0ZWeZC1Ww35ui3ZegG1WBb12LWlSLyTtmzaZjJwAsBxxGssh5rsMnTrHRGY5VAT1L4nhGKExHEcE4g48BrAmuNBG2VnJbcqmbJUeMdqQcTXdDCpN4jsrf8GXe6JDRDSDjHLnUJNhNl88HYaxHtWfgdU4gbfKH5F8MlZ8SG/SR+Sd5Czq4i4c9kpAGMnL7Nc0yDhXK7uC90+EK1uK5Zp+3SX+Sr6uX3eJv66V0pt3R8hAEQSygKfYA/vVBeR+3cMCyf09ybmkBwB1N17RM3ASQIMMcrFBw/ANXcPQyJCs7UkApCkVIigBrS7XwlZVg4NaTDLZfGfQPv905LgcZgPHBT8iMFS39DSyK0ZOhIQduafDMD5KNcvtX0XK5GMKcdOjwIFwg0CCz/CnqWZe9HW0QC1w3wt4SZ/dAvmlaYVRR8GuIT+smTNdSiMKlLxUucRh/sX0Jlnny6MIKhROb6SoYSiZxiwNOyQH7Rf0sBnrQnyIKEsfDSKRVKMwCeavYw9aHwcXigvae/XQEMcf3Q2rFxFD7Tfk7DdiKADO7BOojeTPkPNpwRudKlFr059/heCMcKZe7KsOhvtyZNxv606IQbfqgB0qnfB/910y
*/