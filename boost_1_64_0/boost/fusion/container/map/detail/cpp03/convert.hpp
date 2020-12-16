/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1340)
#define FUSION_CONVERT_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/convert_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_map
        {
            typedef typename
                detail::as_map<
                    result_of::size<Sequence>::value
                  , is_base_of<
                        associative_tag
                      , typename traits::category_of<Sequence>::type>::value
                >
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef typename result_of::as_map<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef typename result_of::as_map<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
seuMZ/2/l7R+VHRWxn3OzHP/h7bUfvbEtf5fq2qD8VyusfX/chfZzP1HxrYOXyLr/9Uusp//x6rX8QE4PoB/iw/gBt0HkPfY8qF59Ysvbtj7gS5X/HbJYdF9ALWNifkAmhsT8wG0NnaODyD3suR8AM2XJecDaL2sc3wAuYsS8wHULorfB+BhHjF9jOMDcHwAjg9gbfQB1HFtLkfeQlxj+UYTMgrxI3VjHR+Asznb3xj/95RM8VYGOuH9/9AagH11H0CwWnED6PP9cYZ3/+davPv/DGXzF5jm4GJeIu89d/Tu//Leke/+Lze9+79Ys0X2K2u/2bz771pobbu8+B91Hmbz3r/0Gfst3vt/Fr05Nnor45hz3z4o8r37z+18CgttfQqiOLb5dYbN/HqFzfv+zdZ6RWf840N7V7qNNi6Vd/2fWZj4e/HvLQyPFaUPZ9m86597qY1/QpqT6NoF96yHDnnP33dp4u2ZeWmoPeoY7G7xnv/z2podansSGoPmd/yXW7zjX2Pzjn9Go43vRcyIxQ9i8r8o77d/3tXa/5LfaO9/iUe344NxfDD/Fh/Mu7oPxveZ5+Lzt3ng7a3T3q4Z8Kj71Ojvt+cvsH//+kB5v30U3BoeDA+Ch8Cp8FBYDg+DAXi4cX3Ghfbvt7vl/fZ9YSbcL1wOWWjvEzpKbjVHwxQ4xuiTWWjvkxkkPokhMAduA0fAbaH0A88x+37YXHwh/Qy+od3hAOiGA6UftpR+2CpcL3Kpfb3bS707SL07Sr07Sb07S727Sb3DpV7Ivd3ehzRefEjHwr5wAhwAJxr6OaPR3vezsdiVCreCvQzl8hvtfT99pJ83hZvDNPH99Bzn+H0cv4/j91kb/T7Z47Ab8SN1SAuyGulzDOMIyT/G8f38E/H/zlj7LxT/726T+99gEf8fHSX+/yT15dRHxP9HxZNHHk/8P7feNv4/Kta/4aPF/2vqreP/o5KMSdvF/9vq7ebqseuMJ/7/tNaPDcpcMO5zZo7/7xKM/xcHw/+xxf9rVBuUc5ls7v9v61nPQdsa7OL/o6KOnY5y//NtYv85C+znnrHodOaczpzz3zLn7Fuk7T/ho/t+3K7g93fO3eKcc5++f8Rp0eP+OfWJxf1z6xOL+9fUd07cv60+ubh/bkNycf+ahs6J+7c1JBb3z1kQf9x/Ln8/Lj3Gmf858z9n/rc2zv/u4dp8DfkNyRhPGxAPMgu5frwz93M2Z/sH4v+FJf5ib0Un+ABC8f+fbtee18FqjfH/faPE/x+hrKvONAcX8zo7/n9lr8j4/0pT/H8f3Rb2xxj/b7KxfU3G/x9F73M2euOJvcYT/2+rs/MpiOI1FP/PvdhKr+jshPi/7+Ik4uVSdqUpXj68S6SP5AmtD5W2VCZ0zszx8pUW8fLuXa37MuMSG/+I2JFo/sEI2vud5B/sfUni/XkUZaU/Y4r/t1xi7XuR5sQUg08k/u+qt/fBxKPb8cU4vph/iy/mUN0X8/oXc67oMfbtjd3v3NA2+I7U76PH/111ayb+31SXWPz/ubrE4v9tdcnF/3Mv7vz4v27XxYnH6bGLZ0Ln5w/QB9ybE4v/u+rjj/9nHev4fxz/j+P/WRv9P26uzXxkFnI98hrimsC4RnKR6gmOD+gfmP8XVPrKOuX7f1vK/H/17eHv/1H3jnrY1ugH2HGgq/2bXRZ+gLupo2aOeU6r1tfZ/oDNLL4FuNjkD7g/aBP71e+5pdv4AzLmdtyGZP0CIf1umS9/gKQjq5D70J8bTX9lICm/Slaq9jOViI35YRtLvb6Q3eq8L+IbZup3yTimsLzKFwiWzQ6flwLNXP0cLJsbPgf6z1+Yfu53fvDnAX2UeSM=
*/