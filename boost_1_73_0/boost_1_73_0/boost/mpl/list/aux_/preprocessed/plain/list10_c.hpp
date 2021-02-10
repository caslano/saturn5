
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list/list10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct list1_c
    : l_item<
          long_<1>
        , integral_c< T,C0 >
        , l_end
        >
{
    typedef list1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct list2_c
    : l_item<
          long_<2>
        , integral_c< T,C0 >
        , list1_c< T,C1 >
        >
{
    typedef list2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct list3_c
    : l_item<
          long_<3>
        , integral_c< T,C0 >
        , list2_c< T,C1,C2 >
        >
{
    typedef list3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct list4_c
    : l_item<
          long_<4>
        , integral_c< T,C0 >
        , list3_c< T,C1,C2,C3 >
        >
{
    typedef list4_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct list5_c
    : l_item<
          long_<5>
        , integral_c< T,C0 >
        , list4_c< T,C1,C2,C3,C4 >
        >
{
    typedef list5_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct list6_c
    : l_item<
          long_<6>
        , integral_c< T,C0 >
        , list5_c< T,C1,C2,C3,C4,C5 >
        >
{
    typedef list6_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct list7_c
    : l_item<
          long_<7>
        , integral_c< T,C0 >
        , list6_c< T,C1,C2,C3,C4,C5,C6 >
        >
{
    typedef list7_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct list8_c
    : l_item<
          long_<8>
        , integral_c< T,C0 >
        , list7_c< T,C1,C2,C3,C4,C5,C6,C7 >
        >
{
    typedef list8_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct list9_c
    : l_item<
          long_<9>
        , integral_c< T,C0 >
        , list8_c< T,C1,C2,C3,C4,C5,C6,C7,C8 >
        >
{
    typedef list9_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct list10_c
    : l_item<
          long_<10>
        , integral_c< T,C0 >
        , list9_c< T,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
        >
{
    typedef list10_c type;
    typedef T value_type;
};

}}

/* list10_c.hpp
8D8Vf3zNL1BLAwQKAAAACAAtZ0pSXJ57j94BAAAVAwAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDc3VVQFAAG2SCRgZVNdb6MwEHy3xH9YUeWlqs+Q5prDQpGqNmpy1zZRwvXdhSWgEjsCJz36628N+XjoC7D27OzM2MQWG5uqBicsLnVu6PWB7aeps2bCZkmy7B7wNE3YPOcvJivzEjO+LnWKjH+xWFzgsegZrtgVrLE+YM2bMkMW17irWtrPlFU9qwh/hDAMAlj8YY/KooRkjzcQRPBqDrQRBhCO5CiSBHl6SVhPJ8Gp5U1XiFx9IHtWtHCSdWQJb+H3Xh9ZhjIMTizTRG0k+MMwGP7kWTrmt9HobjiKfvnsPk1xZ/lK6Q02Et5bmsQejLaoLX9GvbGFhDu3ojG1pdES0so0eMYk7Q6dvn9WFHZbMcZzYzhl0puOxTGELp2HqnQ9fTppVxCk9zVhhbU7ajiVEGu1xT43+CxtAfwLfFNlWAORo08I0UMgTs12q3TWk0ghBrPFOpkv5cB1LxerRIzHXX+GKYXj8gm6fMIoilxIPk0+k9DnUVwn+w3rMm/dUAUqtzTfFtidCRSqgXdEDX5TGEskhw5LFLvaWJOaasLoEoEbf7oAHpuZxkr4
*/