
#ifndef BOOST_MPL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct value_type
    : apply_wrap2<
          value_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,value_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, value_type)
    
}}

#endif // BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

/* value_type.hpp
/vr5XpJfavj7p7IODRxOjSK5p0P6QFjcsWiKbYLUYJLXRurZTPlHfPKpPA4/GXxDPtjvK/8hl752XyKgMKAT1MomZWN921zrgMCMCMWBggzNfxkKnwweGOPw+iC6P7Ix/nTqp9mRWDXd3BwlVEA7i6mFGPoU3yghUakcBl79QOB4vYO96O+NplsfuTpWuuh/oZAkBrluI5uRgR6ixbBKgygH55uq8lNROfstUcPyL/auBk7qMY/PzM7WtM22k6batNVSUXqR6ly1lUrrVlp2qyUuhPA3SJgh7Pa2RWtb5SShEkIIIYlDIQp1F3WuO+Uq3fXfm7jF3lkse7/n+3ue5/+fndde3Nvn5sM287z+nrff83t+rzlF4so3p5xsM8l1krg1l1nzLvr6uZitx+m05JUcLMvV+5WQKeGuYHq10KIEqwDa5DyArDmrKcHO7RO6sUusU2GH67lOCi6ChUed0x5JrBVF8gFu/yPE91IQ5EBoZb7UW4EOeFuAoeJi4Wu4v3BOE9Ayza7oyQvtsD/l2BTMcYxOZnbWdYEcQKfewQs66cuB+VVnc7lfYAlbKY2pZp2kxpR6FZxIx0wY25YJOafwnlycg5RsR2nTI+Vv/dQfjd93H6vxGY759ixtPgJ/QthqPLkFHRTOIluYYMRW1ETgRpTh3ewlrTz21OP5m3rydYGVhngTHMtBbTfnIKgtIXyx/V3wMavtb/R+t4B4O0db41wNQlamn6U7lvw6Yhk7Jfuo7ymmjqX7LHwajOYSU75QcIkLo7Jl+fteYTEtLjb4kqx+UuxKERXSfipo3ujU3KVRP/BzLfBzLeZB7G8FZm2ZAVpbpq/Iseanhkn4jQ4JZmUfG5hgVo3mEu99rsBsq+ZJgusGuKShcFtDw7/VOEzzd6qyJX9rXPleHyQk39tkZsQHwPyPo0sSmZ8i7IGq4EHa+6jgR+L4igx9CdKSYC/UA/EKaQyZMGVryvB6sdVsWdXZdgGR9KhH+vNKUBfMA9etiPxcoKsiEtxwfCjzLqJNeSXaEiAiMaNzgZe+VmTIAA7V19GEw/MG1W+OMRWVD1KBHnKDhy5hOrSPpkc6EEkdaFDO0s0ZJ9pdL5QOxZyozMs4k5zBY54RDUFJ8Uv2YY8RTZ2hHGxoiozaVw7SciPbzwOVrTLTdPvg015eqWLs1e2VjX/bTDFdtDgIFEsm3gxy0noB7zbRrJgO6sFqnki0AK/LT00xW/Rva0n/vJphQ4yIS9UBAUVyY4ZvCRvRtJvCAVPa6D07DFMk06e20a8ZQicD3IQG3saFKfX+r+5pRsov3eFHD3d/WfE//Br/35nvnZtfO0NMvof+OoNtw/2qlDrG1W7FQQwPqVKaOPN2SiLtDKfO7WS4M+TTiANYXC38/zVTT6N+YllLm0ibx2YZ+o2Icv/wqHLNgenqKlyHJ8IU45sL/adWkfHkNcm2RgQAd8KCmP9ZwP+s5H9WMYk7j/9ZzP/IINYrbHZVEPvRDpidgR1AX9JxrGZXlKzGg8knHkyEu1aX70tD2hpBIVAKqXnvrSdl78qSNURBdc5fLXDjGpAay9pIKnKGaHEG76kZFYjvrKwcqIHl4pakv2UriKXbAnYvy/MQxDirqgGk2vIi1eTVanORCfU6ChANW+ft+zqXrKbn8hpOyyucSyqpJesQ/3iunArRQEvkF7gqx7iz1rozKihmeyElFJP20sLg5ZxJkCw0LlHrWSnima8lbgHimc8rylpbuJCRxKwfpKyaZA2rHCFE5L/amnman0oPYBjhqjyTuvMTxl8Q7kadsGAt2EFMmIsBcFUOoyJe8r+74Mb06r8i0D+q5uWvDF4ly1SUrESrYhgrK70=
*/