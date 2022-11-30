//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_COMMAND_QUEUE_HPP
#define BOOST_COMPUTE_COMMAND_QUEUE_HPP

#include <cstddef>
#include <algorithm>

#include <boost/assert.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/buffer.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/image/image1d.hpp>
#include <boost/compute/image/image2d.hpp>
#include <boost/compute/image/image3d.hpp>
#include <boost/compute/image/image_object.hpp>
#include <boost/compute/utility/wait_list.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>
#include <boost/compute/detail/diagnostic.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {
namespace detail {

inline void BOOST_COMPUTE_CL_CALLBACK
nullary_native_kernel_trampoline(void *user_func_ptr)
{
    void (*user_func)();
    std::memcpy(&user_func, user_func_ptr, sizeof(user_func));
    user_func();
}

} // end detail namespace

/// \class command_queue
/// \brief A command queue.
///
/// Command queues provide the interface for interacting with compute
/// devices. The command_queue class provides methods to copy data to
/// and from a compute device as well as execute compute kernels.
///
/// Command queues are created for a compute device within a compute
/// context.
///
/// For example, to create a context and command queue for the default device
/// on the system (this is the normal set up code used by almost all OpenCL
/// programs):
/// \code
/// #include <boost/compute/core.hpp>
///
/// // get the default compute device
/// boost::compute::device device = boost::compute::system::default_device();
///
/// // set up a compute context and command queue
/// boost::compute::context context(device);
/// boost::compute::command_queue queue(context, device);
/// \endcode
///
/// The default command queue for the system can be obtained with the
/// system::default_queue() method.
///
/// \see buffer, context, kernel
class command_queue
{
public:
    enum properties {
        enable_profiling = CL_QUEUE_PROFILING_ENABLE,
        enable_out_of_order_execution = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        ,
        on_device = CL_QUEUE_ON_DEVICE,
        on_device_default = CL_QUEUE_ON_DEVICE_DEFAULT
        #endif
    };

    enum map_flags {
        map_read = CL_MAP_READ,
        map_write = CL_MAP_WRITE
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        ,
        map_write_invalidate_region = CL_MAP_WRITE_INVALIDATE_REGION
        #endif
    };

    #ifdef BOOST_COMPUTE_CL_VERSION_1_2
    enum mem_migration_flags {
        migrate_to_host = CL_MIGRATE_MEM_OBJECT_HOST,
        migrate_content_undefined = CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED
    };
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Creates a null command queue.
    command_queue()
        : m_queue(0)
    {
    }

    explicit command_queue(cl_command_queue queue, bool retain = true)
        : m_queue(queue)
    {
        if(m_queue && retain){
            clRetainCommandQueue(m_queue);
        }
    }

    /// Creates a command queue in \p context for \p device with
    /// \p properties.
    ///
    /// \see_opencl_ref{clCreateCommandQueue}
    command_queue(const context &context,
                  const device &device,
                  cl_command_queue_properties properties = 0)
    {
        BOOST_ASSERT(device.id() != 0);

        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        if (device.check_version(2, 0)){
            std::vector<cl_queue_properties> queue_properties;
            if(properties){
                queue_properties.push_back(CL_QUEUE_PROPERTIES);
                queue_properties.push_back(cl_queue_properties(properties));
                queue_properties.push_back(cl_queue_properties(0));
            }

            const cl_queue_properties *queue_properties_ptr =
                queue_properties.empty() ? 0 : &queue_properties[0];

            m_queue = clCreateCommandQueueWithProperties(
                context, device.id(), queue_properties_ptr, &error
            );
        } else
        #endif
        {
            // Suppress deprecated declarations warning
            BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
            m_queue = clCreateCommandQueue(
                context, device.id(), properties, &error
            );
            BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();
        }

        if(!m_queue){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new command queue object as a copy of \p other.
    command_queue(const command_queue &other)
        : m_queue(other.m_queue)
    {
        if(m_queue){
            clRetainCommandQueue(m_queue);
        }
    }

    /// Copies the command queue object from \p other to \c *this.
    command_queue& operator=(const command_queue &other)
    {
        if(this != &other){
            if(m_queue){
                clReleaseCommandQueue(m_queue);
            }

            m_queue = other.m_queue;

            if(m_queue){
                clRetainCommandQueue(m_queue);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new command queue object from \p other.
    command_queue(command_queue&& other) BOOST_NOEXCEPT
        : m_queue(other.m_queue)
    {
        other.m_queue = 0;
    }

    /// Move-assigns the command queue from \p other to \c *this.
    command_queue& operator=(command_queue&& other) BOOST_NOEXCEPT
    {
        if(m_queue){
            clReleaseCommandQueue(m_queue);
        }

        m_queue = other.m_queue;
        other.m_queue = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the command queue.
    ///
    /// \see_opencl_ref{clReleaseCommandQueue}
    ~command_queue()
    {
        if(m_queue){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseCommandQueue(m_queue)
            );
        }
    }

    /// Returns the underlying OpenCL command queue.
    cl_command_queue& get() const
    {
        return const_cast<cl_command_queue &>(m_queue);
    }

    /// Returns the device that the command queue issues commands to.
    device get_device() const
    {
        return device(get_info<cl_device_id>(CL_QUEUE_DEVICE));
    }

    /// Returns the context for the command queue.
    context get_context() const
    {
        return context(get_info<cl_context>(CL_QUEUE_CONTEXT));
    }

    /// Returns information about the command queue.
    ///
    /// \see_opencl_ref{clGetCommandQueueInfo}
    template<class T>
    T get_info(cl_command_queue_info info) const
    {
        return detail::get_object_info<T>(clGetCommandQueueInfo, m_queue, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<command_queue, Enum>::type
    get_info() const;

    /// Returns the properties for the command queue.
    cl_command_queue_properties get_properties() const
    {
        return get_info<cl_command_queue_properties>(CL_QUEUE_PROPERTIES);
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Returns the current default device command queue for the underlying device.
    ///
    /// \opencl_version_warning{2,1}
    command_queue get_default_device_queue() const
    {
        return command_queue(get_info<cl_command_queue>(CL_QUEUE_DEVICE_DEFAULT));
    }

    /// Replaces the default device command queue for the underlying device
    /// with this command queue. Command queue must have been created
    /// with CL_QUEUE_ON_DEVICE flag.
    ///
    /// \see_opencl21_ref{clSetDefaultDeviceCommandQueue}
    ///
    /// \opencl_version_warning{2,1}
    void set_as_default_device_queue() const
    {
        cl_int ret = clSetDefaultDeviceCommandQueue(
            this->get_context().get(),
            this->get_device().get(),
            m_queue
        );
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    /// Enqueues a command to read data from \p buffer to host memory.
    ///
    /// \see_opencl_ref{clEnqueueReadBuffer}
    ///
    /// \see copy()
    event enqueue_read_buffer(const buffer &buffer,
                              size_t offset,
                              size_t size,
                              void *host_ptr,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBuffer(
            m_queue,
            buffer.get(),
            CL_TRUE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to read data from \p buffer to host memory. The
    /// copy will be performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueReadBuffer}
    ///
    /// \see copy_async()
    event enqueue_read_buffer_async(const buffer &buffer,
                                    size_t offset,
                                    size_t size,
                                    void *host_ptr,
                                    const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBuffer(
            m_queue,
            buffer.get(),
            CL_FALSE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to read a rectangular region from \p buffer to
    /// host memory.
    ///
    /// \see_opencl_ref{clEnqueueReadBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_read_buffer_rect(const buffer &buffer,
                                   const size_t buffer_origin[3],
                                   const size_t host_origin[3],
                                   const size_t region[3],
                                   size_t buffer_row_pitch,
                                   size_t buffer_slice_pitch,
                                   size_t host_row_pitch,
                                   size_t host_slice_pitch,
                                   void *host_ptr,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBufferRect(
            m_queue,
            buffer.get(),
            CL_TRUE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to read a rectangular region from \p buffer to
    /// host memory. The copy will be performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueReadBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_read_buffer_rect_async(const buffer &buffer,
                                         const size_t buffer_origin[3],
                                         const size_t host_origin[3],
                                         const size_t region[3],
                                         size_t buffer_row_pitch,
                                         size_t buffer_slice_pitch,
                                         size_t host_row_pitch,
                                         size_t host_slice_pitch,
                                         void *host_ptr,
                                         const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueReadBufferRect(
            m_queue,
            buffer.get(),
            CL_FALSE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    /// Enqueues a command to write data from host memory to \p buffer.
    ///
    /// \see_opencl_ref{clEnqueueWriteBuffer}
    ///
    /// \see copy()
    event enqueue_write_buffer(const buffer &buffer,
                               size_t offset,
                               size_t size,
                               const void *host_ptr,
                               const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBuffer(
            m_queue,
            buffer.get(),
            CL_TRUE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to write data from host memory to \p buffer.
    /// The copy is performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueWriteBuffer}
    ///
    /// \see copy_async()
    event enqueue_write_buffer_async(const buffer &buffer,
                                     size_t offset,
                                     size_t size,
                                     const void *host_ptr,
                                     const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBuffer(
            m_queue,
            buffer.get(),
            CL_FALSE,
            offset,
            size,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to write a rectangular region from host memory
    /// to \p buffer.
    ///
    /// \see_opencl_ref{clEnqueueWriteBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_write_buffer_rect(const buffer &buffer,
                                    const size_t buffer_origin[3],
                                    const size_t host_origin[3],
                                    const size_t region[3],
                                    size_t buffer_row_pitch,
                                    size_t buffer_slice_pitch,
                                    size_t host_row_pitch,
                                    size_t host_slice_pitch,
                                    void *host_ptr,
                                    const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBufferRect(
            m_queue,
            buffer.get(),
            CL_TRUE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to write a rectangular region from host memory
    /// to \p buffer. The copy is performed asynchronously.
    ///
    /// \see_opencl_ref{clEnqueueWriteBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_write_buffer_rect_async(const buffer &buffer,
                                          const size_t buffer_origin[3],
                                          const size_t host_origin[3],
                                          const size_t region[3],
                                          size_t buffer_row_pitch,
                                          size_t buffer_slice_pitch,
                                          size_t host_row_pitch,
                                          size_t host_slice_pitch,
                                          void *host_ptr,
                                          const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(buffer.get_context() == this->get_context());
        BOOST_ASSERT(host_ptr != 0);

        event event_;

        cl_int ret = clEnqueueWriteBufferRect(
            m_queue,
            buffer.get(),
            CL_FALSE,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    /// Enqueues a command to copy data from \p src_buffer to
    /// \p dst_buffer.
    ///
    /// \see_opencl_ref{clEnqueueCopyBuffer}
    ///
    /// \see copy()
    event enqueue_copy_buffer(const buffer &src_buffer,
                              const buffer &dst_buffer,
                              size_t src_offset,
                              size_t dst_offset,
                              size_t size,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(src_offset + size <= src_buffer.size());
        BOOST_ASSERT(dst_offset + size <= dst_buffer.size());
        BOOST_ASSERT(src_buffer.get_context() == this->get_context());
        BOOST_ASSERT(dst_buffer.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueCopyBuffer(
            m_queue,
            src_buffer.get(),
            dst_buffer.get(),
            src_offset,
            dst_offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to copy a rectangular region from
    /// \p src_buffer to \p dst_buffer.
    ///
    /// \see_opencl_ref{clEnqueueCopyBufferRect}
    ///
    /// \opencl_version_warning{1,1}
    event enqueue_copy_buffer_rect(const buffer &src_buffer,
                                   const buffer &dst_buffer,
                                   const size_t src_origin[3],
                                   const size_t dst_origin[3],
                                   const size_t region[3],
                                   size_t buffer_row_pitch,
                                   size_t buffer_slice_pitch,
                                   size_t host_row_pitch,
                                   size_t host_slice_pitch,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(src_buffer.get_context() == this->get_context());
        BOOST_ASSERT(dst_buffer.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueCopyBufferRect(
            m_queue,
            src_buffer.get(),
            dst_buffer.get(),
            src_origin,
            dst_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to fill \p buffer with \p pattern.
    ///
    /// \see_opencl_ref{clEnqueueFillBuffer}
    ///
    /// \opencl_version_warning{1,2}
    ///
    /// \see fill()
    event enqueue_fill_buffer(const buffer &buffer,
                              const void *pattern,
                              size_t pattern_size,
                              size_t offset,
                              size_t size,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(offset + size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueFillBuffer(
            m_queue,
            buffer.get(),
            pattern,
            pattern_size,
            offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Enqueues a command to map \p buffer into the host address space.
    /// Event associated with map operation is returned through
    /// \p map_buffer_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapBuffer}
    void* enqueue_map_buffer(const buffer &buffer,
                             cl_map_flags flags,
                             size_t offset,
                             size_t size,
                             event &map_buffer_event,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(offset + size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapBuffer(
            m_queue,
            buffer.get(),
            CL_TRUE,
            flags,
            offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &map_buffer_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// \overload
    void* enqueue_map_buffer(const buffer &buffer,
                             cl_map_flags flags,
                             size_t offset,
                             size_t size,
                             const wait_list &events = wait_list())
    {
        event event_;
        return enqueue_map_buffer(buffer, flags, offset, size, event_, events);
    }

    /// Enqueues a command to map \p buffer into the host address space.
    /// Map operation is performed asynchronously. The pointer to the mapped
    /// region cannot be used until the map operation has completed.
    ///
    /// Event associated with map operation is returned through
    /// \p map_buffer_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapBuffer}
    void* enqueue_map_buffer_async(const buffer &buffer,
                                   cl_map_flags flags,
                                   size_t offset,
                                   size_t size,
                                   event &map_buffer_event,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(offset + size <= buffer.size());
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapBuffer(
            m_queue,
            buffer.get(),
            CL_FALSE,
            flags,
            offset,
            size,
            events.size(),
            events.get_event_ptr(),
            &map_buffer_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// Enqueues a command to unmap \p buffer from the host memory space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    event enqueue_unmap_buffer(const buffer &buffer,
                               void *mapped_ptr,
                               const wait_list &events = wait_list())
    {
        BOOST_ASSERT(buffer.get_context() == this->get_context());

        return enqueue_unmap_mem_object(buffer.get(), mapped_ptr, events);
    }

    /// Enqueues a command to unmap \p mem from the host memory space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    event enqueue_unmap_mem_object(cl_mem mem,
                                   void *mapped_ptr,
                                   const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueUnmapMemObject(
            m_queue,
            mem,
            mapped_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to read data from \p image to host memory.
    ///
    /// \see_opencl_ref{clEnqueueReadImage}
    event enqueue_read_image(const image_object& image,
                             const size_t *origin,
                             const size_t *region,
                             size_t row_pitch,
                             size_t slice_pitch,
                             void *host_ptr,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueReadImage(
            m_queue,
            image.get(),
            CL_TRUE,
            origin,
            region,
            row_pitch,
            slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_read_image(const image_object& image,
                             const extents<N> origin,
                             const extents<N> region,
                             void *host_ptr,
                             size_t row_pitch = 0,
                             size_t slice_pitch = 0,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_read_image(
            image, origin3, region3, row_pitch, slice_pitch, host_ptr, events
        );
    }

    /// Enqueues a command to write data from host memory to \p image.
    ///
    /// \see_opencl_ref{clEnqueueWriteImage}
    event enqueue_write_image(image_object& image,
                              const size_t *origin,
                              const size_t *region,
                              const void *host_ptr,
                              size_t input_row_pitch = 0,
                              size_t input_slice_pitch = 0,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueWriteImage(
            m_queue,
            image.get(),
            CL_TRUE,
            origin,
            region,
            input_row_pitch,
            input_slice_pitch,
            host_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_write_image(image_object& image,
                              const extents<N> origin,
                              const extents<N> region,
                              const void *host_ptr,
                              const size_t input_row_pitch = 0,
                              const size_t input_slice_pitch = 0,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_write_image(
            image, origin3, region3, host_ptr, input_row_pitch, input_slice_pitch, events
        );
    }

    /// Enqueues a command to map \p image into the host address space.
    ///
    /// Event associated with map operation is returned through
    /// \p map_image_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapImage}
    void* enqueue_map_image(const image_object &image,
                            cl_map_flags flags,
                            const size_t *origin,
                            const size_t *region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            event &map_image_event,
                            const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(image.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapImage(
            m_queue,
            image.get(),
            CL_TRUE,
            flags,
            origin,
            region,
            &output_row_pitch,
            &output_slice_pitch,
            events.size(),
            events.get_event_ptr(),
            &map_image_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// \overload
    void* enqueue_map_image(const image_object &image,
                            cl_map_flags flags,
                            const size_t *origin,
                            const size_t *region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            const wait_list &events = wait_list())
    {
        event event_;
        return enqueue_map_image(
            image, flags, origin, region,
            output_row_pitch, output_slice_pitch, event_, events
        );
    }

    /// \overload
    template<size_t N>
    void* enqueue_map_image(image_object& image,
                            cl_map_flags flags,
                            const extents<N> origin,
                            const extents<N> region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            event &map_image_event,
                            const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_map_image(
            image, flags, origin3, region3,
            output_row_pitch, output_slice_pitch, map_image_event, events
        );
    }

    /// \overload
    template<size_t N>
    void* enqueue_map_image(image_object& image,
                            cl_map_flags flags,
                            const extents<N> origin,
                            const extents<N> region,
                            size_t &output_row_pitch,
                            size_t &output_slice_pitch,
                            const wait_list &events = wait_list())
    {
        event event_;
        return enqueue_map_image(
            image, flags, origin, region,
            output_row_pitch, output_slice_pitch, event_, events
        );
    }

    /// Enqueues a command to map \p image into the host address space.
    /// Map operation is performed asynchronously. The pointer to the mapped
    /// region cannot be used until the map operation has completed.
    ///
    /// Event associated with map operation is returned through
    /// \p map_image_event parameter.
    ///
    /// \see_opencl_ref{clEnqueueMapImage}
    void* enqueue_map_image_async(const image_object &image,
                                  cl_map_flags flags,
                                  const size_t *origin,
                                  const size_t *region,
                                  size_t &output_row_pitch,
                                  size_t &output_slice_pitch,
                                  event &map_image_event,
                                  const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(image.get_context() == this->get_context());

        cl_int ret = 0;
        void *pointer = clEnqueueMapImage(
            m_queue,
            image.get(),
            CL_FALSE,
            flags,
            origin,
            region,
            &output_row_pitch,
            &output_slice_pitch,
            events.size(),
            events.get_event_ptr(),
            &map_image_event.get(),
            &ret
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return pointer;
    }

    /// \overload
    template<size_t N>
    void* enqueue_map_image_async(image_object& image,
                                  cl_map_flags flags,
                                  const extents<N> origin,
                                  const extents<N> region,
                                  size_t &output_row_pitch,
                                  size_t &output_slice_pitch,
                                  event &map_image_event,
                                  const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_map_image_async(
            image, flags, origin3, region3,
            output_row_pitch, output_slice_pitch, map_image_event, events
        );
    }

    /// Enqueues a command to unmap \p image from the host memory space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    event enqueue_unmap_image(const image_object &image,
                              void *mapped_ptr,
                              const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        return enqueue_unmap_mem_object(image.get(), mapped_ptr, events);
    }

    /// Enqueues a command to copy data from \p src_image to \p dst_image.
    ///
    /// \see_opencl_ref{clEnqueueCopyImage}
    event enqueue_copy_image(const image_object& src_image,
                             image_object& dst_image,
                             const size_t *src_origin,
                             const size_t *dst_origin,
                             const size_t *region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueCopyImage(
            m_queue,
            src_image.get(),
            dst_image.get(),
            src_origin,
            dst_origin,
            region,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_copy_image(const image_object& src_image,
                             image_object& dst_image,
                             const extents<N> src_origin,
                             const extents<N> dst_origin,
                             const extents<N> region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(src_image.get_context() == this->get_context());
        BOOST_ASSERT(dst_image.get_context() == this->get_context());
        BOOST_ASSERT_MSG(src_image.format() == dst_image.format(),
                         "Source and destination image formats must match.");

        size_t src_origin3[3] = { 0, 0, 0 };
        size_t dst_origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(src_origin.data(), src_origin.data() + N, src_origin3);
        std::copy(dst_origin.data(), dst_origin.data() + N, dst_origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_copy_image(
            src_image, dst_image, src_origin3, dst_origin3, region3, events
        );
    }

    /// Enqueues a command to copy data from \p src_image to \p dst_buffer.
    ///
    /// \see_opencl_ref{clEnqueueCopyImageToBuffer}
    event enqueue_copy_image_to_buffer(const image_object& src_image,
                                       memory_object& dst_buffer,
                                       const size_t *src_origin,
                                       const size_t *region,
                                       size_t dst_offset,
                                       const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueCopyImageToBuffer(
            m_queue,
            src_image.get(),
            dst_buffer.get(),
            src_origin,
            region,
            dst_offset,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to copy data from \p src_buffer to \p dst_image.
    ///
    /// \see_opencl_ref{clEnqueueCopyBufferToImage}
    event enqueue_copy_buffer_to_image(const memory_object& src_buffer,
                                       image_object& dst_image,
                                       size_t src_offset,
                                       const size_t *dst_origin,
                                       const size_t *region,
                                       const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueCopyBufferToImage(
            m_queue,
            src_buffer.get(),
            dst_image.get(),
            src_offset,
            dst_origin,
            region,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to fill \p image with \p fill_color.
    ///
    /// \see_opencl_ref{clEnqueueFillImage}
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_fill_image(image_object& image,
                             const void *fill_color,
                             const size_t *origin,
                             const size_t *region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueFillImage(
            m_queue,
            image.get(),
            fill_color,
            origin,
            region,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_fill_image(image_object& image,
                             const void *fill_color,
                             const extents<N> origin,
                             const extents<N> region,
                             const wait_list &events = wait_list())
    {
        BOOST_ASSERT(image.get_context() == this->get_context());

        size_t origin3[3] = { 0, 0, 0 };
        size_t region3[3] = { 1, 1, 1 };

        std::copy(origin.data(), origin.data() + N, origin3);
        std::copy(region.data(), region.data() + N, region3);

        return enqueue_fill_image(
            image, fill_color, origin3, region3, events
        );
    }

    /// Enqueues a command to migrate \p mem_objects.
    ///
    /// \see_opencl_ref{clEnqueueMigrateMemObjects}
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_migrate_memory_objects(uint_ num_mem_objects,
                                         const cl_mem *mem_objects,
                                         cl_mem_migration_flags flags,
                                         const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;

        cl_int ret = clEnqueueMigrateMemObjects(
            m_queue,
            num_mem_objects,
            mem_objects,
            flags,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Enqueues a kernel for execution.
    ///
    /// \see_opencl_ref{clEnqueueNDRangeKernel}
    event enqueue_nd_range_kernel(const kernel &kernel,
                                  size_t work_dim,
                                  const size_t *global_work_offset,
                                  const size_t *global_work_size,
                                  const size_t *local_work_size,
                                  const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(kernel.get_context() == this->get_context());

        event event_;

        cl_int ret = clEnqueueNDRangeKernel(
            m_queue,
            kernel,
            static_cast<cl_uint>(work_dim),
            global_work_offset,
            global_work_size,
            local_work_size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// \overload
    template<size_t N>
    event enqueue_nd_range_kernel(const kernel &kernel,
                                  const extents<N> &global_work_offset,
                                  const extents<N> &global_work_size,
                                  const extents<N> &local_work_size,
                                  const wait_list &events = wait_list())
    {
        return enqueue_nd_range_kernel(
            kernel,
            N,
            global_work_offset.data(),
            global_work_size.data(),
            local_work_size.data(),
            events
        );
    }

    /// Convenience method which calls enqueue_nd_range_kernel() with a
    /// one-dimensional range.
    event enqueue_1d_range_kernel(const kernel &kernel,
                                  size_t global_work_offset,
                                  size_t global_work_size,
                                  size_t local_work_size,
                                  const wait_list &events = wait_list())
    {
        return enqueue_nd_range_kernel(
            kernel,
            1,
            &global_work_offset,
            &global_work_size,
            local_work_size ? &local_work_size : 0,
            events
        );
    }

    /// Enqueues a kernel to execute using a single work-item.
    ///
    /// \see_opencl_ref{clEnqueueTask}
    event enqueue_task(const kernel &kernel, const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);
        BOOST_ASSERT(kernel.get_context() == this->get_context());

        event event_;

        // clEnqueueTask() was deprecated in OpenCL 2.0. In that case we
        // just forward to the equivalent clEnqueueNDRangeKernel() call.
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        size_t one = 1;
        cl_int ret = clEnqueueNDRangeKernel(
            m_queue, kernel, 1, 0, &one, &one,
            events.size(), events.get_event_ptr(), &event_.get()
        );
        #else
        cl_int ret = clEnqueueTask(
            m_queue, kernel, events.size(), events.get_event_ptr(), &event_.get()
        );
        #endif

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a function to execute on the host.
    event enqueue_native_kernel(void (BOOST_COMPUTE_CL_CALLBACK *user_func)(void *),
                                void *args,
                                size_t cb_args,
                                uint_ num_mem_objects,
                                const cl_mem *mem_list,
                                const void **args_mem_loc,
                                const wait_list &events = wait_list())
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;
        cl_int ret = clEnqueueNativeKernel(
            m_queue,
            user_func,
            args,
            cb_args,
            num_mem_objects,
            mem_list,
            args_mem_loc,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Convenience overload for enqueue_native_kernel() which enqueues a
    /// native kernel on the host with a nullary function.
    event enqueue_native_kernel(void (BOOST_COMPUTE_CL_CALLBACK *user_func)(void),
                                const wait_list &events = wait_list())
    {
        return enqueue_native_kernel(
            detail::nullary_native_kernel_trampoline,
            reinterpret_cast<void *>(&user_func),
            sizeof(user_func),
            0,
            0,
            0,
            events
        );
    }

    /// Flushes the command queue.
    ///
    /// \see_opencl_ref{clFlush}
    void flush()
    {
        BOOST_ASSERT(m_queue != 0);

        cl_int ret = clFlush(m_queue);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    /// Blocks until all outstanding commands in the queue have finished.
    ///
    /// \see_opencl_ref{clFinish}
    void finish()
    {
        BOOST_ASSERT(m_queue != 0);

        cl_int ret = clFinish(m_queue);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    /// Enqueues a barrier in the queue.
    void enqueue_barrier()
    {
        BOOST_ASSERT(m_queue != 0);
        cl_int ret = CL_SUCCESS;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(get_device().check_version(1, 2)){
            ret = clEnqueueBarrierWithWaitList(m_queue, 0, 0, 0);
        } else
        #endif // BOOST_COMPUTE_CL_VERSION_1_2
        {
            // Suppress deprecated declarations warning
            BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
            ret = clEnqueueBarrier(m_queue);
            BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();
        }

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a barrier in the queue after \p events.
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_barrier(const wait_list &events)
    {
        BOOST_ASSERT(m_queue != 0);

        event event_;
        cl_int ret = CL_SUCCESS;

        ret = clEnqueueBarrierWithWaitList(
            m_queue, events.size(), events.get_event_ptr(), &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Enqueues a marker in the queue and returns an event that can be
    /// used to track its progress.
    event enqueue_marker()
    {
        event event_;
        cl_int ret = CL_SUCCESS;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(get_device().check_version(1, 2)){
            ret = clEnqueueMarkerWithWaitList(m_queue, 0, 0, &event_.get());
        } else
        #endif
        {
            // Suppress deprecated declarations warning
            BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
            ret = clEnqueueMarker(m_queue, &event_.get());
            BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();
        }

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a marker after \p events in the queue and returns an
    /// event that can be used to track its progress.
    ///
    /// \opencl_version_warning{1,2}
    event enqueue_marker(const wait_list &events)
    {
        event event_;

        cl_int ret = clEnqueueMarkerWithWaitList(
            m_queue, events.size(), events.get_event_ptr(), &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    #if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to copy \p size bytes of data from \p src_ptr to
    /// \p dst_ptr.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMemcpy}
    event enqueue_svm_memcpy(void *dst_ptr,
                             const void *src_ptr,
                             size_t size,
                             const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMemcpy(
            m_queue,
            CL_TRUE,
            dst_ptr,
            src_ptr,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to copy \p size bytes of data from \p src_ptr to
    /// \p dst_ptr. The operation is performed asynchronously.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMemcpy}
    event enqueue_svm_memcpy_async(void *dst_ptr,
                                   const void *src_ptr,
                                   size_t size,
                                   const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMemcpy(
            m_queue,
            CL_FALSE,
            dst_ptr,
            src_ptr,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to fill \p size bytes of data at \p svm_ptr with
    /// \p pattern.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMemFill}
    event enqueue_svm_fill(void *svm_ptr,
                           const void *pattern,
                           size_t pattern_size,
                           size_t size,
                           const wait_list &events = wait_list())

    {
        event event_;

        cl_int ret = clEnqueueSVMMemFill(
            m_queue,
            svm_ptr,
            pattern,
            pattern_size,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to free \p svm_ptr.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMFree}
    ///
    /// \see svm_free()
    event enqueue_svm_free(void *svm_ptr,
                           const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMFree(
            m_queue,
            1,
            &svm_ptr,
            0,
            0,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to map \p svm_ptr to the host memory space.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMMap}
    event enqueue_svm_map(void *svm_ptr,
                          size_t size,
                          cl_map_flags flags,
                          const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMap(
            m_queue,
            CL_TRUE,
            flags,
            svm_ptr,
            size,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to unmap \p svm_ptr from the host memory space.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clEnqueueSVMUnmap}
    event enqueue_svm_unmap(void *svm_ptr,
                            const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMUnmap(
            m_queue,
            svm_ptr,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_0

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Enqueues a command to indicate which device a set of ranges of SVM allocations
    /// should be associated with. The pair \p svm_ptrs[i] and \p sizes[i] together define
    /// the starting address and number of bytes in a range to be migrated.
    ///
    /// If \p sizes is empty, then that means every allocation containing any \p svm_ptrs[i]
    /// is to be migrated. Also, if \p sizes[i] is zero, then the entire allocation containing
    /// \p svm_ptrs[i] is migrated.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl21_ref{clEnqueueSVMMigrateMem}
    event enqueue_svm_migrate_memory(const std::vector<const void*> &svm_ptrs,
                                     const std::vector<size_t> &sizes,
                                     const cl_mem_migration_flags flags = 0,
                                     const wait_list &events = wait_list())
    {
        BOOST_ASSERT(svm_ptrs.size() == sizes.size() || sizes.size() == 0);
        event event_;

        cl_int ret = clEnqueueSVMMigrateMem(
            m_queue,
            static_cast<cl_uint>(svm_ptrs.size()),
            const_cast<void const **>(&svm_ptrs[0]),
            sizes.size() > 0 ? &sizes[0] : NULL,
            flags,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }

    /// Enqueues a command to indicate which device a range of SVM allocation
    /// should be associated with. The pair \p svm_ptr and \p size together define
    /// the starting address and number of bytes in a range to be migrated.
    ///
    /// If \p size is 0, then the entire allocation containing \p svm_ptr is
    /// migrated. The default value for \p size is 0.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl21_ref{clEnqueueSVMMigrateMem}
    event enqueue_svm_migrate_memory(const void* svm_ptr,
                                     const size_t size = 0,
                                     const cl_mem_migration_flags flags = 0,
                                     const wait_list &events = wait_list())
    {
        event event_;

        cl_int ret = clEnqueueSVMMigrateMem(
            m_queue,
            cl_uint(1),
            &svm_ptr,
            &size,
            flags,
            events.size(),
            events.get_event_ptr(),
            &event_.get()
        );

        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        return event_;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    /// Returns \c true if the command queue is the same at \p other.
    bool operator==(const command_queue &other) const
    {
        return m_queue == other.m_queue;
    }

    /// Returns \c true if the command queue is different from \p other.
    bool operator!=(const command_queue &other) const
    {
        return m_queue != other.m_queue;
    }

    /// \internal_
    operator cl_command_queue() const
    {
        return m_queue;
    }

    /// \internal_
    bool check_device_version(int major, int minor) const
    {
        return get_device().check_version(major, minor);
    }

private:
    cl_command_queue m_queue;
};

inline buffer buffer::clone(command_queue &queue) const
{
    buffer copy(get_context(), size(), get_memory_flags());
    queue.enqueue_copy_buffer(*this, copy, 0, 0, size());
    return copy;
}

inline image1d image1d::clone(command_queue &queue) const
{
    image1d copy(
        get_context(), width(), format(), get_memory_flags()
    );

    queue.enqueue_copy_image(*this, copy, origin(), copy.origin(), size());

    return copy;
}

inline image2d image2d::clone(command_queue &queue) const
{
    image2d copy(
        get_context(), width(), height(), format(), get_memory_flags()
    );

    queue.enqueue_copy_image(*this, copy, origin(), copy.origin(), size());

    return copy;
}

inline image3d image3d::clone(command_queue &queue) const
{
    image3d copy(
        get_context(), width(), height(), depth(), format(), get_memory_flags()
    );

    queue.enqueue_copy_image(*this, copy, origin(), copy.origin(), size());

    return copy;
}

/// \internal_ define get_info() specializations for command_queue
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(command_queue,
    ((cl_context, CL_QUEUE_CONTEXT))
    ((cl_device_id, CL_QUEUE_DEVICE))
    ((uint_, CL_QUEUE_REFERENCE_COUNT))
    ((cl_command_queue_properties, CL_QUEUE_PROPERTIES))
)

#ifdef BOOST_COMPUTE_CL_VERSION_2_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(command_queue,
    ((cl_command_queue, CL_QUEUE_DEVICE_DEFAULT))
)
#endif // BOOST_COMPUTE_CL_VERSION_2_1

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_COMMAND_QUEUE_HPP

/* command_queue.hpp
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
*/