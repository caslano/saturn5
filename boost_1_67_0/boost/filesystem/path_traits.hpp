//  filesystem path_traits.hpp  --------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#ifndef BOOST_FILESYSTEM_PATH_TRAITS_HPP
#define BOOST_FILESYSTEM_PATH_TRAITS_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/config.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/system/error_code.hpp>
#include <boost/core/enable_if.hpp>
#include <cwchar>  // for mbstate_t
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <locale>
#include <boost/assert.hpp>
// #include <iostream>   //**** comment me out ****

#include <boost/config/abi_prefix.hpp> // must be the last #include

namespace boost { namespace filesystem {

  BOOST_FILESYSTEM_DECL const system::error_category& codecvt_error_category();
  //  uses std::codecvt_base::result used for error codes:
  //
  //    ok:       Conversion successful.
  //    partial:  Not all source characters converted; one or more additional source
  //              characters are needed to produce the final target character, or the
  //              size of the target intermediate buffer was too small to hold the result.
  //    error:    A character in the source could not be converted to the target encoding.
  //    noconv:   The source and target characters have the same type and encoding, so no
  //              conversion was necessary.

  class directory_entry;

namespace path_traits {

  typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_type;

  //  is_pathable type trait; allows disabling over-agressive class path member templates

  template <class T>
  struct is_pathable { static const bool value = false; };

  template<> struct is_pathable<char*>                  { static const bool value = true; };
  template<> struct is_pathable<const char*>            { static const bool value = true; };
  template<> struct is_pathable<wchar_t*>               { static const bool value = true; };
  template<> struct is_pathable<const wchar_t*>         { static const bool value = true; };
  template<> struct is_pathable<std::string>            { static const bool value = true; };
  template<> struct is_pathable<std::wstring>           { static const bool value = true; };
  template<> struct is_pathable<std::vector<char> >     { static const bool value = true; };
  template<> struct is_pathable<std::vector<wchar_t> >  { static const bool value = true; };
  template<> struct is_pathable<std::list<char> >       { static const bool value = true; };
  template<> struct is_pathable<std::list<wchar_t> >    { static const bool value = true; };
  template<> struct is_pathable<directory_entry>        { static const bool value = true; };

  //  Pathable empty

  template <class Container> inline
    // disable_if aids broken compilers (IBM, old GCC, etc.) and is harmless for
    // conforming compilers. Replace by plain "bool" at some future date (2012?)
    typename boost::disable_if<boost::is_array<Container>, bool>::type
      empty(const Container & c)
        { return c.begin() == c.end(); }

  template <class T> inline
    bool empty(T * const & c_str)
  {
    BOOST_ASSERT(c_str);
    return !*c_str;
  }

  template <typename T, size_t N> inline
     bool empty(T (&x)[N])
       { return !x[0]; }

  // value types differ  ---------------------------------------------------------------//
  //
  //   A from_end argument of 0 is less efficient than a known end, so use only if needed

  //  with codecvt

  BOOST_FILESYSTEM_DECL
    void convert(const char* from,
    const char* from_end,    // 0 for null terminated MBCS
    std::wstring & to,
    const codecvt_type& cvt);

  BOOST_FILESYSTEM_DECL
    void convert(const wchar_t* from,
    const wchar_t* from_end,  // 0 for null terminated MBCS
    std::string & to,
    const codecvt_type& cvt);

  inline
    void convert(const char* from,
    std::wstring & to,
    const codecvt_type& cvt)
  {
    BOOST_ASSERT(from);
    convert(from, 0, to, cvt);
  }

  inline
    void convert(const wchar_t* from,
    std::string & to,
    const codecvt_type& cvt)
  {
    BOOST_ASSERT(from);
    convert(from, 0, to, cvt);
  }

  //  without codecvt

  inline
    void convert(const char* from,
    const char* from_end,    // 0 for null terminated MBCS
    std::wstring & to);

  inline
    void convert(const wchar_t* from,
    const wchar_t* from_end,  // 0 for null terminated MBCS
    std::string & to);

  inline
    void convert(const char* from,
    std::wstring & to);

  inline
    void convert(const wchar_t* from,
    std::string & to);

  // value types same  -----------------------------------------------------------------//

  // char with codecvt

  inline
    void convert(const char* from, const char* from_end, std::string & to,
    const codecvt_type&)
  {
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
  }

  inline
    void convert(const char* from,
    std::string & to,
    const codecvt_type&)
  {
    BOOST_ASSERT(from);
    to += from;
  }

  // wchar_t with codecvt

  inline
    void convert(const wchar_t* from, const wchar_t* from_end, std::wstring & to,
    const codecvt_type&)
  {
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
  }

  inline
    void convert(const wchar_t* from,
    std::wstring & to,
    const codecvt_type&)
  {
    BOOST_ASSERT(from);
    to += from;
  }

  // char without codecvt

  inline
    void convert(const char* from, const char* from_end, std::string & to)
  {
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
  }

  inline
    void convert(const char* from, std::string & to)
  {
    BOOST_ASSERT(from);
    to += from;
  }

  // wchar_t without codecvt

  inline
    void convert(const wchar_t* from, const wchar_t* from_end, std::wstring & to)
  {
    BOOST_ASSERT(from);
    BOOST_ASSERT(from_end);
    to.append(from, from_end);
  }

  inline
    void convert(const wchar_t* from, std::wstring & to)
  {
    BOOST_ASSERT(from);
    to += from;
  }

  //  Source dispatch  -----------------------------------------------------------------//

  //  contiguous containers with codecvt
  template <class U> inline
    void dispatch(const std::string& c, U& to, const codecvt_type& cvt)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
  }
  template <class U> inline
    void dispatch(const std::wstring& c, U& to, const codecvt_type& cvt)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
  }
  template <class U> inline
    void dispatch(const std::vector<char>& c, U& to, const codecvt_type& cvt)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
  }
  template <class U> inline
    void dispatch(const std::vector<wchar_t>& c, U& to, const codecvt_type& cvt)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to, cvt);
  }

  //  contiguous containers without codecvt
  template <class U> inline
    void dispatch(const std::string& c, U& to)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to);
  }
  template <class U> inline
    void dispatch(const std::wstring& c, U& to)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to);
  }
  template <class U> inline
    void dispatch(const std::vector<char>& c, U& to)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to);
  }
  template <class U> inline
    void dispatch(const std::vector<wchar_t>& c, U& to)
  {
    if (c.size())
      convert(&*c.begin(), &*c.begin() + c.size(), to);
  }

  //  non-contiguous containers with codecvt
  template <class Container, class U> inline
    // disable_if aids broken compilers (IBM, old GCC, etc.) and is harmless for
    // conforming compilers. Replace by plain "void" at some future date (2012?)
    typename boost::disable_if<boost::is_array<Container>, void>::type
    dispatch(const Container & c, U& to, const codecvt_type& cvt)
  {
    if (c.size())
    {
      std::basic_string<typename Container::value_type> s(c.begin(), c.end());
      convert(s.c_str(), s.c_str()+s.size(), to, cvt);
    }
  }

  //  c_str
  template <class T, class U> inline
    void dispatch(T * const & c_str, U& to, const codecvt_type& cvt)
  {
    //    std::cout << "dispatch() const T *\n";
    BOOST_ASSERT(c_str);
    convert(c_str, to, cvt);
  }

  //  Note: there is no dispatch on C-style arrays because the array may
  //  contain a string smaller than the array size.

  BOOST_FILESYSTEM_DECL
    void dispatch(const directory_entry & de,
#                ifdef BOOST_WINDOWS_API
    std::wstring & to,
#                else
    std::string & to,
#                endif
    const codecvt_type&);

  //  non-contiguous containers without codecvt
  template <class Container, class U> inline
    // disable_if aids broken compilers (IBM, old GCC, etc.) and is harmless for
    // conforming compilers. Replace by plain "void" at some future date (2012?)
    typename boost::disable_if<boost::is_array<Container>, void>::type
    dispatch(const Container & c, U& to)
  {
    if (c.size())
    {
      std::basic_string<typename Container::value_type> seq(c.begin(), c.end());
      convert(seq.c_str(), seq.c_str()+seq.size(), to);
    }
  }

  //  c_str
  template <class T, class U> inline
    void dispatch(T * const & c_str, U& to)
  {
    //    std::cout << "dispatch() const T *\n";
    BOOST_ASSERT(c_str);
    convert(c_str, to);
  }

  //  Note: there is no dispatch on C-style arrays because the array may
  //  contain a string smaller than the array size.

  BOOST_FILESYSTEM_DECL
    void dispatch(const directory_entry & de,
#                ifdef BOOST_WINDOWS_API
    std::wstring & to
#                else
    std::string & to
#                endif
    );


}}} // namespace boost::filesystem::path_traits

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas

#endif  // BOOST_FILESYSTEM_PATH_TRAITS_HPP

/* path_traits.hpp
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
*/