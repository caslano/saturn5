/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , extent<Seq,rank<Seq>::value-1>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
JVpmSCJrNjLOnQVlDRsa20UD7QHQA7GNPbzWpV540uN07IW9azd0Ma+qjCqvY137E7+rpWq/YA4hjsHAARNXmSrx/U7uYi0IJ+Grzr6sPU6nvRfT2y0L7c4xMV+14OngWZQRERkX1Ru8Bn6NW1ZG1cHUvllScEmaNXsP1nP7pCAxW5d7+wfLyahRoPvV9QbuZ2/ghTPLTdOqc6t3nDEY98LJ2Iev7mDSs8ZGWdJU0ouGt3jSJs+nLpHrsuQCvwTV16kynPi3/nDq1wVrJ+TRsf4DUEsDBAoAAAAIAC1nSlJUJfeFhAQAAMgJAAA1AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9USU1FQ09ORElUSU9OLjNVVAUAAbZIJGCtVW1zm0YQ/s6v2FG/SB6MZLutk8bNlMioJpFBI1BSzWiGOcEhrkF3KndYVuv+9+4dWLIdd+wPQSPuOHb32ZdnF2fRgaPvdlmONgcvXon5J3jheq80qcSfNFXPKyTJHTQ/VFzg+gqoPhy07pIevErrDrpGK2mxLvQ+SV4Bt9BO6ltfKy8SvcWTRrPVH4rNrmKrQkF32IOTt2/fwDGcDk5+tuGScEZLiBTlS1qtbLjIzMlvBbm9dSR9bwNVQErn
*/