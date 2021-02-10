
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
xCP/5t/bmqmNybNzvp7q7WE+bQgKLvXUTu1LGavE3iGE44kwzvZOg+/xEDzy7zH4mIWnXfRC6FxpYcoKqkZHZs9PyulRTZvNSbMZ3v/Mml2CZ3TVJYw+DBa6/u/+BlBLAwQKAAAACAAtZ0pSW66MclYDAABEBwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY0OFVUBQABtkgkYK1Va2/bNhT9TkD/4cJFUWCArC5Nis2RjMZObatL4sRWksbDBlAiLRGlSE2iE6u/vpeSH1nWNvkwwYYt8dzXuefYvuGVSWjF+8QXaqnx4wuvH3TJqj6Zn0eX5Pz6LAovT2YR8b39ke+1aPKKvII5L+956VaCceKXvJC1BWy+NIihFFyZDSJpbhBSNXF9UuWmwIDtLfiK5rwtD/lKGlHQ0sCDMBmYkqpqyUtItDKYBbhKNONlhVFeG+ZXhgnVJ6NS5z1gYolwRDok0j2gSpuMlw5xSKxZ7diyLRz8ROc5Vaztp+d5ryfTOY7ee20buZzOIu/94W/gujkV0i2TwkDJE1HYYT7wNc0LybuYY4tYYn2ouMLu/n08gjdBlIkK8IXNAG/wIJQUioPh682sFJCOGqRWKTRHdmYqlMB7G1cVWJ5KSDJa0sQgKQHO
*/