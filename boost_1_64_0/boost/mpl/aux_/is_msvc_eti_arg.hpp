
#ifndef BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED
#define BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)

template< typename T >
struct is_msvc_eti_arg
{ 
    BOOST_STATIC_CONSTANT(bool, value = false);
};

#else // BOOST_MPL_CFG_MSVC_60_ETI_BUG

struct eti_int_convertible
{
    eti_int_convertible(int);
};

template< typename T >
struct is_msvc_eti_arg
{ 
    static no_tag test(...);
    static yes_tag test(eti_int_convertible);
    static T& get();

    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(test(get())) == sizeof(yes_tag)
        );
};

#endif

template<>
struct is_msvc_eti_arg<int>
{ 
    BOOST_STATIC_CONSTANT(bool, value = true);
};

#endif // BOOST_MPL_CFG_MSVC_ETI_BUG

}}}

#endif // BOOST_MPL_AUX_IS_MSVC_ETI_ARG_HPP_INCLUDED

/* is_msvc_eti_arg.hpp
U5vl96D75fzZBe4T4X9klCYiJiasWs3qNau7hvQOih4SpYvsHaCJkf78tf011c2XNSAmRhOt00ZGqEMCtGGa4IZqbYS6fHl1pF4ndQZqhkgdbawm6O+NU7G5p4+/Z8eWXXp4+6rd3dWaiKBK6uHD5XQPT/N0seh/d1phmoj+ulB1ObU0cguvTi3b+/u07elZSZqAq/m4rE/FqADGDgir9A/XPyaiZu8A/0CtLkYXXT3o68pMHie4ltY/JOpPjkM5x+j+5Dh6MZPPg4X4yz4EGf/s+CvFX2H+Gok/Oa1RNuO0C4hQtdIEqjoERKuaR0XTHaJqp4/gL0zVXN9f5aOJUnUK0qk6RsaqPDRBX7Ps/TURunDzpS/nWju4nGutz/56GoerW3fwFfli1OVqBaulQQ1NUbnqlUkOLheTMb0WAcFqnTZco44NCNNrvrpMtbWC//S200aw4b7alTxOeKDYrczWPyxYFa6NiNEO1bhL/eEBcabPFSpWqlK1WvUaDd2bfu30IwMHaILMF6ujn5eX1G3ctmPX5l5tPZp83XRitP0jMq2cpbWl6l/5Fyf2zYrGqTmqHK0drVVji6iKqBybOarpzy6ocvHPUfwxzj8RmKe1mOE/Pb5x7VWuNWu51a5Tt179Bs1btPTwbCWlppkFucfCwkL+S7NOs1T9K6F3t3Ku9cO6y5/9UJL+Wfpj3+8udekp+5XbUxetiTPfoA35K2NsKOaWulXUqqp0q0j3gZPYSE2au3Q0kYO92H5yozKHcTPmFSWT+c/BmG+0WT7HbNLyZTO9/NmkuZqN62icR02RJpd/IWO+utmk1TNLS59ekEiTJ5ieFpxNmiabNK1p+TLWd67ZfqCyldNWZjPuKrN86eOOt8hYvvR1W2Dx+fSOyPlElJ5vu9XnZf/ISs5nZ3ZR4LExzd4s7Q9jWh5j2r+2p35d6NDcp720z0VEiipQpEUN1MZJXb0upH5kRNgQsS00IQH6MN3X1ndMKkIbbLZj20jRLlOvaf/zXV7MpLm5T8ea/r5tO3h+3Tw4nGQ+F6rZQKWq5fp1x9yvPd5+xXLodUFZj521vnjs/OIxUxwvv3qesZpobciQP3VcDNfoQv3DtIFipIxzMA6wotw7tWjn2dLXmKaV09p29PVs7dklU5qPb5e2HVvL+aKYXbC/Ji7KbPu1aOtrzOMfo9FJJ2ximLQM/kGBZp9DNUED/XWcLJqlRYaFcZg09XPmxtT9o6K14Vod57Dm+4l8VqfKlDdaExDMHCPN88lncmb5Iv0DggMz9YdFBg005ecszjSMeQfV0mbkDdGyuqxyet7Wnh09u3D07unpIe22THiA+b4snVVpogN0Gv9Yt/RpkKaTzlDq1s6UT2c8Q1BlyqcXGU35xNmQWL2MflEGpn6dJtxUMOZpYqXEdOV+TXigJljKKcbNmh6hGZxlmqYZf57+2byiAkRpmqeJ05bs0vyDdHFZ0/URYgrmacbd3ZQmqiptRH//iKDIKJGsMtuHxfKb1ouGUJRe5x8coAsw5fNu6dvdmEvepzP3i0VLH5851dINidKY+sWcs2zGz4fps27jDBOfpfk2b+El7TzB2UxLF+kfKIouyzjSIolFNh+HoooKY39jxxUbN5thYqTs0yOBLEYzzSt9pzb19/D2NK45O2yQTqOTl1KMkTnPF4f7+bZMn6wpLWPzqgLr1pYZSwsntRvoHxzNTiBqH2Nbom0naS38OxrP9+RGoVy7BEZIRWZWgul1vqi/MtVPpvSsdZ0pzVQnymnaQH1I+md5+0oFIU9frroy9rPgrNMwT/MzzSwjXa+L9I7WxrIl2muGZKRnm6YPDNMGyUlUX7ogCkynMZ4=
*/