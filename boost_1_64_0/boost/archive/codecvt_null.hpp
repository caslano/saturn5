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
vMpxmr7yMaZQrhDao80muSMgqCQltgh8cYENfWw1H0NCD21IF6T5iwYh8shjTIgsYVKXa0a1luYwKY0wpXplMLL5t5Y2T/1+ASH7hUD20fq2t0wPZ4lPGx7O2j9dRhQT83Q5D2dJ21mF56F1v9lH7Y9pbFn1sdofkZdUNWK0i5BJArTXB92KSZyo8SSmCn7dytYzG5jfZBce+WxrUkLPu7kok7SaCVT9ljf4UsQsujWeRUwhV/kYmpBA3mPAdVHAcDabmLic+vSzLy0l/1ls8O8/zDfkPxNCyX8M+ErLDfjdW0LJfwQe6zfdgHevDyX/WWTq3xrwJetCyX8EXuJpTy9/3idb8o/llM+/xZI/8YPy+emW/J6zyuc3seS71tv4f7Pk32vT/v6FwfxVPFCrPH9+afl+rQWlf2dQfhn8t9CUhxnz9/64UPr/C015mAEftznU+pv178oz9P/t60f/FuSVf//IN+0BjPIvbgrF/ws8icS82mqWwFEQGPb2/zJ9GebsHBY3+Wl2zOqKe0RscxKm/oUIg8cecjyV4MgIXxPYQ45VMyiayCtAO/Drwm8qZuILU20Sh75gkzh9q01i2CybxKb/4ES3Sp/21JMJjjfU3zj8Leb/5fcW/H335G8bb1/t/wWKciRzhCceLCbSuTH0AkTzHKrXZe//BaY8eJ5h/zLWdn3gShsrkhWOiDT0jITgXW7xbRybSTFrMvCTo27kCA1eDj2hS1QuQnPmhGEVsXqjaqLZbXcUB7BwqdMTHB5auAxoeFDUm2kdkfJTfz89H748Y/+t+8iQ/274SfmE+H9WRTmeNypYC2oY7Ly+e704Roov58g5R/3KGY2Kesg8FIY78PkFZt7Zp12j6mJrz70dzQ1bmo5JunlGgiMzfI07sAeeXlw5VZbdgISf+rsQfwC95xtPhSquVktaqqYqbKyXNdB8tY1IPRaiJu0pYhIvKA6swn/zjP029gPD/+f9oew/DPhKXgN+cKj7YfI80/7DgF+yMpT9hwn/zoeG/DMUfBMTfp0BPzQU/PGPzP7MMeSfoeBXGPCR6wx4fUUo+w8T/oAx3rxQ8LeY8BWN/k8JBd8h2J/3FfxAe/jU/iIdCf/I3EvYQw9oYcRMBuBphAw0h63Cyt+eR+RxQwKuc78pjGhNOrF5Qr02Iq3UGZYX0cUvERxqkPg21y/zDgsHzcSBiBtVc+JaCF8ZkYxjVshQAiOwF6q8laqkOz3mGr4xMslQF73Kny+9asc09WXiLqaz3hx9kiaUtz39mRyRMCta/KH5VifGNxtjOcpUM+CNwiyiLExLjs6qbmPkIUrR4ipFbzmTj2ICfR8ws0w9yrtY6i8WMf8q+zGyuyhDvzTPK6OfUP8aSzyXaUz/fWBQ1sujSlHW0GmCchPR1+Ta8ghia+gNJyhdTY7f6WavhXr2MiKwV0L/BzPPZgThTyvt99MkuWKVHwrqeR0DhgcpcfIpdQf0FBUdnox0eLc4FXSTsYScgCDC8TUuzEWYrX+Qo/VI7oZh0rSIv/XsgsjwVZ5hp4j67zLK2BDkdbeQ2yENJOfD1JdCsvudE8UC6aWTAYmWkMph/PhnpgsQizCp4kFef72QtaI8OTe43BCfVB0PioPkJ0chCqOYKhkeCi+i98yh5/b8RxWbNVTYrKz5xGbNBJs1X7/rb8VcoDoKsF7nnTkiZLxrNrNROFsrrfzHqY+F/9CD/If5tP77SmEu/GPsK5mqB99X+nFHoHiBvaR3mCKiUOUCavg8OZtZhGk0C6bpP0ud6oHGCJd5JJayuOl4h+MpexBXGbMAeS+L2vRHHpSteSQYT0oCY+8rYBJs41y219BfXRFUMmOdDFE=
*/