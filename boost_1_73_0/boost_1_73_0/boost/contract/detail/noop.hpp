
#ifndef BOOST_CONTRACT_DETAIL_NOOP_HPP_
#define BOOST_CONTRACT_DETAIL_NOOP_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Following must be expressions, not statements (as used with if.., etc.).

#define BOOST_CONTRACT_DETAIL_NOOP ((void)0)

// Following always compiles but never evaluates cond (so check correct syntax).
#define BOOST_CONTRACT_DETAIL_NOEVAL(cond) \
    (true || (cond) ? BOOST_CONTRACT_DETAIL_NOOP : BOOST_CONTRACT_DETAIL_NOOP)

#endif // #include guard


/* noop.hpp
WxkQ3aoV46hqii45KrLEDtLtSTgXa+vRPrFU3Va1GrVd0maltYhv5Ct1oJOaqPkWxwKqXMJhtGWibUD94wPUQmuGYAFFndGdtXdHIUFMTTv+TRuhV7lmKit7ciunBWm5gkXLuDrBXTzKcndQJ3B+egr9zjRePy10/Lzwd0XeV3d4fjQvJr0uHMvya+w3tjnh7CtudysVrbA/zGCqzFjNCA4LkOy+RmCd2oLq8ZFjGMe+eMwSRrH/KXSDnkM3JVWao4CFUCU8cj089T5AT49nfb7lbukmR2Db1H5FeGtegROpYI0HvcvQ6ZXz0b0NEgvrhJcxTaZREo2jILZcPdHQ4v3p3kwCz3Lqwupkavrqt0ciZjVTQ1QjK4baeAT/WPB/jWvDXtu42DDYDWu6IThAqJOJaoBAGD7Sk1Tb1IEEUQUlHveZTvhQusejl0m/01AGKeg499E4obHPq24776x/LadgphruF9cP3A9+4CczLNGabKWxT73kdhrCFze49awpVTi7paH10uiz8RjEngduEEc4cD5Mn0kJBniQWJcDlyffvtmD6C6NJ553lQb+jb+P/Q9QSwMECgAAAAgALWdKUlLlMve1BAAADwoAADQACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0
*/