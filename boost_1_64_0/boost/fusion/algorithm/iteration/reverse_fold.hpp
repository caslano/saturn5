/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/reverse_fold_fwd.hpp>
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

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/reverse_fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/reverse_fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt
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

#endif

/* reverse_fold.hpp
0h7HPC+nOXsMxug0S1t5jk1Kcmqi9Jl1XHNtZeTljsrfSRw9df+ZsVWlLpHzbSahOscq7E7dYzW8NH0mjOYmctQjxnMTBerUGf6OtKv6SuyWNNQnXCf3ExGsnGvWazOeeA8tqFNSPGjT7NxWOaSaQbt087Vrl76rmkG7dPNf0y7d3gekujbtneuxxbskHqoioowN4XnfgNGO+lR1TJdV1x7TczQWjNLbp+Oout2vc7p8r9Om63rOE7PuPkrX7r5hPf10rbhO28fkeuX6pr9Pc5q57Plp6zf8pWWZspmJ01InqPPA/3ptfF4JoYwZxIdOL2WKi+NeSPq8uOTL+uu1Zd2vI1tM14tH6fslNPSgvNvHdakhv/dKmehK8FP6XqXb+iWoIuNxfajfh0x7n+GYw2tC6kSX/o7h0of/tMTtJKGmcu+nH7fhnvTjV65TszLUfSZiDeKbpBNfs2quMrlX8uC+N1TnWhBRQtojLP9V2rNaz9nXsLZy75Shm/aYxCz3ab/aZyd5RnCKszw36T8jyX2Ucnvnev8oz1yO/pBy/6Yew2Gs9HOPkPvHvlhHqT/G2PJAbv2V1yIeHvuiOzTHnmt32Y69p8c5TJVnMu4bEYomfcH8vUSJk8HzA/mhyhOz9LNfL3mSL3mSM9qeJ4xBMjmRftpkimd5UmfMtc2TMN3nKW2exJIfKbWteXIo2n2elM/rVz6v33/SvH6rLP1kCnoOfrW/d9+7b//j4Jlu+1+9ULYx14O85P2rvI+dS7hJuVeQZ8eF0n8mF/vhEhyFS2VM8OWYgo/iXfiEtNNeiXOkPfIazMO1+Iy0L16N72K+tDMuwLO4Dr3Y93ppx7UBm2MhhuAL2Ac34fO4GXfjFvwAt+JpfBFbkpZt2Bm3S3usl3Ag7sBI3InjcBfG4CsYh69hOr6Os/FNnId7be3eTfJeVd63Rinvi7C7VHqHpX/Fp9gQj8h8g59JPh7FSDwm28vzkvek8t5UOQ7tlXt223HwsrYLW4Q348N4Ky7GrrgEx+NSTMTl0q7oUZyOj+Hf8XGcj0/gRlyJL2Iefomr8Rtcg//EtdKfYx22xvUYjhtwAG7E0fgCjsUtOBG34t9wGy7D7ZiHL+Ee3IHHcCcex5fxJO7GCkr+4834OrbGPdgW38II3IcpuB/vwncwA9/FR/E9XIkf4Br8EM/gx1jbm3MC6+IR9Mej0n/oC7wVi7ELfond8DjK+SLvRrlP0jlfOkt7ry7YArtJu68eGIY9cSD2wskYhouwNy7FcGn/1Q+3YH98Cwfi+xgp8RiMFdnnEGyMQ/FmjMIQvB174jCMwBEYjyPxQRyFczEal+MYfArvwLV4J76MY/FLHIdfYYz024qVfjvxeAET5bhNxOo4SfrvJKO0U5d3qco7Vu28nN9JPXMWW0o72A7SDra/tIOdgufQLO1gF+KvuAwvSDvZi3gQf8cLeAkvS3+nZsrOLfkD2B8rSL8kb5yKFTENK+F09MUcrIYz8TpJT6FJ3p/iLzIfam1cbevHJ+3UW2IAtsK22BZ7YTsMx1sxGoMwFtvjLAzGx7EDrsROuBU74y4MxVewCx7A7vgR9sBj2BNPYy88i2Eo8Zb3okoZ0sb7Oon39dgCa2IfrIUDsDYmYx00Y0OciTfgi9gIX8bG+AHeiL9gE7yMTVGp3/2xITbDIGyOvfAm7IsBGIEtJN65/H9518m7T2u8lfpvlpx3faV+7Y8xOAD/hgNxNg7CeTgEn8Oh0m8oCrficCk3I/AzHInFGI2+yvkhc1jcgXVwHHbH8dgXYzAC49GME/AeTMBsTMIdmIyv4WTpTzpV5n9NletWmlx/7sK7MR3zMAN3YiZexmk=
*/