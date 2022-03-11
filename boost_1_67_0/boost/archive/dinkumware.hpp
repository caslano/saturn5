#ifndef BOOST_ARCHIVE_DINKUMWARE_HPP
#define BOOST_ARCHIVE_DINKUMWARE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// dinkumware.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// this file adds a couple of things that are missing from the dinkumware
// implementation of the standard library.

#include <iterator>
#include <string>

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

namespace std {

// define i/o operators for 64 bit integers
template<class CharType>
basic_ostream<CharType> &
operator<<(basic_ostream<CharType> & os, boost::uint64_t t){
    // octal rendering of 64 bit number would be 22 octets + eos
    CharType d[23];
    unsigned int radix;

    if(os.flags() & (int)std::ios_base::hex)
        radix = 16;
    else
    if(os.flags() & (int)std::ios_base::oct)
        radix = 8;
    else
    //if(s.flags() & (int)std::ios_base::dec)
        radix =  10;
    unsigned int i = 0;
    do{
        unsigned int j = t % radix;
        d[i++] = j + ((j < 10) ? '0' : ('a' - 10));
        t /= radix;
    }
    while(t > 0);
    d[i--] = '\0';

    // reverse digits
    unsigned int j = 0;
    while(j < i){
        CharType k = d[i];
        d[i] = d[j];
        d[j] = k;
        --i;++j;
    }
    os << d;
    return os;

}

template<class CharType>
basic_ostream<CharType> &
operator<<(basic_ostream<CharType> &os, boost::int64_t t){
    if(0 <= t){
        os << static_cast<boost::uint64_t>(t);
    }
    else{
        os.put('-');
        os << -t;
    }
    return os;
}

template<class CharType>
basic_istream<CharType> &
operator>>(basic_istream<CharType> &is, boost::int64_t & t){
    CharType d;
    do{
        d = is.get();
    }
    while(::isspace(d));
    bool negative = (d == '-');
    if(negative)
        d = is.get();
    unsigned int radix;
    if(is.flags() & (int)std::ios_base::hex)
        radix = 16;
    else
    if(is.flags() & (int)std::ios_base::oct)
        radix = 8;
    else
    //if(s.flags() & (int)std::ios_base::dec)
        radix =  10;
    t = 0;
    do{
        if('0' <= d && d <= '9')
            t = t * radix + (d - '0');
        else
        if('a' <= d && d <= 'f')
            t = t * radix + (d - 'a' + 10);
        else
            break;
        d = is.get();
    }
    while(!is.fail());
    // restore the delimiter
    is.putback(d);
    is.clear();
    if(negative)
        t = -t;
    return is;
}

template<class CharType>
basic_istream<CharType> &
operator>>(basic_istream<CharType> &is, boost::uint64_t & t){
    boost::int64_t it;
    is >> it;
    t = it;
    return is;
}

//#endif

template<>
class back_insert_iterator<basic_string<char> > : public
    iterator<output_iterator_tag, char>
{
public:
    typedef basic_string<char> container_type;
    typedef container_type::reference reference;

    explicit back_insert_iterator(container_type & s)
        : container(& s)
    {}    // construct with container

    back_insert_iterator<container_type> & operator=(
        container_type::const_reference Val_
    ){    // push value into container
        //container->push_back(Val_);
        *container += Val_;
        return (*this);
    }

    back_insert_iterator<container_type> & operator*(){
        return (*this);
    }

    back_insert_iterator<container_type> & operator++(){
        // pretend to preincrement
        return (*this);
    }

    back_insert_iterator<container_type> operator++(int){
        // pretend to postincrement
        return (*this);
    }

protected:
    container_type *container;    // pointer to container
};

template<char>
inline back_insert_iterator<basic_string<char> > back_inserter(
    basic_string<char> & s
){
    return (std::back_insert_iterator<basic_string<char> >(s));
}

template<>
class back_insert_iterator<basic_string<wchar_t> > : public
    iterator<output_iterator_tag, wchar_t>
{
public:
    typedef basic_string<wchar_t> container_type;
    typedef container_type::reference reference;

    explicit back_insert_iterator(container_type & s)
        : container(& s)
    {}    // construct with container

    back_insert_iterator<container_type> & operator=(
        container_type::const_reference Val_
    ){    // push value into container
        //container->push_back(Val_);
        *container += Val_;
        return (*this);
    }

    back_insert_iterator<container_type> & operator*(){
        return (*this);
    }

    back_insert_iterator<container_type> & operator++(){
        // pretend to preincrement
        return (*this);
    }

    back_insert_iterator<container_type> operator++(int){
        // pretend to postincrement
        return (*this);
    }

protected:
    container_type *container;    // pointer to container
};

template<wchar_t>
inline back_insert_iterator<basic_string<wchar_t> > back_inserter(
    basic_string<wchar_t> & s
){
    return (std::back_insert_iterator<basic_string<wchar_t> >(s));
}

} // namespace std

#endif //BOOST_ARCHIVE_DINKUMWARE_HPP

/* dinkumware.hpp
GTp7nCw0HTj8xr+IyQWxY3VlHRODiiVghUvFSdpjacItCIRhoaEdEtLcZeldDc5O0QGQbYEnTNLsVxwPAeGS+bCOrrH3CTs3XHPnl2lNDWXBZTRZ7deT+aY4FJnygzT3dK5Id/UWcEkoIo/xS8EaBEZAnI+Z+Y0n+PALlP65NkrftaP/O246EWMgWYF0TwycZyveN+6vp9pFcM0i/OcD1z6twUNprV4eM2EIZlnq/89asZiAO1kC+UoN3sgQGC3zsrar9pmVBO+YIVH0nJyLhslo1/cVtwRDVSZE7SKIFU+tTqOlipsRX9rXeWNKHXCNB/0Dy0mP3cr5q6P/CG/xvoIzJFydk0OnjqBWjwdy6DrmgDyyNmNzFoPYyIgMWyViGjLsgrzPBvL2sDj4rmVWXCc1F9FElAA+6YueXdktZ3zW3G+Bqw+aE87RVQDUdk45wY5pWEq/wDXvkkEvUOv7SEjdNX4Bn1vwAXopfGma6AOXZHY7dTL8hRgSNRUmliKMRxZnphCuznM5eG4UEzrJsGDPLuNWlBznBdJDeMFRdosew9I51Q1Lton/DoJ/J98aqK4jWj6JXZJXuSzrYpSr1ngi1Mc64ir5a0QMtj6E2qowJOZkJOyWuO0QQtlXRIY74jVUdA0HroZ5EUqKiw+FgfdbV0h16zGkWEtrO3DclN59RHoY2EnPwdHi8x+otY0L60NVCmCZJhKT/48eoZUH1SfbUiOuYXMSNGpgNsd30qklLrTOBB9iIMAhomGgghgNbRDgghhByqE/8X60WVcHAfpi1Pd6A0Sw734vTXklR7XWmjuNDg+Bo6bugEOPBwPP1IfvW39/67XTt8YHMiocrvx4MGy81NZMmg8dOiihz3TMhWFEpMZdFQSuaGsnsP2DNy5Y4QWwinISu/xuArW6m57XHZKAOOwhvJDsYAq7HK4OPDMmV/dejm6n7sXTuXuBrkcW1+85AWEjB289FrVu10l66dMHWFryl/T/Mb3F3iGsrGgYW2j8UJcvaVfMwHgCV7SOoAcJnKE9pcRSbWHQwz4qmNc/+NpxllqO1NNtXWyALW6acIa1tFaa2ztCfRCqbB9YYGORo3e7zmCGGdF2yq2eW6MlZSU7sutG35gA/ZfJfRiLRq0HyyJfITRjEZaxM1MBAVo+zshTO2KWhUJct6Lxl0hHQSDU4J8w9Vx/BLOPSqwUjtFsT/7f91nk9x6oEMeTejp5Gfa55kT2zssDrDoXOmzCYLpFDr230ahwaghVFkTzzH5aTUkoIneuqNxXgvNlWkiBKvAGBwxJOYZJCwxmKEMcFOMNTm/UcHWzDEPEnqVRV2D4sGlB7NH1XXsLrcAUW/++yeuQXXzoxWXKb5FR56bF6/T0a7bWf39KztD2iqFfOOw/rEFIpXghMMvbDRWLBARYggsJSrE3Xjft+0SM5PwzE7Id0UQcHDgSH9Xjol1rL908Rww12H8/EmZccVC03jdbu7eJbYdENRuuqGULgoonLytNrOGHJgYUSsaOhGlQFVJshAaNSjAf3g2twkG4MdmbM0eF/+B8n0ZzslzCg69dmRFWWOxHsI1ojVhav/u2UujmT3gniLvNsxhFAUxARW0CAyz+igbkY07OcGKnN/DNRfdNZMiPHL6Lq+Yabhk4/cGk3fCyoBLJtjkDuaU38JIpUBEst0KpZAo8ENNlCc4nmLMa4NsLAEHy5PxWC5Do2nbUgcXzmiWVTmsOU1f1HEgcPXTXCGHcMq2zn3NlwBH5WO+m4da1wyzLccYsoOsIKqZ1gJS4/J2NzadghnACa/iDwI458qRkGOb9b2eYo7sar5SVrTk1eNLAj3P+PCBZd1Vick53BqjNVxFqFLNSdju4+FyslqAIdBwzUHREmGaU21dxIxKiyKf3ba3va7JPRh/OH5coVrWZ4K0W3NOXY36CWSWG6gZWD8cZoc1XLmcz884si6WnvrCZUiJuKBPW+Sj4LFyNGlR8M1omNWCUkEjqL5/bLO9V5YS2ihoMMT3aPzf36DoKX0UNmrY8u4m47shmEXd+y7OQLik/XPCYkR82MMJAYiOxLmLgLnBT47lmca0ezjMGg9QCQVvJ6ELHlDxvMEXHSocn6hmA2QfFqOE3VROy3qKRRsoOi9uBr+LOPdQhmqXme4h4FVs6u2//wlGnrCDKfQBS/dBkll0UcYOsCzfN7qsHSZUxOR7R0lz/BSpykwRzbOhubJryaZgb18JIk7rnh9433e6xK+DQZc74kmfE9FdEON3+TJzmip33RfhXBPM/3KZfZRl2KNGlfsec/2KlnW2lhJhIVM+HkBTB6Ks2DRl6+nbp8iG4vTEywrihOuxMghMdLCRgi2vrg/gPpqspuin88U6650IOmiiQ+IV6DqYnMaN3Wf5g3qpjll0voalyXAyJfj0RuMI0c+Zt9NaDa8oBi7aSQPo3ewre9MZk0I+ZYCxGKBj7tKD1HVaeOQ0CIQpcDDBiwZEjnXgcjn3D3aIXw82FxEIt1D10DmB7DphZPaXvO2JNymp26gGI5bauAofqI5LvMMg9DWNEk1i/mp8JHupIlGDrV1AJFFPH65gXAhr6K7sPMcUzKUAAj+2jvHQ9FxG7YR8JpdV6IaM7Cd1XvgnkckKxdegSmHS7dp+Td4j2nQE0nPj+X/eprpSDqmh8udeol8sVdnOHLIeSwZeQcilFFslzlk5eib4PlDw5gGnUIz2i1DPDEzTGJsQTBv9fKKAcGJBtCFa2n1OCZoTwGutykPN13rrB4E4Pb8nTh/XFggLf1P79/nu27TuqNF40rbFN647Ev12x1L8B3L0wRJ/T3ecodtlBFAd0TJXoHhlhDsQphMRbyIYJRo+xg/91BvW0cdsYhRdmtYKGnW4i0JSGd2UwMmfiiix3B4R0XwaxuVOdcXt774KMtvt6JaPU7vEli34BfXKoRn3T2KUg28mWtO8cuq7bPZlDHcErAZFSAsso08A8LrSLBCJiHwJ9sNrHdfL8E6wACGzddVUXWZlIlm7xuYFfaHU+IZ1oHVQUIdphuHteVy3sHnjg1CUMUdyFG99lL87HVUMGf3t7DvdR1L24TttnhlvxXcadRr6OlMsDhcU+sh+Wv4QApkGjWkvKIztorA/lKMuC92qqliQyGsZ/ThJPe2EueiiMZoI91zDlen/5YDga2WoR5GpEgF0YE1/OxW8woiqC3ZPrq7W4jVse/f7kptDpgUX0p9BnOyX7kKXXzjGGVL/NNNPswfDyK5DmaX0hmOURDa7BruzPtq8HhG3UCoRMAKG9ASN85KS3jyf5xTk+M2CQ2h4uiy8fmyLs2G41nst4hvd1a8hgKyVw/J6DRzTtiyP2EQttn1po/ylM1LITcvI+o1fP0SV51/SVG961AIbGv/DQ6ZELCc8Up+1obbK+LYnvVtAOvAIVFFTMLgM9CJ/oK0qX2V+xsTdUkQyq8T/JX2LueGfMOK8rKiAzq/G7IE0vOxXNUz6hj4Y+af4GmUNXRTMrEnZ6vUFrO7Mr26v3uEQZzCIHvmVVtSJ8XbR20QpWiCOQ8+VbnvmLxnQElQScTq+v1wUOBCmST8C21cucCHeJLrLH0/BytCW0Bg17ROjPYjeHsRK7yUE8FHs9PBTGattzMDHJzgfoGjj32T45Z/NF1R0Ba+5ShgfebkAvALdcIe0xTaWGSH4yxSKaTk+oVhWTke6aCvlX8d8+5Us0FjK8r5brxvNNBx844vXKk6Yo5iwTzF0KQv8W4KkDdXYwyiFT9d3QTeVS7LxxNvPIIYt38/Bwx/UT0USHd3qu7nVWGiP3Fjn6EJdhOXEp036MXT5cEv7UoFvmeVYjjud5dBYLICvMDvGQl11atShnZCZyKPAU5L5uVs4OchAMbTYNOX4fPSjDCcmcHqBt22oc5liEqjaWqVvcxH9008Y/BA7f5ox5+9ynK1xncVHOvV+a5kY8j7YgnFL79df7oKN/El0fqYH8CJb9589i/4AXcrc7dlOhZxCbNraBAipIw8R92+0cTXGA+cCgWOf9txTCPIeBCkRWY5d7dLvaBBfF1vLBp6OP1jE+12/vKg0Fuu7RVVh5Sps8b3FVEpq3+JaM1tPIa6v1f7eA0vwLKcZghjORy/OFrLI6q4HoysUEq0gFq1J4JuhJMWKgNEpJtm3bbLYGDb+GRqzx51VBGZBqCWX83+dFGQANLPLT+yMFfMFGnSWRT6JuPJfIlk6fywO3Pq4PT9S0LkGbDwG7dmJsdOl3FoUymzXaRb38O0oI+vQynoJk3rB4lGMX5TjT7YARItwNK0DAl6hTH+xxPgH3TbuxluRgfKTLU3bYOEB/GW/o2Ypop5PjX5nch93iygDm4lDrrmm6LtTxMsufGpyxehO+ae6QOiXB2jKBTmwmUVIgTRG87SkgIsdvNYQJp9v9Phe390RD7Cru1tjt7QfAe4BrzOKqLHfuecwk0x8fAHKuAlXdWOPxJlPcVLD4swRXQFcNOKFAmHJMmwVcg9rjU/OWNegKGzORUISgASHMoFRauE7i2b2TMpoz7gTnUYKwUua7fLG9sMPp8+VK3mN+9teMNrn8dvNh5owTmG/7utdeHZGOWEiasfCRduMMTo7ki6w4ruuS06pzShAL4ncS6IWTmiZnQEPC1vRvXLaEsB7weTijX0pIapVPZuZbwflU4FpYjjJ/EsDzorguO83FVUaTq63tGHgMv6XziwnDG9EEFyvlZUJCOjsIVKSPIFFPVgbKiBTIUGLx5GSOKJkIWfLHjwpigjDWnkavO6NQi1f9wWaP39RWwKOO7KA6uCj7yfWMqVfONH2/ccsTZTDvBMMcbtsZg2g36Xk5pabZ9td8pzVKNMyscDLQfcfz9GKU54TxfI9Qoh4BGFE0rGRl9/fntYaFR3pCbNoDe7E/lh++zgB4H2PLVSaX7nV1QJE89txpY+v2jghCtnXIvbCBojf74YHp4sg1U9XysthxXdXj398zl36LRHk5VY1cSWzY/TRzuLKD3sM47moCyZccPxV4ITPVEy+q4nB/TXQ9a5OhdaQ87Z8BSKGa4avQmNfaTkxBTJi6h2Xm0a4gU4SNIsbtPVx7aDvsLc/1uEv0qc2KbKd/bXK5XM+VwXVyWGeEOZ7QQwtu3JYkh8RkI6YW72Batan2NXwn1ilm6495v18rUGim/+3PdCqZHSyNIpjwS+peqXSi00xMEAEJRMLwAFHqMkLcOuv403E9h6A81Ub03rvQSDSATfTZxKABWhgP3+jxV9zk49MFuL0NzlsEYUz7OIMn7uUc4qNKiXtnJYvrpX64eHFDN6bT0ZjL0RcpDxX4tePrtnudRWkXjTy/lKBMN1PSm8C38OzE++NpGyWEJQEZOwWwP2u9iHtHZHhCiXQ625oEDj3I4UDsAe8h5qwFY1BUOiNpGu5i/YQY/elyKwb6Y8wwLljozb9FsH69iShPh02xDyNPxu4J3PuV8dsnVctRZllNzhBuuAgdg0RBk7oxkeN83PqP9OYnlGiTnyCeWQowwaK3ysqgU8h1yP85TaVeOCDc/4XuDokWg+N5GFzSgd1DEJg3tbMzqYHw0QBPT6C2gcsGH17dqqC5GiTF857+c0bKmTkcaelTh6AdCf1cn/VzuwQKxNBD98/pxLQf0vwvFY1+5Txw2qp2dlp6DQv2WmC6PR7ZJAai2aggmWCBKa5xrT8++NhCCZlBgVAduk445IQxdUn3r7P8g2NKMEasJ2r6/flsw+UGyuusd8Q0UyRLG3+P1nsqVPExkUPk9cRwHcRApyf32wPBl3B108ktG9Nnp31ax/E6K6D94azGlsikW32+IetbFMvCUQO7LK2TAt/OOSgoUM7iwevbRBoD3+CZuBRpP0bXHCHa7My9r7/50C8j9O4kQX1soYRARIzcSp+8GWGwDsd1y5hJz6YbF8ESC4FpepsE+kb0jnYI09y0bdOl3Gf0T92cmstyPdSc9VLTVjojw9Mwi4i+Lz41tAIY6MRQA+YpeyngDVlwTAewax+V0H64wph07VyS8bvjqoKrKGR1uca0yW0VsySIbwpZSmvseDgKWeO/EZl6IQZilQgG1RC+bV2x9CpkN9Tq/tmnBHEEiaEkPYY8HbPv+jxC1aBNg1Du2xkgn/GEieM4ihyK838oSjNgjNwtr+qMSHaG0Ulz51rKDd5Bla4h6K9mZB7dLxYuQf49KaWgkVc+Ia87L5TRIzl/CqQEgMX9gztkden9bx1z1dvtcJ1LGGcFanjEDOiGFv3XqPo7tMk0YOwQUbKFP7hqKLpP2jvFtkt3UDxFKCFDJmZ4RCJTwj/5rAe4LOkeEvuLEU0BQNEwVRCbNk2yg/4D0IIbypjoYAWvHB9nRdrDWZI1AVhwZ6XsIpaenIgfUwKNhzcrKseOOMcGd+qQEorrteS/7k7fz6tt89opfgoAHXkx1LZtN22i6I9s8rjZ85qDxMc/ltKb/7Ng0XaLvu3xP0QfC4fKWLs0ieHX8ncfkdJTqiQAKviGwEzS91dNfDu6yA7qQ9A1IQyErACBEC8aLyJTMG6neY//TkmAiGmYqM2lnrLlAPnh8P2epzmrE/IeMsF9Exw1hqobDUMdcbV9Bell4JiAUwn+m63+PiblYe3DlhhC506wNSvh09g5J2vS+TGKZ7yHeK0dVtlQKCGSiGwoRzY7WTN1DMa50FTKqL4HFoLU/rnoJ6MpmDArnkPA3cTfDYZERFW7Baw8fTkX3IgqJkR71c5GjlPynZvOOQ5ahKWBG8Hgk7oCS/rgu/yJIY9Dl5x7YuMnhS0CmgPzFFWTVfwPbPvueaiHnMYHadQhKQITmKbazsvarhULUevYRO7eCAIAh+w4Xyg1sAkrNOHtcD8EGzg8/9ddCi7/CIOn1VcGHl5aBD35iFiEhdG3kQe5e24djD85z1BXnID2KshZvWBgYqmEv6rudF0jS6J/LflxPs5bPOdJhtAxg14KaGbLcoRZy8sCnspbKr33+iQdBXWbgiBUgh7d0KVd+34YuEKCjmRhmNjrpP7PAxtYgRBeeBqiCoocn40KwsJABkRy2d7oM2FP5kWfa1xMvGYOeZhqR85OPZUtvSNaFJHFDwwUS6zo89UQ/kFVzCbDSmoV2v+8QptirIpwNSgCk3UnjvAEi42hVeqlBQqCOJANBEv3iXWK+QlOcnjFksjEiLUeIQjT7zTQpAq8ihspzMjcgsxB9GBVBtVKCeDGZiNM3B2xt1+Ps/aDhj4zeUTUfv9m6onOyylOz1HjhNrx/iq8MimjiuNRR4bf1vkcU0t7w5ug+KRp5psY0DbK4DTqioHvl0AZFcuSrELey7PyaH2G838ZhnojDJZTdHz+z+m4TRAkGVpfbedqbACB/OVzOxilhJ6eGoxa/b/iAlqw4BO5WCHM4oYa7dLF/4iqGRu6+kAST1xbm5FGWqBWm/8xc5bmmtdCmzrcGz6HQ7+g2+ds9ju77z07u/JNt5LAJEgigd078VZxjXVVR3g1BeBkSuBrB8/3tjdy03W7o4RENT5CKK5wgQHNCgUgS0gF1MPBWURNHfOzaagyf6tyGPlWLgy3Z4zeYPQxdu4LJ1YcxD/OuTV80yD72Pze3P7QjRfei5y9iOo5gjSo67ouf78te/9TFVGGqVJBQFIyUCb8XwlH6kxN9QoDJe+ZQSwLEBlFuL3npPYCQ3SUImXvHgD5nMJFfISh22jshIFJxJ0QGCxrfKjL59faVhMPMH1WyRLnrCUcDm/IDW6k3Tza3KYc45xbToAX6bAcSPqrs1O4KxVYfbByZpqKFo2X4qRTeihV8r+xVhIkmAGDIMzyqoXSf63S/77gCxc3oiHgPJLE+1FZRBVW4IydJByRG4kxxIQ3DlvPSVc9Iq+5/+P/0pTXgkJwEM3hqJ6pIafaiZF+GvkDu437rnASBt5R0GPzFSgc59C3D2tPcc3bj2qK7CkqyeLVDo+Z5h15rzYgBeYoBiUk6BJ3Jh106fe5uVub4tDUlAsFljTCgGT2yr37PrPCMIm6dGKMpJOeLJwRcOwxbhiOm1Y4zZC/7dm7Bd80pVMzVKIdjyZRNv0NFz9nGbCdYbfoHuztK2PNhzaf+xjF5rYpOiZ8TPOu3etkodkcU4jDxdlw4t73uU01fjfd+JubrioiLw4GBBlqUELwWplvj1TKnyHZI0ESc8c0ucijMtYDkTB6PMEGX/OHgRSurlyEPQqIdwTsaZ2aefBpI094FOQyI2PnhuudbYTFlMfVw6atHGdshv97kV/1BW+v3kbLr677YeLzWI/8mEOd3J0bXn+JAhc1JKyIAUoQuoQkryShqq7Xi9M/WQBjReSPrAacPMd+CMrphJLii+gZYRQMDNH/LbVLmbXML6slhfeggNZB1/MwFDLeiGEOH8kLP/UrY546nPyS6yMc1HC/0DSZAEhagxVcFx5LQP6CHLJNFZgyTpDVkf3Pxz0ZmQzjv+NDX0gZtqyEwBSgkQX+kO3SfqlN5Ld9nK6/kxWtIelkVJQnuew4iruqpum24nrEsZCyxQAe+NfLAxW5I8g1HzVJnKR4LbLBFNbYp6F665rFlOPhqYP/ZHduu+HG9Gti0NJ5sxyjPXHAvedSt2TC0LMpCUPPbd10ijdh99fjPlqf52JHvJi5UzznJDbRrQtY9jp4TH4Cr+a4Eby5kUXdfaWsQ+go0u6QwWcxe2fp7ee1b3fOT0paIbOeXqM+33Vj9T0w5PEE7a+gORjMWiwh/NTzvghGKvYqI3z8D5dl1EIyPDSuD0I5+gjDybrC1klqwaXWkPeFDFfZQHy228to7Mtg7JdDdvNUADg2qqhzPDjrqw7dsYGHq5XmTuGdFtRBDAUEbyjUR8/V6vIafaoZ3aLe6AnCEZQaJMNv1P8MzOx6HwvpZAWupgoYPw6J9CIsPLvAfGrdCAzpiIsqHdMWBjo9TngTdUw5B8Y7jc0hxhUg9ZtcQ0wr7OyuonYBJ/GGM+AAS+vN7lcDo5+P1b7e0LII9L2IiUDt9IM0xNrEWX8L4/oq5KYW1KFUIUEPD4HHMHmLptt667qeNPqvK9rWNaO/oMlw0sfOf9uFaNZ798DoLb5W/b/VpaRJM8LvStEGGWIenfoyvLEZqqDKHE/nXJoYKyS1ovkmqplm1FPD2u0WFMXfwh2/k8xBvhnt3+pRMQ+I8a/+nkwI/sg=
*/