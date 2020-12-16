
#ifndef BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED

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
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {


namespace aux { 

template< typename Sequence > 
struct begin_type 
{ 
    typedef typename Sequence::begin type; 
};
template< typename Sequence > 
struct end_type
{ 
    typedef typename Sequence::end type; 
};

}

// default implementation; conrete sequences might override it by 
// specializing either the 'begin_impl/end_impl' or the primary 
// 'begin/end' templates

template< typename Tag >
struct begin_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename eval_if<aux::has_begin<Sequence, true_>,
                                 aux::begin_type<Sequence>, void_>::type type;
    };
};

template< typename Tag >
struct end_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename eval_if<aux::has_begin<Sequence, true_>,
                                 aux::end_type<Sequence>, void_>::type type;
    };
};

// specialize 'begin_trait/end_trait' for two pre-defined tags

#   define AUX778076_IMPL_SPEC(name, tag, result) \
template<> \
struct name##_impl<tag> \
{ \
    template< typename Sequence > struct apply \
    { \
        typedef result type; \
    }; \
}; \
/**/

// a sequence with nested 'begin/end' typedefs; just query them
AUX778076_IMPL_SPEC(begin, nested_begin_end_tag, typename Sequence::begin)
AUX778076_IMPL_SPEC(end, nested_begin_end_tag, typename Sequence::end)

// if a type 'T' does not contain 'begin/end' or 'tag' members 
// and doesn't specialize either 'begin/end' or 'begin_impl/end_impl' 
// templates, then we end up here
AUX778076_IMPL_SPEC(begin, non_sequence_tag, void_)
AUX778076_IMPL_SPEC(end, non_sequence_tag, void_)
AUX778076_IMPL_SPEC(begin, na, void_)
AUX778076_IMPL_SPEC(end, na, void_)

#   undef AUX778076_IMPL_SPEC


BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(1,begin_impl)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(1,end_impl)

}}

#endif // BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
L257J7x8+JEQ9Q2uRn2diSWKpH+994vI71f+I+R7X4xdVkw6vZ6v4yBGuvDy3zJ9/pnnVlTogz/VyLJxLQ/Sud7fL6+8gelhJIOzTunoBL31cf0EHtp9vDFQb6CTtrO/sY68U8o5As9rCR6fZ1vo+ZmS4Fn8D3HWdLMjog0Hdi/kRtymlkapJTbwZQv5t6lu/R3ojZJiU4xVWCVIHO5y7V+PIwBdahSUoJYKEYDjhGMz/sWeAEjeL+GeWyirOBqUwC0S5IkEqwtlFa/qBLWVjczdxhrFCyy03iozmXRjiyp8ovVWTe1FRqxTdT4bne//Z3ReVKY0jw2OSs1jII1hhMrADwfpLF7EDko5A3NWk4/WF39F3KhdxabVFuYs2vZqqlsZ34sJPb4Kl/8VzMjeUqxmm64nUDbLNX8ca/441nzuOfI+cDypoCElIxNNXvdz8MIN0D5Ts9cau0/rp+HWbAx5yVKI+Ev0bMjXgfHGUEqgAlvuC0rg4Mms41QdmKA6sOhPasZsMMUnbTDFJ20wxdce5kP9rliNJo5s5oxZSjw/VuhfccVs8bFsAYFgi6PTaKRqB5q4akBjbgDarQGFT9oAhU/aAIXfPsQNKBZFlf7QzCOz2fDCTW4TKUmTdnjdZLGaKIcR+xGWtQrQGnlj0007CrtJhEqVUC5KyP2hAyFKn6Pb/ryt7beeqEHb68i2n09FaZqIhmDAhc2cHUK7nN7auhhLN/jgt0dVM49yR6mVF+lWrrC1ctMXNWjlmIPcShHUHUrxywv6lPJVbFCZWlJpxhXOKlvhBq7G398hwNxF/VdxImuZnMdOA9Ltl4rpUbWYeFlMLBjHEzQ9gHI/IU6rjmCX+A59ggYhg56lqmclRl9VGnTeAz5EZVDF14IDQZrRr2p9T3/O9T0Zw+H5ISHK2CS7Oq25ka7zZKk8ozlP4Hah3WfFUhEH42gLPsEDWeGgqpWdLzOeBzqDCsnV3X+A4hgissg7vym2A2CXBc5BqU2/wGOIm/5ejO8QN31Z/O+X4vz3fMR50GZlpXgglX674f8TEPyAkC0ZaS+kAfIZ4MUsAskGdgl7gfag1/CyA1VGqB/g54XxAq2Zn7Noz5pK7Sut9DsF+F9oL7uxIlyVjJN8ObkiKC+RftREIXpLgxocRtQKsDArUQMWij30cIwiMiOpd+bancqOWHWlRHaFslL50uehHx36wrKoqpE2la+MtFH+o7r8rqup/HRVvqnKN5V3C4krWst6mnFpaqDNeevZcfFZTipqvhlJHdk3clJM10n+Yo5Eci0HdAMLuDTQUhvf23Cjzc5ILCV5ge6yJanSvDtZtyGB0wWaBlK4HFuFX6/DuxrM9ul/xH2kdomyP3mKaEdVPEx/gN6bo0PdULCe+mH9E4tbmWHZp8X8jKGnIeb2I0iGW2A7NFBi178pzBZiqsY7LPK6nKmk62PFVM3jzGB5fuRMIeHz2HcpVcGHAViKAzmezFCvP6bXPMecU7/Yo16UWMaCVa0EC/qcyKBw9szbJKdANVVAgQ85cHsJta8xnkG6S+nMRNByNxvh75FG+LNUb439L9Livm+7XNzC/QanHMyyDr2isoqIH6xm2K6eTYvzD6euiXpwzhWqF1PTjIVVB/O1j/h8O88pQRbqmX12a3VE1tVgxqlv5r2HFb/Wni1dzLv2qSdNJCx2hulZg2fKFC7NeN5iilWVvWWVmx0KscWk4VkrC0uaWc6e6RYudQJwqe/yg7Ss1QW6zWf9kmEogptSmvGbqrV98EeurR+EXUU0gCIAZBFM5FxUjfK9KqOX9CTQgp4pMeyLbNrFT1SOEtEwO051vQD1v2RvTxcmsS6loNR7r8E=
*/