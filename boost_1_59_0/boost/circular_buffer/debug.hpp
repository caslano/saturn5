// Debug support for the circular buffer library.

// Copyright (c) 2003-2008 Jan Gaspar

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_CIRCULAR_BUFFER_DEBUG_HPP)
#define BOOST_CIRCULAR_BUFFER_DEBUG_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#if BOOST_CB_ENABLE_DEBUG
#include <cstring>

#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
    using ::memset;
}
#endif

#endif // BOOST_CB_ENABLE_DEBUG
namespace boost {

namespace cb_details {

#if BOOST_CB_ENABLE_DEBUG

// The value the uninitialized memory is filled with.
const int UNINITIALIZED = 0xcc;

template <class T>
inline void do_fill_uninitialized_memory(T* data, std::size_t size_in_bytes) BOOST_NOEXCEPT {
    std::memset(static_cast<void*>(data), UNINITIALIZED, size_in_bytes);
}

template <class T>
inline void do_fill_uninitialized_memory(T& /*data*/, std::size_t /*size_in_bytes*/) BOOST_NOEXCEPT {
    // Do nothing
}


class debug_iterator_registry;

/*!
    \class debug_iterator_base
    \brief Registers/unregisters iterators into the registry of valid iterators.

    This class is intended to be a base class of an iterator.
*/
class debug_iterator_base {

private:
// Members

    //! Iterator registry.
    mutable const debug_iterator_registry* m_registry;

    //! Next iterator in the iterator chain.
    mutable const debug_iterator_base* m_next;

public:
// Construction/destruction

    //! Default constructor.
    debug_iterator_base();

    //! Constructor taking the iterator registry as a parameter.
    debug_iterator_base(const debug_iterator_registry* registry);

    //! Copy constructor.
    debug_iterator_base(const debug_iterator_base& rhs);

    //! Destructor.
    ~debug_iterator_base();

// Methods

    //! Assign operator.
    debug_iterator_base& operator = (const debug_iterator_base& rhs);

    //! Is the iterator valid?
    bool is_valid(const debug_iterator_registry* registry) const;

    //! Invalidate the iterator.
    /*!
        \note The method is const in order to invalidate const iterators, too.
    */
    void invalidate() const;

    //! Return the next iterator in the iterator chain.
    const debug_iterator_base* next() const;

    //! Set the next iterator in the iterator chain.
    /*!
        \note The method is const in order to set a next iterator to a const iterator, too.
    */
    void set_next(const debug_iterator_base* it) const;

private:
// Helpers

    //! Register self as a valid iterator.
    void register_self();

    //! Unregister self from valid iterators.
    void unregister_self();
};

/*!
    \class debug_iterator_registry
    \brief Registry of valid iterators.

    This class is intended to be a base class of a container.
*/
class debug_iterator_registry {

    //! Pointer to the chain of valid iterators.
    mutable const debug_iterator_base* m_iterators;

public:
// Methods

    //! Default constructor.
    debug_iterator_registry() : m_iterators(0) {}

    //! Register an iterator into the list of valid iterators.
    /*!
        \note The method is const in order to register iterators into const containers, too.
    */
    void register_iterator(const debug_iterator_base* it) const {
        it->set_next(m_iterators);
        m_iterators = it;
    }

    //! Unregister an iterator from the list of valid iterators.
    /*!
        \note The method is const in order to unregister iterators from const containers, too.
    */
    void unregister_iterator(const debug_iterator_base* it) const {
        const debug_iterator_base* previous = 0;
        for (const debug_iterator_base* p = m_iterators; p != it; previous = p, p = p->next()) {}
        remove(it, previous);
    }

    //! Invalidate every iterator pointing to the same element as the iterator passed as a parameter.
    template <class Iterator>
    void invalidate_iterators(const Iterator& it) {
        const debug_iterator_base* previous = 0;
        for (const debug_iterator_base* p = m_iterators; p != 0; p = p->next()) {
            if (((Iterator*)p)->m_it == it.m_it) {
                p->invalidate();
                remove(p, previous);
                continue;
            }
            previous = p;
        }
    }

    //! Invalidate all iterators except an iterator poining to the same element as the iterator passed as a parameter.
    template <class Iterator>
    void invalidate_iterators_except(const Iterator& it) {
        const debug_iterator_base* previous = 0;
        for (const debug_iterator_base* p = m_iterators; p != 0; p = p->next()) {
            if (((Iterator*)p)->m_it != it.m_it) {
                p->invalidate();
                remove(p, previous);
                continue;
            }
            previous = p;
        }
    }

    //! Invalidate all iterators.
    void invalidate_all_iterators() {
        for (const debug_iterator_base* p = m_iterators; p != 0; p = p->next())
            p->invalidate();
        m_iterators = 0;
    }

private:
// Helpers

    //! Remove the current iterator from the iterator chain.
    void remove(const debug_iterator_base* current,
                const debug_iterator_base* previous) const {
        if (previous == 0)
            m_iterators = m_iterators->next();
        else
            previous->set_next(current->next());
    }
};

// Implementation of the debug_iterator_base methods.

inline debug_iterator_base::debug_iterator_base() : m_registry(0), m_next(0) {}

inline debug_iterator_base::debug_iterator_base(const debug_iterator_registry* registry)
: m_registry(registry), m_next(0) {
    register_self();
}

inline debug_iterator_base::debug_iterator_base(const debug_iterator_base& rhs)
: m_registry(rhs.m_registry), m_next(0) {
    register_self();
}

inline debug_iterator_base::~debug_iterator_base() { unregister_self(); }

inline debug_iterator_base& debug_iterator_base::operator = (const debug_iterator_base& rhs) {
    if (m_registry == rhs.m_registry)
        return *this;
    unregister_self();
    m_registry = rhs.m_registry;
    register_self();
    return *this;
}

inline bool debug_iterator_base::is_valid(const debug_iterator_registry* registry) const {
    return m_registry == registry;
}

inline void debug_iterator_base::invalidate() const { m_registry = 0; }

inline const debug_iterator_base* debug_iterator_base::next() const { return m_next; }

inline void debug_iterator_base::set_next(const debug_iterator_base* it) const { m_next = it; }

inline void debug_iterator_base::register_self() {
    if (m_registry != 0)
        m_registry->register_iterator(this);
}

inline void debug_iterator_base::unregister_self() {
    if (m_registry != 0)
        m_registry->unregister_iterator(this);
}

#endif // #if BOOST_CB_ENABLE_DEBUG

} // namespace cb_details

} // namespace boost

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_DEBUG_HPP)

/* debug.hpp
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
*/