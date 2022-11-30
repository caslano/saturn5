//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_WAIT_LIST_HPP
#define BOOST_COMPUTE_UTILITY_WAIT_LIST_HPP

#include <vector>

#include <boost/compute/config.hpp>

#ifndef BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

#include <boost/compute/event.hpp>

namespace boost {
namespace compute {

template<class T> class future;

/// \class wait_list
/// \brief Stores a list of events.
///
/// The wait_list class stores a set of event objects and can be used to
/// specify dependencies for OpenCL operations or to wait on the host until
/// all of the events have completed.
///
/// This class also provides convenience functions for interacting with
/// OpenCL APIs which typically accept event dependencies as a \c cl_event*
/// pointer and a \c cl_uint size. For example:
/// \code
/// wait_list events = ...;
///
/// clEnqueueNDRangeKernel(..., events.get_event_ptr(), events.size(), ...);
/// \endcode
///
/// \see event, \ref future "future<T>"
class wait_list
{
public:
    typedef std::vector<event>::iterator iterator;
    typedef std::vector<event>::const_iterator const_iterator;

    /// Creates an empty wait-list.
    wait_list()
    {
    }

    /// Creates a wait-list containing \p event.
    wait_list(const event &event)
    {
        insert(event);
    }

    /// Creates a new wait-list as a copy of \p other.
    wait_list(const wait_list &other)
        : m_events(other.m_events)
    {
    }

    #ifndef BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST
    /// Creates a wait-list from \p events
    wait_list(std::initializer_list<event> events)
        : m_events(events)
    {
    }
    #endif // BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST

    /// Copies the events in the wait-list from \p other.
    wait_list& operator=(const wait_list &other)
    {
        if(this != &other){
            m_events = other.m_events;
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new wait list object from \p other.
    wait_list(wait_list&& other)
        : m_events(std::move(other.m_events))
    {
    }

    /// Move-assigns the wait list from \p other to \c *this.
    wait_list& operator=(wait_list&& other)
    {
        m_events = std::move(other.m_events);

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the wait-list.
    ~wait_list()
    {
    }

    /// Returns \c true if the wait-list is empty.
    bool empty() const
    {
        return m_events.empty();
    }

    /// Returns the number of events in the wait-list.
    uint_ size() const
    {
        return static_cast<uint_>(m_events.size());
    }

    /// Removes all of the events from the wait-list.
    void clear()
    {
        m_events.clear();
    }

    /// Returns a cl_event pointer to the first event in the wait-list.
    /// Returns \c 0 if the wait-list is empty.
    ///
    /// This can be used to pass the wait-list to OpenCL functions which
    /// expect a \c cl_event pointer to refer to a list of events.
    const cl_event* get_event_ptr() const
    {
        if(empty()){
            return 0;
        }

        return reinterpret_cast<const cl_event *>(&m_events[0]);
    }

    /// Reserves a minimum length of storage for the wait list object.
    void reserve(size_t new_capacity) {
        m_events.reserve(new_capacity);
    }

    /// Inserts \p event into the wait-list.
    void insert(const event &event)
    {
        m_events.push_back(event);
    }

    /// Inserts the event from \p future into the wait-list.
    template<class T>
    void insert(const future<T> &future)
    {
        insert(future.get_event());
    }

    /// Blocks until all of the events in the wait-list have completed.
    ///
    /// Does nothing if the wait-list is empty.
    void wait() const
    {
        if(!empty()){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clWaitForEvents(size(), get_event_ptr())
            );
        }
    }

    /// Returns a reference to the event at specified location \p pos.
    const event& operator[](size_t pos) const {
        return m_events[pos];
    }

    /// Returns a reference to the event at specified location \p pos.
    event& operator[](size_t pos) {
        return m_events[pos];
    }

    /// Returns an iterator to the first element of the wait-list.
    iterator begin() {
        return m_events.begin();
    }

    /// Returns an iterator to the first element of the wait-list.
    const_iterator begin() const {
        return m_events.begin();
    }

    /// Returns an iterator to the first element of the wait-list.
    const_iterator cbegin() const {
        return m_events.begin();
    }

    /// Returns an iterator to the element following the last element of the wait-list.
    iterator end() {
        return m_events.end();
    }

    /// Returns an iterator to the element following the last element of the wait-list.
    const_iterator end() const {
        return m_events.end();
    }

    /// Returns an iterator to the element following the last element of the wait-list.
    const_iterator cend() const {
        return m_events.end();
    }

private:
    std::vector<event> m_events;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_UTILITY_WAIT_LIST_HPP

/* wait_list.hpp
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
*/