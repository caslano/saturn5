/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_BEGIN_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, (Sequence::next_down::value + 1)>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
U7wMP8Op+DlKnyK5PlfrJuet8xu3qo6nk/j6y3hz47i25w3r1ch63epfj+tX9+JLdHO9csN6JQTjel0N61XLet3qXU+uo6BDvesRprgXX+IU9/JXLuv1dbGejzZ+sMFxgn0WeNP/y3mMYALLLYTNC7wbNV7w1x4reIRgue/8xwpeiHGCjR0jSJ+3BscG7qT8XyScIPhc4e0VSoglpBBshG2Eg4RThMBU/kbIIWwmHCCcSPX0qfO8PC/Py/O6EC9vQsEv1v5v5b/ah3Rm2krULgDn3wfgrr5e+nNGjshv5jhp+4rBXsqzVgZpbV8zU2dMmJ5qK0zlX7MnzJg8cW7q+KRk7X7pugbawZoPsW8HK2f5AxFa+9ZSuWe5FX+KVJaxf7IsRJZJO5j+LOPmavuTpTAvN3OFlyyPx/VqnLn56kTmstyC8er6+VnMIL/I2A44Ql1eUMhzBfR2rOHautZFDs+USpNr5+6EVvJ7rY9yn17bN2OpzNSec0UritX9Z5A47rsf/qDmRYvImJeTkpeehJZyP7lfFP+LcMpLsvLYd3VS+nPMi6/kRfps2JeJ9C94WO7tP0AIIx/hZvnIVB4pUWxpzLMz9Hw49Gs40lRWlnRHSbp+kc7pNtyO5l6a8fJzKUXSnCNpWszSzC3IbcwzTV2leUDSTJU2mnmEAcpn0ixNmmfceRaT2X4aj2lcM+d6PkjZzyiTNKnn6vN/GvGsHZO6JW3iGXb5OCT5CJY63knqeIWLfFzoOj5O8mFrrm0cIXNwDiEMVj73rvIhp5/GPH/ImJcAyUuI2jafk12iNHPLuoGKTu3c8rzb5s7HLUL5TAx1kU8rD1vLPrc81pbXt13rnjExtLa9r4Vzu9utrBc7tLatKzkqfHjtIw3cb+PiXOj0PIM7/J2fZ3BGzo/m7T6Nb8/6Um0fuSWqa1T+R9bHE+/acHb9S/MO/vLz+o9X8xnzbZ/eSd+Urt07aV7gqRYbuAF2sJmy/LnDyZ/vzut08uebK+Le6fHIl9yrVpdXfjS3221p97e69uJDTQK+ue9x6oK3snzP3JXJp5pvumfVrktqDt1700HX7V/m7Wiu2q0a/3wA83YuV+1rrtu5bOp+rbnvjqMfvxAefvULM0tyb7j3VOPb4xrbXmbeLua6nW63mk9b0PVfXz399nnX9ptzp19kyxOu22FDxynL13r5HbWmHHr9x3mbTl53+sO4+tvdQprI7zT5/baf0E2bf1t9Zct90IUYivk4DwswAwuxAC1YhktxLVrxZizGPbgMq3E5HsUSfAtX4Em8Er/DUmxO2ldhf1yF4bgaR2MZ/yXi1bgWf4Mb8Ro8gNfiUbwOv8e1+COuw5/wemzLPm7AALwBu+EmDMdyHIE3YQyyDzIPovxek/Pkfod5EMeyXisch4E4HrthnL69/MaCno7bSztHS+yLnbGflHd/2b6MEC7bPyzbt0GbbD9N7qsmYhBOx644EwdgEo7D2ZiIyXgFzsUVOF+O2wLcgql4N6bjA5ih39+V30o4TvJhvL/bVfIRIvnohsHYA3thKI7CnoZysUh8KSbl0lHiC8IJ2AnnYLAhP6dl+1ST/PjJGNZ22BcvwcHYHmfhpVKfA4z5iXJ9nCPlOEfJcR4qx3mYvr38zsBgk+0HynEehO0xHDvhYMN86dWyfYRsb5xfOF6pvzhZ6sllsl9TcAgmGPLhN9T1foyQ/Rgp+xEj+zHKcD84VrbvL/2X9fvBUi/Oert3P3h/IX9L4x4iH6h1hIOE44QUC3+XscKB6dwzJoSM4l6lhe0JsaPq7iF7L+W+LaH2XnIs/87h7+sIZ3hfiS8Sslh+EpV7yz6jtfvLfTCGsJG/7SI=
*/