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
    codecvt_category_t() = default;
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
    // Return a default locale object.
    return std::locale();
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