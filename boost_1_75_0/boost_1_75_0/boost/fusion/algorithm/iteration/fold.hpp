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
jnZR3weiwkUseqQXJ2QGX6r2FsmrhphIR9O+x23D6kUfYnIrNkaBIB+Ozjc9SeTHeSfqiNek89dqtMkwCYsG0CR8HS0nwQAOLPHTbq4nzxRudYAHlCvYusyWYlk6igzrQMkHrl7gNxrWkTuB6Dw2q9MM3cGRByIydDMwG5VEV7PhElvWUWxW9HpA6G68MZItom7WNZSqj0F71xyjPRRZU6aYqV0oIQ0qYQ7PQr0Q3YCRLKq+ygkzYNwqDRhPoc33dLZoWitzkMvg+P1klh+0lxnKtLRJuwFyxSw0mEL1/hq4g6wHnIOmb5BoNs5oi4Kd9IKkSciROkNL/ZYNWjOjMmQwarVGsLJwSwFLVKY+gL+we/8aZjMM5ZlhRhXDhfyLVmHuMD0op3cYqxTSZ8XyJ3133bAwS+K4oH2CLEKVXTjM1sLEbbXRxM1oimmTMGlQUnGzSs+OK8jgxE3wfVdasqmGNxY1fODS7ibN74iTlB7+ELmBRHo2ocG1wgf3/Ctsemk0tJO2mqwwFOKSJJWt7E7GkWYQ0AfG+EOSKfriNhIsfgZPtefN8HcnEPPbibD/YIJ43wAJ9ZTwEiS8BwlvUcIiSHgB6X9KqICERyDBTwkbb8LHGnpMnMC2b9xyAT/d/HTeZuTPDFYDRDxZ8lbramCYsidPOR5G45a4mL6TNG6z2AR/2O7PTisTvz2mihcRHsQHlpduslGEoVXn
*/