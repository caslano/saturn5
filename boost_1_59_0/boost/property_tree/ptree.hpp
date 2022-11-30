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

#ifndef BOOST_PROPERTY_TREE_PTREE_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_PTREE_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/string_path.hpp>
#include <boost/property_tree/stream_translator.hpp>
#include <boost/property_tree/exceptions.hpp>
#include <boost/property_tree/detail/ptree_utils.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/throw_exception.hpp>
#include <boost/optional.hpp>
#include <utility>                  // for std::pair

namespace boost { namespace property_tree
{

    /**
     * Property tree main structure. A property tree is a hierarchical data
     * structure which has one element of type @p Data in each node, as well
     * as an ordered sequence of sub-nodes, which are additionally identified
     * by a non-unique key of type @p Key.
     *
     * Key equivalency is defined by @p KeyCompare, a predicate defining a
     * strict weak ordering.
     *
     * Property tree defines a Container-like interface to the (key-node) pairs
     * of its direct sub-nodes. The iterators are bidirectional. The sequence
     * of nodes is held in insertion order, not key order.
     */
    template<class Key, class Data, class KeyCompare>
    class basic_ptree
    {
#if defined(BOOST_PROPERTY_TREE_DOXYGEN_INVOKED)
    public:
#endif
        // Internal types
        /**
         * Simpler way to refer to this basic_ptree\<C,K,P,A\> type.
         * Note that this is private, and made public only for doxygen.
         */
        typedef basic_ptree<Key, Data, KeyCompare> self_type;

    public:
        // Basic types
        typedef Key                                  key_type;
        typedef Data                                 data_type;
        typedef KeyCompare                           key_compare;

        // Container view types
        typedef std::pair<const Key, self_type>      value_type;
        typedef std::size_t                          size_type;

        // The problem with the iterators is that I can't make them complete
        // until the container is complete. Sucks. Especially for the reverses.
        class iterator;
        class const_iterator;
        class reverse_iterator;
        class const_reverse_iterator;

        // Associative view types
        class assoc_iterator;
        class const_assoc_iterator;

        // Property tree view types
        typedef typename path_of<Key>::type          path_type;


        // The big five

        /** Creates a node with no children and default-constructed data. */
        basic_ptree();
        /** Creates a node with no children and a copy of the given data. */
        explicit basic_ptree(const data_type &data);
        basic_ptree(const self_type &rhs);
        ~basic_ptree();
        /** Basic guarantee only. */
        self_type &operator =(const self_type &rhs);

        /** Swap with other tree. Only constant-time and nothrow if the
         * data type's swap is.
         */
        void swap(self_type &rhs);

        // Container view functions

        /** The number of direct children of this node. */
        size_type size() const;
        size_type max_size() const;
        /** Whether there are any direct children. */
        bool empty() const;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        value_type &front();
        const value_type &front() const;
        value_type &back();
        const value_type &back() const;

        /** Insert a copy of the given tree with its key just before the given
         * position in this node. This operation invalidates no iterators.
         * @return An iterator to the newly created child.
         */
        iterator insert(iterator where, const value_type &value);

        /** Range insert. Equivalent to:
         * @code
         * for(; first != last; ++first) insert(where, *first);
         * @endcode
         */
        template<class It> void insert(iterator where, It first, It last);

        /** Erase the child pointed at by the iterator. This operation
         * invalidates the given iterator, as well as its equivalent
         * assoc_iterator.
         * @return A valid iterator pointing to the element after the erased.
         */
        iterator erase(iterator where);

        /** Range erase. Equivalent to:
         * @code
         * while(first != last;) first = erase(first);
         * @endcode
         */
        iterator erase(iterator first, iterator last);

        /** Equivalent to insert(begin(), value). */
        iterator push_front(const value_type &value);

        /** Equivalent to insert(end(), value). */
        iterator push_back(const value_type &value);

        /** Equivalent to erase(begin()). */
        void pop_front();

        /** Equivalent to erase(boost::prior(end())). */
        void pop_back();

        /** Reverses the order of direct children in the property tree. */
        void reverse();

        /** Sorts the direct children of this node according to the predicate.
         * The predicate is passed the whole pair of key and child.
         */
        template<class Compare> void sort(Compare comp);

        /** Sorts the direct children of this node according to key order. */
        void sort();

        // Equality

        /** Two property trees are the same if they have the same data, the keys
         * and order of their children are the same, and the children compare
         * equal, recursively.
         */
        bool operator ==(const self_type &rhs) const;
        bool operator !=(const self_type &rhs) const;

        // Associative view

        /** Returns an iterator to the first child, in key order. */
        assoc_iterator ordered_begin();
        /** Returns an iterator to the first child, in key order. */
        const_assoc_iterator ordered_begin() const;

        /** Returns the not-found iterator. Equivalent to end() in a real
         * associative container.
         */
        assoc_iterator not_found();
        /** Returns the not-found iterator. Equivalent to end() in a real
         * associative container.
         */
        const_assoc_iterator not_found() const;

        /** Find a child with the given key, or not_found() if there is none.
         * There is no guarantee about which child is returned if multiple have
         * the same key.
         */
        assoc_iterator find(const key_type &key);

        /** Find a child with the given key, or not_found() if there is none.
         * There is no guarantee about which child is returned if multiple have
         * the same key.
         */
        const_assoc_iterator find(const key_type &key) const;

        /** Find the range of children that have the given key. */
        std::pair<assoc_iterator, assoc_iterator>
            equal_range(const key_type &key);

        /** Find the range of children that have the given key. */
        std::pair<const_assoc_iterator, const_assoc_iterator>
            equal_range(const key_type &key) const;

        /** Count the number of direct children with the given key. */
        size_type count(const key_type &key) const;

        /** Erase all direct children with the given key and return the count.
         */
        size_type erase(const key_type &key);

        /** Get the iterator that points to the same element as the argument.
         * @note A valid assoc_iterator range (a, b) does not imply that
         *       (to_iterator(a), to_iterator(b)) is a valid range.
         */
        iterator to_iterator(assoc_iterator it);

        /** Get the iterator that points to the same element as the argument.
         * @note A valid const_assoc_iterator range (a, b) does not imply that
         *       (to_iterator(a), to_iterator(b)) is a valid range.
         */
        const_iterator to_iterator(const_assoc_iterator it) const;

        // Property tree view

        /** Reference to the actual data in this node. */
        data_type &data();

        /** Reference to the actual data in this node. */
        const data_type &data() const;

        /** Clear this tree completely, of both data and children. */
        void clear();

        /** Get the child at the given path, or throw @c ptree_bad_path.
         * @note Depending on the path, the result at each level may not be
         *       completely deterministic, i.e. if the same key appears multiple
         *       times, which child is chosen is not specified. This can lead
         *       to the path not being resolved even though there is a
         *       descendant with this path. Example:
         * @code
         *   a -> b -> c
         *     -> b
         * @endcode
         *       The path "a.b.c" will succeed if the resolution of "b" chooses
         *       the first such node, but fail if it chooses the second.
         */
        self_type &get_child(const path_type &path);

        /** Get the child at the given path, or throw @c ptree_bad_path. */
        const self_type &get_child(const path_type &path) const;

        /** Get the child at the given path, or return @p default_value. */
        self_type &get_child(const path_type &path, self_type &default_value);

        /** Get the child at the given path, or return @p default_value. */
        const self_type &get_child(const path_type &path,
                                   const self_type &default_value) const;

        /** Get the child at the given path, or return boost::null. */
        optional<self_type &> get_child_optional(const path_type &path);

        /** Get the child at the given path, or return boost::null. */
        optional<const self_type &>
          get_child_optional(const path_type &path) const;

        /** Set the node at the given path to the given value. Create any
         * missing parents. If the node at the path already exists, replace it.
         * @return A reference to the inserted subtree.
         * @note Because of the way paths work, it is not generally guaranteed
         *       that a node newly created can be accessed using the same path.
         * @note If the path could refer to multiple nodes, it is unspecified
         *       which one gets replaced.
         */
        self_type &put_child(const path_type &path, const self_type &value);

        /** Add the node at the given path. Create any missing parents. If there
         * already is a node at the path, add another one with the same key.
         * @param path Path to the child. The last fragment must not have an
         *             index.
         * @return A reference to the inserted subtree.
         * @note Because of the way paths work, it is not generally guaranteed
         *       that a node newly created can be accessed using the same path.
         */
        self_type &add_child(const path_type &path, const self_type &value);

        /** Take the value of this node and attempt to translate it to a
         * @c Type object using the supplied translator.
         * @throw ptree_bad_data if the conversion fails.
         */
        template<class Type, class Translator>
        typename boost::enable_if<detail::is_translator<Translator>, Type>::type
        get_value(Translator tr) const;

        /** Take the value of this node and attempt to translate it to a
         * @c Type object using the default translator.
         * @throw ptree_bad_data if the conversion fails.
         */
        template<class Type>
        Type get_value() const;

        /** Take the value of this node and attempt to translate it to a
         * @c Type object using the supplied translator. Return @p default_value
         * if this fails.
         */
        template<class Type, class Translator>
        Type get_value(const Type &default_value, Translator tr) const;

        /** Make get_value do the right thing for string literals. */
        template <class Ch, class Translator>
        typename boost::enable_if<
            detail::is_character<Ch>,
            std::basic_string<Ch>
        >::type
        get_value(const Ch *default_value, Translator tr) const;

        /** Take the value of this node and attempt to translate it to a
         * @c Type object using the default translator. Return @p default_value
         * if this fails.
         */
        template<class Type>
        typename boost::disable_if<detail::is_translator<Type>, Type>::type
        get_value(const Type &default_value) const;

        /** Make get_value do the right thing for string literals. */
        template <class Ch>
        typename boost::enable_if<
            detail::is_character<Ch>,
            std::basic_string<Ch>
        >::type
        get_value(const Ch *default_value) const;

        /** Take the value of this node and attempt to translate it to a
         * @c Type object using the supplied translator. Return boost::null if
         * this fails.
         */
        template<class Type, class Translator>
        optional<Type> get_value_optional(Translator tr) const;

        /** Take the value of this node and attempt to translate it to a
         * @c Type object using the default translator. Return boost::null if
         * this fails.
         */
        template<class Type>
        optional<Type> get_value_optional() const;

        /** Replace the value at this node with the given value, translated
         * to the tree's data type using the supplied translator.
         * @throw ptree_bad_data if the conversion fails.
        */
        template<class Type, class Translator>
        void put_value(const Type &value, Translator tr);

        /** Replace the value at this node with the given value, translated
         * to the tree's data type using the default translator.
         * @throw ptree_bad_data if the conversion fails.
        */
        template<class Type>
        void put_value(const Type &value);

        /** Shorthand for get_child(path).get_value(tr). */
        template<class Type, class Translator>
        typename boost::enable_if<detail::is_translator<Translator>, Type>::type
        get(const path_type &path, Translator tr) const;

        /** Shorthand for get_child(path).get_value\<Type\>(). */
        template<class Type>
        Type get(const path_type &path) const;

        /** Shorthand for get_child(path, empty_ptree())
         *                    .get_value(default_value, tr).
         * That is, return the translated value if possible, and the default
         * value if the node doesn't exist or conversion fails.
         */
        template<class Type, class Translator>
        Type get(const path_type &path,
                 const Type &default_value,
                 Translator tr) const;

        /** Make get do the right thing for string literals. */
        template <class Ch, class Translator>
        typename boost::enable_if<
            detail::is_character<Ch>,
            std::basic_string<Ch>
        >::type
        get(const path_type &path, const Ch *default_value, Translator tr)const;

        /** Shorthand for get_child(path, empty_ptree())
         *                    .get_value(default_value).
         * That is, return the translated value if possible, and the default
         * value if the node doesn't exist or conversion fails.
         */
        template<class Type>
        typename boost::disable_if<detail::is_translator<Type>, Type>::type
        get(const path_type &path, const Type &default_value) const;

        /** Make get do the right thing for string literals. */
        template <class Ch>
        typename boost::enable_if<
            detail::is_character<Ch>,
            std::basic_string<Ch>
        >::type
        get(const path_type &path, const Ch *default_value) const;

        /** Shorthand for:
         * @code
         * if(optional\<self_type&\> node = get_child_optional(path))
         *   return node->get_value_optional(tr);
         * return boost::null;
         * @endcode
         * That is, return the value if it exists and can be converted, or nil.
        */
        template<class Type, class Translator>
        optional<Type> get_optional(const path_type &path, Translator tr) const;

        /** Shorthand for:
         * @code
         * if(optional\<const self_type&\> node = get_child_optional(path))
         *   return node->get_value_optional();
         * return boost::null;
         * @endcode
         * That is, return the value if it exists and can be converted, or nil.
        */
        template<class Type>
        optional<Type> get_optional(const path_type &path) const;

        /** Set the value of the node at the given path to the supplied value,
         * translated to the tree's data type. If the node doesn't exist, it is
         * created, including all its missing parents.
         * @return The node that had its value changed.
         * @throw ptree_bad_data if the conversion fails.
        */
        template<class Type, class Translator>
        self_type &put(const path_type &path, const Type &value, Translator tr);

        /** Set the value of the node at the given path to the supplied value,
         * translated to the tree's data type. If the node doesn't exist, it is
         * created, including all its missing parents.
         * @return The node that had its value changed.
         * @throw ptree_bad_data if the conversion fails.
        */
        template<class Type>
        self_type &put(const path_type &path, const Type &value);

        /** If the node identified by the path does not exist, create it,
         * including all its missing parents.
         * If the node already exists, add a sibling with the same key.
         * Set the newly created node's value to the given paremeter,
         * translated with the supplied translator.
         * @param path Path to the child. The last fragment must not have an
         *             index.
         * @param value The value to add.
         * @param tr The translator to use.
         * @return The node that was added.
         * @throw ptree_bad_data if the conversion fails.
        */
        template<class Type, class Translator>
        self_type &add(const path_type &path,
                       const Type &value,
                       Translator tr);

        /** If the node identified by the path does not exist, create it,
         * including all its missing parents.
         * If the node already exists, add a sibling with the same key.
         * Set the newly created node's value to the given paremeter,
         * translated with the supplied translator.
         * @param path Path to the child. The last fragment must not have an
         *             index.
         * @param value The value to add.
         * @return The node that was added.
         * @throw ptree_bad_data if the conversion fails.
        */
        template<class Type>
        self_type &add(const path_type &path, const Type &value);

    private:
        // Hold the data of this node
        data_type m_data;
        // Hold the children - this is a void* because we can't complete the
        // container type within the class.
        void* m_children;

        // Getter tree-walk. Not const-safe! Gets the node the path refers to,
        // or null. Destroys p's value.
        self_type* walk_path(path_type& p) const;

        // Modifer tree-walk. Gets the parent of the node referred to by the
        // path, creating nodes as necessary. p is the path to the remaining
        // child.
        self_type& force_path(path_type& p);

        // This struct contains typedefs for the concrete types.
        struct subs;
        friend struct subs;
        friend class iterator;
        friend class const_iterator;
        friend class reverse_iterator;
        friend class const_reverse_iterator;
    };

}}

#include <boost/property_tree/detail/ptree_implementation.hpp>

#endif

/* ptree.hpp
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
*/