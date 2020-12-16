// Copyright (c) 2016 Klemens D. Morgenstern
// Copyright (c) 2008 Beman Dawes
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_LOCALE_HPP_
#define BOOST_PROCESS_LOCALE_HPP_

#include <system_error>
#include <boost/process/detail/config.hpp>

#if defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/locale.hpp>
# elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__) \
|| defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__HAIKU__)
#include <codecvt>
#endif

#include <locale>

namespace boost
{
namespace process
{
namespace detail
{

class codecvt_category_t : public std::error_category
{
public:
    codecvt_category_t(){}
    const char* name() const noexcept override {return "codecvt";}
    std::string message(int ev) const override
    {
        std::string str;
        switch (ev)
        {
        case std::codecvt_base::ok:
            str = "ok";
            break;
        case std::codecvt_base::partial:
            str = "partial";
            break;
        case std::codecvt_base::error:
            str = "error";
            break;
        case std::codecvt_base::noconv:
            str = "noconv";
            break;
        default:
            str = "unknown error";
        }
        return str;
    }
};

}

///Internally used error cateory for code conversion.
inline const std::error_category& codecvt_category()
{
    static const ::boost::process::detail::codecvt_category_t cat;
    return cat;
}

namespace detail
{
//copied from boost.filesystem
inline std::locale default_locale()
{
# if defined(BOOST_WINDOWS_API)
    std::locale global_loc = std::locale();
    return std::locale(global_loc, new boost::process::detail::windows::windows_file_codecvt);
# elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__) \
|| defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__HAIKU__)
    std::locale global_loc = std::locale();
    return std::locale(global_loc, new std::codecvt_utf8<wchar_t>);
# else  // Other POSIX
    // ISO C calls std::locale("") "the locale-specific native environment", and this
    // locale is the default for many POSIX-based operating systems such as Linux.
    return std::locale("");
# endif
}

inline std::locale& process_locale()
{
    static std::locale loc(default_locale());
    return loc;
}

}

///The internally used type for code conversion.
typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_type;

///Get a reference to the currently used code converter.
inline const codecvt_type& codecvt()
{
  return std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(
                detail::process_locale());
}

///Set the locale of the library.
inline std::locale imbue(const std::locale& loc)
{
  std::locale temp(detail::process_locale());
  detail::process_locale() = loc;
  return temp;
}


namespace detail
{

inline std::size_t convert(const char* from,
                    const char* from_end,
                    wchar_t* to, wchar_t* to_end,
                    const ::boost::process::codecvt_type & cvt =
                                 ::boost::process::codecvt())
{
    std::mbstate_t state  = std::mbstate_t();  // perhaps unneeded, but cuts bug reports
    const char* from_next;
    wchar_t* to_next;

    auto res = cvt.in(state, from, from_end, from_next,
                 to, to_end, to_next);

    if (res != std::codecvt_base::ok)
         throw process_error(res, ::boost::process::codecvt_category(),
             "boost::process codecvt to wchar_t");


    return to_next - to;

}

inline std::size_t convert(const wchar_t* from,
                    const wchar_t* from_end,
                    char* to, char* to_end,
                    const ::boost::process::codecvt_type & cvt =
                                 ::boost::process::codecvt())
{
    std::mbstate_t state  = std::mbstate_t();  // perhaps unneeded, but cuts bug reports
    const wchar_t* from_next;
    char* to_next;

    std::codecvt_base::result res;

    if ((res=cvt.out(state, from, from_end, from_next,
           to, to_end, to_next)) != std::codecvt_base::ok)
               throw process_error(res, ::boost::process::codecvt_category(),
                   "boost::process codecvt to char");

    return to_next - to;
}

inline std::wstring convert(const std::string & st,
                            const ::boost::process::codecvt_type & cvt =
                                ::boost::process::codecvt())
{
    std::wstring out(st.size() + 10, ' '); //just to be sure
    auto sz = convert(st.c_str(), st.c_str() + st.size(),
                      &out.front(), &out.back(), cvt);

    out.resize(sz);
    return out;
}

inline std::string convert(const std::wstring & st,
                           const ::boost::process::codecvt_type & cvt =
                                ::boost::process::codecvt())
{
    std::string out(st.size() * 2, ' '); //just to be sure
    auto sz = convert(st.c_str(), st.c_str() + st.size(),
                      &out.front(), &out.back(), cvt);

    out.resize(sz);
    return out;
}

inline std::vector<wchar_t> convert(const std::vector<char> & st,
                                    const ::boost::process::codecvt_type & cvt =
                                        ::boost::process::codecvt())
{
    std::vector<wchar_t> out(st.size() + 10); //just to be sure
    auto sz = convert(st.data(), st.data() + st.size(),
                      &out.front(), &out.back(), cvt);

    out.resize(sz);
    return out;
}

inline std::vector<char> convert(const std::vector<wchar_t> & st,
                                 const ::boost::process::codecvt_type & cvt =
                                     ::boost::process::codecvt())
{
    std::vector<char> out(st.size() * 2); //just to be sure
    auto sz = convert(st.data(), st.data() + st.size(),
                      &out.front(), &out.back(), cvt);

    out.resize(sz);
    return out;
}


inline std::wstring convert(const char *begin, const char* end,
                            const ::boost::process::codecvt_type & cvt =
                                ::boost::process::codecvt())
{
    auto size = end-begin;
    std::wstring out(size + 10, ' '); //just to be sure
    using namespace std;
    auto sz = convert(begin, end,
                      &out.front(), &out.back(), cvt);
    out.resize(sz);
    return out;
}

inline std::string convert(const wchar_t  * begin, const wchar_t *end,
                           const ::boost::process::codecvt_type & cvt =
                                ::boost::process::codecvt())
{
    auto size = end-begin;

    std::string out(size * 2, ' '); //just to be sure
    auto sz = convert(begin, end ,
                      &out.front(), &out.back(), cvt);

    out.resize(sz);
    return out;
}




}



}
}




#endif /* BOOST_PROCESS_LOCALE_HPP_ */

/* locale.hpp
qn/AX5RfYJTaElR3O1v70sh4ubfl/4wjwe8/XWZ9jp5axh2dAtt3FnNbuvsGLdhv+nGfQD6D/7fHlxzTZv3tk3n3N38HR6m5JbZ96Ijcgx6gEhr83GeWI95rgPrGq8Zl3Psa57dVrmMaKq9bG3d5HRss7z1HnbJs94Qnmde5Xdvp+zO63HAZzuJM5ZLPqTz3IeIlPZrUJnob1Emz+hETcqli/tDTouQbyjx7sH/VvQdzjnslfmoAUeU9Qhn3Y4zv1A/iu8un0vltAHUdGLBws+c79Y8zrPuETM+vM233gT6Ue1peephv0Mqwt3wH31Nm5wyzzNX/SZk7pAzfWmVkUMZqowzvhQs8Zaxh2J5nmWc+fvfMaajsNXLfKuhfLu9Wc173TGpoXkfJ4yW/PVj8hX2d7HlcPJPYaeTxXvxhQ+W0J88LxrwC/5LqybO+Tp5UK09iQ3kqydMjlDyh69Z58jxfJ89S8vR151lUN88/2bvv+CjKNIDjs0lIIQHSCCFECB2khd5C70hHFBEJIQkkkEYSOiehSG8qKqAUMQJSpEtVkSKonDRRVLqoVEWkKRzcb599p2QZTu7+u8/H8Hn47jzzTnun7Ozs7DtPevcKmkJiRrDr990jmO+GmA/nBprhTfcG3EgMIzYRI0NsVaHK2cQHyu3KUSF5yw4KEgljerbjHR1iBN3/W/zjL4YNoH9j5qeAfTmZl4+JnYSP+t0zYX1NGTMKqWXdo7ofEFOJo0QM0wmk/1nJmQaRK0js5vVT6r7xlUGIweQnkAtBQsY7k+5QXhcmhqlxzA52RaR7TkUE+eJECeJFyzyMCSHUMDlYjChCjCX0ZRmnXEiMV6/DcQLxEvEZ3RVxDtN5AssQVQjndCeq8tE4iZhMTCGmOocNlm3BmN8sur/AaZZlGE3usIrpKj9DORNnqdcNlY3we+cyYzieIpBwjaMxeZSyXxAo/W4TTVRd/0HcJe4R/1LD3VQSxrJNIiYSU4mm5Ah5fZ3Qx6Pp9SWvEV9GmbaKbkESvNb938ZhDPOIcuY03F+bvx1iGPdxWaetpuc+fvvyU1WES5jjeMVcv5h3PG+pOn41BNX28ROOJPTlOEv8SPccyuzEZqrerdE8xByXTAtbkHsDz6hcW8vyPBVilJFhW6p+rdTrubbDmfFaiLktzCf07XK+ms9pyPI+tO2dkvJGWXw4zioZnnHJtNR0zP1yQbDrd1ueBN0PRRvyfgyXn+hgibAgmReJiDy/98rTvpHxPvus6743+S3KBC/b34m3CM77Wy+jLZULVRkW9e4dbt1z3bqz3bojq9CtfucSyXm4tMXSqVaNaJULNnPV66vc4SfNXB2VO1DBzNVWuc2WXE2Vm2XJ1VC5FpacPt0oMxddT+XaltNzNevr06hmyenTKGLJ6dP4uayZq65yWy05fbprzFw9fXknWnL6dJ+KMnK19PH1LmHkatZSuV3FjVwNfXznnjBzev31teT0YcdFGjljfdQwc9X1eqlYzMgZ9VzeX8/R5LPKBVpy+vh+zq/nqtfXx/eNJVdXXw5LTp/nDWbOWB+5lpy+HK+aOWMdpZk5Y314mbl6+nR/9zNzdfT6M3PG+lgbYOb06eZYcvryZpq5usb27Gfm9DrYacnp8xJnGVafl66WnD4vzSy5Wvr8Wcan18EiS66Gvn9Ycnq9vGjJ6cuRaubq6MvxgiWnL0cHS05fjhhLTl+OSpacvhwRlpy+HH6WnL4cf/qaOX2eawWYOX2eT5vlauvzfNCS0+f5PUtOn+fxlpw+z6mWnD7PPS05fZ5bWHL6PFe15PS6L2rJ6cvha8npy3HXx8jV0uf5F0tOn7/PLDl9XrZbcvp037A=
*/