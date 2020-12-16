//-----------------------------------------------------------------------------
// boost detail/reference_content.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_REFERENCE_CONTENT_HPP
#define BOOST_DETAIL_REFERENCE_CONTENT_HPP

#include "boost/config.hpp"

#   include "boost/type_traits/integral_constant.hpp"
#   include "boost/type_traits/has_nothrow_copy.hpp"

namespace boost {

namespace detail {

struct void_type {};

///////////////////////////////////////////////////////////////////////////////
// (detail) class template reference_content
//
// Non-Assignable wrapper for references.
//
template <typename RefT>
class reference_content
{
private: // representation

    RefT content_;

public: // structors

    ~reference_content()
    {
    }

    reference_content(RefT r)
        : content_( r )
    {
    }

    reference_content(const reference_content& operand)
        : content_( operand.content_ )
    {
    }

private: // non-Assignable

    reference_content& operator=(const reference_content&);

public: // queries

    RefT get() const
    {
        return content_;
    }

};

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction make_reference_content
//
// Wraps with reference_content if specified type is reference.
//

template <typename T = void_type> struct make_reference_content;


template <typename T>
struct make_reference_content
{
    typedef T type;
};

template <typename T>
struct make_reference_content< T& >
{
    typedef reference_content<T&> type;
};


template <>
struct make_reference_content< void_type >
{
    template <typename T>
    struct apply
        : make_reference_content<T>
    {
    };

    typedef void_type type;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
// reference_content<T&> type traits specializations
//


template <typename T>
struct has_nothrow_copy<
      ::boost::detail::reference_content< T& >
    >
    : boost::true_type
{
};


} // namespace boost

#endif // BOOST_DETAIL_REFERENCE_CONTENT_HPP

/* reference_content.hpp
w1jvfTDcWsZj49J3/dyVdG3to1KDm3nL1OuHTbn5EPys9MI/74pLLzyl0Qv38RY78k9+6YfkWjUjtlTCFnuHO0ovlFGSBzhJV0ryQ3OSFZjkSkrCKzGOuRSNfPAuOsPdAcpBXLl45zuScrj80riUQx3jOOUdmuhmHD9YCDg+47JQDjqtcF7QQiyYIvMtkaqqDra7sPPtrhChxdYUEoZE2+TWpG6Artwvt6aUh4/YrclWPj3xTot8mm09e+CaUkprCvVkoZCz/NEvXYPOVD058GboydNS0PfmDOvx93gI1sdWnjBy5dbinSFI29HsZFF41hwqcQqXOMSuxCcWQIlb1MVWVUYWO2vVjWXzG0r4gP7e237XRqQyecgOuCR6pZFf+u73I66IgbzjKIAJKD+mQXXMG/fnyQwyZZFWiBx5t0FmqAcu1gkTZLY3QaC9CfztTeBrbwJP+xI4Adad/mKqFDcUo89bDOzZvUdjDcGHZJclqaJCqGVcymNqNo+pPftsxtQkEGiQ6iAbn8w9Pb9hLg+gBwCc+Co8gPZPjA6gHDmAyMrxVEwdvZq7OkQIcLLonh0NLGVDTxq77MirVonONzykc0IJ+4XCL5Ed9vfeBNg/KaXw1sxpmmhoqDX9kvyGW7mSz/+BK8lgxj8nWC/+YpFSUuRCVcNStua1z5rZZmXfEmunx3DfLj1Pcbaca6QnV/fd5f9dsvQj4WdrX7ekVrOv0y4OTJqdFqrkV1rVSUThYUJ8y+8UjX+dGlGFN5CI4mIgsvVJiLRbN5t5iOG99amYo9Ps0YOAvM7QSOLL8giPNMbjDDs8tlYQHq+6o3sTjTk6Thxr9EVLUMUbZwP1nwNsJEeMTI7lUT2SgJWpXllP5i5NAwOUyFtMuHiXnCBKykniRWMQI3fvmzbIDQHk4AK6DjZR0LaJmAYxmAYR9ik9KRRbLMj78UmMVDc7pO64HpBSLs+ZslJrQY66iaQCJMcZN5gtIJMi52sr3RkpxEMWzqKDNdBK2c17Ud2XO8If7Yhe2jrAUzsvckLb/urOGY9dcFgNGQ/Rz5ae6nKbRaCgqHY6+p7Aa/hFbyiqvVT12+/L5dH3MTnYU66nVCdxqmMp1TXmVA+oVBWYykrHF1P/I+MtFJT0sl1kvhYpeTSFNXRCIRRyGYXVe21QGKBQ+LvLMhVy7OZBjmUS6ES3rIA2bHlU8asiIGgu8Co2klH76nUb1JaUCdQil8uBL2v3FyBWUSwquMmjebZYy1JTyLy9EQ7aNnsk7lwshii/leUrp18ZR74SvlWTrzw7PqG9ZUCHv3W8M3lMZIlVnvLXae2Qpzy6xGr/d7cT+z9KW7rE7K91mFJaWIGZKGcNt9yNSgvD+FD3wWtShHDKGidKC+3SN/C03z+bKd6/JYZ8dfFiIV89nmsxGGrRECBGQthGIj2AJ4/rNXVEXxzV/5lFYuRBsFHQtbDJqTt2+9GKw0hW+if5/g6LgqzjY+ciNajyjAygY4QAq7fuDNmj6a8lkv/p+b2+TOV3tJ5fyONYIS6Gfznuqdjx1FNW+9cqRo09VP6kl629IOsr2ynJ/SyaPGjcBURNLN8w6FWNNOUmsg4awws1OVKHLzCp4WcadThTCG50Kjr0otR9pIfYq+/qK+zkXwT2bmRVu/TnXnrJQf1oDDfeYuacMdOqbACxT4EjE6AXKTAqMd6fIkY2aqVP7+sS4tD0L16VKjXHAroYCGwwHO0IQ+4eXbskxOeX80IQxr16AsP6APb1qyXsByq3lwFWQBAFWXOeD+sC74jeeeApxUcOrxh6wligx55nDmi9yqMay2Nh66m8ynhmQ66FkGtjitSQu5gKb4SEt6uE4cs=
*/