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