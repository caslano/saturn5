
#ifndef BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct empty_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : is_same<
              typename Vector::lower_bound_
            , typename Vector::upper_bound_
            >
    {
    };
};

#else

template<>
struct empty_impl< aux::vector_tag<0> >
{
    template< typename Vector > struct apply
        : true_
    {
    };
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct empty_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
3JjYcZ2t/vRZNnp84ukI2/vF9eVP7WAHOziW449c/Wmwt6/eYIvHg0N76uFHIpci5/lZUAZXIz9hw79698TXnw2KMLL9aOQR/vGZExP7fxwpu3HjxqX/lw7bDfYfiVz6Nef1n+M7IvzqxMM7rvDzHRPXr1M6z33urn9FdlAeHO0vn3324WDrOyL8+Y2JS1+6/sTVx9lAjP8JcmRZyEcRKlCHVvQjnsqSihzkoQoNaEE7whjGLPqsbASvrS9AMZrRhiHMozNdhlzkoxo9GEEKA9M5SEUmclCFBnQjjCQaqwVYjGysQQGK0YwBDIHhfUw5DyLVoht9GMaseP4eBShDDXoxiiChMw9pyEURKlCHDowj/haOEzkoRAnKUYVatKAbYYSmsi9kIBsFKEMl6tGGTgyB7iJmBnJRigrUoQeDGEcKEzvpyEM5WtCHMYRezH5Qhhp0YgBDSHwJ54U0ZKEIFahGEzrQj0GMIyWJa4AclKMKDWhHGKFkzgsFqEEbhpD4UvaDLBShFNXoQD/GkfIyzgF5mJXCMaMYZahBPZrRiQEESZNEpCEX+ShFNTowiPhbqS/IQR7KUYt29GEYYwi9nH1iARYjA8UoQyU6MYAhBJNYiViGXFSgCT3oxwjSZ1IHUIVatKMbYwi9grqKDBSjDJWoQRs60Rs8iPhKdoVlyEI1mtCP+FmUFzJRiHJUoQHt6EMYwwjN5tywGNkoRhtGMeNVXBc0oQM9GEf8q7nfkI5M5CAP5ahCLRrQjj6EMYxZc7j2KEYZKlGDZrRhCIlz2SdKUYdWDGIc8a+hfiEHVWjBMJJey7GjAGVoRi9GMWMeZYQsVKAJ/RhHyny2hRLUogEt6EPodWwXs7AABahEPXoxipjXc7xYhizkogLVqEMTejCOlAXsC+WoQgv6EMYwFtxGm4QyVKIZvRhAzBsoEyxDLorQhFb0YBwpb6RskI48lKMWDWhHGMNISuVaowBlqEEzOjGKxIXsC2nIRQWa0INBpL6JfSAP3RhG6M1sEwWoRA3a0IsBjGJeGsePXJSiGh2IX8SxYw5SkYk81KIB3ejDgrdQPihGM3qR+Fa2iyzkowjV6MAIUhdzrMhEOdoRxjDGkLGE64lmdGIAMW/j3JGFIlSgDk1oxSDGkfp2to08FKIKDWhHGKF0yhqLUYYatKE3PQhWOXakYRmykI8iVKMfIxhH6jvYDzJRiCrUogXDCL2T/WABFiMbxShDG4YwbxnbRymq0Yp+xC+n7DEH6chEIapQixa0ow9hJL2LfaAMbehEzLvZPtJQgVb0YxypGZQPSlCLFrSjG8NIWsH9hcXIxhoUowz16MQQRhHzHvaBLLS8l7/HrEz+FmtQhkrUoBltGMgMBlqUNdKQhXxUownp7+N8UY4GdCOM0PspT2RgDYpRg2b0YhRpWWwP+WhCBwYxgnGk3E65Ih15KEED2pH0AbaPAhSjEvXoxShmfJD7BEWoQDXq0Ip+jCMlm/JFOjJRhRaEEVpF2WAxClCDZrShFwMYwowPcR7IQi5KUYdW9GAQI0j/MOeAQpSjBe3oQyiHc8FiZKAANahHG4aQuJptow5N6EA/xpH+EbaLEpSjAS1oxzCSPsr2kYECVKIebejEEOblch8hFxWoQys60I8RxN9BmSETOchDOarQgG6EMYZZH+O6oxg1qEcnehHzccoLFejAIFLXsE0UogotaEc3hjGGWWs5D2SjAM3oxSgSP8HxIxdFqEAPBjGOzE9SPqhFA1oQxjBCeZQRFiMbBShDDXqRuI7rjGWoQB060IP4T1H+yEEt2tGN0KfZJjJQhkq0oRdDSMyn3mAZ8lGBOvSgHyOIX89xoxDtCGMYY1g=
*/