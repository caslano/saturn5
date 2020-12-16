
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct list_c_chooser;

}

namespace aux {

template<>
struct list_c_chooser<0>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list0_c<
              T
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<1>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list1_c<
              T, C0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<2>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list2_c<
              T, C0, C1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<3>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list3_c<
              T, C0, C1, C2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<4>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list4_c<
              T, C0, C1, C2, C3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<5>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list5_c<
              T, C0, C1, C2, C3, C4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<6>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list6_c<
              T, C0, C1, C2, C3, C4, C5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<7>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list7_c<
              T, C0, C1, C2, C3, C4, C5, C6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<8>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list8_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<9>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list9_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<10>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list10_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<11>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list11_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<12>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list12_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<13>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list13_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<14>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list14_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<15>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list15_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<16>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list16_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<17>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list17_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<18>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list18_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<19>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list19_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct list_c_chooser<20>
{
    template<
          typename T, long C0, long C1, long C2, long C3, long C4, long C5
        , long C6, long C7, long C8, long C9, long C10, long C11, long C12
        , long C13, long C14, long C15, long C16, long C17, long C18, long C19
        >
    struct result_
    {
        typedef typename list20_c<
              T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< long C >
struct is_list_c_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_list_c_arg<LONG_MAX>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      long C1, long C2, long C3, long C4, long C5, long C6, long C7, long C8
    , long C9, long C10, long C11, long C12, long C13, long C14, long C15
    , long C16, long C17, long C18, long C19, long C20
    >
struct list_c_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_list_c_arg<C1>::value + is_list_c_arg<C2>::value 
        + is_list_c_arg<C3>::value + is_list_c_arg<C4>::value 
        + is_list_c_arg<C5>::value + is_list_c_arg<C6>::value 
        + is_list_c_arg<C7>::value + is_list_c_arg<C8>::value 
        + is_list_c_arg<C9>::value + is_list_c_arg<C10>::value 
        + is_list_c_arg<C11>::value + is_list_c_arg<C12>::value 
        + is_list_c_arg<C13>::value + is_list_c_arg<C14>::value 
        + is_list_c_arg<C15>::value + is_list_c_arg<C16>::value 
        + is_list_c_arg<C17>::value + is_list_c_arg<C18>::value 
        + is_list_c_arg<C19>::value + is_list_c_arg<C20>::value
        );

};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct list_c_impl
{
    typedef aux::list_c_count_args<
          C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        > arg_num_;

    typedef typename aux::list_c_chooser< arg_num_::value >
        ::template result_< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18,C19 >::type type;
};

} // namespace aux

template<
      typename T, long C0 = LONG_MAX, long C1 = LONG_MAX, long C2 = LONG_MAX
    , long C3 = LONG_MAX, long C4 = LONG_MAX, long C5 = LONG_MAX
    , long C6 = LONG_MAX, long C7 = LONG_MAX, long C8 = LONG_MAX
    , long C9 = LONG_MAX, long C10 = LONG_MAX, long C11 = LONG_MAX
    , long C12 = LONG_MAX, long C13 = LONG_MAX, long C14 = LONG_MAX
    , long C15 = LONG_MAX, long C16 = LONG_MAX, long C17 = LONG_MAX
    , long C18 = LONG_MAX, long C19 = LONG_MAX
    >
struct list_c
    : aux::list_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type
{
    typedef typename aux::list_c_impl<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19
        >::type type;
};

}}


/* list_c.hpp
HB+zIstViY+xFxujGRdT/xfr2JjkDNf7Fh/T7RfHYmR4bs99i4+ZmeH6j8XIHGGbXiR5rCKOixRAGkpKJS0gbSEdI10lea5mnyQFkwykaaQVpL2rnXE2zsk5Oaf/n+nB9/8bwpLiDPfl2f9K/38ZT5Yh8f91NPrlH+fEbrepz6Zzp7CuXcg9huz1xiCEhKh8r22WZYzBAJaRzkW5QsYR8yQWQPLcLv3FS4uYrgEvxjK8f9keuRauzpNhBc3XqX3zGeuv8gHjuag+Pkqukyuvc4I8IjEhxdx/WAJf5MdPosx74E7mw2XeU+YjZL4iflVLri3LuH+7eFN8c+mvNM/7muaPqMYJVOZzzH9vKv2X5nm5Tp5rnm925xnxS8hPKW8FuU7tw7KjY/SxUWFxKbHy+jFe97O8nvSkeX2yzcvzM9VBFvNK+ZVhzVgH6XeU9/ibxtjq86HpHJ7lGeefknkfmV9iM/+hzfyje9WfZ3ky72Nens38Epv5rvut5+Ns5uczr17+Jpv5YzbvH/6R9fwUm/mVlnmbdin94N1lDMrO6M17Mr7SaJf0YjraLrcec6xdqtuhh0079LRphznq8ShV2zQ5zmCJN8m+8xqtQfrLpX0pr4Xl08ayNNpYWWnDsowmYfKaeT8YHOHX1JzXceu2J32c8r5w5X2m7eF51Hp7tmZevb3G2Pw90+bvt23max2znh9qMz/xmPb2Py39133dTNs/CD15T+7HGts/KkKpJofGIK19uKSMQfr3jkuy/TWPO8fzOe7cUB13tI4zp+20gVw7x5mLNseZbNvjDPX8xyfW223uQev5P5lXb5fIQ9Z//9Bm/pTNvPun1p9Ps5nfx7z6/Rds/t79M+u/v2Az/7PMSzuxjIebKT9x6sh3Zi1SY96TfkqjnVgqNP8+wbu1Deraqm2w7dRtg3nt7yx1uQOlb95byl2d1IRyr9cut2zwB1tudTkHSDlnSl/5YInbGYB/KWN15mqUc4Q+OayHITFhlD4ymR5jhgdOSIyKiQ9P1ifxNoriSB+yW5lzv9x9Hy2rOkYbEgheMK+TrGOqeZ1kPs28LWT+aZmvarMf37A5jt/W2I/Kmsqm6yntMtBmfox5XtppkPl4Jn3tsyUubwZepvy5OVr1qKxoWORIfeTosKiYpMjEmDhq0RJL5J1P/Q264NgxTr3up23W/eqd76swP/N3jeq1JrKcXNWxS31si5DP5Kjq0PZ4GW7z3Uhj0SfK99Dx89b16v6Tdb12kXqNklgAP9mPfEknqNesH+3Xa6w+PFHGO3Z4fxpRz1J/VvvxRcnfIPnHk06Rv8dp+/knGNIKlG+UPinZErcn2zIpMdJYjo5SjpElteshw349SA04fkxR14F6G4wrZXpzazlGNMcc8g44Zzdv5UhBVM8YvaPHhBE5jrVppR0ZbI4H4VbHA9Wx+R72/7PnrNtl+Rztdnlb6sRTtkdZ0gWlXebctU6i9CMS9Y6M166qA812mVxa+rEk/4mk78k/+5Td/GkOyQ7na68tZMqny8lxrjSeId9l9veHJNu24JFPW5h31qYtSHls24LxuHQP39NyXLNqCzc0zp9vq46H4XLc2nXGun20OyvzNue3/jIYZLBsnyCSF+9ZlpW3ntgyY/SJjm8bre/KFzW+K2V9rY4je8vkbbeVKZfH51rlSgoLT6Z00UrTcfyYlt93ubo8W8qZFpAuvwPHYTXK42unPAnx1m2pfj5tac6Rez/XULeXY6r2ov5dP7i5zTm+zTn7YH85t7dzzp+T95xf+xxf2qi0R6vv2cSRprZY4Qvrc+rONvNRNvPPMa8+R6/0pfV8B5v5aTbz62zmqxyxnh/CvORntc0=
*/