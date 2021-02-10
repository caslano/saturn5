
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
jb508NUgfKEVmnDF896hBN9XRYz4Kcx/XVGiDK1DalGF0LBBneD38JhUWQ3Kw7mSvcTWIyhDEmUBtoRp3jo9ZaJLi5hWx5fZMzEMLgNhZE278apuNEI/N4TK2fazAm1zqYeNwFmFyrYBhuHRUSUfSkHktq6lKQaNc84ny22arXbzyWa7XqVZvNltk4xTX/gXITU3BjKvK6HJPtCp8gKFDBJkGdCRMoTuQaGSHo6IBka+smFEyVmcZoc4SQ7pfrGI07RbCTpnXW4LhMenGROnno+a3OIR6wH+JyD4LY3f/84PUEsDBAoAAAAIAC1nSlLhdHP+fgEAAKUCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTA1VVQFAAG2SCRgnVJNT9wwEL2PlP8wWoQ4gXvhgtwURBd1L2y6CVQcTTJuLBw7sr1s9993nOyHeu0pM/Z7b+Y9RyaKqVWRSpDGac+fD9rvfOhiCU9NBVKceylmCFxgTeGTwnU0HYEMNNp9vj4UfP9oDbl0uG+nhgFxYpWg08joY3eByXuLJuKuV4kb3EZC42Ii1aHXeNVug70CmWElWPN+++WW+XMLKJ0aaNoWt6P1zNmZ1GOgfI5KJwqYgnJRU2C0mOEoWz8MynXTOndCXP5Y
*/