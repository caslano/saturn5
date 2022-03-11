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
GXLvU+C9EDcHmNLPEM+uj/zfW5fo+XpUSO59HM+xy71TzGdZcu99X0u59UR3Q8i9sY975N4FeH4+0KC/QcV7yPtHpXnk3v3PGl5yb+zTBnV8xqAxeNac3ga930+WOWMMvnF+f9n2+m50K/UC9+Edqn31xXuq21Eo6Kp9BUtAV7XfYonqdvQq4gs/hzbelPelP9OliP6/a1xis+RkYZi20iY3sYqX1ffn656+v6fwPcSrZCma714uu/ZolOCaeUUtwVxV04QGOcewx5Prbqni/ubinoHiaZb/vHDcz/J9T1DY+4nURfe8VZWaLqaGepy4Jt/7hLn3Te7rkb+te6WnFstLsu/uNYxtqNNNnjPI1sc0T0pM7Rg3Itbqa+zrNnytgH4G964fjTo/xqCm4zztoeKLN257qPGC//ZwYqysY20CytDbiKeP+ev0A0uK+G5v/SDesx6hyR3u3jvQO5rtqNXOkpGsDzQZ+cS81HsT5LgkryaGalpDj3A3chjCi0VY6gltN/V1eoeaMbLkqbsMjxwQavfrwiS7PVsRZ5tb6D5zG/8m23u+7NhWN5U1rwWv9b6Wj/TqoFn7CpqsM/yOo2y39GrH0XMrr6/5p/X4ZtX8k3u99zh6rezWVl4l/YlYdmut+Sdfu7X2+adGXxvCbm21NYZfu7UZq80xILAMPWQrx6LmEctfZTmyX5jY1ddXOfqbR1y4wbsc/yi/MFyOy7YYynlEu1+YFVuNS/qF4ZExTsxPxRWMsTzXfewbt3IfxGHUVUsP/N48TWM0A/2BbA+9Pmj1FfQGoDVQ0BuC1tBGV+k/vLxKxufDei/rvfcyn8OH9V5fuvVeX7r1Xjud02PZkbWnkw+7fdmVOWo9gg5Ip2p/wWz0cap9K1NX+eenuBzSdrqV+l/PovxV6xDH3i2m9Hvz5TZ1vr69yVDqo2/ZrF6HGJ+jlseqZKvzI26Leh9n8mpJ990fkGz1LYrDjf4mYJdBPQPleLfzpCH0T2ciXDnQRdJLn5qfG6LV0difHv9upw3An68+LlsVYkso0ooN26rxWD6x7wKV42B4fFxsYmqzlNhoORga37opvoZ6nuuYmd6FxV1iruOhYjK8ywy/ZIZnlXeJ7/Hoz3aITUgaJg024MhBvDSXiyZWcNH+lq4i5c9f27guq7+tH+RSyp9P3um67uXPP2J+dmUtF0WiHrVEHYgWe+PYI2K04PD5kLYw+Xq4rc9spqWIumXtepXz+/d/738+ZQi5xL5N+8Hrgi/d4aJ6CnmsNOI3VNBXoD5UVtBb13DRXQr6uXLgRRXrB/ubugrbaW1Ujka7C9P7gt6pVGF6DOif3VGYPgj0GVUK0+NBH/FgYXrZ+8tR62quItYt/OW/Wsc+EucuJhctbUfZrUJpWvWbIGe0c1F486SUBHP/be5uN2VpnvY8eU2pgvSEd0yOj0tNjU0x+WBjj7esa2/7Yu/jHlkPVPJ3OvgDVf+e0dOl7Gc39nAp+9kEPMcapxrlSfC41qq3pPO4ZtF5XCMbPQq0KJM+wKTzYdH5Oem2+O1Ba6+Ib9Gt+Kr9QK2Q/rKqfXY9/Zf3H7GPdZioO08JmzZcd+x7WU3fWEMT0MOLMDvKSo1N4N+H93pkHj7yv/bUi5OoR2f7uugiUDVa9s/Tc9X98yuAvX+elKvunzm+XF+JS0w1neJZNorDzTBXWZ50GZ/rpja3yLSNi3VR6AZP2tJwLTvYk+60iR79iQhHGRqF9F6Ovd7M2MsbVy5nXvMlvPNS48qfocf4t73eK9djvFb2ejm9f9vrvf7t9XK/MRP9xjNow+v7uUT7KYY+3F+/UWHQ1fcb92BsS2kX4sWPvt3LdUPwo1ci/6v6DT4f7RZCJdqHFNzDecTnZqi/DwAl4kLoJN6jDZb2rZ5AOejDQ0Q5cDjQtHkV1MdFN7UNoc7xITQuJYSqoEzY/nruQf/2ltkfhYrfmBTtf7xmDZf/sncl8FEUSz+EYNjpWVJIlsADBASUyyA8RESUkCCHiuQRgnI8SWJiCElIIIkcgtzIKQiCHCoIyqGA6MPriQ8UFY98IoeKn/IMIsgpp4iIn9+/pnd2Zje9uQOoTH6Vme3p6e7p6a6qrqqumjI6hNq640eq+Jh3QUdU69HzyQ6lnvrqJIv/qLAPafsk/3EswX878sW4RNp6tGmKm37/muLwipfH8dGi27so+qowuh73mg2S47oguRbHQCzpuP6j+D2pP9hRqnHtT67lHOrwkmtlo79Lax/3XbpD0gI/cS69YygGBLx3yBoPLyOPXU6diHHA/m++fkiOgzmZ/vHbX9X/TXH4In/jwNdO8ta00o8D/n4b8f3a4ptNGlL4POa5/2f/fhdrHvfOKv33853HvvEveb4tOCbnqoqOMN0aqFhnnkC5Krn2CowRlRz0kyHqdXj3dPU6fD7SUxT15qCPVH6Ibs+00TWbH5mbc6x1td2PzNrBVn67Hxl7frsfGc7vXat1lMe6mp9PMnLm9xEVa+x7Hxpg+nDNUujJrXuSfkcNzh5qj6GZeTyUgira1rE2fP0Z5nv4GAd9PKFwfH1kQsnn+0LU8UeY7xcLX4txpZ/vy8c6qCLKmTNWzu3Mk6FK/jANfa/yN7punHpetxhfAH8YGZ+VxL6Bcf0Z6gtw8wF82GV4zYPD6CTGS60lDpq3oGC5e/slJR9XJbH7Kk/5iL91TsNFko6Uh3yk7mzQa7wHy0c4r10+Yu/roshHDk1zeMlH5qJcu3zEbItdPnJjoCUf4faybMSUjyzD2Ryv/E6mP2G7fCQS3/+2pQ4v+YiZzy4f4bHD13zvXI1gmj/LYchHWF6ceca/vHjhbPX6iMtTzZdo9I/KT+tP0/PPF6ZHN6B//Plr8iWEnP4L+nisd7KRvn4u+kGR3mi6Wv67cV4B89RLn2d6JeV4DlkBvUFrsgwqJX0tsH6GNX5MacycvjHQ1PcD8qUbNKh756ieKQkJGYPl5nrrd1R8ZnYKkqWFaNBZy8/MNyvwjjk2ufBPoaSThVvuq2Hd2wDc0vV58Dg4D8X5DKD6cvAQKKNr5TBqh+u7XiRj/t2X4KTdi5yUPsRJybh+YBVwSpqTnsfvlyY6qTHGfXPAjQBzHhhyxmUOao/reYC3AVNR5g2YD/XnOan2FCdlve6gX58DP4N8eZPlnOCxmTPTSW2myzHa9AEn9Up00k2AiIVO2o/8C55zUl6izM82Tub8rJrkpDj8/malvNduvpPCn3ZSZeRdi+vfHg2hiMVOSkE7Rq5FG/DO3A7Oy3OL6+6ywEm9UecMnA8AFuF6ZI6TLqAMruuWZGnD9TLStwA+B/wAeCMdv4c5aQPKO7/ESTXdePcxtPl7wFeD5PtwXTwnKw2S9b6D92E4iH6sstJB5yc5PXObYQ/628RjK9xlMHROsnzBMkxD25YDNgJCUf+0yZKOMrRHm4YDdtxTkfbi/lOVpd53DOpln6sH3b+Xun+r9dOsl+bIJ3fjP0d96WNosjhGikr3ZffAz1FaumGUR3ru5Y+foirD96n8kXXkoXq2K/J0wf+73ede+crjOzFGejejNd0LLC8SOTq7o49YUXB8yzRLYt2fFddFxhfqaWCLhAArvqE1p2Oy47Nzsnim7/4llHJtc7btWVusduTnXamGDqZrUlqmj7V4a0cYnd0E/Peto1B9yn8PlB2/cGHT5alPGbit/PiF8tSn8P3y1qd8s9tBj33tzS8Upk85sNnhV5/yIMr7I+hTnsQ7vAoI/MRRZH3KrC8d1Ga3/M7+9Cl8z9SncH9VyZU8m68+5f5v5Tcy9SmrtjsMfUrTXY5C9SlN3sF7fuigRz+WbSlIn7L+XYeXPuWRnfKb+upTnN85qNUe2aYFwB8nMJf773XQSoBp9zwa12Vl98zPmrjlYtg9+9v/sGDQVYYOIu539f79H/c7lPuLumPsqPZL1P7CofRndhzfV+UPaOIONX/8QZ5Due/i9M6C7FKk9b8Zo9eIO9Mp5aGURCMMWMCNAS7q7+YR+53G3D9p0RQ+juK7fw960POog6afLnid2e2nsqMbf6V15oAfHH7XmQcPS/pZHuvMFNR7qdeZqaccnnXmOycwxtCm9YBrDjpoOOCrk/g+Zx2Ue8hBcwCT0B+C+wQQeMRBsYB+uN8DY6/rcYch66hR0aVcd3Iclno+6ZxvxFH1fN6AdNV+wW+OOZT7nM4iXbU+bnDC//p4vCL/loNqOe5/DqrlvufRh6p9ii2P+8cLZjygGEOeKqNo8NFJk/x+XIBmjHtj/098grF5Ni7IRUGNJa5Ydo1GrcOtNeNsPNdrYBCtGBVU6D7E3GlBRcITW1GWL574EWnFxRMFyTkXpwWVSs7pD0+MeSRIKedM31tyPFEDz25GH/cFNJkURPtTguhsDfBFNTVKHx5EI8cG0b6JQdRnBK7xXo8Ajrq/55CrNMOut60Io3H4tjvw/Xq8Lwr8TnHRWpG+U1nh8/KUR4c306hvUy3fd9qua6WSR6u+0/uB6F+HRtMqaDQGMG6ZoLtcGjXUNNIAL14L3ulVQdfOF9T4NfDuWwQNwXWtBYJ6LhR0bipw+TRBDVBG4nRBCwHHAQc2C6rzlqDhMwStA3w1U1CVxwS1wvk3/K6yXlDVuYLuBowHvA24F/dnAMYvAX+6QfKhe9G+1SibY51txb35N2p0Q5BGu1F/7CxBh6trdAva/PscQS2RJxIQA5iItl83T5BrhaBM/N5eRaNnNwq66QlBdQFPAp6ppNE3gMzlUm7S/nlBqwHnnsN9lB2PMpbh2QycBwIeAnyC3zMBo3H9BN8LB++PsrivKUjybXzdCP2SizJeeVzQrJcFLUbe2jdpdLa+RvMqyLjqD2LMNqqj0QyM8Q5Ie7G25ol9Jq2n7zX2aPKRh/7s6pA4TIVvI4WmxOfPRWlK+rKshaakI6cx11R4O/V2TUkX4jEmVXzho2iPKq7Hmnqakq7dE6Ip6dftjTUl/bq6qqakI01DNaXf8lVIV/GptTHPVHzwYow7lT/bTsBNKj3nOHw7Vfysjfi+Ptk9RwW3Zc91hqWQP/lPjCFz6REgoy9552GpVK+ATsbuii6G9CbW8HcudziqyjPzSv/oHInWis+syu9r793dOMcY0iFpFe5PbsZSsyjDH7sso+D8lo05583fOrYhTo1PSPPom0Ab7PGXuP319DD6uCfWUL85qfk8rUB6Me6Zi0svLgX/X3+MpBdlyf/b5UZ2/n9TH82QG0XEaIbciNNUcqOp/UHb+mlF5v9rTJC4chLK9eX/83pJfGvKjSY/JOUqJv9vlxvdjTa/BRAPawb//xPaG9BX8+L/t83RaO0jWj7+n9+by9icpHn4f5Ybpa50+LXD5ef9yY04jq8pNxJog+tBzSM3ykS7FuJdfOVG+9BnPQeB/qD/7nUIj9yI3/OVBzRDbvTYAPmuDKbcKHWWRmG9NUNutBb1vHi/RmMBO9GfjWJkO1slahTVT17PQFrXoeiDcRq9MEOjJTka/Wu4Rkcf12gu7u2YAjqK80doy3qcXwPkApqjXa2TZf1L52v08wiN9s7V6KUn0HbMxYqDMV4yNEqZirorCSJyKf0ab4nTlH6N0xdqSv+AjkQ13TsYq6ZvsRPV9OREspr+NJ6kKf2gV0O/+CJ2rndeHzX9rDRATSePTtOU66dI9N1Sn3TO33u0mu4tQr0quc0PaZgjino3Javp4XCMA5Ud65p+ajq5Z7xGuidFHqyPrPS0pty3+PQCNZ1cMsE/nVTRC7m/MAZ/TGs4njrTJNZvsC6nl5GLD5tPCEPlYPdHMwr04hXQgTXL8W3WWP5Bv1+Cb7sF9GGdRv+zXMqAdy3ViuwflNODVsq87B/hTZTH+aY9i7mC6wEvyHpYTjj1BTlnTP+gry/TaP+ywv2DjnlZ+gfNw/MsJ6y+SqM3nsecxXu8/5uMo2GXrZqwG/Wno/w7wGWy148c9868KLd2xzs+tCWR43zZAdKXB9uLcCw55nvsseoHuOOvRLv7nc1DzL02R6u56LlAOQ7u3Ap8ZNPh5uI7NELaSEBh9iHPbv3z0+3ykNup6Danl6W+p7j2Ib76HhXd3ntQnk253VegHdnBIp++p6j2IYXtnykq3Vbpe1R0uyj6Hra1LEzfwzSTbett+MyDy/Iwf6oBF6j8HCd/rnn5Od73UdHxmKnvMPGYObd8/Ryb+g47Hiupn2MT/yQY+MeOdxoZVpDRxm7DLEPzHOVeC0TXsHDLkxi7vnqBM+if4fvBCx8rHL9wP1/BL5cHfimKXqAs8EvjQFGm+KUs1gUlwS/2dYEKv9jXBb74hXURq2pJmqzimw8eU/PH235U89NhFdRx5AdhfKj0CHMOqfnOWkfU/G4a3j3Qh9/lOEl7/k/NT++5oOWLT8f+Av73d/98Z7Thp8zbf0F38J2xhve0RKQNNNLYjo79pmUY+aR3ND7s8Yx6Gp7UuhnyvCTDks77fmfgtXjDT1tHQ8uRjFTLa5uZN9vrGTM2eJJbRqjKY7VL2u75s+nzteUz5ZAqXyCybywbv8rOMBp7oAJNdgkDz9CtIX7x66BrLy5+LU85vR2/tiPhwa8bD5Tcr0azw5JOm/j1U+A+xn+zUe7g4xUoFxAL2H0UOL26lEukXSMo6YCso8oR4Pm6ch6b+xlGR0hgvzs16wnPPodHIiRw+tJaVvqoCAmcfjzESh8RIYHTV7qs9IcjJHD627b0kRESOH27Lf3xCAmc/mM1K31OhARObxEqlOv6zFDp41J1xDml/mg1xhjrj9a4f4c2EHRTA+kHoNPQjMxOGcMGMw+VYOOh7PeM/RI+aeY6ho9zKHdvQ0HTAIXZp3VpU3bj/djT0jbmUvETV/b7F98+zd9+/x8wdv4q+/274V0HAgqzT7vc9vv/rYUcD54xWsr9/vKoHcH2WtTIpeSb5qBOFZ/11nX+8V7/KmEU3EjQ6DaS/ha0T/OZUuCjP3I8kmron6LiI4ai7Ntq0ViUet+WGY/khnbCiBXT+HqXUn58oaVQ6nEHXK+mky8gvb5PekFxT/c0EUr97qCmQhnvc3NT/+PxDYzHNqhnF8Za7K3CI4/YdrOg/XjuMO79hHsNwgVprQU52kr9e1HkETPDZV5TrvoBfufeYs3TspRHxN4EnoH1jimDk1nUkNUzg11bBWxo7KKuAZZtuz1eMh+VQ8KoaXtBo3rL+cjt6tAd79pFUK0IQU8jffVtgq65T1DN/oL2dZfvG9JRUDzgbLKgObgfEYnnUU5PwON9JK/3GNJn3IVxFy2oYQd3+2JSsplf6dXERe3d9pF3Zol8cpBeaNebaYJG4l5hcpDoESXHE8y31BosisWnlyffcinkIHb7SJNv4fO9Q+S3Nvu6KHxLaeUgKvvIXUPkPCoL+0ium+8lPCw8cpCJQ3GNMRA2VtBijLfrcJ01WtBJnJtkCFoJyAHo6YKOZAtKRXpNtGnmMEEjhgOnIX0Yfo9C2S1HSflE1+ZyXeNP3+fPjlKF14JQh0re0BrtVskn3hqixpsts/zjQXMNba7TrZ13XnqpmBFZ2UnpNu3UGszTxXjvwEmyX038GTwRfYe0m3Eujl5qwyRL/5M20Rt/cr7y1kv1RZ2zJwtDL9XjUastdjD1Uh69kduOs2G4y9BfqvYVB1AYDdtbgeqcCvHYcRbVX9z9h0OU+OzaQyH0OdrYYYqgD3C9FefrAN8i/2yS68nRrwqa+A7wK37XnSpo02ZRqH0i22+VBp9ernIPOz7NWypKLPfwh0+bniYDjq4X9NQmYdgnnporDH6r07/l/Utpn2i2z7RP5OvTOJv2ifweRbFP5Od87RPvmy3o3wB/9omqecTA9om8VmT7xC9Qt2mfyGDifJV9Iu+dXtXSpbSbSFsplHYEo55Wr1eqrFbLfzc+I5TrnjdfFEo574B1ary7D21X8cnN0Vcq+7//og9U9ny98F4qO4WXXvOP10+48cDdWyR/p97zyfsmpc9j04qOj/x5vXeYdjR08N0MW7iCn7Ns5grLZ9XQzfjvrxbVs9LC0MzDZ3skBffezyQpGdv1dxett+Fqu47fRu+yonKysjPSU0YmdUqJT8tIDriA55ZWtvkEfdd6rn1V2dfx2wRNrhZCU9y/T30oDF/Pa7uFUFxrt97CfMh98Hj4ZasgaQ1pHWzHsgnPq+x3fvnA/3ffhbq/w/2ndhYu5+73Ufni+0Wo+2Lh+5boKxW+b9suJB++z9lZ9HW2Ct9nRIXQxo4hNA3917xLCIV9aq0NGUx51JPbgZNRl76wuideFfv0ubCgOrW1/c47W40S27iIz73ayHGSdrXkG14/IL9jcfiG0d8L5Xfcg/Q1zYjeA/QPJ7qAOjrsB/8LaAaI+0FQ4kFBfXA9E9DnkKBqh7EOw/VqwMuAidVku9ofKX67qu5Xt4v7myFynzD6PRf9Vc+nfybe7KJdqPsL1LsO8C7gBCD8mKBOhl4qGTxskhEZaASeG2aLHcT6HzOPjOvTyfAowfqm/qHyfU4dK/77rDqifp8ETgdoR6U8P59tV5Zl4hXd1kXZARKvNDuB9fQ6y2cvH2vQvveOg86e8Oaznfg9htMAxbWbMNNN+c7FspswLbVYX5eOv/gAuXPATI9GeibObENhxIc2cbDNIu4C+uP3k+Bxzgove7i1FXS64xTWtmetdcf8M6JY/RF7RvaJMecv0rrDtIdrcM7yi2HiHRPMdcfPZ3g8JaV3TkkzFmhL27mI40mbNCnAZclSol1htKqSTlWv0o1xvSNQp4xXA0l7LZCeB7z1EnDt64F04D+BtCNIpxsA11fUqT5gGOATQG6QhK0AbttinL8EvICyNgJOovyO71eg3biOiknKzk4ZnJwVk50xFK1re6vLmMPctgpOnXzlT0vRvlZoW7hTti+1ik5vArpX1ilY16lSiE4Ng1Eu8kx26PQy0qcCYgFtkdZA6NQO91/RdPoM93ugnA04t0BaDKh/Z1D/e8EPMI/TH/Uddcl5/nVVWV9B8zzwar3I67APSadWKJPXYRNwrgngdRjjCraFsr+z/YiKzUoayogB1xHVw6gy6vysGr5XmE7JOH/j0ul5pFW5WjfKmFFdtv/RGsVvvz881QRl/Yz6VuG8aCEfhzrI85tGnERPaHZTqYgjD+2oXVOn/s31QvWK2273bkdp+Is=
*/