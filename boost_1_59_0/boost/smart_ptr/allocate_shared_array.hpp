/*
Copyright 2012-2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_SMART_PTR_ALLOCATE_SHARED_ARRAY_HPP
#define BOOST_SMART_PTR_ALLOCATE_SHARED_ARRAY_HPP

#include <boost/core/allocator_access.hpp>
#include <boost/core/alloc_construct.hpp>
#include <boost/core/first_scalar.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/enable_if.hpp>
#include <boost/type_traits/extent.hpp>
#include <boost/type_traits/is_bounded_array.hpp>
#include <boost/type_traits/is_unbounded_array.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/type_with_alignment.hpp>

namespace boost {
namespace detail {

template<class T>
struct sp_array_element {
    typedef typename boost::remove_cv<typename
        boost::remove_extent<T>::type>::type type;
};

template<class T>
struct sp_array_count {
    enum {
        value = 1
    };
};

template<class T, std::size_t N>
struct sp_array_count<T[N]> {
    enum {
        value = N * sp_array_count<T>::value
    };
};

template<std::size_t N, std::size_t M>
struct sp_max_size {
    enum {
        value = N < M ? M : N
    };
};

template<std::size_t N, std::size_t M>
struct sp_align_up {
    enum {
        value = (N + M - 1) & ~(M - 1)
    };
};

template<class T>
BOOST_CONSTEXPR inline std::size_t
sp_objects(std::size_t size) BOOST_SP_NOEXCEPT
{
    return (size + sizeof(T) - 1) / sizeof(T);
}

template<class A>
class sp_array_state {
public:
    typedef A type;

    template<class U>
    sp_array_state(const U& _allocator, std::size_t _size) BOOST_SP_NOEXCEPT
        : allocator_(_allocator),
          size_(_size) { }

    A& allocator() BOOST_SP_NOEXCEPT {
        return allocator_;
    }

    std::size_t size() const BOOST_SP_NOEXCEPT {
        return size_;
    }

private:
    A allocator_;
    std::size_t size_;
};

template<class A, std::size_t N>
class sp_size_array_state {
public:
    typedef A type;

    template<class U>
    sp_size_array_state(const U& _allocator, std::size_t) BOOST_SP_NOEXCEPT
        : allocator_(_allocator) { }

    A& allocator() BOOST_SP_NOEXCEPT {
        return allocator_;
    }

    BOOST_CONSTEXPR std::size_t size() const BOOST_SP_NOEXCEPT {
        return N;
    }

private:
    A allocator_;
};

template<class T, class U>
struct sp_array_alignment {
    enum {
        value = sp_max_size<boost::alignment_of<T>::value,
            boost::alignment_of<U>::value>::value
    };
};

template<class T, class U>
struct sp_array_offset {
    enum {
        value = sp_align_up<sizeof(T), sp_array_alignment<T, U>::value>::value
    };
};

template<class U, class T>
inline U*
sp_array_start(T* base) BOOST_SP_NOEXCEPT
{
    enum {
        size = sp_array_offset<T, U>::value
    };
    return reinterpret_cast<U*>(reinterpret_cast<char*>(base) + size);
}

template<class A, class T>
class sp_array_creator {
    typedef typename A::value_type element;

    enum {
        offset = sp_array_offset<T, element>::value
    };

    typedef typename boost::type_with_alignment<sp_array_alignment<T,
        element>::value>::type type;

public:
    template<class U>
    sp_array_creator(const U& other, std::size_t size) BOOST_SP_NOEXCEPT
        : other_(other),
          size_(sp_objects<type>(offset + sizeof(element) * size)) { }

    T* create() {
        return reinterpret_cast<T*>(other_.allocate(size_));
    }

    void destroy(T* base) {
        other_.deallocate(reinterpret_cast<type*>(base), size_);
    }

private:
    typename boost::allocator_rebind<A, type>::type other_;
    std::size_t size_;
};

template<class T>
class BOOST_SYMBOL_VISIBLE sp_array_base
    : public sp_counted_base {
    typedef typename T::type allocator;

public:
    typedef typename allocator::value_type type;

    template<class A>
    sp_array_base(const A& other, type* start, std::size_t size)
        : state_(other, size) {
        boost::alloc_construct_n(state_.allocator(),
            boost::first_scalar(start),
            state_.size() * sp_array_count<type>::value);
    }

    template<class A, class U>
    sp_array_base(const A& other, type* start, std::size_t size, const U& list)
        : state_(other, size) {
        enum {
            count = sp_array_count<type>::value
        };
        boost::alloc_construct_n(state_.allocator(),
            boost::first_scalar(start), state_.size() * count,
            boost::first_scalar(&list), count);
    }

    T& state() BOOST_SP_NOEXCEPT {
        return state_;
    }

    void dispose() BOOST_SP_NOEXCEPT BOOST_OVERRIDE {
        boost::alloc_destroy_n(state_.allocator(),
            boost::first_scalar(sp_array_start<type>(this)),
            state_.size() * sp_array_count<type>::value);
    }

    void destroy() BOOST_SP_NOEXCEPT BOOST_OVERRIDE {
        sp_array_creator<allocator, sp_array_base> other(state_.allocator(),
            state_.size());
        this->~sp_array_base();
        other.destroy(this);
    }

    void* get_deleter(const sp_typeinfo_&) BOOST_SP_NOEXCEPT BOOST_OVERRIDE {
        return 0;
    }

    void* get_local_deleter(const sp_typeinfo_&)
        BOOST_SP_NOEXCEPT BOOST_OVERRIDE {
        return 0;
    }

    void* get_untyped_deleter() BOOST_SP_NOEXCEPT BOOST_OVERRIDE {
        return 0;
    }

private:
    T state_;
};

template<class A, class T>
struct sp_array_result {
public:
    template<class U>
    sp_array_result(const U& other, std::size_t size)
        : creator_(other, size),
          result_(creator_.create()) { }

    ~sp_array_result() {
        if (result_) {
            creator_.destroy(result_);
        }
    }

    T* get() const BOOST_SP_NOEXCEPT {
        return result_;
    }

    void release() BOOST_SP_NOEXCEPT {
        result_ = 0;
    }

private:
    sp_array_result(const sp_array_result&);
    sp_array_result& operator=(const sp_array_result&);

    sp_array_creator<A, T> creator_;
    T* result_;
};

} /* detail */

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator, std::size_t count)
{
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::sp_array_state<other> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(), start,
        detail::shared_count(static_cast<detail::sp_counted_base*>(node)));
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator)
{
    enum {
        count = extent<T>::value
    };
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::sp_size_array_state<other, extent<T>::value> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(), start,
        detail::shared_count(static_cast<detail::sp_counted_base*>(node)));
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator, std::size_t count,
    const typename remove_extent<T>::type& value)
{
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::sp_array_state<other> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count, value);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(), start,
        detail::shared_count(static_cast<detail::sp_counted_base*>(node)));
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator,
    const typename remove_extent<T>::type& value)
{
    enum {
        count = extent<T>::value
    };
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::sp_size_array_state<other, extent<T>::value> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count, value);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(), start,
        detail::shared_count(static_cast<detail::sp_counted_base*>(node)));
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value, shared_ptr<T> >::type
allocate_shared_noinit(const A& allocator, std::size_t count)
{
    return boost::allocate_shared<T>(boost::noinit_adapt(allocator), count);
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value, shared_ptr<T> >::type
allocate_shared_noinit(const A& allocator)
{
    return boost::allocate_shared<T>(boost::noinit_adapt(allocator));
}

} /* boost */

#endif

/* allocate_shared_array.hpp
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
*/