
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
ZOXlZiu5SUOkvrt08jcaPqWIo8R6i9v+5BHGdS6YVei2/3THDx9N5HVZ1Ffs2d6Yf/wk72Z32rCYctOilXy6RdImkneVO29KZnHx2YVFOfoHhEsbdhzpbhM7mxnoZu4lbZHmzuvdBn2lDWwGeaRd3fnq3fnGF8yz5hXaJE6Bu42kPrZRkk/CGWiyudtym+TTblWh1vdh8qWMduUbV0KFafLsTMnr1T9tYlx5HadOkbW42DNjd/IdSRvOcOZzBuiwzsosybM7/lNsSx5BHZRyCuzuVsvJsmflkc3dvlFjvPJJ61KW9FeyXh5lrIeLTRXkk3rya31uVgmur/Rp/Iafnmu35pNZyVujl3e6M5iFK7dbf/0YpX+tuTZ7cVJRYb50r9IfUWM1+U6ynlVC/zWOKRmv2nxKXXpJWbvdeaY5r5FKld3XgpRYV54JxcUl1qJxBTnTqEFm3uSS/CzOKe21Y7nkl3GfYC3i5HOOhaTCovxMtxnhMl63uvMrWRPmFOZm01bUXj2n0uIkr7PBrUVeF0eSXFN5n1fGbaatuCTPMRy9+1YdJ3Xa8mWYuPI8140208mjvZ5XjtOc+/MKqVVuYYEjszSDtt22u4/xzN7QFFI/seNrbO0fr9rReP6oY6o63vu67NHHMg4sCZpzXBrK6FqYlqBcj1OLMguKfV8LNyZ4tAcHuc8HV17n3LkLlPg5c8R/3058Z46P9R04px4T35neCeiH3zMEm3ph00rn+ZZHS+dxoKfPdbuB7s2i2+CE9lv3Fl3dRzh1Zxyir7tyrejWucAGojtqtEa3Ou/FQHfQo6Jb9yT1b78fl/6YOON2n9FOX3+d6Pe6YQSoOy7GW/coafetBrqrpN29bzJN6+2K3vjO/D7v7O9cji4qQDXHes4TSznUoN6P6ekObJzbNWNN1VtroDfM3d6aWEd++KVdemtGeetNkrZObm8wzqS+mot2s+u+MU5nrIsNmwxsqBIbDC6GAbVBTIJx2ycepq8/8lGN/mac451HG+utNtAbJ3obHxwD15s6yvjaEnO4wRh/RPQaPGAEor801vj8Xmugf9HDot/jZSEwvWHRxte0yCP09aZIe6svH80aYzq6J0qd1x1hUOc1otvnC2dg51r0cOO+jw7StyND2sDoxS6QPsgZYax/nYF+m+hXHmSarX9VgvH1LuZIg+cJ6QcfL84BPVdEjjB+rlhnYEPlY3o2UPkA763b4330/1EG41DaX/+HhsDG39bhxu1frasfEf2GLysBtkF1rPF1ILqDvg0VYoPew3Egfb8zwfhet85It1z7vH6kaEb/x4z0Mf47GuiXsefrRSmQNqgdZzwGqw1ssEj7Kz/sNPsasDvaR/8HG4xBaQPtC32gY8821lv3cNG9Wl83A0OrO7BzbulY4/tt7xCD9ze532t+6Ajontd5rHE/rzTQWyn9rPsjaIDX2eXDjZ+vQjsZ9HNjvZs9vrbonWOit9JAb5XU2/DH6ADH2a5hxm0f1tmgz8UGgx83Aur79vHG51hol4YDnpPYrU8jKY753TLOPX/oYpfQwhyrq+69feg+Subafk9dbDn80C/ftYcRaJ5rncuurI371Q7iu5K5+ercbtmvtnHP1RDyFM7lKylrN9+lYitviUznbYzjewiGzc0jj+zdOpk81mxHFs/zbXkXg3eq9Zq6N+PaHhVrPN7bdzV4tpE+lx+omvW+Xhlv/DxTbqDXItdTnR8JAxpni+KM6kzqZlDnRzx1N+c5arHOPSxC6tw+tOGATchhwu8572vWumMTZ2eJrvY+5463b1ib6LAXHkV85pMb/u6dPHlwpEXiTEe4v4t2fu7g/jwcezknZGzzrljkPKc=
*/