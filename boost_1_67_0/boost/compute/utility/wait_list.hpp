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