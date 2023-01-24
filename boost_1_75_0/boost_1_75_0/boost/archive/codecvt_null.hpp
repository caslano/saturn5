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
zp7vq32ksxIA14NNYExJ28rHYQTzqdfq9YE3hZrwlmI+EENVjE6eOq5atheNnj4OfpdTkMntM0FxPqZL5Q7I6lL5e8jwX+APm/EkkPchyhOM+zxCxgBEIQnj6yA/1VFu4sUz0YkxY0wVmORUtjZCfJL5BiIdjbdR22MdBWGB9mjoAm+hljtoHcuttU7t4Y6CngZ7B3ZhnV+Py7HH4wBR6dA5TxFUitV8Gal8Gmv8dZ1OUxHmX0Icr2ILAy9DwCasUIgVdJ3SG+N2yP5wMfZWGO5jCBam3dloKsIfubPRCGyEYUtYHyS2mIgdlIJcucxeBCmnG2/5ejAJWLsQWFGNPUXs5E3wWzRyAEYScUYgzNgfNprecZXSU+0he31MhBFIghTvh6Vjeyo5ZtwQ3uqBQTQs/ay0eHtOo7UVBstrunoa1+7NHnSVBd66cTkiNc1mTj8QbwsK8+RXX9sJCmFeJkrQ0q4N4hLwx7o2NF8CnoI3HVtq6RLwuZDG6UO/1fcPb6XCOfTllYwQJd+sWCgy9uf7MaJ9eCpYQofa4/3OkK8w9TLwh19sUKfwcS82x67qlgd7RMql6axVDu4qrhcb6Fj9NvjNbkBak8+xCOBV9vilkLGcs7JIYE12xFJRlN8WinZNCwjzXlQslxVD9OGimCCDoVR6rkwpQ25nG84GhXlPbRkjy4uX58iLF0UsiJDX5ixesihiZVbElJTJ
*/