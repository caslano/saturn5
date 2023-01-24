/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_10022005_1619)
#define FUSION_END_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/detail/end_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct end_impl;

    template <>
    struct end_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::end<Sequence>::type> type;
        };
    };
}}

#endif

/* end.hpp
+t5ZlgviY8niHGTDxQahSnzkME3xZE2Rqb38kaKmyCyzZtv5vpldVJRvlIuwtToq2qXIE6iEImWhm3e5Ajy9vLSHssFn8oEkyWR4YV14A48Y87Jl1yZy3WEXWCik2f7SZKbQV/SVY3TirOCa9T4eCjufUw/1vaihso/0sTijgwROdvE9hq7PablHM2ZWKtkE5mFsIB1xSBXFDkRW6AmK+ogvCpRb9Nsusi6wyEXQ48+0xmSqrIT5NXN6DLIOZG+xzA6InhVotvD77JlQgHF4MsXhFdBKYBWBbcD7ZpqAThG0RsBs6dg82DgccBRbg6+5+E66jkt+lN37FDkTgd27w/p7NKwDlAf2ced12HEYiF++KUhvV1e/jgkWoy8ZHtipmu37w+ZEMHFCvZv3G13LHZtJvM4eP9OhXRZL30ySf/LkaYaW5wBpec6yogdPI04fonNuzXZaWIgvRlAB2YL+1qcpZr4kjUKeHvkwXaQGfMF0AU/MZNOOuc3Dj8PaRuRVcMC/E096pBNC7vPXJkFpo6i4qxXnoYfgQ6MNuNN0Ua/hra47pJN5iANHW55P5fFYjLy9T2xnTOOLYQnVQ0MuexrrJLNVy12pSIRLvvDL1Ay8X0G4pAUI0ewpHClVjUzCIh/SgsD7pbFMoLZ7B6RidEArtLy/cRAZLEphGxGDRmA688NrOywIYZe5toMg7NLgXet7YC8Qtfx38Ufw
*/