
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

/// workaround for ETI bug
template<>
struct apply0<int>
{
    typedef int type;
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

/// workaround for ETI bug
template<>
struct apply1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

/// workaround for ETI bug
template<>
struct apply2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

/// workaround for ETI bug
template<>
struct apply3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

/// workaround for ETI bug
template<>
struct apply4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// workaround for ETI bug
template<>
struct apply5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply.hpp
aZqUJ3XZGS+3WkNkmxGEj5nPVN15m1J6PN6eqzSeke2NkO0NJ3zC9mJdb09Kh+dptG3T829NGm38Pa/vMNr42+ov1lrrL+r9p2nmttfDtlzTec8bw1+vdt3Fqb8INcnvOga7aOP/kLRFz8aG+LCqb1OLLJen6dtU24dqIDbStV3vgY0wAoNxIjbGTGyCczAEF2FTXIPNcB22wE3YEl/FVvgGtsX92A4PYHtHG3n5/cROLtrIL5X0PYrNcTm2wxXYAVfKeki//P6hrKcuzlc9n66NXSW912AodpP0Xos3Yg+cgD0xDXthBobhI3gDbsTe+DSG43PYH1/DAbgLB0q8jprkdxAzpT+TILk2UoZbJF7jJV63YaiqzX4sDsY4iddE2R+TcC5OwbswEdfiNMn3JNyNyZiPKfgxzsAfMBXPYZr0WZyOQ3AWxmAmxuFcnITzMBXvxHTMkvRFmOT3CkdLvl+GYZK+1bL/1mBDXIvdMQd74RM4Etc71ie/RTDExfoGy/qGYCAOxc44HK/BERiBkep3MGR9I1yUr/myvntlfQtkPyzE4fgAxlbwXQfqF4z3HSpQr/BnqFPwtj7BeO+h7PqDAet8TVMI2YSXCEcJZwktcnxNETkX//l/DcKkC3b/n5A03jJz2qSkqvn235D6Jkf7qzy594/CQByEnynX0x9a77XilfZgNw+NiU9MsV1D289z5ffJ51vvvo+c7/+S/KRNmFxfH2NbE+OljZjcg2egMn6AdY2sV9qf3lHVd/uV8QLp6075pH19xvMYz9Dde51g2udsg+yLmWJOtU7LL/0mmDKbddoxedeZdTFN2847srpzO9AvWKff0dI8Sk2cyRfZhibM9uL+XNrHyb0GEtj45PQp2vvzPdWd22seZ/uhrrav7Cov4iD7Q5PecB/X6Y1UbS8jfnriRDbnzfMIT9O71cd1ei367UtyvYmDOr2dpK22yVfee5RvmkfhCbaXXbo9c5rcJ7cp6/16yvzUf7MMm0lIotiXkfYMQnyiUky195WJaZaMeFnuhLr8S3k/0qy0j8ujUo6T42enJ8gyhUzb7c91WXyydfy0jE+W8TPqY0ieJbzK381pcdZnEMdkfgsFSj57Kf1MynTWo2y7WMaJrTKbJj/nS/vz9ZKfOZKfWZ848jOVzcn5pOz8fODTqsvPIl1+5kkazLq8YxVyTpC/J1kcz/wO6PJczifMx7ZmJFns852W+abYZpT9J/vGsX8lD1XPeYoZJ3MYL83jBMe+kn1HwmX/S/xmKPHTfHMr/HLn7w9+xT7I+8y2D6anxMfYjr3yn+XJczKnPK7lyGPl8HCZ79Jfg3OendHkj/Z9pWiJTDV5/neO8A1xj/zcGveJUxJ4tmOLCAem7XlSUDnlKLSAZYl+nJnSqipHUvYlPc5x98OMGuR5UtzkxIml6UlX5YV9X61pxnEm6z4t4zPs+1bGLfKsr1DGHceZbK9IpstxpcmXfGlf/7jkyxo8Sb7kFDjnC2XIo/NVyHHX+WIth17myxltvkh6mKbb95J/su+1+cUo+eNTbzyRyCO9fzDe+Asljtp8NquOUcY1x6jkrRyPcuzp9scJ1f6QY4lxzbGkyfuXpB3/Y3I8LSN8pzyTJv/Ie3MC+zEhhqsMj78VTD6jfJtY1b+O9nmyH+qvafxlPvVzySD982nJ5/BATp78YEg+OPZR6kzt+WK6tEk/KN+d3Y3ft2J9X9rSl2K7DEwxS91PzxqeXwdW+0Z9Hej+/C1p1KSbvHEcY/6668Ug3fVibonj/G4rG4xb+4RWpb+AaeR5aTkokXOq/fzOuLI+W7GWsiHL8DA5nRJlLZ87KA/RRLwj+bTTmkdS9pg=
*/