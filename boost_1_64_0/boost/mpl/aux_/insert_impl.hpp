
#ifndef BOOST_MPL_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_INSERT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'insert_impl' or the primary 'insert' template

template< typename Tag >
struct insert_impl
{
    template<
          typename Sequence
        , typename Pos
        , typename T
        >
    struct apply
    {
        typedef iterator_range<
              typename begin<Sequence>::type
            , Pos
            > first_half_;

        typedef iterator_range<
              Pos
            , typename end<Sequence>::type
            > second_half_;

        typedef typename reverse_fold<
              second_half_
            , typename clear<Sequence>::type
            , push_front<_,_>
            >::type half_sequence_;

        typedef typename reverse_fold<
              first_half_
            , typename push_front<half_sequence_,T>::type
            , push_front<_,_>
            >::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(3,insert_impl)

}}

#endif // BOOST_MPL_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
fyL87eG/E/734N8C/qHwbw7/2fCvBn8H+K+Gvy/8t8K/0AEaAPAfDv/B8B+WRgMA/gPhHwn//fB3hb8F/PvDvwr8P8H/fAcaAI9oAMD/MPzHwP8Q/EfA/x38e8C/NfxT4b8S/mfgv9CTBgD858J/8R0aAPDfpacBAP+P7jQA4F8e/nVH0gCA/2v4HwmlAQD/JfC/C/+n8B8E/wvwrwn/gvC3hv9B+JeF/174O8P/B/jbwP9H+OeEf374j4b/LfinwL8C/NfCXw//XPBPgH9V+BeFfzH4R8C/J/znw78L/BvB/9wIGgBdaADA/zb8a8B/LPx94C/8w/8x/NXw/wD/NfDvBf8Bk2kAwH8H/BvAvx38veDfHf7H4X9iPw0A+C+H/3v4t4R/B/i7wX8c/D0f0ACAvyX8R8HfG/6N4f8z/JfCvzP8F8G/mQ0NAPh/B/958K8P/5fw3wb/DfC/BP/S8HeEfxr8n8P/FPyPwt8O/gXg/wj+/vCfCX8P+BeG/z4/GgDwHwl/d/gHw78P/IvAPwb+/eAfD/9O8L8C/zLwrwz/qfCfAP9WB2kAwH8T/J3gfw3+feGfB/6X4X8D/rV0NADgnxv+be1oAMDfZRMNAPjvgf9p+K/YRwMA/tPgPwP+d+A/BP734Z8M/3rwD4f/ZPifhX9H+C+Dfxj8u8L/Bfwfwl/zggYA/FfB3xb+W+AfB/9y8K8O/+Lw/wX+6+B/AP4G+F+Fvw7+peDfHv7b4Z/kQAMA/lHDaQDAfz38Q+DfBv5W8H8F/7zwDxhAAwD+3eC/uTANAPjvhn8J+P8E/5vwf1OFBgD888FfC/+L8P8W/tPhPwf+JQvSAID/A/gfg78f/CvC/7oVDQD4L4B/Ivzt4b8T/vfg3wL+ofBvDv/Z8K8Gfwf4r4a/L/y3wr+Q919edPbRNB+5d3Hhoj/0rdDw94F/bfTUc16pv3Z/t+J7q9vt/d65ql+Fx66cFntkQjkvy5cfzt/tdP73yvtHe9QpP2VR4Pq2Pddc619sS7lZeR963tz1qY+lvsbe/Kle8Ytmtpp84O3pgff9p1jNmPtdwZSh4Tsv9egyo1rCjjOnS+u6V9LeaOuRfOjbAYl79HFDvn0xsEn32VcHba6wodPNHYVXTkgNWaE+tK7hsRHO7a4HjalZ9G4/t84zPUf5BN4YHLxm7KqBW4vPj/80vYrt2+6hbaKKfPScMj7s2vSNb4Z1KXs65q+3LNtHd5tS6nblv/qF5KyYstZqz/oaPw7b/80S23qnn42v6Lp2yc6yWwZYWfYeU+hxleLHJ363bshfUp/lfL7glrbj0ReXNGd32OQoFVj75MRPv+yb51O99ny/5wtr3Zxoo095tbjBo4Q8y5/0a5bj50F9OztGbH87sXQT9xxXf1hl0+Rqq+33Oqyf7DvNps++QZFnclinFfTu5/J+VpGZD7afO9KyWeLgny72397CsHpCUmLO+r2K3L/8R/KQ1rmHL3jg0GL4oZJj30h1SMI3o3O1eVyl1oqofCU7RvcMe5+W92PX+uMcSp5d5V6hQbW6wRcdcpf+pXfoSd9ecxpWr+uypn9uO4f73b4/9cMf636aNqdYp/27Ri9UXwnQth/cs1DR/MVzb/n+1t3K83e1vFGmcYnCxfLnsc+Vd+XBpGebl26olryspNO4Ik+7eeXU/7r16uw/PvYbtejn8havt72M7r2/UYhH7ZHve8VWapl05UDZ30M/PN4Q9PTOpsNXap53HBfUolmZmQXU+Q6MHeHSbtwb962n8tV6uyp8QaWD7Wv8VOK569orj7p8Y3/i9u7BYYV+qzJ7c9Syd22m5ysT/KD1vkkflhZtmjr/QtURXZ9MdSs=
*/