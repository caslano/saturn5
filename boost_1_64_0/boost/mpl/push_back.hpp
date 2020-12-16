
#ifndef BOOST_MPL_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/push_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_back
    : push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_back,(Sequence,T))
};


template< 
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_back
    : has_push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_back,(Sequence))
};


BOOST_MPL_AUX_NA_SPEC(2, push_back)
BOOST_MPL_AUX_NA_SPEC(1, has_push_back)

}}

#endif // BOOST_MPL_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
uo72IZTZoMiPJhmKbKcgSZ+WvyayySTlI5i4ls8zas1BgjyNyTkU8cgkpQgWod5bustbWsvTbRt6dJksbyVyNMfWUTJfPkKjR9wXevU64Tl5rk5SEH05XZ85SWmB+V/rLd3tLd3OntUGFzdmktIib6Fo0GfvuZJ+WNLHlJvdcoHG9KVn3jtRqYCZ3+wtbfaWbuUpuQ09ukOUiyVoCjiIPrulBpFNKpD00dE8ny8IM305pV82UcnPzG+gLqa+Vmv72jxRLi7goJm57hwvk/TbJH30cjSKxkxU8jPz66l/qaMNFGVNtKBos46i8DkKRYK+6OJoCO04x4DQBuCnlnrZgNAjKFcQ2qBDaJWk3yrpo3Oj8TPvHAM/6wGe7dTLBn5molzhZ72On/HnJIifrHMM/NQBPFuplw387J1gwU8d0Yf9T0gQP49MUPIz880w5A0GfpahXOFnl46f+RMSxM/MCUp+Zr4JVrzewM8YlCv87NbxkzshQfzsHa/kZ+bXwYTrDPzsQLnCT7OOn4bxCeJn2XglPzNfCxPeZeBnHsoVfpp0/Fw2PkH8jBmv5Gfmt8OEdxv4yUK5ws86HT/hsxPEz46zlfzM/FaYcLOBn0dQrvBTq+Nn1dkJ4meebN9uHgUM/MxEucLPdh0/489OED9Zsn2reQgw8LP3LAt+tur4aT4rQfw8IttrZv9v4GcZyhV+GnX8zD8rQfzMlO3DZv9v4GcMyhV+GnT85J6VIH72nqnkN/t/hZ8dKFf4qdfx03BmgvhZJtu3mf2/gZ95KFf4Wavj57IzE8TPGNm+3ez/DfxkoVzhZ7OOn/A4E37omMwyEjafddiawVF4W8YmA0dgaMs4pQcOheq8HBbVGwHR/ShXAdEGPSBaLp/Tpp6j5bMutQxeZG6n5yg8gbFvjDPi/fXegl3egu3egrWMBxv0OVmWt2HHNY0HgPEI+Zx29ZxwPus0nMGvFFrpOQpXAPg+r9ILC7MbMd5mxoUNen3Fa+i1neZVeujd6JW4Us/pzGfddmZwmKvRcxS+APRlXqUXFqbZW9BIsSTjwwb7nOc17LPVX0rjA2B9mXyOpp7Tlo9duxn8GiJMz1E4A+CHe5VeWJgmb0GDt2A948QGO031Kr3y9t3desDdfobEmXpOez7RoJ7hyLiTnqPwBuD/5QylFxZmHYGA0MA4scFefyXL+dU2TVz0meiSM3qJt0vPMPDWBLCtJTQYeDsb5QpvTTre8s7oJd72nm7gbR3AtpnQYOBtB8oV3tbpeGs4vZd4+4mkEzZPKAy8XYNyhbdaHW/Fp/cSbyeebuBtO8BGVtRk4K1rrAVv23W8aWN7ibc/jVV6YWEa4BLWGXi7C+UKb1t1vC0c20u8zRyr9MLC1MMl1Bp4G4NyhbdGHW+5Y3uJt/fGKL2wMGvhErYbeNuCcoW3Bh1v68b0Em+3jVF6YWE2wyVsNfD2DZQrvNXreCsc00u8HTdG6YWF2QCX0Gjgbd9oC97W6nhrGd1LvD0yWumFhVkPl9Bg4G0ZyhXeNut4mz+6l3j7iqTTZh5/DLwNR7nC2wYdb57RvcTbP09TejGPPwpvf0G5wtt6HW91p/USbz+UdFrN44+Bt0tRrvBWp+Ntymm9xFuWpKOZxx8Db3tHWfC2S66CAXUvjpLLMS9v+tY2sdDkLW3ltRjCGRh6ZJQRX+z2FjV5ixq8Ret5FcoGfS4bZeizHatsYiELD79Bp78C9I0QjeJfGZ/NlO07zfMTIz4bg3IVnzVb1qL66fQXg754hx+xELV3pJLfPM4oXO0YacFVk2W56rGRZv2I9dWItaplI7tfq5o30rpWhTd8ctfArJFW/SDEt24ZGCPbt5o=
*/