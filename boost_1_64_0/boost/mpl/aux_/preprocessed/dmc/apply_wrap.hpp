
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
k4lpphHca4PXu1ycNjjl0AanDdrgnEMb+AUpC1vaYFkXp23gnY/uEsbP/L/NR/eYOR5mfb/RrwzzHTxv3IX9J3vvfuX0nzNueEQ1efan6t/flP/fTH6X3SX9iPKxFd6HvfB+7I8PYjSuwkm4BmdiAc7BR/F2LMTl0n/4n7gWN0j/4TdxPe6R/sKHcCP+gs9Iv+oirEmZnsc6+ILE02zCLNyMt+EWXIMvYhm+hB9jMX6CJXgCt+L3uA0v4HaspsRtoC++iiH4Gl6Hb2BbfFP66xRWk2d7Slml3Toqv3mt7Sb9de7GILwHQ/FebIz3YU+8HwfggzgUV+EY/AdOxockTmKNxM8U4M1YiKtxLRbgOnwMn8Zi3IDv40b8Cp/Bb/E5PIXP4xncjBdwCwYr7YXNsRjbYwmOwK04HbdhPO7AmViKN+OrWICv4WO4E5/At3Ab7sKPcTcexj1Yju/geXwXfWjDfRiA7+Fg/ABvwA8xDg9iCh7CdPwMs7Ecb8HP8Vb8AmX/lmd8Sl30+3d32U49MQR7Y0Psi62wH3bG/jgKB2AiDsQUjMS5OASX4DBchSPxEYzCHTgay3CMxLOMxe8xWuKdxmEtyjRetsNEvA4nYX+cjAMxBkfiFByHU3EqTsMMnI634wxcirF4D8bhSkzANZiMT+JM3ISzcAumovQHl+eE1NWgP/hxOS9UYEPpb9pc+pt2kf6mUXgKx0l/01n4K6bjabwRf8P1eBZL8Ry+JnFFRyWu6LQC1qYc1bEZ+kpcmD+2xBrYBQOwN14u8UFXSH2KfOQ5Ie6W/pLBuNYaLyf9wVthCLbGhthO+ru3xzbYAfthBEZiR0zATpiLnfFG7Ib3YHd8AHvgKuyJhdgH/4l98QXsh69hf3zDXD5VueV5G3XWlfsKKfeVUu4gbIt1sDMG40gMwXEYhonYAJdjQylnI1yNV+MWbIzb8Bp8BcPxA7wWv8Um+As2xd+wGV7A5lLu/Gry3E+eA1Ju8z3VYuUD6Z9bH4dhHxyBk3EkzsBREk8yBhfhWLwNo3EpTsDHcSI+hZPwWYzBd3CKxOtMxY9xBp7GG/ACxqKf9LNtionYGpOwA6bgbEyV+JvZOA/TcQlmYD5m4hmci8p5Kwu7YzbGYg4WYC5uwHn4Mt6Ib+F8/AQXYDkuxC/wJjyHi1D5Mfs3rI63YGPM439N8FZshouxPy7BaXg7xuKdmIDLbP3J5Xkfmgz6k3eR47o7RmAPHIw9JW6qF07H3rJ9+mAq9sU07KfuBz9c4sNczEc7YLh789bGDXc9b62yXJ5qffkOy61TLVdoLZ+L5YrcXF+ZtXwulqtwc7nAEa6Xi1CSLHc1yTGuiH01zxdvl+vaHfijrC9OvveqfO8qXCzfS5frYqZcF7Olv3EO9pI43n54I8bjfMzBBXgvLsT7Jc73CYnzXSdxvk/jLbgN8+T6eKuUq9xHnhlY8qBclnGR9jvEgZ3AevgdXoMnsTlWYF/8ASPxFE6R/tLJ+AsuxF8lDvk0rpH+009K/+nteBZ34Tn8FH+X+6jzeBYvoJ9SSKXfMlbDJuiLvdAPR6M/jsMAnIu17Od1eU7AvmtwXt8jx+FeDMEybCLxhn0l3jAS98t99gd4M36EL+EBuZ/+WM6HByWu4RCewE/xezyM57EcfSWuMAC/xDCJL2yIR2V/oxzy255tLOVWzuM7pdx1ZPsEy35TX/abUNkuYbJdGuIcbCT3s42RctMWlvKG43t4LX6ETTBQ4n5bYDO57jfH1ngdDsOWcr/aCqdgG7wB22IitscciROehxF4xI+/x52p7rKPtKdz4Xjnwflz+zt72tfZOye0d07oP9JXOfQSzXkTMsXXpwc=
*/