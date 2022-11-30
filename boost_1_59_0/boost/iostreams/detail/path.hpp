/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/path.hpp
 * Date:        Sat Jun 21 21:24:05 MDT 2008
 * Copyright:   2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the class boost::iostreams::detail::path, for storing a 
 * a std::string or std::wstring.
 *
 * This class allows interoperability with Boost.Filesystem without
 * creating a dependence on Boost.Filesystem headers or implementation.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_PATH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PATH_HPP_INCLUDED

#include <cstring>
#include <string>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
# include <cwchar>
#endif
#include <boost/static_assert.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS //------------------------------------//

class path {
    template<typename T, typename V>
    struct sfinae
    {
        typedef V type;
    };
public:

    // Default constructor
    path() : narrow_(), wide_(), is_wide_(false) { }

    // Constructor taking a std::string
    path(const std::string& p) : narrow_(p), wide_(), is_wide_(false) { }

    // Constructor taking a C-style string
    path(const char* p) : narrow_(p), wide_(), is_wide_(false) { }

    // Constructor taking a boost::filesystem2::path or
    // boost::filesystem2::wpath
    template<typename Path>
    explicit path(const Path& p, typename Path::external_string_type* = 0)
    {
        init(p.external_file_string());
    }

    // Constructor taking a boost::filesystem3::path (boost filesystem v3)
    template<typename Path>
    explicit path(const Path& p, typename Path::codecvt_type* = 0)
    {
        init(p.native());
    }

    // Copy constructor
    path(const path& p) 
        : narrow_(p.narrow_), wide_(p.wide_), is_wide_(p.is_wide_) 
        { }

    // Assignment operator taking another path
    path& operator=(const path& p)
    {
        narrow_ = p.narrow_;
        wide_ = p.wide_;
        is_wide_ = p.is_wide_;
        return *this;
    }

    // Assignment operator taking a std::string
    path& operator=(const std::string& p)
    {
        narrow_ = p;
        wide_.clear();
        is_wide_ = false;
        return *this;
    }

    // Assignment operator taking a C-style string
    path& operator=(const char* p)
    {
        narrow_.assign(p);
        wide_.clear();
        is_wide_ = false;
        return *this;
    }

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
    // Assignment operator taking a boost::filesystem2::path or
    // boost::filesystem2::wpath
    // (not on Visual C++ 7.1/8.0, as it seems to have problems with
    // SFINAE functions with the same parameters, doesn't seem
    // worth working around).
    template<typename Path>
    typename sfinae<typename Path::external_string_type, path&>::type
        operator=(const Path& p)
    {
        init(p.external_file_string());
        return *this;
    }
#endif

    // Assignment operator taking a boost::filesystem3::path
    template<typename Path>
    typename sfinae<typename Path::codecvt_type, path&>::type
        operator=(const Path& p)
    {
        init(p.native());
        return *this;
    }

    bool is_wide() const { return is_wide_; }

    // Returns a representation of the underlying path as a std::string
    // Requires: is_wide() returns false
    const char* c_str() const { return narrow_.c_str(); }

    // Returns a representation of the underlying path as a std::wstring
    // Requires: is_wide() returns true
    const wchar_t* c_wstr() const { return wide_.c_str(); }
private:
    
    // For wide-character paths, use a boost::filesystem::wpath instead of a
    // std::wstring
    path(const std::wstring&);
    path& operator=(const std::wstring&);

    void init(std::string const& file_path)
    {
        narrow_ = file_path;
        wide_.clear();
        is_wide_ = false;
    }

    void init(std::wstring const& file_path)
    {
        narrow_.clear();
        wide_ = file_path;
        is_wide_ = true;
    }

    std::string   narrow_;
    std::wstring  wide_;
    bool          is_wide_;
};

inline bool operator==(const path& lhs, const path& rhs)
{
    return lhs.is_wide() ?
        rhs.is_wide() && std::wcscmp(lhs.c_wstr(), rhs.c_wstr()) == 0 :
        !rhs.is_wide() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

#else // #ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS //---------------------------//

class path {
public:
    path() { }
    path(const std::string& p) : path_(p) { }
    path(const char* p) : path_(p) { }
    template<typename Path>
        path(const Path& p) : path_(p.external_file_string()) { }
    path(const path& p) : path_(p.path_) { }
    path& operator=(const path& other) 
    {
        path_ = other.path_;
        return *this;
    }
    path& operator=(const std::string& p) 
    {
        path_ = p;
        return *this;
    }
    path& operator=(const char* p) 
    {
        path_ = p;
        return *this;
    }
    template<typename Path>
        path& operator=(const Path& p)
        {
            path_ = p.external_file_string();
            return *this;
        }
    bool is_wide() const { return false; }
    const char* c_str() const { return path_.c_str(); }
    const wchar_t* c_wstr() const { return 0; }
private:
    std::string path_;
};

inline bool operator==(const path& lhs, const path& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0 ;
}

#endif // #ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS //--------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PATH_HPP_INCLUDED

/* path.hpp
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
*/