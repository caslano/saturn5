//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< pnm_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    pnm_image_type::type asc_type = is_read_supported< typename get_pixel_type< View >::type
                                                     , pnm_tag
                                                     >::_asc_type;

    pnm_image_type::type bin_type = is_read_supported< typename get_pixel_type< View >::type
                                                     , pnm_tag
                                                     >::_bin_type;
    if( info._type == pnm_image_type::mono_asc_t::value )
    {
        // ascii mono images are read gray8_image_t
        return (  asc_type == pnm_image_type::gray_asc_t::value );
    }


    return (  asc_type == info._type
           || bin_type == info._type
           );
}

template< typename View >
bool is_allowed( const image_read_info< pnm_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
YPsC+62jcBucGEBmbzCgVSwKYyF6BaPbMErz4M5oPq1/YwxfuAbOYlLvtWgeNzM1h4wryOgpAxY2V6/Vxyv68nZWOGmOlNrjszz6Pgwbmszs3Wk+N36m6rSr4tNfPRrvqbO5rtFUSu3nKZ6AGGZE0mfidvPxsOyBx+ro7j4eUyhsmf0xly+VW96eHh63vMk+HlOe7stCzZfb59Z2FPfDx5txeHUZ3hKXl1cg2loz4VKd7zQvr936adJyPUPz9jPuMzWfGvc0/VPQ3SCD1ou9HTrdX2gWPrZ/Z3t4wkCvc7ZgXw+fCh7aMd3P5UufVdD3G3p4aFzwgShbr7JcHrtPTrm2vAqXT58xzl/3IAvrG8z10O16xwTrdKyaNYvLb6rP3sLy1mCYwtCfHot5bhlmPAfCo3XdrSvrpXTX2XzOHpzNE57+xJhRVr88Rq/s3DPfKUufH/60Q0M+i8xZybx0n7wsdPnU+KV5qlwe1Xcb4tH6Uu3wmDhu5v5IQ19BXa0FVfPt/hm6JadpZ+bG1m1f1BXk0Mx9dJE/MEHtTbp8Rq7osoytWVzQH1+2j7E59WK16t3j6SeO2ML2ZK++e6ChIJenC5OVrK9cVFG9uJ5PINeWLqKOTgzTEecgpB6eWddjd0hO3iYop9YZh+bypJz87Dg2wZs9D8KCZVVrfRWLIuJmR4w8su+DtVOg6we0FGToGKXVPnlZYXgMKQhr2XX+AdCMfDJgA/j+lgl05L5n9rp3zXipsVHhDX7h9SKZe/onbIjH3NXvzyuIheu88vPovNxvB+hPA1hZcOk6i4H6p71re911NSOu+8jWpc2xB9092WdqVvnoyeXdei5v8/LgjHPsfsDvD/b1pnLH9UNVZ/N9Rcp6UqL7sccYrAvsB1uyllDY4WBPb8m/DVa8wToEnd1hfqjIevfOydgwn3/fo+2h2TN399FYcDS1sqFlYlkuLYyljHfxVPZtxVqnUpRJedZd0rTegNbTtSZ6miWZE6MGjjZfjXRxCTLTNOtPlydcJDhMzv3yXUYf6TB7znmin27vWve9Z0uZmtc9n+zmZc8Z5ynLrCP02Vx1BsspC77w2J7mceuTUmf7JufnMdexpndkuzr1+QnioS6/v45+XisnE/opX5/bsftwyINnuN/Ue9Ca5MpvlD2tMburHlq4BDTjacvMFZ8BfPvK6KAVg85ez92vo5Qe9vtt5RJZ3/93i0tUW48qSNPtdaJWV58ZTGmNyZYwau/IJYum8E5gLdfpMVpbYL6xl46QaAFxvtuKtcRxMbfScsg1Or6N3fLLuF2zsejm6ECwg0wBjSuyvqdzRIH3GV6jN9zmm2TpMj7n5+9mJZRugi1m4gCe4X7vVaY/+uXtaY1YJ9t+8/K5VaCdVoZ9/KHYh590bwu3Jiz/kb78jcVTD1gdOhp+987FoF3udyXM5qTakzTXK0heXlO0jgRm+usY4zupM1tsPdnv7Ojz+yam7yz5nXMJiGKaQYubGixlJykbfiVg+NacYmndIE9rc8DVP88KSszMFSd6ebrp8m7GsCM4wrCBMtlI2GC9uHXe7Q/N4xkKI7v98RujLxvOV/e4DCBfYyXy8uljkzoubNpOzwUfFvC0ir5UeqbNE0yRE9PHu3B+Hp1RYPb4tjpzUh5e3WRdR5cPdXLWcJKP1+wZDKw9hjeciSf0y2NGUZ+jcPmM9I/PSzeSr3T99GEOjyPVGyoPid3YOTOYbnzffRnmWR9hN53vCKo5pMDlybgAVnZPLTA0vFQ7pZjr87XunG75mJr74Tszi898TLOnLXwRSdu7syzfyg77dT/nvMk5Ph7nm497jkzzMCVmXDFbw/bWTPziuzY/Rs8=
*/