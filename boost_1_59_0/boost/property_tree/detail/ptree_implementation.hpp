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
#ifndef BOOST_PROPERTY_TREE_DETAIL_PTREE_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_PTREE_IMPLEMENTATION_HPP_INCLUDED

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/assert.hpp>
#include <boost/utility/swap.hpp>
#include <memory>

#if (defined(BOOST_MSVC) && \
     (_MSC_FULL_VER >= 160000000 && _MSC_FULL_VER < 170000000)) || \
    (defined(BOOST_INTEL_WIN) && \
     defined(BOOST_DINKUMWARE_STDLIB))
#define BOOST_PROPERTY_TREE_PAIR_BUG
#endif

namespace boost { namespace property_tree
{
    template <class K, class D, class C>
    struct basic_ptree<K, D, C>::subs
    {
        struct by_name {};
        // The actual child container.
#if defined(BOOST_PROPERTY_TREE_PAIR_BUG)
        // MSVC 10 has moved std::pair's members to a base
        // class. Unfortunately this does break the interface.
        BOOST_STATIC_CONSTANT(unsigned,
            first_offset = offsetof(value_type, first));
#endif
        typedef multi_index_container<value_type,
            multi_index::indexed_by<
                multi_index::sequenced<>,
                multi_index::ordered_non_unique<multi_index::tag<by_name>,
#if defined(BOOST_PROPERTY_TREE_PAIR_BUG)
                    multi_index::member_offset<value_type, const key_type,
                                        first_offset>,
#else
                    multi_index::member<value_type, const key_type,
                                        &value_type::first>,
#endif
                    key_compare
                >
            >
        > base_container;

        // The by-name lookup index.
        typedef typename base_container::template index<by_name>::type
            by_name_index;

        // Access functions for getting to the children of a tree.
        static base_container& ch(self_type *s) {
            return *static_cast<base_container*>(s->m_children);
        }
        static const base_container& ch(const self_type *s) {
            return *static_cast<const base_container*>(s->m_children);
        }
        static by_name_index& assoc(self_type *s) {
            return ch(s).BOOST_NESTED_TEMPLATE get<by_name>();
        }
        static const by_name_index& assoc(const self_type *s) {
            return ch(s).BOOST_NESTED_TEMPLATE get<by_name>();
        }
    };
    template <class K, class D, class C>
    class basic_ptree<K, D, C>::iterator : public boost::iterator_adaptor<
        iterator, typename subs::base_container::iterator, value_type>
    {
        friend class boost::iterator_core_access;
        typedef boost::iterator_adaptor<
            iterator, typename subs::base_container::iterator, value_type>
            baset;
    public:
        typedef typename baset::reference reference;
        iterator() {}
        explicit iterator(typename iterator::base_type b)
            : iterator::iterator_adaptor_(b)
        {}
        reference dereference() const
        {
            // multi_index doesn't allow modification of its values, because
            // indexes could sort by anything, and modification screws that up.
            // However, we only sort by the key, and it's protected against
            // modification in the value_type, so this const_cast is safe.
            return const_cast<reference>(*this->base_reference());
        }
    };
    template <class K, class D, class C>
    class basic_ptree<K, D, C>::const_iterator : public boost::iterator_adaptor<
        const_iterator, typename subs::base_container::const_iterator>
    {
    public:
        const_iterator() {}
        explicit const_iterator(typename const_iterator::base_type b)
            : const_iterator::iterator_adaptor_(b)
        {}
        const_iterator(iterator b)
            : const_iterator::iterator_adaptor_(b.base())
        {}
    };
    template <class K, class D, class C>
    class basic_ptree<K, D, C>::reverse_iterator
        : public boost::reverse_iterator<iterator>
    {
    public:
        reverse_iterator() {}
        explicit reverse_iterator(iterator b)
            : boost::reverse_iterator<iterator>(b)
        {}
    };
    template <class K, class D, class C>
    class basic_ptree<K, D, C>::const_reverse_iterator
        : public boost::reverse_iterator<const_iterator>
    {
    public:
        const_reverse_iterator() {}
        explicit const_reverse_iterator(const_iterator b)
            : boost::reverse_iterator<const_iterator>(b)
        {}
        const_reverse_iterator(
            typename basic_ptree<K, D, C>::reverse_iterator b)
            : boost::reverse_iterator<const_iterator>(b)
        {}
    };
    template <class K, class D, class C>
    class basic_ptree<K, D, C>::assoc_iterator
        : public boost::iterator_adaptor<assoc_iterator,
                                         typename subs::by_name_index::iterator,
                                         value_type>
    {
        friend class boost::iterator_core_access;
        typedef boost::iterator_adaptor<assoc_iterator,
                                         typename subs::by_name_index::iterator,
                                         value_type>
            baset;
    public:
        typedef typename baset::reference reference;
        assoc_iterator() {}
        explicit assoc_iterator(typename assoc_iterator::base_type b)
            : assoc_iterator::iterator_adaptor_(b)
        {}
        reference dereference() const
        {
            return const_cast<reference>(*this->base_reference());
        }
    };
    template <class K, class D, class C>
    class basic_ptree<K, D, C>::const_assoc_iterator
        : public boost::iterator_adaptor<const_assoc_iterator,
                                   typename subs::by_name_index::const_iterator>
    {
    public:
        const_assoc_iterator() {}
        explicit const_assoc_iterator(
            typename const_assoc_iterator::base_type b)
            : const_assoc_iterator::iterator_adaptor_(b)
        {}
        const_assoc_iterator(assoc_iterator b)
            : const_assoc_iterator::iterator_adaptor_(b.base())
        {}
    };


    // Big five

    // Perhaps the children collection could be created on-demand only, to
    // reduce heap traffic. But that's a lot more work to implement.

    template<class K, class D, class C> inline
    basic_ptree<K, D, C>::basic_ptree()
        : m_children(new typename subs::base_container)
    {
    }

    template<class K, class D, class C> inline
    basic_ptree<K, D, C>::basic_ptree(const data_type &d)
        : m_data(d), m_children(new typename subs::base_container)
    {
    }

    template<class K, class D, class C> inline
    basic_ptree<K, D, C>::basic_ptree(const basic_ptree<K, D, C> &rhs)
        : m_data(rhs.m_data),
          m_children(new typename subs::base_container(subs::ch(&rhs)))
    {
    }

    template<class K, class D, class C>
    basic_ptree<K, D, C> &
        basic_ptree<K, D, C>::operator =(const basic_ptree<K, D, C> &rhs)
    {
        self_type(rhs).swap(*this);
        return *this;
    }

    template<class K, class D, class C>
    basic_ptree<K, D, C>::~basic_ptree()
    {
        delete &subs::ch(this);
    }

    template<class K, class D, class C> inline
    void basic_ptree<K, D, C>::swap(basic_ptree<K, D, C> &rhs)
    {
        boost::swap(m_data, rhs.m_data);
        // Void pointers, no ADL necessary
        std::swap(m_children, rhs.m_children);
    }

    // Container view

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::size_type
        basic_ptree<K, D, C>::size() const
    {
        return subs::ch(this).size();
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::size_type
        basic_ptree<K, D, C>::max_size() const
    {
        return subs::ch(this).max_size();
    }

    template<class K, class D, class C> inline
    bool basic_ptree<K, D, C>::empty() const
    {
        return subs::ch(this).empty();
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
        basic_ptree<K, D, C>::begin()
    {
        return iterator(subs::ch(this).begin());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_iterator
        basic_ptree<K, D, C>::begin() const
    {
        return const_iterator(subs::ch(this).begin());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
        basic_ptree<K, D, C>::end()
    {
        return iterator(subs::ch(this).end());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_iterator
        basic_ptree<K, D, C>::end() const
    {
        return const_iterator(subs::ch(this).end());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::reverse_iterator
        basic_ptree<K, D, C>::rbegin()
    {
        return reverse_iterator(this->end());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_reverse_iterator
        basic_ptree<K, D, C>::rbegin() const
    {
        return const_reverse_iterator(this->end());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::reverse_iterator
        basic_ptree<K, D, C>::rend()
    {
        return reverse_iterator(this->begin());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_reverse_iterator
        basic_ptree<K, D, C>::rend() const
    {
        return const_reverse_iterator(this->begin());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::value_type &
        basic_ptree<K, D, C>::front()
    {
        return const_cast<value_type&>(subs::ch(this).front());
    }

    template<class K, class D, class C> inline
    const typename basic_ptree<K, D, C>::value_type &
        basic_ptree<K, D, C>::front() const
    {
        return subs::ch(this).front();
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::value_type &
        basic_ptree<K, D, C>::back()
    {
        return const_cast<value_type&>(subs::ch(this).back());
    }

    template<class K, class D, class C> inline
    const typename basic_ptree<K, D, C>::value_type &
        basic_ptree<K, D, C>::back() const
    {
        return subs::ch(this).back();
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
    basic_ptree<K, D, C>::insert(iterator where, const value_type &value)
    {
        return iterator(subs::ch(this).insert(where.base(), value).first);
    }

    template<class K, class D, class C>
    template<class It> inline
    void basic_ptree<K, D, C>::insert(iterator where, It first, It last)
    {
        subs::ch(this).insert(where.base(), first, last);
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
        basic_ptree<K, D, C>::erase(iterator where)
    {
        return iterator(subs::ch(this).erase(where.base()));
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
        basic_ptree<K, D, C>::erase(iterator first, iterator last)
    {
        return iterator(subs::ch(this).erase(first.base(), last.base()));
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
        basic_ptree<K, D, C>::push_front(const value_type &value)
    {
        return iterator(subs::ch(this).push_front(value).first);
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
        basic_ptree<K, D, C>::push_back(const value_type &value)
    {
        return iterator(subs::ch(this).push_back(value).first);
    }

    template<class K, class D, class C> inline
    void basic_ptree<K, D, C>::pop_front()
    {
        subs::ch(this).pop_front();
    }

    template<class K, class D, class C> inline
    void basic_ptree<K, D, C>::pop_back()
    {
        subs::ch(this).pop_back();
    }

    template<class K, class D, class C> inline
    void basic_ptree<K, D, C>::reverse()
    {
        subs::ch(this).reverse();
    }

    namespace impl
    {
        struct by_first
        {
            template <typename P>
            bool operator ()(const P& lhs, const P& rhs) const {
              return lhs.first < rhs.first;
            }
        };

        template <typename C>
        struct equal_pred
        {
            template <typename P>
            bool operator ()(const P& lhs, const P& rhs) const {
                C c;
                return !c(lhs.first, rhs.first) &&
                       !c(rhs.first, lhs.first) &&
                       lhs.second == rhs.second;
            }
        };

        template <typename C, typename MI>
        bool equal_children(const MI& ch1, const MI& ch2) {
            // Assumes ch1.size() == ch2.size()
            return std::equal(ch1.begin(), ch1.end(),
                ch2.begin(), equal_pred<C>());
        }
    }

    template<class K, class D, class C> inline
    void basic_ptree<K, D, C>::sort()
    {
        sort(impl::by_first());
    }

    template<class K, class D, class C>
    template<class Compare> inline
    void basic_ptree<K, D, C>::sort(Compare comp)
    {
        subs::ch(this).sort(comp);
    }

    // Equality

    template<class K, class D, class C> inline
    bool basic_ptree<K, D, C>::operator ==(
                                  const basic_ptree<K, D, C> &rhs) const
    {
        // The size test is cheap, so add it as an optimization
        return size() == rhs.size() && data() == rhs.data() &&
            impl::equal_children<C>(subs::ch(this), subs::ch(&rhs));
    }

    template<class K, class D, class C> inline
    bool basic_ptree<K, D, C>::operator !=(
                                  const basic_ptree<K, D, C> &rhs) const
    {
        return !(*this == rhs);
    }

    // Associative view

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::assoc_iterator
        basic_ptree<K, D, C>::ordered_begin()
    {
        return assoc_iterator(subs::assoc(this).begin());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_assoc_iterator
        basic_ptree<K, D, C>::ordered_begin() const
    {
        return const_assoc_iterator(subs::assoc(this).begin());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::assoc_iterator
        basic_ptree<K, D, C>::not_found()
    {
        return assoc_iterator(subs::assoc(this).end());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_assoc_iterator
        basic_ptree<K, D, C>::not_found() const
    {
        return const_assoc_iterator(subs::assoc(this).end());
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::assoc_iterator
        basic_ptree<K, D, C>::find(const key_type &key)
    {
        return assoc_iterator(subs::assoc(this).find(key));
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_assoc_iterator
        basic_ptree<K, D, C>::find(const key_type &key) const
    {
        return const_assoc_iterator(subs::assoc(this).find(key));
    }

    template<class K, class D, class C> inline
    std::pair<
        typename basic_ptree<K, D, C>::assoc_iterator,
        typename basic_ptree<K, D, C>::assoc_iterator
    > basic_ptree<K, D, C>::equal_range(const key_type &key)
    {
        std::pair<typename subs::by_name_index::iterator,
                  typename subs::by_name_index::iterator> r(
            subs::assoc(this).equal_range(key));
        return std::pair<assoc_iterator, assoc_iterator>(
          assoc_iterator(r.first), assoc_iterator(r.second));
    }

    template<class K, class D, class C> inline
    std::pair<
        typename basic_ptree<K, D, C>::const_assoc_iterator,
        typename basic_ptree<K, D, C>::const_assoc_iterator
    > basic_ptree<K, D, C>::equal_range(const key_type &key) const
    {
        std::pair<typename subs::by_name_index::const_iterator,
                  typename subs::by_name_index::const_iterator> r(
            subs::assoc(this).equal_range(key));
        return std::pair<const_assoc_iterator, const_assoc_iterator>(
            const_assoc_iterator(r.first), const_assoc_iterator(r.second));
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::size_type
        basic_ptree<K, D, C>::count(const key_type &key) const
    {
        return subs::assoc(this).count(key);
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::size_type
        basic_ptree<K, D, C>::erase(const key_type &key)
    {
        return subs::assoc(this).erase(key);
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::iterator
        basic_ptree<K, D, C>::to_iterator(assoc_iterator ai)
    {
        return iterator(subs::ch(this).
            BOOST_NESTED_TEMPLATE project<0>(ai.base()));
    }

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::const_iterator
        basic_ptree<K, D, C>::to_iterator(const_assoc_iterator ai) const
    {
        return const_iterator(subs::ch(this).
            BOOST_NESTED_TEMPLATE project<0>(ai.base()));
    }

    // Property tree view

    template<class K, class D, class C> inline
    typename basic_ptree<K, D, C>::data_type &
        basic_ptree<K, D, C>::data()
    {
        return m_data;
    }

    template<class K, class D, class C> inline
    const typename basic_ptree<K, D, C>::data_type &
        basic_ptree<K, D, C>::data() const
    {
        return m_data;
    }

    template<class K, class D, class C> inline
    void basic_ptree<K, D, C>::clear()
    {
        m_data = data_type();
        subs::ch(this).clear();
    }

    template<class K, class D, class C>
    basic_ptree<K, D, C> &
        basic_ptree<K, D, C>::get_child(const path_type &path)
    {
        path_type p(path);
        self_type *n = walk_path(p);
        if (!n) {
            BOOST_PROPERTY_TREE_THROW(ptree_bad_path("No such node", path));
        }
        return *n;
    }

    template<class K, class D, class C> inline
    const basic_ptree<K, D, C> &
        basic_ptree<K, D, C>::get_child(const path_type &path) const
    {
        return const_cast<self_type*>(this)->get_child(path);
    }

    template<class K, class D, class C> inline
    basic_ptree<K, D, C> &
        basic_ptree<K, D, C>::get_child(const path_type &path,
                                        self_type &default_value)
    {
        path_type p(path);
        self_type *n = walk_path(p);
        return n ? *n : default_value;
    }

    template<class K, class D, class C> inline
    const basic_ptree<K, D, C> &
        basic_ptree<K, D, C>::get_child(const path_type &path,
                                        const self_type &default_value) const
    {
        return const_cast<self_type*>(this)->get_child(path,
            const_cast<self_type&>(default_value));
    }


    template<class K, class D, class C>
    optional<basic_ptree<K, D, C> &>
        basic_ptree<K, D, C>::get_child_optional(const path_type &path)
    {
        path_type p(path);
        self_type *n = walk_path(p);
        if (!n) {
            return optional<self_type&>();
        }
        return *n;
    }

    template<class K, class D, class C>
    optional<const basic_ptree<K, D, C> &>
        basic_ptree<K, D, C>::get_child_optional(const path_type &path) const
    {
        path_type p(path);
        self_type *n = walk_path(p);
        if (!n) {
            return optional<const self_type&>();
        }
        return *n;
    }

    template<class K, class D, class C>
    basic_ptree<K, D, C> &
        basic_ptree<K, D, C>::put_child(const path_type &path,
                                        const self_type &value)
    {
        path_type p(path);
        self_type &parent = force_path(p);
        // Got the parent. Now get the correct child.
        key_type fragment = p.reduce();
        assoc_iterator el = parent.find(fragment);
        // If the new child exists, replace it.
        if(el != parent.not_found()) {
            return el->second = value;
        } else {
            return parent.push_back(value_type(fragment, value))->second;
        }
    }

    template<class K, class D, class C>
    basic_ptree<K, D, C> &
        basic_ptree<K, D, C>::add_child(const path_type &path,
                                        const self_type &value)
    {
        path_type p(path);
        self_type &parent = force_path(p);
        // Got the parent.
        key_type fragment = p.reduce();
        return parent.push_back(value_type(fragment, value))->second;
    }

    template<class K, class D, class C>
    template<class Type, class Translator>
    typename boost::enable_if<detail::is_translator<Translator>, Type>::type
    basic_ptree<K, D, C>::get_value(Translator tr) const
    {
        if(boost::optional<Type> o = get_value_optional<Type>(tr)) {
            return *o;
        }
        BOOST_PROPERTY_TREE_THROW(ptree_bad_data(
            std::string("conversion of data to type \"") +
            typeid(Type).name() + "\" failed", data()));
    }

    template<class K, class D, class C>
    template<class Type> inline
    Type basic_ptree<K, D, C>::get_value() const
    {
        return get_value<Type>(
            typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class C>
    template<class Type, class Translator> inline
    Type basic_ptree<K, D, C>::get_value(const Type &default_value,
                                         Translator tr) const
    {
        return get_value_optional<Type>(tr).get_value_or(default_value);
    }

    template<class K, class D, class C>
    template <class Ch, class Translator>
    typename boost::enable_if<
        detail::is_character<Ch>,
        std::basic_string<Ch>
    >::type
    basic_ptree<K, D, C>::get_value(const Ch *default_value, Translator tr)const
    {
        return get_value<std::basic_string<Ch>, Translator>(default_value, tr);
    }

    template<class K, class D, class C>
    template<class Type> inline
    typename boost::disable_if<detail::is_translator<Type>, Type>::type
    basic_ptree<K, D, C>::get_value(const Type &default_value) const
    {
        return get_value(default_value,
                         typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class C>
    template <class Ch>
    typename boost::enable_if<
        detail::is_character<Ch>,
        std::basic_string<Ch>
    >::type
    basic_ptree<K, D, C>::get_value(const Ch *default_value) const
    {
        return get_value< std::basic_string<Ch> >(default_value);
    }

    template<class K, class D, class C>
    template<class Type, class Translator> inline
    optional<Type> basic_ptree<K, D, C>::get_value_optional(
                                                Translator tr) const
    {
        return tr.get_value(data());
    }

    template<class K, class D, class C>
    template<class Type> inline
    optional<Type> basic_ptree<K, D, C>::get_value_optional() const
    {
        return get_value_optional<Type>(
            typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class C>
    template<class Type, class Translator> inline
    typename boost::enable_if<detail::is_translator<Translator>, Type>::type
    basic_ptree<K, D, C>::get(const path_type &path,
                              Translator tr) const
    {
        return get_child(path).BOOST_NESTED_TEMPLATE get_value<Type>(tr);
    }

    template<class K, class D, class C>
    template<class Type> inline
    Type basic_ptree<K, D, C>::get(const path_type &path) const
    {
        return get_child(path).BOOST_NESTED_TEMPLATE get_value<Type>();
    }

    template<class K, class D, class C>
    template<class Type, class Translator> inline
    Type basic_ptree<K, D, C>::get(const path_type &path,
                                   const Type &default_value,
                                   Translator tr) const
    {
        return get_optional<Type>(path, tr).get_value_or(default_value);
    }

    template<class K, class D, class C>
    template <class Ch, class Translator>
    typename boost::enable_if<
        detail::is_character<Ch>,
        std::basic_string<Ch>
    >::type
    basic_ptree<K, D, C>::get(
        const path_type &path, const Ch *default_value, Translator tr) const
    {
        return get<std::basic_string<Ch>, Translator>(path, default_value, tr);
    }

    template<class K, class D, class C>
    template<class Type> inline
    typename boost::disable_if<detail::is_translator<Type>, Type>::type
    basic_ptree<K, D, C>::get(const path_type &path,
                              const Type &default_value) const
    {
        return get_optional<Type>(path).get_value_or(default_value);
    }

    template<class K, class D, class C>
    template <class Ch>
    typename boost::enable_if<
        detail::is_character<Ch>,
        std::basic_string<Ch>
    >::type
    basic_ptree<K, D, C>::get(
        const path_type &path, const Ch *default_value) const
    {
        return get< std::basic_string<Ch> >(path, default_value);
    }

    template<class K, class D, class C>
    template<class Type, class Translator>
    optional<Type> basic_ptree<K, D, C>::get_optional(const path_type &path,
                                                         Translator tr) const
    {
        if (optional<const self_type&> child = get_child_optional(path))
            return child.get().
                BOOST_NESTED_TEMPLATE get_value_optional<Type>(tr);
        else
            return optional<Type>();
    }

    template<class K, class D, class C>
    template<class Type>
    optional<Type> basic_ptree<K, D, C>::get_optional(
                                                const path_type &path) const
    {
        if (optional<const self_type&> child = get_child_optional(path))
            return child.get().BOOST_NESTED_TEMPLATE get_value_optional<Type>();
        else
            return optional<Type>();
    }

    template<class K, class D, class C>
    template<class Type, class Translator>
    void basic_ptree<K, D, C>::put_value(const Type &value, Translator tr)
    {
        if(optional<data_type> o = tr.put_value(value)) {
            data() = *o;
        } else {
            BOOST_PROPERTY_TREE_THROW(ptree_bad_data(
                std::string("conversion of type \"") + typeid(Type).name() +
                "\" to data failed", boost::any()));
        }
    }

    template<class K, class D, class C>
    template<class Type> inline
    void basic_ptree<K, D, C>::put_value(const Type &value)
    {
        put_value(value, typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class C>
    template<class Type, typename Translator>
    basic_ptree<K, D, C> & basic_ptree<K, D, C>::put(
        const path_type &path, const Type &value, Translator tr)
    {
        if(optional<self_type &> child = get_child_optional(path)) {
            child.get().put_value(value, tr);
            return *child;
        } else {
            self_type &child2 = put_child(path, self_type());
            child2.put_value(value, tr);
            return child2;
        }
    }

    template<class K, class D, class C>
    template<class Type> inline
    basic_ptree<K, D, C> & basic_ptree<K, D, C>::put(
        const path_type &path, const Type &value)
    {
        return put(path, value,
                   typename translator_between<data_type, Type>::type());
    }

    template<class K, class D, class C>
    template<class Type, typename Translator> inline
    basic_ptree<K, D, C> & basic_ptree<K, D, C>::add(
        const path_type &path, const Type &value, Translator tr)
    {
        self_type &child = add_child(path, self_type());
        child.put_value(value, tr);
        return child;
    }

    template<class K, class D, class C>
    template<class Type> inline
    basic_ptree<K, D, C> & basic_ptree<K, D, C>::add(
        const path_type &path, const Type &value)
    {
        return add(path, value,
                   typename translator_between<data_type, Type>::type());
    }


    template<class K, class D, class C>
    basic_ptree<K, D, C> *
    basic_ptree<K, D, C>::walk_path(path_type &p) const
    {
        if(p.empty()) {
            // I'm the child we're looking for.
            return const_cast<basic_ptree*>(this);
        }
        // Recurse down the tree to find the path.
        key_type fragment = p.reduce();
        const_assoc_iterator el = find(fragment);
        if(el == not_found()) {
            // No such child.
            return 0;
        }
        // Not done yet, recurse.
        return el->second.walk_path(p);
    }

    template<class K, class D, class C>
    basic_ptree<K, D, C> & basic_ptree<K, D, C>::force_path(path_type &p)
    {
        BOOST_ASSERT(!p.empty() && "Empty path not allowed for put_child.");
        if(p.single()) {
            // I'm the parent we're looking for.
            return *this;
        }
        key_type fragment = p.reduce();
        assoc_iterator el = find(fragment);
        // If we've found an existing child, go down that path. Else
        // create a new one.
        self_type& child = el == not_found() ?
            push_back(value_type(fragment, self_type()))->second : el->second;
        return child.force_path(p);
    }

    // Free functions

    template<class K, class D, class C>
    inline void swap(basic_ptree<K, D, C> &pt1, basic_ptree<K, D, C> &pt2)
    {
        pt1.swap(pt2);
    }

} }

#if defined(BOOST_PROPERTY_TREE_PAIR_BUG)
#undef BOOST_PROPERTY_TREE_PAIR_BUG
#endif

#endif

/* ptree_implementation.hpp
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
*/