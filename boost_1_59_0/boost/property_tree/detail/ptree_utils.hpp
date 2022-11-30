// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_PTREE_UTILS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_PTREE_UTILS_HPP_INCLUDED

#include <boost/limits.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/and.hpp>
#include <string>
#include <algorithm>
#include <locale>

namespace boost { namespace property_tree { namespace detail
{

    template<class T>
    struct less_nocase
    {
        typedef typename T::value_type Ch;
        std::locale m_locale;
        inline bool operator()(Ch c1, Ch c2) const
        {
            return std::toupper(c1, m_locale) < std::toupper(c2, m_locale);
        }
        inline bool operator()(const T &t1, const T &t2) const
        {
            return std::lexicographical_compare(t1.begin(), t1.end(),
                                                t2.begin(), t2.end(), *this);
        }
    };

    template <typename Ch>
    struct is_character : public boost::false_type {};
    template <>
    struct is_character<char> : public boost::true_type {};
    template <>
    struct is_character<wchar_t> : public boost::true_type {};


    BOOST_MPL_HAS_XXX_TRAIT_DEF(internal_type)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(external_type)
    template <typename T>
    struct is_translator : public boost::mpl::and_<
        has_internal_type<T>, has_external_type<T> > {};



    // Naively convert narrow string to another character type
    template<typename Str>
    Str widen(const char *text)
    {
        Str result;
        while (*text)
        {
            result += typename Str::value_type(*text);
            ++text;
        }
        return result;
    }

    // Naively convert string to narrow character type
    template<typename Str, typename char_type>
    Str narrow(const char_type *text)
    {
        Str result;
        while (*text)
        {
            if (*text < 0 || *text > (std::numeric_limits<char>::max)())
                result += '*';
            else
                result += typename Str::value_type(*text);
            ++text;
        }
        return result;
    }

    // Remove trailing and leading spaces
    template<class Str>
    Str trim(const Str &s, const std::locale &loc = std::locale())
    {
        typename Str::const_iterator first = s.begin();
        typename Str::const_iterator end = s.end();
        while (first != end && std::isspace(*first, loc))
            ++first;
        if (first == end)
            return Str();
        typename Str::const_iterator last = end;
        do --last; while (std::isspace(*last, loc));
        if (first != s.begin() || last + 1 != end)
            return Str(first, last + 1);
        else
            return s;
    }

} } }

#endif

/* ptree_utils.hpp
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
*/