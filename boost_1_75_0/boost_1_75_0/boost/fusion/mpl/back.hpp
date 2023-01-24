/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_10022005_1620)
#define FUSION_BACK_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/back.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct back_impl;

    template <>
    struct back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<
                typename fusion::result_of::prior<
                    typename fusion::result_of::end<Sequence>::type
                >::type> {};
    };
}}

#endif

/* back.hpp
f/X3znJ6S6gbCFh67AW0/V+/1mV1OGVlqS9gKHxkahq77d9ChWGMEr2r0W9IunbxJunaiheBCY4oTcgD41WaKD93S76mnMcDZYZU/REBsRenkbnpoNUkgKe+/uwrbaM0tzafdMioVsZKKDFL5DH6rdmu+RzNQeGtpFo2yqqibLsoq1LZ70+S6Qh92IDv9ovdOAg3nBsaWj4kwjxGdaHvyVCfQigH9FtpdAmAhNSkuGJovXmMsl5g/gGsj31oOYtDwBtqNwe641OYNjKqxFo+7yQlkVu/05rwUqnqbtQ8iB6xCatlBl4ynhwqnnySKPU099a46xZ3V1jj+/71Z2bTK2Z0Nc8hc8bTpEFnlfmEs6pGNCQVOLn8oZH4afot+uy1xpH3gCBvs3gxozf87jNhmdMfp8vFTlSLsGGIdPeYf2zTThDppczXqMg5KXMrVeWPBLP8ygQvqrRg7ch+5WPK0Ih+9s6ChwYEXXRZVmaAuHzAl3vILdVYJks16b09uXXBbnhGBtYYbIHj6kMpsuLNjO5EvCCO/Uc/tehmV8GKAcGr/UqR3ZdbK9WkTZJq+ppy9wQxVtkCB62vYADC67Bbm/L5P6u3cHKaVHWrhRM3FFDKIF6J3V82mQxgoEiJnVGWBDaaOmI7WR+mpqlfwIF+oy880Rdekwb/MvNhC52SxaavTHe2TLECKMTpjghq+S6Ey2/K17yRqTnStezd
*/