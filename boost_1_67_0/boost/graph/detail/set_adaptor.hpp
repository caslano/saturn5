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
/WeNzaHvBN8UZU/E17RZ8jOmVKAWd+qrF/BxhvGRpi99iX2DyJhn0DMOIOG3F8S3zGg+DMgK99kfztY8jQc/SlcgzTJI030j/JiHP/BN8VR9NzBPZO+EThnMFb9/cwi3TXD/BHtPFA+zdJ4JGdYvgho3k8M721MEdsmwMoEM6+LLIJ8O3gq9tNjGDxzUKa44QDsy2aKg4CFaAHHCdFnEF+6/otHSPtVpKJUCsrXhOPehVR1VRRPEHtbFD9MVO0jngP9v+Mh0HrI9zXzeJVPcg1tbzL95DvSF8KD58/dLxnoL3iOtpvAIqFCcrP2REkT/yKWWlitofs5USH/Kpfz1emN+dpt049XWx4Nc3F+34OFkWPHfBJe34BKFrLUmrG1vF7fP0ZdkEB9Q3qb0/us9FH+IGOx0kKLQUsE+RC8WL6AVnib0tmKBeqLfYU8GRm9oMZ8ZwHX5Ri30ALi+iPfvR/d3vXCF4Xk+PW8QJs58ASfuW4OxjbW5dD4mlzethjpG24gMxedE0lx+cjWtEel5hlOe0H5yz7UnNlriwB6haqJgknTi40nyDA9HGJ2Il3IudMtssZz1VcsVe+Ph0GiE0N4GjqK356Fh4Dpg/k5XuFkGA79bgReEiIMY2s9GzmkI2g7u/3NCJpLnGT06dgK/9UHJwt5Ad3P59g10KBFctwo6pICPVn43hz5iZXtYH78LOhPdSiwRPnNeq16XfCcY5F24OcXCwoGuXajL+RyRFAzECn3rX6HQzeTjTpcib1C5gUqKv8XfNn70cyp0P+vgu8D9AieNFYhCXdFC/Vjob6myiNIkKVIjG8fJynGdaB9igAsecNHF3oY9ne0Qjy4+94cw0De36+ccce9K808gk/lQS5eN9Zx7ie0On7KfW2/inz734FZKZIJMdx5g2lhKRqzcLWGMAAvI4Ra5Ai9DpXspBONks09eQWubT+lLJfFhpVLi/YfQ659W+vd6dEkEHnfOTozlUlQR6c0KZfahYRah5tThlV1aqSQmbNbTmWJsTs/Uu6AvuqddZLwx+uQj39PneV90S9tjpHEbb4Ybb8bqb5aOZnv4s3gEapqbWSu0tbTabYW+xd86pelTxDz82IM+yjxva2gKfFug5xhWoT2B18KGz1oiTN/sHx0+awsNKwmlBp8qBk0+ItiA/ziCIfxnSLAK/uFD9+KUYEApTvaMsGh+mQjCaA76TWHDWqkskuHZHwoI5lsaaMwGV072eFtFXLyFN207jzu/XlzV+wr3U/bQHUr8PTybchrh0YLqfE8+21vKj4d1cbW1rwk9UMWrPrcS+nVtiRBZ0UWuEOdg2Dc6bcKgYGhQJC7dRN6gYQPzhmUPzSIzQMiuixJhRGQ0xi6+J7LD/Bi7JxbkIuHoFj2eA3UxuVNHSxY040yG3+7Wt8E/aic0erEFL0j4ma0zX05iZzxoZHqpnQwuhQ3rnBSXM0mm8btJDD+KkUNi2DIazyURw5VUjMyrinF8l87RCCGGczBivGxk+riNxHAORowlRqZXIFNcKYLHia4kmb6/i2QvRtnvsOv9Y+xnVqgEGRcVaiexdlyLKIaZ4g6qUOt76C9ofj/reQeXNXMOn/tdrQto5AMNMS74yF1kmrq6q/CvqBUy6NLbyNKo4jvBLPYThjQMsLxzZNnpfd7G83ZTqmC0v1f6epHLCcVkrrzTrhPJ/sxqoLg7Mxp2Y4thU0GHxhUfvfVydkECDKZaPQdGylq8tglmyjHQFNnMhv2KDe+UdndK7YbauG6id39dR1c2jSu+6AsxfjChtVQMEJz7IuvJU1ubUNHYp6XefrC7oloOtmEL6Q/2Vor3cvq8PXV/RAMwWn1dGN8tRqaT9VSgdPyG5y1iDzujcbSVGDvSRRuRQQHqM8avmavMzp1QwbqmdRoVAj9zLjQ21we6h+rss8SOknc1/hUz/wU7TfxjDWEJw/z60js9K/SMdoOpC1y/U4xMXHbPLwVBqnvNrS/xO9vJrp+hGLLQqky+n28OGV5ztugIG1sT+slP3j2vdT+iN7FD7wxOUOMPQDkv8viWTODroR0i/g7rc1EA0h/uMfM1hL/YllBaSwH1Sp2Zm1t1Iz3oN7R8KUHtzNYppPC19Vo8hfe2nNdiEwGkj9f+qXxrfRLtr26JaX/c6jS0f8vn/bT/x49Gtf9GQ/vPPBWv/V0x7d9+LdrftpNUxzhUHaOH9NP+rqjazBRbUAlq031VtfnSDl2ZHd9GatM1GLVZY2R6eRv1Mddg1KZ3B4kxFsWo6K/9XeZJrP1aJ7GPt+sc3bBt8JPYK0amky2Dn8RCRqbft/TT/q6BtP8PtpPsHpR9pqH9bz1haP/sRO2fPbD2d8W0/43bde3/QIL2V1p0xd32sUn733nGPM5kfic0SFhAIxgqwEKu/aIA31RjqACnGHX/sU0n6TkRnQtcGQ37Y3OBKzYXuGJzwUP/Xdr1x1RVxXF+6nuKvIc/KTEJSQkwQE2p91rPhaU8Z0ik+Gtp88f17ZU0n8sNbWqwkegkZWVbrbbacmtaMwUR44E5MHXOlluGPMOkeQm2UBGfgN7O9/y499zzzlsy/3jb2b3nne/n+73n++P8/CLrTvJ1Pao/mEv8wcoOsxU5+xj+oLGJs6d3/Nj+JDJ/YDf8QZPuD5KYP4j9TPcHycQf/HyD9wfj8k2mxqrGXNP9QSITSh6skDyGP4jg8c/k8fP+4KzgD86Y7e5Ag+APlnfx/WGEmn7a7A+szB98964+i0o6w1eNgoV+q7ZX66ygyRo5l5CEXIIPkdr3l/ljCtBWNwguwf8PD22kuq9J2lWLUr2F6igRXVQjm24iVxcSKMncttzSpYjGABqJ4P3uYLap4Ksu0NSgoYZZYnQ2+rFWxxCylX42+ZWqj2yQM/HlAP/XjZENzjiCP+US9VPSQoSh0/P8DHwa/gOcykmjrSy4boyoLnOtLCatDLr1VrQGhiWTiQAuDBFFEGw3RMCSp+y/YhIBbwclIljfgEkH3VgEFTrZbI5stkh2p4xs21DI/vsTJttLyCYgsjjXgBf9StDPB4mT0C8PX4Sv+33anUbBeSYIIJx4lg/ONnkdF3GmMivqUiUZvzb1R1fiTEdoLJ+Hl+itlc0Z6AnMu1yylbfgtXuoi18OrzyN1+6R8rjIjM3wDASg6WG0o3nLFMc532TUjivjViAmPhDJJnt2fwAzXE0Wx7ktN6mgII9xNpEfTqyszwvtIpZnAex9eyUZ1cjGddDfSJLMPEiSqX3SbmjVCtj/XP9QY6sHlaD6rvJfbOUwkzCzEc+eIGTlqNnb10i3yqGk/6fZH09yzeJGqYTQH7AYXkAvbXvLyCaYxEBME/mkB+CTFkqcY8op6lGXoZY19JeuQ6a2tjsfrZ3WetpOAm2n0wKXp130rFK1uodQSFb76nDwWKmHFosxy+LFJhcL1D31ZApX6UGdTD1C8ry52N6IgxvZRTVefH+13tuYdYJKm2mleXFwc6T1w2CMrdwai0+RkMuPcGiMXH4uSWIGsySQCEldHdC0JXvdLnVCCqRbgHmT7Zc06PHdho5PrGeWwsmZOaeobGMDEjPXMRQzt+skVjaVKNs3J5mOuzgdd4lkv2iT6Lg6FB0fSch2ELLTdbJ5HNk8kexUGdnuoZCtrsNk2wnZmjpGdj5Hdr5I9vurErI9QyE7iZBtI2RfruPGODCBPQHf1QI9K14rLNCh4JubtIKF4IyN4YwNJvTxxteb7+GpZ/DjCs68a4vcEouzhMNkbAttEWoeRjWJ87aVfYv7odraSpiCHEXVJAGTnhC3UO0u0Uc8vWZvvr+GbmT1qq9dRvGncmxOll257M4i55hQy1UB3r3b1R/qzJFHPPbtrkI1Zz3x7aDVjhpzvN3ZYsSeBdwHsVX+TkyPAru5zhNe4jleygReCtRkykuCtl/gpfm4zkvpb2Ze8Lbg8+qZNp6XBLXjRCgvcO20um6dwcum44wXYs3gxJvEBllqqQ26BDYovZYpfJEeGhTR0OC5P4zQIMiFBrNryVFSw2x01LAeXcz16GKxRweuSHr04FB6tLuGHG4kPfqdGiFkdG7StJboCH3H9Vo9aFrraLaVlRKXN/5vI3CykFwf8PHoGv42uobvReMoJu/RNryTT0s9vjrSZveMUE4hAJ3wxjNMOQZliFM9FuUQlLeR58WOLHvXZlT5c/Swy4OeVENhjWe4sgcKxejVDii87rEqPii8igoKFF5ChZVQmIUqF0EhAz2ZD4UU9C+nG69ERiu5brwSOULJdOOVyFgllWhEibrTcUvzxKmzV7Ils0x8bxNgHuOzU91WS7UolkEn2a2nEgKxj1b9A+jdSLIHCm+2yoVgB/yJOZUQFpC6czAqItzAz/828Vn4myhcD1FMKvYxUav3b0h6SVwkTiezYUUoO+N844gW0suzbmbqWYGSCE8uylOE2tWPecKJHlyQ0CC3kPI0Xt836tS702GQAFYOL+cNvTLQcD9JiEe0E9BHl4eCniCAnmGAThRBz+43PoTL9CGMXEYG6CDUxpIuQWAq4Ow9knTJi3kwzbqPoB1Lh07wEkZ1cC4VdRbrcnZUBgUT5X20ySd8KJBQmx5EReyGIxDDfNOz7BWLLBjrWBHr7vvhsD4pwbpQx+rTNdUHmlpFcHq5IQ6sB5b3+axkSc7eNQMBLl4WKtmJvnglzo0TZT0IRuGsQoyeYskhcFE4dD0YDmiSBOjX9xnQrZxQt5qE6m83CzWJCPVYsUyok7BQvYMyoVpEoT4fFutTEqz3ggzrNg7rNhPWMQLWZILVIsU6GWNtHJBhjRGxfnQvHNZkCVY3w0o2RLpht2fmVfSrjMQHX6t2kNVV/Mykd9WEkfw/qd6hIUy2atmUBI2g8UUqUb05S0M7yNOC6tWm6aoXIXJT3xeOmxQJN9vvMW7KCDdU+HgXikn+B66Z5Z9G5F+xRCb/KVj+rn6Z/AfzBcTWsIhTJYjP9zHEFfRqChp+VVCvLNq51oDEOGcSYZ97M1TYzwjCzp+mCzsoQl90N5xxnioxzvY+apxJIloavOBdrZwFSQ8YMUwusyD4xmtiQcZLME9DFqQnH1uQ+l7BgnTn6xbky95wcNMkcNfcZXCreLhVZrilbQbcbAncDUWhcJ814MaJcFUDbs+dcHDTJXCP9jK41TzcajPcC1cNuLMkcE+8EQo3w4C76o4At92AOzcs3EwJ3Ggd7kEe7kEz3EkcXKcErlUCd7oB98jt/wDkqTznnToAgENLzF17eFTVtZ9XyAEmnAMJZJBgYztAJPkQi7WRRIxAklGSMHkSa4RYX2OKXjCT2yhg8ZsZzXAyylUQWy8q91aLtbVYLcUCNuEVEJGHHwKVKNbXjoFKeCYQMnettc9zJoHPP+79br7vTM5r799ae6+9z9p7r71WDLlHdXKfPTUQuZP6IbfitKpY1BCtTbTOV2PqIhb8Q53eTKHpTQvvIu4r66+LuI66iLHQJHBPudJFFPAu4nBsO/u6K6aLcKldxOR+uoi1wFkgx+LPMIxgHK/DeGSroxxOb/sDdw/AjdE++T2f0VdGgWScsmrNGTROwYapO64LWlTHdVNrefA8p0WODjo3TBoBx9VwTIRjChy5cOTDUQLHHDhq4XgQjkfgWARHEI4IHM/D8fI5s/8Fzd5lndTPLgTyyisPwq0HH0YlFAT5MO7ShPt72X5oiYGLdj/UEhv3QTQamRENdCeJTznt5IIoI0GU8LUL6ymAVFGsCyV81rd/4GdbDg787N8P9P/MbFo7O+/7x0I4LtoJYeZ7A6N7LvMsa/PAz9YdHviZY8vAz7LbBn6WNkBJ8Imuo2QbxjdB+YfIUjlZgXY6fUeLaPfR1WthVEpv4vQzri/Ju/2P1qWz/NfgAbV7Z6jFXwoivZtd/xoOyqt8hyGt74MiGoun467B7D04FsdQAtXUHqpfJxFHw9UKku9fjqOV5G0E2vENrcKWY+Yp+t39fGfuJlyr2655wr8SA3f9rh8G6oGB4KtGBkqIgQWvxjOAk9Hslx9oDND8zaq1xECWxsB6NzGwgUA7rzVQr9waBafvoE1UEpysw6yfoWH/iddo9ado3lyzk7Dlw2yi9DgcLrso9cL/Y3BMhKMAjvlw7+fw/wb474WjCQ4rtKbbHKKE++e76pIiL5HZNOObyJ56jfsIeJyq410unhLuZx7bS/OXuP8V3puH71VlZFa5A//sDVwQFmPTrWuJkkMNbgQnD+7ouGje/xo27n/19SLDe9mKTdGoavqHEUmjZVSSD8Ft30n+ykI8/5Kf3wfnfD9hhdshb6mKLLByfxmqv+kdgW773Ibxy2y5s/2O3H9rSFs23ZpbAKf3NwxfNt2mnA6i4Dlbdff2PF6H3CV7KJzS47MSLG2DpGLAVDwTtlnxqmPk7QlqPMouxoChczPdgtU/uIrl8y+a+j70HeiOpgj3pct8QstTxWM3WZ0UD8MT6LZi8LSGUXz6GM3Ojs535x1Nqs1CEzkMJ5jLZVJ9xDuaI63qTM8YtZ/ikcqLoFOCrmdhkt2Cvr9pN5LgVQNSYCu/vwASLO3TLxqdOy+wbfJWdf9kmlzs5LmUY1eG/bT9wzlTWqZEc7rQ46b8aRhEQAzgJq3OISgOSnnbc4eIwQS4m5skBi/h1/+IfLE+eVli7hC/mJvkH5qb7l9SmNPzyAno9Isz5EOZH5WVs8oGqG5QSLidALnirXCnY/ybo5Xcg7kYouDuh1GX5b7duWPz6ZjJ1swd3iomNaDDX0kuzpIr00rlYleZMvvtZaG+KHfidbozO6en/sllhdZCIORMx6O4llCZhcny0zAJGkt4lXRlrLhP3U8hn5eL0fvu5Pb89MA2F8ZmjwmgMxzqL4pF81lnI+nxn3UuiKU2C6ltI2p/7h+Q2kPk8N4FSOSWqTiN0Ap0uBmgeqTBq/Jp9uJQu0UP8ZNTg26vHuLcmpBvBOTMvjlV7Nt6jlsJtKSVyZWu0jIVd94liiLuBuw83tPjTmKncqraa+/r50vuArn3ZRcroTgSO2x8AxutSgs8ikiWKYqIHvvzffVlwRhFxJEjiEHSJBdKvpZpSsZvMhvfTCepEfy0IKH6ZjopXEGhL3n2v1Czd8Zk779ZDVLSnjC52Nh8JrYnZJhujG5PSDfdEEAOuVTERkrV9J0/Do8vpVquB2CLclXxDObgOZk7aZU4WdMlsrV7uqbhYY+STJpIfixXJShWF1HiPE3Wnma356foGXZEyAmWid3HbsTMlISm8FE6gcrTbPT2jJnlp3TOUgppl5rNNCNFelCsxpFxFOlc5juxLHDmwVPnYhcL1NFAiuJ/x+8fSnHHQzei34DA7qgadrwiXONuZE9/bbNwjZI7WMcg1eTnYakWqkPRrr3wvp+VfGPDYfNzOg7takDf0hYKXZuuDZuTXUp87FQvuc9s1AJsV8amtqup9UH3wdSBUqfGpnaoqSdrqVcNmPpIfkzqBDV1tpb6jgFTvxibepCaOk9LPWbA1HfFpk5UU3u01O2jBkr9g9jUaA7lH83lQ0u/GtLjK52C6lrZl1tsqPDVX9p4fINBmrf/9FKtxgfH13jNVzYcw62ZqaK7OPoQRB9BOyhBvAog2xjYdVMMsOMRFmeORime/PmmYgV2qHGPMof96kuCnajBpnNYJ4dNKSTYvV/EwWZMNsD+6Ys42HQdNike9mGEdbG3Z8TA4tqgP6nOAZg5U/Rpb96UaglrBmIVC3yMWuuljTSGZRoNqIaAEr6khnR7LBDuD/KPVNURpVJ3phhCzZuEYkhs+uH9pW8aMP3702PSj8D0WcuK3MnBXRjgI0XLZAZmkmIM+XH9gNnWx2abHJOtnsnxZJ6tDvSP5H6zxXUZ9Ihh0NsVfwo7+/lyzKwb4VucejnfAcnX9OM7oCSrX98Bn87WvGbh/lQJFdwqR+iALMzBbf9k+CHIBbQjyYYBSVBbxQiYoQPwbBc8KxEy32/tsZVvhE/sLZlHcj6rT8T1bbiKfcW+N6e1Ugx8jCzv3N+hJjhcjyA2e2t/79ePoLtEhEBE2Ntaj9nQijSdfZ1Hfu7kGneavA80P/QaF8kKIb+VpWXw7U9nqdTMJPI7ZN+Ou7hYBXz4EWI3QLR+bist97IuEDb0ybYNt05qNOxEGnpgTDfYy8KFqjkIxuBKu+vOiHODfd+8cJUzXCKgH7c7cM7kYQGDwckHMz9qvWDLORRxbKYZFvSo7KqfZd/qrSxnBxfhCEqQ92V+RFUBb2ZeIMI2BogwtIWx74RsyUtlemnmyapy9oPNVsB3Usg4QKqUL2V2V85hTZBZ5ZzycIHAiheRAYubwo8AVDnr3IRpXGoa3PBHrh1mo982p1woUIERx+c6E+VTmV2tfTbsVLx11jIYCnSiDjgbeXZGUt6aF5bmmvzLV8kLHRQO9gAUV6mQ+TFwEjrnvwb3r+2AjHP21Y+Ub0XX7II8IiwFWhzhWwXy6I53bhVoDxvG71Ucu3P/cSUj4jdDNQ9TN0PJdwl8N9R9J9Hpm2/fS7dKU7b7/gD/wvnH5XwniG9xSp3FG/5LLjrOX40B28KbM/A3UoRK4N9p0jYFF/bfCDosOwKoDFinfBJePZkS3EC/2fAbWYkJyqa0AJ2RCO46D9/Vyz5GX/Q0W7iYvmQ4Go1E0C8K65wOY/kQnqK5QH6vlT04NQE9In3ILN4ES85WMTgsBcehwV1i0AFn4nu7Aq2bAz03wMs28alh0EWK68NF14pS1B0R4N/SRmu9GDoHTVyuEjKrHDSWdvh/4jtcgnv88WcF/pzF70MjnEUiDIbUbOGlS4qz1xBee9n5WSTgslDKzl6tBLwd2lCJnuiG4IKUV+GQ/bXNYYHzk8jPnfAmPy2VI1iQQKad/eU5h4XfRapZQeRMtA14JecuHWKU/MPoUTi2hQWeNvzqvTwHR1sIz6hTuulFh0VPfACdy5j5pF34Op9oIKDw6esCCsO9Gp947WWizmfSZfncu4P4xElRVj8W+cRTnc8EtvpZ5NMSVfic22zkc0LfFfkcZODzP35t5PNbkPllHitIQWjMMFPVCsCy31y1Y5Dlal61IHrs+Yt61aJfB5Z2O+8ER1PosdU0i1S2GHhzITUhEvrPL3QhSYmgOm/GG0uyZDvGryDzNDmCMRxhvJTWg1NeWe0ra+G6fYxMeRU=
*/