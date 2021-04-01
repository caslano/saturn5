
#ifndef BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/config.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, < 0x582)

#   define BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC

#endif

// BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION is defined in <boost/config.hpp>

#endif // BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

/* ctps.hpp
fbtwOvr6g1830VYb6fa471UX85wT9tZfVCHUsLBXPcYTE8yc5mMsO3x4umBfp0ARpIBVAn1L5/bPnfob6rq8eM9Av734uUWnrn7g++ithAZDhW7mOBb2QQieeN3fPlnyf9xUFahc8UpasW3c3TDEZF7yDCvO17mRwAHpq1MGDpleRfW5wadVxRphT8Ts6Rc/0IYCPxvK3EymMbNbXOs9vBUfL1YkFxVQV4jySuqsIm6Onjefz6Hbtznlz2kT9r5s3oWVBPFywBNqtebe9EKZxprDbn4V4SKtwU31loVJUF7xAoG7qSwm3aQORli4yPXe6zqIV+kgCYdLgOorUBYoFCTwJxsK7v6WsI1JIfH0ZG1ZwQNImFMHXqiOGpabunEcdC8qIfn9FNbUUh6nnSfXUCzWoTFTyGVjgzEKcRXe+hA5LJpDYUvgZR++KPwPuZdhRp10yFtUhlLh1CCM46nVRfCT5TFeJF2OvJGiTO4l3CrtGRv959arbCGuYhuQNtQesNIo0jQYG0spq5YrlbNX2AlLs7yKqAioujVDEfnTOoUI4jgWdDcRCLPeaw==
*/