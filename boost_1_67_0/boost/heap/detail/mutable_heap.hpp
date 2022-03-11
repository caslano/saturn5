// boost heap
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_DETAIL_MUTABLE_HEAP_HPP
#define BOOST_HEAP_DETAIL_MUTABLE_HEAP_HPP

/*! \file
 * INTERNAL ONLY
 */

#include <list>
#include <utility>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/heap/detail/ordered_adaptor_iterator.hpp>

namespace boost  {
namespace heap   {
namespace detail {

/* wrapper for a mutable heap container adaptors
 *
 * this wrapper introduces an additional indirection. the heap is not constructed from objects,
 * but instead from std::list iterators. this way, the mutability is achieved
 *
 */
template <typename PriorityQueueType>
class priority_queue_mutable_wrapper
{
public:
    typedef typename PriorityQueueType::value_type value_type;
    typedef typename PriorityQueueType::size_type size_type;
    typedef typename PriorityQueueType::value_compare value_compare;
    typedef typename PriorityQueueType::allocator_type allocator_type;

    typedef typename PriorityQueueType::reference reference;
    typedef typename PriorityQueueType::const_reference const_reference;
    typedef typename PriorityQueueType::pointer pointer;
    typedef typename PriorityQueueType::const_pointer const_pointer;
    static const bool is_stable = PriorityQueueType::is_stable;

private:
    typedef std::pair<value_type, size_type> node_type;

#ifdef BOOST_NO_CXX11_ALLOCATOR
    typedef std::list<node_type, typename allocator_type::template rebind<node_type>::other> object_list;
#else
    typedef std::list<node_type, typename std::allocator_traits<allocator_type>::template rebind_alloc<node_type>> object_list;
#endif

    typedef typename object_list::iterator list_iterator;
    typedef typename object_list::const_iterator const_list_iterator;

    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

    typedef typename PriorityQueueType::super_t::stability_counter_type stability_counter_type;

    stability_counter_type get_stability_count(void) const
    {
        return q_.get_stability_count();
    }

    void set_stability_count(stability_counter_type new_count)
    {
        q_.set_stability_count(new_count);
    }

    struct index_updater
    {
        template <typename It>
        static void run(It & it, size_type new_index)
        {
            q_type::get_value(it)->second = new_index;
        }
    };

public:
    struct handle_type
    {
        value_type & operator*() const
        {
            return iterator->first;
        }

        handle_type (void)
        {}

        handle_type(handle_type const & rhs):
            iterator(rhs.iterator)
        {}

        bool operator==(handle_type const & rhs) const
        {
            return iterator == rhs.iterator;
        }

        bool operator!=(handle_type const & rhs) const
        {
            return iterator != rhs.iterator;
        }

    private:
        explicit handle_type(list_iterator const & it):
            iterator(it)
        {}

        list_iterator iterator;

        friend class priority_queue_mutable_wrapper;
    };

private:
    struct indirect_cmp:
        public value_compare
    {
        indirect_cmp(value_compare const & cmp = value_compare()):
            value_compare(cmp)
        {}

        bool operator()(const_list_iterator const & lhs, const_list_iterator const & rhs) const
        {
            return value_compare::operator()(lhs->first, rhs->first);
        }
    };

    typedef typename PriorityQueueType::template rebind<list_iterator,
                                                        indirect_cmp,
                                                        allocator_type, index_updater >::other q_type;

protected:
    q_type q_;
    object_list objects;

protected:
    priority_queue_mutable_wrapper(value_compare const & cmp = value_compare()):
        q_(cmp)
    {}

    priority_queue_mutable_wrapper(priority_queue_mutable_wrapper const & rhs):
        q_(rhs.q_), objects(rhs.objects)
    {
        for (typename object_list::iterator it = objects.begin(); it != objects.end(); ++it)
            q_.push(it);
    }

    priority_queue_mutable_wrapper & operator=(priority_queue_mutable_wrapper const & rhs)
    {
        q_ = rhs.q_;
        objects = rhs.objects;
        q_.clear();
        for (typename object_list::iterator it = objects.begin(); it != objects.end(); ++it)
            q_.push(it);
        return *this;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    priority_queue_mutable_wrapper (priority_queue_mutable_wrapper && rhs):
        q_(std::move(rhs.q_))
    {
        /// FIXME: msvc seems to invalidate iterators when moving std::list
        std::swap(objects, rhs.objects);
    }

    priority_queue_mutable_wrapper & operator=(priority_queue_mutable_wrapper && rhs)
    {
        q_ = std::move(rhs.q_);
        objects.clear();
        std::swap(objects, rhs.objects);
        return *this;
    }
#endif


public:
    template <typename iterator_type>
    class iterator_base:
        public boost::iterator_adaptor<iterator_base<iterator_type>,
                                       iterator_type,
                                       value_type const,
                                       boost::bidirectional_traversal_tag>
    {
        typedef boost::iterator_adaptor<iterator_base<iterator_type>,
                                       iterator_type,
                                       value_type const,
                                       boost::bidirectional_traversal_tag> super_t;

        friend class boost::iterator_core_access;
        friend class priority_queue_mutable_wrapper;

        iterator_base(void):
            super_t(0)
        {}

        template <typename T>
        explicit iterator_base(T const & it):
            super_t(it)
        {}

        value_type const & dereference() const
        {
            return super_t::base()->first;
        }

        iterator_type get_list_iterator() const
        {
            return super_t::base_reference();
        }
    };

    typedef iterator_base<list_iterator> iterator;
    typedef iterator_base<const_list_iterator> const_iterator;

    typedef typename object_list::difference_type difference_type;

    class ordered_iterator:
        public boost::iterator_adaptor<ordered_iterator,
                                       const_list_iterator,
                                       value_type const,
                                       boost::forward_traversal_tag
                                      >,
        q_type::ordered_iterator_dispatcher
    {
        typedef boost::iterator_adaptor<ordered_iterator,
                                        const_list_iterator,
                                        value_type const,
                                        boost::forward_traversal_tag
                                      > adaptor_type;

        typedef const_list_iterator iterator;
        typedef typename q_type::ordered_iterator_dispatcher ordered_iterator_dispatcher;

        friend class boost::iterator_core_access;

    public:
        ordered_iterator(void):
            adaptor_type(0), unvisited_nodes(indirect_cmp()), q_(NULL)
        {}

        ordered_iterator(const priority_queue_mutable_wrapper * q, indirect_cmp const & cmp):
            adaptor_type(0), unvisited_nodes(cmp), q_(q)
        {}

        ordered_iterator(const_list_iterator it, const priority_queue_mutable_wrapper * q, indirect_cmp const & cmp):
            adaptor_type(it), unvisited_nodes(cmp), q_(q)
        {
            if (it != q->objects.end())
                discover_nodes(it);
        }

        bool operator!=(ordered_iterator const & rhs) const
        {
            return adaptor_type::base() != rhs.base();
        }

        bool operator==(ordered_iterator const & rhs) const
        {
            return !operator!=(rhs);
        }

    private:
        void increment(void)
        {
            if (unvisited_nodes.empty())
                adaptor_type::base_reference() = q_->objects.end();
            else {
                iterator next = unvisited_nodes.top();
                unvisited_nodes.pop();
                discover_nodes(next);
                adaptor_type::base_reference() = next;
            }
        }

        value_type const & dereference() const
        {
            return adaptor_type::base()->first;
        }

        void discover_nodes(iterator current)
        {
            size_type current_index = current->second;
            const q_type * q = &(q_->q_);

            if (ordered_iterator_dispatcher::is_leaf(q, current_index))
                return;

            std::pair<size_type, size_type> child_range = ordered_iterator_dispatcher::get_child_nodes(q, current_index);

            for (size_type i = child_range.first; i <= child_range.second; ++i) {
                typename q_type::internal_type const & internal_value_at_index = ordered_iterator_dispatcher::get_internal_value(q, i);
                typename q_type::value_type const & value_at_index = q_->q_.get_value(internal_value_at_index);

                unvisited_nodes.push(value_at_index);
            }
        }

        std::priority_queue<iterator,
#ifdef BOOST_NO_CXX11_ALLOCATOR
                            std::vector<iterator, typename allocator_type::template rebind<iterator>::other >,
#else
                            std::vector<iterator, typename std::allocator_traits<allocator_type>::template rebind_alloc<iterator> >,
#endif
                            indirect_cmp
                           > unvisited_nodes;
        const priority_queue_mutable_wrapper * q_;
    };

    bool empty(void) const
    {
        return q_.empty();
    }

    size_type size(void) const
    {
        return q_.size();
    }

    size_type max_size(void) const
    {
        return objects.max_size();
    }

    void clear(void)
    {
        q_.clear();
        objects.clear();
    }

    allocator_type get_allocator(void) const
    {
        return q_.get_allocator();
    }

    void swap(priority_queue_mutable_wrapper & rhs)
    {
        objects.swap(rhs.objects);
        q_.swap(rhs.q_);
    }

    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());
        return q_.top()->first;
    }

    handle_type push(value_type const & v)
    {
        objects.push_front(std::make_pair(v, 0));
        list_iterator ret = objects.begin();
        q_.push(ret);
        return handle_type(ret);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    handle_type emplace(Args&&... args)
    {
        objects.push_front(std::make_pair(std::forward<Args>(args)..., 0));
        list_iterator ret = objects.begin();
        q_.push(ret);
        return handle_type(ret);
    }
#endif

    void pop(void)
    {
        BOOST_ASSERT(!empty());
        list_iterator q_top = q_.top();
        q_.pop();
        objects.erase(q_top);
    }

    /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * */
    void update(handle_type handle, const_reference v)
    {
        list_iterator it = handle.iterator;
        value_type const & current_value = it->first;
        value_compare const & cmp = q_.value_comp();
        if (cmp(v, current_value))
            decrease(handle, v);
        else
            increase(handle, v);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void update(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.update(index);
    }

     /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be greater than the current one
     * */
    void increase(handle_type handle, const_reference v)
    {
        BOOST_ASSERT(!value_compare()(v, handle.iterator->first));
        handle.iterator->first = v;
        increase(handle);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be greater than the current one. If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void increase(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.increase(index);
    }

     /**
     * \b Effects: Assigns \c v to the element handled by \c handle & updates the priority queue.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be less than the current one
     * */
    void decrease(handle_type handle, const_reference v)
    {
        BOOST_ASSERT(!value_compare()(handle.iterator->first, v));
        handle.iterator->first = v;
        decrease(handle);
    }

    /**
     * \b Effects: Updates the heap after the element handled by \c handle has been changed.
     *
     * \b Complexity: Logarithmic.
     *
     * \b Note: The new value is expected to be less than the current one. If this is not called, after a handle has been updated, the behavior of the data structure is undefined!
     * */
    void decrease(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.decrease(index);
    }

    /**
     * \b Effects: Removes the element handled by \c handle from the priority_queue.
     *
     * \b Complexity: Logarithmic.
     * */
    void erase(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.erase(index);
        objects.erase(it);
    }

    const_iterator begin(void) const
    {
        return const_iterator(objects.begin());
    }

    const_iterator end(void) const
    {
        return const_iterator(objects.end());
    }

    iterator begin(void)
    {
        return iterator(objects.begin());
    }

    iterator end(void)
    {
        return iterator(objects.end());
    }

    ordered_iterator ordered_begin(void) const
    {
        if (!empty())
            return ordered_iterator(q_.top(), this, indirect_cmp(q_.value_comp()));
        else
            return ordered_end();
    }

    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(objects.end(), this, indirect_cmp(q_.value_comp()));
    }

    static handle_type s_handle_from_iterator(iterator const & it)
    {
        return handle_type(it.get_list_iterator());
    }

    value_compare const & value_comp(void) const
    {
        return q_.value_comp();
    }

    void reserve (size_type element_count)
    {
        q_.reserve(element_count);
    }
};


} /* namespace detail */
} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_DETAIL_MUTABLE_HEAP_HPP */

/* mutable_heap.hpp
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
*/