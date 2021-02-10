
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
gjThOWEmSg+djwazrnYzEYScuTo4aSpCzvGuiWtV23XhfgB7T8CDZEWu68LxOxYjzq13dzdMre8G4exWtymSI1sYVDQjWC4ptpFehXYdC3xtIDuINu89BbZb6cCBmcx7Pusc7ECDg8Vc8x3hACu2jiurx6qO7syh04r7iRtFnNtO0Zx1ZmCn7jE7t1gknqDlCqcPW/LgiHjmCoRAdsbaZnTGynSNrzm7iNGBKZi+KpLTRUr4s3FN+rT2m+Za3Qw3yYB59dsoiiTLgKrUSDgz86XoGEnusUrVSNdJIDH7RBKPtSZNfL1BhIObO5emreuhPcj+jaq5WVdX67DhK/uasJtqNq4GNAWRoKJ6cGAo27Ci3pgYr3S0+T6m8SUxgYsXsxUAjjWtvtrnKydqDgdRj+YNISPxENyeM1Z0T1RUUBI0bS4Dxzbj2IRZeVQc7Ji3BQhXSOz6lkiVN9Wud6HveQdrVNIcR/a8ZO3xGx5PmETXtB9Ue0kJkjXVyhArUxoTn4B8L2wXSZq4njF9a1yo6TjIjaA0YLKJoIl0fOsbsZg2F7UOZWU8tl7t7fno0o4tMmy27SwmUFLcIovQFSeW/LPrctg63Zqc2RSrvTVa1bGZaVKPFdcpSkUvRVLQLljkSFZ59ewNuSYG9eOK
*/