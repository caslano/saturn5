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