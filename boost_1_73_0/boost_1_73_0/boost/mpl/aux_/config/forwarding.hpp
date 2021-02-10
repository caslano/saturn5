
#ifndef BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_NO_NESTED_FORWARDING

#endif

#endif // BOOST_MPL_AUX_CONFIG_FORWARDING_HPP_INCLUDED

/* forwarding.hpp
sklp9X7k+c7YrOZkxyPXp9f15g1WOCXi8igXyjhjkq8PkIsMwVqjAVATyJFCFChYMpbAZf5bIIjnIhYLpFJoEYoYRen7UDSAF3tVyL1Q2oQ/cFRI7gUh+c9C7tdmcLbamzzN1pP5Pv12PeWjbTSdDTr2g+98GD7Z2UP343701L+ZTAed/+qatFoVMkWXGvYGJ2JCmMmYVmd913NGj6gYnk4pvr6iVxVSwcmdlbfoaRz0fKj+AlBLAwQKAAAACAAtZ0pSxmYXBLQCAABaCAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNTdVVAUAAbZIJGDlVttu2kAQfV+Jf5ikQkqiGgMNTeIaJAIkQeJuE9QnZMyAtxivu7tOoF/fMRAgSp6jXh5s79pzOefMzMq2RqV9T2GF2TyaCXoscP0s5FRV2IPr9jY3uG+420UH50JzTyN4iQ7gTOlkApEOl+fMNg+etrkN9gkclE8oDcWnyGyJcbimryeGAXdcKg0SfyaE4DPgKkZfw2W+AGdpPPADLwwxmuM5GAb5TD3tFbaYzEKusLGsEgYh+S9PcxHBgGJxiVO2zWlBm/tSKDHTRrPpmFe5PKuJSGOkDXcdowUaV9oM9DL8lmaTCnWZK2FcX5dujAIb
*/