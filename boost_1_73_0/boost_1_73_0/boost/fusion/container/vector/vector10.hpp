/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR10_11052014_2316
#define FUSION_VECTOR10_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector10.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector10.hpp
VeAfnSYal7qZpfNGR+AjzhKVeQILAR+gU5gCm8eiTEKZU2fauV3C8JQY3Cuamt5QpAkQI9YOzsTx2ZqY+lrpsfhwfP765OJcfDg4PT2YnF+Kk5fiYHKJk705nrwA0StYLBfyc5ZLDYvnQs2zWMnQrPn9PtuDwU8qCeIylGINpedpWZTZ1mzNaXiGDSzb2b47AN6EfuFj78bL5ossT69wH8238zIulIqaL8GkwtarIE2SwA9mstVzBtxuvVJXmcrk4nCAJ9rQ9gbpcuzrQvxFVH1QmNoaxlSyESlkO+oAsKjFoSxXSdGmEhvmcp7mt61tynkop+UVczSUkUqkeH1w9vrN0aV3dvzvI7Hz5O+DgS78QgXiU6pCgSR7Meh+4YVFmg/p5QYYSj7mDhsylnOZFKPBfwdCgLKVgL9moygPsYFfxJ4w/XahF80ywknwG7Zv7k9By8F+98Tk4u3b3cGXiozDi9O3QQrkcw8vyKVfyGFzJTN6Y4MfMqbmxdHzi1cHZ2dHp+dD2yL2eIkRLl2/BBiI4zQYavW7TKPO2Uc0REXDB/UqiN45KGmeEJ1HHpiSd/LSe3f07uT0cneAm616b+4n5dwzcyoEgj3xeLfVhVQRWANtzy8mL2DKi8mbycmHCU12iKJlcahEFcN1
*/