/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0100)
#define BOOST_FUSION_CLEAR_10172012_0100

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/boost_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail {

  template <typename Tag>
  struct clear;

  template <>
  struct clear<boost_tuple_tag> : mpl::identity<boost::tuple<> > {};

}}}

#endif

/* clear.hpp
/r97b6zTbS6uto/m1PkZTNMdHvasz+sy/wU13eKXnvMMurCmJ77wD+uvm1z4p7OoS7wUM3Wbp7W9s+5wzwvu9XGf5UMQusznYkV6Br4bTd3mIS96Tp3nr6CtS3waFqX5fDfqusXbvOTMp/l8LDKuX+Eb0UrPyR+gozNre2I/LNUlPgdZ82t8H1ana/JW/7LvusC/xlhz6vweRunMv3vi+yjqKj+Lgu7wgS/bU13mm1HSLf78OmdSl/gyTNBN3vdVa647/NR6z6Azr/mb8rp312We84Y10W0+sONddIXbG5whHe84J4itPSfv967nT3P4IizWdb4NC3WTX8UyHRt74jNYoot8HObqCv8Ks3WN78QC3eL3MU9nNvXE7pihi3wiZukq//k9e+F54v2euGCzdU79ge/jh85D6uiNbbfojbwu8ylb9sYo3eRXhvRGIfXWvfHk0N4Yq/Pb9Ma+md6o6cy2PjesNxbpDs8c3ht1XeePdvfGfF3mszBT1/hOzNEt3oSqzmR7Y3eUdZFPQkVX+XpM001+GkXd5i16eqOkM7wXJusSn44JusYvoqmjtzeewVKd6euNr6Ghy/xyrjfW6NKI3rh2oDc6upjvjdk79MYK3eb7PtUbG3Xs2Bs37twbQ4d6x11642ejPLNu8Nd27Y25usJXftrndYenfqY3ZukaH/Y576JLhd74ESboKt+AybrJr6CkY/fe6EZB53lf5HWJT0dR1/hOjNUt3oRROvN5+4h5aQ4//IXeWKDzY3qj/4u9sVCX+e8Yuo17fak3fophus5PYXN6ft5pj94YZLzIR43tjVyaw49imTltHr5nb6zXBZ6GDbrKS7FWd/iwL/fGKl3hJ7AmjfNBe/XGyjTO87Bc1/lRLNZt3nZcbyzRed5z794YvY3r8w/36Y0xusG3FXtjvC7u2xuDx/fGON3kbffvjZG6wDO/1hvTdYu3OqA3pugM74epusTnYKKu8X2YlOZzfkJvzNBFPgWzdJVXYv0n9Nd74/ADvZeuJWOtzh/UG1/HDF3mMzE9zeHbMU+3+A3M1TGxN3bFMF3kb2OorvAVGKMb/BhG6zYPOdhnt3Ev/gpm6xKfhlW6xn/GSt3kV7BBxzd6YwDrdYGPwhJd4QuxWNf5IUxK9+IPMVFnDrEXWJjuxadhSXov/jMW6yYPLXkGnedjsUxX+EbMSnP4AyzQmUN742DkdJl/i3G6wa9hXnrmw3pjb6zRJT4fm3Wdn8cy3eHdDre/aQ35FCzXVb4Fs3WT38JCHZN64wsYmebzKRif5vMtWJDWjd/CyjT/CPOxNp0HPgWD0ny+BcvTfH4LU9P8I70rcp/0nJz/pnvpIl+DYbrJR0z2Luk6/BYGGc8c1RvHH20d0xx+FRvSNY+xR8dak3Sdb3knRMb1eS02Go9v+20o+50xXuNTvt8bbeOd6c7/DO+iWz/pjYtm+a7q0s9dp+p9df4sv23o6Aoffbbvdro+P4rBus0/Pac31qX34k/M9rtkvMDHIqMrvOMvvLMu8Va/7I1smsO/+LX1T589z7nCWOP5ub3x6/P9jukO73yhvwW6yk+gkMZ5as3z6RrfcbHfT126xL5c6vdTN/hxzP6k5+Qhl/mO6Dzvixm6xKdhlq7xTRitm/wKxui4vDd2wHRd4AMwUZf4Rxinq3wDpugmv4pJOuZ7HkzVRT4R43WDv3Wl3tZ1fuNv0ALfwYz+rbm/cwZ0g5df5QyYk6n3xhkYo+t82NXuq6v8g987P7rBixc6G2ltr/E3CDnjTR5zrfOjyxyL7HvaF34Fo9P1r3f2sCaN85F/9I7Ga3zoDc5TRvPpi53bdE0e3PC9TmeAd7rZ+6bn4Rs=
*/