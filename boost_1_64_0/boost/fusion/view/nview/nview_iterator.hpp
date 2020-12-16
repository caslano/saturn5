/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_23_2009_0948PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_23_2009_0948PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

#include <boost/fusion/view/nview/detail/size_impl.hpp>
#include <boost/fusion/view/nview/detail/begin_impl.hpp>
#include <boost/fusion/view/nview/detail/end_impl.hpp>
#include <boost/fusion/view/nview/detail/deref_impl.hpp>
#include <boost/fusion/view/nview/detail/value_of_impl.hpp>
#include <boost/fusion/view/nview/detail/next_impl.hpp>
#include <boost/fusion/view/nview/detail/prior_impl.hpp>
#include <boost/fusion/view/nview/detail/at_impl.hpp>
#include <boost/fusion/view/nview/detail/value_at_impl.hpp>
#include <boost/fusion/view/nview/detail/advance_impl.hpp>
#include <boost/fusion/view/nview/detail/distance_impl.hpp>
#include <boost/fusion/view/nview/detail/equal_to_impl.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;
    struct random_access_traversal_tag;

    template<typename Sequence, typename Pos>
    struct nview_iterator
      : iterator_base<nview_iterator<Sequence, Pos> >
    {
        typedef nview_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;

        typedef Sequence sequence_type;
        typedef Pos first_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit nview_iterator(Sequence& in_seq)
          : seq(in_seq) {}

        Sequence& seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(nview_iterator& operator= (nview_iterator const&))
    };

}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Sequence, typename Pos>
    struct iterator_traits< ::boost::fusion::nview_iterator<Sequence, Pos> >
    { };
}
#endif

#endif



/* nview_iterator.hpp
h2v+rSBZyp7bBmsOZ8odwPE+rvdA01dCFCtFGHA9DZf4Bu5xvWdFyW7dDfcTHpYh+7yASwY15LYBwmDso64uEQ928vtWpHjLB1doLmeYu2xNvDKgXAwQBrMWFLvE4hQtgw+s+Mg5Nc9rLh+Su+IhP5vLPqqhtg0MAhw77usSA6G20lqrx//yKeArPCgXgwx6cckgRO4sGAzo/OR8l6iGffFD617vax7o8f6Aqa+0iOtdGDHST+wzIgzGPrrIJQbAvviRegY7X7oZIseyo51jwXHf3aLQqoJXQnaxsxkGEztTMpBwjrYu0ut/E9Qdn2bud2dz6UFtiPhVMAjw3bWLXcIHevCxenackwQ24lTZlAg2YgKTfRQO1NGqgUGA88+udInbwV9ab3E+/8Tv9OgU2RgHOZlcNmK4rraIVgYGAYqf+F1iqEfLwLqkkNr45XI9OtnUHPTGM70LDeT7gsGA1sQbXaIU3oVP1bP6vf6Qo3y/bCwAPfAw3FnxV6h/lLeaEQK8HjzhMndZm9Bd1vvkYjhbfC6R4W53hETCm6yO+ZFt8JRLLIW14DPrRvsK95+aw3tlRTzskBy1BzV9vooAVetKhADHj150md7Wn1tW0f6kdZBRI2dI+EOOXkwREgl7MTnmR3bBSy6TX7IB5ZfcIwdw5p9G6KPLLzHTx8ZMFP/VwP9Gq+LiBzvBPr5bzo2DvDKOWvSawGEBogMlM32sj/SqSywC/+AL9fvJA86C2OFdsnMixEwSGfIsNYHD/UQ52Gb62HzbRpfwwBr4pVDfc+sx8/ToRHk1nKUUctRziBBIaBGa6WP0f6VLHAH6v8nKLVh5Z6oenSDbZUAENY3t+ydLLjTTx+r/epd4C/jfbO18fXtDzZ87ZUM65Beq79/Fwz+1GWTmN/lVG1wmt/Qryyd6OOkuzeEd8lvQhLnpDPl1Efooq7ogBFgHfnSZfgxfW1VWH2vzF2QVmdziFRz31CIk0uVXmeljc+x2usRM4N9KLF720ULIK7hdJtjxUj7+a8t9xd26EeXZIhSxtQx2ucRYkMO3ViWPyesv1qO3yd05ECNxcfhE4VLrQ+oVYRR4T0zNFjeAHLZYT2/e2Xr0VpNzOymZwy/SRFJ6RrEYzL6YnS3Wggy2qmfZ9J+e0lyOk7vtul8s74SmkNIzcGDAZ0k52cY32IZ8g1vkIFbfQFNI6B04EeCcu9xscTrETbdbuQQP+DP16M1yH+RehrIY9YDOQ3AiwDZikZIB6MF3Fr/BvDf06E2yr10/l8VH1iQSWslOBDj3tDjb2MnfIzt5rJyTAbGidA47WZNIaCk7EWA7qV+2sZWt+gZBz1v99OiNsiIL3oUUDltZk0hpLcdiMPGic5QegL+4w4oXFJ0E68EYuSIJ7GWOfi02hTXhMNHtzGYYjH1webZ4FPTgR6u6y3UhqBF6gyy0+zcmc/gMmkJSrwGjwLVBA9mm5s9O9Wy9Of56PXq9DMW3wLpI5zk4EeD9sSLb3Nu2LqbGVdWM0KPXqfNlxhofNonh4DBiIRgM5iwlGN0fd1k2wpxdeZrL0bJOQhydUwb1tVRRtCiCg64Hea2pB1kYx1DXwh+OfEr8ZKuiPf9B9rFqkC+2DP/lPrIXAaHAdlIw6jP8inyGUby9jIBISp/BIIi1l5UMtoIMdqtn+Lz8L/RovfTaMUWOWhZAIqWtaBAc9HowUi5qiffB+nNCUwkhOWhZ1LXM2lBfRVQfEiHAttJ12eIl8KOthv/33HD9Aj0alt/a9X6yGN+JUcHq7kW0UoigOGhdqJWNzl+p5RAo8/mDRFknjrnNvqCKtZTDmvi7enYZsa+X5myEbDgB3oF2QuST863Kmo8=
*/