//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EVENT_HPP
#define BOOST_COMPUTE_EVENT_HPP

#include <boost/function.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/detail/duration.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// \class event
/// \brief An event corresponding to an operation on a compute device
///
/// Event objects are used to track operations running on the device (such as
/// kernel executions and memory transfers). Event objects are returned by the
/// various \c enqueue_* methods of the command_queue class.
///
/// Events can be used to synchronize operations between the host and the
/// device. The \c wait() method will block execution on the host until the
/// operation corresponding to the event on the device has completed. The
/// status of the operation can also be polled with the \c status() method.
///
/// Event objects can also be used for performance profiling. In order to use
/// events for profiling, the command queue must be constructed with the
/// \c CL_QUEUE_PROFILING_ENABLE flag. Then the \c duration() method can be
/// used to retrieve the total duration of the operation on the device:
/// \code
/// std::cout << "time = " << e.duration<std::chrono::milliseconds>().count() << "ms\n";
/// \endcode
///
/// \see \ref future "future<T>", wait_list
class event
{
public:
    /// \internal_
    enum execution_status {
        complete = CL_COMPLETE,
        running = CL_RUNNING,
        submitted = CL_SUBMITTED,
        queued = CL_QUEUED
    };

    /// \internal_
    enum command_type {
        ndrange_kernel = CL_COMMAND_NDRANGE_KERNEL,
        task = CL_COMMAND_TASK,
        native_kernel = CL_COMMAND_NATIVE_KERNEL,
        read_buffer = CL_COMMAND_READ_BUFFER,
        write_buffer = CL_COMMAND_WRITE_BUFFER,
        copy_buffer = CL_COMMAND_COPY_BUFFER,
        read_image = CL_COMMAND_READ_IMAGE,
        write_image = CL_COMMAND_WRITE_IMAGE,
        copy_image = CL_COMMAND_COPY_IMAGE,
        copy_image_to_buffer = CL_COMMAND_COPY_IMAGE_TO_BUFFER,
        copy_buffer_to_image = CL_COMMAND_COPY_BUFFER_TO_IMAGE,
        map_buffer = CL_COMMAND_MAP_BUFFER,
        map_image = CL_COMMAND_MAP_IMAGE,
        unmap_mem_object = CL_COMMAND_UNMAP_MEM_OBJECT,
        marker = CL_COMMAND_MARKER,
        aquire_gl_objects = CL_COMMAND_ACQUIRE_GL_OBJECTS,
        release_gl_object = CL_COMMAND_RELEASE_GL_OBJECTS
        #if defined(BOOST_COMPUTE_CL_VERSION_1_1)
        ,
        read_buffer_rect = CL_COMMAND_READ_BUFFER_RECT,
        write_buffer_rect = CL_COMMAND_WRITE_BUFFER_RECT,
        copy_buffer_rect = CL_COMMAND_COPY_BUFFER_RECT
        #endif
    };

    /// \internal_
    enum profiling_info {
        profiling_command_queued = CL_PROFILING_COMMAND_QUEUED,
        profiling_command_submit = CL_PROFILING_COMMAND_SUBMIT,
        profiling_command_start = CL_PROFILING_COMMAND_START,
        profiling_command_end = CL_PROFILING_COMMAND_END
    };

    /// Creates a null event object.
    event()
        : m_event(0)
    {
    }

    explicit event(cl_event event, bool retain = true)
        : m_event(event)
    {
        if(m_event && retain){
            clRetainEvent(event);
        }
    }

    /// Makes a new event as a copy of \p other.
    event(const event &other)
        : m_event(other.m_event)
    {
        if(m_event){
            clRetainEvent(m_event);
        }
    }

    /// Copies the event object from \p other to \c *this.
    event& operator=(const event &other)
    {
        if(this != &other){
            if(m_event){
                clReleaseEvent(m_event);
            }

            m_event = other.m_event;

            if(m_event){
                clRetainEvent(m_event);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new event object from \p other.
    event(event&& other) BOOST_NOEXCEPT
        : m_event(other.m_event)
    {
        other.m_event = 0;
    }

    /// Move-assigns the event from \p other to \c *this.
    event& operator=(event&& other) BOOST_NOEXCEPT
    {
        if(m_event){
            clReleaseEvent(m_event);
        }

        m_event = other.m_event;
        other.m_event = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the event object.
    ~event()
    {
        if(m_event){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseEvent(m_event)
            );
        }
    }

    /// Returns a reference to the underlying OpenCL event object.
    cl_event& get() const
    {
        return const_cast<cl_event &>(m_event);
    }

    /// Returns the status of the event.
    cl_int status() const
    {
        return get_info<cl_int>(CL_EVENT_COMMAND_EXECUTION_STATUS);
    }

    /// Returns the command type for the event.
    cl_command_type get_command_type() const
    {
        return get_info<cl_command_type>(CL_EVENT_COMMAND_TYPE);
    }

    /// Returns information about the event.
    ///
    /// \see_opencl_ref{clGetEventInfo}
    template<class T>
    T get_info(cl_event_info info) const
    {
        return detail::get_object_info<T>(clGetEventInfo, m_event, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<event, Enum>::type
    get_info() const;

    /// Returns profiling information for the event.
    ///
    /// \see event::duration()
    ///
    /// \see_opencl_ref{clGetEventProfilingInfo}
    template<class T>
    T get_profiling_info(cl_profiling_info info) const
    {
        return detail::get_object_info<T>(clGetEventProfilingInfo,
                                          m_event,
                                          info);
    }

    /// Blocks until the actions corresponding to the event have
    /// completed.
    void wait() const
    {
        cl_int ret = clWaitForEvents(1, &m_event);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Registers a function to be called when the event status changes to
    /// \p status (by default CL_COMPLETE). The callback is passed the OpenCL
    /// event object, the event status, and a pointer to arbitrary user data.
    ///
    /// \see_opencl_ref{clSetEventCallback}
    ///
    /// \opencl_version_warning{1,1}
    void set_callback(void (BOOST_COMPUTE_CL_CALLBACK *callback)(
                          cl_event event, cl_int status, void *user_data
                      ),
                      cl_int status = CL_COMPLETE,
                      void *user_data = 0)
    {
        cl_int ret = clSetEventCallback(m_event, status, callback, user_data);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    /// Registers a generic function to be called when the event status
    /// changes to \p status (by default \c CL_COMPLETE).
    ///
    /// The function specified by \p callback must be invokable with zero
    /// arguments (e.g. \c callback()).
    ///
    /// \opencl_version_warning{1,1}
    template<class Function>
    void set_callback(Function callback, cl_int status = CL_COMPLETE)
    {
        set_callback(
            event_callback_invoker,
            status,
            new boost::function<void()>(callback)
        );
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    /// Returns the total duration of the event from \p start to \p end.
    ///
    /// For example, to print the number of milliseconds the event took to
    /// execute:
    /// \code
    /// std::cout << event.duration<std::chrono::milliseconds>().count() << " ms" << std::endl;
    /// \endcode
    ///
    /// \see event::get_profiling_info()
    template<class Duration>
    Duration duration(cl_profiling_info start = CL_PROFILING_COMMAND_START,
                      cl_profiling_info end = CL_PROFILING_COMMAND_END) const
    {
        const ulong_ nanoseconds =
            get_profiling_info<ulong_>(end) - get_profiling_info<ulong_>(start);

        return detail::make_duration_from_nanoseconds(Duration(), nanoseconds);
    }

    /// Returns \c true if the event is the same as \p other.
    bool operator==(const event &other) const
    {
        return m_event == other.m_event;
    }

    /// Returns \c true if the event is different from \p other.
    bool operator!=(const event &other) const
    {
        return m_event != other.m_event;
    }

    /// \internal_
    operator cl_event() const
    {
        return m_event;
    }

    /// \internal_ (deprecated)
    cl_int get_status() const
    {
        return status();
    }

private:
    #ifdef BOOST_COMPUTE_CL_VERSION_1_1
    /// \internal_
    static void BOOST_COMPUTE_CL_CALLBACK
    event_callback_invoker(cl_event, cl_int, void *user_data)
    {
        boost::function<void()> *callback =
            static_cast<boost::function<void()> *>(user_data);

        (*callback)();

        delete callback;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

protected:
    cl_event m_event;
};

/// \internal_ define get_info() specializations for event
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(event,
    ((cl_command_queue, CL_EVENT_COMMAND_QUEUE))
    ((cl_command_type, CL_EVENT_COMMAND_TYPE))
    ((cl_int, CL_EVENT_COMMAND_EXECUTION_STATUS))
    ((cl_uint, CL_EVENT_REFERENCE_COUNT))
)

#ifdef BOOST_COMPUTE_CL_VERSION_1_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(event,
    ((cl_context, CL_EVENT_CONTEXT))
)
#endif

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EVENT_HPP

/* event.hpp
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
*/