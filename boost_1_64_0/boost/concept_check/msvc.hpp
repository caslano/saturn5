// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept_check/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif


namespace boost
{
  namespace concept_checking
  {
    template <class Model>
    struct concept_check_
    {
        virtual void failed(Model* x)
        {
            x->~Model();
        }
    };
  }
  
# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
  namespace concept_checking
  {
    template <class Model>
    struct constraint_check
    {
        virtual void failed(Model* x)
        {
            x->constraints();
        }
    };
  }

  template <class Model>
  struct concept_check
    : conditional<
          concept_checking::has_constraints<Model>::value
        , concept_checking::constraint_check<Model>
        , concept_checking::concept_check_<Model>
      >::type
  {};
      
# else
  
  template <class Model>
  struct concept_check
    : concept_checking::concept_check_<Model>
  {};
  
# endif

# if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

  //
  // The iterator library sees some really strange errors unless we
  // use partial specialization to extract the model type with
  // msvc-7.1
  // 
  template <class Model>
  struct concept_check<void(*)(Model)>
    : concept_check<Model>
  { };

# define BOOST_CONCEPT_ASSERT( ModelInParens )                          \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =                   \
         sizeof(::boost::concept_check<void(*) ModelInParens>)          \
  }
  
# else
  
  template <class Model>
  concept_check<Model>
  concept_check_(void(*)(Model));
  
# define BOOST_CONCEPT_ASSERT( ModelInParens )                          \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =                   \
         sizeof(::boost::concept_check_((void(*) ModelInParens)0))      \
  }
  
# endif 
}

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

/* msvc.hpp
3RjGwesjjs0R38wxbDhP9t8QcHwBjXJntpnv6kKJUUrC3H8jjeP+PrcT9DvAmLf79tzpEWsUzua32PxxDnzhx6PmwHuxvY1Z7S1JPHARFP2v7Y3eTfstizd5MaXyvY4fnhUBtyt+Lce/7ijOXpx3P/mTfA6cRWEe51EorCWCOc8wc76XMzlfJFUUSicvmBx3rd/6dmOy4I47zsJMxqIrqtb+0EUmG4miqvIgTYNO2b18n+EKlS2E6+RlXMaRIKu9RoCecXyK7fXLUGVPKiPBVo+NFMpspTKl8FSVSPImHJxV2WcpO7mMK2URVlko6OhsZHDt8ylrbzT2Ix8csA4Px0N7ozGVlcL3XJkHshK8F+J7uI9g4algYifx4iJu10vMq7DA+ww8bWFcFnFQlYKuYO2znGexsByR536cx1VdztyBMfcPfc6Si+MkDorU13L4Hsu2z/QBKz+iOPETpwIx8kaN16eLXEZmRVL4cYoyNCQ8y6AyB13HB0duGWQFq3+78CzDildWhH7lh4LvQlhnGZ9m9bwsfekVSaJk0EbFUJvcCTLML2/s5mXo1j6ju/McwztIZSsRe3nlB45gC1lTd3HtzcJzhBdnRVoGsbCWsKZe4F4hT1sUFVnhOrE4DntZj2beA7Eu9d/NwwqyIM+SQgmpDUmdJOoxDs/dqNxBL/QcNw8rkOK+/tBfJ0uTL7ysyKI8S4m/zCGH6K7Jf+bXLoWz2zKLS0egCPGESoIH2dD4vfy0tSeaeJkbJK4Y9NTNa7WT2WxBzvcG6vey2g6F3z3jfbTZs3vwLpXH92j25JyOPbuHKPziQcRH7tldpnt2Du7Zsbvnvxk11pE9+e20z75H4OV56Oapqcp1FqA9vz3vJNy7p0GauXCuaDbgdxmdu5lOL48CB26BQZM9advAOki5Bz1POnlWSQGtAcl0DzCmfC8XYaa61sD9n+fgxl6S/Bjo08kltn8AP6PeJV8weGuwYHJq5UxrG+jjQzhq2aF1XG504MAN8rcwdoMucEzLYvhnDY4GDWpxtCl0geM0eNwLebmaj/3aiiPdK9myFnDUoWHy/l3jxLoPYmIdYmjZB+/Sr6dYrRLlXqsx7DEBQ7s+iKFVnxvjGwDATO+MMvAWXn/HZRtiv9wCGOYxTA8wjk++DsOYfZcrgNW2OVjetfh1ESd514b7h+sRHNJC47TVYBh2azPg+oDVPftxOu9+6A3hO9jH6I7P7m2Id8bnCuLD8XnPjRDD+KDdC9h/rOODFhQGtE2e+yjfqw7dxE+k9z/creV71f+k+qTInbBy/LQU3eYoxg7hnVxoZ8QHg4xSz3PqvuSQthG6bLjbGDdM4yyIgwr6KEWd4H3UNYybBWXq59IREpjwv33GvYvxI5mEVRKG4v6j+Hdm/DxzMgduh0Sj+PsZv6ryMpVFKZZG8e/D+F5YuUERJWJg88FmxqYbjS7vHWR//ldg80JR9AEI1t3PrwUMgHoJjWvCh67T35nBC27PQq5HzpDRi9sZ/Rs0p8voBenznrZR87iVB8QvbuK4bQPh3DjHdTLbs4LNiKNhDdx7vo7GuBEDxN+4leG9BcTx/hzBMWgMe+s2jaPlB3Lvj2EYNOLnb0JwDJr02Tsozm1aPOFmGuP7JCh7zTWIz51oZBH75S0AU1+g0uAYovXekmL1PgXWiW07AeuYJJN6M3Mr5Nh5qt8RwDgOd95VfE8srKjaMHv3PXv3g63xyX7LuTSKc6LlXBnFeXTLGf845+zds/8g2COnYe0cwaFhHRzBoWHJTs7EARrW7AgODevJozgQluoX7nTDq+YhckbnIXKulofIGZ2HyLlaHiJndB4i52p5iJzReYicq+Y=
*/