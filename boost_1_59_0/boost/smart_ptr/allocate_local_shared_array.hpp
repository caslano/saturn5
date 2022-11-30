/*
Copyright 2017-2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_SMART_PTR_ALLOCATE_LOCAL_SHARED_ARRAY_HPP
#define BOOST_SMART_PTR_ALLOCATE_LOCAL_SHARED_ARRAY_HPP

#include <boost/smart_ptr/allocate_shared_array.hpp>
#include <boost/smart_ptr/local_shared_ptr.hpp>

namespace boost {
namespace detail {

class BOOST_SYMBOL_VISIBLE lsp_array_base
    : public local_counted_base {
public:
    void set(sp_counted_base* base) BOOST_SP_NOEXCEPT {
        count_ = shared_count(base);
    }

    void local_cb_destroy() BOOST_SP_NOEXCEPT BOOST_OVERRIDE {
        shared_count().swap(count_);
    }

    shared_count local_cb_get_shared_count() const
        BOOST_SP_NOEXCEPT BOOST_OVERRIDE {
        return count_;
    }

private:
    shared_count count_;
};

template<class A>
class lsp_array_state
    : public sp_array_state<A> {
public:
    template<class U>
    lsp_array_state(const U& other, std::size_t size) BOOST_SP_NOEXCEPT
        : sp_array_state<A>(other, size) { }

    lsp_array_base& base() BOOST_SP_NOEXCEPT {
        return base_;
    }

private:
    lsp_array_base base_;
};

template<class A, std::size_t N>
class lsp_size_array_state
    : public sp_size_array_state<A, N> {
public:
    template<class U>
    lsp_size_array_state(const U& other, std::size_t size) BOOST_SP_NOEXCEPT
        : sp_size_array_state<A, N>(other, size) { }

    lsp_array_base& base() BOOST_SP_NOEXCEPT {
        return base_;
    }

private:
    lsp_array_base base_;
};

} /* detail */

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value,
    local_shared_ptr<T> >::type
allocate_local_shared(const A& allocator, std::size_t count)
{
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::lsp_array_state<other> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count);
    detail::lsp_array_base& local = node->state().base();
    local.set(node);
    result.release();
    return local_shared_ptr<T>(detail::lsp_internal_constructor_tag(), start,
        &local);
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value,
    local_shared_ptr<T> >::type
allocate_local_shared(const A& allocator)
{
    enum {
        count = extent<T>::value
    };
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::lsp_size_array_state<other, count> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count);
    detail::lsp_array_base& local = node->state().base();
    local.set(node);
    result.release();
    return local_shared_ptr<T>(detail::lsp_internal_constructor_tag(), start,
        &local);
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value,
    local_shared_ptr<T> >::type
allocate_local_shared(const A& allocator, std::size_t count,
    const typename remove_extent<T>::type& value)
{
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::lsp_array_state<other> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count, value);
    detail::lsp_array_base& local = node->state().base();
    local.set(node);
    result.release();
    return local_shared_ptr<T>(detail::lsp_internal_constructor_tag(), start,
        &local);
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value,
    local_shared_ptr<T> >::type
allocate_local_shared(const A& allocator,
    const typename remove_extent<T>::type& value)
{
    enum {
        count = extent<T>::value
    };
    typedef typename detail::sp_array_element<T>::type element;
    typedef typename allocator_rebind<A, element>::type other;
    typedef detail::lsp_size_array_state<other, count> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, count);
    base* node = result.get();
    element* start = detail::sp_array_start<element>(node);
    ::new(static_cast<void*>(node)) base(allocator, start, count, value);
    detail::lsp_array_base& local = node->state().base();
    local.set(node);
    result.release();
    return local_shared_ptr<T>(detail::lsp_internal_constructor_tag(), start,
        &local);
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value,
    local_shared_ptr<T> >::type
allocate_local_shared_noinit(const A& allocator, std::size_t count)
{
    return boost::allocate_local_shared<T>(boost::noinit_adapt(allocator),
        count);
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value,
    local_shared_ptr<T> >::type
allocate_local_shared_noinit(const A& allocator)
{
    return boost::allocate_local_shared<T>(boost::noinit_adapt(allocator));
}

} /* boost */

#endif

/* allocate_local_shared_array.hpp
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
*/