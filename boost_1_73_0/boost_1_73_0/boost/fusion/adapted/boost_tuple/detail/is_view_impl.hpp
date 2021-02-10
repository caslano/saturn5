/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09272006_0725)
#define BOOST_FUSION_IS_VIEW_IMPL_09272006_0725

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
JGCtV21v2zYQ/q5fcfC+OIFiN2ux9R1THWcx6tqGrawLEECgpZPFVRY1kooTrP3vu6MkO4ldNB/qIpFD8u4e3j33nNq77sDxT/t4PXYHP/xE7ieiDz1bo5lW/2BsDxtE0Veo/5HhNT2fEKoPO6uv0RE8yeordJ1V1MR6y9+j6Anhrhkk/+qz8XXEX2mltmzsB6q803KVWegOjuD01auXcAK/Pjt95cOZKCTmsLBYLFGvfHibuJU/MnF72zP43ge0IPLeA4dhJg0YldqN0Aj0PZcxFgYTEAYSNLGWS/pDFmAzhFTmCIPp7Go0+dOHTSbjrPFzpyowmaryBDJxg6AxRnlTuymFtqBS8kD+E2ks+aysVEWPwiNY1GvTuGEQIjcKxI2QuVhSOGEhs7Y0r/v9uNI53aSfqNj04zYVvcyuH93qitCsxR2o0oJVUBn0gc/7sFaJTPlJKaLFslrm0mT+DhYFLJK+0mAwzxt3ZCrR1FdAWDTZ8vkklIReWn4YVRiOtsnU+sFBSmvjKK10QeEoLXQuUZR4H6oiQe3Ou0S0UZosu5T/oGQ77AmoglBBJ1jAaNGBpTDS+PB5FF5ML0P4HMznwSS8guk5BJOrxt/H0eSMuCEpqga8LTUaQqFBrstcYvIg+E/tdK8XXsDg
*/