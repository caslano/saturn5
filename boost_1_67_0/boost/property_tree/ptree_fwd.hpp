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