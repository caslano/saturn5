/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_10022005_1617)
#define FUSION_SIZE_10022005_1617

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct size_impl;

    template <>
    struct size_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : fusion::result_of::size<Sequence> {};
    };
}}

#endif

/* size.hpp
LBxLdVLU822zuem90ru3C3H1wgtryK0QV+9JKgQ5ei/f9u1DHHRS9PtxJg/rFtbVJ4S4HeIIuzwom7bLc3cIcahjEQd9L4uTWndt3THIC8pfu5PmkiEfn2anfGFfFDI4MOPE+1xZXJhyzB0Vs7heAYStv3PxvOKuyLsPDql0sFhwSak3W+qa5xcFbNNspXCxL2R3WmFx4t6UxHz7dM3xY14XOqpxv+Rv92V7TMwYDgqCt7wsJ94TEWqPbC7aA3tISpY7ZGud63s2zEuSRH1fQreZG8FUfPaSFm90V1sybrar68z1rFM4F6Ixvdav6bS76+1VOn7F+DPUtzA00VbvPZ/FaVkgbYidDI6zRyHjs3Q+1At5DY3x11VbKbnH5Cx04WYpPNYY9wPaohDk2Pe6e5aX3JDegF4ZTqd1Vs9/7PM0XKp98TZ18+ZpvN8m7yndwasS7GA+yORj/bDC69wU15unvjueQv1+HDaGuyA76Y8nYDt/QuH6DZ+vXgdYfE3xfHUGasJ51F6J9qXnUJFLDz55g1O9y3P6IXxSvAvyqhDuT2ALOQqvTvOop4h8agan0gp80+BOU1mOidcaXMsB+/AA8xZq1Xo0rHO8bfuxaRxRuzXYNYYTVwrW9Y+zOO6WFGcPNzN4g5gI3sjwsNOsJdObfHwGz6cIX0aQ57VTjvVPCPIoU+H7CXNo/8JA9ceC5VEDiXeQ3ob2oyixtsn57LjkWB/llk7D2u33yUsct/DL81DjDI6ZY+6bzaNOD95uFs+bEEjvfmmeDiLCdtqPFztT4HepNSTX+zj9NW3+rIzY16K43kRxkgr/9aKsX/gsh7BPVP3HPkv0CZ0+ZPb+n3Pwcb9dpqF9m7sqDT/QbBx3JWlhHDhuOew7FGdwP3MgxSMf8hodwRB3QvRMWtG8Zd7P37I8V3GsAwZXKnUOfWnF8lilmNcL85IOfA72q+Hpeh+IOWt7H+5ArMnGLcPzTcBnGPJtzbH+Ps63Zrl+8o2HS9gHhgdf0zr2y2rdcRPMGfjMFRbfDQtb4VvXEhjm0A5ssW9bnGqH7cgfKhw+P7SDln0Qagfo+JFrp7moX4zzZcMJ1tmW4dk621R9Wvvn8ksSg38OeO1eqlxD/5o68G39PXxw8HHCr5347XUsB3PDgRCPaHIvg+HomAzK9OBrG95Gj+eYpsHjMQg26K3SuImLrGCPX5Abx7NWotvMZpwvt5Pwd8J87wOa31g7ru/pyV3XlNn3W7ZbC4ZjYhx9zC2Ga+Ic/UTWseEGYx2QY/J6hm/iHZgrDFfHPGCbrpn66gzlfUi2LV2/b+NuWFvf1EfSzcNl2Lp1iK+bB/7DT8J2p2f49P0/NY25Nga2bbA1TvNTClP3iuUVpt9SHD8tD2yxulCSB0sIXoMN8HTL80ZYDzZriONKEIcY12CzZvH8nSDQ+WzeRr9PnoX4ffXOVFKW/8pPwl5se+SeYb8RyxTIkt+P1/ZPlIk+UMjk+zNMQ6o7ecfUwQy+P92CWEJmutRRnGHdFmejQmni/foBeJtI0/Bce4BXuGUmr786EO+e3TqLh/oHt3C7MFestMHdzZAzKk76rf0Mrrd0HRltO/HM/bix0C3RtpP78n0DE38qqY/9+TymCL9/L/Mb9E3MJVsZXKi9P1MPXcvgx+dIckOMgfvyaA7tDaPYKOo8xNfnG04ldTL5rExuz93p48/66XuAs76h//nmhyy9bC6GAdRfFne12z290fO9hf1D2/vzfW9g/m4Wf31jjbst83dub/mJC1/2C9hK4fRx4z32Hzx7X567nOD+iIEaLg4K9sF5keUk96KgrkKc3ka/R0cnKL1TlPNQnRl8ieX7K7tdrZ4=
*/