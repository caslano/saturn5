/*=============================================================================
    BOOST_PP_VARIADICS version of BOOST_PP_IS_SEQ inspired from 
    boost/mpl/aux_/preprocessor/is_seq.hpp, original copyrights goes to :

    Copyright Paul Mensonides 2003
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_PP_IS_SEQ(seq) BOOST_PP_CAT(BOOST_FUSION_PP_IS_SEQ_,       \
    BOOST_FUSION_PP_IS_SEQ_0 seq BOOST_PP_RPAREN())

#define BOOST_FUSION_PP_IS_SEQ_0(...)                                           \
    BOOST_FUSION_PP_IS_SEQ_1(__VA_ARGS__

#define BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(...)                                    \
    0

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_0                         \
    BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_1(...)                    \
    1

#endif // BOOST_PP_VARIADICS

#endif

/* is_seq.hpp
ETy/LfRer/d95OJ+7Ndl4wjo5KXC7nBX6eD1k47dIOnY5UmnzitduhK4F/RJl+4Y2BueBPtIl7IfPBvuDa+F/aU7NgDeA/eB98H9pMM3GL4Ah8BX4EHwS3gw/B6OhJ2ROQduDXPhDnAsHADHwaFwvHTJ8mApnAAr4eHwYjgJzoVeeBfMh/fDybAeFsMXYYlRL5wCf4SlUPOJ3vW5TqLnE+m8G3wEtoZce9JZ0nu73udnR+ksfaHr4UuNh69gL/i15pflcBj8Bo7w65pLtxNOko55iXwiT4crpFP/E5wFf/ZIxxMuhCvh4/KR/K500T+RLvq30kVfKV30VdJFbyUfye1aANgVbiCd11ZwJ7gh3E2+knvLR/JA2AYeBNvC8bAj9MIUeATcVOdpM3gC3ByeBDuF93uadM1s+r2H4Vsc7qZ+7An1O72/M9Yc5v+umv8H6rPmMQa34gTazGN3a15YJB3ue6RbeG+4jp9+jyzosEfqsh1u5uOdVe2Kka8+zvI8vePLl6l8PWLkqwnL1xSVb0y4fMrXNUa+RuXbLka+lD5qR4x8OcrXJ0Y+PVM7tuMy6cZ1+gJdFdIwUj7prZfQybgXvRD+XUtaQHqalPcAOjFwFanbMnRTSLkkH2k2qY5UT3qPtIq09ZfokJDySDNJhu/piTzcLX0loI932ZeQ1EBaRvJ8xe/v5Hcw/avYenqJxpZ0fVUnr4u3tvxUuz6qnXxUrxn/1K5v6tX3TZ3zFb8h1ZIWkd4irSJt/TVtJOWTakgLSQ2kZaSU5bSTlEuaSVpAaiCtIu34DWWSqklzSfXfuPpw7uEe7uEe7uEe7uEe7uEe7uEe7uEe6+pYS/r/eHlcff1/Q5d/KzP+P74ZTH3srbXG7DX8bwb2iqvw11ZQVd7LqDxB3TlDL1q6Fjb+1zLlQ1M6r+ul/oW9PoWzXoa9noWTvsa/T//CXs/iv+u7rHtf4/s7dp856ft5KS3Kfj9oVPYmLxydvP6Frin+bd1/2076F9tLD2AHuFCxOdlXYT/F2BeJvffh7nusnX2PtRmj0937+Gf3PtzYnGtm/2OZuz/hHu7hHu7hHv+jY629/5dUGAsAq/X+H4zp15hhxLQaPHRo1pgx3mFZY4aOHp6Ta9hVKKrfbuTrz3t8ziB/vrEYJY0enjvBO3zk/qO8+tnU6uJp5PWvKbTdy2PG/7KJ/ze6C7pn2xvvP3aVGnZcsW3zgja/wzqbdoDBOlc4xABs3MqpTiw647BDDcUBHBQdA8ysO88mDuBBRrwl2/bKkCkOW8Tw+HUNG1j79GDqqFUdtifI6NY46gn26357WPt1REv7fm1SvzoMjLj71WfpV7PNi1pa+3XMnvRFc22ma+Ox8wyPsZbeyvjbEmONl/B/Osaazq3qH6Q1uP6kHCOGXKD+ItbgrGMojjYGz+vIDDO+mFH2lECMF8TQWpyfki1q3PlaW2UbQ3n1pmy25yGecxCU75Ak5Av23UrJ10f6tnuSxlJeyo6K11aQXN9pLTMiRk4Hybe/zfxTs6FVjvHIkROUoyg5Ocw5L7KPjvD3UcX06qjz1W4jqxwTjHkiJMfqny/NE86y6Lo6R5MGSzR+OTrDwzKMgSRZjm5elrfsZRlK4dzvBuInwqi3hd/vwnPbmH4XuiBXo9aho2OBLDPlN+6n/u+aFAtEviX4LtxfQjmDTv4AQuehqLiq0LRdV5wPXC04xgJR+dX+CrrI50PF5sZ33NH5ZdhYV8y6cr4NxOZM4ZzO3hi5DXsMf9+Zsa3KI31bRNhnr9w42r5W8+eOsqmMHpJJ2NgGz3X1JjY2ttTV5FRXEna2D1OebDgj2tnOxib/8Ax+vVMzdWOIHvs=
*/