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