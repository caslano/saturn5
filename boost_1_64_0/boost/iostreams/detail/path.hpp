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
9bdnZiv2VN8E3PvQ6edK+dFB7tXuk6av1/Wh4r6sm6r7RT5RNrjZf43dz+2faBX7U3XeWKXc+MjXk7yR6gyjfDcO99V/T7lx0P+FlWz6Vqvr1a37qPGF+huw+1ut5ehr7iK25FpRWdmCC4uc7WKJ82cqfIPl+4ykG6vupFgPWy9Yp1CGveSa16C/g7vnIWibP9An3P/TWpWtVwylLB4uZWLLNYXuuvMqjrtZ+purFlebVvF7yO2Ob6Qb5Jvq2Y79SQZwfJfMY0BPz2X4pAN0tYnnxd1fm9Se/CB9SInvZ++uX6UY9jnZZvomGue3z7C7213zJpz9J4dG6P3x1a87ModxMnn96spplbdpKIZWSY9vn4TQ/T7PNsA8dT1gGer/pt8UY/3ftb5e/qiQco2U9W8iS+z2UCgurpkeoXg831PXI/Q3vY1K/0X1RF1LbJ4zt3dx19ge0P2w69X1VzgOWpsI6W/MfT+4k9g8hYp+8c9T0Lq63WCbAJ3wd011fYuVpfeBoT9Qneutv2PerY5/hfspViaaM60LpbwNX3uSmD1mrFPdr67vsEbhfnrUPbniFm0k8uH+E/luTMCTW68y7cGidA6jc2EHdJJSo/ZH6yI6Z4wM17X62HUt/wD+dde1VL+ATvu6cuomFbYefHFrE+Fv8UipS7U43l2X0jqVI6XOllzxqKPOpnSyOG5uEXYpz+5G74UOSuTv+Pqsz8kOlTfLyWjpHL/ZTx2zZqTkbcdzQt6WutmxmWcS7neoOtlSv7eRbsg+ZG0251XYKgpXzFdTBCOr+e42tqNOUa3u22VNt9qbnjNx16fHXvlkvl04Dz+hru+hzt/O+HzJ/cZ3KPqqvhVzfBPpO3uUxRoKxCGd9O2ZqfrK8zg+gqh2fTCzdfPW/ezu8uaGvnJ3m0U/H8+rsD3ITIwUz7b9q9mx+9Nfzq5r2zv3APy+vNfsd+E5/D1Vxnme4azre7/fYvYDyDuJdAjlo91xvpMWuMrs/adY/FQbQfNGu83YX+UlV6+wFdc3j+r+8ffTiK6n7f+orqd52v636norw/eR+N9nxMf7OXWt7Vori2udiqj3puwRbQ1Q9go9eIuWlcwvXRrXXtjcZ5qnY7QVuubxqGKLzup6q7o5AurYr/eDeNy2huz/elUC/X2mPbSd44ad9Zni02QsF8ZpAxfCMuyT57RPYZGayoyN9N5XX3RQcS9y9hEvHajGupjsJu7JOzso9zrq5RmwSN2fbbSl3O9OI33vrer6K6b3P/ca53YZ3/9aV5d9KpiGecMqLXUbbqG6b5ovndg29/VyzzvWZe9ypTfel0wquOYW6HbMfKUzk7krAb0n8A+IZJXMH7bLqB/K+HX5W4+bv0fGTtp5JVjPu3HTwOi6uJ2uHSVd08PPVlDOOeYWJxvyWYphj8GjupxTt0fkvb2nW+rXVfYS7AI3ZBPWQY68x3Qx5v2Fs547/fX3vo7qno6+DP49DpG55+JWB2delHM+bX+fRXDN5R267rqmHv9jymvoG/OPDk9vdb2Fz5SP0mFXrnM37XHWU0GM7WztTpopn6n8eJK6/i/iEHTnM93/11nptPOlks8G6Lym2ngqv93ryG/bJL+F/74UUXktzrEDrQfrvBaznCKcMhbGXd/Sdtf3u/KVrm+Vj41ez3u53a4Z7LXng9oVQNmpOPba87jR8D0BcDuyH1jCu2RcdHhL0K30Dq+slh9fmCsHx79efuXghq+XXxzHevnhNMoYHx3nInsM8WDjPhU6kdR7Nyt2fKsakUa4bUyj5AnR4b0Q3Z2e4dWJFFeYdyaQRjsbkUaLsupPo3D5vHuCeV+N6sGN21ejuhHp47WvxraJ5r0=
*/