
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
lpolfffMxgDM1/RJlSDz1XMyX02ZrxbWxdqa+QquEV+mzGeS+Mya+fbLfPWdzDdH5puLQThP5ssrJedJOX8q84Uo+xQqQ135RkQgBmNDbI5NcCQ2xQnYHM0YglOwBc7Elng3tsLFGIoPYhs8jGFYgbjaYW1sj82xA0ZiOI7HCLwLI/Eh7Ih7sBNewM5oUKpbsTZ2xToYhdEYjXdhN1yH3fEB7IG7sSd+jr3wV+yNXhRYH2yK/TAbh+BCHIoFOAwfxdH4AY7Bf+JYPIvxeCvlmogdMRmj0ajdTkJcr7dsWW85st5yNX2DFch8PzjpG2yBtH27F31xEfrjYmyISzEaC7A/LsPxuALvwvtwKa7C+3A1PoxrcBuuw124Ht/BDfglbsRv8X7tdinH4dpO8jdV8jcNa+J0zXxnZL7GTuZLk/kmSH4mIs+3in0OcPbjipbnBfSJdVP6w/qrngncqL6wbvb3Fpz1fbW/Gd9XIFwi+DSnfyvCEEIeYQ1hR3PPMwFl+Ivv/5XumK/7/j+Q936rKc/SLf0os+D4dJNpYq7Z1hFzM/6uuNfy92RTvMNP4k2kN547pniDpS5hkJ9BvfdIlXNWDbnerE64U3mXu5p6XR8dEzOo94AeAy2ZMWZnF3vtabu23xKhvDOTprvXOVkkPmYivlAn8aUkZqSlTy3+mvta8c2X+/AcuW8xE+YSX6yz+LKMRnf6tbbFt0niU96JOlWKOKznUhra6N/rU36XaczTfa8gS35zt8O94GWvouVzD78pdJJeZZnu3JM4K58uEl96aakHkPLpK+vDp3rR+GzfaStJGTmL80zponmcT5z5ReK0dnitbHd/NJ+3S5wjyjjf7jZdI854peeEPxivLa+HXcS730W89Cvu1rcCHOLU3auHl5XrUImzDuFe4jyjj9PST3dWCeKyfJ/TrK8X2CJxeUtcFQiLlO3HVxdXifflnU7i8pH79FoSl5/kK8ghLvbjEpWh5Eu33naUK/pe8xLiitLHZfmwhvKtBqn5cHu/kPzp6j14/9qYlZZEvuzvA9uW79gHR4jUE4wglCUMIRREEhzSl5E40WlZlL92Wah1BQsZz07U95WyUuIeJGUzgLAsUtnI9XFnGqe4VR5X5duvnKF0x8IykkglutKSz+XEY3aIx5yYkyrl7/Y6l/LXxbdb4lsi+bqXsJL48h3iy0qcIqdC9+u5JD5dPSijjNvfe0zXnDNqMlGJhE+VaL6dUrSeOU/ev98uZfQYYZWynfoVSbOyKbhdPgedbJ+yD6v1ckoap6Qas2zvYftirkGmkVBt3VwwQb7Zo0v/WUl/K0l/C8JqZZ+uWST9zO7O9wSkvJ3s0/kVne/TCQ5xZRuzJqcl2XZp989119inde/4y/J1216hpK28lEM5whrStkOftj90PpR06c6Hqd5F41tLfPtdxBefyZk/M7tE1xvOjqunJN6WEm+InC+O6uP9w+dgyavueOX7H/buBS6qKg/g+Ph+gIryVBFBQFB5qYAKqCjiO5+IaBogoIAILAyKSj4231FiWpnRZqXmmpWVlrluWfbcrKiszKxs18o2tqWysrLc3535z50744xAWbvt555Pp69zuffcc+5r5px77j3y7PnY5jJOD1azTjcfyzrl17Ksx3iZ9fjxvpSfurKc+fRUhmrhGlvAUNbKsDbmcaGSfU1/57N2TB+bcaykLV49FtTxcP9E/uWnu/JTQNq7bc8/9X0q9uMSy3PQ2ygbVyf7sZpMv1NPu5if9d/CtOtM5Zdn0GW+eZl56Zb3TVUy7e5B5JuHgEvlvLWksb296RkQg29ncxrKGGWDWG/1emW+XNqo2ShzMk0D3vTgb2V4RKk=
*/