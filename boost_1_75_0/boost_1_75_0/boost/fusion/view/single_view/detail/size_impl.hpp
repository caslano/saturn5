/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM)
#define FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM

namespace boost { namespace fusion
{
    struct single_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef mpl::int_<1> type;
            };
        };
    }
}}

#endif



/* size_impl.hpp
MglUl4b0RuEO2y/7C16qOfLZ1Crdj1iH+61qWRfYSnvtyRD04J7+QR1gQRrFzn0YdUU+0fMN9qCeXMo3glGMrrklk4/YDfT9JC366fmRWnkacGLSoVrqVsDmgM4xEwcYJP4Lz04XV7w33Yx9UIVwfb+MV/2DN8MXLwH77hrmq+rllTZhDrAhCvmYVbrp9ATBOQ9uIZfPO4A93+XTOZ9NPqIPsyt2scgvxFcj43feD9CaRBQ+a+5XqwJ+n1F+LLeHaBM7Tf6mzOTjxMC6bJbS8e5+vPn+rrprQ5KyTfvbxXzkD1rloDwpAr8Z1AK1ATAST8lnFM1z5Bt11uuklzfd0PLYX/J/YHsf324tP3EKanacndx/AV957uoWsPcYz9+G+ebw1vHrweCPAa4tz5cM6STTDWEG6pP/tJF/TwcI3f1gM8egIwisfS4fnBKVbsAUsBhe+fXGMFsAjCBU9cpDH574F9DsVbR6f3tQw6cyZX6fNVz9AlkNDwzTJbbL+xuCas6qDBA8P55ng09NroJIhHifWsAm/zznl98CzpRV+SYyeNNh38iRlVHKux6169TgGmWITvnIPYLkdO1puHt/Q0zyzPPzV4aZ4HI8HF1JY/pk8hF1nHwK2NApBknPbB84MeidGy72iJ49MKTu0hh1tz7N/TALE3gW+FCaQzNQq2ePBmW34M5ZdK6nAB90yjenG0LfCwxNz8FPFgFm
*/