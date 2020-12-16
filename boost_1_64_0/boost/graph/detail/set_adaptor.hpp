// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SET_ADAPTOR_HPP
#define BOOST_SET_ADAPTOR_HPP

#include <set>
#include <boost/unordered_set.hpp>

namespace boost
{

template < class K, class C, class A, class T >
bool set_contains(const std::set< K, C, A >& s, const T& x)
{
    return s.find(x) != s.end();
}

template < class K, class H, class C, class A, class T >
bool set_contains(const boost::unordered_set< K, H, C, A >& s, const T& x)
{
    return s.find(x) != s.end();
}

template < class K, class C, class A >
bool set_equal(const std::set< K, C, A >& x, const std::set< K, C, A >& y)
{
    return x == y;
}

// Not the same as lexicographical_compare_3way applied to std::set.
// this is equivalent semantically to bitset::operator<()
template < class K, class C, class A >
int set_lex_order(const std::set< K, C, A >& x, const std::set< K, C, A >& y)
{
    typename std::set< K, C, A >::iterator xi = x.begin(), yi = y.begin(),
                                           xend = x.end(), yend = y.end();
    for (; xi != xend && yi != yend; ++xi, ++yi)
    {
        if (*xi < *yi)
            return 1;
        else if (*yi < *xi)
            return -1;
    }
    if (xi == xend)
        return (yi == yend) ? 0 : -1;
    else
        return 1;
}

template < class K, class C, class A > void set_clear(std::set< K, C, A >& x)
{
    x.clear();
}

template < class K, class C, class A >
bool set_empty(const std::set< K, C, A >& x)
{
    return x.empty();
}

template < class K, class C, class A, class T >
void set_insert(std::set< K, C, A >& x, const T& a)
{
    x.insert(a);
}

template < class K, class C, class A, class T >
void set_remove(std::set< K, C, A >& x, const T& a)
{
    x.erase(a);
}

template < class K, class C, class A >
void set_intersect(const std::set< K, C, A >& x, const std::set< K, C, A >& y,
    std::set< K, C, A >& z)
{
    z.clear();
    std::set_intersection(
        x.begin(), x.end(), y.begin(), y.end(), std::inserter(z));
}

template < class K, class C, class A >
void set_union(const std::set< K, C, A >& x, const std::set< K, C, A >& y,
    std::set< K, C, A >& z)
{
    z.clear();
    std::set_union(x.begin(), x.end(), y.begin(), y.end(), std::inserter(z));
}

template < class K, class C, class A >
void set_difference(const std::set< K, C, A >& x, const std::set< K, C, A >& y,
    std::set< K, C, A >& z)
{
    z.clear();
    std::set_difference(
        x.begin(), x.end(), y.begin(), y.end(), std::inserter(z, z.begin()));
}

template < class K, class C, class A >
bool set_subset(const std::set< K, C, A >& x, const std::set< K, C, A >& y)
{
    return std::includes(x.begin(), x.end(), y.begin(), y.end());
}

// Shit, can't implement this without knowing the size of the
// universe.
template < class K, class C, class A >
void set_compliment(const std::set< K, C, A >& /*x*/, std::set< K, C, A >& z)
{
    z.clear();
}

} // namespace boost

#endif // BOOST_SET_ADAPTOR_HPP

/* set_adaptor.hpp
21sBbv3Ssozb2+o2lB1uc7NzBmX2zDFxvmPizEnv3yu9F4n3y8t31X1wdjoXsG9OWrad3vf8zydrUGb/HN/zed/jrnmRnZ2bnXm+r/sH6p4zaHB2DlFrUTTuH6p79uDMnPQeue07pOYO6N/XPufDQe52uj8KcOvawQ73Y2+60wblZKa5r1UaE3Fs9yPq3n8AFzDH45zt4/6JcddTk+JL/5W6f+pf/tIG52Tk9k0fkt7XR+cz1aGEDLiQrBswlAKRPign2+f++Nx7j/ZNy87ROT4t6lpmz8al4ZYcUR5YkZiL6/EtslTGG7orIiodz7gNValyf0p7DCNh6ryhPEwdTDZmewPqETvM0eNKi2QfqsA1kc244FL/tWG7ir03o1MdMp7nXsJzWJ5gSn33Qha9HlaivT4sYfmvDzuozvHNpZD1Yf3XvzVjOIkfmYnfbx/MtyKqztO59vlLpR0yT4k/ME/3aGAFLtKjzKnPtz+fMKWCxi3aHu9r8lP08EV+M1YZN3lueNzJDnVvKPZL0L9V7H1c8Wbt3smFZRXF9jhxE2YdsWdjXyf2gS7vGsen6tjcVqHP0Yzx2VqGXx/7kjJ7zM8vk4LH47w3KXjszZ5JwWu6b7FlZmzQcltmxgFNtWUdvONxYo2sq9i/LvXau4j9gLF3wu5bVsrMOsLkNXbJa7O3MPmJzOSn3zrm+2pYcizHnIRZink4ye0p4DrnMnp54uSqrrXqJlshrrW6NzN7mTcTO/sf6brLu5JkTW2/+XcjROcM/Axn+dETnZP023njW9abR1d9/6y182BsYbm0UY7rHvLelzm1RM76mKzFpBxSn7JnhyvjrMgD2keyP+y4snJTJ6leb6uJjtP/VuxFzo7MGlrCffCqVZd+yrGOaPVPr7IZC/mZ6K4ze+J8IPZSZxRzfBJEh92bK5AxQmIAYzDH0qOPHF32oRX5S46ljkR2g3IGreleRHjJotONtGE3aVtI+Hn0Fccy46MmfaajHfb4QMaT6X18yRS3biWxRquMOnaqd9zlSM9YTSkTjAmbXC5jBJPtuptDss3U1TskLfscqx0t0EFmziHGZ9zn1HEF5UVmXOMRSe9unUvk1X+IMZGrOGv2Q6dM5MTq/IY5bHvURiZzBM5tMGMezxD/zdROrST2uCrnNsTD9uKeKHMbvPHt98bXJ+YUmcsSHhMQnxlTq/ldYXVlDliCX5ynMya0hjWakQ8BcZtr93O5zzwSjbtvTTM38UpijoiMifnN+SvpUyQ+K17L53SxX4R7Zsg5Hd1Fp4XE3UTj3mXH/XNMC29Oh473bgmjsZm/sl/s4SHj3Kr6MmeH+iQKWSszz9H/d+M4MXKfV0pYoceNzoWMG5X6fLGU39rUzakdvGMYt0LuS3TkvhZZMjLKNjIp2371xW0nWXJcrnXxfMwg9zN3qqkvxpWMK/edhzEaaJny6iX5zsOYYtnzb9Q91Yo29c1EU9/eLG5TxJ5ldO19w/YSQYKVLf7GU5FGRZj3O3NdjomfSBnLjLocz4gsEb/IdF7shyLrwN0R+Zt1ebzffFLOV2X2PFI9R2TdTX5P9MvXnVpjd9F8bY+5siF12DSffC33LW/2HhGcl+o1soLbJnY7sIPoNKdWdpj8xp/mYTfNj2Lcekg6zxG3JJO/2XV+9bl2QXD7UNKo7cPAZ7zJD/xI+fPLj7V6cfZjmmAewPRKpP1s50fxxJKxofJD9Zqb+TsLxL5B8ie+irZbH+OnqZkXP0/st/vmjambN4ub797NjFAutevareLexOTlFWLfaPns/U1jhQ8SGn99uFR0Vv1Te6tXld/x/vlt9rkoFbmmlzHKkjfIW+iY5aUB9nVqH18=
*/