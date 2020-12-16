//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#if __KCC
namespace std
{

template < class RandomAccessIterator, class Distance >
bool __is_heap(RandomAccessIterator first, RandomAccessIterator last, Distance*)
{
    const Distance n = last - first;

    Distance parent = 0;
    for (Distance child = 1; child < n; ++child)
    {
        if (first[parent] < first[child])
            return false;
        if ((child & 1) == 0)
            ++parent;
    }
    return true;
}

template < class RandomAccessIterator >
inline bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    return __is_heap(first, last, distance_type(first));
}

template < class RandomAccessIterator, class Distance,
    class StrictWeakOrdering >
bool __is_heap(RandomAccessIterator first, RandomAccessIterator last,
    StrictWeakOrdering comp, Distance*)
{
    const Distance n = last - first;

    Distance parent = 0;
    for (Distance child = 1; child < n; ++child)
    {
        if (comp(first[parent], first[child]))
            return false;
        if ((child & 1) == 0)
            ++parent;
    }
    return true;
}

template < class RandomAccessIterator, class StrictWeakOrdering >
inline bool is_heap(RandomAccessIterator first, RandomAccessIterator last,
    StrictWeakOrdering comp)
{
    return __is_heap(first, last, comp, distance_type(first));
}

}
#endif

/* is_heap.hpp
E2E3nghjqe+lS2nfGZz3ON6yslg++20P7WIu1wfb6U+27OB6JZf1uY96n8X+5nw9hPuthZM4T7Gft7EdR1ZQX1xfTWQ/xvfiOnw8zxOWcpw+z/o+xPp3N+Uc5f7HP4T9RXvNYP/63WbGUc/TtF/qIZD6yeD47nkr7T+e+xe2azzH8SjOe4uKTb57PvI0+qJ+VnTUA2Ey9b+A88RR2lcg/aBrX3OM8+sw2svNpp5TaBdLp7HcZ6gP9tORc/QrKVwfc/7cH8/6ZfD8g+vuIdRfFvWXx/okVnC95fITfdifpdzX0D8fpv0Vct2SN4vlr+C4H0h5OfPfxf7K4jzjsqM5tIMPOX7f4Pw2nOvVB9jO+5gf/dNa13gIMGHiU/TjGVxn0B4GDWQYyfH4CO3hMpNuA+e7nFvYD7cYfa/gPq9wIv18P67nue/I4Pw5pMG1zuQ6NI5+5QTjVXNfMc687z6f8zjPheLfpF9kvKMMfSjvs5f7t+H0Q2xnxDKOvxruY97m/vVF7tceQR7Sbq7nN7nW/31pn9TTDNrngve4b+L8vKKrlwk532atpH2wXR5xpj3jO/odIc9jfKbwN/fru7kfHnqrGc/nE014Gn7qOim/1fihnv3YT3dwHzSBfhLpPRFOZP9lfclxcj/bkUY/5xpnnE/XX+5l7LHU6OFQiclny+0cD09znfQx/Q799yD6qVO010Hvsj5XsV130h44PqPTOV5uNvlG0A/4dPYy/cP15R7GW8v9XiHH4cSp9Cv0D/5Xcp7ifmnGbO5bGC/6CfoHjscZXH+EJZp57yz3Uctnsn7vsX6pSNNxrsN5m+N6D/t54nL6v8dpX1w/HOW67thM2vV9fP8s983cB06sp/+/levYB8z708d5bvKpa33DdRv9SBb7e3s5/Tj1HkE976CeY8cbuxmE+vsg9MvgvLDU2M+ieR4IUT7LPc/6xb7Dcwr6gS1r6ScWcN8RwvVkAu2X/vUk7WQX9bKEepnCfXZYCPsxzISjAulf+rN9OfQnqzkeUyjnvuwY9bSN/ZnH8XOI65Rp17DdT9PPMt12lht/NfuL8/hyzlenuR4Z1It2wXwKZxj9JU43/donnucvlbQX+t8lU837Ea+zH7gPXR5n5B7pnLdo10eov7xz9CcDTBjIeKO4T/Ur5znHQfqPDK7nqM+sJznO3mM8jqcpGeyfWWwH/f3qx2iP2zlvvGXCDR9x3/Ukx9Ea1ziln17AfQLPtSf2Y3/Tzy99gecjs9hPiWY+WES7ufgQ2/MHzmfU855szu/c7/hTH2tLeY5xA8fJG+zPQK4rpnB/Q3+xn/kdbuD5yALqg+vzBQ+zPW3s9zn0X/R3Hg9wPqDfTxxt6p/3kPGD+1l+3kzO79ONngP5ezXtPeNx2t8Ss98NY3+MSDD5RY/l/on5jee4XXiM9tGf67q97B/61xGzuV4cQ/1Q72fjTJgYynHP89YT2eyfW7nO6Un/z/lgyCHOE3HcB7P+55fRXjjvTFnI8cL0h67hvvi7nHcquG+cwfUF51e/HMajfXqkmvdb3uF8y/VZIf37btbrNPvjGMfleO5jB03gOon7wULOVz13sHy2YyL78dBUDxPyPPj8u9Qnx+lJztcbmP96zl+BE3hecjv6CmEW++8E108nHzDl7v2U6acx5PpxBtcn/mlc95fSPm7neOA+47Avy+M5qs8X9F9DOf7u4vit5fhmOUOGU1+xPD8dxvEwh+MziHZxG/eVj3If/D7H5830Ozzvi6ffGxLC9eVO6i+T9taP42oA14czTZhzpWsfzXXnVfRjbNegVvp37gv8HjPlbBvEfAewPSO4L7jVZddch4dw/n2K4/RZ6v1NM64=
*/