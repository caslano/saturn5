
#ifndef BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
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
#include <boost/mpl/set/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : s_iter_get<Set,typename Set::item_>
    {
    };
};

template<>
struct end_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef s_iter< Set,set0<> > type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
XQXGh/HzWa5/GRgLPgf2B5+n3nJQi4Fkm4ltqeaQGMgjsVwMaKV/s8E0xj6O5vcM8CgwF5wTWC/bHuDoMOs9m/6dw/11HjgEXADuCl7I7V8IjgQv5XpzJLYzwIQw77S4guu9i9t7N7gzeA/LeyS2G8AClt8RyS5p9ihjLB8Dt2dsaxxjWndhLOswxrDuwRjWceAL4D6MZZ3KGNZ8cAWP3+skthnYlmjmfltI3XT4ty04EowHR/O4ymA9ZPL8OB6cDGaDB4A54HRwH7AO3BecDeaBDrAInAtOA28AS8AV4AHg62AZuBosZ/0sktg+YLuhme27qyTNahjreghjmQ9lLPPh4DSwDjwUlMFGQ8yyEzwTbATPB93gtaAfvIsxy0+ALeDLjFl+AzyWMdongHHgMeBg8MRADC/vqcHhYY6z67g/rwct4E2Mmb2V59HbeF6/k/v1LsN6O7nenDDrfZXrfYPrWQMOBd8B9wTf5fn4fTAb7Aysl/e6oCvMeiX1OADAwWBfcDewH5gPbg8WgDuCR4EDDOebNq63JMz5ZgjXO5TrTeJ6k3lcpYBjwVRwPDgcLAT3MFzHU541/p+Dr8c78zwxkOfTQeAixiJXllkCz4Fx4rMx7nghvrchJSH2eD0YV44YX6QGpKuQHkGqxG92pDLE3DUgGWPxOsp7jlFea4jJW4L1jCnSniWziPF5XViHMUYvJssSiNMzxisvRdJj9GIqgmOUEyqCY5RrkEZUdMcnTxkXOUY5B8sZ45Rr8N0Yw+fE93XgfHAJ0iak9AMRp4jUirQYqR1pI1J6JdaBdA7SEqT1SIkHoe6QPEjXIa1BipmOekAqRJo1/f8V7yxMmLBoxv83YRF0ajXVatH/fzIGQBkTvy5RCvTJ4j5Ate14DerHcYbFbwT6tihvxfCJ1RbcQ9tzH5exr7s1glZbJK3QEZRe9EMb9boi6K3sWc8u/wG95j6b6w2DXmcEvdBew63pZ89EsiqracQAQMi4eWzf8H509dKPwMiCSf60hvEnV2kArA7rD7pC6/TOUI7mNHqcsr9X9aP2sbGtfZ7a15Vy6Zx9nKsHjP3Bt/Or5151bpbeB8NjnH5JofdgdHsgqB43oF6ubQvlhrFcKssNBwN9Plsol8Zye7JcuqFc5xbKDWa5RJYbYijXtYVySSy3G8slB8rBVkcuN5rlxrDcWM6HXTIDc9aQEqow7wNpPtKdSOuqxP2QMGHChAkTJkyYsP+uxSDVmtv+1+L/0ST1zfG7PSbMAzAjrv7lRCkQ/5HEdu/EbbRxxHHgNxloS7ystCO2R/tOD2RXn/6mtuHG9JXCWOxmseJKVJYES0Xer3zO2TybD7VR2zR7NgJIPUqUoEuLK2Fc73NB8X6MVPdpv1+H358J+t2LWH+v9owwxooU5PEZYYxT6kDQyRO5ii9YUbOfJbRndO2wQmsrpU7Svmfz+8pc7Xsev7+oP6suJPY/jzEzU5AK8aVthbFNPFtGu7gB0e3zEHMOIKqNfS4lW44rUmPIxmF9jIbiuw80n96iT8V5wXFOCRHa6XGvRIjPg1e9iXOiRlBM/8nc7hP0GOFgDZ+10eZCdBl6fjye3sYM9RQD7pGZzXpIVzUR9wTvjbF+U2LCv9diZZCPPlnpNWmwuexOuBkaFdubvgrFhzX0YWVucF/SWvpwBM8p1UjTlD4cgw+90e9NnFI7tAP/Elgy67I0L/z/xPi8t8MZ8z+AddUfqW13rG+l5ie87P6vNrjdc3pRL/QL80K6Y4D/KfFT69U+pfYr7j7g9viy2N+e//qgI9uuKRPxU39l/FT6Nry28JrTDKZq47CqncB4g5PABPBkcAh4FjgcPIfj7Rc=
*/