//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_DETAIL_CONST_CONTAINER_HPP
#define BOOST_BEAST_UNIT_TEST_DETAIL_CONST_CONTAINER_HPP

namespace boost {
namespace beast {
namespace unit_test {
namespace detail {

/** Adapter to constrain a container interface.
    The interface allows for limited read only operations. Derived classes
    provide additional behavior.
*/
template<class Container>
class const_container
{
private:
    using cont_type = Container;

    cont_type m_cont;

protected:
    cont_type& cont()
    {
        return m_cont;
    }

    cont_type const& cont() const
    {
        return m_cont;
    }

public:
    using value_type = typename cont_type::value_type;
    using size_type = typename cont_type::size_type;
    using difference_type = typename cont_type::difference_type;
    using iterator = typename cont_type::const_iterator;
    using const_iterator = typename cont_type::const_iterator;

    /** Returns `true` if the container is empty. */
    bool
    empty() const
    {
        return m_cont.empty();
    }

    /** Returns the number of items in the container. */
    size_type
    size() const
    {
        return m_cont.size();
    }

    /** Returns forward iterators for traversal. */
    /** @{ */
    const_iterator
    begin() const
    {
        return m_cont.cbegin();
    }

    const_iterator
    cbegin() const
    {
        return m_cont.cbegin();
    }

    const_iterator
    end() const
    {
        return m_cont.cend();
    }

    const_iterator
    cend() const
    {
        return m_cont.cend();
    }
    /** @} */
};

} // detail
} // unit_test
} // beast
} // boost

#endif

/* const_container.hpp
KI+ZXI/XgbFgCTgRrASng3PBEnAeOB+sAhdJ53h7H8T5HIx9q+/VM72rZ3r/sjM9ex+cxcGM6XP1zO3qn6t/rv65+ufqn6t/rv757/zz7zn/h/aSin+O/v+nIi3id81ZvDYKgwlgA91f+FCrZn+6MGdufja2pXMRT2VFPiXGbD+aw4aJ33I+Hfnbfsvp+t1mI1c6vV3Czu/dR4Ffgn+DbK02ncUlsysKSorzy+a7zh4poTNLi+rS6cNxJFrCeE/4DbI/Y4vHnYDdNptGH3EE712/SjLP25Lx92HcjF5sS+S9dTW+OD7Tgsa7xXQnQpy/BYu99vLcnKKcMot0Bv0yhR1GmgB4D57j6yrOpG+m+MJYt7+HDiIRV3wN3R/A+cUqcb76EsV1zNYLpfuqco51eqvP6CS+fzCanhFPz9hnMTiD5D32KTfSOZD87QGOS6GwhyzG3x4YC9m1FPZ5q9t/QRz589npQvK/aDW6HzEIPErPeRPPVv2pXvG75FKhi3wLxeFL9tmIcyfZ/yCdgc3DGYu7/P9aTXFiu3mlaB8PkltPoQfoLNnPoa+chhtkhNv3eNJ76jcA2O33iqzHLILTtZL87lPC0DPG4i7ESsXbEkZ+alzLFMSPpywXOsRXk/sA6fy2OKd8lvs8ZQ/5/4hnnLC04La3m9xOKja4fmkJxOmnP05Th1ukMlfrhPL/Ug3rX+I411N52RWyi3aRIL7pcDf5f2k1+k7CCIQvd5W/7QaMBS0sfHcC5tlI7RnG9zB9deZd1klziv1TQ1wmoInLHEYcz8Go9iOu7w8gDPzY3BgGNx5/qnnAMTvfQD/VnG/UWjz1Lm6T9H+Hwb5bnG2Ivkxh9xmcOR4yON+Ir9aeb1wr7Np7F7E+nuP0cef4t0Qe//RDtLF+UbRpDhdm2K+Hsr88hr9wBWP4Iv1vwOvSH8860fOs2HcGB4AvIvyhJUbno8iT+TjOYQaI+1jeS0nfg9VAnzzL9hP31Gwk+7FyyfIYjz+K5bNlNO7yGanJuM39xILwCKEEKlt53FafkSbuWN1N8VXihluCoT6AkSJMbzG+/kz2tlbns4/qdAFIYy6H4zsjnNY327jTigCiTwdSOkJE+Fhd+G0m4/04yF4guc5WNWyKOyzdR9it2lGjuco8Q90wxQi3l9JgZbta1smyHgLxHviVytazXvhsG39ycklHML+/HSQfiHpX/UvFeNSA/PyshvckeJz9kdLf0doHbb8h65F+CbLH2DwP8wzMkUA3j4Mvw7xCpv5nqp8tq9/3GeQxZ43JmLPBQNdCLXhUp2shjMcxtA8RBzxMv51ybKnQwUD2r9huY/vEZVr/RWy38RgWz3O4WNbn7qz/tuBw8CdnX7+J+nrBDHT04fjUk+FcjdvueZJtrYg+T/ZYjY4Y7uPs10v0pUtk7ybuRCq6d9XfyL8VxZ0pwqdahLxufvI9+XfgOZQqnyTfpYjX91PIiH6GuhayiFsjG6uTRRsw/T7LlyR3jSL6pC4s2othP5zt7FskF6NIdx/i5Dla8M1O/yayf7z8HaQI8vdXVN3bK3XfFjrF5sZ66pTzWm6qo1D0h0L3fQLWTyj0OsWpfaFKuFGdcd8S4bis0bfYDXLCbY1BH8i8WXvvYJ7OfpfOfpjtFrZ/IPy1fSIzkHWjwbMVGAb+jPyuWS71ibySyulF+aZ9Yi/J/sDvQTVstIdusKHCL1a0+UNk/8Yty3dZMoVsF1HXT5JdMb3//Bj5+3F/UMO3N217z5L/z/K9G03/ep38P2Jdsty2rrA9bbqlTh2FOj1gKCduc9x2KEyhQXs4t1xbv763aO0dYZfbQz+d/2SdfSHscvvoyu3jKF9GXGs=
*/