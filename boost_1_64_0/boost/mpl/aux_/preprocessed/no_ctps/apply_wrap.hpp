
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
DH/nIOWSxFUBhGC+Ak0gSGtIKwsKlrisJlOCCm8FlTy7YWymSxazjuA+7YtaP5L3MaNJa6R/mY6j8zSgr/MqHddg9tclITOMYu4vkjjHROYUpI2ApzsMncC9hKeF7kIvu1JARRowEMInCQWEGUekfgHmupWoyodu0HGIlOi2cC52b9qu/5FG9cR+Li4ePd6KSPsZOk8YtJVu/E5YBRUfPltGFRT+Ss1nfCk2F2Aq8yudx6Ohj1QTGSSr0aRlftAzfIC+PqosVSZ+OGi7sqhcGnNfDYoUxIEbRkJD+X5vjMtj1xCAI7GAzBR4VeEdCPLCe8LKp7hbKPe35wsNuBnlTW20VbltLd8ECCU75wp34ePyIf9sXNKH1CEN5VII2F2gycTdFWq09hhe23wv/IHrh+0WahVMxq+YnIeiGKtuGv4iuxawockRFspwfUtatG1ZrMGpPdvdglOI51JyaMnEWo/Tdq0/SJqADibSuUVzuMRe6COGlHnDKvLkzFG9YU7/Q/tvKCWymYCEKaVUMOIQK0BZY03hWIT4S/uN5akM5pXLgHH5ppiTsldgFQ==
*/