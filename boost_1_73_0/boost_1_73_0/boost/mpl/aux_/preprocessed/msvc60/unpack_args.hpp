
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
LFggtn/gekVQ9NpXPd9ab671SjQIso3ddZw1YL7Bm25ZAGowTOsZbz2TBIrXX3DihWRO8+IqvwPkcfXPeq3y/0zgz0QLxckXEv5QF8hV4zs/Qj0Ab6kTJdmrmSf+uzt3/R/1N7nvn9RRPbRQ3zU+Qk8qF/dAal6oulEQnCEhQLMoeidI4GxBN1GCmr5bZbYqxVFlLqJZoofpBma0BkdxI7pj/tQZ1E1R/WyhYr2yJFV+N64P0gckT6tGZSMtwkw/1lAhQ9M8jiF/ilYr7dvpr/wN7cPnB6R/euaE7uIbuuiJUg/+FzkWqvUFsfftZJ6fTAe9OXyGBg7Ahz6dqZ7jKM2+XR5z+GRGkeeC9MSN5rEf6RY0AadaHgDrNupvaKyn6enIAh+hZ2EeGKd+uPIeEBMkmbtxTZhX2DUCCZRF6dkVmI0jtHAaFoxGHB1AAuDiMYprkL6hmQN+GvFrWmoPyMKBUFSHv4YbVosphaF9D3UV4AguOrj1PCC+Djc53QbpyQcQ7t0kCgNoIIU8lxTezY29m+m+mxVvqRkl4JVutuo1utnGfuj/QRluMyakfKVqRONO99r9gzYcjwfXGnOneeq6zOsozn09udlq0Az0oQ6n84+SD4CrQYKqtYjvAN+7cic4O4PT32nfuZPo
*/