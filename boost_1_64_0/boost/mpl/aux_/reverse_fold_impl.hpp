
#ifndef BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

/* reverse_fold_impl.hpp
dHnIFQHo7Eju/USYqvcEysrYgLE10VA2XsjfqjVjys7vfHKiCK6Na6Sz2lexU6+Y1hj3or12VrzGNRgvVXbw61rzabnaEPo89CvtGSjC/Uq+0oURjK/x+Iz2nHaaOdiDnp47g5ghDKH2Xlh53oMUcRynp7WgX1wcW2Jzm1QXS0Nn0DQcqD4Hw94HSazlLkTzplNKZiq7KpdIDwwrWMeVMkgnqPKSfo3I3a1LKeuU4XsphWmrcAye58v4sCuCeZ0vH648j0Ys3cMnZI9Cd4Azl889jC2X45H3U5a2TFDklrVmeDXYjwpm7qR3w5vw7rEvft6+zY5s8kBzpAIVlBjQUEUpHqKlhZOhfVBfvoHYsAI69uwDvnn347j6BmpzxhEjMfqWcoTjSxyGLw6A1x8TsT7blQdKRdDp9x+oQ8iI2o+58ep1JlRp3M6veJvT4idhGDVUhEL2LSSLJetQEa7C1Xe/R90uSUztdxsv56uzvXwkIs4WYO/8pXglfRWoP4AHPx355o5LmD9hAlO6+Jk0ltTyXV8z6NG6ZNoTuorCzGex8Bwhyu08yw9fCINownvsURpG7NIhOqygQMpmsTz+Sjls9Iuw9vUynDN8xuKUikiPQMJ+PnSfheKoaSkVtxiwnb7TkbH9Iq0Q0aGi3q+p0DEQ2fGT2dkPergw/ylfO2cL7sxJ4121+5AbZMg3VDRiCS/ixnqnMP9kJ2/e95zObI3kx5OGYri8BO3yakRqdw4PqDuA/caJdNFHF4efH+MfWzsRfNdDYI8OoZ0GC7nenqPwrexker4eJLu8mKcvlqC6Sw+5u7QOaTfN4oXDTyNCw4JPGTmCUnfHkpxwK3xdN7Ay9V60wSqOa93fTdsq49mS94mof/8Emu6l1NM5lBWlv8Doh0HcWy+TLl9T4DNt1uKd0ia+n23CmTXSaN05n3qEG9F3xlBavj0RweNm0KBUH9Q4J5HtrWpS+vSNvl17zzvFx+DqhhO0+KMquS+X43bxn5Dn8JrV9ktFsOZlfnPdIXy7soU+TtlFCzekwn1/CqpGF2NCP1vIDF7PdEtWQyRiKMnYzqHrF3OZusdC9JXj/Bv/TpcOPyQfF0m67nUb+1bkI0RYlsyVR2JMlBhJt51C2EsHttBNi4ZOsOchp56Q5bv3dOaqImJuSPMpHr1JrFKS5d83IQ/vBjawcCN5z/TmIwQ4geoGQwotkiNr7QUkNWAkElctZfM7rBAdvAA6M79S+AsrkhEeQzZqpiyyUIBt3Z1B0qWiUFnQzsWPG9BAaQMoLSuCUh9FNuLAYTqeJgnx2AB8X3GXe+Zsod2lVpjl3kQDRxVx3Wn96dKpAH5SMQc6yeb0dOpVGrjBlN6k/aQrU5RYSP4uFAlkc0D9aWxScOa9wxdAvdibGq/OIJv9WugoHU8fSpvR8cAX2UdX4OL1dSRRYElDFtfAbEIkywln9GrBd97Wu5TmhhWSdYodshs+8vWrTiFf+SX3yP9MbZ7vWOGoc4jxDaeBpRZYKaXLFw41pgyhULbcmtOGDQ8oYEUg2ZduJ+edU7F1iBweRs8j3crx7I+f63Bj60s6/iwbStWiNOGCG/r1NcHF0jLcGg4+6mgPHc2rZreCrTA6xhk3RMsocEAWn7RUFdouXkyjRJgcLaWYc4IT+g6ygsJKb+ifGEavF6UjU/QSK/w+Fv3q1+HCwfFUvGaEYM3VHJbL3mLNmTasL9/NNl1/DwXZKi4/2hcfGtzYStM9eLPoO0075Eq62o+hYaBFKYHXuIWXB2ncMKEmvWv00u8Gyr+pQeabAJeqNKIYESt+4vhbnOW5bIbvAZyv0kAfh+FUqTSFXh/dRM0H06D68jv1X2w=
*/