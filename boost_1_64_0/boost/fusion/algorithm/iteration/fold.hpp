/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_ITERATION_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

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

#include <boost/fusion/algorithm/iteration/detail/segmented_fold.hpp>

#endif

/* fold.hpp
hT2ybrZRL7Hcl1fV4mf5VRc+wSyA0MVv8k+cuuEwf1jB7rG7xpTOxaC8iQ8M9r1wNrbtOEYxhoh/aO961KXMnjPtWmHd4FlVVV1QuR/x1Y6EfhE7IjJOsDrdeBOE6GLU5ZucpEZDF2ATncPx9GgvPjB6outl8OK5yslEkUKv0y+p/pXEnSLYfVA93Kd5mfR5OFSlp+kLd7KNkU/+ozHImzCwDqIWp6zC6+JJVeVqR2z01Woz14u7Wm0Zo71mj6VuUag41tr/tlj35LUdCCmDFQJ7WUBR4VWnjhDjLfcGAc1Jz857ykEByqsiTs4nULOevyPlReN23UHvFrpkQtw4K0KeShH8bOaWijuJZyG4GE58jqK3331TUN4b6euGebmFfJFTCn8+Su9piplYTPAwjL/joU4S9sHMJ8uNMpCaItnkXEpAJTnXyxiOVKZMsi1w42wzeum0kPgoeEooF2npCY1d5YjmyYc83YtAqTbsQZhSfhILSP+BxGebO89lAffFK5fyBz4i8OIHOqWwhhNWlSSbUA/SMIZ3iM9icpargxCGeakCoe5EEYY7uA==
*/