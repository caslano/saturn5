// boost heap: helper classes for stable priority queues
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_DETAIL_STABLE_HEAP_HPP
#define BOOST_HEAP_DETAIL_STABLE_HEAP_HPP

#include <limits>
#include <stdexcept>
#include <utility>

#include <boost/cstdint.hpp>
#include <boost/throw_exception.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/heap/policies.hpp>
#include <boost/heap/heap_merge.hpp>

#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/type_traits/is_nothrow_move_assignable.hpp>

namespace boost  {
namespace heap   {
namespace detail {

template<bool ConstantSize, class SizeType>
struct size_holder
{
    static const bool constant_time_size = ConstantSize;
    typedef SizeType  size_type;

    size_holder(void) BOOST_NOEXCEPT:
        size_(0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    size_holder(size_holder && rhs) BOOST_NOEXCEPT:
        size_(rhs.size_)
    {
        rhs.size_ = 0;
    }

    size_holder(size_holder const & rhs) BOOST_NOEXCEPT:
        size_(rhs.size_)
    {}

    size_holder & operator=(size_holder && rhs) BOOST_NOEXCEPT
    {
        size_ = rhs.size_;
        rhs.size_ = 0;
        return *this;
    }

    size_holder & operator=(size_holder const & rhs) BOOST_NOEXCEPT
    {
        size_ = rhs.size_;
        return *this;
    }
#endif

    SizeType get_size() const BOOST_NOEXCEPT
    {  return size_;  }

    void set_size(SizeType size) BOOST_NOEXCEPT
    {  size_ = size; }

    void decrement() BOOST_NOEXCEPT
    {  --size_; }

    void increment() BOOST_NOEXCEPT
    {  ++size_; }

    void add(SizeType value) BOOST_NOEXCEPT
    {  size_ += value; }

    void sub(SizeType value) BOOST_NOEXCEPT
    {  size_ -= value; }

    void swap(size_holder & rhs) BOOST_NOEXCEPT
    {  std::swap(size_, rhs.size_); }

    SizeType size_;
};

template<class SizeType>
struct size_holder<false, SizeType>
{
    static const bool constant_time_size = false;
    typedef SizeType  size_type;

    size_holder(void) BOOST_NOEXCEPT
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    size_holder(size_holder && rhs) BOOST_NOEXCEPT
    {}

    size_holder(size_holder const & rhs) BOOST_NOEXCEPT
    {}

    size_holder & operator=(size_holder && rhs) BOOST_NOEXCEPT
    {
        return *this;
    }

    size_holder & operator=(size_holder const & rhs) BOOST_NOEXCEPT
    {
        return *this;
    }
#endif

    size_type get_size() const BOOST_NOEXCEPT
    {  return 0;  }

    void set_size(size_type) BOOST_NOEXCEPT
    {}

    void decrement() BOOST_NOEXCEPT
    {}

    void increment() BOOST_NOEXCEPT
    {}

    void add(SizeType /*value*/) BOOST_NOEXCEPT
    {}

    void sub(SizeType /*value*/) BOOST_NOEXCEPT
    {}

    void swap(size_holder & /*rhs*/) BOOST_NOEXCEPT
    {}
};

// note: MSVC does not implement lookup correctly, we therefore have to place the Cmp object as member inside the
//       struct. of course, this prevents EBO and significantly reduces the readability of this code
template <typename T,
          typename Cmp,
          bool constant_time_size,
          typename StabilityCounterType = boost::uintmax_t,
          bool stable = false
         >
struct heap_base:
#ifndef BOOST_MSVC
    Cmp,
#endif
    size_holder<constant_time_size, size_t>
{
    typedef StabilityCounterType stability_counter_type;
    typedef T value_type;
    typedef T internal_type;
    typedef size_holder<constant_time_size, size_t> size_holder_type;
    typedef Cmp value_compare;
    typedef Cmp internal_compare;
    static const bool is_stable = stable;

#ifdef BOOST_MSVC
    Cmp cmp_;
#endif

    heap_base (Cmp const & cmp = Cmp()):
#ifndef BOOST_MSVC
        Cmp(cmp)
#else
        cmp_(cmp)
#endif
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    heap_base(heap_base && rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<Cmp>::value):
#ifndef BOOST_MSVC
        Cmp(std::move(static_cast<Cmp&>(rhs))),
#endif
        size_holder_type(std::move(static_cast<size_holder_type&>(rhs)))
#ifdef BOOST_MSVC
        , cmp_(std::move(rhs.cmp_))
#endif
    {}

    heap_base(heap_base const & rhs):
#ifndef BOOST_MSVC
        Cmp(static_cast<Cmp const &>(rhs)),
#endif
        size_holder_type(static_cast<size_holder_type const &>(rhs))
#ifdef BOOST_MSVC
        , cmp_(rhs.value_comp())
#endif
    {}

    heap_base & operator=(heap_base && rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_assignable<Cmp>::value)
    {
        value_comp_ref().operator=(std::move(rhs.value_comp_ref()));
        size_holder_type::operator=(std::move(static_cast<size_holder_type&>(rhs)));
        return *this;
    }

    heap_base & operator=(heap_base const & rhs)
    {
        value_comp_ref().operator=(rhs.value_comp());
        size_holder_type::operator=(static_cast<size_holder_type const &>(rhs));
        return *this;
    }
#endif

    bool operator()(internal_type const & lhs, internal_type const & rhs) const
    {
        return value_comp().operator()(lhs, rhs);
    }

    internal_type make_node(T const & val)
    {
        return val;
    }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    T && make_node(T && val)
    {
        return std::forward<T>(val);
    }
#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    internal_type make_node(Args && ... val)
    {
        return internal_type(std::forward<Args>(val)...);
    }
#endif

    static T & get_value(internal_type & val) BOOST_NOEXCEPT
    {
        return val;
    }

    static T const & get_value(internal_type const & val) BOOST_NOEXCEPT
    {
        return val;
    }

    Cmp const & value_comp(void) const BOOST_NOEXCEPT
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }

    Cmp const & get_internal_cmp(void) const BOOST_NOEXCEPT
    {
        return value_comp();
    }

    void swap(heap_base & rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<Cmp>::value && boost::is_nothrow_move_assignable<Cmp>::value)
    {
        std::swap(value_comp_ref(), rhs.value_comp_ref());
        size_holder<constant_time_size, size_t>::swap(rhs);
    }

    stability_counter_type get_stability_count(void) const BOOST_NOEXCEPT
    {
        return 0;
    }

    void set_stability_count(stability_counter_type) BOOST_NOEXCEPT
    {}

    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

private:
    Cmp & value_comp_ref(void)
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }
};


template <typename T,
          typename Cmp,
          bool constant_time_size,
          typename StabilityCounterType
         >
struct heap_base<T, Cmp, constant_time_size, StabilityCounterType, true>:
#ifndef BOOST_MSVC
    Cmp,
#endif
    size_holder<constant_time_size, size_t>
{
    typedef StabilityCounterType stability_counter_type;
    typedef T value_type;

    struct internal_type
    {
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
        template <class ...Args>
        internal_type(stability_counter_type cnt, Args && ... args):
            first(std::forward<Args>(args)...), second(cnt)
        {}
#endif

        internal_type(stability_counter_type const & cnt, T const & value):
            first(value), second(cnt)
        {}

        T first;
        stability_counter_type second;
    };

    typedef size_holder<constant_time_size, size_t> size_holder_type;
    typedef Cmp value_compare;

#ifdef BOOST_MSVC
    Cmp cmp_;
#endif

    heap_base (Cmp const & cmp = Cmp()):
#ifndef BOOST_MSVC
        Cmp(cmp),
#else
        cmp_(cmp),
#endif
        counter_(0)
    {}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    heap_base(heap_base && rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<Cmp>::value):
#ifndef BOOST_MSVC
        Cmp(std::move(static_cast<Cmp&>(rhs))),
#else
        cmp_(std::move(rhs.cmp_)),
#endif
        size_holder_type(std::move(static_cast<size_holder_type&>(rhs))), counter_(rhs.counter_)
    {
        rhs.counter_ = 0;
    }

    heap_base(heap_base const & rhs):
#ifndef BOOST_MSVC
        Cmp(static_cast<Cmp const&>(rhs)),
#else
        cmp_(rhs.value_comp()),
#endif
        size_holder_type(static_cast<size_holder_type const &>(rhs)), counter_(rhs.counter_)
    {}

    heap_base & operator=(heap_base && rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_assignable<Cmp>::value)
    {
        value_comp_ref().operator=(std::move(rhs.value_comp_ref()));
        size_holder_type::operator=(std::move(static_cast<size_holder_type&>(rhs)));

        counter_ = rhs.counter_;
        rhs.counter_ = 0;
        return *this;
    }

    heap_base & operator=(heap_base const & rhs)
    {
        value_comp_ref().operator=(rhs.value_comp());
        size_holder_type::operator=(static_cast<size_holder_type const &>(rhs));

        counter_ = rhs.counter_;
        return *this;
    }
#endif

    bool operator()(internal_type const & lhs, internal_type const & rhs) const
    {
        return get_internal_cmp()(lhs, rhs);
    }

    bool operator()(T const & lhs, T const & rhs) const
    {
        return value_comp()(lhs, rhs);
    }

    internal_type make_node(T const & val)
    {
        stability_counter_type count = ++counter_;
        if (counter_ == (std::numeric_limits<stability_counter_type>::max)())
            BOOST_THROW_EXCEPTION(std::runtime_error("boost::heap counter overflow"));
        return internal_type(count, val);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <class... Args>
    internal_type make_node(Args&&... args)
    {
        stability_counter_type count = ++counter_;
        if (counter_ == (std::numeric_limits<stability_counter_type>::max)())
            BOOST_THROW_EXCEPTION(std::runtime_error("boost::heap counter overflow"));
        return internal_type (count, std::forward<Args>(args)...);
    }
#endif

    static T & get_value(internal_type & val) BOOST_NOEXCEPT
    {
        return val.first;
    }

    static T const & get_value(internal_type const & val) BOOST_NOEXCEPT
    {
        return val.first;
    }

    Cmp const & value_comp(void) const BOOST_NOEXCEPT
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }

    struct internal_compare:
        Cmp
    {
        internal_compare(Cmp const & cmp = Cmp()):
            Cmp(cmp)
        {}

        bool operator()(internal_type const & lhs, internal_type const & rhs) const
        {
            if (Cmp::operator()(lhs.first, rhs.first))
                return true;

            if (Cmp::operator()(rhs.first, lhs.first))
                return false;

            return lhs.second > rhs.second;
        }
    };

    internal_compare get_internal_cmp(void) const
    {
        return internal_compare(value_comp());
    }

    void swap(heap_base & rhs) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<Cmp>::value && boost::is_nothrow_move_assignable<Cmp>::value)
    {
#ifndef BOOST_MSVC
        std::swap(static_cast<Cmp&>(*this), static_cast<Cmp&>(rhs));
#else
        std::swap(cmp_, rhs.cmp_);
#endif
        std::swap(counter_, rhs.counter_);
        size_holder<constant_time_size, size_t>::swap(rhs);
    }

    stability_counter_type get_stability_count(void) const
    {
        return counter_;
    }

    void set_stability_count(stability_counter_type new_count)
    {
        counter_ = new_count;
    }

    template <typename Heap1, typename Heap2>
    friend struct heap_merge_emulate;

private:
    Cmp & value_comp_ref(void) BOOST_NOEXCEPT
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }

    stability_counter_type counter_;
};

template <typename node_pointer,
          typename extractor,
          typename reference
         >
struct node_handle
{
    explicit node_handle(node_pointer n = 0):
        node_(n)
    {}

    reference operator*() const
    {
        return extractor::get_value(node_->value);
    }

    bool operator==(node_handle const & rhs) const
    {
        return node_ == rhs.node_;
    }

    bool operator!=(node_handle const & rhs) const
    {
        return node_ != rhs.node_;
    }

    node_pointer node_;
};

template <typename value_type,
          typename internal_type,
          typename extractor
         >
struct value_extractor
{
    value_type const & operator()(internal_type const & data) const
    {
        return extractor::get_value(data);
    }
};

template <typename T,
          typename ContainerIterator,
          typename Extractor>
class stable_heap_iterator:
    public boost::iterator_adaptor<stable_heap_iterator<T, ContainerIterator, Extractor>,
                                   ContainerIterator,
                                   T const,
                                   boost::random_access_traversal_tag>
{
    typedef boost::iterator_adaptor<stable_heap_iterator,
                                    ContainerIterator,
                                    T const,
                                    boost::random_access_traversal_tag> super_t;

public:
    stable_heap_iterator(void):
        super_t(0)
    {}

    explicit stable_heap_iterator(ContainerIterator const & it):
        super_t(it)
    {}

private:
    friend class boost::iterator_core_access;

    T const & dereference() const
    {
        return Extractor::get_value(*super_t::base());
    }
};

template <typename T, typename Parspec, bool constant_time_size>
struct make_heap_base
{
    typedef typename parameter::binding<Parspec, tag::compare, std::less<T> >::type compare_argument;
    typedef typename parameter::binding<Parspec, tag::allocator, std::allocator<T> >::type allocator_argument;
    typedef typename parameter::binding<Parspec, tag::stability_counter_type, boost::uintmax_t >::type stability_counter_type;

    static const bool is_stable = extract_stable<Parspec>::value;

    typedef heap_base<T, compare_argument, constant_time_size, stability_counter_type, is_stable> type;
};


template <typename Alloc>
struct extract_allocator_types
{
    typedef typename boost::allocator_size_type<Alloc>::type size_type;
    typedef typename boost::allocator_difference_type<Alloc>::type difference_type;
    typedef typename Alloc::value_type& reference;
    typedef typename Alloc::value_type const& const_reference;
    typedef typename boost::allocator_pointer<Alloc>::type pointer;
    typedef typename boost::allocator_const_pointer<Alloc>::type const_pointer;
};


} /* namespace detail */
} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_DETAIL_STABLE_HEAP_HPP */

/* stable_heap.hpp
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
*/