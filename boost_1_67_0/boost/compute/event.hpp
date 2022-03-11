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