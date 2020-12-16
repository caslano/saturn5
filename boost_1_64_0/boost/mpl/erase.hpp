
#ifndef BOOST_MPL_ERASE_HPP_INCLUDED
#define BOOST_MPL_ERASE_HPP_INCLUDED

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

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/erase_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct erase
    : erase_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,First,Last >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,erase,(Sequence,First,Last))
};

BOOST_MPL_AUX_NA_SPEC(3,erase)

}}

#endif // BOOST_MPL_ERASE_HPP_INCLUDED

/* erase.hpp
8vo+La/vc8rr+0x5/Wq7Ue6Ojbb+X70vWf/fuS9p/8/eF9f/TjG//jH0/5ES81/5sgV3Gk9zlt6nZ2kwZuvKu39r68pJnyTrytGfJO3KAZ/EdWWCqD/iUfRmGsyw8WK99xUJq8phKfsbG76/+jgZ17j/46QoLv442WwjDPV8u289MDy0TUJa/T8jQFWbtLHw5UqJdaxjTiPMx4kbdVCB3uFv84nV3it0mKKfyYnVQ6+pE6vYaDSwRIx6qUROQvjruzIQaC52XCyYEITO60baATcZ8W8q4uLlXO5898a9vxr3Pjju3XdF2/Cmxb2Pjss/MA6fMN5T47si7r0//J/esZ+3Usi1VvpZISUe1rZREuIp0HgffYj4wsMIF5EUNwiNGi9WqVAtPBb1+m6jgX/HSYSKVcEzovZ9Hw8HbQcw9q3HDNvdJ4DzqgAl8RKFikISWMIa1fc/BSSCjxWtfnSnZpgngBxe0IkRFztEGa/9xAzk0BhQtnbGRvoIDPmcCdRQ/2uF/GpJAnqgFssacLoGTYCpwn3K51u+1he/GVKVoIoJjYCjM79JG9pd+IL1A9ApaIokG71/gaUlko2M2fJGabgSQr9JpNwnFJ4fiehMEVRaq7rZK35dEujgV454jt3VdNB7pyPxM+/DHf62nd4s0toYaPTao5chmkiZSR0w0FST2fjwL7qX5StlJnJgYpwBGqQe5SPxp9apPsSI3f+46sNtT+l9K1M4Ii2rbp4nWYQn7Z+urUMZEYtimSgB8NJ9IAFBPhRxoVTFj4GamiHIl68rXisQpQAqMYn7aDssGcFL3jmSIwj/L8z/P9rHA7bmXwNKs19VaA/bZLl0q3B22difn4Q5FNL5sh35Mqo6qnxY3XpK7AVZgMXbPHeNuB6eV1+fRzxH6LizfAQGz6rcKt1oEv/UMIcSql/K38qMPz1syYnSbyf86XD0mynv17+l9l/hV1KeN5W0rzzoCxifyOoe58xsPPsHiYX4fPribmL8j902WeHRx+zxP1Bp/KnGnpcPLv4H2JmO//GYPf4HqolTxM97+bDH/3gz/jyt988TdBmPPmrDch54cvx52rg9zvO0e1ce1Hna6nUJ52mDVeVId0vlzs3Oi+86z9N6rjzsmx1L//NG06H51z39iMO/7lViSw7/urHrbX3d1WhK9K/r9rjTKb7/D/81/nUbrnTKP7lx74vi3ic434GB7Z1v/ir2V2bbZUxjyzTweJ3X6T8x2QHPyKBV3f4+YI3z/Yq3nO/3rna+d33M+X7bH5zvC16Ig/+juPJx8Ev/jPc4/veaNd+qMca/eChhvhX/wkYDX5FD/dqN8VMuusw55fLuS3fKNc7Ru6QJEt/soYRZ99TPbbOu7s8aBefE66gw0IV+tOKwTzxrvOUOZ8GkzibIntpg45q79piYGsvBOAJpMUvr/pNXZH7rCLyjJCRjB3pF2AAJUPOy7i/zSLS7eYi6T1bezN+gdjh9tLTbGaa/yPWvOPcPiA1IEeo0Qlm3/VFvv1/brrDYQx4LgVkcHRCL5fHhW3mn9+pVtOfzTiHTxu4ijZvG/HtgPlxfvEMks6HPK0zZK4XtmbGjnFNH6cYzXtVw2OZXIWUyW1DOOzHSytuFiIv/J5oqYmW45UKyDWHD5p2hSIZoWhpQCX35HoXXzXhqU3OG0FbItGPRRsyGCB4PvnY4BI/29MFfUCdebBrYuCq/Qn89lafR34zKUbEpcnfqo0J0TZveywDOt+yWni8QeWUEhuMa+cjycyDaRVL6wj4wiPTzdXog6pNUMtsTM7IDb6ZNXpkK6Hf8wTYLMh+2Td4Xd6kpES+y3Ji+yHIPmMW5gNdb1YRqlz9kq3Y=
*/