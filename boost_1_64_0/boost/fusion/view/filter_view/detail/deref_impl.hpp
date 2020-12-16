/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_05062005_0905)
#define FUSION_DEREF_IMPL_05062005_0905

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_deref_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<filter_view_iterator_tag>
            : detail::adapt_deref_traits {};
    }
}}

#endif



/* deref_impl.hpp
hPL0Nr2wf505TxT7JnOUChhxuQcUD/snZnTYN23oiR9nbuEl17wmN/dNX6DTpL5n9sknT3Gs+8zddToihOyfDbzee4PspekWdpjV20wbr+MHpzPb4miKuZ8Ejh5TcI64z8Aa+57lfhPbVfZj6MsNrE4UfehNB2p8a4sY4z5y9se8bdwo9eI8vOb9K/3NO/9j/s2zbct38+L/7ZOH+jn4E6M8hShD1wkDV+gPDz4pjr3HJ6W+D/8LvZ4345PXDoNCvldliTqaCLneRraU+dM6sr7OUeQgqP71r0b0sPHfD9dxxfgTEEpKf4p6vSTHolCdt9I3Y2N9c32k1vjARndimHKKeacaS9ty8rMH/ExLVsLU72q8bMvrTy7ieF4rDkVBHMvtONRwZsZxth2HomBsovHl+diDqD4A2OeeZpjyTbdzugPZ1zGc2zv+hWPDvmknNNPEutsbq4Rj36LGeyeHtHehh3CMDb+qcSrxlrmPd3GfDt86QhDy4u5n4YOekdYPDGyjX6HsbONAhSsTgJ1x+X7Hwiknpv3UHMNknSK+zvUqTPuDRj4QThuNo5FcDQ6f3RtA7m03AC4/4Qj/6A3r8NXdgZnvQzeqw1XqRt50uGzNUxu900OjzUxMveI9BLZxYwNrnIf/QGPrQ1kRskFRrsFNgJGCnO6NaMbGbF8NfHt1FeHuQSN8qz/ek0U49ALY3W86xp7T39k2sddobKNfaY2BDW5WY5u94TOqIQD5mLt5hSntNmUQTj1KiRg2Xg2szilk125R40M5h+2rqGEfwzByWVVFDtmztwSuerzKE+zmNYa2RbznTAwNYdj83Bp4q+0vAkPbo37EbTRG2mrUQXjbOny0bU6xIPc7je+qjoC0vnS7OlydZaumBxbevsZom2+tKiCwn2lMNny1vYm9QfcOEkPnRx7/KMPba37E+cU7GngFQZbGZsLa57Kwt7+zwrHXjzGThx8x7ZwXDzGMZtv0iD5sxSvO2l0qjurX3XF/uSTDcV5q1Nld6/Bn1xnp8Hnp82SdPWOH6plm3TvGHsslfe7eR9mAfbvC1FhUVQz2MIQpNxyRmq1UDEP+isGpwS7WSN/VGFk7b5/q1rZMqzjX/1qN93Z2etd1+1Q5ea7v7P+ow+6WR2GSxrFzzWfhpo3cc1labO2kMPXQp7ys8+zc8s158bTGUUfA0pkKU2Pp6mbvjCkHDPU+7qOzBtbQx5dqjOpUmsfpARDz/H3A2+2i59zgtNO+xX5grbQ/CMxsM2POztolFo7nZW4e2NfaLreq7Ycu/1DGt/SY491RdZfFOCd8jppX+Ec2q4UW8vjKKYbt7BwZbG9cZ5Rv2sTVkoOtsxgm5Q380GwTp4N7o+7n9k3AG3H8pcWh/mrE8ef9E3AeByXU5Kxvmfl4w/XbeDMfoxswDhZ8WFPecAJexYF1/Q1v3OQMtzee1aclnppb4Zyoc5O9eSpKc6/7oMnFYhP5Km86AW+UbfFmEzgj4z7XzSfhVSRoJ8aROnSkwvX9p1sQTn1B4apuDp853AFO3+gmfuSM/Ahg/Hw5jW/qng1xqibSZrDoT+d/2FgD50nkJFlx7f1p/B24Ts3tVqh92P6PCm/mA28YTLdx2tfrniSjiZU1fLPINkPy+rsrG+tsX+c2+yj8H5T1zA8b9j6p7/hpeM1lNffEzlCedRc6Ui2HkF7YqNs0ctIij685PbNun03pybTYvslUHY6ubszVpjlWZxH9622zE/DxwgH1e35/m6cncOhXc5xT2xsBv/v1G/iQTmU2+rhveukGEs8Kt+udkLZMUeZ1naJ8Qtc/XmTd8rhHFsrm3dhv3mgP/nKh2egrl28suapcPcq4WhQ=
*/