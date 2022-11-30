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

    typedef std::list<node_type, typename boost::allocator_rebind<allocator_type, node_type>::type> object_list;

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
                            std::vector<iterator, typename boost::allocator_rebind<allocator_type, iterator>::type>,
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