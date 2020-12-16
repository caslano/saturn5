
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
/8Z3lnkLoi9a9Jnu0enjsdz3uDLaPglpT10cJ66Rd4FVsJjzYjW6ZIE76eVx1mmUHzrt7yiydqN8iTRai4/3G91aaPItRLtmcph7nTE55phgKu8Isj6aez2qteQp5tvfGybiY1sXx3jnQ0pZRf9JSSvrS6XI906Nz2qk4BFN8BkMhUspZ9S94jP1dyJ3N5WsuVb3u9Mf76v/O5Hmm5CUT/dtRb5lyLcV7+tZi7885ni76kv7LcZ4TfIQqTf3nGZ5B9N8G5B1AjXfqRzX3WuK3+RbvLLf8g/sy3c79XV4IFr83kj8Dq9Vjt2v9rsqZoKpYd8Vzhh8d6uVY9KGMt1tTbuuVS2+2a9cP+xvttslbVDSe67pNsb5PtrVYdR18q0EtfbrMPUBTdkshQXpvJ+7vzVZG1hGpTzKPFMyIgvdtagpW8EiR9mqSF/e1TFHZTt2qdfsku9WrvXYDsjfB0Rrvwkd6+YwbIFcO+mQchLgX1NO5VOBvVw96rleuj1Eujr6/U+o1weVb4N1fXMIkXLzLZYYaHyJdV5LUn8s7erylcRJEx+ovlNI25cxKHbf7cZv1d0c3w2Dt7nbRbXmO4X+XrNBbhjPS7t4FimhfHEPi7/c8575vm+jadn7qX3qM65+WO87KZOmjIrvOqr6KgrSbfauBYkNoJmPbDxv1Nv8Yv/n856recfG86b9n+drPE/Z//m852qesr/zf/2dp+zvvHLjecre55U37a4c3/vYoPRXwz7+2nT9FxtyP1+/+Jefd+xtHvop+1oAMkYNRspaA+3t83AcW68mzF+AvWEojIGdYD8YA2PhFNgfpsMBMBsOhPlwEFwGB8OtcAjcA4fC5+EweAgOh0fgCFgL46Bi1GgYBsfCCBgPHWsyyFg0uNRgTYYZMu8iEUbAK+BQOBMOg7NgIkyGV8DZcB6cC21wHrxaO2+S8WTe59e1kXlWbWEIPF/SpZpk/BfIk3QtYJKk+1jmpVTDPvBT2A9+BsfDz+FEeBwmwC/hAngC5njMk14neu4ymCf9uug5AEPhW3AgrIKD4UE4Bb4NL4fvwAx4CGbB92AePAxvgh/A2+CH8HZ4xLVWlIzZgrsM1jxZIfNSboIt4G9hW7gSRsJVsDe8BY6Cq2EiLIPz4Rq4GK6FpfBWeCtcB7fA2+BOuF49n7dM5sfVMy+3hce8XHMd6TIlXZakWwBda1NJOotBuyyUeiiCF8Or4Qh4DYyDS6UeSuAV8DqYApdJfZfKPPXlqnqvEX15jfT1/jfR9z1Mhv+AZfAHuBb+CP8Ef4Z7Zd7aadgE/hM2hRwznQenwuZwAWwBc2BLd7llrBS2GpR7j9jxPIyGL0g9V8L+8EU4FP4JzoQvST3vhUVwH1wK97vmfcuYKHihZl6x93nabWA+DIMFsBO0iP3JyDrJL8OkX7PwcbH/CWmnT8JhcKfU31NwLHwaXgV3w1T4DHTM55NxSDDcYD5fF7E3CraG0bAD7Aqd6WPrSB8i6dtL+lBJ30F1HzJL+vkG96E75Lq8E0bAu+Al8HdwCLwb/ou9c4GLqkoDOCam5iNARFSSR1qaj0XznSmEz3yh4CsxQEAhAUcY1JQUH+UjMyorNTUqMy0rempvKitbrajtYeVuWG65rSW1tVlrtf87883Mudw7zAyybu3O/f2+358Zzjnfd75z7plz73kNg1ukfdgKp8Ntks87lXxWip5WJnY+IHp2Q9v+WzAYPqSu55f4PU3K9W6Jfw8Mgdthe3gvvAjeJ+3nTkmvKkDmycAucn+01do1ZZ1yC3ghDIWdpV50gTGwK4yF3WAf2B2Ohj1gIvwDnAx7wmthL7gK9ob3wT5wF+wLK2A/+BLsD18=
*/