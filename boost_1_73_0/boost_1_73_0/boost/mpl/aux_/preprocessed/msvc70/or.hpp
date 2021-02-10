
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
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };

    template<> struct result_< false_,false_,false_,false_ >
        : false_
    {
    };
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
        >::template result_< T2,T3,T4,T5 >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
0UGypo605U4+kCfc8zV5KEoPvqCtzeEJoXyuyWH+twKeKN/3KpJehinQvPxnH75z7n5eJfsctAG5sCXWoQ+IaRdc4tvYzEQRwoYb3pagal1hZxl0CQTWVjomhaYMxcEprpJdGShDVaXrvANKpRzMF6vsZpkODgjLxUMmG5Ta8WGtDIzg2V8Y3jHneyvf9rJawY/oyvUeDgOBXgd0bBjCYeNAoT07hjWcsH3hRKhdW8sQG0eBDNmZ4L0DX5K+fZlIzMmHFD5JjcRv9mF4/sxa2N6ts3LwePWwulncR+LcGNzw4zN5FonoE8sf6fm3ZEoex1PyfWZ5/Jm8AlBLAwQKAAAACAAtZ0pSaboNB/0BAADFAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDQ5MFVUBQABtkgkYM1T7W6bQBD8fxLvsCWyIkWhB46b1idqKUrdOm0SWzbJ/zMsBgXfIe5wgqq+exfwR6W8QCUEt7fD3M4MhBaNjaXBCQtzlWp6vGDzqqvETNgsihbdDRZPEQv5qRPyHszO2BmssNph5Zk8QRZWWBYNARJpZc/Ag48BDH0f5r/YN2lRQFTjJfhjeNQ7agQ+BCMxGguC/HiIWE8noJ3MM13BU/mC7F7SxoNO8jTHZM8S
*/