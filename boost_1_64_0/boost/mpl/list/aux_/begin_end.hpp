
#ifndef BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/list/aux_/iterator.hpp>
#include <boost/mpl/list/aux_/tag.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_iter<typename List::type> type;
    };
};

template<>
struct end_impl< aux::list_tag >
{
    template< typename > struct apply
    {
        typedef l_iter<l_end> type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
++yTHPTZp1jKVjdJVsYWV5bdRO7t1VcWKG1XUK6H7rO9M04bl60sNWiQITJyoGHQUFP/8OPf/7Tu67tHOYxPb7cP75ZsB7n/qasz3xds+m+iWWDqt5Y6m+IhlJ7C0Hjn+zCidfvCIBfTfcZ04/L5jmt17zhJfr/9CwUUFJW+9X3HLfXRPvugqsujxznw+lrft376pKVvfbPyb1OfudrvvUbmafvRy8g8bT96Ccs8tW+4gGWe2jf88IRtf3uGZZ7aN7zDMq+OWhfLPLWfOumE7XMYmnyl9mery3v1S9t+5Z4yzzzuQhF1umGW97XMxlW4Y7Xv3dfve+r+qJQRouwc2r4Y6T8uKvetz5dguSzYfM/+MPuqD/tHJNM9lPXFUnJPO4a84dEEI8WFxg6PGBQq+7mar1Me0/nGTWk7TZ/QJupmCAmJtX7/GN6v7Cyyf6h9QZt5fxh1kvfr9t37su+Gk+T3ncZ+wGDN8a+cqJ09hgxory21v9UPljEGukrZnaXsjFOWsjmpOlWu9dj+d/La72uMsRybf8vY/oeloGVSrxTj+AqYptbrLx3bX/rQLNtKznlX0vR9SDmPm6arWp0Dk+USdy5lFhS38p7yZyzrExdvUMfv98nCOTDle8s5r+336vlDPedt/ac6Tz3PjPlOPaeo7zt01jaW5vgZzXgvMi/2jO25Z66pXIYF4XhmerRMJ0bE84jl6BiXTNpfPjus21rt01JjCqXtVyrvHyjPY2GBnWjTLfxd6kodLTEwYYZhEZEjLbEZnt9J3525b++f+ulQacuVMj1dM63djv2kb/5d2S9nmftBj6nb0dQN+gT7ZVbH0HC0T5a12icbyHT17P6/v6X/b9oMZX5u75bFGyzr6jvz5vqSS1o2rf7f1f/Xx0W+o2CI3Adyw06yQ/8s/TsX0B0vYn68jL54BZvjVeyE13AgXteMQ5Amy29v5z7TGbl/+U+sht9jLUzHRngOW+EP2AZ/VO+/yncQ7G17/5V+EJaLJbAslkRfLIVVsTT6ow8GYBnsimWxO5ZD6S/k+4bj/sJfpX1uoBvetNRPvkuwrnbqd1vu991BL/wDy+ADrI4ulF8fXLEh5sbm6Cb1dkfz9kuV+nW3s/1ySDm50BtzYznMi1XQDRuiOwZgPuyCBczjpbjK9bxc3yvLD1O+78p3kS6y/G6yHt2xNPZCX+yDXbEv9sGX0YD9cBj2xzE4AF/HIEzGYJyDg3ARhuBGDMMdOBj3YAQexiH4BQ7FExiJ53EYXsYovI3R+ABj0JN1eQVLYiy2xARsi8OxPY7ELjgKu+IY7ItjsR+Ow0H4GobiBIzESRiFr2MCTsZR+CZOxLdwGk7F2fg2LsKZuBVn4T6cjd/jXLyM85B9w2U+5scF6IsL8XlchO3xPXwRF2MPTMFwXIJj8B/4Fi7FObgMF+NyXIIrcCWuxI24CjfjatyJa3EfrsdDuAFP4Qf4M27EK7gZb+EWvIvbMCf7znZ0wx1YCD/EkrgTK+Iu9MXdWB33YG3ch374EbbAA9gOD2In/AS742Hsg59hfzyKg/ALjMRjOAHTcCoex6X4JX6IX+EJPI2X8AxewR/xBv6Mt/AK3sOrmDsX5z3MixlYCG9iEbylPoNBvmPIdw/rZzAUluOpKHqiJxZHLyyP3pr+hgZYAlthSXwBS2FPLI1BWAZDsCzK+UK+Z/D9w8754nc5H9/G4ngHK+BdrI738Hn8A9vjA+yMDy39SnzHcNyvVEDOy4XRBz2wHhbBhlgUb+BcF/lOgMtkOR44VZZTQdqpInphJSyDlbESVsHGWBVb4LPYGmtgB6yJXbEWDsXncCTWxnFYB6djXVyEDTAFG0o70v8=
*/