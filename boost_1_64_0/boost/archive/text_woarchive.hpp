#ifndef BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <ostream>
#include <cstddef> // size_t

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_warchive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_text_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_woarchive_impl :
    public basic_text_oprimitive<std::wostream>,
    public basic_text_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
        friend basic_text_oarchive<Archive>;
        friend save_access;
    #else
        friend class detail::interface_oarchive<Archive>;
        friend class basic_text_oarchive<Archive>;
        friend class save_access;
    #endif
#endif
    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::wostream>::save(t);
    }
    void save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_WARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_WARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_WARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_WARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    text_woarchive_impl(std::wostream & os, unsigned int flags) :
        basic_text_oprimitive<std::wostream>(
            os,
            0 != (flags & no_codecvt)
        ),
        basic_text_oarchive<Archive>(flags)
    {}
public:
    void save_binary(const void *address, std::size_t count){
        put(static_cast<wchar_t>('\n'));
        this->end_preamble();
        #if ! defined(__MWERKS__)
        this->basic_text_oprimitive<std::wostream>::save_binary(
        #else
        this->basic_text_oprimitive::save_binary(
        #endif
            address,
            count
        );
        put(static_cast<wchar_t>('\n'));
        this->delimiter = this->none;
    }

};

// we use the following because we can't use
// typedef text_oarchive_impl<text_oarchive_impl<...> > text_oarchive;

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from text_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE text_woarchive :
    public text_woarchive_impl<text_woarchive>
{
public:
    text_woarchive(std::wostream & os, unsigned int flags = 0) :
        text_woarchive_impl<text_woarchive>(os, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_woarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_TEXT_WOARCHIVE_HPP

/* text_woarchive.hpp
lKhueznKVd5y1SQsw0rqIz0VnPYfpVLuxmH8YAUno5gT5K1RqD4nD8ADttprqJXymdDmxc2FSayrX4ZKp9vpI5IQ0wRi1fMcnVFDuLdl0pYpwaqggsoitBR1Q2TKSxm0eRHFqTNrHzmP+r/FvfN9sLIPYHdJaK9jx97gL4QOyrNiZdEw4SVBXYi3rscBKS80IefJJoXdSao5adSVc+I5yqKPuVwx81OTFPViNf452WRuw9XB0suM4bg8VNgzWQ+Znid4SsU9VRkdWX/mf8mk7YtDpQfZiDTgQv/NU9hofCuvaBGfgy0oK5S0enJa59jWH+xIWlKIPKyo5T5FkE5KeW+SvFhF8k95wYp+thXbP7zwln4WUlikHvpZ7FXSrxPZf6ts1tF6YQjBF5oiWBP3ofl+nnjuWPkcIiwy8HJMbIEQdYLUkU18+GuxHmFkDJBVn+LbRhpbjxKkO41p74jnGPaW6tRVv9OivFU0qCZ0xJGgWYP6oRk4vxbnGTgk+BfopkCrOUTQOuMwfohC3AbxKe7hpkB7Vt6yH/2ihmn8oW/IknMLX4wGu6AmmBElHUxsEbNeYUdXJflNByn5n7paJb9NJK8yJ/9KbkvJXz/FyV/nlhVJx4aTDpNN80CBj+kDHUXqzSX1Z+bU23DqzaxT32X5gH/nyh/w7CQkbkDilCqV8lFhTxUyGsNSXQg1iGU9hLrowTGTSYT0wbUzEnaqHOlLnwQf1pqkg9C/y1eWmYWjyDqS+kQXpSQHU6gkCV2sSnJA3KePq+UxDkFRjOf5/Yv9fpAZ7tMRQlVMiGMysrzEty6lkK0Y7s4GC913F5SZtmwIlsIdUbyF7s4c44dTUXB6u3I1FH4qtmxwQaJ1QhwjCqG/hFMP0alSEsmSMWjXTUkZsxAquYs7fnkUSrkwk3ZIUUuPMCJQUud0Vm7rcTLdlrGz1W2dtTzgBnn4AX+9j/uBK1JpDAY953uiB+abR+gU+903Wh59RCEF4XAv0qwXYHskQEkCShJQkoBSbD/ff5N2/V/vgjDNyGKQrMEZs3KvcgWLck+PxluonFWoR3LzI7yruLerMkN6E2tJSPk2l8294CfaxP6W9pZVwf3xJnhcnC+GXQtwZbYOaRnMIbHpdUExnNNd9OVrkvzjbOnL31oi+vLm/s+HkkJDI5LawklFjKM+xJf5zf1lJJjH2TIK2TzdKEYhezCKQni44SIGiVHe7odNJiW0Hm6BdwKWjuO+cVvy7o2kQ1gkEt3qJKrzcyNqeIpRTQ2j9ptCVvLAfCezPHDGaJYHxCId6FI7KbXdYT/V9pcdPygPtHLi2r5mL8sDW0CbcQ1ffqSjuf+TxP2fju9LNd5OFqlmAK7PGAF72T65xPWW1F+aE5nCiYzp+EHJ66iay1AaafCcb/UQZys1VIA8MEEsFAkwLxRpi3hZ4k5qhGVbWVFZuO9EGpS5GJoVhsj+66brWO9faIIyzWI/U9ImlkRn2RnPQ9ExlO2gPODi++gBF8AhGxhgq/diEtgwR+Ut5ciJ6DS/va+h2NWrwH3LnB7klErtWyfZZP4guPCek4dZQfU3KQd4FSKvR3zLcqEYBBCLh3zEbUra677ukMOkh6HYsAQwFd3LWmJ9jD9tXbZCvP4yLmgnaG4Ctj4KqYYiovcHiQC3q2zY5klrhoTijMzP8Xoe0SAE4IsRLL0xaRd7585oeIpkrftz2LSbZ/f4KjOGMcHfS277k0XmLyj2Rd4giiHHJgOa2bhOmVqDTgc1EmPEWCUN08sRYpVaX/QE6YpLt8yDtpH56OG2u0F3uZUrcEZT1vW4oHyS9moJd7HO5Ahs8slFMOgAzWiki7yFFU2y0tO9v9E=
*/