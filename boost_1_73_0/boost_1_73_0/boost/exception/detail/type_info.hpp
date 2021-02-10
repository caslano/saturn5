//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_C3E1741C754311DDB2834CCA55D89593
#define BOOST_EXCEPTION_C3E1741C754311DDB2834CCA55D89593

#include <boost/config.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/demangle.hpp>
#include <boost/current_function.hpp>
#include <string>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <class T>
    inline
    std::string
    tag_type_name()
        {
#ifdef BOOST_NO_TYPEID
        return BOOST_CURRENT_FUNCTION;
#else
        return core::demangle(typeid(T*).name());
#endif
        }

    template <class T>
    inline
    std::string
    type_name()
        {
#ifdef BOOST_NO_TYPEID
        return BOOST_CURRENT_FUNCTION;
#else
        return core::demangle(typeid(T).name());
#endif
        }

    namespace
    exception_detail
        {
        struct
        type_info_
            {
            core::typeinfo const * type_;

            explicit
            type_info_( core::typeinfo const & type ):
                type_(&type)
                {
                }

            friend
            bool
            operator<( type_info_ const & a, type_info_ const & b )
                {
                return 0!=(a.type_->before(*b.type_));
                }
            };
        }
    }

#define BOOST_EXCEPTION_STATIC_TYPEID(T) ::boost::exception_detail::type_info_(BOOST_CORE_TYPEID(T))

#ifndef BOOST_NO_RTTI
#define BOOST_EXCEPTION_DYNAMIC_TYPEID(x) ::boost::exception_detail::type_info_(typeid(x))
#endif

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* type_info.hpp
ZeeCkKrkMapEk9s2C1A3dCZxJwxSLlbihnQHiUSFKKRu5Q9B7jgvGwRazuIWpU3iqgNLcVwoLlqTkSTRaKlrdeO+sKfj0NiU6k7HY1isUYpTVue6vYQph97QGwdUC80Bx8RwFjg2LbGzKEMZymaMSkDDZu08G1fnq33tjx3DKlKjpWSzV7+/IKwohO4j+0TaJ+MO/GPA//lMhmce48OE3kanuzFbsVwOUimthSh6CPgmSjOKDgdhchmzPJNKnxzvH++/H+Fpn3pxzqq7Dx/373CCJ6omrWZdKhX+GL6sGs+Qocu25O1Icc5ZUZebo38NKxVNM+0v9mhsn43Go3Bm2PmKrVVjnzjhdOLCF3s8dYwJ16j6qknRibwrEGkzD/pFIQHHtEpZoXab3ZWpe+V6N27kNUtP15FWJiqy0UFMw8i7iK6da28yo2MSbg4rXBNRqDpNRSxoNzLOSqQyi3nLml7gOGCPAw818myy3TLoIfuxYdvWcOY7mxPjP1BLAwQKAAAACAAtZ0pSZn63u/4FAACCDQAANAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUFJPWFlfQ0FJTkZPLjNVVAUAAbZIJGCtVl1z0zgUffevuBMeSDuuQ4FlF5Zl
*/