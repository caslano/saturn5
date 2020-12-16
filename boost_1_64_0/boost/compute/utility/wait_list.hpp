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
LEuK2vMF/tUtFq73e7He3Arc2pc0zkvGGId9Y57AO6U2B70SnL/tBMfe3xz44tjDOO39VF2u8X3EW74IHyGyKTe5wj0NcOYpHDr52UM6vCnw0oIc1IHL1qBxI2kZPdK+/IjEaQ/ZqOgmbXzD9w/j6BCyi2zOBx79P1zelAb5eENbTo8R4Bx4Y5uj987BudPBwXvfjZ+oN7U52DM3dPfNA8TDONFs+yOtM2/uwmfWNtaZvzPGoQ+G2ebvMRxFRhovvYXhVBT96hjikAcmnLMmzd1YvwJujXfNOE0/N+1UHcmsz9NuZf/UxninmI1RlfA8x3Oj+P798uox6v2Gn6J3meMHpU33dS7RgN9YrQz49Wgnf/M8p+M7ecfmy3zJLra8QD1NNhrIQBc0xhgyyM+srFaZCHjq7RDwkI+V5TlNwzcw327x7ExAH2SHZnB7/18ftxl/uD5ONuelu7r4w5WCue0WZt8a+06V5LXQNc1t4F80uW4i8ipJM69wxenVxY0vza5LS/R+Q4NBfF8+bWwVt1jfQbd0o6T2BZnanJHnPtSIZ6o6KOVNhZnnvOPK8ObExoJ+nEPIz14T120rrjhK0iorg+646OiEIsulUpRhWk1x0T7v4Qm5bvuYMTdurv7LNfoTGr/XhZONqt7r/5b8ll6jbzJ/g1aFX6dw/gatknlZYjcVRk6H1PVrrMPzUbqDPXNpUV1Tk5cyMfehNSZhZDI9s7SwsrZg2gLc2ioxs68jszIa822qMfBQHvNe+PQ2wnXq5jd6O4VrAazwjDdNx018Xlbb+uoLBv7oThPHhgzGwyu7DJx1EMQh56/EoSahM0C7KT3j/eq9wPsJWPjSQ8DNSsH345mJThylgb9Cxmu/cfrlhxnOIzF08jeDN9cQzbes9gNnjwtD/lHgqiEtaj9++D68geMUgZn+2hs5vql98OEtozeZuGqnqK/5AxaGAg7m21eHzbfJAsV4v+rGOw2eMi+Q1yVWRubLZuwY5d+n0ourOvcfeJ8Ufl3+ucUc99w8K4qqFPNke748x+03b49adyo9N/b9uBDN8NIfdk83dolps7drjlFhLkIv8926LIT/7DGd2dXN9bkFI+PzchKH7Mu4luGD6d9GfqeqvHLcLPNF4mu/Lw3vn2a5joZ+GOVp7IrGocoafP7cM3jTYVW7uVeHwk+em5Fx61jNuycm/+myzL28TBLFd3zLX9SaWe6jcRLnVZZ74qjtd+iemdfpKinK3HcdkSdy9Hb8dh7G/mXwjydeFaSJHwszv6Lhbph5OJaXmZ/7XiKW5+leep8taPz/wyNy3GF7I7IGZpbUvegGf7GFb8zKtsneNHun/vZS29Z7qrjrDez8C/Kzwt6bJAxzGL0GBX5ujOPoM82erIHDfI5w7Ata+Nr6wiWVN9gSAtdmVoTBNwewzTUJL2JMiMcJa/r0GhvPxndqDLqanTfHjC/vsnEs48BZ2W1xmswRp1l7HzLGC5rvyFVIM3kum3bIxoxSRHlahKHrPOiYQd/yr8nv9ZJqB80g1tuQF/dhV7qmsMaim8ANOWFckhTeTp4Y5YsBvCW0RWPYO1bD6eJF44z0qsGB+002p3sX/Acwnh6WQTXS/YHNXbgM+znsHY9xjt7iMKIzfM5v49xmJwBtzsKpQzwJf7IcUx8rpGK8dW3x9FwM8Tyzg+O6NmALBxvXAQ/rSKkXtHFgvVZ9oK1zTnd9/JrxXr8+XtnFuLw+Gs5uxnnd+tjYw7l2fUzuZTirj5F9DBtaH79iPNSH8b4R4R17y0ad7ZngHHs/H3u1ijd0/w68A48wnj3vwDztm/sZD1s0tn13/WibR9Nq5g/5DeAYcxjj/bI3Auc=
*/