/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct vector_n_chooser
    {
        typedef vector10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> type;
    };
    template <>
    struct vector_n_chooser<void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector0<> type;
    };
    template <typename T0>
    struct vector_n_chooser<
        T0
        , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector1<T0> type;
    };
    template <typename T0 , typename T1>
    struct vector_n_chooser<
        T0 , T1
        , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector2<T0 , T1> type;
    };
    template <typename T0 , typename T1 , typename T2>
    struct vector_n_chooser<
        T0 , T1 , T2
        , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector3<T0 , T1 , T2> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3
        , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector4<T0 , T1 , T2 , T3> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4
        , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector5<T0 , T1 , T2 , T3 , T4> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5
        , void_ , void_ , void_ , void_>
    {
        typedef vector6<T0 , T1 , T2 , T3 , T4 , T5> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6
        , void_ , void_ , void_>
    {
        typedef vector7<T0 , T1 , T2 , T3 , T4 , T5 , T6> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7
        , void_ , void_>
    {
        typedef vector8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8
        , void_>
    {
        typedef vector9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> type;
    };
}}}

/* vector_chooser10.hpp
tiVdp5fgeNL3HOR8fd/pkH5gvKRveijHl25LqfM9zbuhfbotkm/jQ74nbSzHF532PpLnex3STtHb+Gpf7OK61gIznOs+M8nejlYpA6cXqHjqwFPqnP69Dum3SfqGl+2ep1/sfL/L5q9tG5B6iPGCGtd7Refhzu8V9zrY4LG1gczH+WxtPzRG/W/s8GyV8rd/oY+v/RUe7lz+D9qmj8jzxrFDHWcZBA5yvg9kbuLwPitlYNeBi6fuA8XOz7p7HdJulntfVGegB/VfWhaj/W/q8H4j5R+rMx9PGXQVObfBBx1syJHyN3SgenwP6PLFqP/NHK6/3SV9y0eneNte4dTotMdK2jc5pJ0UlXZ815xnmvPzNnVzh/xKeVs+xsX1zGuf4lzPix3S7ZR0bT82xHufneH8fjU02eFeE0m/x+3LW253jclcIod0uyRdx48+cbYzT4znfMpghzqX69zhA1xcdV96iPM1NmoL/hA2IrHhcCBcsBV2STs3f4xlj8+6Cn8475Wr8VsNwCN0X9pAhb8+5EvbpPZYne2fre2yKnGbYZZ+vHF2jfjdzoNBh/12v0oK7cnKYbVO70LdR5Y+Y0OVWgf2tCH6+dVG///Jof1Ky4lmuv4Wb+Fwz59gKYse3OtbpsVo/1s63GukDchH1R713wsPdX6/WeiQbo6ka/NhO65213awc56ThjjkOdOcdk/eq5ptnmk7S547Jd0vxE/7E+Qu7n8dY9V6xOVl3dhLenPz3sABf71+hap5Fnegk3Z/lK86sp90s96+sUjaYiVct5/eFpt89bNUO74k5OvNIWnvNmtQp0t+Wofyh3Cl5GeR5Kd1N5Wf2b76KjK1+jkm4utum6d8mzwV2uSpyCZPml3v6ns4a6aY7S/luBYKxP69xH5vxP56/2zM78YcmbVpf7Je/phiKf9lW4kFCdgPfhX7W8Yr+0Ol/w+1KW0/6QrKeCl2PqftIxuyS+VrKz1f1IrsPT2Q3xWIVs4vG+KmwbdDdRiUOlTxFyDp2vnZkfhe+P4wuc9zgjH+ExJ/miF+JvxAjx84WvSLRMp6ydb8IVRKWymXsi7NUmXdoJV1d+ZTrY22ouWvg7wt3jrkb3t6lrGsoXkOh5rHsTSh9+ZxuPM1ejZf43W9HBLvHpC51dS58x5YeUp+37env9iz+RopHhlzkeebttZzAtxUGuCeCZ7mcLzOGPEOMMRrG+scbx1DvMJM53i830k8JMs5Xn+DvvYY6W5uiNcVIx+7GeKVxrCvy2PIRwz7djTES9rNOV6pIV4gRro/GeI1x4j3ubH8HONBY7rjneO1GeK1xNB3jzHdGPk92hCvNYa+Gwzx2mLEm2W0L0a656l4hBjxDjXEa4+R7lmGeN4Y7WALQ7yOGPqqjfUboz4eN8TripHuXoZ4OTHSfdhYLrs7xytOMLTnGPHKVTxCjHQPNt5fYsQ7zVjOMeJ9YCyXGPHqjfl1Lj81b6vVI/1M6X8Sz7QHfhP5GA7nwJFwLhwPT4XT4WmwAZ4Oz4Xz4BJ4BmyDZ8L74VnwMTgfPgvPhsvhOfADeC78ErbAH+F5UOsHnw9Vu5ngnJ+gsf5i5PsgY7uJEW+E8f4Wo7wnqXJU/Rf6NdHlOAT7UuBQKcdhcAzcSspza7gPHA6nwW3gsXA7uACOgAthGrwD7gAfgSPh43BH+CTcBb4DvbATZsBP4K5SPs0e6ZfAK8XODWBQ7LxA5gVdCHeCF8EMuBBOghfD/eElcAq8FPrhIhiEl8Hj4OXwDHgFvAheCRfBq9Qe7NK/gAVih3EP9uPEjjlix/FixwliR7Psa3ESlH0z5H2fIO3YuG/GUtH3DNwRPgsz4XOibxkshM/Dw+E=
*/