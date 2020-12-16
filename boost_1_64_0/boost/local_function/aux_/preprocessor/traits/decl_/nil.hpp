
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL_HPP_

#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_NIL \
    ( \
        /* returns: list of `return result_type` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* params: list of 2-tuples (param_decl, param_default) */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* const-binds: list of 2-tuple `(var_untyped, var_typed)` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* const-bind this: list of 1-tuple `(type)` */ \
        BOOST_PP_NIL \
      /* number of const-bind `this` */ \
    , \
        /* binds: list of 2-tuple `(var_untyped, var_typed)` */ \
        BOOST_PP_NIL /* nil list */ \
    , \
        /* bind this: list of 1-type `(type)` */ \
        BOOST_PP_NIL \
    , \
        /* error: `[ERROR_message_text] EMPTY` */ \
        BOOST_PP_EMPTY /* no error */ \
    )

#endif // #include guard


/* nil.hpp
eNxz2uvt0iReb0k3PQK93fCyqM4uqrOL6uy2lM6ukOfLAzVAy6F1UIo7wRgBuaB57qjeLnpFr+gVvaJX9Ipe0St6Ra/oFb3+i9ff7F0JXBVFGN/HJcKrnkiIeKFpdlhRWZl2WGmRUpFRClJAgEEivOBpdlNpllnRbWVF91102223lRXddlNZWVmR2X3+37z/DrP7Znn7QO34vdWP/9vZb2bn+2Z2dnfmP7MJkCPXy/h/99f+N7n/qxzm/i/UcP+fUrj/AQ33fwHSa54axv3PdTP3v3lqdOMtOu7/Cgfuf8tUR+5/bnfm/i9y4P63TtVz/3MduNqvT+2Uq430ouJqR+T+Fzhw/33Fztz/XIe5/5nFHdz/ZvgjG2k/vY64/zka7v/ZyLe/OIz7n+tmzAzxJPd/EtLx4DroZO4/9KOro3buP86BfXkO6zcrHbj/TWG2qXVXX58uKO60PiHNqOpTxLn/TQ7c/9ZiJ+5/bsSyaS1eO+OZ5tx/w4H3317cGe8/9z83jpk82YPwIz979Ketyv74YN6g0+a9+NguJ8TGMWPjmO7HMc1K/nQ45x/36a5x/lumdo3z3zp17XL+fcVrh/PvL+4e57+peO1y/luLu8b5by9eN5z/ezB2sawiNn4YGz+MjR+uq/HDFbi+jErUW0guxA9ZAGmBvF4ZGztc39t64/+XV/urKuu73Qdg8v9Xij6AUKIq///ZCPz/r7Y2UCdt79bMnBP/f06hhf+P+Fr+P8Ld8/9V3dG9wvn/l+C4yf8/QMP/n4fjKv//Ouzb+f9L1wP/H3m38P8vFvnAN0Vc8v/bHMoiGv5/W+H64f+fEyyHIn1+3fD/jaKI7+Jd5v/7ihz7QZhBfV/IkKJw/v9za5n/v3ORlZddVNQ9/v9ORaxjLvn/TXrf0C967vqFRWHcdaSj5a4jvHPu+o1FkbnrN9p89EJRVNz1qPj/10v/Wet8a1J4X9W50Gm3+K9B1nk33HXEldz1AzrhrrdHvjY65a4foOGupyc7zAeZqu+fUuzSzwmZGlYnkJa2TiA8wpyQqZHrBHSsc0KmRlUnoprPsCnSZp1wxf/3T9X3k9GFrvj//qlrp78sEv+/aapzfxnz+5/k/48R/WZvf33m1SkHv7/R2A9uax9+v++HWL9ZrN/Mfb+Zyf9/TuH/L9Xw/xsL1y3/v62wa/x/o6hr/H9f0drh/zcVrTv+/yhxX+w6Px/HcR9ad/MHckQb3jX+f9PUdcP/z5sW67+L9d/F+u/WVf9dFa6v0yEtkNchxhGo75A8yGxI8xGxPrzYFttiW2yLbbEttsW22BbbYlts+zdu6238v6yhdkag+3MAhnD8f4UY//fjm4LBlLcV9GSVB7BsgCHHMGri2I9ocv4gC5FGdoF9LNeanhMfYGiBhQ/AdEbb+QAId88HUHU3zwznA+wsjg8Xxw/V8AGGF1j5AOPNPGJc9z0cX4POthfXAx8AebfwAXYS+TAM5Dk0VsMyGerAB/BHKJNoeAH+grXHCzDznU/e+CMcX3oAchlsa4qU74ZAGL8kA2WVgbArRdybcSzBuALCMmea+1jHmpV60ssXTAcJO9SpprD6V1OJSiPH/u8Sx3uJuF4lrleJqxvv/xnj/Sly3LJajI9m4tcHIk4V+qF7clyT8crrZtZiJ6iXjpC3hV6tUYpcdtT3sqCbpO1vCZ1ZorzUHiWfy7oJ32AfvmGZes0ypQ8QJuxQxkFtdZj5QR1+o6MOi/01tv1hB4f2P8qwjp22J4ZzSC5BnMaDO68rbrgkjQdHHC+PyCUJcL2/+8T5UB8gkzdH2av5U/I2rbq2gvVYlNuybOQPDD7s6vKIdKKoqwdr66q2bqo=
*/