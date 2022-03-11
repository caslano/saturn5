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
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
*/