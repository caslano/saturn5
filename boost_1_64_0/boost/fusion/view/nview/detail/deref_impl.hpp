/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM)
#define BOOST_FUSION_NVIEW_DEREF_IMPL_SEP_24_2009_0818AM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<nview_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef typename result_of::value_of<first_type>::type index;
                typedef typename result_of::at<
                    typename sequence_type::sequence_type, index>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return at<index>(i.seq.seq);
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
9kf1YAzSgx1GD/ons+hBsfUh1QMHBlTj5qgCowc3Ij34gVsPIhRS6oFBEGsTHl0gHgQZWLy2+br37Xr0eyODRRz9Qq0st8h/lFJAKHBuaacC8QPI4SYF6N24a70e/U7MjQc/OZ5FF4BIyhcCocBxsx4F4jaQw82WPhQM/w28I3F9MlgNHLZCVaCKiHuY2HHP5IQC0Q14vkUBTv5mVaUe3absY1gLWdaBQFWJr5LIRjaTY3tA8W7fL7HyRdqmnQGxka2inb0Gsrz/ijx/2TA63mFyB++id4FIAd5vVYAVcR1u0qNbxKBEiJKpdz6Pg/cwVeaMmRyvdycWiG0QE7rNio+/8dU+PfqtaEiAdT+BQ+drVF2MoSps2a2oF5EAHBhwbPTMArEVbKDbFaA88wjoN/KNWJAOnXLT+GTgq6KWAWBw2kAq8LMWfCIrX+rIQd9N1Fx+LcYnQQ0vRj0oL6OWAWBw5tDVF4hpEBu8QwEG/b4J+hx+JSYm2rmUfDKoq6WWAWBwxsnGFoj3QQ/utGpfnzH5Vvj2xcY0qFOVxCiDMLkMbAyO3vkF5u75BAVY+sUssPw2iYluiBXmsclgGPl64MBgbKEtBeIrWBMnKsD61nPO1lx+KQbZfXb41sQaH/V6ABhQLk2GV/hBD+6ycsrK38zTXH4hdoNNNDCOTwbkayJgQDJwecVqsI3uVoAhQyve0VxuFCkQNWtI4rALIxSOqi0NEQvBiUJE94ZDvKIn1EO3cswS/uzwhR7dIBbEg33M4hdGiGwgXxcBA4ofH+0V1aALkxTgk41fLdVcfi52ANdetT96qGVQo7rcEHlHMDW2kQu9pr7pvai+6WciJCGnjsM3qikpD4aI4uUwN7IFFN92P9v7UD/bJpERD983Rx8ERRtdQrWZHMcCuntFPvB+vwJkvL/3YT36qfBy9sGoIWxVCnMjP0DxbccBJytAnw39qjVnn4gFaRD/Smb5zsN1ZO84TO28Q3SK2uuB7ykKUDl/1Rt6dL26PwnrO4f/U1NSF6wiCnzC3Cgn5EyvKAd7f6p6NroXP6g5+1jss+vzpjPU2lJEBZQtrmgkvEXXDAne4wd7xQdg701TgFfva32oHl0n1rSBmlP5DDVWgEzrWeKnatjcDAm+T3SD1+QMTEc5Ax+JIZx1hxxk0uUNNEOC+8YpWZSBLB5QgD/au8AP+FAsA1nM4qjH5iCTLqO8GRJsC431iuNgvXhQPc9O+fN4sIDEwAzIHUrm2BcdZDbUBohyKWKx4DyC8V4TN35IAdYNbHWq5vYD0QfuGYQyhcgll4UvHIr8pzqjUllJGAW2laZ7RRbIYYalE79ccYsefV90zobc2gyGfLIokT6i22fNMJj34snoevkwWi/fM+tlShyrLtCtlhgFPkdScrBr08y06pTNfvN8PbpGVMBtrH3ZrLoQaKDaQTEKXKfrDa94B+TwiAJ8+GI8nKetFrvTYJ3k6PMfJbKCXAyAwdhTa72mLsUsBZiQe9e1mstVYl8i2NTJapxPBnS7JkaB98zPvWIY2JWPKsCa9kPg7sVK0TYVavelsr4TZB0FEYrYd2K7V3QA2+ExqX7P+vRWyDQTbTPhnUhjlUO4tp5aDoDCWdNzj1c8ArH12dZdlNR68DDfFYVZYDekc8TRDJH1VJd1EYpYfyutlRgJ+jBHPWvOfGqgHn3HvBfbOe5mRYis716inkS1a5wYsA2Z28rYDY8rwDVP9IAShstF9jHwdrgY7u2rylLWh67fKkKAcxCLojJ4AtlOy0x+eiNH/yggkc5yQghwDkr3VmIByMCq75k8V5bq0aUizz5nSWPUg2B1eQ2tEAwG40f0ayUaQQZzFWBwdf8=
*/