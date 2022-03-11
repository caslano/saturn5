#ifndef BOOST_ARCHIVE_CODECVT_NULL_HPP
#define BOOST_ARCHIVE_CODECVT_NULL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// codecvt_null.hpp:

// (C) Copyright 2004 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <locale>
#include <cstddef> // NULL, size_t
#ifndef BOOST_NO_CWCHAR
#include <cwchar>   // for mbstate_t
#endif
#include <boost/config.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
// For STLport on WinCE, BOOST_NO_STDC_NAMESPACE can get defined if STLport is putting symbols in its own namespace.
// In the case of codecvt, however, this does not mean that codecvt is in the global namespace (it will be in STLport's namespace)
#  if !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
    using ::codecvt;
#  endif
    using ::mbstate_t;
    using ::size_t;
} // namespace
#endif

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

template<class Ch>
class codecvt_null;

template<>
class codecvt_null<char> : public std::codecvt<char, char, std::mbstate_t>
{
    virtual bool do_always_noconv() const throw() {
        return true;
    }
public:
    explicit codecvt_null(std::size_t no_locale_manage = 0) :
        std::codecvt<char, char, std::mbstate_t>(no_locale_manage)
    {}
    virtual ~codecvt_null(){};
};

template<>
class BOOST_WARCHIVE_DECL codecvt_null<wchar_t> :
    public std::codecvt<wchar_t, char, std::mbstate_t>
{
    virtual std::codecvt_base::result
    do_out(
        std::mbstate_t & state,
        const wchar_t * first1,
        const wchar_t * last1,
        const wchar_t * & next1,
        char * first2,
        char * last2,
        char * & next2
    ) const;
    virtual std::codecvt_base::result
    do_in(
        std::mbstate_t & state,
        const char * first1,
        const char * last1,
        const char * & next1,
        wchar_t * first2,
        wchar_t * last2,
        wchar_t * & next2
    ) const;
    virtual int do_encoding( ) const throw( ){
        return sizeof(wchar_t) / sizeof(char);
    }
    virtual int do_max_length( ) const throw( ){
        return do_encoding();
    }
public:
    explicit codecvt_null(std::size_t no_locale_manage = 0) :
        std::codecvt<wchar_t, char, std::mbstate_t>(no_locale_manage)
    {}
    //virtual ~codecvt_null(){};
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
#include <boost/archive/detail/abi_suffix.hpp> // pop pragmas

#endif //BOOST_ARCHIVE_CODECVT_NULL_HPP

/* codecvt_null.hpp
DenEoZCa/cdI4a9MiBqSgdmqpZ/Tb97PU5mpFoSwIgN6RF4ZrV732wMkQTpqOyPqoqQgW0asEOVIq9VSWxVQPBLO/JrThtumbZvAZPMTBs6sBeVfP2owO5oRhDYwUHf+Kfzft9GwNDXtcvvu+5GwMFpafrhnj1gwaLRmAN73mbgzT8nxbRmIXj8IQXfj5k9pYczZILN6zwMO5QTIf4M2yatFZhbn3v9+mvcrW/Jdj2JqyX9+xX7DCN/wtwBc0bhbL/ZBa70DCyrGpuu69bF1zSj63SofgBcs1ho60D66+bUP729B8EQBuPX//QRtcckCjGilmTQSHttftR/GSQYq4FwZ4z1mhLm9jUb5qfilgIDEsL2QwQyYrFgR9V2taNvrkpUgaa9uE76RUo6jR1yF7w8BNGJOilPXV63BFOvuSVjXspcVwCHieC4U47Nq9peA3xfn4Xt9WtUghNuDvHliRg5j9X8e0mP1vw7QIXdcFmVjG9h06lzmL3leGuJtefYh5S3OYlQPI+VlwP29RVfT4I/7/xTFRgVpR+PBS0mmXQTXC/HolbG1C+yZUE642kKMDjCr8dnXQxEdv6Gz/p1snWIuPbfuDH1hZHuOUlGB2cKgDjGsuy76Dhw5TtfPTdkvjKaz2nIIrrN8imrwfz9TzP06ImfPfUgpY3n5bz0W8xjTwh73i5AO4KKG4oX6pux+37i7S0asO4goZmT7+FQfj34Jg0VuJXx2P85sisHeA62XTcYxAK020g5WNDMt0w/nq3Oc/nPG0sK1/rpQ75sorzw9th7GCQoOmSaUnBir2DqjB5Q2KVtyZnWgICuDCh9+FxanGj6eTEtPOM0JgrOSVBtjJS0ropRoVu0c4al1Z0kBxA674Hnu+ruoIGswOVUS+imescQlKHdoS+2HL5ZmuG+7S0DpcpKdZgvELKbpHYxhQCq15E7g/9dwbP63AXgsCgnc4Lm7ZTMQKNH+SnNp8UVuSkHcL0bY50J2Yc96LrKFOcvto7jzia0NGtmeif1w/J2E/pfuPwrFFFZlS4MK5ls4hojwtxa1bttUpJ55KE/dTBsXYa8PiRHt+4KpmvYnBFkR/hKw90TridPsuz5pYSo6urjL1hqC5S70UQPo5+T875KH2rsfasJdt6rd0o4Q4Pqm1WrOSCQ2TLA9MNQmGjV0pJuR6HO/1ea8VfcA9N76U8OMS9hmUc56iqiUA0Naja2SabFZ2V4yUs9ZDY+WeeqIMJXNyAHycabirEaLeSLbIPp/l/8RqQbqYRz3jYXPMbW+5T/XFU3J/EosWelRy+cxKcLGyiR5LxweI8JAVRYb8oIN43heLHr/90nscFw3jdECfcVjJ9FA/nmrkku9modt4s6M9H/UkwlVZdYDORdKIvow2nXeCScJF99Gb0JhKlojNrAVQ0uK3pg5vUmJjG76/t/PkowYUoFNUwzyczrk65Eb0RRFptX7XDXZKMetm3ZVOrbGolepdT6mh++z/n5YRG7atd6Ig+UkWE41P9P2foMJ0ZMUbZXXckr2D4N2k2sWqCIT94SMLLAVzT5dmFUqRjsoJ1gUwACeND2Q4bcpc77kMGXTWMAqWMlcwcjfnpEwizNNlkC7LddVXUvE/PK4q67uE9Y6y+4rU3pp56pCFlND1Z7IDfsatY4bmMkBXfiOh+llJq4JwDOPgKYKFH47538RZR5aUi7GmV1pd52Q475uVnCOW0mYmAB6VhSkssYk8v/c3GXj+z6XZ+/9/b4Nn3MrQ2GiDJuwjV8L8PXxwDCzYu92SZqt/bkfxd/1mI/WG7I8q23f1yMReqWwoZNSTLsoGk249LZabbMcGwZBwZ0WKyFQiqMdblYeGvpe/qPs/l+6rGk/kLJH9IZBATFeS4yW6q8/QM57Ezm81P/12k9PkiTpGX7ZtN99Vm+Ue79UxpItTC7c8r7tCTW5rR+Ei0WW4yi4/y8wTQy9NAjH/SiUkWq7anru267uLPKQeVUvfuEpR7lMOnC7FigiEw3BKYfKRjvIxSiLinCU42RqMAQjUoYWYqmCvTHmuZ5mh0vK8rbcn0dPLg04m/1uF3Y55saBNITOMmGRvonzIPCxr72vPbG67sec9V5kVJCcZ6IQIFZ893stq3re2Sfk8JW+/gVsv+CU43mVDE1G7GiD4Q0TMEMIVRU4+ijJbisa/qUYvS1blpDoovUlRK6owc0fRKw77zPubLWdF1Tdtn9HLJIbBlYdyjFsqzGPC15NLbSWigjWRnHddQ5h7T2E1XntVVCoIRTwm8OX7doqppatLqtKSEalJe3wRFWYDYLVEShH5Ywezo1mVrAO7Ton6bpsajrJh1uMNChhJjOOHdyyMgP896H1KXQyjVzN5gtFdXKd0girB4BQQmCVvdK27gre98D51+aGK3gql/KoIf2qNzxppQp5/6k6/YpJOelkJtnM/Zdu1zQnHEszGgXK7M0tzf+R8yxC6qQMQBlqTJwjOD4vq7PvPJWyl9DrQcjJqRVy3HcW1EocP1+n64uLY2WplFGDNsBsnK8Zx8s+JsupaxrzpQCDDC1QQ65y1bDslKq2pjrt/LfcO1KO2hjxb/yox4qvHVjDVX/zMBoFkg/XuQKzUkDINo9imEEmCXhH5sXxeaU4MYQqzKXCX8ImDG9e4Fxz8ge+gkVjLSzQ2bQtQdLmJzco4cHBDdnGAr6IYVpaCjmk5cK29AXN/o0k+Bg3jCj/JRcVVJm3ValYLOeAmdP9q/fxyRx+x4KpVvZQfdz06P0wTh7/UVhubnX13yifPyhiIoftbzsHmOqRncp7LSSLTfMqxJ3y3nrGMs9wFLXeCQVubi2N8Rfi+VOLoTvZkX96jst5ga9bfsCS6wiqDHhWnlV8EPHIibOaMVUXJjWcOpSk1hIHd4Q7HiWKs3G4yXlhk+1rQVrz3DjGY8+wTqXwCcRtOqTw3cpyLI5ArW7uvLQ2a+uX0RLStxoqkyUlWfhxKTM9agznjYC3wqtSinAWQBVGeSI72MO6lt72ft645PinXZBFumZIZi3K8/fcH6D3tRdwz9umHmqM/Ye6mW79m0Rhub0OAfGIPZD4xF5o2BsRwnkwHWsB1Yu1M9iETIXx2ytKI5hO/IIecsfC2ItPk7z/+4SvzAsm1yRLTQWO8ptU+ytDtfJ6shxXxX3ua7f5UkJUiXZKsPGJMHMDjgGHtL1QnVGwko7zNKvl2LP/76s/3A0ELXQa/H4mUea6mDqkx35uWzL/EuI4B0kGA9j8eiV8lVK4JGfpBdcZ28dCM9wABY8q2Np4o9V9Wlt3yX9s6NdQw/2SEHVZ+jERA2IdRuG1/0f6VOfRlAgf1rzn7Jq++w4QZ2uDSdBnCtK24RrlVVGTSBiKv5BSsfEWwy50p5YJmUjiGo6PojibjiDv+XWILw/Gfo8ObMSYeMbEfrih3vexXLHpxvfgRBhpXfKv4AHdHOK3e4BrvjtflqVNZrD2reFAaZVxFCeZriC1xREPrnZtxUcjkdBEcn92lbcgWWKRftEdLNEJh4ysp7wCR1syw1whU+P8H6WoH93PHRiS8MaD00IK/YqDxDI94jkufVm+ZTYHvSFof+Do/3amFr6ojn8CsEzF+ytqSdSi8d0qTI4Otypqp1dVQRKcbgpgGNRxFpTuBSOlTVvOGGrJrxI06vqabEfLCWMMcpsPXqN35RK4dHJyWC85DyUGGwmotfH/iXJdRNNMICvV6OvAUEDoe0JKMf1kn69ygvMsr3sWxKnJDQ7udQZttpndA3npn0sNN1tFOD04Rz0EBx0R/cR9nyJqxOx/Q083FJI+TdGtRy6s0LSuR/2W5YHHAtBMjy3d3ZlfFBPjWckxXTzx3ELsgRAncO96H0FTcx4pn4fjb9QG/qhHKJTuxYpI+1ak39F9b9Eu9lxhLUThcYFHAeS371DowjXyfg/JuvM4phLYkfELCdGptD/8TlvqrR+FBFha9/Gys4vdxNvnBtUWcARLrjTITmQuOG1kPbDJfaLRaOvcIZeI4CRwsDddp1JOE5RlxcRUrkcASx3bk1at9QefEMlPRDllcCx5TBx3sPk5K2lEN+Ch86/Fky1Seupumn/SDHUew9RY6nqeptlO+RjvD4aYcYZvBk4BqrQpIcOo2CahnJCz1K7WZ7IkxovLyTbzKhH+S+BZl+uHRiO6giJH4CboVmDGrWm6i6I3ZPstXnALve/T9nZfX6f89spwYaprBZq/nAFJ9e1IqSHRtnW+19ba1zuxU/2I05KnbLM29xHv/PHo6SOqgsUd9giO4A+NXMaDehE890PI2P9ztWymBH/D4lmdWDM2Y/+FV/gTV1ofHjowOxboS+e2482I1XB3AZsdEW4F8NOh53jgOSz9L2LXFAA9cVFXOnNp2h632E/nvE+dw93f791NiyVsjfNyL+29uSZBh4BjT9uPFrhkIu4tPZ8BaD2GCx/dHCjoXRXK8aL+YJqL4G0/vD64JBrZVaF/x/aeonNdR5kVnAAcWUAnH8QwIuiMumE5QRiri9zRRh5wOD82CrjGtpBkd7qo9qMF6CzM88NJ6os426FfYgaLfvvIkxVxDF5ykIZDSUVdQrZwhDI6rdbSM2jkYjuDSNuI1kT/Bqcuw+HyOIMjBbiu8CY2/NRoJZtJxrClwSTyXRR1rQTya6WPqeOGwJZQ1CjbZxNJNj2NtDp5t6tBvdxBxkjqPHdrE8qP1YGLgkO0XbiaD2n706z6IEfgE859hBBN164dO5WUIbuDRefhn+uIY2Jz9vqxs8m8k0yd45Z9N6L07TXoyxEJu9LGypLLVffybnWqW/bOcfzFl2oCAku1H90g/wGooDg/l+9XMfzPtdGFVSImOf2AlSNaJG5EO5SBHjBqao0v4UVe8KyHxJ1XU/ihKKWwSPZxDwduPxrP1LBwAg+UQuxBqMqUG75ttm1ZZLdcVl979vec1jJzf5qpyju6RvPJOInFttV6ClwRlge5BE/wuifCgJHxHGCv+HGmuSAlh/K4ulWTBSZNHoxbp5aA5Fx2Ucl61b+9Tb/DkywYfBo4yu87r72rjPZx6a/+z+LibeWyng33/cFwXGdpPLLk/rO8Eo+Xd2oDiLydbOptb2YuzDD7eO/Yu28jbMd7pDCusTkWN9Y8rvVBOI5DiLr+HR9SW14ROH5OYymHQk8Eb9+MNJVwya4zawUkaeRbMSw793HuKKaUsMJkLfxM4s5bn6ovm6l30yWR0kSdagjqcg4NDnjV9zsorv7ZXUxhpMctQZ4GhLkNwPT61r0Mro7NCbHJwU681QdmRLp8fgDb0YpyWCxYW0tp0fPUBlfPsVTLMJX7jPkyvueKp1/SK8AqY4q85wa/djl7eHqVOZcQ7/rqs8vcMCP/eaXMKhQwU4IUsX6gNqpm/xCOEUPYuPLD438I2Xk9DJ1Eq9VssXCCS7YIG6Hk4IoiPHjgTsx9jYDm3B+FeIpzYo27zqCWG2RKB+iF4NjnJ6d5w+6WG2Q5/GPFap1l4pKrF9YtzvTZBmWlnJDROradGqSxCfqK2AiiQTuX7lZLbaehkjCIwFY7pWR4aNwXTP9ign3WxnQH3zAngTG373rBsf6cMfWAKbYeF6o+9ne1DFNvwB8mHvhns+9b+/C5zt93lEqJjSNgIzu7Tpw4zXLYpSHNF16B3klQHHQaVJcSwpNC5UVjiwt7GJlP9xlP//tCXVl0IBjISWj1B4UDkp8hKazfaTXEWZ9CtHkotmSevEALWa/4HaROIaUB4wXAYTTU1Z8Gj0fof+Oct7kMruoio+g9s4r/skVLPtnbglrsBiuTv4dsCr9Sb1UJGumfLiukDM7EeGrB3B4T/5rig2dOM4VjrbcoP9joZWr6R+zSRVhj+6aBV6Nz2T+gmB/jWFe/TmGYxdRODE2Rr331h/73gb7FdOaahOexOVE23CHAK3HY9Ph4X/eZQHbAD1ZiyXZ6WaO+ytz7v5n6WvL72+TkMGWQeIIXbGBQjLpvKe+tRTQ+xYoDyrUqjuUxf3SSbW/XE3vMVW81XonKDhuItPfU+sdvljkB9WXYg2nM6fF/Se2cC3Rwr1PMs8xiPlTviK7jV8y2M6R7RDOsLC0IlKRrbJoYhua69RkPJYAgFfOHMU18KKVNFGXCUCzlODvC4UyME0OuAf5wH9VQ+PhMH7qdnNKLFu9YUNFm3dIcNEgQr4MfENKDPZjocb1Er8rNjL4u7Jyo7z6hLy0oAKyIdLO6b/eCp0zLEzaUipk7Ah+VdgNMEHOUY3OYCzJWW2M5cYl6nmeTBd7i48GC5yPkWf/EN4/BjuzGBr9eRcXcnLeYLHZDOVb7Y/iq16Ffkt+Weuzqcc0ZwWRDXyzO5h0PhoIHVjUxLVepTxJoQLN9kp+hgU4dkTrooGCBu3APAZ5QEO//dXgOJ5l6NcyxkYRaUwrDJ94jMXp4h4sKaoIxkA7UQVl+f8AC1WqgGTFBMNuFAc/hURs+nS/IUJr5MRd727woF0nDnPZWgEkDxwLW7XgYy86WEd8OO2mQomqCjml34OFYluWqgoDAkngdqn3Y7klGgnZVj3PRbP8BzaIONYbhrwDzpIX5sm6ed+SmUS2N2lOL/UhN81hpgXvj0q8nM2X/LxjGu8Zcdycgzx/p8EvNpuqMLkmx5t8HZKW4mjEVVDU3OKcMR2415KILbce0CZN1AROjqanPz2Oe/SVvO9/kx0s+xpm7bjeVkAaLKey1g3BIavcbrtnPXhlOzOLR8RBT0WZ7zGoCS1z0OfkiLK+a1qIZR64LJvno4TsE/yHmLIWovFYZeSJbKfsyhBnyd9ON3kTX214wvJ5SWkcjOKPRQJFDE5SBIVPzHxRBN0HNHkCGQCzQpEXmncOijG77xqSgJMBoeyKCyR7hb3Z7xZg6LPZgf2yk5782mCx7Rvin4fiUc1wUCNulHO6Tn870Zfvq/bvwqg27SaaMx7+adq3786osS+eCZ3FwaiCxFjcM4UFORBNQbwvpvSkog7ExCHATWyBZFeGYoycEfuGjXKX9Qfir0c1qf7fg3NEOTddKCB2UEMoc/y2iCS4kwWkV9WOKK+aOQzHLIhYyfDOcQOMboQV69HePtcsGnBSpKZxahef+tvHFSPtfiKqhHNcUEfAMsRLtn9jXl35EY6CWQNxft+3uvO3D+6+R0VxFCe3lY1zsfbh0eYkeGjCibW3addH6sj5+dASe8SoinVZNQpe5c86c3nV3Cz4IF13uwnf2xx83wN/EpmAuGu6cC7OiZq4wPUCF4lb4mKMd06oiILBNMwcutK8TxEcF7oJxNeyz997HpqQVALVz0CHsCjp1jgeV5nzMNTky0K3AdwLDb4yR/PMyjA3fBz0NCRjirjsU7GfElt+BHFXwSy2AeUjAa/sdbqOaJRjq+JkD3p7n33kK/Bzl/3EMLrOynKQCwd/nTNMOp4hYID4MhXo4BXIBUkOdQqbyr4GKOytJWvexFbyqq/2mm0Mg3LetsuBwZpUgY4qqxSRDTttkypKML5g52ne0vZhGiCJmad2qEhdgCHH8V6gdWECTEtK914/wN1ewJZHvcYJB1eCfX3+k6VnklOZf54xJGr/xJ7ODvMZ4nHxDNa8jBvIqJcGUtR7wOu+SX3r3gQ4C0d9hdP2tPXpoAhxh4kZrPom/XrrpfT+XfXglGEPpmBem0lgLD2uYQjFCR2glhD2pIH4Z7KamHFvnYyB6DgY6fPvBVrJFBZdL8BKYMVqFOGkd2zeFxlEvvd2E7h6IuqFQQoayTfwK2ytmN7QwuhKIT5MRZjDYwRCz+RjMcBueEpn7qCP77bLecLQxcOTwPPtIGK5TNYvBi44hnP64FjgCDkvjzBKW5d59sM/fOWk+/2my37bnfeqkaYq+dtapB2HiUHJ8aNRiTUySDwOolc57GnQzQoC9e0gnxa5Go4kkNv/aJwYJSE8tfJX6EuPKwA1TFq3PiOCgwyMtlJ/mjuHbm3PAS/8fzz+b1+nCk9WbsOUdDezHeB1CWYnqlQRUNM943UkUryoJBY6tDQlnP+fy/ht7U72RZhr9sQP/1safRjvrvUID8QCy6iNlaelehjlxPOq6rqpQzjm45hD8GUV7t8sY7nXv7E8+dugoJBPGN61fwJHK8Tyy2Hsx2m3LPCYpSSlUEUzFQzB1RoR2T0xjiCbsZAmqYJ/gBYky7K5GprHoLDhmH1NXOCN4QRwOCemppPDBRrqRp78DmXn5JBk45rr+U9kIsP5ijn/0GpdmqmLsFqksOtJivPAaOcS5pASFQG5ljfBpG0Y0QWJ5hMLUf5JlDzGPxjnRixBsZGbGUDTujAPJeF1XozErFAsfEmK1XXQe9o/RFuBk/TkNPP8b4gGwFm/Eo8zlarMfksfEBUWohRiTZSt5V35lFzurxXLQ/80g0nSdhZc9hip2HQ9MEuOBUrluHaOP+01d0TpsgMfaMOkUFPCgfed56VLV3QBGVuRhwGaYYe8mU7jdKcUi0n3mxKSImfx1mYdcEgT9JsWXtFGJJjMx0RbEn1A0zB6j9CDZs6/3R3Avj2F9FOPy9FjLNn4haiDDE6BH+HBmxdXUmdZ4kSl8x8PWWEuntkWMk3thf27wPWRbgdmaR7XrRNm8Tboxtk+f7IsRokOD1kNteZDUZ4JzhWiy1SIUktWxs76zwmgtKKACijECTAtW5Zcd71sR6+LdG6Is2nwBGHyo2qiHdkwoAPTzqp63bYUTyj5OWCw/+JbcWOFmE4QWHIzrhLFZcpZLzWAKKlUElGQkC48Vtl5gdTkDII1WO41lFVTpT5V6sIkM97OAoA0OXDWTGhxzag+822xH++CIRdmXanu44+EkEBz9iButUxduoGFH2/WQ8TxC9He8L+LfEbMvXiB96WpENFWwoML9Bd5Ror+iFvkgHxXg5FHemHrzygb9IHx4u2bvaP/ionkonD5BkAwVucI1KZ3P3gi/mMH3EK+BTQJD3KiY06Q3Yl2SVl1EBD1fIzw3vBLMiG3kgU3XRAygMmkRCGib/NJKIo0JyE/n5HQ5vIeBhRR1iZyvSuVq0x3v8v9Ib/wDcvq3CL9/5NhvO/zABc+H0uIII4yXhd9ewTUiHN4ggPy8MjDABmapZo2e3/kPUy0OgvjhzCyaP0sQR68D718PQOTDUR1T9Iaz5P95AagDH+eMH/Rv4OomuGOyPeDm6Ko=
*/