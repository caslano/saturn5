/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ENABLE_COMPARISON_09232005_1958)
#define FUSION_ENABLE_COMPARISON_09232005_1958

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion { namespace traits
{
    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_equality
        : mpl::and_<traits::is_sequence<Seq1>, traits::is_sequence<Seq2> >
    {};

    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_comparison
        : mpl::and_<
            traits::is_sequence<Seq1>, traits::is_sequence<Seq2>
          , mpl::equal_to<result_of::size<Seq1>, result_of::size<Seq2> >
        >
    {};
}}}

#endif

/* enable_comparison.hpp
H2RzJOoVcbdXRNX8O1khF+oOcsnELZzUS6MetF5OINUZW2vDSntPw9DyVPu+ztqXObhE4yks6JU3gTJxqNA7VI8Q9PSGsmjVGvPuulmWh6XqhW23yN3msrZxUd8eiy4UXxxDZ/nAzZp+JvF9XI8jRx9FWpv1qJouY7OmFyg6YR5lPcd9/mC0MTi9MZQPlTfSABH/pza5HsTPPL+AF1fV6zs4KeSet6Q2MAmQJWVqjm3WzhzRqbmbiXtMtQeayi1wI3vULNk8cz64WTtzkhAPu0Hb6WzNxF181yiwvCjXdtUTaqwZX4Xjdwq3225jT+QvfdTMsjAabpoA4u1C8dYa8zss4hVCBY6HPSFMDbdLha04N24Ur6Zl21+wtf3cwTYy0YI/fYd/4Nhcl14RRrisxPWepzE7+0QlM465HhCGztDk4UEXFEcznC9V7CFwgf1SD/m2OoeLMZ9rMNvJY8w3Qc9pj4qoYOa0WVPjPWF9kDh4Ust7ft4pyyjLIdVdhu4VfUFdrIF6/nxwzOdP1OvlbpAWVB6NFxVIxVWsrmAO6TVxpdZGPEh5UeL61XoSUl25OM+UY/8ovv/9ecz1VHHge1gXSclLSPrNTE0br2IEv1BHnQvVWbbFywqCrod3taqfMM3SbKteJr7mqiA3U2O+xfcsrPAOzsWCyvEG4+PHZkLtsj0dmjd1Ko/rMLfYGSuWROyFcVnccpXgX3SxpNI6yAmnC6H3KSCnOKgAlPF0ujPcNgiP3l/N9WPGOfDIIEjhCgP9gOJrqvDOm+UfbvtxmOUd30mfJvHojGL9kTud3G1jZUMprpS+9sNybUG5qqxLW/xchi4OFbup3rvKWwDkwK3t5qJaLs27rZovS46jKYx9/tZMWxV/ozdpfewrkL46URjrs0TIkUvVzicmLttDy3NGjBWtqaVJTceSQSJMgkrgKNtVLYbZbnmXwTY1EtrGSt6jpunyTrLy8N7i9RLPy2KHipnWzjuLSVEerbMLE97vHc/r+C42aTWXi2ouz++6lnNPtWYvQX1i3o3kregG+MDMytwVAi4YFTY4sIuS339QfhdClw27UsLWGmE/LWFiXmjgPQFbOox+/7mAkTRXSdugEfBD98Va1vA1DddlOyUcGv3+YDgVlkmSdvoEtEPYMgh+FUx0sYTPAHdOK/hwvF6DP/buuEOWfJcCHHQW/fLlYSrhD3wEeP8og29DB1T6Kd5H8ub/nOAbo9P9Ui2Hvl4jHsT9/BLhVHDxHKbav4i9QMDlXVj1XsuAL1lw0YgKvoM2XizbWE26zTUIymfAobR1O3enyvbvKTeKd/awnwaIOu9XsJeAtrQZFhaisS+cd9sg4zCyxKyg9wHsxQQrrVPjlSjt40k3E2HogxPSh/9ulb+xsv28QZUZnKhipsvygFv2kc6qUNXxudK2vB7omfvCfKnCEc2TcRnh6+UHlu307+4s+RUBHmWQWdHGl1I7YEKgbR5Knl4OWEGBIatyfoj6ZD0pPPvJbvUnJR8UVGf5ye2VE0HAbct/XuJUYxALHzHuwlK251cVjhwuWK/K0aKS5Nj8psKTgf54n/x+ThnMPlf6RBtIIRguv7/q/q1WpcdHIH+/jyiyWeln8keUKyss++cv+LeZcUS0sXUn1g9ilC17z9veifpBRLR5ct2n4Y3od2Wao2x6b6hoeNcTXdWeA8BhkdJlffeqaA1WibAs+xDg9thxm/8HWGVwW+rzYq7wiVQ5v8jxetidzPHiPkKHjf6opgWVTf55WGVYX9UceUyJbwU3p0JVnzn2WCzX58Cbaf7DIUauR/F9zwPM9SLYqcbmLcAXWDKKSclPXNVjJ6mp+XhkwOPz316nJ+4=
*/