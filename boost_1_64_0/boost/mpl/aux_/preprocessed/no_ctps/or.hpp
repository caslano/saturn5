
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
};

template<>
struct or_impl<false>
    ::result_< false_,false_,false_,false_ >
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
aw78Gz3XvZM59m/aHPiuznVvPGf+v28O/Fiz9vxJ0321B7UsN7POez13dinq2/PP58D3N8l3PRY1uI9sebmvcDB6Ygj+gLNM8n2N78n77sQJ8r5Mmet6EHrhE1gJn8IGOBhD8Glsh0MxDIdhPA7HBHwWn8UROBJH4kIchYtxDL6Jz+N6fAE34lh9PeW7eKNBPV+Ser4s9Zwg9ZyEdfEVqedkqedUqec0qed0qeerOBRn4nCchfNwNi7AubgU5+HbOB+zcYHUs7FJvhfBW+pZGO+TeraX/dABS2JHrIqd5P0HWPzl/WFyPzbtO2SnvL+LtLOrtDNc2tkdvbEHPoAR2BR7YRD2xl4YhckYLe2LwZcwFl9HM67COHwf43E/9sGzmICXMBHLULckLIup2BAtGIDp2Bat2AEzsLeHum+ampfaffNSN17L/c5YhrC8xrJzrcp3qVCh4q/FP9H/T05NcVv/v2oB+v85i/T9f9b+F/r/nlnG/f+dss4gWWdrlnq83n+R9Mcc65Q+cKw5JjXWXID1/v0+r76eVg/jeu5e6KSe5pSbUs/7pJ/dlkV+q9vGU0oZ1lPGUwq0H/96PZ31ZfX98u1S73ZS7xCWhtR7vLPjQOuXW1MjU1Pcu42Ntmla4XzbVPZ9mrNtyjjNjd6m+nq2lnrmSD1bST1bsBz1o/+x4Jp6yhhLkjnKQp0Z7ujjQn114xl5728p91k8KOs/YB/jeT3f+l0c49HGVbJft4+rFHzMx14v/tNwuwQ42S6yRa5br+tuD1nvgyzFWRqwHGG9x15zsl5Wa5XtUdjF9drvs6m9PzXRlOezNZ0xCJsy5jXZPuY1L389jMe8Sl1n38yef+PHvHIMxrySuCkWtZb9f/X+l3wn2F5zwY3jYurekP+Pe0NOMmvPTzizY4b30zV/HXBlevOhK7wmXn9cLGeR83GxsjIeE4Se2AZ5H4/ldwwGyftuxabyvs/lfUexGB5DHzyOdfAEtsavdOXtXui8vI+lvH1S3idS3n4p7zMp76CuvFJSXluD8rKlvPVS3gYp710pbzMG4xYpL5xlvLS3nZTnKWVrcUrKOy3lnZHyzkp557Al5kg9v8cQ/EFX37Q/qe92KX+HlP++lP+BlL9L6vuRlBdqkr+N2ErKuw0DpbxIKa83lsYorIzRUl4MPoCx2ALNUi71kL95bGsptxyuk3L7SLkJUm5fKTdRyk2SclOwDaZiKPbDbmjBWEzHZLRiP8zA57A/voADcRJm4mIchKvwCVyNgzEbh+JOHIb7cTgewGd02yngT7ZTF2lPV2lPuLSnm7Snu7Snh2ynCMf+lL+F+KDB/mwr45QdpLxQrIkd0R87YQMMs9fzFvmbJn/rLrH4aPVELUZJeaPRC8dgJXwOq+Pz6ItjsTGOk+NxPHbEF7EHvoxROAFTcSJm4CR8EqfgMzgVx+A0HIfTcQHOwE34Km7DWfgRzsZPcA4exLl4CV/Dn3E+FqItC7Aovo5lcCFWxMXYBJdgc1yK7XEZhuNyjMcV2A/fwqdwNY7GNTgRs3AyrsWBarxVjbe6cbz15DuepmLrPE0NWSJYhrC8wbKbxZTtaarFEsoyMFuNw6pQoUKFChUqVKhQoUKFin9vFGaJu6H5/8TINEuKlv7/27l/b13uP1zyr0uKkCPChdjRn7HeKZL7Dw0JjbJEkfc3W9KpQUKK1ZYbCjLaCLrc0G0z7bkhHktuKJnkT3Ra3pzdQLTnhWw5rLg42+PturyP9vjk1XPOWX+xO7U3HLPNXRBvTonMSImhgRZzero51uT4/4cd/1/3f2V9FyRnxP/Nk0NK4/+X4/FuHs/Q1pcaFxVjTbWY5Pksns/gv9M=
*/