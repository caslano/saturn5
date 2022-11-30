#ifndef BOOST_SERIALIZATION_BINARY_OBJECT_HPP
#define BOOST_SERIALIZATION_BINARY_OBJECT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// nvp.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <cstddef> // std::size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/preprocessor/stringize.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/wrapper.hpp>

namespace boost {
namespace serialization {

struct binary_object :
    public wrapper_traits<nvp<const binary_object> >
{
    void const * m_t;
    std::size_t m_size;
    template<class Archive>
    void save(Archive & ar, const unsigned int /* file_version */) const {
        ar.save_binary(m_t, m_size);
    }
    template<class Archive>
    void load(Archive & ar, const unsigned int /* file_version */) const {
        ar.load_binary(const_cast<void *>(m_t), m_size);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()
    binary_object & operator=(const binary_object & rhs) {
        m_t = rhs.m_t;
        m_size = rhs.m_size;
        return *this;
    }
    binary_object(const void * const t, std::size_t size) :
        m_t(t),
        m_size(size)
    {}
    binary_object(const binary_object & rhs) :
        m_t(rhs.m_t),
        m_size(rhs.m_size)
    {}
};

// just a little helper to support the convention that all serialization
// wrappers follow the naming convention make_xxxxx
inline
const binary_object
make_binary_object(const void * t, std::size_t size){
    return binary_object(t, size);
}

} // namespace serialization
} // boost

#endif // BOOST_SERIALIZATION_BINARY_OBJECT_HPP

/* binary_object.hpp
We/aMK98Y1P2R+5SFrOaN+CVw/pckGS6KcFD6j2wTxQTlOHuEP1D7ejZrei7CrYeWb24zxn+axWLv0Yym3eu47wfCfCqBOwBNpoNhXLgp3g5UHdf6o1Z0p12oSUPeYdzXbVQcmcFX9KNzYKNJaMO2UZR5MDmoaOPipfjASUDTo9B3+lyWHgkI++hwEPf7fNZuWE/3CQLL5hu//35tv+FpV91Sr1s3uIIkO/7YuszDOgGiAfcgp+DnINRAHYAFoDrAwo4BzAL2OehdYfbY+mbBPh8aEp58b3rRg4AdwBOAToC1IFmgBSAZ6iTmewGv2Pq2wXwg75TDuAGZAOsAqcAkQBsgyJA6wNgyIZ2BOQD4QCcg67D3jMMyANqAlIBRAFGATIBmgKMAGYAcsDYLT3eAXlrVtqxpS6IA6gEdAKsAU0HMQDAoFxyygP2gbmj6uMLIAe4Aev13t+EUYBWgFKASICsAyDAM8ABAL8zBFxCNmDvE0awZ+8TDGAHBGOAn5qEcwRIAnACkALEAtwAuAH3QNoD6JMMEAT4ppLAN+ASgOp7BrgEtAK8AWjD3iP8qz05wAxgDIBIzYqTMsABIBqACRAKUArQEsAW4J15gD7AFTgH0B1bHzkAMYAZ+BysAJAAXAByPlQAeBvynmAAL8Do3+MYUU06LH3BAeDXWOX06btgHgAOjgg93gB+sA7sa1mAWABcfXrQdXh9kAqAdnIBPgElANCANUARYBgz4R3C6SgBlQBnQUwO0aAR4BoQCdB1WAa0ArB9ZAGdgH/hY+xJ/gVJD9QF6UCXNz8M8QR77mXG5qRDLUOnsNyOOvSq5qIN7claY/DjHZiLB9yGvycXIPtXwysAacAkgFLgM0Aw54AXQDigK1APqL1VAH4gjnaRSdvAWmwD1j6lAE4AR4BDgLBGwHAAcwA9sDX4O5I+YIAcAJ4+2f+1BwASQClAk+BWbaoQN1AXuANIPvQeZAA4ABdg5l+1qACyATwBzgGc/27CYPBDO4J1QDCA70MGgAfagq0DzQfLhyAAJwA1QBNg+WstSbI99D2GvwYtA8ADa4PfowtQ+4sUFWD47x1/3wM0AjgCBAPoSwIgzCbslXaODxdAHrAL4g66pBspX/cAwCnlxTHoU2nYnr7tG2tPMSAN9fcYZ1bVCXs8e3rZGUgdnA7n9ABnC6wmsfIEC+XTyaEe0MS5st/mNIpCTi1HtLyzpMbPOaekob6+Z16p1zB4bk1DkxH+Qe9ibU5ju0/b5mzQMe6Dys/Z09i0orKjYuGgvBb17eKjo1RJXa0/s3RiJN9f8Dls5IOsTnCsI+pjWrZkPd0M97bKxiaIogSOHaRybHzWvpBrifX+uLn5OD2T9LL0Q6yn4UDK6ZQa+3LCevkr7ZjelcIwo31OkcXejCd8t+rry7XSNo71XaE66Oq4piPqamTCqYcJeoHSgcNZNxL6RNBPh3LtdDprtMBtbKpEc516Zc05tTZ3fHorIUxva2oDyk6TNE9520Xazti0pKjAR7jEVhqtdaClYy61liTIEm0jCqelUEjbUVFx5cK0hWgY9qdTrUbPkFpHua+9D4hvXdMt3ErvsK765G6WR7sedtERVe0hAf+APnqhubaUxoyMpryN7m6UqZEItvfJPEV/gdQvXcHwXcwnJa2RfcX+vxqIDXV1u6pT6uvjLuw1b9Le9p771IUMbA46KiQL8kqGTTDWrHZAxgAPBARy5vpAKUBmtICghygpaTlX40xTM+SR+iO1VTWthkvslv/ocNKAOXpryr2MTTNJW3taWvycXbf/j70/D6eqCx+H8XPMmTOlSKqjhFBkCKEQIsdMpgZ0SIhDKRkyhIMkU1IRlZlEUUKZp1JCoTSgkymZ5/Outfehnuf5fL/v9/fP73rf63pdrbP3Xvtea91rrXta97rXrjVBjNXc/I2V3Ht5E1ondfwROpZKl+mmfQFCrysuDhRdyT2YP9XtMxfQTsHs/vhE9n2nvJkcjaFpZ+fJfLzDPfFMSmvUACAPm8pz2/HmVY00rj0xYVzGfC3iYoXG/MKBI/H07M93C1SElDUntorXeJu2RHOJ7jT9aGbY+lhManefO6nNfR274w7cNuYyH4vQ3HvKHj0xjoEYsc9vj8pe7aBPMd64le6FbYkH/Zdey89hPrsLcrKldjtLFJw5uUxbrV42mTrwNHOAYWFXZgGns/geGjk5LoklF69XWpnjoU0Pdgz2yTax5aWcOmNz/ZPZjzvmZSGEYHo9a7xFWQhHyQ8zebm0IC55TuHj5jSFtuYmdnYseW9jSqsMzT+39ec/LB7kHZCqLXCQbBtpuZlyw+riukQa5X2akTuWmVi+6Iv8Ytp2tD7bN4StX9bMjaau+nJPXmp5/pLj+LGbj2VvzQW/c3t75yzHzCmX9zf1EyzVfnVFHn1YZHhCiZxgY2duelmG83xZui2hFx/u+8qD5WtBeEEvwdLmYw3t+geWLl4D8h1mZpxbP4gL/DjpXyzxZh1nffIz54Ty+8d9JD1D7jGbDghcwIYllWGMxIPZmMN3EV138ch9zmBwN5Ezo7Vj9TpYLsf9YFDMP2Cf9FXhS2qMQ597S7pszzyKPFnOXiG4UQrn+CjAzcTecJ+dVVb/4XgtmboXG3uyGsyO37Xczz0ndu/85nfz+49nN98qEpMz6zqXP8AuMNxee+Sx2annRXfY7AAELPvTdIN/s9dxy8m9N5uIL7Ha3fZi2Hk4sPkL4O8lmoB5tcchZ97voWFuZNEP2D9V4NptYUOvb4n9/jIzu6oQ6yBa3x3XZ2LeV7re98nr7x7NWw0ylw+6yJ+gfbf7KVNLpnQSXcCbDPUEQft1A1L9jgc/0EXXbR7j4w8XO8P9VmCInN1XLq2z9fLILx0rzj4rhf5H8ua0mlXkJ0W/ByeeDfXE2Qp8qyhjr2+KL9PMz+144jb59Gaih8JrGmuCY63yNOVpXaihfuTZ7e4SyslnXlZhhr72PxEPVuIWCzt1/Ki2Vfdmy5mBwASNjzRNUceDfnt5rZ8yZbL7ZFEWKHWUNmGnmu6HAGb1N4Z0YTffX9BVOCwiJWtvc7K+OI2/Z13yk+19mglmJvZ3DSTYrmoN3dDv+lIac1bc1jbuxd6rdc0/ZW49+C7fdb0S4/6sKK3IVXPArCeBU76h2tJW3CQ2/VuCcThO63ViqfpITGnk5V27xFwb9sYnpfdKtso/f1IRHms8khPcVJfnrNPJaVc4Ps2HcyftL7dM6Ygqx9vmtIWLDDsSzh85O60fNRBl9cNSQnNsaMcR7huvNom78WJI+nyfbebduDLzH7+XfyUdNo891Sc8Ht8maqpfElP07kQhG9d1lkN2wk4tNILr96cHHEy8v+BIlovndep9l/vqYM+QF+4kb/53k0tHV/amRhh6Lw65FOYUJW1/2HCTXlDukteB6Y6UgWjeYTXRY8wTBmNNr7Zl3H/Xu7BfqD4joGzKbork1hijoRuBs4zy3SROG5nslltQ8qE57XmCGBfu5ANBHzqDadcmqYLnlgFfsd/7T/NKBl1QFBbIitP7ekti2qsqdhO9msPmNMGN8QEN2GazZkdycwKbhiQvJ42Tbby+1HpmhTqvn1JvSSLFMp41T7/2+ddVhn+O8Xrtcq94DzfRat2pz4N1zkLDxb60cRcsT71oq1KQ+2goebwlJfejgHgDd25I827xMy/r0ta1m10JbDXMij5IsGLfbtPGEJfHyvQhMaFI1vH1rbuFwmnrHHQHnz2rEDJi6iY9kTMJ7bZ8dMV7n6lj0OeM/j2PaeqijOS8fX8p0+Wl18tuun3E3FwuzlzeyD4uUN6UgdvW9nTg1k2tCQe/OHzEpR4UmuTZ6qq/+UFTRvrNM8ymE1o7dJSNrm/lNrVkHaTjm2pJ+mh/W/HGFcPSB7qfr/QxxFac+FzygCAyXjbic+QxYZsj/fHYMjHjzKl8vGzMpayTdO/ctl1XW++he9brVrbA8LDcQULkr1dT4qmHzF2zP6t9GChl3nvaXX7HAwm6cwWRE7vOYX7cZYxaJ1v7bNt5JynjT5V2Qg/33J62VSOX98ab3PXR1Hz/K5HZ1DTGpK4lQvueleO30ltJSleNafXuEpLP9f+Ky92TJ1tjmFCN5ZYQfPKB3+xZfhVW2+7U6aTczNz7ZDxjqoSL2Q7BPUpRw+MFYWL6RR+Hhm59Up4S4bJKWvLbbX9+1DdhZ6P4fZcp194mMkdWZaGHTGSg7iwjY2RjE+2kY+hzfxnag2U0gz76wstuVZYWAedfN9uVRR4haVAEX7dOsjl12dSbPuJo6InHO6ce7+ETXY9bLvCc7+QZVRXrOa83kqJtLtzuUGB5+7lyn9be29z8/t53dl+qfXaPy4TGy6TTrNWUfrOII15vTtLui1VJvCiX+WSHQqiph2JJiTM/Yyf3/ELTCH0jdn7zQ43AtuNvntLb+8SxxZhMnAjWPHDD7jI3WxsnwzMr/GC9ExNnHbAymo/vYC+p8t5hqOE0yewYoH72dquTuITREOPWxB8JmMsBws/r7twwtf+uoNl/MFn42ZvHAz3r1QlanV+uBJY9ovnRNql77vXVs5F+kiInA6u/BTTephdZEIu4wVKY8pzhIjnlJu+c4cDjAUXhO1nGN+8ryknvlBR2YntlnXhWnYkY3hF9r0OzaVu1nmZA+qMDUj1s6XYi0s+HsvMITwdymjeludD1XLx9dnooPqcrT1Isw+dzHcMBtZ735wuF5qcFms7hW7NcnTN39zXl2bLzXOeu2edhYN/IuqVZQdRCpKAlYWS6o6ZQsOwjjzKLo2YNh8RjTG2Xe5MRRl7mufBOf580tua7rV07zBSCb8m9T5DfN/D+cySbnuvx1yE3L99/kcIl8lQisMC8Ovtc1/t9YlO1I2IlgZTk0AgPQbUc99fYSSN5c4P50y9Zpx2PfpHziC9+prXE2aI8FeGR/CLBU/5cieC770W/zv2YcnmRT1rxKBvhLq48PxpXaec7F/971qK008sz2qT8UviLJcf2t34GbSsrR1uzPm5dKc0JXfdi6QzbqHHWzNBt9edLGXW5i98JlJUjI4x3N501mPNs82uX2eTZIaO+mP7GucX/csLH3YlLnp6P4/wTF3y7KpVfL0lRSi7XV77d6k24QllptyMsKcm+9O+mjN/d1EUz3UXwWigc3xMa1vCoLvPcjsm5ddzpp3boR79waRo4Z/zQ5kSZx0Lk3E1zG5Xh5DOn39xU+vUseJ6F60bsBkldHf3HD05L2MbeLJFVqk94LuE2Py0+wcJs3m2uzmj7ncib2Ot+yuljt9dws1s33tDS6/HzZ4MJ3VFe02xP5eR+v3rQavXks/clz+Yno4EzRctniYutvTl7cgY1pH90yn19toPRzutO8KDDVkdy6LSsUJanrVcFZ/IYx12ONFK12oarQTNXtm+azN4u0Tds15nEYuc4+MFcdlAhYGRBi//FXNWSz6l2hi8M8XFRySux5oe7qonbCJSvTlHzOx8GzXRVLTFgGoZ897EuuAhF+Prdr37pItupkLBBkuWRh6I4S1HChtBnAb6l0ifUnU36reUmxdwImXmfq+wb2Qa8FCK/BqsRXp3j/kE3IDDnzB8pv+uM7LRp/6aY6xKTzOpC1q1NvE4FeRJur3w0NnP8tlg6zmBerWFAIGS60d1tmohKEMus1qpiadHNdl9HWy1dhm1OuuLAQ3Oj6QuT8znzBPnC7uOlmvzszTaW5lK9I09kv16Rux+V7q+toavK7/Z1tu7MN/EVzXL7yC5htUfyj8Kz7utm9qQKFz6Rw69k/NL3t7lsI4Kv96qK+Hrq66OIwKkfD6Pzz6u0UNan6U8fP73XVTr3SnrTbjbpKOwetj3c3d38jm9FTsgxl/ju+8XwMp9GuvhrwpFqf1XbOG3p4LhD45kNbutjnpeHD45Lz6lrfVhgPnFck+aIWYJzckXi94rItmCmXusKr8/+IqO4DD+3zWJBXJjgusJdfQJPyn87Ymn3KrJXS1YVmpZMD4gmHtvkTnyY6aJz7av0h30pHSbPRz4+pr3QcHpYiF+S62DO62L2Sw44SdK3byr6hHcCSbUHT1YUhZTw9xeUF0cJtBNKf4h9ka83wqiybHry6pq4aGn+vW/P8uKuvsDUzdCkLLpl1oSYEMWDP6Y525YFFhxOTy8KNN/8OPgWfZxj/gbnXVHDgd7jtzraLKL0ilLLz9Ee/eYh7ubME/fM2s72sFYDY3s9cY++Hkv7S1nhz2Z6tN9PWUdWKzb5pD26l5JnsM/sRlbDblm5Xa75TRHPdGuNcNLG6pc3KyrQDVi9BpBXv+4RDFX3H6v070uwksCWDVD2NYr03x1UXZLX9Vg3/3CZgxKiK0l5Sqn49IByvjGfkkNZsVn+bSe7xFISsrD8PDl6xWbTSl/HZM90xXv6a3tlFD1+WEbNX3+cPvC6cOWtd2PBHsYNwkUCL+k82PJvvOK8ZWr+lZCZ31ynSQx5Jm07qRhVxi1MXGoqKuSVZomUjxI1vkd0NxbRluGNV+bWlHueI1/auLnmu1aaevymuOu/hh40OJuq3wtnbAx8wkLzObu828Q2xOqMqIJJ17r4Jm9M0/YBL9Ex2d/XpYkHO7c+d5zcFu/1XO3n+4M2WTPJEke4M2g7+rKHokzoeXTk4liEs5dIzJp+BiESFJ+QbRTNEIk+063sXR6W8zQiBWIF+ZqG+zK8P9g+9cvew3KXoWf54V2nlso5CYKdl+0pW887rU5L48sme9L9f2hGbdxh3NQbuvv6twci+TdFLwqJu2UH9iYwijyWiJ4Zn2y+NSeRbPBhWMA9kbU36bZINa9axIC8uWReX2wtNlSg4+bGyAHpjOoGdlrlyEnp3u+ZBh6MYVzChgHHsRP0YRuFzwa0YYsYw4SFw1PVuA4+nLOhtBIuUt4yPb7BVU3p5zBQ9b5fJBOpKOVUGsghi1Wd3vA8Ke/al18O71VvZQ58y1N/ehq/hdtIIYmPeOTgC1H3nsc4shmtK+3bY2OfOZ+2f/Hm7H3tQPfpnrnaQkx9+tavEVWjrMEyoXH32bweCffitXsvvdyN7WUPrrks0Bu6dSxnq4PQU4Z3m7YUX11Zsbo2XTltQVm7xJf5FEfr3onynLmY9MLqpa15WuQFabUVncfWG/Vvd+h3gMWVhwGDNc9tcddyhn3yZ9zqLjtHDw+4ePEqCj/s6Guxee2Q2NUp1ljdllLrVBzDtkWvL/Tc6EDpdOOyxeNyV+6G86UChZtCnaNzOt7l0/MXdOTnZ9xPSnF5rT3v4KnsZ/mNZzDY29P40PaGvaaWvabWT56X76n0k/l5fsf1s/qHaD8uJV9ZqPryOv6EmMvw09RYt9zPGIukAi8XAt3G7MwDz58ke58//+7oEcXKl5slFk8dM1UvNDoX/NvqVEFuuQj/4LGmjfEzRaXm++gH2FhlTGy5O4JGjqQ5nlErDymnl3x4j0ulad4juidM7klfOLuP8Bl1geJ74j/LFFJrvORPn3tDMDPp6rxHQ9h+XuBk1MYyBtZ1moyP8tgncx9MZRqZzHlwpSqO8XmY05zzemltySBhl2lwJsZ2YnjPqXzJD8wRze3WR0/ND/YusB3k7phU6XXId9h9MejK6MhC94KW
*/