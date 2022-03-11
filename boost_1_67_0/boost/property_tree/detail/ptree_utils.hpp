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