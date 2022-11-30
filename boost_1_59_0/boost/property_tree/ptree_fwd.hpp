// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_PTREE_FWD_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <boost/throw_exception.hpp>
#include <functional>           // for std::less
#include <memory>               // for std::allocator
#include <string>

namespace boost { namespace property_tree
{
    namespace detail {
        template <typename T> struct less_nocase;
    }

    // Classes

    template < class Key, class Data, class KeyCompare = std::less<Key> >
    class basic_ptree;

    template <typename T>
    struct id_translator;

    template <typename String, typename Translator>
    class string_path;

    // Texas-style concepts for documentation only.
#if 0
    concept PropertyTreePath<class Path> {
        // The key type for which this path works.
        typename key_type;
        // Return the key that the first segment of the path names.
        // Split the head off the state.
        key_type Path::reduce();

        // Return true if the path is empty.
        bool Path::empty() const;

        // Return true if the path contains a single element.
        bool Path::single() const;

        // Dump as a std::string, for exception messages.
        std::string Path::dump() const;
    }
    concept PropertyTreeKey<class Key> {
        PropertyTreePath path;
        requires SameType<Key, PropertyTreePath<path>::key_type>;
    }
    concept PropertyTreeTranslator<class Tr> {
        typename internal_type;
        typename external_type;

        boost::optional<external_type> Tr::get_value(internal_type);
        boost::optional<internal_type> Tr::put_value(external_type);
    }
#endif
    /// If you want to use a custom key type, specialize this struct for it
    /// and give it a 'type' typedef that specifies your path type. The path
    /// type must conform to the Path concept described in the documentation.
    /// This is already specialized for std::basic_string.
    template <typename Key>
    struct path_of;

    /// Specialize this struct to specify a default translator between the data
    /// in a tree whose data_type is Internal, and the external data_type
    /// specified in a get_value, get, put_value or put operation.
    /// This is already specialized for Internal being std::basic_string.
    template <typename Internal, typename External>
    struct translator_between;

    class ptree_error;
    class ptree_bad_data;
    class ptree_bad_path;

    // Typedefs

    /** Implements a path using a std::string as the key. */
    typedef string_path<std::string, id_translator<std::string> > path;

    /**
     * A property tree with std::string for key and data, and default
     * comparison.
     */
    typedef basic_ptree<std::string, std::string> ptree;

    /**
     * A property tree with std::string for key and data, and case-insensitive
     * comparison.
     */
    typedef basic_ptree<std::string, std::string,
                        detail::less_nocase<std::string> >
        iptree;

#ifndef BOOST_NO_STD_WSTRING
    /** Implements a path using a std::wstring as the key. */
    typedef string_path<std::wstring, id_translator<std::wstring> > wpath;

    /**
     * A property tree with std::wstring for key and data, and default
     * comparison.
     * @note The type only exists if the platform supports @c wchar_t.
     */
    typedef basic_ptree<std::wstring, std::wstring> wptree;

    /**
     * A property tree with std::wstring for key and data, and case-insensitive
     * comparison.
     * @note The type only exists if the platform supports @c wchar_t.
     */
    typedef basic_ptree<std::wstring, std::wstring,
                        detail::less_nocase<std::wstring> >
        wiptree;
#endif

    // Free functions

    /**
     * Swap two property tree instances.
     */
    template<class K, class D, class C>
    void swap(basic_ptree<K, D, C> &pt1,
              basic_ptree<K, D, C> &pt2);

} }


#if !defined(BOOST_PROPERTY_TREE_DOXYGEN_INVOKED)
    // Throwing macro to avoid no return warnings portably
#   define BOOST_PROPERTY_TREE_THROW(e) BOOST_THROW_EXCEPTION(e)
#endif

#endif

/* ptree_fwd.hpp
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
*/