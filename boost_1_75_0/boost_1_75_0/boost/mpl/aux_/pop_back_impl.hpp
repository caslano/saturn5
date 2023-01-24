
#ifndef BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_back_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_back_impl)

}}

#endif // BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

/* pop_back_impl.hpp
hzyusTJw3idI6iLmRHpWQZtd6l3XWuQonL7TdjsRaI32JxHWOLoij+JD15LNK94Qtn4dy467RaPhvMmFEN4mqj+pPrAPA5j1+bGylOT+icgig8LJu8jwUHfXrwfpDaZaZozVFnZKf/4wXAInxyp36HIxGq4HlfTWebcFkfp8w/IXl1FvzQBrhQ3Vo59AHE+37qf0Vr7ft7FAP2ldO6Krkpx1n5MUf3NJ5VP0X2IgL7jh+ibpjgZI+v6s11UyCqU2zMOe5fP/LhKZtcf4wiosOTmDecqQM4AxFeX+UXD0EHKjY802SzGtDamA0kHRXxj8E1+jO6U2i0VLwLngQnAeuFfkZhJKdSpRPU2yhPMaHiAtWmI8RhzFF6DN+jkgUL/0gcX9+YDvFY1sMGex9gbbXeix+Beb0zFfp9HgbqgA+aC7kEjBLsyHbBORbNN47uoFQ6AzUHPw3ulnmfetY9RuUW1jwwTw2F7VYyH4UB9ttdmPcfteLkpJsV4IXXbQ92bNbVP3KlH7IPreY0DPPKu2u2VxycKekyeyxLpe5wfvl6hOtvd9CYbWJHiKA+IrDtGqFS0kLE0uaxD2bO7WaIF2QgN26WhELs3d11jijoGb+rsJLd/IgMEHj13lbVgovnCzb+cf2UQnmwws+7BYmTIoLBzwuVoG3F7opMz3161U86BAtpLNI6mm29OTq89RBeD09912sYvbEkeiX49X
*/