//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct capture_traits
{
    static std::string type_name()
    {
        return ::boost::compute::type_name<T>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

/* capture_traits.hpp
7JNbo1NfYClrdPFAtXvUXhkj/jnh50cjuordoJZnCk1nhg65GuJMF0U+n98/ozLOFgnwb+baYPxoL3dlKnY2AS6rTVdxT3SiYlJ6RYCk2W1zx1DCb7rWoE1oO0/oVu7Db4rrgIdf1Y4XnUDht1yKWcP+xgXGl0W8cjdTKiawlgJLDtBQymN684uPvqILAnMq8c2RiBkbvHF+bR9jMACxnwrcOwuK3jEfFpmJWf8YrjaBrB4jZh2DdKFOahRdeVEGqLKuw1aEjFFcr6pDvo152IN4RpjHbBC1ilhLwH8OjCrT75OqWzEgGYShclsbP5xbATwtg496+5qRpFfEAkV6p1llT3mwycBoIFpnrsteRpqX13q9NY+d1fipfH42jnmojymaL++feemixxm+dAjd0EphKIULa/SPoK+FgYoUNOMbAG5HUnrRcKXQf9aoes5c8O+Nwrbu9tmCAzUbSMFeK/GoQ4b3OZBZlPzAENAhTGkycnCz4dimpsPGgZKT/WflWN7XwOupOZ3sOW3B3o55IJyyNXwbnzJvFixZqTSnDKa9+Uvtk/2Lhvn+MIwCmh8I8M1jIBMnk7487P3p5rEy5pT/k8WX49shYuHQ570DjjiKwls8K7J1pJbYCIAvwIAcApWxVyp1rxgTuuWJDpueyWOPxkOcpoLDUb3CdUT+Ww15mB1nmBVsZTVpmbaHhTY6LQq+PRRbmBtXh5vxo6CUAQZQXHm8F362q9bM4cBGwnKKSRPqTEeGNPpE8ipKh7/lJ20+DyuxbIQDH6ARP/pfrBEmJIBpDM6iUZzXI3jWhw2Zu7PU5M3iUVahLq2Nu1N3HVIjtNNXPJ/f4ThpBiUQyWbWJarsux35wcV90JuOI5AaSfCKDY95MFXoGwZ9owWhZ3g/vp81lYmHV+nseOJ7FuInD4n3d6IOB+JJApwPG7h3KrRgnmDM6YFJW/kXIBSfL9azGSTdzDqWQu6w3X7tKS3IKg7vNdCLf8zYf7cghhrlKvKVB8l8NGEwgajh25pCfi8ceYZsWH1O2aIKTNA1VF9uoG3vCn/9FvGDY4zOu9WwAzQK1HFZuyF3xoijr7nRgFJ941bauo3OunO4gLc5mg4aQJ+Ad+cXqd/8KPvZpPd8OlaN06tNkBPHgtmhO5BNTx/KiMqg6Qhzjnb60sxusTPU1TPjTqIrguQb7xmYZvWOM43YG8jKzXhtAYH9ZYSm4vtfATgMgXJGQDmUTwFsW3CTUaCZRyf0qMhs8kYHJfoY/YQCXtxucnbMYhDMXQErmqX82yPkCX8v57zpdcITXWtUeqtZ949FNuVB9Dqzj+9fdD3ZC/QzaPYKJjuAiZlJHFAJ0jMOjKTxmEzFHdeJqTd6bpKqhUcGf0nKvTCNZCuGL6YGk4dNAwLcCwkiG+p78lxb9M0MzeAK/wgC/ztRU/+HN74X1wQZk7DnZLrGNlCkyuWJxjM+coc0ATIHNWVYBQBbNiw+t7/5FhlJgREXIC+WAXY6CguzfvpBWHEC8M7qU/QGooTAQ+7znUEd5nPxKnH5Kgp3jIJ4PYeXsKmOLrt3pX6+dPfGjAsO5LLLOipgFeW8S+mK6UbOLnYyDYWbqmAPpkp5jQwqWLPF3270rNWTEPt8SFdyxFA8BMZq7x3KoC+c0kqMKev8+KLLxqy+9J0/fHZOKtqX3BMJWYZm7I2ClwmRDzu8TTKbrFvKafJ9FnRc7/2S8viAUDt+e0UuMkrarddNLoRp/RiNFDLyfRBd9drs1Sv2H/H0gWX0vbQ9fGRWhNcIz200vXdC41DygWoNs5PkbCaczkIXLQukMwTIV8EoFTkQiW2D5rNuFuFFcvkprMFJkjmlQ/GstTtHiGny0QIsj5s+osEh5gNKTxD1hI1k5DeRUbAatlPXP68XPanHh1uMiZle9nwaFkulXCtZQd7p1FyjIltATjuKM/c0nRENpzgQUFFHDNAmyFWt72ZdUpIcJayul+8evRujpyde0DJSrGMU7Cm6Vyh1laTGV25M/RV5BT/WfO3Jxefhs6ZcnNW3DzfsrlsnPvg9Ar+liOoNv3GqAH7APWjyLrLVHrKxZnixVFkTIUr908SMWNrs2La8OuNiSyeLUvEEkX7wURTqXcfupzTulZFr8Am6jkmdAJA54Y6UG9j3ItTxxbi4sUuUoFIdmYvpwfr/QLsXXWTG/quS/HdxzXmXWEZYAcjQAqF4iiWlo4tRU3dnoXzVItYsMtSNMvIx83Pp1sb9PjsNkgmONnCjSI98lDZK+0Z9w1q2dftUqG/krzq1GmrQgvFKlOCJruvd49JJaXWka3GtW930qLXQReMXfudQJmEbTjPYpeR3uozU3Wle5mQJjppJT7tQmoNadiUPeScpp9dVUhdm2aSGHdsNG/l67vFmTbxwqk2huWdE9J74Xud/VM7Jk3UdUJePhWZVNXccyEP8Cml9ux5g9Y/jxwvMGHboCp9r4Hs6xA0ZG6kBYE6jTjGcP7qNwGpKH549ieW7E6c1BQK4rDEJV+Rqc+7jsSsAWwNg2GYoirqruCUvWf/FmAhFr7y1fvDKn5/TntbKhLcyW9XOXdn8tez5JnXsxunrRm72pu5B16Xcv3cWPboou2f1bDMGEOnLG3TJu8vK+50M0FvO2yIuIMl6pqi8p68CUEilWlDyCh9bpAsmgOtyIduH1kcE6p4Ov96LIKTVVLg1iZ49V4mWUdExSt6bihbhZdAJQJZBRg3QwdCIKndmSpAAz6y+Bal7v0qV+LoC7zJ/qGqCBSXXGFq8FzQ15N00C7RXzOqIpvZBFpxvgnRKs4/1ct47bYCEVERX4qj36bk2HRUlaCRsjjTG168vDBziAiy7Fax+FBRnBWnIWpnp5ycnH8rTHW8rDoawRgKfSJEQVifc9Sncoi1BrgmhhJcqFITt+Ew4YwdB9CFhs5QQSjlogFACniMBD3pfp+pQp6j+DOtvrycEmzUI7c5XaqST8TOqSQXL23pG0Tq3gDjdkm5qKbPCNTpBybi+s47mwkgBCOAMjXOnPMiJMHdoFNVc96jJaSacWc1QxEJf774eDGYEF2uBfNI+5qjX3G7UlOIc8tbrzIgL+II7iRczQnB4u7OEzN/P/rMEEj3zggFnu9nxyzaIwdeH8imBubbw1jAXMHN2o0h1i8IKqeoOZ78a6qpXiZKilJhro5asnrfFWQMJ24pAvJppYhup/+fA5oOr3XaqKQOQmOzAT/OyownOBqPunrqE/UJzTeNFRWMp4kCg/hYB5/gBSEAIyhY68i9v36ekvwPytJdGAFOIZtviK7rZgQJKPB5ESHzOWZ7wSeLOX/5hJ1u6ORwZxaF3aj/0lajxNg+dWuetFDj5iUivNMca2CgolR+dLIS4uD/imyNcZ/x6/s3rIR0LlEHULtuPq/X90rNGSMdQy8QTqJ2bsDCQewUCTTMRoZYDa8wZTZET1TwZrqK8KwEBLLUn0oP4ieNWLKT8LlSXSGPwKlU66iNLwkvckGmyaWyxWZ7Pif/d5XFiOpZc9XquQkBFXq4CiycvYmF7L/6bPPHeJPxOhPB2V2cDWcn+s+/W9Te1fT/aVl5N4hdN/nfm1+dhm8Xqfce1yX3J6+l5Y6Z8ZvCyDkqxqmeVW1kxFoIxgQFwGBqXM2JDnoKjnfH7FawCVXJDmQD3MlHOplCbsdjXdUES97yZ/aOZ4SMGByz87Fl3a1dfzT2k3yDGKwKVJVdKgpaO/Z8nARiVIYOd9Glh1nScm+ETl8ay1F6R9vEMnN4KEKxnO4uxWi7SthYMj9+ppkHl41J+FTqkC//YwbEu+YgrgD3ZpMnC1aY0e5u36XUp0K/IUvT6ylqshzAsawzofMOg2fMiOSv0dSAgWlS4vhVuJ7D/NZ+2gI18WkYSxdFaY3S+Vq8C0tawwXuHdcYXe/TGb4m/aOekDWbG5s2/7ViE8HX21xJppz65Fli79dxa1Pvej0qfL+veGZ33JpCuoN20nTvA0SUf0d3QQO40q6Ro8760UmOYxZ/y3LDatvTZqpZfXfxtYzwIzudbzy+ItslHnVfxOdWjG0F9w8Ee71V5Oje+3nXp6JtYHv+XsOikEFfC4WbnZmLjiuRTCMZnDT3zLe/7FxNKJvQ1qDjClYMKlOMWsg4OflPkeAdUcbp4hhIL0DoGzlVzKliG8M3Mzi+5Qkyj2wsHGV1caXjEG3/M1qhwKbsasrul3PnSfylzNWVnDZ4PEU1MaSi8dZl0TgOGXykSdhP/RodRyg0fwfqKOemHd15X+WfgC43B40OImjPiplqwf0Oce6h6Ct8wEFBtlPcjD2MflyQoXtYW/Kmw/tPLnAS7p5JBftpRmyupe6KaiFDdoaOG3Fmno9O/RqipPO9GqLF7y6dRW2S6vU7qb0iiV1t1ZaRX26WeYyqvVctWSFSbGKDYWcIv0dhpLr/gxP2UPIxhO9x09mXPLl59SsM4S2w0GRPzKzY5dTNNM1nNm5WeuAmGp2LfZdUxXsCWRB1w3UZuKazdzzQ52xUpD0b7b+F24Bdwhq4ZJ9IfIEBYOufLVAFlB5vfzx5Qmn673sX9lS4ncWFhWwmIiEY6PBEJaIE0BwiIDjYoACIigAWJSEmq6Xfu9fVzbst5biv+JuPxaTqb2XzWVfeWnJ6vjc/onfs/QyZd0HlEqkuIeUUu2R5kGQTJSniZbaYeTPJBZqErZHvdurXivXDu6rVkClBFgJj3LL1vDnHWlreYg+ucN5pEBcWDKUTXkBApUauePm+E557h7v9qC48Gja2/9fUd8nyD9hHY+Xe8rXILKZ63S/ZClx4aLn2hkYwokGDvGFiqX+40PAl70F6q5D+i0Ucm+1LKmPNK2A8xiExbEy/8dIl8w0HyaEkvqSZueltfUnbEKKl1r9F4/RO26W2pr9ii1FATuatrLtM+n5kf262JD3sSv27jUAuy9FUD/3vw/7DDz61z/YScyIthEKHMhhSVjZxtgIGUvJQ7o6L+0X3zouZVoJpg8pGrOCnzaMko3NoNIK659dVMLK5y+fwEbsXHfH6mACFHMhxzd/++JGa7eJJhVTuqWi8dBtZkhko7mzhYKWEB2YsbjA4QXmvp9GtDAL5ucwznsAKLAP7ixbRfPfdEmIhPPJBUe90HIWOlIl0trgYI9LHvqRXs7Djx4NJ940DEWn7s4RQ8nzWMKIN+XMZLLS/oF/shUU8h2+FXUxkI7M42D2mr5ro5Xr1FaWElDsIygVThrmYR5imiARGDtFLGbta3FrsnWkxa42BDlu4UMz1lUjDbgVnq5DF2Mqe13DzVrv+8ZiTxtG6f2saIrJyoj9KwHi1PW3zBLifL0bE2i3uFL03LMGZqrdG0v8XYz/MchWXSbko6zlmH0+HntbN9ln+l27PQ/jDhXI16no1fO2pvTvdxWrnQqxwV/Mx2nwwMeGvBBk/TQLPHLhtdn1JTpot8qEez3p2e7tCjq0gfdps1/r26dddhglbFxa8wmpA61THpXeGDukOMT27aV1vjSxjqlShJvgi6m32Y7eaYUmrF0hKBSgH6b/15pD2KZw7PI6WoTBFgw9MO1S0oozzX2YlchaoP5zQtbcxWlGbzHoZU4UM9Q1CUep1mgWFJoFLKO/TfYd5GmtxiFC56ipJK7UP/0X0QcySQfVLs4OFXRtuRyjvI8CeEUNX7ZFMTlk44luqM/GNLTYZpABwerGROaNh0x4OhQk3qalloKvZ8pY6xHiB0zghcR8eHbjVQ23PrrEdBgqFxxFScYH6XoMjD7uj4JBMyTRXhR0HRepJEf/KIs+Xw41TXviDf3ldZCWQtvasoSMs+O9cuf9rMCnrFEufUA/3i65cp4m2WO/t/6tfn7OcW1S713yPWHx19TY9iy5trZbNY/lVNLO/h+b/PuSMBNSJVqA0K/Z1Zpk1VKq/N8g1ZknNbrQufuaI/u3gtevx+ziWu47dQoWznWBw/cLXrKl9DeMvMXVovvbeH9PjK8frWq4S9uufDQfSz0F5uuDMm9jeh8FMQNX7BnQx14SE2EZfs/WTXsSH/kXfFdVrvqnaCJYWB4IJc4k7vzi+99PHFqMte37Rcn3UWIo2QycfUsqu7xt4xOqsfQK3N++g6Bat5dsOgJHwRm3GUPtkTs5wssqNFMbhrMc/FVKveV4E3RYr3vtM/PbO1y9YeQt7wFiWwdQXJeaXXiRZ2CIvIwhybKddyNlsyP/MntdCO+vMh0tt8tGpuU/HiPkSRVREbyTdk/yaRxnkwvj1yU1k+rnucbG3VOXVVHkzF59gGT67rq0ifvUy3eIGFAfrCNWsM9vbisnpSe/oHtH/vqI5+vdL+2HMvtrLXSlOWdazkwc/TN0FXPWVdpjzD25Cd9yn9wJR+MxNln9G8HMnOutk6pJ+C6uxwsP889xNntAKydZKCzOfDuSUTmO0M8XHkZ9JDdu0hEwvL+BYAyPpGoXC48gXEF9NnGovr45F2KBECwvBqVECZkrmvXnu4EfqrxRCkRK/wBB4zA6Ttvp9qFRHOv7638v3MwZ2iR4FlTIiBsM7r64WNaMEhIT55eM+zPNJI6go5qj0YKWflGBfikk1pUwKvibsvnmmoFlydzqOy8VNatqhl2z7yuW1+dfN15o429noG43r1NrNaGTyOs4c1ypOs3Zu9lEDlj/ezqkl7RjGLnxElRT0ypKKGtynT1kl5pGWrpoxrjgcOjpbGKL339Ia9FM2vsgGH0JE/YNuKGTE5/JNMPmGYWUDrZTgeiowcvzNK8i93GCbYf+WBAuC1pFCjbdG5s/3YlkfjX6tOu5Yc8bgl2/bCMBweyqOwueJD8wx+D3hsm++2h47s2Xc1454a9OO4e/fouct9L26HnqlEfPYhVr+lujnMn46zHU7PmnSllaWfDfV9mp5N4k9c/2CIhlHrz6EiEBXDlLoOiBaGJnyvff7PrvftuJ4VyCMTgVSU07p8MrhdXtAXxBN9G67amL+Jg6bGmDxKEMLsihU6wADRQVlG3Nr/twiDxCyelrbXUlNdralvcTffcKv/cNPjTTtmsf0GxQo+pm1sfyMApxGAlO1unkLAn3ENA65Sa0y14VjIMLmMLcIjwYAWZKFs78GbawUBgEE0oKWegAoGqLg10r0MamNgb50jgAFACUZMMz5lIT1lZQ0QZVjKNazgSGj+2GZBtWFBHEhiU/p8PuuJN6s5Xuo/5SyYjOqYsZLpGjiaxZLxbtmwFSW0BGJkZpDeVsgyc+PtDZNSOuOv5gkxoMJW05JFJUBlIIB1EYxRpQV6/vESNkou6QyWVovDeQk4GFTekDC/9DFPZc4g1f70lEbnaDeX6BVX5QBNWYdo2fqoWLBVSYMpRYd6mSP9DAHzDAdUbH4L7fIWGZcZRRYn5Rhr7exuHYhVybPF1Prl1pBLNlWSoDIz6DlvgekM2MycCzyV0Z70OGEU2HkhyCKNFIzlEJ2GzUlSGyuvEqa8xBG0pBG81pYC7lsD1ElzG8VmblEGuOM3QR4YKbKMHHbzrP/MAZT2VQBWE/PCFMWKTvOHHrSAZSzA+VjBFUbyLwiC6sKE2xqE2pIONb1D9fjDf5qbdojGiizheJFOxX+p8LZVzhpHopobMflUMBSdL5JV99wblEqMyz2ehm3IWIXMGAMonXotoiRQ9MfJ9E/IjvfZ6pVEKfVCxeVT5MOGoqBFIYWDvQJj1iuIwhTexVMS0oZ8eKpRarNdCKtFSE2lYjCkWw0b1wS9rejAT6jA6ejEC6jEKenIS6jIYelOxVVnzXToWlXpanVm4RnjVINNQul8Qtd0rWhZOroOQcBwT2fvh1cR1q2/WWtjgkREDdYH6JIWmQKmYHU9pyKeeJ1dDfDqb3Fcol2OBww4dNvaEwsYn3X0iop5eLImnzGwbgErmdha2AF6W6j0nYRPjyx+HdTxspiclEUCdBLLNFhNiIxv4v6j+i/4A6Youz0a5jgIoGNbYAtOe9lOlaDxCbAcDezku6hnGJZJcNIYEOBO5HB0kPiIKiEyReo+OPHmXG7Mm8dqHgUHmD/xANrgBoFEU9qLcY7arfClMQJhaDw872XMW35XZeRBhbx8GuvLYR8TRKnE7lHmmlBeh5DOzvG/Wspe7UmcytxFugpzy+1tffxLA/CK29Z7KM+F1Of355eUZw/iDEat2go/7a2f2BseVKpzTi+jwy5MrHr88+A4pvlk0jgfcgrVlGB8Uu2G0W7OYO9pd2HRXxWx5/YtccQLpXKX2OKYbOA8BrCdTAsJqgBWx7GuPHfnZ/JEx4R3IdE3C4V3EBavg1ztljxsT4Q0SJMWzGlBmdSEPuh2Ng9LHoTHRcogTw6SxyYQneu+ODmaQipH9qW98THyYCzefdf2ipHjSDnyigpesutu8lbZnUKaQwoKaXk4jmYSRcm8H5rXlZpj8w2LvKqaBf+e2kI5ct3IyzKTcvFy4wzxBw+9WUNxakp6GyavepxG/Bq8i9CyiOdJUEfNKMJlfEKgcf/nu+Mw6H0GC0LTVPakj13ASN2Ucn8305vEluB2UjfKTUceZng+vDkLSByFchjyWKRjEniLocvTb09yl61tbnBPAwsD9LLY5XmJeMCYoUPMsGiq+OUgTYPJXrWJ+wCS26bHrKKtt427/O8JOSVAe1YMcdyRLKXM2aE6ImGJzyHNFq3nEv2XVuFUzi9ATpGWpSB3BiJAEVeF0uD9lfnhu4LGb0CnPrdcPrU7EFoJbGrDgtsvirCVnTL+JOrqRwoCHQaJnL9Wi46hbch4ysXGC0sPCGkEUeXLiz5RRHmzpWCjVRgZeZnDXJxsxYCN2pzAXULYukSU//SJA6nvPLkXSy6PR/CDEHFYs23+bo1uezfwLJERri+6vyfvZiz/bwCatE604cxutybZn0/8rHlk/Xs2YDKI86dz1rIxc3fys5eXQZ2fcFUUKA8lfbcC1XIfiW4DRhQvsDiG1n8kG8wOrN+CUPbJCryoT9TCuKRR12cOCY2p5wHM2uvHl/7JUqspb7+6vERma9nSJ1ym+tf3gBMYq30eQa3jTg/PF7x7293JloLMgWK+IrmheNDu/NfgiPLwEQQEKvueBWm7wikVgj3n/t4x/z8ixhTAfC6vX4iK0fHpSeHm07rwAqyqQ3jspvbTvGjjNotuUKLx7zl7CQpEDVY5aIjdO3tTxLsvbAGP/fv8lHo=
*/