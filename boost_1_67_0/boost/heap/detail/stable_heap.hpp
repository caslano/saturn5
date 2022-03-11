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
#ifdef BOOST_NO_CXX11_ALLOCATOR
    typedef typename Alloc::size_type size_type;
    typedef typename Alloc::difference_type difference_type;
    typedef typename Alloc::reference reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::pointer pointer;
    typedef typename Alloc::const_pointer const_pointer;
#else
    typedef std::allocator_traits<Alloc> traits;
    typedef typename traits::size_type size_type;
    typedef typename traits::difference_type difference_type;
    typedef typename Alloc::value_type& reference;
    typedef typename Alloc::value_type const& const_reference;
    typedef typename traits::pointer pointer;
    typedef typename traits::const_pointer const_pointer;
#endif
};


} /* namespace detail */
} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_DETAIL_STABLE_HEAP_HPP */

/* stable_heap.hpp
Dyjx0C5bPnm5A+XZetnSceOjhavcDna+ssow8OkKDe+CgxCOswtZXYUmYx9EKn4RlM0esaox0PihnWQhQQrVm97skoLNodOqvfYECzKb4OdIMibhjCju3sw7pn1eBJhLQ4WPiDZ5TWS1nDBf48ZoJumk/9IbRwiUUs79MvRt93uTcgvw2722GCQKUZjgnDrXdNRkshWQ1j3L9PBN7YeexQ1TeXeiKJK2+VuOr2nI63nHGlKOoMixf84CyQ5DlF8zq14GAZdEIk5L6GSVYDE6YkmRfEXgDR4o/MfRV7vMSks9bmhGafS3WTluwl9Ao5olSUl0NlIK+VDuD0XiJAxT0DAOy7Y1zU7N7bqc5poxN20AYI3LG4eJKDtfNDwc88pJqRW0ugAAmlMzpukYGBpKWBaAmnFf90ED4f+7S45Rf+xcJeXj4M9JyEIu8umL+mE+09Vb0rwVKXOeA1Jk5Ajq8+Il4N2oy6QmNKW4+I7t5f6xVYCrDLWqWvtunzrIwiraLnEbNriMYmZde+S4N8iinGYdH4Ldlng6WgZY04/oQz0cl25OiSHVnlj4L/sNfNHhkzOsBYjHnmprNzRpeNHGbh7IChqlXM5WP0tcXeebYufX62B82JjhnSmWx9wh86IXFECcnLRJwdtCi+b330zQbJjU5UcjH6CpG9bYQthtT4T36wru0J1T4+46fkyWqGqQkQ/bf7saFghU64pqUBhyB7iyY4yFsBYZW+DZJUD6WyYI7QcUJrEgjBglaYDe9GjPgXsr7RQsZLZNDQ0eW+OIvwLLwbMCi6pdNVuJTFy24DhrZiQB7ow0Pb6qygJ76nZn7L7SlcnRO6WpcM/rXT2Tz9Y1/Q0vcBNjn05Q6tUknIIUUUAueVERme8lycsycTJVNLWJeBEgSubUHTChTCGjZJpPKqU2pn7Xs7BoW+mndF7taFkqXJEZX7FeDcv4isI8yDU9lzlrlnEFfm15sxi05MdGsYnEL6kl/E2MHmx5nJJwVW5UbRiusY1VxThlg1cyWojCP6ivZN8p/yn5u0OkuZs66RX924mF2VQKgP89UdGMWWmrnksNfPuPwURcolFLtSKCopiio5THNHnhxUjFbLU65b0p6TawBXXQJ9JMr5HY4uxt6eyE/FBaP2MYsQ8VLWHEu+EtigkaJMjIHUqeIr9P5FQl4qDKcmGNceF8KtdTfu3a86qU5FboZItg8FN4I28PQBH2/l7t0u7k2u/0igOYl6hFvRsVizxt6ZgbDueGNio/CMFfCKqWLrjbBv4weuFZQa45Y38LUZdhsJT4/G5XH/NsuLw5F8mjZYLcugbNi+CrsxAMOF9bAKkwNaOWt1KCd05NbdNhKpXga1bu81HHsJ1XbKCLr/TEsmd15sEsStV/8lDuWG22AaZbMVZ22FlJThJBj67rVOToGnceh5WQjjJ3+GClsbZS8TFUIVLFjdnlYN6M8dmx1ksIAV7HrCfJQhpTvLNOmzGoY2JI63KlbZPlJjkB+luH7vjm4Ne595pZXuh4lR71Htkd7AHp99Fiv6XOAiUTdsOVD//sg5ypow6DWseZHaO00ABrAVTA+Hpm5pvVTFVOeJp7JlYfAj7jjg6V+ioE9Cg0xtEi7zUggfzib9F8qu1+cTosR7/TNqOtjtF+vbzTUOXLK7aAa/VtBFa5YAPJ1Qh4D2j8ijWmNIlPTylb7uMNKZ9sPoLRlFOiCoXaOJ7SmGcKcELPuNZGFZtFyOWHujrlOcIYMSluhJ7FpYMlylS4aXJInkDBxaB8i5PltqsQdFEQKoBbQNF/EOXfng+1I6kaLhwI21IEBUaVRiOGJaHXvyOjGRAhRhw1HGht0+I6m6Xp9hpAL7e5HCtes08RA+npXVN1EdgPokvTnaj8inkgEFEIWy5f9QWunMck5zXwhiaYuyE6BGZu6+j9P9R2JfT1aGPVOkknYqRZv6ZX4v+TUZDNLz0c96pBA2Qi70rJJZiHWQUKWgkqxdoxgLQA9oOcert82VT1M3RYw2lu0sffflW+tlfLKEZiU9cPrPk8TAXosaZTyZ5ebhlJCWNvTrcGxlfuaF8TNiULPioxKLz9fR+gF/conXOrvKct31dK7OW63M2cBBUyFyM+EMWG6PqSzGLDvXX3Y8zCCunLXlQ4joj9ta2+bPNwRW3L8Utn+FctxW4tBbtdKL3XjcDQavY65ZeEdxC1jv16u63IiqlPjbsa5LPDjnf87NqKvdQw3o8UTsreF52FGuwOxtxEW87L8Jny2k0nHzK791b6KVJV93QxxxaZCFi4yKl+1tPp3ywHMlZEzzCdorRrMSiqm83U0cifARvPeT2yXGe+h1/E4QrO2oNGaMBmmvDqpwV+I8ObsRH25l6p5Co9NlJLMidaSJsQ7DuQo6MTJaYFJX55MSRqobqwwgFV8x9auhgCDnEXOxMOZCvDYwNI36Wl2UKH37IpGBvx13fq7vwWJ0tXQzXmyhk8iCGWqhUM0Iv8J/9asIP9ZQjOfso/IGaninyENjISU/VEqYbm8oVGvQL+tPl80ZJhFtdGKNuWs3gQPqCbKpDTyPIZ4kTOyichWtG5ImPGx4u9+HhE3XBfYzJtwuCTtAyV2QgL4c6ibAnKgTNbvDZwKZO1pZp+fVp9/sjhvccwLJ7OReX6QZOsJmFNgb67nYpF5uAsmJSxJ6NnGX6oClt8fs++EzuAFyub5hC0MEFsuJxHU8aeMIYhGjW28bxSt9WmnRMryi53pZnmAj0m3Fo+DAXYpIsPaSJyAAo4YeRv/8POoYCRAmsemW3t7jCCa+Li45h+D+aVVV60ek03UQmY/r4Jx6Q7g/gBuoUeFdnjhy/DoIoeHydpRhmEXc3TYRIxEEfmEY7EkwnnusHbLtKW385SfxC31z1BewTvg0FH4lCmJ0iTTXZU4K9SA21y4yXekKExWz4n3sx+uPlWWAoGrpA1LXQTeeTRbnA226dR1OHlXP7IfycfLAh4QNsKKdZ4pBIPCIi2nAq0NPv1jaHDXEpI/4EoIcSzYx6FcMAjpsjfYfwXrNGGPnY6xsxmLohxBCz7kfIGuvXoHjEdj02pa6zZEzzjY2vFMm+sc+Wi33RafVKiivrjJgx4AS/KzYkWmmfv9ZG/QHs3zS8tR6vFoiTPOQpzuWmFCuXvksJ6+j7SrA+I1Ed4JbvVlzLUPzn6oL236mKo7UdwczWq1cp2j1gRCy33nLr/2QlK2NxoUxOr9d+RL4a3cKmfOaNpzNkQpNj+S9sFkkT6SsHhBbz2WZXn2PopBN5JGrsmve7dp5nszBds5T/9D1P2r2kHMfpkYjUbzZ+djCjYWwdepUgKlLa70ymANCHgvj6PTuZ1SaWspW5GOnbyGBmaCczvilCrjy5OhmtxWWtrd8eZXiJh5HCIxOUlgToUfbn/9OldgfckP+ddqxX2pqBTgzh76Nk6c7WhaOd8bBoXbUFafPOJT262cqcgmcqj0aXWm26/OF+6/VmpbVVbRPzZvtVhKARUL30s6uxF+gikDLhVmEgZ2piSTLlyUPOjkzG5XEgD0e6UHdV/YbXeYbP0+FmvGiIIKbCqw7X9+V6cnsBNyZLehqf5gbLy2zHXaCjmrbw8j4DDfa1qPIbByw8LlcL8FQUedANaXYOQpdGFHSe1VjJKtZvKMsGtltT33Kd2YQYhKCD57fGS05YvuZ7gqOjM/8tLkNbkFBAccRr2HwO0D8mZ//UgkXL+J57KkwHxQRLMmp7xoaP5/tK51sR8Slw7Om+xJsAqmxQQaxLPCGIw4vbCucqKnf/ioxJjmW/7BtaGSPLEo02kK+o9rNhZWTM3NCBi6KUCx1cO928ap5AqSbwGlYB4pkyUp/x705CWPd184nMJ1ufBlZszqMwJP+ly2b3wPdXOaUyeGCGrJlAIJJF1E1mWfiYVHZj4cgVPRQpj+D/GOaFUmvstjPMU/lLiJLTrXoyX3dW0VBah8QsFqmMXkt6+mG/1IY623sFUAPYxgMf5xIvBoVMLVT4LoREdJmy/tARVhOSi/siSHOepErb8D7O8CXZw2xHnZnSiyIPsDqb20iFo6syqneuRtGW6bFvJI/DmUT4Uqq+KZNbZV/GSTpy0hLtOukVpgvm9Y49vb7SL4Fv8WYEATjR70uKoC0ED9oNDFsWGSkcKb4OC356GSjrJoXyJccqTUtnkdgoeQV7fNESA/rBprMz6xNrAfefV8INFMsKKpJC+kD5DThDIoJ/SVe8WM8E1pUeN1TS6+i1zKXoANbQflNq16xzmB7Bye0lxgH34sDdfuEJg68DmeW+SaC/7SSnPWYmBdwVAdestRC6r8TYphCJBCI3d/mmaNWcbxRPrKMSz2AunxvXM/U9yMtF0KiIVbxtlDDMXz9vas7SkEcLU8MTkafPM889wB/BvBn7jdlL0Mf56R1AbHyS/nmjgHmwpy9cpeoPsTEdc5i1K32XLp+cMnNOPY7P3Z+Rc8gtu2qNJfNiXdu13oyVpOqb/gj9ekC0LsVI77qGyXKUpF9VWIoNa8CyQQxzO0gkcwM/DXzhkiOQIOPnGt5Zb1cO6YWR4jbuuGx6DP2eTZYoQpj4say6bojYb1mR9t9Tz1zhaRDSy84xjaQ1YgLFrycLYi9njZ3YkoK7xbkliku0wEDNKkxOdoKk1z2/imCYruqfnuiEpTBfn3mdLOsFRswT3JkicAXIIeu2WvotYQUtl4w7sKZKYLrkrER25fOXxLN52gDQbQ8WLSoXF9LgwZfH7p3TwDFlEIvAURXWCKimFO2UUsEL17Q0Sp7yEnoLTlC5VoJNZmki36QkqirmyMYjgl8y5iFiv/XRdRI4WWpvR2w+2/rXd2RouAen33c2v6g/Xu2/UxNjEZ4QQRU7lY5ltOyvQ6pa/xF6YzF21U29vqMfKj4Oxs2zMkOjltrR2sLyVBVRxAW/j69ipLAdRegzZBN6wJd2wgDytqTNmSNZ4lUIA3bSrf72Ba95I7LIKGVuKSH1q8g61TnJ70rsUmA165hTBAQKfpSkapvQp/Qf2jN28UjpG+hHk6V+2ON2zm2G/pzoPWbfqHRgJoLNwpTzldMUaSa2IKxZM8fIPa7PWhjPWV8a7umqoIDFjw4x8B639JhVBcmYPAgZfIFIpJrLFzibPNFK+Z8ThsKM6TIFX01SlboVJOrb3h8ssAwsTEH/eEFfAvYP3ywHZTerTsPZ9OoxJHwQ/OmUxz66kz0bwk5bP64ZLR7h43ZBPcXZgUOvyX8BUcpaHrOOJSpsW/7quOoSQ1RYeW7tT2DvST0fzAGq5i3vJNdKQ//htAx3a4Wp9wpEyuRqag7DkEROvs7d3TyQm9M9utdVGhKHuQo+AR1ZR4yEljySp68mu6hIdhqyia7csjvI6bqhaKtCxUBQo7jhGpaEwIX12t9V/ep+DPKC0D0uo1/Agd6ZkdnXc2fiuMmvEM5Hf8R7pBERkIEf9b/lxgk4btBRDkH7p+mENkYC0Ba33R69LYGe1inNguC3wU3dUeLpg0ZftVof4Jy0qRN2Z9In3fg7mKJLYm6QvCEPbV9Irx/1xm0kWoBZCdSTVpIAXZB9LVMMXWq3LwrU4wMvnDnBbftPSzGGG09LTttMGYHvs7mj3D8aTROxXRd2EC2/dSZjqwlS3KCP/AOKRaUJgeUVsFOHQU4MylgMomnQb58g2V+QITuzcuFBZnB3wC2gcMXMYKGL8DEtSMO0pHKf4kFaERe2B2Q7FLSb6gwi76NRZ1wyA0p2p1zh6Iv+ll1dcNQg+efQwSeWyxCEGuLrqUzNVia3uXDrd4YhM1akNQ+FzKRvRhCKrdxVqfELaNQSI0mcUnLeMs25Qeltb4VyuArmn6iFUq9NJ3aGRHZFIPEH90rqkcgF/w4LOoE5mv6AiUj17hdTxMyBm+Dz6JIZzZ7Vo+yO9r1Ev5qbY37HGFoyrwWoysw7NvnSMzSf7S5mYTdCdpWsZXmmccf2a40lv9jmHFqzz9wjvcdVcdFw4+ZjY2B1bjoZxFS2GkSzHyUyPuYImTEpj7pT+qLjhbX++YoNpdgkE9y8HrUfRB/9DNE16x6q/F+cVhVgJHTBYD8svHhk8Glx68Xhy7Y9LJG3XcL/WvwLv68uEB/Jtsb2wrIE16i+JD9o4aLj8dn+VLeceiMGrLrAfM95YCi5+S6q8lqyOzxPKzGlDy1VyGu5If0Et4HiSLXYjHISog9l882hXXSxwBcZbDsitwXPGW2QzvLd51l4viT6V82n2Peummu1tz/eYdXn4xm9ReMNCo9d2HuqcGoNQtIzz0NYSwkM1fK6dj80DxFKyEEmG7wgsYGzGpdVcj+bHqC5C2e2sV6szazysvSRGCBzp/Ea8nltUjZB2xlA5R8N/0xPZ38lggVg6Su1uZ6J7M8jCXhSVerPhPBAr7tWSiGUZZ0uYzxAmy+ZyHsUAsXnbGS9wYKIckPS/xpC5I9DJ/q9Kl5bImgmw4HMbfpMz4S4cRv9FkjZ+rpPpzbNfVJwgl7Kyi2oKgSxOgkrkYqEBLOV2CZqTpXytLVkCP5rr7ueW9pL7cIKP/l8VqKe3FVRYp6Sy/TR7Jt4Dxd6WAY63FO8zornRwwF/2bvHDNjqVgAfphfrCvN/9+tyXsXUk7pBzBNAp36f59DBuokYdjh4JlzvQ5nXEEkdJgwFv8uC6qpAMcw5XQHSycMxH4a5MEvK1LutnnwlZuwrzC9OLKO53mLclYdX+/+dLbOCdxeTLVred/3kNhNCuEiJr6r/ByctcKFUlPPIGZMQju4Mx9HQSb0Fl7GlFZiCUNLFcCJLGION8HL7Wyi82arbBbf/tMp90cncU+P53/J8wf66TTpJwT/KAktm6sfvJg1msT5YnzEqznyKPeS8NRcyFNoyxqjA1l7U4uwLNHX5KLuyC3fJa3+ylxD0TI6tO7PoutRq324wXuIIpLRkjdHfJqdReePFWua1QPRCXBnTiB7N236iKP4NBtpE8Qt1G7eYH/IoBHotKuCNIS4NSboWR/r0UHYtOP/g26xyRZsaXkkr5qrUpXTA5bZS4x3Aum/o0K/9Ix+tn8PxUugyuzMUXOhJGBaQqnvzlbdPovRbrpe5S3BczgdIsd0x5Q18aWb+5OXhQ4POp5dN5xvDGBvbvh9SwtsFOWreQMZsmslxMNTEnwGtFmCxi1dpqyIS0wz9AWDlL/LCy//GgvGPI6lbTkSf0VC/vlcO1ByomdNvet9nIkktM9HJvvgYCsLJS/VGtsurI4A0D188lYxbcYK7Ybatjo7pd229EogskWvI/m1sMUGIOO/3YjD9J05WtjCmS2gJW0lUwcMUG9WHfmq5ZPfk9EWVuXlroUWHVFIZY1kOl7JxJ6NLu1y0MRxrMGGlu6k+VBN8ziFszipDHnLH18pPP0kQAZR1jMAuQWEqEBBfjKmFgasko5LA6myXyN1Q1WYQmvMhPIV5yu4TS9vEGs03b1rMHONZV1CgiSOLgdXv7FkRT3vBEJPaaDsLGNDav1z6nEuMNmD4xhNAbP+QNViJpXG/wE6Uz/4j1tq1fSP6HwJZw+bwZCSVsp9pYHbKoORnsDndWF/JMCfjqJ59pq7+UvzVsqyg8YnquHtU9IZPShSzqTNCoDwxv83nWf6OtA9CgxPSeB01NZLOKGUuNwLwZ8ms7Ld8viA0CheXw9LUR8n3Kh5SKAzgt/Rbn6iA8Mdp2uibKBQtlrdEyb9qardCTKdG9w8MP2WdoS1foCgz3UAEd2QIOlc0imVFXjJccShGsNZe7AowXkHs7wgPARAu1iD7DR+1ieuyMLaqdTM1ggq8WM2NapPWbJ1hPcxtENa+G5z03sSX6RyR5lWQ7PG48EE85Qp2QzqtT1GQ1pOXxSsR+zkWzCWt/V1zhmgtMt4jpbTWhABt1qpoZA4wwOxEWL3002G+UQ9MUYUXHpBJLaXgRROnTAGnANwvoCT0UyjslLBUnS5PKG93Fz9Z+cMkDZK2QLkSquqM4kVBeyVnkpfj2Fck2eMozAfN5gbj5IF6zI0IzN1DmTkchkkXF0srWozoIsy8BJ5/BtptxZFWCIN6mB68sMLSXKD1/hn8b2f3u0881yfVeSdeM+yWRL94+dfO1b5xFTK76Pj9+M2FrjW7iPD/Efxs2HLS/myz91u007FjkrR6/dC7f0lNI+7A1EULFPocYDq0fGgPkV3YLVaLKzlZLMtAvawF8IRt2B3j5NmN33jKLKE2s1Zk9YKqqYEcwqoKvITS1Rx2LVDhZlpXEccIZj5VLe6e3wOmxcOdcurooGwIlB66bBclqwy5Sujq0ox5rNWAaEKuNpQCS5U1r4gfhgfe4yS6RVvBPO1CZ0PLUjxvuYANlYdVWp8yBx+qVneawbxaKnmNaGuL4eAK+2b5ZcB8G29FppD2Ei3l0PwnhO5ebE/8XmmSgwu0C7Ht+jjeB8QZCp4k+aqvOnx9BhxxRzpnM4tVDP+uyStk47MHZUDGOT4A8pYF48+jY6Fl4cpYL3OVKYkH1ZAFIk0+yjmnuteB9mwo3WeUWnvT651hCqW6rj8lJ8q3EBl7J7iroElNxX1EHZbm+l/WxSXKNJclogN+nQgf8q5le88Bx8Tq1EoEcPbVzy61u+C0YGAbOKes+H9s0BDbMvw6jBZnOjtLO3r2B9VI8y+4l6xr1lC5DrlaCcQLgnPhQoj191QqpB8ouj//HWO1YIqICUyc5BvapFeyM3FVLM5pDhakMP6sG8dORYa+EdIjJfZByPfjE4cf8fh0v4HWJolVc0bmfBcPFizF9z2H1TKRDDQ75rsuPH56NB9aO1YQJCkiPwUracH+Fx1aTybdq3Dhy9CYX/87AIXNulBOeXGBuOY1oD8lWUYABCz702LpzcWByBRIJve6TT/jgLse3Ry2wJmteHoPcZvnAUcsbeLV4Fl7V0l90GzWb44hdYua9Qutm6CD46L1xFb5xTiImzu2fNlNXV3WGqfPtgABGkGUDKnWkSK2KbhbLRocbcUq9TSqFYs9jyHs3LIBaCfQI/Bt3Q2/YKk88sXT1nK/2KY7wL5b9MDZOQSLlRcVb+nmaekZM7wJ3MxMaPOws02xEX6+2fDW8eB6Nat4L1RUmYxZaLMEjwDsrQT2Ull8wN2Mfa/Umm10ysBQyz46PIOy4FtvtwomJYqD7DxQrt1k+IZLqQ15tZc=
*/