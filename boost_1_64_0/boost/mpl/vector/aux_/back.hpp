
#ifndef BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<
              Vector
            , prior<typename Vector::size>::type::value
            >
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long n_ >
struct back_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

/* back.hpp
nFdbb37jsM+NbCm3P7L+7v6KcdKdvh81+j4gnw9d4fqWCfN+jc4PbHD8sct++JjtyKpq67PzAGvvtF++aH+2wvlb87oJT06OE7f/0fHfbyfrz/Qe47J084fO3+2xHA7esD3zvd37V3k8rr+5w+f4T35uqnkZ4x3Hk6uM2zb4OfEV86q+R3/d172Pfe/eobmWS9j1yvaXOx3nnjQPeMdTlud266lxx0b7h9N7zCe83fc57rb++HzEtVPmme9yHLbauG/N5Hxi8oPen6+1XzHePNDl7ydanz5jXuynxukvNn52nnf/w9bDr5pXdbzxzE7Hb6+3/7eenfuk7bPjy4NJxvlvNx7aan161PbW/M25x+xnIt6vznMddP3fbPNx195uHuEl5lktl5MZU21PHddWJzivG/xeUB5+z7Rx3Ey/L2PJ3KmTzzc57p55n/kf1wFtmmp9eJP92Be9ro63NjW6H+OJFXONF213uswvXhk0zrtncj7vtojzEJb389TnjwT1osr5pQftvx81Pzdq+32P5bhsMq5fZzx5pNx6ecTfd34ldq/3QXK8+R3n3zOtLz7vfehdk/OgF37rdU0wnnPd+MU0x6vBe1uCz87J920uiq7f8nwOR78HvND5P9vtXb4XYJ3jmuTCybzXEvuPrcX2/47jdhtfPzfhOOmy40bbq13O1yy1/Vm6znj4vHkHy+GOe61vV8xX2k5M6/W+e4P9eKX32wbj/+Dvgs/g+cPg03b57Dzj1m/63KHjlnXlju8Zx40F76uJtr/33jRZv8yPHTUvfLbSdYKuHzxtfmuV/eXWVQmuP7Lfepf17+uWt/H82hTr19PmB95q/uQux1u/iJ+MN27c5Dovn2O0f73ylOsYLjpuj1i/TpqP6nIdGfM+98dST99lnvKQ8zlN3ldTLbe/GIfZH6y8I/r9jfbrzquvNv9/8JB5Re+39c6bbe8znm31uM5bTt6n+z9p3Gnc+9zPbB/tf/cYzyebV9tn+Z0tMS931fvJ41nnOrcj232+9Cfm140HzpXaXvk+hV22u1v22y4WO29nnLPwXvOpnn+XeZNpxs3Hbf/XHbM/jY5jbnU/tq+NZ1038WHHv583/rA/u835s0Xmny980HXWrj9aal7nKHHwsuDvrK9H7nD82WweJGx7u9k4bJ3t99usD/bns6PPiVi/9nzKeWHb9+VnjTdsdzY+aL/vurGlnebVjhhPFnm+7zeOLTZPFeu460HzU3+yv/X8rz1pHGT+6uAp282JOPOajptjPR7zDSdLvG6e/3bHhwnWu/mOO2833j30ActhifUueH9G8Dlo/Hdf0J4H7wtz3av1f/YL1oNu499M7yPbgXNLPd5N5pneHF3/7vsgtnjdP+RzBScch//c8/e9pl1Z1gfmneKC41znevKVzhMYL892PLTKuHZrkuNy800XZjveesB21/W6ye+anO/dYHsxzbxpY6vzf27v0HrL2/b5ZJr34x/M177aebcdxh3ptlPGXfv9fobd93vcD3j/OJ+X8CLzz++1Ha80f/sD2x+f4zu7zfHCgx7HZuO6MvMq5mNWxzleyDTP+iPXB37YebSq6Ht9bF+mWu9tL2I/avxRalz1HeftzLssMt+x0/zpkYddX3/K+P+k67vNVyzdbRyR6LzZNMcdlz3/O71PBxyf+T2AcSe9j8xTnzQ/GltmnPxv1+GtMm76ke3uhOU2YHy63nyA+93baFzh/N8G4/ULf3D/rpdc3T/F9tZxT595pHznP1c4/+X4djr1NiG4zuZN9hTGm68zf3jU+9086sZHXGf1mOXtuHS2+e3ptpPnuv33b3o8nzQfZjt2wfH4FvuBhPPmsb4fXVc=
*/