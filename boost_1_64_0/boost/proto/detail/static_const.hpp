///////////////////////////////////////////////////////////////////////////////
/// \file static_const.hpp
/// Contains definition of static_const for declaring static constants that 
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012
#define BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        struct static_const
        {
            static T const value;
        };

        template<typename T>
        T const static_const<T>::value = {};
    }
}}

#endif

/* static_const.hpp
4D1XuH1p7LX5nMQtR/p4LFnPDX/0MSipyPl06n0pdXLxRCrp0TFQnXQHxYE3A/tTStK6E3AoFA8/cVXerwQ5WBPBIgtOB/T6+f5Ol38d6azE2vjCXh9HOh7xHqKPk3oc8e3I7fKy9r62wXscPy/3oCU+p/Tmg3Uq53kPJmWaXMQ2MF4G6l3YJ3mZNacsvBYRYyP4cprwy3fKL1/uwzp8Xuljse+2KP1NL+PuPdjfm68+sU+B90KYO7uwgOf7G8P5bDoZ6X27s1bJLS/lFvOpvnWGQrKs0zsQZmlJxv7rB8qFGR/aReR7kOwJonW+PzKYB1zf19gziNVtfUTsy0KvqrGuxZn38GwNk4cfxB3cEIsT5MvYL5ssE9sS8OCBRyp1mbYPZHXafq7/dqe4Y+LnYLDV2I5nxMuwApBtMcKcbm97HPBzfOiDg9RG7Ed7C3w2ndR3ycJ8VS0bzst98U1v2bF1uO975aEs7Ppa3oifrai15Xk+j/QzpPgAsfrew14fC4MaQZoEeOxtH87Lurq6K8xTXfHdGD+byhaW3iCfdeQ3r4fw9Egd61AH8GT/SGzdKWdmcfHEcg57ZKUmz3RaIRaNmrmPd0Mc2kDW+A6ozeHpK+RQv00vmfALmPo+T5intVSVx7+cU+j8XKwfKJ/1XT6uo67VaXuni3t9jLvGOO2TJdcYYj10Jsia+mji10P8ZHwLYLml+onkK2G+XuponuphbMTHm+uNwx6ZdDme71HKNnJfo+W2fOBrH6GPl/4Hxn15M/XxXe5TfrmmzlnU0/0g76/XfwR5f71+31sfaKvKNpJemawHXkZZMHH6udVVXVdf9baRXGNr9nkhdiJe8J+tKpbPuJx9R6JQWEofWy7gKoEumPOZ7hCeBjfnJcyTMuut7E9h3GEzxxeXoCdyP3yykCcZSFv6Sfh9gIMWktwtWVf4si1a7INdt+K4vQMcTBR8ZiTXUe4ruZzmIQ8HyWHmNPfbUYeDVsRne8Va/YabN5hBgaVyvJW/S3u9LK2Wief2vumXTT2K+afTOJI2RK+fTy9lcouLGb1G+JEsu/kqZ5HvDwtGvtrKc7sMN1+vLfK3XTDeF1RF/V2TrPuSqsFekaz7eqvBXpes+/qqwT4iWO8Lq7K9g6yb368GWTe/N0Ms5VeOG8m6r7Rqn0KC873UyudqknNf8+X+1TI5Z33wGRnuvsDLcj4gOHr9V54tfUKEuy/9Rvo8TXDel4xF/W4K1vsysqjfiy4rq4NldgXnfZFZsVTmjwhWvmzM/l9kOL50SW7munxPRjLyNU3BbO50mVoDXKXrb1TXZWiHTL4IG7yvcllq9xqfU7gMtRnL47sOBySbp1MKVA/TBSaphxzIq59xOaXviAzksQXZFtjPkuq5wn5/gpy59h4Jc9A16AxQ3/8L8XlWyQOv3wgyefW/Au4A4jpA22+2ExsPsNh4K6xDtLh8IVFYziOKDaKWdyoXbH8a5g19/bUwR/2ny+d6giV7WxqcXbVkaoi16IMwC9+ylpoCDJ3NHQ+Pp74dvLMr9g+3/SxVAuJST3vA5UVbFNneyCMXKkva0fzex6yJfEo7ohCLlbXKPup8HFb+WV6rexgavLI+p8iOxsPT6JL1JM9J7w6MA694tWllrveaoThYb2u8zg9xWM41ysM/fByNTHhAQu1h7P7wNKd9X6eq2BzZYFfHNmNmGo42nO+t+Dk6IgEF6Cm2Lw6wjWajXBVz8A2XI3d2NElq/0guyxOOavS3yT7+M5cVXTx6G33fuh4Omoq/S2648x25ZTEL+eNwF2spnS1QWfTaeAirnIM1ZdtcCvPGvHU5zGF+5Vt/Zv/A65A4t5RiXYNgZ/w=
*/